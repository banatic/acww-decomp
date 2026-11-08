"""Synthetic fixed-record names and the actual host C buffer/metadata helpers."""
from __future__ import annotations

import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

import localize_clean as L

ROOT = Path(__file__).resolve().parents[1]


class Names(unittest.TestCase):
    def test_keeps_every_original_byte_and_long_name(self):
        original = bytes(range(24)) * 2
        donor = b"\x03\x01\x01long western name" + b"\x02\x00\x00short\0".ljust(20, b"\0")
        converted = L.extend_name_records(original, donor, 24, 20, 3, 0)
        self.assertEqual(len(converted), 2 * 88)
        self.assertEqual(converted[:24], original[:24])
        self.assertEqual(converted[88:112], original[24:])
        self.assertEqual(converted[24:32], b"LTXT\x03\x01\x01\0")
        self.assertEqual(converted[32:68], "long western name\0".encode("utf-16le"))

    def test_accents_and_furniture_gameplay_prefix(self):
        original = bytes(range(32))
        donor = bytes(9) + b"\x03\x01\x01" + b"caf\xe9".ljust(20, b"\0")
        result = L.extend_name_records(original, donor, 32, 32, 12, 9)
        self.assertEqual(result[:32], original)
        self.assertEqual(result[40:50], b"c\0a\0f\0\xe9\0\0\0")

    def test_series_have_no_invented_grammar_attributes(self):
        result = L.extend_name_records(bytes(24), b"\x07series".ljust(20, b"\0"), 24, 20, 1, None)
        self.assertEqual(result[28:31], b"\xff" * 3)

    def test_rejects_partial_different_count_and_control_records(self):
        for original, donor in ((bytes(23), bytes(20)), (bytes(48), bytes(20)),
                                 (bytes(24), b"\0\0\0bad\x1a".ljust(20, b"\0"))):
            with self.assertRaises(ValueError):
                L.extend_name_records(original, donor, 24, 20, 3, 0)

    def test_c_helpers_default_and_enabled(self):
        compiler = shutil.which("cc") or shutil.which("gcc")
        if os.name == "nt":
            compiler = "C:/Program Files/LLVM/bin/clang.exe"
        if not compiler:
            self.skipTest("no host C compiler")
        source = r'''
#include "localized_names.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>
int main(int argc, char **argv) {
    uint8_t record[24+64] = {0};
    memcpy(record+24, "LTXT", 4);
    record[28]=3; record[29]=1; record[30]=1;
    record[32]=0xe1; record[34]=0xf1;
    int owner1=0, owner2=0;
    uint8_t inline_text[22]; memset(inline_text, 0xa5, sizeof(inline_text));
    if (argc == 1) {
        assert(!localized_names_enabled());
        assert(localized_name_stride(24)==24);
        assert(localized_name_text(record,24)==0);
        assert(localized_name_attribute(record,24,0)==-1);
        assert(localized_name_buffer(&owner1,inline_text)==inline_text);
    } else {
        assert(localized_names_enabled());
        assert(localized_name_stride(24)==88);
        assert(localized_name_text(record,24)==(const char *)record+32);
        assert(localized_name_attribute(record,24,0)==3);
        assert(localized_name_attribute(record,24,1)==1);
        assert(localized_name_attribute(record,24,2)==1);
        assert(localized_name_attribute(record,24,3)==-1);
        record[30]=255; assert(localized_name_attribute(record,24,2)==-1);
        record[24]=0; assert(localized_name_text(record,24)==0); record[24]='L';
        memset(record+32,1,56); assert(localized_name_text(record,24)==0);
        uint8_t *a=localized_name_buffer(&owner1,inline_text);
        uint8_t *b=localized_name_buffer(&owner2,inline_text);
        assert(a!=b && a!=inline_text && b!=inline_text);
        memset(a,0x3a,LOCALIZED_NAME_CAPACITY);
        assert(localized_name_buffer(&owner1,inline_text)==a);
        assert(b[0]==0);
        localized_name_release(&owner1);
        uint8_t *again=localized_name_buffer(&owner1,inline_text);
        assert(again[0]==0);
        for (unsigned i=0;i<sizeof(inline_text);i++) assert(inline_text[i]==0xa5);
    }
    localized_name_release(&owner1); localized_name_release(&owner2);
    localized_name_release(&owner1);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as folder:
            c = Path(folder) / "test.c"
            exe = Path(folder) / ("test.exe" if os.name == "nt" else "test")
            c.write_text(source)
            target = ["--target=i386-pc-windows-msvc", "-D_CRT_SECURE_NO_WARNINGS"] if os.name == "nt" else []
            subprocess.run([compiler, *target, "-std=c11", "-I"+str(ROOT/"runtime"), str(c),
                            str(ROOT/"runtime/localized_names.c"), "-o", str(exe)], check=True)
            env = dict(os.environ, ACWW_NAMES="")
            subprocess.run([str(exe)], env=env, check=True)
            env["ACWW_NAMES"]="1"
            subprocess.run([str(exe), "enabled"], env=env, check=True)


if __name__ == "__main__":
    unittest.main()
