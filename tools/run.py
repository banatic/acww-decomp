"""Build runtime/run.c and boot the game's ARM9 code in the interpreter (docs/runtime.md, M3),
or with the matching sources compiled for the PC in place of the ROM's code (M4).

    python tools/run.py                      # run until stuck or 200 M instructions
    python tools/run.py 50000000             # an instruction budget
    python tools/run.py 0 600                # no instruction budget, stop after 600 frames
    python tools/run.py 0 1300 --input runtime/recordings/title-start.txt --rtc "2005-11-23 12:00:00"
                        --png build/frames --frames 0-1300/50 --hash build/frames/hashes.txt
                                             # (one command) the recorded title run, saved and hashed
    python tools/run.py 0 1300 --input runtime/recordings/title-start.txt --rtc "2005-11-23 12:00:00"
                        --native=all --hash build/native/hashes.txt --ram-hash 300,700,1299
                                             # (one command) the same with every Native function, checked
                                             # against the Reference run (M4)

Options for the screens (docs/runtime.md, M3):
    --png DIR        save frames as DIR/frame-<n>.png (upper screen above the lower one)
    --png3d DIR      save the 3D engine's output alone as DIR/3d-<n>.png (transparent pixels
                     as a grey checkerboard), for the frames --frames lists
    --frames LIST    which frames to save: n, a-b or a-b/step, comma-separated (default all)
    --hash FILE|-    write "frame <n> <sha1 upper> <sha1 lower>" for every frame; the report
                     ends with one SHA-1 over the whole sequence, so two runs compare at a glance
    --input FILE     an input recording (format in runtime/input.h)
    --rtc "YYYY-MM-DD HH:MM:SS"  start the clock at a fixed moment and advance it with the
                     emulated time, so runs are identical (default: the host's clock)
    --save FILE      start with this image in the save chip (a 256 KB flash image, as emulators
                     write .sav files); the file is only read (default: an erased chip)

Native functions (docs/runtime.md, M4; the design is in runtime/native_run.h):
    --native=all|leaf|none|FILE
                     which functions with a Native (tools/native.py, run first) run as Native:
                     all of them, the leaves (functions whose ROM code calls nothing), none, or
                     the names / addresses listed in FILE (one per line). Functions listed in
                     runtime/native-reference.txt stay Reference in every case. The run is made
                     twice: a Reference run that records where the Native run will cross between
                     Native and interpreted code (and the step count there, which gives Native code
                     the Reference's timing), then the Native run, which follows the record and
                     reports the first crossing that differs. Both frame sequences are compared;
                     the exit status is 1 when they differ.
    --ram-hash LIST  a SHA-1 of main RAM, ITCM and DTCM (stacks and the static data of functions
                     that run Native left out) after each listed frame (comma-separated), at the
                     first moment no Native function is half done; compared between the two runs
    --ram-dump DIR   also write those memory images to DIR, to compare by hand
    --no-timing      the Native run without the record: Native code takes no time
    --learn          when a Native function touches hardware (it faults) or loops waiting for an
                     interrupt (the watchdog), add it to runtime/native-reference.txt and run
                     again, until none does
    --expect FILE    the frame sequence SHA-1 (as in runtime/recordings/*.sha1) both runs must give
    --clean[=FILE]   run each Clean function (clean/, registered by its check in tests/clean/) in
                     place of its Native one, in both runs: the Native run then checks the Clean
                     code too (docs/runtime.md, M5). With FILE, only the functions it lists (names
                     or addresses, one per line)
    --clean-ran FILE with --clean: also list which Clean functions ran in the Native run, however
                     they were entered (from the interpreter, from Native or from Clean code), as
                     JSON to FILE: [{"module", "address", "ran"}]. The program is the usual one
                     with runtime/clean_ran.c linked in, which marks each Clean function's entry
                     with a breakpoint until it first runs; the Clean code is the usual build's

Prints how far the boot gets: where it stopped, the registers the game touched, the BIOS
calls, the PXI traffic, the functions branched to most and the last branch targets with their
symbols. The ROM is extract/adm-kr.nds; the modules of build/adm-kr/rom are only compared
against memory after the crt0 has unpacked the program. Same compiler as tools/diffcheck.py.

Environment variables, for following a run on stderr:
    RUN_TRACE=card,pxi,irq print cartridge commands, PXI words, interrupt requests and DMAs
    RUN_TRACE=gx           print a line per rendered 3D frame (polygons, vertices, pixels drawn)
    RUN_CALLS=f1,f2,...    print each call of the named functions with r0-r3 and the frame
    RUN_BRANCHES=N         how many of the last branch targets the report lists (300)
"""

from __future__ import annotations

import argparse
import concurrent.futures as cf
import functools
import hashlib
import json
import os
import pathlib
import re
import shutil
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402
import diffcheck  # noqa: E402
import native as native_build  # noqa: E402
import native_abi  # noqa: E402
import native_clean_profile  # noqa: E402
import native_stack  # noqa: E402
import native_aggregate  # noqa: E402
import native_publish  # noqa: E402
import native_contract  # noqa: E402
import objrewrite  # noqa: E402

WINDOWS = os.name == "nt"
# Per host: a Linux run (in a container) and a Windows one can share the build tree.
OUT = (pathlib.Path(os.environ["ACWW_RUNTIME_OUT"]) if os.environ.get("ACWW_RUNTIME_OUT")
       else C.BUILD / ("runtime" if WINDOWS else "runtime-linux"))
RUNTIME = C.ROOT / "runtime"
ROM = C.ROOT / "extract" / "adm-kr.nds"
NATIVE = C.BUILD / "native" / ("windows" if WINDOWS else "linux")
KEPT = RUNTIME / "native-reference.txt"
HELPERS = RUNTIME / "compiler-helpers.txt"
LIBRARY_ARGUMENTS = RUNTIME / "library-arguments.txt"
# CLEAN_AS(symbol, function), or CLEAN_AS_SYMBOL("symbol", function) for a symbol that is not a C
# name (clean/clean.h): the symbol is the first group that matched
CLEAN_AS = re.compile(r"^CLEAN_AS(?:\((\w+)|_SYMBOL\(\"([^\"]+)\"),\s*(\w+)\)", re.M)
# DIFF_CHECK(symbol, "module", address, bits, ... (runtime/diffcheck.h)
CLEAN_CHECK = re.compile(r"^DIFF_CHECK\((\w+), \"(\w+)\", (0x[0-9a-fA-F]+(?: \| 1)?), (\d+),", re.M)
SOURCES = ("arm.c", "memory.c", "io.c", "bios.c", "arm7.c", "boot.c", "gpu2d.c", "gpu3d.c", "frame.c", "input.c",
           "run.c", "native_run.c", "native_aggregate.c", "native_os.c", "host.c", "native_tramp.S", "render.c", "drive.c")

