"""Compile the matching sources for the PC (Native; docs/runtime.md) and describe them for
the runtime.

    python tools/native.py

Writes, under build/adm-kr/native/<host>/:
- one object per source, compiled for 32-bit x86 with runtime/native.h included first;
- absolute.s: every name those objects use but do not define, at its DS address from the
  symbol table, so Native code reads and writes the game's memory where the game has it;
- natives.s: the table of Native functions (runtime/native_table.h);
- objects.txt: the objects, for the linker;
- left-out.txt: the sources that do not compile for the PC, with the reason, and the names no
  table entry resolves.

On Windows the objects target i686-pc-windows-itanium, whose C++ names are the same Itanium
names the symbol table has, and whose member functions take `this` on the stack (cdecl) as on
Linux: windows-gnu would make them thiscall, and Native code calls through the ROM's vtables,
which hold C functions as well as members. Elsewhere gcc -m32.
"""

from __future__ import annotations

import collections
import concurrent.futures as cf
import hashlib
import json
import os
import pathlib
import re
import shlex
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402
import protos  # noqa: E402
import objrewrite  # noqa: E402

OUT = C.BUILD / "native" / ("windows" if os.name == "nt" else "linux")
WINDOWS = os.name == "nt"
LLVM = pathlib.Path(os.environ.get("LLVM", "C:/Program Files/LLVM/bin"))
# Names in COFF objects for i386 carry a leading underscore.
PREFIX = "_" if WINDOWS else ""
# Old C the sources still have (implicit int, undeclared calls, a value-less return) is an
# error in current compilers; it compiles as it did for mwccarm.
RELAX = ["-Wno-error=implicit-int", "-Wno-error=implicit-function-declaration",
         "-Wno-error=return-mismatch", "-Wno-error=int-conversion",
         "-Wno-error=incompatible-pointer-types"]

# Names the PC's own C library and compiler helpers provide (runtime/native_rt*): the game
# has its own memcpy and so on in the ROM, with the same behaviour, but the host's must win.
HOST_NAMES = {"memcmp", "memcpy", "memmove", "memset", "strcat", "strchr", "strcmp", "strcpy", "strlen",
              "strncmp", "strncpy", "__udivdi3", "__umoddi3", "__divdi3", "__moddi3", "_alloca"}

# How a function returns its value, as runtime/native_table.h numbers them.
RET_VOID, RET_U8, RET_S8, RET_U16, RET_S16, RET_32, RET_64, RET_SKIP = range(8)
# the instruction that widens a narrow result in eax
WIDEN = {RET_U8: "movzbl %al, %eax", RET_S8: "movsbl %al, %eax", RET_U16: "movzwl %ax, %eax",
         RET_S16: "movswl %ax, %eax"}
COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
# the vtable of a class named after it (`_ZTV12Obj_020d82b4`, `_ZTV18Obj_ov128_0229cbc0`)
NAMED_ADDRESS = re.compile(r"^(?:g|data|gData|s|sData|D)_(?:ov\d{3}_)?(0[12][0-9a-f]{6})$")
VTABLE = re.compile(r"_ZTV\d+Obj_(?:ov\d{3}_)?([0-9a-f]{8})$")
WORDS_TO_DROP = {"static", "inline", "extern", "const", "volatile", "struct", "enum", "unsigned_"}


def compiler() -> list[str]:
    if os.environ.get("NATIVE_CC"):
        return shlex.split(os.environ["NATIVE_CC"])
    if WINDOWS:
        return [str(LLVM / "clang.exe"), "--target=i686-pc-windows-itanium"]
    return ["gcc", "-m32"]


