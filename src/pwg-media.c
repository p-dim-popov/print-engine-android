/* print-engine-android
   Copyright (C) 2026 Petar Popov

   PWG media names (PWG 5101.1) for Gutenprint's papers.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include "pwg-media.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The standard sizes of PWG 5101.1, by their self-describing names. The
   size is read from the name itself. */
static const char *const standard_names[] = {
  "na_index-3x5_3x5in",
  "na_personal_3.625x6.5in",
  "na_monarch_3.875x7.5in",
  "na_number-9_3.875x8.875in",
  "na_index-4x6_4x6in",
  "na_number-10_4.125x9.5in",
  "na_a2_4.375x5.75in",
  "na_number-11_4.5x10.375in",
  "na_number-12_4.75x11in",
  "na_5x7_5x7in",
  "na_index-5x8_5x8in",
  "na_number-14_5x11.5in",
  "na_invoice_5.5x8.5in",
  "na_index-4x6-ext_6x8in",
  "na_6x9_6x9in",
  "na_c5_6.5x9.5in",
  "na_7x9_7x9in",
  "na_executive_7.25x10.5in",
  "na_govt-letter_8x10in",
  "na_govt-legal_8x13in",
  "na_quarto_8.5x10.83in",
  "na_letter_8.5x11in",
  "na_fanfold-eur_8.5x12in",
  "na_letter-plus_8.5x12.69in",
  "na_foolscap_8.5x13in",
  "na_oficio_8.5x13.4in",
  "na_legal_8.5x14in",
  "na_super-a_8.94x14in",
  "na_9x11_9x11in",
  "na_arch-a_9x12in",
  "na_letter-extra_9.5x12in",
  "na_legal-extra_9.5x15in",
  "na_10x11_10x11in",
  "na_10x13_10x13in",
  "na_10x14_10x14in",
  "na_10x15_10x15in",
  "na_11x12_11x12in",
  "na_edp_11x14in",
  "na_fanfold-us_11x14.875in",
  "na_11x15_11x15in",
  "na_ledger_11x17in",
  "na_eur-edp_12x14in",
  "na_arch-b_12x18in",
  "na_12x19_12x19in",
  "na_b-plus_12x19.17in",
  "na_super-b_13x19in",
  "na_c_17x22in",
  "na_arch-c_18x24in",
  "na_d_22x34in",
  "na_arch-d_24x36in",
  "na_arch-e2_26x38in",
  "na_arch-e3_27x39in",
  "asme_f_28x40in",
  "na_wide-format_30x42in",
  "na_e_34x44in",
  "na_arch-e_36x48in",
  "na_f_44x68in",
  "iso_a10_26x37mm",
  "iso_a9_37x52mm",
  "iso_a8_52x74mm",
  "iso_a7_74x105mm",
  "iso_a6_105x148mm",
  "iso_a5_148x210mm",
  "iso_a5-extra_174x235mm",
  "iso_a4_210x297mm",
  "iso_a4-tab_225x297mm",
  "iso_a4-extra_235.5x322.3mm",
  "iso_a3_297x420mm",
  "iso_a4x3_297x630mm",
  "iso_a4x4_297x841mm",
  "iso_a4x5_297x1051mm",
  "iso_a4x6_297x1261mm",
  "iso_a4x7_297x1471mm",
  "iso_a4x8_297x1682mm",
  "iso_a4x9_297x1892mm",
  "iso_a3-extra_322x445mm",
  "iso_a2_420x594mm",
  "iso_a3x3_420x891mm",
  "iso_a3x4_420x1189mm",
  "iso_a3x5_420x1486mm",
  "iso_a3x6_420x1783mm",
  "iso_a3x7_420x2080mm",
  "iso_a1_594x841mm",
  "iso_a2x3_594x1261mm",
  "iso_a2x4_594x1682mm",
  "iso_a2x5_594x2102mm",
  "iso_a0_841x1189mm",
  "iso_a1x3_841x1783mm",
  "iso_a1x4_841x2378mm",
  "iso_2a0_1189x1682mm",
  "iso_a0x3_1189x2523mm",
  "iso_b10_31x44mm",
  "iso_b9_44x62mm",
  "iso_b8_62x88mm",
  "iso_b7_88x125mm",
  "iso_b6_125x176mm",
  "iso_b6c4_125x324mm",
  "iso_b5_176x250mm",
  "iso_b5-extra_201x276mm",
  "iso_b4_250x353mm",
  "iso_b3_353x500mm",
  "iso_b2_500x707mm",
  "iso_b1_707x1000mm",
  "iso_b0_1000x1414mm",
  "iso_c10_28x40mm",
  "iso_c9_40x57mm",
  "iso_c8_57x81mm",
  "iso_c7_81x114mm",
  "iso_c7c6_81x162mm",
  "iso_c6_114x162mm",
  "iso_c6c5_114x229mm",
  "iso_c5_162x229mm",
  "iso_c4_229x324mm",
  "iso_c3_324x458mm",
  "iso_c2_458x648mm",
  "iso_c1_648x917mm",
  "iso_c0_917x1297mm",
  "iso_dl_110x220mm",
  "iso_ra4_215x305mm",
  "iso_sra4_225x320mm",
  "iso_ra3_305x430mm",
  "iso_sra3_320x450mm",
  "iso_ra2_430x610mm",
  "iso_sra2_450x640mm",
  "iso_ra1_610x860mm",
  "iso_sra1_640x900mm",
  "iso_ra0_860x1220mm",
  "iso_sra0_900x1280mm",
  "jis_b10_32x45mm",
  "jis_b9_45x64mm",
  "jis_b8_64x91mm",
  "jis_b7_91x128mm",
  "jis_b6_128x182mm",
  "jis_b5_182x257mm",
  "jis_b4_257x364mm",
  "jis_b3_364x515mm",
  "jis_b2_515x728mm",
  "jis_b1_728x1030mm",
  "jis_b0_1030x1456mm",
  "jis_exec_216x330mm",
  "jpn_kaku1_270x382mm",
  "jpn_kaku2_240x332mm",
  "jpn_kaku3_216x277mm",
  "jpn_kaku4_197x267mm",
  "jpn_kaku5_190x240mm",
  "jpn_kaku7_142x205mm",
  "jpn_kaku8_119x197mm",
  "jpn_chou4_90x205mm",
  "jpn_hagaki_100x148mm",
  "jpn_you4_105x235mm",
  "jpn_you6_98x190mm",
  "jpn_chou2_111.1x146mm",
  "jpn_chou3_120x235mm",
  "jpn_chou40_90x225mm",
  "jpn_oufuku_148x200mm",
  "jpn_kahu_240x322.1mm",
  "prc_32k_97x151mm",
  "prc_1_102x165mm",
  "prc_2_102x176mm",
  "prc_4_110x208mm",
  "prc_8_120x309mm",
  "prc_6_120x320mm",
  "prc_16k_146x215mm",
  "prc_7_160x230mm",
  "om_juuro-ku-kai_198x275mm",
  "om_pa-kai_267x389mm",
  "om_dai-pa-kai_275x395mm",
  "roc_16k_7.75x10.75in",
  "roc_8k_10.75x15.5in",
  "oe_business-card_2x3.5in",
  "oe_photo-l_3.5x5in",
  "oe_square-photo_4x4in",
  "oe_square-photo_5x5in",
  "oe_photo-s8r_8x12in",
  "oe_photo-10r_10x12in",
  "oe_photo-12r_12x15in",
  "oe_12x16_12x16in",
  "oe_14x17_14x17in",
  "oe_photo-14x18_14x18in",
  "oe_photo-16r_16x20in",
  "oe_a2plus_17x24in",
  "oe_18x22_18x22in",
  "oe_photo-20r_20x24in",
  "oe_photo-22x28_22x28in",
  "oe_photo-22r_22x29.5in",
  "oe_photo-24x30_24x30in",
  "oe_photo-24r_24x31.5in",
  "oe_photo-30r_30x40in",
  "om_business-card_55x85mm",
  "om_business-card_55x91mm",
  "om_card_54x86mm",
  "om_square-photo_89x89mm",
  "om_dsc-photo_89x119mm",
  "om_small-photo_100x150mm",
  "om_wide-photo_100x200mm",
  "om_italian_110x230mm",
  "om_medium-photo_130x180mm",
  "om_16k_184x260mm",
  "om_16k_195x270mm",
  "om_large-photo_200x300mm",
  "om_folio_210x330mm",
  "om_folio-sp_215x315mm",
  "om_invite_220x220mm",
  "om_photo-30x40_300x400mm",
  "om_photo-30x45_300x450mm",
  "om_photo-35x46_350x460mm",
  "om_photo-40x60_400x600mm",
  "om_photo-50x75_500x750mm",
  "om_photo-50x76_500x760mm",
  "om_photo-60x90_600x900mm",
};