# The ROM's compiler helpers that Native code does inline (runtime/native_run.c, status H):
# the libs/Runtime package, and the C library functions the PC's own versions replace
# (tools/native.py, HOST_NAMES). Where a source calls one by name (__register_global_object),
# the Native run interprets that call without counting it as a crossing.
HOST_NAMES = {"memcmp", "memcpy", "memmove", "memset", "strcat", "strchr", "strcmp", "strcpy", "strlen",
              "strncmp", "strncpy"}
RET_SKIP = 7


def generate() -> tuple[pathlib.Path, pathlib.Path]:
    """The module manifest (as diffcheck writes it) and a flat symbol list for run.c."""
    OUT.mkdir(parents=True, exist_ok=True)
    mods = C.modules()
    manifest = OUT / "modules.txt"
    manifest.write_text(
        "".join(f"{m} {info['base']:08x} {C.ROM_DIR / (m + '.bin')}\n" for m, info in mods.items()),
        newline="\n")
    syms = C.symbol_table(mods)
    rows = []
    for mod in C.RESIDENT:
        for s in syms.by_module.get(mod, []):
            if s.kind == "function" and s.size:
                rows.append(f"{s.address:08x} {s.size:x} {s.name}\n")
    # overlays live at overlapping addresses; only the resident modules are named
    table = OUT / "symbols.txt"
    table.write_text("".join(sorted(rows)), newline="\n")
    return manifest, table


def compile_asm(src: pathlib.Path, obj: pathlib.Path) -> pathlib.Path:
    target = (["C:/Program Files/LLVM/bin/clang.exe", "--target=i686-pc-windows-gnu"] if WINDOWS
              else ["gcc", "-m32"])
    cmd = [*target, "-c", str(src), "-o", str(obj)]
    key = hashlib.sha1(" ".join(cmd).encode() + src.read_bytes()).hexdigest()
    if built_before(obj, key):
        return obj
    p = subprocess.run(cmd, capture_output=True, text=True)
    if p.returncode != 0:
        raise SystemExit(p.stdout + p.stderr)
    obj.with_name(obj.name + ".key").write_text(key)
    return obj


def built_before(out: pathlib.Path, key: str) -> bool:
    """Whether `out` was last built from exactly what `key` names (its .key stamp says so)."""
    stamp = out.with_name(out.name + ".key")
    try:
        return out.exists() and stamp.read_text() == key
    except OSError:
        return False


def link_key(cmd: list[str]) -> str:
    """What a link of `cmd` is made of: the command, the runtime's sources and headers, the
    Native objects by the one key tools/native.py writes for them (objects.txt.key: reading
    25,000 objects would cost more than the link), and every other object and source it names,
    directly or through a response file, by its content."""
    h = hashlib.sha1(" ".join(cmd).encode())
    native_list = (NATIVE / "objects.txt").resolve()
    native_key = NATIVE / "objects.txt.key"
    h.update(native_key.read_bytes() if native_key.exists() else os.urandom(16))  # none: always link
    for path in sorted(RUNTIME.glob("*.[chS]")):
        h.update(path.name.encode() + path.read_bytes())
    for arg in cmd:
        listed = pathlib.Path(arg[1:]) if arg.startswith("@") else None
        if listed is not None and listed.resolve() == native_list:
            continue
        names = listed.read_text().split() if listed is not None else [arg]
        h.update("\n".join(names).encode())
        for name in names:
            path = pathlib.Path(name)
            if path.suffix in (".c", ".o", ".obj") and path.is_file():
                h.update(path.read_bytes())
    return h.hexdigest()


def address_of(text: str) -> int:
    """A check's address: `0x... | 1` for Thumb."""
    value = 0
    for part in text.split("|"):
        value |= int(part.strip(), 0)
    return value


def clean_checks(only: str | None = None) -> list[tuple[str, str, int, int]]:
    """Every Clean function's check in tests/clean/: (DiffTest symbol, module, DS address with
    the Thumb bit, result width in bits); with `only` ("all" or a file of names or addresses),
    those it lists."""
    out = []
    for path in sorted((C.ROOT / "tests" / "clean").rglob("*.c")):
        text = path.read_text(encoding="utf-8")
        for m in diffcheck.TEST.finditer(text):
            fields = dict(diffcheck.FIELD.findall(m.group(2)))
            bits = re.search(r"\.return_bits\s*=\s*(\d+)", m.group(2))
            address = address_of(fields["address"])
            out.append((m.group(1), fields["module"].strip().strip('"'), address, int(bits.group(1)) if bits else 32))
        for m in CLEAN_CHECK.finditer(text):
            out.append((f"diff_test_{m.group(1)}", m.group(2), address_of(m.group(3)), int(m.group(4))))
    if only and only != "all":
        wanted = {w.split()[0] for w in pathlib.Path(only).read_text().splitlines() if w.strip()}
        out = [c for c in out if c[0][len("diff_test_"):] in wanted or f"{c[2] & ~1:08x}" in wanted]
    return out


def clean_registrations(only: str | None = None) -> list[tuple[str, str, str, int, int]]:
    """Every Clean function registered with CLEAN_AS (clean/clean.h): (symbol, function, module,
    DS address with the Thumb bit, size); with `only` ("all" or a file listing game symbols,
    Clean function names or addresses), those it lists."""
    syms = C.symbol_table(C.modules())
    out = []
    for path in sorted((C.ROOT / "clean").rglob("*.c")):
        for plain, quoted, function in CLEAN_AS.findall(path.read_text(encoding="utf-8")):
            symbol = plain or quoted
            found = [s for s in syms.by_name.get(symbol, []) if s.kind == "function" and s.size]
            if len(found) != 1:
                raise SystemExit(f"{path.relative_to(C.ROOT)}: CLEAN_AS({symbol}, ...) names no single function")
            s = found[0]
            out.append((symbol, function, s.module, s.address | (1 if s.thumb else 0), s.size))
    if only and only != "all":
        wanted = {w.split()[0] for w in pathlib.Path(only).read_text().splitlines() if w.strip()}
        out = [r for r in out if r[0] in wanted or r[1] in wanted or f"{r[3] & ~1:08x}" in wanted]
    return out


