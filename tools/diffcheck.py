"""Build the runtime's differential check and run it: every Clean function against the ROM's
code on generated entry states (see docs/runtime.md and runtime/diffcheck.h).

    python tools/diffcheck.py               # every check
    python tools/diffcheck.py func_02039444 # some
    python tools/diffcheck.py --native      # Native against Reference (tools/native.py first)

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
CHECK = re.compile(r"^DIFF_CHECK\((\w+), \"(\w+)\", (0x[0-9a-fA-F]+)", re.M)
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
        for m in CHECK.finditer(path.read_text()):
            name, module, address = m.group(1), m.group(2), int(m.group(3), 16)
            fn = syms.function(module, address)
            if fn is None:
                raise SystemExit(f"{path}: no function at {address:#010x} in {module}")
            rows.append((f"diff_test_{name}", fn.size))
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


def game_names(objects: list[pathlib.Path]) -> pathlib.Path | None:
    """An object placing every name the Clean code uses from the game (`data_...`, a function
    it calls) at its DS address, the way tools/native.py does for Native code."""
    windows = os.name == "nt"
    tool = "C:/Program Files/LLVM/bin/llvm-nm.exe" if windows else "nm"
    prefix = "_" if windows else ""
    defined, undefined = set(), set()
    for obj in objects:
        for line in subprocess.run([tool, str(obj)], capture_output=True, text=True).stdout.splitlines():
            parts = line.split()
            if len(parts) == 2 and parts[0] == "U":
                undefined.add(parts[1])
            elif len(parts) == 3 and parts[1] in "TDBRC":
                defined.add(parts[2])
    syms = C.SymbolTable(C.modules())
    rows = []
    for host in sorted(undefined - defined):
        name = host[len(prefix):] if host.startswith(prefix) else host
        addrs = {s.address | (1 if s.kind == "function" and s.thumb else 0) for s in syms.by_name.get(name, [])}
        if len(addrs) == 1:
            rows.append(f"\t.globl {host}\n\t.set {host}, 0x{addrs.pop():08x}\n")
    if not rows:
        return None
    OUT.mkdir(parents=True, exist_ok=True)
    src = OUT / "clean_names.s"
    src.write_text("".join(rows), newline="\n")
    obj = OUT / "clean_names.o"
    target = (["C:/Program Files/LLVM/bin/clang.exe", "--target=i686-pc-windows-gnu"] if windows else ["gcc", "-m32"])
    p = subprocess.run([*target, "-c", str(src), "-o", str(obj)], capture_output=True, text=True)
    if p.returncode != 0:
        raise SystemExit(p.stdout + p.stderr)
    return obj


def build(sources: list[pathlib.Path]) -> pathlib.Path:
    exe = OUT / ("diffcheck.exe" if os.name == "nt" else "diffcheck")
    flags = ["-std=c11", "-O2", "-Wall", "-Wextra", "-fwrapv", "-fno-strict-aliasing",
             f"-I{RUNTIME}", f"-I{C.INCLUDE}"]
    if os.name != "nt":
        flags += ["-fno-pic", "-fno-pie"]
    clean = [s for s in sources if C.ROOT / "clean" in s.parents]
    objects = []
    for src in clean:
        obj = OUT / "clean" / src.relative_to(C.ROOT / "clean").with_suffix(".o")
        obj.parent.mkdir(parents=True, exist_ok=True)
        p = subprocess.run([*compiler(), *flags, "-c", str(src), "-o", str(obj)], capture_output=True, text=True)
        if p.returncode != 0:
            raise SystemExit(p.stdout + p.stderr)
        objects.append(obj)
    names = game_names(objects)
    rest = [s for s in sources if s not in clean]
    link = ["-Wl,/SAFESEH:NO"] if os.name == "nt" else ["-no-pie"]
    p = subprocess.run([*compiler(), *flags, *map(str, rest), *map(str, objects), *([str(names)] if names else []),
                        *link, "-o", str(exe)], capture_output=True, text=True)
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


# What each parameter of a Native function is, so the check can give it a value of its type
# (runtime/nativecheck.c): mwccarm's callers widen 8- and 16-bit arguments, and a random word
# where the game passes a pointer or a small number would test inputs the game never makes.
PARAM_WORD, PARAM_U8, PARAM_S8, PARAM_U16, PARAM_S16, PARAM_POINTER, PARAM_UNKNOWN = 0, 1, 2, 3, 4, 5, 7
COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
PARAM_WORDS = {"int", "long", "unsigned", "signed", "u32", "s32", "BOOL", "float", "f32", "fx32", "size_t"}


def param_kind(text: str) -> int:
    words = text.replace("*", " * ").replace("&", " & ").replace("[", " [ ").split()
    words = [w for w in words if w not in ("const", "volatile", "struct", "enum", "register")]
    if "*" in words or "&" in words or "[" in words or "(" in text:
        return PARAM_POINTER
    if len(words) > 1 and words[-1] not in PARAM_WORDS | {"char", "short", "u8", "s8", "u16", "s16"}:
        words = words[:-1]  # drop the parameter's name
    if words in (["u8"], ["unsigned", "char"]):
        return PARAM_U8
    if words in (["s8"], ["char"], ["signed", "char"]):
        return PARAM_S8
    if words in (["u16"], ["unsigned", "short"], ["unsigned", "short", "int"]):
        return PARAM_U16
    if words in (["s16"], ["short"], ["signed", "short"], ["short", "int"]):
        return PARAM_S16
    if words and all(w in PARAM_WORDS for w in words) and words.count("long") < 2:
        return PARAM_WORD
    return PARAM_UNKNOWN  # a structure by value, a 64-bit value, or a type this does not know


def param_table() -> pathlib.Path:
    """build/adm-kr/runtime/native_params.c: for every game function, its parameters' kinds,
    three bits each, `this` first for a member; bit 31 when they are not all known."""
    rows = []
    for path in C.all_sources():
        if C.SRC not in path.parents:
            continue
        src = C.parse_source(path)
        text = COMMENT.sub(" ", path.read_text(encoding="utf-8", errors="replace"))
        m = re.search(r"(?:^|[;}])\s*((?:[\w<>]+[\s\*&]+)+?)((?:\w+::)?)" + re.escape(src.name)
                      + r"\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*(?:const\s*)?\{", text, re.M)
        if not m:
            continue
        params = " ".join(m.group(3).split())
        parts, depth, cur = [], 0, ""
        for ch in params:
            depth += ch == "("
            depth -= ch == ")"
            if ch == "," and depth == 0:
                parts.append(cur)
                cur = ""
            else:
                cur += ch
        if cur.strip() and cur.strip() != "void":
            parts.append(cur)
        kinds = ([PARAM_POINTER] if m.group(2) and "static" not in m.group(1).split() else [])
        kinds += [param_kind(p) for p in parts]
        packed = 0
        for i, k in enumerate(kinds[:10]):
            packed |= k << (3 * i)
        if len(kinds) > 10 or PARAM_UNKNOWN in kinds:
            packed |= 1 << 31
        # Overlays that share an address range have functions at the same address: the module
        # tells them apart.
        rows.append(((src.address, src.module),
                     f"    {{0x{src.address:08x}u, \"{src.module}\", {len(kinds)}u, 0x{packed:08x}u}},"))
    rows = [row for _, row in sorted(rows)]  # sorted by address: the check searches it
    known = []
    for line in (C.ROOT / "tests" / "native" / "known.txt").read_text().splitlines():
        if line.strip() and not line.startswith("#"):
            address, reason = line.split(None, 1)
            if not reason.strip():
                raise SystemExit(f"tests/native/known.txt: {address} has no reason")
            known.append(int(address, 16) & ~1)
    rows.append("")
    out = OUT / "native_params.c"
    out.write_text("\n".join(["#include \"native_params.h\"", "", "const NativeParams native_param_kinds[] = {",
                              *rows, "};", f"const uint32_t native_param_kinds_count = {len(rows) - 1};",
                              "const uint32_t native_known[] = {"
                              + ", ".join(f"0x{a:08x}u" for a in sorted(known) or [0]) + "};",
                              f"const uint32_t native_known_count = {len(known)};", ""]),
                   newline="\n")
    return out


# Names Native objects use that runtime/native_rt.c defines (C names, without the COFF "_").
RUNTIME_NAMES = {"__cxa_guard_acquire", "__cxa_guard_release", "__cxa_guard_abort"}


def build_native() -> pathlib.Path:
    """runtime/nativecheck.c with every Native object (tools/native.py must have run)."""
    native = C.BUILD / "native" / ("windows" if os.name == "nt" else "linux")
    if not (native / "natives.s").exists():
        raise SystemExit("run `python tools/native.py` first")
    exe = OUT / ("nativecheck.exe" if os.name == "nt" else "nativecheck")
    asm = []
    # absolute.s places every name the symbol table does not know at 0; the ones
    # runtime/native_rt.c defines must come from there instead.
    prefix = "_" if os.name == "nt" else ""
    provided = {prefix + n for n in RUNTIME_NAMES}
    absolute = OUT / "absolute.s"
    absolute.write_text("".join(line for line in (native / "absolute.s").read_text().splitlines(keepends=True)
                                if line.split()[1].rstrip(",") not in provided), newline="\n")
    assembly = [native / "natives.s", absolute]
    if os.name == "nt":
        assembly.append(RUNTIME / "native_rt_win.s")
    for src in assembly:
        name = src.name
        obj = OUT / name.replace(".s", ".o")
        target = (["C:/Program Files/LLVM/bin/clang.exe", "--target=i686-pc-windows-gnu"]
                  if os.name == "nt" else ["gcc", "-m32"])
        p = subprocess.run([*target, "-c", str(src), "-o", str(obj)], capture_output=True, text=True)
        if p.returncode != 0:
            raise SystemExit(p.stdout + p.stderr)
        asm.append(obj)
    srcs = [RUNTIME / n for n in ("arm.c", "memory.c", "loader.c", "host.c", "native_rt.c", "nativecheck.c")]
    srcs.append(param_table())
    flags = ["-std=c11", "-O2", "-Wall", "-Wextra", f"-I{RUNTIME}"]
    # Classes split one function per file define their destructors and vtable in several
    # objects, identically; the linker keeps the first.
    link = (["-Wl,/SAFESEH:NO", "-Wl,/FORCE:MULTIPLE", "-Wl,/DYNAMICBASE:NO", "-Wl,/FIXED"] if os.name == "nt"
            else ["-no-pie", "-Wl,--allow-multiple-definition", "-Wl,-Ttext-segment=0x400000"])
    p = subprocess.run([*compiler(), *flags, *map(str, srcs), *map(str, asm), f"@{native / 'objects.txt'}",
                        *link, "-o", str(exe)], capture_output=True, text=True)
    if p.returncode != 0:
        raise SystemExit((p.stdout + p.stderr)[-4000:])
    return exe


def main() -> None:
    OUT.mkdir(parents=True, exist_ok=True)
    if sys.argv[1:2] == ["--native"]:
        generate()
        exe = build_native()
        log = C.BUILD / "native" / ("windows" if os.name == "nt" else "linux") / "differences.txt"
        p = subprocess.run([str(exe), str(OUT / "modules.txt"), str(log), *sys.argv[2:]], cwd=C.ROOT)
        sys.exit(p.returncode)
    unit_tests()
    exe = build(generate())
    p = subprocess.run([str(exe), str(OUT / "modules.txt"), *sys.argv[1:]])
    if p.returncode == 0 and not sys.argv[1:]:
        write_clean_list()
    sys.exit(p.returncode)


def write_clean_list() -> None:
    """build/adm-kr/clean.json: every function whose Clean version passed, for
    tools/progress_map.py."""
    rows = []
    for path in sorted((C.ROOT / "tests" / "clean").rglob("*.c")):
        text = path.read_text()
        for m in TEST.finditer(text):
            fields = dict(FIELD.findall(m.group(2)))
            rows.append((fields["module"].strip().strip('"'), int(fields["address"].split("|")[0].strip(), 16)))
        for m in CHECK.finditer(text):
            rows.append((m.group(2), int(m.group(3), 16)))
    out = [{"module": module, "address": f"{address & ~1:08x}"} for module, address in sorted(set(rows))]
    (C.BUILD / "clean.json").write_text(json.dumps(out, indent=1) + "\n", newline="\n")


if __name__ == "__main__":
    main()
