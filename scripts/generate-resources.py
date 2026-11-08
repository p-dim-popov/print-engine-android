#!/usr/bin/env python3
# print-engine-android: writes the Android resources that describe a data
# directory: the printer table, IEEE 1284 make and model to Gutenprint
# driver, and the version of the data.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# Usage: generate-resources.py DATA_DIR RES_DIR
#
# DATA_DIR is Gutenprint's data directory (scripts/build-data.py makes it).
# RES_DIR gets two resource files:
#
# - xml/print_engine_printers.xml: one <printer mfg="..." mdl="..."
#   driver="..."/> per printer model, where mfg and mdl are the MFG and MDL
#   that the model's IEEE 1284 device ID gives and driver is the name
#   `print-engine --driver` takes;
# - values/print_engine.xml: the string print_engine_data_version, 16 hex
#   digits of a SHA-256 over every file of DATA_DIR, its path and its bytes,
#   so the same data has the same version and any change gives another one.
#
# The rows come from the printers that the data's printers/*.xml lists, read
# as XML, so an entry inside an XML comment, which Gutenprint does not load,
# gives none. A printer gives a row from its device ID (attribute deviceid,
# keys MFG or MANUFACTURER, MDL or MODEL), and one from its manufacturer and
# its name without the manufacturer in front (Canon, "Canon PIXMA MP250": MDL
# "PIXMA MP250"). The device ID rows come first, then the name rows, each in
# the data's order. Two rows whose make and model match once case, spaces and
# a trailing "series" are set aside are one model: only the first is written.
# The raw and ps families give no rows: their drivers write raw pixels and
# PostScript, not a printer model's own language.
import hashlib
import os
import re
import sys
import xml.etree.ElementTree as ET

TABLE = os.path.join("xml", "print_engine_printers.xml")
VALUES = os.path.join("values", "print_engine.xml")
NOT_PRINTER_MODELS = {"raw", "ps"}


def normalised(text):
    """text in lower case, spaces and tabs collapsed, a trailing " series" cut."""
    text = " ".join(word for word in re.split("[ \t]", text.lower()) if word)
    return text.removesuffix(" series")


def key(make, model):
    return f"{normalised(make)}|{normalised(model)}"


def device_id_model(device_id):
    """The (MFG, MDL) of an IEEE 1284 device ID, or None without both."""
    fields = {}
    for field in device_id.split(";"):
        name, colon, value = field.partition(":")
        if colon:
            fields.setdefault(name.strip().upper(), value.strip())
    make = fields.get("MFG") or fields.get("MANUFACTURER")
    model = fields.get("MDL") or fields.get("MODEL")
    return (make, model) if make and model else None


def name_model(manufacturer, name):
    """The (MFG, MDL) a printer's name gives: the name after its manufacturer."""
    manufacturer = manufacturer.strip()
    if not manufacturer or not name.lower().startswith(manufacturer.lower() + " "):
        return None
    return manufacturer, name[len(manufacturer) + 1:].strip()


def local_name(tag):
    return tag.rpartition("}")[2]


def printers(data_dir):
    """The printer elements of the data's printers/*.xml, in file name order,
    without those of the families that are not printer models."""
    directory = os.path.join(data_dir, "printers")
    files = sorted(name for name in os.listdir(directory) if name.endswith(".xml"))
    if not files:
        raise SystemExit(f"generate-resources.py: no printers/*.xml in {data_dir}")
    for name in files:
        root = ET.parse(os.path.join(directory, name)).getroot()
        for family in root.iter():
            if local_name(family.tag) != "family" or family.get("name") in NOT_PRINTER_MODELS:
                continue
            for printer in family:
                if local_name(printer.tag) == "printer" and printer.get("driver"):
                    yield printer


def rows(data_dir):
    """The table's rows, (mfg, mdl, driver), one per model, in order."""
    entries = list(printers(data_dir))
    candidates = []
    for printer in entries:
        model = device_id_model(printer.get("deviceid", ""))
        if model:
            candidates.append((*model, printer.get("driver")))
    for printer in entries:
        model = name_model(printer.get("manufacturer", ""), printer.get("name", ""))
        if model:
            candidates.append((*model, printer.get("driver")))
    seen = set()
    table = []
    for make, model, driver in candidates:
        if key(make, model) not in seen:
            seen.add(key(make, model))
            table.append((make, model, driver))
    return table


def escape(text):
    return (text.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
            .replace('"', "&quot;"))


def data_version(data_dir):
    """16 hex digits of a SHA-256 over each file's path, size and bytes, in
    path order."""
    files = []
    for directory, _, names in os.walk(data_dir):
        for name in names:
            path = os.path.join(directory, name)
            files.append((os.path.relpath(path, data_dir).replace(os.sep, "/"), path))
    digest = hashlib.sha256()
    for relative, path in sorted(files):
        with open(path, "rb") as f:
            content = f.read()
        digest.update(relative.encode() + b"\0" + str(len(content)).encode() + b"\0" + content)
    return digest.hexdigest()[:16]


def write(path, lines):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")


def main(argv):
    if len(argv) != 3:
        sys.stderr.write("usage: generate-resources.py DATA_DIR RES_DIR\n")
        return 2
    data_dir, res_dir = argv[1], argv[2]
    table = rows(data_dir)
    lines = ['<?xml version="1.0" encoding="utf-8"?>',
             "<!-- Generated by scripts/generate-resources.py from Gutenprint's printer data. -->",
             "<print-engine-printers>"]
    lines += [f'    <printer mfg="{escape(make)}" mdl="{escape(model)}" driver="{escape(driver)}" />'
              for make, model, driver in table]
    lines.append("</print-engine-printers>")
    write(os.path.join(res_dir, TABLE), lines)
    version = data_version(data_dir)
    write(os.path.join(res_dir, VALUES), [
        '<?xml version="1.0" encoding="utf-8"?>',
        "<!-- Generated by scripts/generate-resources.py from Gutenprint's data. -->",
        "<resources>",
        "    <!-- Names a copy of the data: another version is other data. -->",
        f'    <string name="print_engine_data_version" translatable="false">{version}</string>',
        "</resources>"])
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