def write_clean_table(clean: str | None) -> pathlib.Path:
    """runtime/native_table.h's clean_functions: for each Clean function, a function the Native
    run calls like a Native one (the argument registers, then the stack words) that calls the
    check's run_clean with r0-r3 and the stack words in diff_stack. Empty without `clean`."""
    names = {m: int(i) for i, m in
             re.findall(r"native_module_name_(\d+):\s*\.asciz \"(\w+)\"", (NATIVE / "natives.s").read_text())}
    syms = C.symbol_table(C.modules())
    prefix = "_" if WINDOWS else ""
    text = (NATIVE / "natives.s").read_text()
    count_match = re.search(r"\bnative_function_count:\s*\.long (\d+)", text.replace("_native_function_count:", "native_function_count:"))
    assert count_match is not None
    native_count = int(count_match[1])
    profiles = []
    lines = ['#include "diffcheck.h"', '#include "native_table.h"', "", "const uint32_t *diff_stack;", ""]
    rows = []
    for i, (test, module, address, bits) in enumerate(clean_checks(clean) if clean else []):
        fn = syms.function(module, address & ~1)
        if fn is None or module not in names:
            raise SystemExit(f"{test}: no function at {address:#010x} in {module}")
        ret = {0: "NATIVE_RET_VOID", 8: "NATIVE_RET_U8", 16: "NATIVE_RET_U16"}.get(bits, "NATIVE_RET_32")
        lines += [f"extern const DiffTest {test};",
                  f"uint32_t native_body_clean_{i}({', '.join(f'uint32_t a{k}' for k in range(16))})",
                  "{",
                  "    const uint32_t args[4] = {a0, a1, a2, a3};",
                  f"    const uint32_t stack[12] = {{{', '.join(f'a{k}' for k in range(4, 16))}}};",
                  "    diff_stack = stack;",
                  f"    return {test}.run_clean(args);",
                  "}", f"extern void native_clean_{i}(void);", ""]
        profiles.append(native_clean_profile.Entry(f"clean_{i}", native_count + len(rows), alias=False))
        rows.append(f"    {{0x{address:08x}u, 0x{fn.size:x}u, (const void *) native_clean_{i}, "
                    f"(uint32_t) {ret} | 4u << 4 | (uint32_t) {names[module]} << 16}},")
    # Functions registered with CLEAN_AS have their matching source's signature: the table calls
    # them as it calls the Native version, with its result kind and parameter count (a source
    # that is assembly only has no Native version: a word result and four parameters). All of
    # them are listed, since Clean code calls Clean code directly; the ones `clean` does not
    # select are on standby (bit 11), and the runtime sends a call to one on to its function's
    # Native version or to the ROM's code, as the policy says.
    table = natives_table()
    selected = {r[0] for r in clean_registrations(clean)} if clean else set()
    for symbol, function, module, address, size in clean_registrations("all") if clean else []:
        if module not in names:
            continue
        native = table.get((address, module))
        info = native[1] if native else (5 | 4 << 4 | names[module] << 16)  # NATIVE_RET_32, 4 parameters
        if symbol == 'func_020404b4':
            if function != 'EventCalendar_ScheduleKey':
                raise ValueError('Schedule-key Clean ABI needs an audit')
            # The PC copy asserts this prototype against the real Clean header.
            # Native's union and Clean's scalar need bridges in both directions.
            info = (info & ~15) | 5
        if symbol not in selected:
            info |= 1 << 11
        lines += [f"extern void {function}(void);"]
        profiles.append(native_clean_profile.Entry(function, native_count + len(rows), native_build.WIDEN.get(info & 15)))
        rows.append(f"    {{0x{address:08x}u, 0x{size:x}u, (const void *) {function}, 0x{info:08x}u}},")
    lines += ["const NativeFunction clean_functions[] = {", *(rows or ["    {0, 0, 0, 0},"]), "};",
              f"const uint32_t clean_function_count = {len(rows)};", ""]
    if clean:
        assembly = native_clean_profile.assembly(profiles, prefix)
        if not WINDOWS:
            assembly += ['\t.section .note.GNU-stack,"",@progbits']
        (OUT / "clean-profile.s").write_text("\n".join(assembly) + "\n", newline="\n")
    else:
        lines += ["const NativeBody clean_bodies[1];", "const uint32_t clean_body_count = 0;", ""]
    path = OUT / "clean_table.c"
    path.write_text("\n".join(lines), newline="\n")
    return path


def clean_headers(path: pathlib.Path) -> list[pathlib.Path]:
    """Every header a Clean source pulls in through #include "...", transitively (its own
    directory, clean/, include/ and include/msl/ are searched, as the compile does)."""
    seen: dict[str, None] = {}
    todo = [os.path.normpath(path)]
    while todo:
        for cand in direct_includes(todo.pop()):
            if cand not in seen:
                seen[cand] = None
                todo.append(cand)
    return [pathlib.Path(p) for p in sorted(seen)]


@functools.cache
def direct_includes(path: str) -> tuple[str, ...]:
    """The headers one file names in #include "..." (see clean_headers), found once per run."""
    out = []
    with open(path, "rb") as f:
        names = C.INCLUDE_LINE.findall(f.read())
    for name in names:
        for base in (os.path.dirname(path), str(C.ROOT / "clean"), str(C.INCLUDE), str(C.INCLUDE / "msl")):
            cand = os.path.normpath(os.path.join(base, name.decode()))
            if cand in header_files():
                out.append(cand)
                break
    return tuple(out)


@functools.cache
def header_files() -> frozenset[str]:
    """Every file under clean/ and include/, listed once (testing each candidate path on
    Windows costs more than the listing)."""
    return frozenset(os.path.normpath(os.path.join(d, f)) for top in (C.ROOT / "clean", C.INCLUDE)
                     for d, _, files in os.walk(top) for f in files)