def flags_for(path: pathlib.Path) -> list[str]:
    lang = ["-x", "c++", "-std=c++11", "-fno-rtti"] if path.suffix == ".cpp" else ["-x", "c", "-std=gnu11"]
    # no position-independent code: references must be plain relocations tools/objrewrite.py
    # can point at the game's memory
    pic = [] if WINDOWS else ["-fno-pic", "-fno-pie"]
    # no stack canaries (Ubuntu's gcc adds them by default): the ROM's code has none, and some
    # of it writes past a local array, harmlessly on the DS and in the PC's frame alike
    pic += ["-fno-stack-protector"]
    # structures as the DS lays them out (runtime/native.h): GCC's bit-fields on Windows too
    layout = ["-mno-ms-bitfields"] if WINDOWS else []
    relax = RELAX if "clang" in " ".join(compiler()) else []  # gcc only warns about these
    return [*lang, *pic, *layout, "-O2", "-w", *relax, "-fwrapv", "-fno-strict-aliasing", "-fno-exceptions",
            "-include", str(C.ROOT / "runtime" / "native.h"), f"-I{C.INCLUDE}", f"-I{C.INCLUDE / 'msl'}"]


def nm(obj: pathlib.Path) -> tuple[set[str], set[str]]:
    """(defined global names, undefined names) of an object."""
    tool = str(LLVM / "llvm-nm.exe") if WINDOWS else "nm"
    out = subprocess.run([tool, str(obj)], capture_output=True, text=True).stdout
    defined, undefined = set(), set()
    for line in out.splitlines():
        parts = line.split()
        if len(parts) == 2 and parts[0] == "U":
            undefined.add(parts[1])
        elif len(parts) == 3 and parts[1] in "TDBRVWC":
            defined.add(parts[2])
    return defined, undefined


def compile_one(path: pathlib.Path) -> tuple[pathlib.Path, pathlib.Path | None, str]:
    flags = flags_for(path)
    obj = OUT / "obj" / path.relative_to(C.SRC).with_suffix(".o")
    key = hashlib.sha1(path.read_bytes() + " ".join(compiler() + flags).encode())
    key.update((C.ROOT / "runtime" / "native.h").read_bytes())  # included first, by -include
    for inc in C.included_files(path):
        key.update(inc.read_bytes())
    stamp = obj.with_suffix(".key")
    if obj.exists() and stamp.exists() and stamp.read_text() == key.hexdigest():
        return path, obj, ""
    obj.parent.mkdir(parents=True, exist_ok=True)
    p = subprocess.run([*compiler(), "-c", *flags, str(path), "-o", str(obj)], capture_output=True,
                       text=True, errors="replace")
    if p.returncode != 0:
        first = next((line for line in p.stderr.splitlines() if "error" in line), p.stderr.strip()[-200:])
        return path, None, first.split("error:", 1)[-1].strip()
    stamp.write_text(key.hexdigest())
    return path, obj, ""


def rewrite_one(obj: pathlib.Path, known: set[str], native: set[str], names_key: str) -> tuple[pathlib.Path, set[str]]:
    """The object with its references pointed at the game's memory, and the names it now
    refers to by their DS address (cached by the object's content and by the sets of names:
    a call goes to another Native function only while that one compiles)."""
    data = obj.read_bytes()
    out = OUT / "linked" / obj.relative_to(OUT / "obj")
    stamp = out.with_suffix(".names")
    key = hashlib.sha1(data + names_key.encode()).hexdigest()
    if out.exists() and stamp.exists() and stamp.read_text().startswith(key):
        return out, set(stamp.read_text().split()[1:])
    new, names = objrewrite.rewrite(data, known, native, PREFIX)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_bytes(new)
    stamp.write_text(" ".join([key, *sorted(names)]))
    return out, names


