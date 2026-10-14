"""Build the runtime's differential check and run it: every Clean function against the ROM's
code on generated entry states (see docs/runtime.md and runtime/diffcheck.h).

    python tools/diffcheck.py               # every check
    python tools/diffcheck.py func_02039444 # some

Needs a C compiler that targets 32-bit x86: clang on Windows (CC, default
"C:/Program Files/LLVM/bin/clang.exe"), gcc with -m32 elsewhere.
"""

from __future__ import annotations

import json
import os
import pathlib
import re
import shlex
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

OUT = C.BUILD / "runtime"
RUNTIME = C.ROOT / "runtime"
TEST = re.compile(r"^const DiffTest (diff_test_\w+) = \{(.*?)^\};", re.M | re.S)
FIELD = re.compile(r"\.(address|module)\s*=\s*([^,]+),")


def compiler() -> list[str]:
    if os.environ.get("CC"):
        return shlex.split(os.environ["CC"])
    if os.name == "nt":
        return ["C:/Program Files/LLVM/bin/clang.exe", "--target=i386-pc-windows-msvc"]
    return ["gcc", "-m32"]


def generate() -> list[pathlib.Path]:
    """The module manifest and the table of checks."""
    OUT.mkdir(parents=True, exist_ok=True)
    mods = C.modules()
    (OUT / "modules.txt").write_text(
        "".join(f"{m} {info['base']:08x} {C.ROM_DIR / (m + '.bin')}\n" for m, info in mods.items()),
        newline="\n")
    syms = C.SymbolTable(mods)
    rows = []
    for path in sorted((C.ROOT / "tests" / "clean").rglob("*.c")):
        for m in TEST.finditer(path.read_text()):
            fields = dict(FIELD.findall(m.group(2)))
            address = int(fields["address"].split("|")[0].strip(), 16)
            module = fields["module"].strip().strip('"')
            fn = syms.function(module, address)
            if fn is None:
                raise SystemExit(f"{path}: no function at {address:#010x} in {module}")
            rows.append((m.group(1), fn.size))
    table = ['#include "diffcheck.h"', "",
             "typedef struct DiffTestEntry {", "    const DiffTest *test;", "    uint32_t size;",
             "} DiffTestEntry;", ""]
    table += [f"extern const DiffTest {name};" for name, _ in rows]
    table += ["", "const DiffTestEntry diff_tests[] = {"]
    table += [f"    {{&{name}, 0x{size:x}}}," for name, size in rows] or ["    {0, 0},"]
    table += ["};", f"const int diff_test_count = {len(rows)};", ""]
    tab = OUT / "diff_tests.c"
    tab.write_text("\n".join(table), newline="\n")
    sources = [RUNTIME / n for n in ("arm.c", "memory.c", "loader.c", "diffcheck.c")]
    sources += sorted((C.ROOT / "clean").rglob("*.c")) + sorted((C.ROOT / "tests" / "clean").rglob("*.c"))
    return sources + [tab]


def build(sources: list[pathlib.Path]) -> pathlib.Path:
    exe = OUT / ("diffcheck.exe" if os.name == "nt" else "diffcheck")
    flags = ["-std=c11", "-O2", "-Wall", "-Wextra", "-fwrapv", "-fno-strict-aliasing",
             f"-I{RUNTIME}", f"-I{C.INCLUDE}"]
    p = subprocess.run([*compiler(), *flags, *map(str, sources), "-o", str(exe)],
                       capture_output=True, text=True)
    if p.returncode != 0:
        raise SystemExit(p.stdout + p.stderr)
    return exe


def unit_tests() -> None:
    """The interpreter's own instruction tests (runtime/tests/arm_test.c)."""
    exe = OUT / ("arm_test.exe" if os.name == "nt" else "arm_test")
    srcs = [RUNTIME / "arm.c", RUNTIME / "memory.c", RUNTIME / "tests" / "arm_test.c"]
    p = subprocess.run([*compiler(), "-std=c11", "-O2", "-Wall", "-Wextra", f"-I{RUNTIME}", *map(str, srcs),
                        "-o", str(exe)], capture_output=True, text=True)
    if p.returncode != 0:
        raise SystemExit(p.stdout + p.stderr)
    p = subprocess.run([str(exe)], cwd=C.ROOT, capture_output=True, text=True)
    print(p.stdout.strip().splitlines()[-1] if p.stdout.strip() else p.stderr)
    if p.returncode != 0:
        raise SystemExit(p.stdout + p.stderr)


def main() -> None:
    OUT.mkdir(parents=True, exist_ok=True)
    unit_tests()
    exe = build(generate())
    p = subprocess.run([str(exe), str(OUT / "modules.txt"), *sys.argv[1:]])
    sys.exit(p.returncode)


if __name__ == "__main__":
    main()