def build_clean(flags: list[str]) -> list[str]:
    """The Clean code and its checks as objects, and the names they take from the game placed at
    their DS addresses (as tools/diffcheck.py builds them). Each object is rewritten as the Native
    objects are (tools/objrewrite.py): a call to a game function that has a Native version goes
    to it, as a Native caller's does, so it runs where the run's policy says (Native, Clean, or
    the ROM's code through the patched entry) with the same crossings as the Reference records."""
    syms = C.symbol_table(C.modules())
    known = set(syms.by_name)
    native = {name for name, _ in natives_table().values()}
    prefix = "_" if WINDOWS else ""
    # Each Clean function stays a function of its own, as each Native one is (one per source):
    # the runtime redirects a function at its entry, which a call inlined into its caller, or
    # two identical functions folded into one, would get round.
    flags = [*flags, "-fno-inline", "-ffunction-sections"] + ([] if "clang" in " ".join(diffcheck.compiler()) else ["-fno-ipa-icf"])
    # uninitialized locals filled as the Native objects' are (tools/native.py), so the memory
    # comparison tells the bytes a structure filled in part passes on from the game's values
    flags += ["-ftrivial-auto-var-init=pattern"]
    # indirect calls through natives.s's thunks, as Native code's (tools/native.py, flags_for)
    flags += native_build.indirect_flags(diffcheck.compiler())
    tree = OUT / "clean"
    profiles = {r[1] for r in clean_registrations("all")}
    # A direct call to a function without a Native goes through its native_call_ stub, as
    # Native code's does (tools/native.py, call_targets): the ones natives.s does not have
    # are in clean-calls.s. The PC's own C library functions (memcpy, ...) stay the PC's.
    calls = native_build.call_targets(syms, known - native - native_build.HOST_NAMES)
    # what the rewrite of every object depends on besides the object
    rewritten = hashlib.sha1("\n".join([*sorted(known), "", *sorted(native), "", prefix, *sorted(profiles), "",
                                        *sorted(calls)]).encode())
    for tool in ("objrewrite.py", "native_clean_profile.py"):
        rewritten.update((C.ROOT / "tools" / tool).read_bytes())
    compiler = [*diffcheck.compiler(), *flags, f"-I{C.INCLUDE}", f"-I{C.ROOT / 'clean'}"]

    def one(src: pathlib.Path) -> tuple[pathlib.Path, str | None]:
        obj = tree / src.relative_to(C.ROOT).with_suffix(".o")
        obj.parent.mkdir(parents=True, exist_ok=True)
        source = src
        original = src.read_bytes().decode()
        copy = original
        if src.relative_to(C.ROOT).as_posix() == native_publish.CLEAN_SOURCE:
            copy = native_publish.translate(native_publish.CLEAN_SOURCE, copy)
        elif src.relative_to(C.ROOT).as_posix() == native_aggregate.CLEAN_SOURCE:
            copy = native_aggregate.clean_copy(copy)
        elif src.relative_to(C.ROOT).as_posix() == native_stack.CLEAN_SOURCE:
            copy = native_stack.clean_copy(copy)
        copy = native_aggregate.clean_caller_copy(src.relative_to(C.ROOT).as_posix(), copy)
        copy = native_clean_profile.source_copy(copy)
        if copy != original:
            source = OUT / 'clean-copy' / src.relative_to(C.ROOT)
            source.parent.mkdir(parents=True, exist_ok=True)
            source.write_text(f'#line 1 "{src.as_posix()}"\n' + copy, newline='\n')
        cmd = [*compiler, '-iquote', str(src.parent), "-c", str(source), "-o", str(obj)]
        # the object as linked, kept by everything it is made from (here and in the cache every
        # checkout shares): an unchanged file is not compiled again
        key = hashlib.sha1(C.tree_free(" ".join(cmd) + "\0" + copy).encode() + rewritten.digest())
        for header in clean_headers(src):
            key.update(header.read_bytes())
        key = key.hexdigest()
        stamp = obj.with_suffix(".key")
        if obj.exists() and stamp.exists() and stamp.read_text() == key:
            return obj, None
        if C.cache_get("clean", key, obj):
            stamp.write_text(key)
            return obj, None
        stamp.unlink(missing_ok=True)
        p = subprocess.run(cmd, capture_output=True, text=True)
        if p.returncode != 0:
            raise SystemExit(p.stdout + p.stderr)
        return obj, key
    sources = sorted((C.ROOT / "clean").rglob("*.c")) + sorted((C.ROOT / "tests" / "clean").rglob("*.c"))
    with cf.ThreadPoolExecutor(max(1, (os.cpu_count() or 4) - 2)) as pool:
        built = list(pool.map(one, sources))
    # the compiles run side by side; the rewrite (module state in tools/objrewrite.py) one by one
    saved_calls = objrewrite.CALLS
    try:
        objrewrite.CALLS = calls
        for obj, key in built:
            if key:
                data, _ = native_clean_profile.rewrite(obj.read_bytes(), known, native, prefix, profiles)
                obj.write_bytes(data)
                obj.with_suffix(".key").write_text(key)
                C.cache_put("clean", key, obj)
    finally:
        objrewrite.CALLS = saved_calls
    objects = [obj for obj, _ in built]
    objects.append(compile_asm(OUT / "clean-profile.s", OUT / "clean-profile.o"))
    stubbed = set(re.findall(rf"^{prefix}{objrewrite.CALL}(\w+):", (NATIVE / "natives.s").read_text(), re.M))
    stubs = native_build.call_stubs(syms, calls - stubbed)
    if not WINDOWS:
        stubs += ['\t.section .note.GNU-stack,"",@progbits']
    (OUT / "clean-calls.s").write_text("\n".join(["\t.text", *stubs]) + "\n", newline="\n")
    objects.append(compile_asm(OUT / "clean-calls.s", OUT / "clean-calls.o"))
    names = diffcheck.game_names(objects)
    # Through a response file, as the Native objects are: the paths would pass Windows's limit
    # on a command line.
    listed = tree / "objects.txt"
    listed.write_text("".join(f"{p.as_posix()}\n" for p in [*objects, *([names] if names else [])]), newline="\n")
    return [f"@{listed}"]


def build(native: bool, clean: str | None = None, ran: bool = False, play: str | None = None) -> pathlib.Path:
    """The runtime; with `native`, linked with every Native object as tools/diffcheck.py
    --native links them (runtime/native_table.h), else with an empty table; with `clean`, also
    with the Clean code (write_clean_table); with `ran`, also with runtime/clean_ran.c, which
    lists the Clean functions that run (--clean-ran), as a program of its own. The Clean code is
    the same: what each function computes and leaves in registers must not change. With `play`
    (a program name), the same run with runtime/play.c's window in front (tools/play.py)."""
    name = play or (("run-native" if native else "run") + ("-ran" if ran else ""))
    exe = OUT / (name + (".exe" if WINDOWS else ""))
    flags = ["-std=c11", "-O2", "-Wall", "-Wextra", "-fwrapv", "-fno-strict-aliasing", "-D_CRT_SECURE_NO_WARNINGS",
             "-D_CRT_NONSTDC_NO_WARNINGS", f"-I{RUNTIME}"]
    if not WINDOWS:
        flags.append("-D_DEFAULT_SOURCE")  # strdup and the POSIX calls, which -std=c11 leaves out
        # The program is linked at a fixed address (-no-pie below): position-independent code
        # would only cost a register and a call per function (the interpreter's among them).
        flags.append("-fno-pie")
    srcs = [str(RUNTIME / n) for n in SOURCES]
    extra: list[str] = []
    link: list[str] = []
    if native:
        if not (NATIVE / "natives.s").exists():
            raise SystemExit("run `python tools/native.py` first")
        assembly = [NATIVE / "natives.s", NATIVE / "absolute.s"]
        if WINDOWS:
            assembly.append(RUNTIME / "native_rt_win.s")
        extra = [str(compile_asm(a, OUT / ("run-" + a.name.replace(".s", ".o")))) for a in assembly]
        table = write_clean_table(clean)
        extra += [str(RUNTIME / "native_rt.c"), str(table), f"@{NATIVE / 'objects.txt'}"]
        if ran:
            extra.append(str(RUNTIME / "clean_ran.c"))
        if clean:
            extra += build_clean(flags)
        # Classes split one function per file define their destructors and vtable in several
        # objects, identically; the linker keeps the first. The image sits at a fixed low
        # address (below the DS's 0x01000000) and its data must not be executable: a call
        # into DS memory has to fault (runtime/native_run.h).
        # On Linux the heap starts after the image's last section (.heap_floor, above the DS's
        # addresses: runtime/memory.c).
        # The map names the host code a fault report points at.
        # No identical-code folding: every Native function keeps its own address, which the
        # runtime patches (functions kept Reference) and looks up by.
        link = (["-Wl,/SAFESEH:NO", "-Wl,/FORCE:MULTIPLE", "-Wl,/DYNAMICBASE:NO", "-Wl,/FIXED", "-Wl,/NXCOMPAT",
                 "-Wl,/OPT:NOICF",
                 f"-Wl,/MAP:{exe.with_suffix('.map')}"]
                if WINDOWS else ["-no-pie", "-Wl,--allow-multiple-definition", "-Wl,-z,noexecstack",
                                 "-Wl,-Ttext-segment=0x400000", "-Wl,--section-start=.heap_floor=0x10000000",
                                 f"-Wl,-Map={exe.with_suffix('.map')}"])
    else:
        srcs.append(str(RUNTIME / "native_none.c"))
        if not WINDOWS:
            link = ["-no-pie", "-Wl,-z,noexecstack"]
    if play:
        # run.c without its main, the front end's in its place (runtime/run.h). The window's
        # libraries load once the DS's memory is mapped: loaded with the program, they take
        # address space the DS's main RAM needs.
        srcs.append(str(RUNTIME / "play.c"))
        flags = [*flags, "-DRUN_FRONT_END"]
        link = [*link, "-luser32", "-lgdi32", "-ldelayimp", "-Wl,/DELAYLOAD:user32.dll", "-Wl,/DELAYLOAD:gdi32.dll"]
    cmd = [*diffcheck.compiler(), *flags, *srcs, *extra, *link, "-o", str(exe)]
    key = link_key(cmd)  # an unchanged program is not linked again
    if built_before(exe, key):
        return exe
    exe.with_name(exe.name + ".key").unlink(missing_ok=True)
    p = subprocess.run(cmd, capture_output=True, text=True)
    if p.returncode != 0:
        raise SystemExit((p.stdout + p.stderr)[-6000:])
    exe.with_name(exe.name + ".key").write_text(key)
    if p.stderr.strip() and not native:  # the Native link warns of every duplicate it drops
        print(p.stderr[-4000:], file=sys.stderr)
    return exe


