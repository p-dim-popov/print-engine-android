# print-engine-android: tests of the licence guard.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
import os
import subprocess
import tempfile
import unittest

GUARD = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "scripts",
                     "check-licence-notices.sh")


class LicenceGuard(unittest.TestCase):
    def check(self, files):
        with tempfile.TemporaryDirectory() as repo:
            subprocess.run(["git", "init", "-q", repo], check=True)
            for name, text in files.items():
                path = os.path.join(repo, name)
                os.makedirs(os.path.dirname(path), exist_ok=True)
                with open(path, "w", encoding="utf-8") as f:
                    f.write(text)
            return subprocess.run([GUARD, repo], capture_output=True, check=False)

    def test_files_with_notices_pass(self):
        result = self.check({"src/a.c": "/* GNU General Public License */\n",
                             "scripts/b.sh": "# GPL-2.0-or-later\n",
                             "third_party/x/c.c": "upstream's own notice\n"})
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_a_new_file_without_a_notice_fails(self):
        result = self.check({"src/a.c": "int main(void) { return 0; }\n"})
        self.assertEqual(result.returncode, 1)
        self.assertIn(b"src/a.c", result.stderr)


if __name__ == "__main__":
    unittest.main()
