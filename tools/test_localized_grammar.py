"""Synthetic Spanish tag conversion and C rule tests; no ROM or game text required."""
from __future__ import annotations

import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

import localize_clean as L

ROOT = Path(__file__).resolve().parents[1]


class Conversion(unittest.TestCase):
    def test_preserves_both_gender_alternatives_and_termination(self):
        tag = bytes([26, 8, 11, 4, 0]) + b"o\0a"
        report = {}
        actual = L.convert_text(tag, report, spanish_grammar=True)
        self.assertEqual(actual, bytes([26, 0, 14, 11, 4, 0]) + b"o\0\0\0a\0\0\0")
        self.assertEqual(report, {"4": 1})

    def test_gender_and_article_metadata_stay_numeric(self):
        tag = bytes([26, 8, 11, 0, 0, 1, 2, 3])
        self.assertEqual(L.convert_text(tag, {}, spanish_grammar=True),
                         bytes([26, 0, 10, 11, 0, 0, 1, 2, 3, 0]))

    def test_preserves_capitalization_and_article_state_tags(self):
        for kind in (1, 2, 3):
            tag = bytes([26, 5, 11, kind, 0])
            self.assertEqual(L.convert_text(tag, {}, spanish_grammar=True), bytes([26, 0, 6, 11, kind, 0]))

    def test_default_remains_first_form(self):
        self.assertEqual(L.convert_text(bytes([26, 8, 11, 4, 0]) + b"o\0a", {}), b"o\0")

    def test_rejects_oversized_variant_tag(self):
        with self.assertRaisesRegex(ValueError, "exceeds"):
            L.convert_text(bytes([26, 205, 11, 4, 0]) + b"x" * 200, {}, spanish_grammar=True)

    def test_c_rules_on_synthetic_attributes_and_strings(self):
        # Native compiler is sufficient: these pointer-free rule tests do not need x86-32.
        compiler = shutil.which("cc") or shutil.which("gcc")
        if os.name == "nt":
            compiler = str(Path("C:/Program Files/LLVM/bin/clang.exe"))
        if not compiler:
            self.skipTest("no host C compiler")
        source = r'''
#include "localized_grammar.h"
#include <assert.h>
int main(int argc, char **argv) {
    const uint8_t forms[] = {'m',0,0,0,'f',0,0,0,'n',0,0,0};
    assert(localized_grammar_form(forms, sizeof(forms), 0) == forms);
    assert(localized_grammar_form(forms, sizeof(forms), 1) == forms+4);
    assert(localized_grammar_form(forms, sizeof(forms), 2) == forms+8);
    assert(localized_grammar_form(forms, sizeof(forms), -1) == NULL);
    assert(localized_grammar_form(forms, sizeof(forms), 3) == NULL);
    assert(localized_grammar_form(forms, 6, 1) == NULL);
    assert(localized_grammar_form(forms, 4, 1) == NULL);
    assert(localized_grammar_form(forms, 1, 0) == NULL);
    const uint8_t empty[] = {0,0,'f',0,0,0};
    assert(localized_grammar_form(empty, sizeof(empty), 0) == NULL);
    assert(localized_grammar_form(empty, sizeof(empty), 1) == empty+2);
    assert(localized_grammar_upper('a') == 'A');
    assert(localized_grammar_upper('Z') == 'Z');
    assert(localized_grammar_upper(0xf1) == 0xd1);
    assert(localized_grammar_upper(0xe9) == 0xc9);
    assert(localized_grammar_upper(0xfc) == 0xdc);
    assert(localized_grammar_upper(0xf7) == 0xf7);
    assert(localized_grammar_upper(0x9a) == 0x8a);
    assert(localized_grammar_upper(0xac00) == 0xac00);
    uint8_t attributes[10] = {0}; attributes[8]=2; attributes[9]=4;
    assert(localized_grammar_article_index(attributes,10,0) == 2);
    assert(localized_grammar_article_index(attributes,10,1) == 4);
    assert(localized_grammar_article_index(attributes,10,2) == -1);
    assert(localized_grammar_article_index(attributes,10,3) == -1);
    assert(localized_grammar_article_index(attributes,9,0) == -1);
    attributes[8] = 0xff;
    assert(localized_grammar_article_index(attributes,10,0) == -1);
    assert(localized_grammar_enabled() == (argc > 1));
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            directory = Path(tmp)
            c = directory / "grammar.c"
            exe = directory / ("grammar.exe" if os.name == "nt" else "grammar")
            c.write_text(source)
            target = ["--target=i386-pc-windows-msvc", "-D_CRT_SECURE_NO_WARNINGS"] if os.name == "nt" else []
            subprocess.run([compiler, *target, "-std=c11", "-I" + str(ROOT / "runtime"), str(c), "-o", str(exe)], check=True)
            env = dict(os.environ, ACWW_GRAMMAR="")
            subprocess.run([str(exe)], env=env, check=True)
            env["ACWW_GRAMMAR"] = "es"
            subprocess.run([str(exe), "enabled"], env=env, check=True)


if __name__ == "__main__":
    unittest.main()