# --------------------------------------------------------------------------- Native policy

def natives_table() -> dict[tuple[int, str], tuple[str, int]]:
    """(DS address with the Thumb bit, module) -> (name, info) of every Native function, as
    tools/native.py wrote natives.s."""
    text = (NATIVE / "natives.s").read_text()
    names = dict(re.findall(r"native_module_name_(\d+):\s*\.asciz \"(\w+)\"", text))
    out = {}
    prefix = "_" if WINDOWS else ""
    for addr, _size, host, info in re.findall(r"\.long 0x([0-9a-f]{8}), 0x([0-9a-f]+), (\S+), 0x([0-9a-f]{8})", text):
        info = int(info, 16)
        name = host[len(prefix):]
        if name.startswith("native_"):
            name = name[len("native_"):]
        out[(int(addr, 16), names[str(info >> 16)])] = (name, info)
    return out


def calls_something(code: bytes, start: int, thumb: bool) -> bool:
    """Whether a function's ROM code calls or jumps out of itself: BL/BLX, BX to a register
    other than lr, or a branch outside its bytes. Literal pools can look like either; that
    only makes a leaf look like a caller, which is the safe side."""
    end = start + len(code)
    if thumb:
        for i in range(0, len(code) - 1, 2):
            h = code[i] | code[i + 1] << 8
            if (h & 0xF800) == 0xF000 or (h & 0xFF87) == 0x4780:
                return True
            if (h & 0xFF87) == 0x4700 and ((h >> 3) & 15) != 14:
                return True
            if (h & 0xF800) == 0xE000:
                off = (h & 0x7FF) << 1
                target = start + i + 4 + (off - 0x1000 if off & 0x800 else off)
                if not start <= target < end:
                    return True
        return False
    for i in range(0, len(code) - 3, 4):
        w = int.from_bytes(code[i:i + 4], "little")
        if (w & 0xFE000000) == 0xFA000000 or ((w & 0x0F000000) == 0x0B000000 and w >> 28 != 15):
            return True
        if (w & 0x0FFFFFF0) == 0x012FFF30 or ((w & 0x0FFFFFF0) == 0x012FFF10 and (w & 15) != 14):
            return True
        if (w & 0x0F000000) == 0x0A000000 and w >> 28 != 15:
            off = (w & 0xFFFFFF) << 2
            target = start + i + 8 + (off - (1 << 26) if off & (1 << 25) else off)
            if not start <= target < end:
                return True
    return False


def kept_reference() -> dict[str, str]:
    """runtime/native-reference.txt: name -> why it stays Reference."""
    out = {}
    if KEPT.exists():
        for line in KEPT.read_text().splitlines():
            line = line.strip()
            if line and not line.startswith("#"):
                name, _, why = line.partition(" ")
                out[name] = why.strip()
    return out


def compiler_helpers(found: dict[tuple[str, int], str]) -> set[tuple[str, int]]:
    """The compiler helpers' (module, address): those `found` in the library sources, which are
    not distributed (libs/README.md), kept in HELPERS for a checkout without them."""
    if found:
        HELPERS.write_text("".join(f"{mod} {addr:08x} {name}\n" for (mod, addr), name in sorted(found.items())),
                           newline="\n")
        return set(found)
    out = set()
    for line in HELPERS.read_text().splitlines() if HELPERS.exists() else []:
        mod, addr, _name = line.split()
        out.add((mod, int(addr, 16)))
    return out


def library_arguments(found: dict[tuple[str, int], tuple[str, int, int]]) -> dict[tuple[str, int], tuple[int, int]]:
    """The library functions' parameter counts and argument words by (module, address): those
    `found` in the library sources, which are not distributed (libs/README.md), kept in
    LIBRARY_ARGUMENTS for a checkout without them. Without the words, a Native call into
    library code would copy the bridge's whole extent of host stack words onto the ROM's
    stack, over residue that the game's code reads later (the house's collision centres)."""
    if found:
        text = "".join(f"{mod} {addr:08x} {name} {count} {words}\n"
                       for (mod, addr), (name, count, words) in sorted(found.items()))
        if not LIBRARY_ARGUMENTS.exists() or LIBRARY_ARGUMENTS.read_text() != text:
            LIBRARY_ARGUMENTS.write_text(text, newline="\n")
        return {key: (count, words) for key, (_name, count, words) in found.items()}
    out = {}
    for line in LIBRARY_ARGUMENTS.read_text().splitlines() if LIBRARY_ARGUMENTS.exists() else []:
        mod, addr, _name, count, words = line.split()
        out[(mod, int(addr, 16))] = (int(count), int(words))
    return out