#define POINTS_PER_INCH 72.0
#define MM_PER_INCH 25.4
/* Gutenprint keeps sizes in whole points, and a few of them are up to a
   millimetre off the standard (its JIS B5 is 182.7 x 256.5 mm), so a
   standard size matches a paper within a millimetre. */
#define TOLERANCE (POINTS_PER_INCH / MM_PER_INCH)

int
pwg_media_size(const char *name, double *width, double *height, int *metric)
{
  const char *size = strrchr(name, '_');
  if (!size || size == name)
    return -1;
  size++;
  char *end;
  double w = strtod(size, &end);
  if (end == size || *end != 'x')
    return -1;
  const char *h_start = end + 1;
  double h = strtod(h_start, &end);
  if (end == h_start || w <= 0 || h <= 0)
    return -1;
  double scale;
  if (strcmp(end, "in") == 0)
    {
      scale = POINTS_PER_INCH;
      *metric = 0;
    }
  else if (strcmp(end, "mm") == 0)
    {
      scale = POINTS_PER_INCH / MM_PER_INCH;
      *metric = 1;
    }
  else
    return -1;
  *width = w * scale;
  *height = h * scale;
  return 0;
}

/* A dimension in a self-describing name: up to two decimals, no trailing
   zeros. */
static void
format_dimension(char *out, size_t size, double value)
{
  snprintf(out, size, "%.2f", round(value * 100) / 100);
  char *dot = strchr(out, '.');
  if (dot)
    {
      char *last = out + strlen(out) - 1;
      while (last > dot && *last == '0')
        *last-- = '\0';
      if (last == dot)
        *last = '\0';
    }
}