def signature(path: pathlib.Path, name: str) -> tuple[int, int, bool, int]:
    """(return kind, parameter count, called as a C++ member, floating-point result) of the
    function defined in `path` under the source name `name`. RET_SKIP when the check cannot
    compare the result: a floating-point value, a structure returned by value, or a definition
    it cannot find. The last is 1 for a float result, 2 for a double (the PC returns those in
    st(0), the DS in r0 or r0:r1), else 0."""
    text = COMMENT.sub(" ", path.read_text(encoding="utf-8", errors="replace")).replace('extern "C"', " ")
    pattern = (r"(?:^|[;}])\s*((?:[\w<>]+[\s\*&]+)+?)((?:\w+::)?)" + re.escape(name)
               + r"\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*(?:const\s*)?\{")
    m = re.search(pattern, text, re.M)
    if not m:
        return RET_SKIP, 0, False, 0
    words = [w for w in m.group(1).replace("*", " * ").replace("&", " & ").split() if w not in WORDS_TO_DROP]
    member = bool(m.group(2)) and "static" not in m.group(1).split()
    params = " ".join(m.group(3).split())
    depth, count = 0, 0 if params in ("", "void") else 1
    for ch in params:
        depth += ch == "("
        depth -= ch == ")"
        count += ch == "," and depth == 0
    floating = 0
    if "*" in words or "&" in words:
        kind = RET_32
    elif words == ["void"]:
        kind = RET_VOID
    elif {"float", "double", "f32", "f64"} & set(words):
        kind = RET_SKIP
        floating = 2 if {"double", "f64"} & set(words) else 1
    elif words.count("long") == 2 or {"u64", "s64"} & set(words):
        kind = RET_64
    elif words in (["u8"], ["unsigned", "char"]):
        kind = RET_U8
    elif words in (["s8"], ["char"], ["signed", "char"]):
        kind = RET_S8
    elif words in (["u16"], ["unsigned", "short"], ["unsigned", "short", "int"]):
        kind = RET_U16
    elif words in (["s16"], ["short"], ["signed", "short"], ["short", "int"]):
        kind = RET_S16
    elif len(words) == 1 and re.match(r"(Unk|Obj|Base|Elem|Member|Vec|Pair)\w*$", words[0]):
        kind = RET_SKIP
    else:
        kind = RET_32
    return kind, count, member, floating


ASM_FUNCTION = re.compile(r"^\s*asm\s+[\w\s\*]*\w+\s*\(", re.M)
STRUCT_TYPE = re.compile(r"\}\s*(\w+)\s*;|\bstruct\s+(\w+)\s*\{")


PMF_TYPEDEF = re.compile(r"\(\s*(?:\w+\s*::\s*)+\*\s*(\w+)\s*\)")


def pmf_names(path: pathlib.Path, text: str) -> list[str]:
    """The member-function pointer types (typedef'd in the headers `path` includes) that its
    text names: a source that calls through a table of them has no `::*` of its own."""
    names = set()
    for header in C.included_files(path):
        names |= set(PMF_TYPEDEF.findall(COMMENT.sub(" ", header.read_text(encoding="utf-8", errors="replace"))))
    return sorted(n for n in names if re.search(r"\b" + re.escape(n) + r"\b", text))


def struct_results(text: str) -> list[str]:
    """The functions a source declares as returning a structure (its own typedefs or struct
    tags) by value and calls. Virtual methods count too: called through the vtable, a Reference
    callee stores its result where the PC's Native passed something else (`this`)."""
    types = {a or b for a, b in STRUCT_TYPE.findall(text)}
    out = []
    decl = r"(?:^|[;}:])\s*(?:(?:extern|virtual|static|inline)\s+)*(?:struct\s+)?(\w+)\s+(\w+)\s*\([^;{}]*\)\s*(?:const\s*)?;"
    for m in re.finditer(decl, text, re.M):
        rtype, fname = m.group(1), m.group(2)
        if rtype in types and re.search(r"\b" + re.escape(fname) + r"\s*\(", text[m.end():]):
            out.append(fname)
    return out