def write_policy(policy: str, clean: str | None = None) -> pathlib.Path:
    """Every function of every module with the letter runtime/native_run.c reads: N, C, R, H
    or -. With `clean`, every function with a Clean version is N."""
    mods = C.modules()
    contracts = native_contract.audited(C.ROOT, mods, C.module_image)
    syms = C.symbol_table(mods)
    table = natives_table()
    image = C.module_image('main')
    for address, size, _sha in native_publish.ROM_SITES:
        offset = address - mods['main']['base']
        native_publish.validate_rom(image[offset:offset + size], address)
    for relative in native_stack.SOURCES:
        native_stack.validate_source(relative, (C.SRC / relative).read_bytes().decode())
    kept = kept_reference()
    # what tools/native.py finds Native code cannot do (keep-reference.txt)
    found = NATIVE / "keep-reference.txt"
    for line in found.read_text().splitlines() if found.exists() else []:
        name, _, why = line.partition(" ")
        kept.setdefault(name, why)
    # every source's parameter count (with `this`), libraries' too: the Native run compares
    # the arguments of the calls Native code makes into the ROM's code
    params: dict[tuple[str, int], int] = {}
    arg_words: dict[tuple[str, int], int] = {}
    helpers: dict[tuple[str, int], str] = {}
    library: dict[tuple[str, int], tuple[str, int, int]] = {}
    # (what each source says, kept by its text and by the code that reads it: an unchanged
    # source is not parsed again)
    memo_path = OUT / "source-facts.json"
    readers = hashlib.sha1(b"".join((C.ROOT / "tools" / n).read_bytes()
                                    for n in ("common.py", "native.py", "native_abi.py"))).hexdigest()
    try:
        memo = json.loads(memo_path.read_text())
        memo = memo["facts"] if memo.get("readers") == readers else {}
    except (OSError, ValueError, KeyError):
        memo = {}
    facts = {}
    for path in C.all_sources():
        rel = path.relative_to(C.ROOT).as_posix()
        st = path.stat()
        digest = f"{st.st_size} {st.st_mtime_ns}"  # (a changed source has a new time)
        fact = memo.get(rel)
        if fact is None or fact[0] != digest:
            src = C.parse_source(path)
            fact = [digest, None]
            if src:
                _kind, count, member, _floating = native_build.signature(path, src.name)
                words = native_abi.word_arguments(path.read_text(encoding="utf-8", errors="replace"), src.name)
                fact = [digest, [src.module, src.address, src.name,
                                 count + int(member) if _kind != native_build.RET_SKIP or count else -1,
                                 words if words is not None else -1]]
        facts[rel] = fact
        if fact[1] is None:
            continue
        module, address, name, count, words = fact[1]
        params[(module, address)] = count
        arg_words[(module, address)] = words
        if C.LIBS in path.parents:
            library[(module, address)] = (name, count, words)
        if C.LIBS / "Runtime" in path.parents or (C.LIBS / "MSL" in path.parents and path.stem in HOST_NAMES):
            helpers[(module, address)] = name
    OUT.mkdir(parents=True, exist_ok=True)
    memo_path.write_text(json.dumps({"readers": readers, "facts": facts}), newline="\n")
    helpers = compiler_helpers(helpers)
    for key, (count, words) in library_arguments(library).items():
        params.setdefault(key, count)
        arg_words.setdefault(key, words)
    wanted: set[str] | None = None
    if policy not in ("all", "leaf", "none"):
        wanted = {w.split()[0] for w in pathlib.Path(policy).read_text().splitlines()
                  if w.strip() and not w.startswith("#")}
    cleaned = ({(module, address & ~1) for _, module, address, _ in clean_checks(clean)}
               | {(module, address & ~1) for _, _, module, address, _ in clean_registrations(clean)}) if clean else set()
    images: dict[str, bytes] = {}
    rows = []
    counts = {}
    for mod in mods:
        for s in syms.by_module.get(mod, []):
            if s.kind != "function" or not s.size:
                continue
            address = s.address | (1 if s.thumb else 0)
            native = table.get((address, mod))
            if native:
                name, info = native
                allowed = name not in kept
                if policy == "none":
                    allowed = False
                elif policy == "leaf" and allowed:
                    if mod not in images:
                        images[mod] = C.module_image(mod)
                    base = mods[mod]["base"]
                    code = images[mod][s.address - base:s.address - base + s.size]
                    allowed = not calls_something(code, s.address, s.thumb)
                elif wanted is not None:
                    allowed = allowed and (name in wanted or f"{s.address:08x}" in wanted)
                status = ("C" if (info & 15) == RET_SKIP else "N") if allowed else "R"
            elif (mod, s.address) in helpers:
                status = "H"
            else:
                status = "-"
            # A Clean version runs in place of its function, unless the function stays Reference for
            # what the PC cannot do (hardware, the ROM's stack layout): its Clean code cannot either.
            # One whose result the ROM's code takes another way than the PC's (a structure by
            # value: mwccarm passes a pointer to it in r0) runs Clean for Native callers only, as
            # its Native does.
            if (mod, s.address) in cleaned and s.name not in kept:
                status = "C" if native and (native[1] & 15) == RET_SKIP else "N"
            counts[status] = counts.get(status, 0) + 1
            frame, spill_arg, spill_offset = -1, -1, -1
            if (mod, s.address) in native_stack.FRAMES:
                if mod not in images:
                    images[mod] = C.module_image(mod)
                start = s.address - mods[mod]["base"]
                frame = native_stack.frame_extent(mod, s.address, images[mod][start:start + s.size])
                spill_arg, spill_offset = native_stack.SPILLS.get((mod, s.address), (-1, -1))
            contract = contracts.get((mod, s.address), 0)
            words = contract & 0xff if contract else arg_words.get((mod, s.address), -1)
            rows.append(f"{address:08x} {mod} {s.size:x} {status} {s.name} {params.get((mod, s.address), -1)} "
                        f"{words} {frame} {spill_arg} {spill_offset} {contract:x}\n")
    path = OUT / "native-policy.txt"
    path.write_text("".join(rows), newline="\n")
    print(f"native policy {policy}{' with Clean' if clean else ''}: {counts.get('N', 0)} Native, {counts.get('C', 0)} Native for Native callers "
          f"only, {counts.get('R', 0)} kept Reference, {counts.get('H', 0)} compiler helpers", flush=True)
    return path


# --------------------------------------------------------------------------- runs

def run_once(exe: pathlib.Path, manifest: pathlib.Path, table: pathlib.Path, budget: list[str], env: dict,
             log: pathlib.Path | None = None) -> tuple[int, str]:
    if log is None:
        p = subprocess.run([str(exe), str(ROM), str(manifest), str(table), *budget], cwd=C.ROOT, env=env)
        return p.returncode, ""
    with open(log, "w", encoding="utf-8", errors="replace") as out:
        p = subprocess.run([str(exe), str(ROM), str(manifest), str(table), *budget], cwd=C.ROOT, env=env,
                           stdout=out, stderr=subprocess.STDOUT)
    return p.returncode, log.read_text(encoding="utf-8", errors="replace")


def summary(text: str) -> dict:
    out = {"sequence": None, "ram": {}, "stop": None, "native": [], "diverged": None, "ram_differ": {}}
    for line in text.splitlines():
        m = re.search(r"sequence sha1 ([0-9a-f]{40})", line)
        if m:
            out["sequence"] = m.group(1)
        m = re.match(r"ram frame (\d+) ([0-9a-f]{40})", line)
        if m:
            out["ram"][int(m.group(1))] = m.group(2)
        m = re.match(r"native: memory after frame (\d+): (-?\d+) words differ", line)
        if m:
            out["ram_differ"][int(m.group(1))] = int(m.group(2))
        if line.startswith("== stop:"):
            out["stop"] = line.strip("= ")
        if line.startswith("native:"):
            out["native"].append(line)
            if "DIVERGED" in line and out["diverged"] is None:
                out["diverged"] = line
    return out