void
pwg_media_name(const char *paper, double width, double height, int metric,
               char *out, size_t size)
{
  const char *best = NULL;
  double best_error = 0;
  int best_same_unit = 0;
  for (size_t i = 0; i < sizeof standard_names / sizeof standard_names[0]; i++)
    {
      double w, h;
      int m;
      if (pwg_media_size(standard_names[i], &w, &h, &m) != 0)
        continue;
      double error = fmax(fabs(w - width), fabs(h - height));
      if (error > TOLERANCE)
        continue;
      int same_unit = (m != 0) == (metric != 0);
      if (!best || same_unit > best_same_unit
          || (same_unit == best_same_unit && error < best_error))
        {
          best = standard_names[i];
          best_error = error;
          best_same_unit = same_unit;
        }
    }
  if (best)
    {
      snprintf(out, size, "%s", best);
      return;
    }

  /* No standard size: "om_" (other metric) or "oe_" (other English), the
     paper's name in lower case with '-' for anything else, and its size. */
  char name[64];
  size_t n = 0;
  for (const char *p = paper; *p && n < sizeof name - 1; p++)
    {
      if (isalnum((unsigned char)*p))
        name[n++] = (char)tolower((unsigned char)*p);
      else if (n > 0 && name[n - 1] != '-')
        name[n++] = '-';
    }
  while (n > 0 && name[n - 1] == '-')
    n--;
  name[n] = '\0';
  double scale = metric ? MM_PER_INCH / POINTS_PER_INCH : 1 / POINTS_PER_INCH;
  char w[32], h[32];
  format_dimension(w, sizeof w, width * scale);
  format_dimension(h, sizeof h, height * scale);
  snprintf(out, size, "%s_%s_%sx%s%s", metric ? "om" : "oe", n ? name : "paper", w, h,
           metric ? "mm" : "in");
}