def main() -> None:
    paths = [p for p in C.all_sources() if C.SRC in p.parents]
    OUT.mkdir(parents=True, exist_ok=True)
    workers = max(1, (os.cpu_count() or 4) - 2)
    objects, left_out = [], []
    with cf.ThreadPoolExecutor(workers) as pool:
        for path, obj, why in pool.map(compile_one, paths):
            if obj is None:
                left_out.append((path, why))
            else:
                objects.append((path, obj))
    defined, undefined = set(), set()
    per_object = []
    with cf.ThreadPoolExecutor(workers) as pool:
        for d, u in pool.map(nm, (o for _, o in objects)):
            defined |= d
            undefined |= u
            per_object.append(d | u)

    # Point every reference at the game's memory, except direct calls between Native
    # functions (tools/objrewrite.py).
    syms = C.SymbolTable(C.modules())
    known = set(syms.by_name) - HOST_NAMES
    strip = len(PREFIX)
    # A class named after its vtable (Obj_<address>, CONTRIBUTING.md) has its vtable there in
    # the ROM: a constructor compiled for the PC must install that one, not the PC's copy,
    # or the ROM's code calling through it reaches PC addresses. The Itanium vtable symbol
    # comes 8 bytes (offset to top, type info) before the address point the object holds;
    # mwccarm's vtable has two zero words there too.
    vtables = {}
    for d in defined | undefined:
        m = VTABLE.match(d[strip:] if d.startswith(PREFIX) else d)
        if m:
            vtables[m.group(0)] = int(m.group(1), 16) - 8
    known |= set(vtables)
    # Data a source defines under a name the symbol table does not have, but that names its
    # address (`int g_021f450c;`): the ROM has it there, and the ROM's code uses it there.
    for d in defined:
        name = d[strip:] if d.startswith(PREFIX) else d
        m = NAMED_ADDRESS.match(name)
        if m and name not in known and name not in syms.by_name:
            vtables[name] = int(m.group(1), 16)
    known |= set(vtables)
    native = {d[strip:] for d in defined if d.startswith(PREFIX)} & known
    # A function that returns a char or a short: the ROM's code widens the result in r0 and
    # callers rely on it (many declare such a function as returning int); the PC's code
    # leaves the upper bits of eax undefined. Its definition becomes native_body_<name>, and
    # native_<name> a wrapper that widens the result as the ROM's code does.
    widen = {}
    for path, _ in objects:
        src = C.parse_source(path)
        kind = signature(path, src.name)[0]
        if kind in WIDEN and src.object_symbol in native:
            widen[src.object_symbol] = WIDEN[kind]
    objrewrite.BODY = set(widen)
    names_key = hashlib.sha1(" ".join(sorted(native) + ["|"] + sorted(known) + ["|"] + sorted(widen)).encode()
                             + pathlib.Path(objrewrite.__file__).read_bytes()).hexdigest()
    to_ds: set[str] = set()
    rewritten = []
    with cf.ThreadPoolExecutor(workers) as pool:
        for (path, _), (obj, names) in zip(objects, pool.map(lambda po: rewrite_one(po[1], known, native, names_key),
                                                             objects)):
            rewritten.append((path, obj))
            to_ds |= names
    objects = rewritten
    undefined |= {PREFIX + n for n in to_ds}
    defined = {PREFIX + objrewrite.NATIVE + d[strip:] if d[strip:] in known else d for d in defined}

    # every name used but not defined goes to its DS address
    absolute, unknown = [], []
    for host in sorted(undefined - defined):
        name = host[len(PREFIX):] if host.startswith(PREFIX) else host
        if name in HOST_NAMES:
            continue
        addrs = {s.address | (1 if s.kind == "function" and s.thumb else 0)
                 for s in syms.by_name.get(name, [])}
        if name in vtables:
            absolute.append((host, vtables[name]))
        elif len(addrs) == 1:
            absolute.append((host, addrs.pop()))
        elif not name.startswith("_Z"):
            # a helper of the PC's compiler or C runtime (__chkstk, __aulldiv,
            # __cxa_guard_acquire, ...): the host provides it; a definition here would take its
            # place for the whole program
            unknown.append((host, len(addrs)))
        else:
            # mostly vtable slots named by position (`vfunc_60`) that no function has; a call
            # through one faults at address 0, which the runtime reports
            unknown.append((host, len(addrs)))
            absolute.append((host, 0))
    (OUT / "absolute.s").write_text("".join(f"\t.globl {h}\n\t.set {h}, 0x{a:08x}\n" for h, a in absolute),
                                    newline="\n")

    # the table of Native functions (runtime/native_table.h)
    modules = list(C.modules())
    lines = ["\t.data", f"\t.globl {PREFIX}native_module_names", f"{PREFIX}native_module_names:"]
    lines += [f"\t.long native_module_name_{i}" for i in range(len(modules))]
    lines += [f"\t.globl {PREFIX}native_module_count", f"{PREFIX}native_module_count:", f"\t.long {len(modules)}"]
    lines += [f"native_module_name_{i}:\n\t.asciz \"{m}\"" for i, m in enumerate(modules)]
    lines += ["\t.p2align 2", f"\t.globl {PREFIX}native_functions", f"{PREFIX}native_functions:"]
    count = 0
    for path, _ in objects:
        src = C.parse_source(path)
        host = PREFIX + (objrewrite.NATIVE if src.object_symbol in known else "") + src.object_symbol
        if host not in defined:
            continue
        kind, params, member, floating = signature(path, src.name)
        info = (kind | (min(params, 15) << 4) | (int(member) << 8) | (floating << 9)
                | (modules.index(src.module) << 16))
        lines.append(f"\t.long 0x{src.address | (1 if src.thumb else 0):08x}, 0x{src.size:x}, {host}, 0x{info:08x}")
        count += 1
    lines += [f"\t.globl {PREFIX}native_function_count", f"{PREFIX}native_function_count:", f"\t.long {count}"]

    # the wrappers that widen narrow results: the arguments (16 words, more than any function
    # takes) are copied down for the body, whose result is then extended
    lines += ["\t.text"]
    for name, extend in sorted(widen.items()):
        wrapper, body = PREFIX + objrewrite.NATIVE + name, PREFIX + objrewrite.NATIVE + "body_" + name
        lines += [f"\t.globl {wrapper}", f"{wrapper}:", "\tpushl %ebp", "\tmovl %esp, %ebp", "\tpushl %esi",
                  "\tpushl %edi", "\tsubl $64, %esp", "\tleal 8(%ebp), %esi", "\tmovl %esp, %edi",
                  "\tmovl $16, %ecx", "\trep movsl", f"\tcalll {body}", f"\t{extend}", "\taddl $64, %esp",
                  "\tpopl %edi", "\tpopl %esi", "\tpopl %ebp", "\tretl"]
    lines += ["\t.data"]
    # each body with its wrapper, so the runtime can name the function a fault in a body is in
    lines += [f"\t.globl {PREFIX}native_bodies", f"{PREFIX}native_bodies:"]
    lines += [f"\t.long {PREFIX}{objrewrite.NATIVE}body_{name}, {PREFIX}{objrewrite.NATIVE}{name}"
              for name in sorted(widen)] or ["\t.long 0, 0"]
    lines += [f"\t.globl {PREFIX}native_body_count", f"{PREFIX}native_body_count:", f"\t.long {len(widen)}"]

    # Each function's own static data in the ROM (from tools/link.py's placement). The PC
    # version keeps its statics in its own memory, so writes there are not compared.
    placement_file = C.BUILD / "placement.json"
    placement = json.loads(placement_file.read_text()) if placement_file.exists() else {}
    lines += [f"\t.globl {PREFIX}native_private", f"{PREFIX}native_private:"]
    private = 0
    for path, _ in objects:
        src = C.parse_source(path)
        for _name, _mod, _romsec, start, end in placement.get(path.relative_to(C.ROOT).as_posix(), []):
            lines.append(f"\t.long 0x{src.address:08x}, 0x{start:08x}, 0x{end:08x}")
            private += 1
    lines += [f"\t.globl {PREFIX}native_private_count", f"{PREFIX}native_private_count:", f"\t.long {private}", ""]
    (OUT / "natives.s").write_text("\n".join(lines), newline="\n")
    # Sources whose Native cannot do what the ROM's code does (tools/run.py keeps them
    # Reference): one that installs a vtable the ROM has at no known address (a class not named
    # after its vtable), so the objects it makes would hold a PC vtable the ROM's code cannot
    # call through; and one that calls a function no address is known for, mostly a virtual
    # call on an object (not a pointer) that the PC's compiler makes directly, to a method the
    # ROM only reaches through the vtable.
    nowhere = {h for h, a in absolute if a == 0}
    # A caller that declares a function with fewer parameters than its definition leaves the
    # rest to whatever r1-r3 hold, which on the DS are often the caller's own arguments passed
    # on; one that uses the result of a function defined void reads whatever r0 holds. The PC
    # passes and returns neither.
    short: dict[str, list[str]] = collections.defaultdict(list)
    for rel, callee, n, dn, ret, dret, _drel in protos.disagreements():
        if (n is not None and dn is not None and n < dn) or (ret and not dret):
            short[rel].append(callee)
    keep = []
    for (path, _), names in zip(objects, per_object):
        name = C.parse_source(path).object_symbol
        vts = sorted({n[strip:] for n in names if n[strip:].startswith("_ZTV") and n[strip:] not in vtables})
        zero = sorted(n[strip:] for n in names & nowhere)
        text = COMMENT.sub(" ", path.read_text(encoding="utf-8", errors="replace"))
        by_value = struct_results(text)
        if "__MWERKS__" in text and ASM_FUNCTION.search(text):
            keep.append(f"{name} matches as assembly (`asm`, under #ifdef __MWERKS__); its C version for the PC "
                        "is a rewrite, and passes registers on differently" + chr(10))
            continue
        inner = sorted(set(re.findall(r"\b(\w+_unk)\s*\(", text)) - {name})
        if inner:
            keep.append(f"{name} calls {' '.join(inner)}, an entry into the middle of other code: the ROM's code "
                        "there goes on into a function whose Native would not start there" + chr(10))
        elif by_value:
            keep.append(f"{name} calls {' '.join(by_value)}, which returns a structure by value: mwccarm passes "
                        "a pointer to the result in r0, the PC's compiler returns a small one in registers\n")
        elif "::*" in text or "->*" in text or pmf_names(path, text):
            keep.append(f"{name} uses member-function pointers, which mwccarm lays out in 12 bytes and the PC "
                        "(Itanium C++ ABI) in 8\n")
        elif short.get(path.relative_to(C.ROOT).as_posix()):
            keep.append(f"{name} declares {' '.join(sorted(set(short[path.relative_to(C.ROOT).as_posix()])))} with "
                        "fewer parameters than their definitions or a result they do not return, which the DS "
                        "passes in registers and the PC does not" + chr(10))
        elif vts:
            keep.append(f"{name} installs a vtable the ROM has at no known address ({' '.join(vts)})\n")
        elif zero:
            keep.append(f"{name} calls {' '.join(zero)}, which has no address (a virtual call the PC's "
                        "compiler makes directly)\n")
    (OUT / "keep-reference.txt").write_text("".join(keep), newline="\n")
    (OUT / "objects.txt").write_text("".join(f"{o.as_posix()}\n" for _, o in objects), newline="\n")
    (OUT / "left-out.txt").write_text(
        "".join(f"{p.relative_to(C.ROOT).as_posix()}: {why}\n" for p, why in left_out)
        + "".join(f"(no address) {h}: {n} candidates\n" for h, n in unknown), newline="\n")
    print(f"{len(objects)} of {len(paths)} sources compile for the PC; {count} functions in the table")
    print(f"  {len(absolute)} names placed at their DS address, {len(unknown)} without one")
    print(f"  {len(left_out)} sources left out ({(OUT / 'left-out.txt').relative_to(C.ROOT).as_posix()})")


if __name__ == "__main__":
    main()