# The Reference pass only interprets the ROM: what it writes (its log, frame hashes, memory
# images, the crossings record) follows from the interpreter, the inputs, and which functions
# the policy makes Native or Clean (it records the crossings at those, and with Clean the
# runtime runs the static initialisers itself), not from what the Native or Clean code does.
# A run with all of those the same reuses an earlier run's results, from the cache every
# checkout shares (tools/common.py). ACWW_NO_REFERENCE_CACHE=1 always runs it.
REFERENCE_PATHS = ("RUN_HASH", "RUN_RAM_DUMP", "RUN_NATIVE_RECORD", "RUN_FUNCTIONS_SEEN")


def reference_key(env: dict, budget: list[str], manifest: pathlib.Path, table: pathlib.Path, args) -> str:
    h = hashlib.sha1()

    def add(label: str, data: bytes) -> None:
        h.update(f"{label}\0{len(data)}\0".encode() + data)
    for path in sorted(p for p in RUNTIME.iterdir() if p.is_file()):  # the interpreter and the runtime
        add(path.name, path.read_bytes())
    add("run.py", pathlib.Path(__file__).read_bytes())
    add("rom", ROM.read_bytes())
    add("modules", C.tree_free(manifest.read_text()).encode())
    add("symbols", table.read_bytes())
    for name in ("natives.s", "absolute.s"):  # which functions have a Native, and where
        add(name, (NATIVE / name).read_bytes())
    if args.clean:
        add("clean table", (OUT / "clean_table.c").read_bytes())
    add("budget", " ".join(budget).encode())
    for name, value in sorted(env.items()):
        if not name.startswith("RUN_") or name in REFERENCE_PATHS:
            continue
        path = pathlib.Path(value)
        add(name, path.read_bytes() if path.is_file() else value.encode())  # a file by its content
    add("paths", " ".join(n for n in REFERENCE_PATHS if n in env).encode())
    return h.hexdigest()


def reference_files(out: pathlib.Path, ram_dir: pathlib.Path, trace: pathlib.Path) -> dict[str, pathlib.Path]:
    files = {"reference.log": out / "reference.log", "reference-hashes.txt": out / "reference-hashes.txt"}
    if (out / "functions-seen.txt").exists():
        files["functions-seen.txt"] = out / "functions-seen.txt"
    if trace.exists():
        files["crossings.bin"] = trace
    files |= {f"ram/{p.name}": p for p in ram_dir.glob("ram-*-reference.bin")}
    return files


def reference_cached(key: str, out: pathlib.Path, ram_dir: pathlib.Path, trace: pathlib.Path) -> bool:
    """Put a cached Reference run's results in place; False when there is none."""
    entry = C.CACHE_DIR / "reference" / key[:2] / key
    if os.environ.get("ACWW_NO_REFERENCE_CACHE") or not (entry / "done").exists():
        return False
    try:
        trace.unlink(missing_ok=True)
        (out / "functions-seen.txt").unlink(missing_ok=True)  # (an older entry has none)
        for old in ram_dir.glob("ram-*-reference.bin"):
            old.unlink()
        for src in entry.rglob("*"):
            name = src.relative_to(entry).as_posix()
            if src.is_file() and name != "done":
                dest = ram_dir / src.name if name.startswith("ram/") else out / name
                shutil.copyfile(src, dest)
        os.utime(entry)
        return True
    except OSError:
        return False


def keep_reference(key: str, out: pathlib.Path, ram_dir: pathlib.Path, trace: pathlib.Path) -> None:
    """Keep this Reference run's results in the shared cache (written whole, then renamed)."""
    if os.environ.get("ACWW_NO_REFERENCE_CACHE"):
        return
    entry = C.CACHE_DIR / "reference" / key[:2] / key
    if (entry / "done").exists():
        return
    tmp = entry.with_name(f"{key}.{os.getpid()}")
    try:
        for name, src in reference_files(out, ram_dir, trace).items():
            (tmp / name).parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(src, tmp / name)
        (tmp / "done").touch()
        os.replace(tmp, entry)
    except OSError:
        shutil.rmtree(tmp, ignore_errors=True)
    C.prune_cache(("reference",))


def native_main(args, manifest, table, budget, env) -> int:
    exe = build(native=True, clean=args.clean, ran=bool(args.clean_ran))
    env = dict(env)
    env.pop("RUN_CLEAN_RAN", None)
    hash_file = env.pop("RUN_HASH", None)
    out = OUT / "native-run"
    out.mkdir(parents=True, exist_ok=True)
    env["RUN_NATIVE_POLICY"] = str(write_policy(args.native, args.clean))
    if args.ram_hash:
        env["RUN_RAM_HASH"] = args.ram_hash
    # the Reference pass leaves its memory images there; the Native pass compares with them
    ram_dir = pathlib.Path(args.ram_dump) if args.ram_dump else out / "ram"
    ram_dir.mkdir(parents=True, exist_ok=True)
    env["RUN_RAM_DUMP"] = str(ram_dir.resolve())
    trace = out / "crossings.bin"

    def reference() -> dict:
        ref_env = dict(env, RUN_HASH=str(out / "reference-hashes.txt"))
        if not args.no_timing:
            ref_env["RUN_NATIVE_RECORD"] = str(trace)
            # the functions the game runs, for scenes.py --affected
            ref_env["RUN_FUNCTIONS_SEEN"] = str(out / "functions-seen.txt")
        # (a run that writes pictures, RUN_PNG, keeps nothing: the cache holds no pictures)
        key = None if "RUN_PNG" in ref_env else reference_key(ref_env, budget, manifest, table, args)
        if key and reference_cached(key, out, ram_dir, trace):
            print(f"reference run: the results of an identical one ({key[:12]})", flush=True)
            return summary((out / "reference.log").read_text(encoding="utf-8", errors="replace"))
        print("reference run" + ("" if args.no_timing else " (recording the crossings)") + "...", flush=True)
        status, text = run_once(exe, manifest, table, budget, ref_env, out / "reference.log")
        # only a run that ended as it should is kept: one cut short (a full disk, a crash)
        # would otherwise be reused as if it were the Reference
        if key and status == 0 and summary(text)["sequence"] is not None:
            keep_reference(key, out, ram_dir, trace)
        return summary(text)

    ref = reference()
    nat_env = dict(env, RUN_NATIVE="1", RUN_HASH=hash_file or str(out / "native-hashes.txt"))
    if not args.no_timing:
        nat_env["RUN_NATIVE_REPLAY"] = str(trace)
    ran = out / "clean-ran.txt"
    if args.clean_ran:
        ran.unlink(missing_ok=True)
        nat_env["RUN_CLEAN_RAN"] = str(ran)
    learn = out / "learned.txt"
    while True:
        if args.learn:
            learn.unlink(missing_ok=True)
            nat_env["RUN_NATIVE_LEARN"] = str(learn)
        print("native run...", flush=True)
        status, nat_text = run_once(exe, manifest, table, budget, nat_env, out / "native.log")
        if status != 3 or not args.learn or not learn.exists():
            break
        kept = kept_reference()
        added = [line for line in learn.read_text().splitlines() if line.split()[0] not in kept]
        if not added:
            break
        with open(KEPT, "a", newline="\n") as f:
            f.write("".join(line + "\n" for line in added))
        print("kept Reference from now on: " + "; ".join(added), flush=True)
        # the record depends on which functions are Native: make it again
        env["RUN_NATIVE_POLICY"] = nat_env["RUN_NATIVE_POLICY"] = str(write_policy(args.native, args.clean))
        ref = reference()
    nat = summary(nat_text)
    if args.clean_ran:
        write_ran(ran, pathlib.Path(args.clean_ran))
    # the run's directory may be outside the tree (ACWW_RUNTIME_OUT)
    shown = [p.relative_to(C.ROOT) if p.is_relative_to(C.ROOT) else p
             for p in (out / "reference.log", out / "native.log")]
    print(f"logs: {shown[0].as_posix()}, {shown[1].as_posix()}")
    for line in nat["native"]:
        print(line)
    if nat["stop"]:
        print(f"native run: {nat['stop']}")
    print(f"frames: reference {ref['sequence']}, native {nat['sequence']}")
    same = ref["sequence"] is not None and ref["sequence"] == nat["sequence"]
    if args.expect:
        expected = pathlib.Path(args.expect).read_text().split()[0]
        print(f"frames expected ({args.expect}): {expected}")
        same = same and nat["sequence"] == expected
    wanted = [int(f) for f in args.ram_hash.split(",")] if args.ram_hash else []
    for frame in sorted(set(ref["ram"]) | set(nat["ram"]) | {f for f in wanted if budget and f < int(budget[-1])}):
        a, b = ref["ram"].get(frame), nat["ram"].get(frame)
        differ = nat["ram_differ"].get(frame)
        verdict = "same" if a == b else "same apart from words holding PC addresses"
        verdict = verdict if differ == 0 else "DIFFERENT" if differ is None else f"DIFFERENT in {differ} words"
        print(f"ram after frame {frame}: reference {a}, native {b}: {verdict}")
        same = same and differ == 0
    print("Native and Reference agree" if same else "Native and Reference DIFFER")
    return 0 if same else 1


def write_ran(raw: pathlib.Path, out: pathlib.Path) -> None:
    """The Native run's list (runtime/clean_ran.c: "address module 0|1" for each Clean function)
    as JSON, one entry per function."""
    if not raw.exists():
        print(f"clean ran: the Native run wrote no {raw}")
        return
    ran: dict[tuple[str, int], bool] = {}
    for line in raw.read_text().splitlines():
        address, module, flag = line.split()
        key = (module, int(address, 16) & ~1)
        ran[key] = ran.get(key, False) or flag == "1"
    rows = [{"module": m, "address": f"{a:08x}", "ran": r} for (m, a), r in sorted(ran.items())]
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(rows, indent=1) + "\n", newline="\n")
    print(f"clean ran: {sum(ran.values())} of {len(ran)} Clean functions ran ({out})")


def main() -> None:
    ap = argparse.ArgumentParser(description="Boot the game in the interpreter.")
    ap.add_argument("max_instructions", nargs="?", help="instruction budget (0: none; default 200 M)")
    ap.add_argument("max_frames", nargs="?", help="stop after this many frames")
    ap.add_argument("--png", metavar="DIR", help="save frames as PNGs in DIR")
    ap.add_argument("--png3d", metavar="DIR", help="save the 3D layer alone as PNGs in DIR")
    ap.add_argument("--frames", metavar="LIST", help="frames to save: n, a-b, a-b/step, comma-separated")
    ap.add_argument("--hash", metavar="FILE", help="per-frame SHA-1s to FILE, or - for stdout")
    ap.add_argument("--input", metavar="FILE", help="input recording")
    ap.add_argument("--rtc", metavar="TIME", help='pin the clock: "YYYY-MM-DD HH:MM:SS"')
    ap.add_argument("--save", metavar="FILE", help="the save chip's image at power-on")
    ap.add_argument("--native", metavar="POLICY", help="all, leaf, none, or a file of functions (see above)")
    ap.add_argument("--ram-hash", metavar="FRAMES", help="hash memory after these frames (comma-separated)")
    ap.add_argument("--ram-dump", metavar="DIR", help="write the hashed memory images to DIR")
    ap.add_argument("--no-timing", action="store_true", help="Native run without the Reference's timing")
    ap.add_argument("--learn", action="store_true", help="keep functions that touch hardware Reference")
    ap.add_argument("--expect", metavar="FILE", help="with --native: the frame sequence SHA-1 both runs must give")
    ap.add_argument("--clean", nargs="?", const="all", metavar="FILE",
                    help="with --native: Clean functions (all, or those FILE lists) in place of their Native ones")
    ap.add_argument("--clean-ran", metavar="FILE", help="with --clean: which Clean functions ran, as JSON to FILE")
    args = ap.parse_args()
    if args.clean_ran and not args.clean:
        raise SystemExit("--clean-ran needs --clean")
    if args.clean and not args.native:
        raise SystemExit("--clean needs --native")
    if not ROM.exists():
        raise SystemExit(f"no ROM at {ROM}")
    manifest, table = generate()
    env = dict(os.environ)
    if args.png:
        pathlib.Path(args.png).mkdir(parents=True, exist_ok=True)
        env["RUN_PNG"] = str(pathlib.Path(args.png).resolve())
    if args.png3d:
        pathlib.Path(args.png3d).mkdir(parents=True, exist_ok=True)
        env["RUN_DUMP3D"] = str(pathlib.Path(args.png3d).resolve())
    if args.frames:
        env["RUN_PNG_FRAMES"] = args.frames
    if args.hash:
        if args.hash != "-":
            pathlib.Path(args.hash).resolve().parent.mkdir(parents=True, exist_ok=True)
        env["RUN_HASH"] = args.hash if args.hash == "-" else str(pathlib.Path(args.hash).resolve())
    if args.input:
        env["RUN_INPUT"] = str(pathlib.Path(args.input).resolve())
    if args.rtc:
        env["RUN_RTC"] = args.rtc
    env.pop("RUN_SAVE", None)
    if args.save:
        if not pathlib.Path(args.save).is_file():
            raise SystemExit(f"no save at {args.save}")
        env["RUN_SAVE"] = str(pathlib.Path(args.save).resolve())
    budget = [a for a in (args.max_instructions, args.max_frames) if a is not None]
    if args.native:
        sys.exit(native_main(args, manifest, table, budget, env))
    if args.ram_hash:
        env["RUN_RAM_HASH"] = args.ram_hash
    if args.ram_dump:
        pathlib.Path(args.ram_dump).mkdir(parents=True, exist_ok=True)
        env["RUN_RAM_DUMP"] = str(pathlib.Path(args.ram_dump).resolve())
    exe = build(native=False)
    status, _ = run_once(exe, manifest, table, budget, env)
    sys.exit(status)


if __name__ == "__main__":
    main()
