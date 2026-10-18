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
import native_layout  # noqa: E402
import native_pmf  # noqa: E402
import native_virtual  # noqa: E402
import native_profile  # noqa: E402
import native_stack  # noqa: E402
import native_publish  # noqa: E402

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
              "strncmp", "strncpy", "__udivdi3", "__umoddi3", "__divdi3", "__moddi3", "_alloca",
              "native_guest_stack_slot", "native_publish_word"}

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
    # Separate functions so the assembler keeps inter-function branches as
    # relocations, including tail jumps that must go through Native wrappers.
    pic += ["-fno-stack-protector", "-ffunction-sections"]
    # structures as the DS lays them out (runtime/native.h): GCC's bit-fields on Windows too
    layout = ["-mno-ms-bitfields"] if WINDOWS else []
    relax = RELAX if "clang" in " ".join(compiler()) else []  # gcc only warns about these
    # Locals the source leaves uninitialized hold what the stack held before. The ROM's code
    # can pass such bytes on into the game's memory (a structure filled in part and copied);
    # the PC's stack holds other leftovers than the DS's, which no Native can match. Filled with
    # a pattern (0xff bytes from clang for a 32-bit target, 0xfe from gcc), they read the same
    # on every run, and the memory comparison (runtime/native_run.c, compare_with_reference)
    # counts a word whose differing bytes are all the pattern's apart from the game's values.
    uninit = ["-ftrivial-auto-var-init=pattern"]
    return [*lang, *pic, *layout, "-O2", "-w", *relax, *uninit, "-fwrapv", "-fno-strict-aliasing", "-fno-exceptions",
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


def code_references(obj: pathlib.Path) -> set[str]:
    """The names an object's code refers to (not its data: a vtable the PC's compiler emits
    with the class's key function lists the bases' methods, but Native code installs the
    ROM's vtable, and the PC's copy is never read)."""
    tool = str(LLVM / "llvm-objdump.exe") if WINDOWS else "objdump"
    out = subprocess.run([tool, "-r", str(obj)], capture_output=True, text=True).stdout
    names, code = set(), False
    for line in out.splitlines():
        m = re.match(r"RELOCATION RECORDS FOR \[(.*)\]:", line)
        if m:
            code = m.group(1).startswith(".text")
            continue
        parts = line.split()
        if code and len(parts) >= 3 and re.match(r"[0-9a-fA-F]+$", parts[0]):
            names.add(re.sub(r"[+-]0x[0-9a-fA-F]+$", "", parts[2]))
    return names


VPROBE = re.compile(r"^_*vprobe_(\d+):\s*\n\s*\.long\s+(\S+)[^\n]*\n\s*\.long\s+(\S+)", re.M)


def probe_virtuals(path: pathlib.Path, methods: list[str]) -> dict[str, tuple[int, int]]:
    """For the methods (Itanium names) a source calls directly that are virtual, the byte
    offset of their vtable slot and the adjustment of `this`, as the PC's compiler lays the
    class out: a member-function pointer to a virtual method holds 1 + the offset."""
    tool = [str(LLVM / "llvm-cxxfilt.exe")] if WINDOWS else ["c++filt"]
    plain = subprocess.run([*tool, *methods], capture_output=True, text=True).stdout.split("\n")
    lines = [f'#include "{path.resolve().as_posix()}"']
    for i, demangled in enumerate(plain[:len(methods)]):
        name = demangled.split("(")[0].strip()
        if "::" not in name or "<" in name:
            continue
        lines.append(f"auto vprobe_{i} = &{name};")
    probe = OUT / "vprobe" / path.relative_to(C.SRC).with_suffix(path.suffix)
    probe.parent.mkdir(parents=True, exist_ok=True)
    probe.write_text("\n".join(lines) + "\n")
    asm = probe.with_suffix(".s")
    p = subprocess.run([*compiler(), "-S", *flags_for(path), str(probe), "-o", str(asm)], capture_output=True,
                       text=True)
    if p.returncode != 0:
        return {}
    out = {}
    for i, ptr, adjust in VPROBE.findall(asm.read_text()):
        if re.fullmatch(r"-?\d+", ptr) and int(ptr) & 1 and re.fullmatch(r"-?\d+", adjust):
            out[methods[int(i)]] = (int(ptr) - 1, int(adjust))
    return out


def virtual_calls(objects: list[tuple[pathlib.Path, pathlib.Path]], nowhere: set[str]) -> dict[str, tuple[int, int]]:
    """The names without an address (`nowhere`, as the objects name them) that are virtual
    methods the sources call directly, with their vtable offset and `this` adjustment
    (probe_virtuals). A name the sources lay out in more than one way is left out, and so is
    any source with a virtual destructor in sight: mwccarm gives it one slot, the PC two."""
    work = []
    for path, obj in objects:
        refs = sorted(code_references(obj) & nowhere)
        methods = [r[len(PREFIX):] for r in refs if r[len(PREFIX):].startswith("_ZN")]
        if not methods:
            continue
        texts = [path.read_text(encoding="utf-8", errors="replace")]
        texts += [h.read_text(encoding="utf-8", errors="replace") for h in C.included_files(path)]
        if any(re.search(r"\bvirtual\s+~", COMMENT.sub(" ", t)) for t in texts):
            continue
        work.append((path, methods))
    found: dict[str, set[tuple[int, int]]] = collections.defaultdict(set)
    with cf.ThreadPoolExecutor(max(1, (os.cpu_count() or 4) - 2)) as pool:
        for (path, methods), slots in zip(work, pool.map(lambda w: probe_virtuals(*w), work)):
            for m in methods:
                found[m].add(slots.get(m, (-1, 0)))
    return {PREFIX + m: next(iter(v)) for m, v in found.items() if len(v) == 1 and next(iter(v))[0] >= 0}


def virtual_thunks(vcalls: dict[str, tuple[int, int]]) -> list[str]:
    """Dispatch unresolved virtual calls with cdecl this on the stack."""
    lines = []
    for host, (offset, adjust) in sorted(vcalls.items()):
        lines += ["\t.p2align 4", f"\t.globl {host}", f"{host}:", "\tmovl 4(%esp), %eax"]
        if adjust:
            lines += [f"\taddl ${adjust}, %eax", "\tmovl %eax, 4(%esp)"]
        lines += ["\tmovl (%eax), %eax", f"\tjmp *{offset}(%eax)"]
    return lines


# The functions each source declares with a narrower result than their definitions
# (protos.narrowed_results), filled by main(): the source is compiled from a copy with those
# declarations returning int (protos.widen_declarations), so that the PC's caller goes on with
# the whole of eax as the ROM's goes on with the whole of r0.
NARROWED: dict[pathlib.Path, set[str]] = {}
WIDENED: dict[pathlib.Path, set[str]] = {}
PMF_TRANSLATED: set[pathlib.Path] = set()


def compile_one(path: pathlib.Path) -> tuple[pathlib.Path, pathlib.Path | None, str]:
    flags = flags_for(path)
    obj = OUT / "obj" / path.relative_to(C.SRC).with_suffix(".o")
    source, text = path, path.read_bytes()
    relative = path.relative_to(C.SRC).as_posix()
    layout = native_layout.translate(relative, text.decode("utf-8")) if relative in native_layout.paths() else None
    member = native_pmf.translate(relative, text.decode("utf-8")) if relative in native_pmf.paths() else None
    virtual = native_virtual.translate(relative, text.decode("utf-8")) if relative in native_virtual.paths() else None
    stack = native_stack.translate(relative, text.decode("utf-8")) if relative in native_stack.paths() else None
    publish = native_publish.translate(relative, text.decode("utf-8")) if relative in native_publish.paths() else None
    copies = [copy for copy in (layout, member, virtual, stack, publish) if copy is not None]
    if len(copies) > 1:
        raise ValueError(f"Overlapping Native source-copy transforms: {relative}")
    if NARROWED.get(path) or copies:
        wide = copies[0] if copies else text.decode("utf-8")
        if member is not None:
            PMF_TRANSLATED.add(path)
        if member is not None or stack is not None or publish is not None:
            flags = [*flags, "-I" + str(C.ROOT / "runtime")]
        if NARROWED.get(path):
            wide, done = protos.widen_declarations(wide, NARROWED[path])
            WIDENED[path] = done
        # the copy finds the original's neighbours (#include "...") and names the original
        source = OUT / "wide" / path.relative_to(C.SRC)
        text = f'#line 1 "{path.as_posix()}"\n{wide}'.encode()
        flags = [*flags, "-iquote", str(path.parent)]
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_bytes(text)
    key = hashlib.sha1(text + " ".join(compiler() + flags).encode())
    key.update((C.ROOT / "runtime" / "native.h").read_bytes())  # included first, by -include
    if member is not None:
        key.update((C.ROOT / "runtime" / "native_member.h").read_bytes())
    if stack is not None:
        key.update((C.ROOT / "runtime" / "native_guest.h").read_bytes())
    if publish is not None:
        key.update((C.ROOT / "runtime" / "native_publish.h").read_bytes())
    for inc in C.included_files(path):
        key.update(inc.read_bytes())
    stamp = obj.with_suffix(".key")
    if obj.exists() and stamp.exists() and stamp.read_text() == key.hexdigest():
        return path, obj, ""
    obj.parent.mkdir(parents=True, exist_ok=True)
    p = subprocess.run([*compiler(), "-c", *flags, str(source), "-o", str(obj)], capture_output=True,
                       text=True, errors="replace")
    if p.returncode != 0:
        first = next((line for line in p.stderr.splitlines() if "error" in line), p.stderr.strip()[-200:])
        return path, None, first.split("error:", 1)[-1].strip()
    stamp.write_text(key.hexdigest())
    return path, obj, ""


def rewrite_one(obj: pathlib.Path, known: set[str], native: set[str], names_key: str,
                pmf: set[str] = frozenset()) -> tuple[pathlib.Path, set[str]]:
    """The object with its references pointed at the game's memory, and the names it now
    refers to by their DS address (cached by the object's content and by the sets of names:
    a call goes to another Native function only while that one compiles). With `pmf`, its
    tables of member-function pointers go through native_pmf_ jumps (tools/objrewrite.py)."""
    data = obj.read_bytes()
    out = OUT / "linked" / obj.relative_to(OUT / "obj")
    stamp = out.with_suffix(".names")
    key = hashlib.sha1(data + names_key.encode() + (b"pmf" if pmf else b"")).hexdigest()
    if out.exists() and stamp.exists() and stamp.read_text().startswith(key):
        return out, set(stamp.read_text().split()[1:])
    new, names = objrewrite.rewrite(data, known, native, PREFIX, pmf)
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


# what a table of member-function pointers that only Native code builds may hold
PMF_METHOD = re.compile(r"&\s*(?:\w+\s*::\s*)+(\w+)")
PMF_CONSTANT = re.compile(r"(?:\(\s*\w+\s*\)\s*)?&\s*(?:\w+\s*::\s*)+\w+|-?\b(?:0x[0-9a-fA-F]+|\d+)\b|\bNULL\b|[{},\s\\]")
CALL_KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof"}


def _statement_start(text: str, pos: int) -> int:
    return max(text.rfind(";", 0, pos), text.rfind("{", 0, pos), text.rfind("}", 0, pos)) + 1


def _open(text: str, pos: int, start: int, opening: str, closing: str) -> int:
    """The position of the innermost `opening` still open at `pos` (looking back to `start`),
    or -1."""
    depth = 0
    for i in range(pos - 1, start - 1, -1):
        if text[i] == closing:
            depth += 1
        elif text[i] == opening:
            if depth == 0:
                return i
            depth -= 1
    return -1


def _typedefs(text: str) -> set[str]:
    out = set()
    for m in PMF_TYPEDEF.finditer(text):
        if re.search(r"\btypedef\b", text[_statement_start(text, m.start()):m.start()]):
            out.add(m.group(1))
    return out


def _is_argument(text: str, pos: int) -> bool:
    """Whether the expression at `pos` is an argument of a call, or part of one."""
    start = _statement_start(text, pos)
    paren = _open(text, pos, start, "(", ")")
    while paren >= 0:
        head = text[start:paren]
        m = re.search(r"(\w+)\s*$", head)
        if (m and m.group(1) not in CALL_KEYWORDS) or re.search(r"\)\s*$", head):
            return True
        paren = _open(text, paren, start, "(", ")")
    return False


def _in_static_initializer(text: str, pos: int) -> bool:
    stmt = _statement_start(text, pos)
    if re.search(r"\bstatic\b[^;]*=", text[stmt:pos]):
        return True
    brace = _open(text, pos, 0, "{", "}")
    return brace >= 0 and bool(re.search(r"\bstatic\b[^;]*=\s*$", text[_statement_start(text, brace):brace]))


def expand_macros(text: str) -> str:
    """`text` with its own macros expanded (a table written with a macro per entry, or as one
    macro)."""
    text = re.sub(r"\[ \t]*\n", " ", text)
    define = re.compile(r"^[ \t]*#\s*define[ \t]+(\w+)(\([^)]*\))?[ \t]+(.+)$", re.M)
    macros = [(m.group(1), m.group(2), m.group(3)) for m in define.finditer(text)]
    text = define.sub("", text)
    for name, params, body in macros:
        if params is None:
            text = re.sub(r"\b" + re.escape(name) + r"\b", lambda _, body=body: body, text)
            continue

        def subst(call: re.Match, params=[p.strip() for p in params[1:-1].split(",")], body=body) -> str:
            out = body
            for p, a in zip(params, (a.strip() for a in call.group(1).split(","))):
                out = re.sub(r"\b" + re.escape(p) + r"\b", lambda _, a=a: a, out)
            return out
        text = re.sub(r"\b" + re.escape(name) + r"\s*\(([^()]*)\)", subst, text)
    return text


def _constant_table(text: str, pos: int) -> bool:
    """Whether the declaration at `pos` is static and initialized with constants."""
    stmt = _statement_start(text, pos)
    if not re.search(r"\bstatic\b", text[stmt:pos]):
        return False
    depth, i = 0, pos
    while i < len(text) and not (text[i] == ";" and depth == 0):
        depth += text[i] == "{"
        depth -= text[i] == "}"
        i += 1
    init = text[pos:i]
    return "=" in init and not PMF_CONSTANT.sub("", init.split("=", 1)[1]).strip()


def _private_structure(text: str, brace: int, head: str, tables: set[str]) -> str | None:
    """Why the structure whose body opens at `brace` may hold data the ROM's code shares, or
    None when it is only the type of static tables of constants, which `tables` gets."""
    close = brace
    depth = 0
    for close in range(brace, len(text)):
        depth += text[close] == "{"
        depth -= text[close] == "}"
        if depth == 0:
            break
    tag = re.search(r"\b(?:struct|class|union)\s+(\w+)", head)
    after = re.match(r"\s*(\w+)", text[close + 1:])
    if re.search(r"\btypedef\b", head) and after:
        tag = after
    elif not tag:  # declared with its definition: `static struct { ... } tbl = { ... };`
        if not after or not _constant_table(text, close + 1 + after.start(1)) or \
                not re.search(r"\bstatic\b", head):
            return "a structure the ROM's code may share"
        tables.add(after.group(1))
        return None
    name = tag.group(1)
    for m in re.finditer(r"\b" + re.escape(name) + r"\b", text):
        if brace > m.start() >= _statement_start(text, brace) or close < m.start() <= close + 1 + (after.end() if after else 0):
            continue  # the definition
        rest = text[m.end():]
        if re.search(r"sizeof\s*\(\s*(?:struct\s+)?$", text[:m.start()]):
            continue
        d = re.match(r"\s*(\w+)\s*\[?", rest)
        if d and _constant_table(text, m.end() + d.start(1)):
            tables.add(d.group(1))
            continue
        if re.match(r"\s*\*\s*\)\s*\(\s*\(\s*char\s*\*\s*\)\s*(\w+)", rest):
            continue  # an entry of a table, found by its offset (checked below)
        if re.search(r"\btypedef\s+(?:struct|class|union)\s+$", text[:m.start()]) and \
                re.match(r"\s+" + re.escape(name) + r"\s*;", rest):
            continue
        return f"{name} used elsewhere"
    return None


def pmf_unsafe(path: pathlib.Path, text: str) -> str | None:
    """Why the member-function pointers `text` (a source's text, comments removed) uses cannot
    work as Native, or None when they can. mwccarm lays one out in 12 bytes, the PC (Itanium
    C++ ABI) in 8 with another encoding, so the PC's code can only use the ones it builds and
    reads itself: a static table (in the function or the file) of `&Class::method` constants,
    and locals filled from it. Whatever shares one with the ROM's code breaks: a parameter or
    a result, an argument passed on, a structure field (whose structure changes layout too),
    data the ROM has (`extern`, or a global at its DS address), a cast, a pointer to one. A
    virtual method in a table is left out too: its entry is a vtable offset, which the PC
    counts with its own slots."""
    headers = [COMMENT.sub(" ", h.read_text(encoding="utf-8", errors="replace")) for h in C.included_files(path)]
    text = expand_macros(text)
    types = set(_typedefs(text))
    for h in headers:
        types |= {t for t in _typedefs(h) if re.search(r"\b" + re.escape(t) + r"\b", text)}
    declared = []  # (name, position of the name, a pointer or reference to one)
    for m in PMF_TYPEDEF.finditer(text):
        if m.group(1) not in types:
            declared.append((m.group(1), m.start(1), False))
    for m in re.finditer(r"\(\s*(?:\w+\s*::\s*)+\*\s*(?:const\s+)?(\w+)\s*\[", text):  # `(Obj::*tbl[2])()`
        declared.append((m.group(1), m.start(1), False))
    for t in types:
        for m in re.finditer(r"\b" + re.escape(t) + r"\b", text):
            stmt = _statement_start(text, m.start())
            if re.search(r"\btypedef\b", text[stmt:m.start()]) and re.search(r"::\s*\*\s*$", text[stmt:m.start()]):
                continue  # the typedef itself
            after = text[m.end():]
            if re.match(r"\s*::", after):
                continue
            if re.match(r"\s*(?:const\s*)?[*&\s]*[)>]", after):
                if re.match(r"\s*\)\s*" + PMF_METHOD.pattern, after) and _in_static_initializer(text, m.start()):
                    continue  # a constant of a table, cast to the table's type
                return f"a cast to {t}"
            d = re.match(r"\s*(?:const\s+)?([*&]*)\s*(?:const\s+)?(\w+)", after)
            if not d:
                return f"{t} where no declaration is"
            declared.append((d.group(2), m.end() + d.start(2), bool(d.group(1))))
    tables, locals_ = set(), set()
    for name, pos, indirect in declared:
        stmt = _statement_start(text, pos)
        before = text[stmt:pos]
        if indirect:
            return f"{name}, a pointer or reference to a member-function pointer"
        if _open(text, pos, stmt, "(", ")") >= 0 and not re.search(r"::\s*\*\s*(?:const\s+)?$", before):
            return f"{name}, a member-function pointer parameter"
        if re.match(r"\s*\)?\s*\(", text[pos + len(name):]) and re.search(r"::\s*\*\s*(?:const\s+)?$", before) is None:
            return f"{name}, which returns a member-function pointer"
        if re.search(r"::\s*\*\s*(?:const\s+)?$", before) and _open(text, pos, stmt, "(", ")") >= 0:
            # a declarator in parentheses: a parameter when another parenthesis is open around it
            inner = _open(text, pos, stmt, "(", ")")
            if _open(text, inner, stmt, "(", ")") >= 0:
                return f"{name}, a member-function pointer parameter"
        brace = _open(text, pos, 0, "{", "}")
        head = text[_statement_start(text, brace):brace] if brace >= 0 else ""
        if re.search(r"\b(?:struct|class|union)\b[^;{}()]*$", head):
            # a field: only of a structure that is the type of static tables alone
            why = _private_structure(text, brace, head, tables)
            if why:
                return f"{name}, a structure field ({why})"
            continue
        if re.search(r"\bextern\b", before):
            return f"{name}, data the ROM has"
        static = re.search(r"\bstatic\b", before)
        if not static and brace < 0:
            return f"{name}, a global the ROM has"
        if static:
            end = text.find(";", pos)
            init = text[pos + len(name):end]
            if "=" in init:
                value = init.split("=", 1)[1]
                if PMF_CONSTANT.sub("", value).strip():
                    return f"{name}, a table filled from elsewhere"
                for method in PMF_METHOD.findall(value):
                    if any(re.search(r"\bvirtual\b[^;{}]*\b" + re.escape(method) + r"\s*\(", b) for b in [text, *headers]):
                        return f"{name}, a table with the virtual method {method}"
            tables.add(name)
        else:
            locals_.add(name)
    if not tables:
        return "no table of its own"
    # a constant outside a table's initializer
    for m in PMF_METHOD.finditer(text):
        stmt = _statement_start(text, m.start())
        brace = _open(text, m.start(), 0, "{", "}")
        if not re.search(r"\bstatic\b", text[stmt:m.start()]) and \
                not (brace >= 0 and re.search(r"\bstatic\b", text[_statement_start(text, brace):brace])):
            return f"{m.group(0)} outside a table"
    # each table or local is only indexed, called through, assigned to a local or tested
    at = {pos for _, pos, _ in declared}
    for name in tables | locals_:
        for m in re.finditer(r"\b" + re.escape(name) + r"\b", text):
            if m.start() in at:
                continue
            stmt = _statement_start(text, m.start())
            if _is_argument(text, m.start()):
                return f"{name} passed to a call"
            target = re.search(r"([\w\]\)>.-]+)\s*=\s*$", text[stmt:m.start()])
            if target and not re.fullmatch(r"\w+", target.group(1)) or \
                    target and target.group(1) not in locals_ | tables:
                return f"{name} stored to {target.group(1)}"
            if re.search(r"\breturn\b", text[stmt:m.start()]) and not re.search(r"->\*|\.\*", text[stmt:m.end() + 4]):
                return f"{name} returned"
    return None


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
    narrowed: dict[str, set[str]] = collections.defaultdict(set)
    for rel, callee in protos.narrowed_results():
        narrowed[rel].add(callee)
    NARROWED.update({p: narrowed[p.relative_to(C.ROOT).as_posix()] for p in paths
                     if p.relative_to(C.ROOT).as_posix() in narrowed})
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
    profile_names = {C.parse_source(path).object_symbol for path, _ in objects} & native
    objrewrite.BODY = profile_names
    names_key = hashlib.sha1(" ".join(sorted(native) + ["|"] + sorted(known) + ["|"] + sorted(profile_names)).encode()
                             + pathlib.Path(objrewrite.__file__).read_bytes()).hexdigest()
    # Sources whose member-function pointers only Native code builds and reads (pmf_unsafe):
    # their tables refer to the methods through native_pmf_ jumps at even addresses.
    pmf_why: dict[pathlib.Path, str | None] = {}
    for path, _ in objects:
        text = COMMENT.sub(" ", path.read_text(encoding="utf-8", errors="replace"))
        if "::*" in text or "->*" in text or pmf_names(path, text):
            pmf_why[path] = None if path in PMF_TRANSLATED else pmf_unsafe(path, text)
    methods = {n for n in known if n.startswith("_ZN")
               and any(s.kind == "function" for s in syms.by_name.get(n, []))}
    to_ds: set[str] = set()
    rewritten = []
    with cf.ThreadPoolExecutor(workers) as pool:
        work = [(po, methods if po[0] in pmf_why and pmf_why[po[0]] is None else frozenset()) for po in objects]
        for (path, _), (obj, names) in zip(objects, pool.map(lambda w: rewrite_one(w[0][1], known, native, names_key,
                                                                                   w[1]), work)):
            rewritten.append((path, obj))
            to_ds |= names
    objects = rewritten
    thunks = sorted(n for n in to_ds if n.startswith(objrewrite.PMF))
    to_ds -= set(thunks)
    to_ds |= {n[len(objrewrite.PMF):] for n in thunks if n[len(objrewrite.PMF):] not in native}
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
    # A virtual method the PC's compiler calls directly (the object's type is known to it) has
    # no address of its own; the ROM's code calls it through the object's vtable. Such a name
    # becomes a jump through the object's vtable, at the slot the PC's compiler counts for it.
    vcalls = virtual_calls(objects, {h for h, a in absolute if a == 0})
    absolute = [(h, a) for h, a in absolute if h not in vcalls]
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
    profile_ids = {}
    for path, _ in objects:
        src = C.parse_source(path)
        host = PREFIX + (objrewrite.NATIVE if src.object_symbol in known else "") + src.object_symbol
        if host not in defined:
            continue
        kind, params, member, floating = signature(path, src.name)
        info = (kind | (min(params, 15) << 4) | (int(member) << 8) | (floating << 9)
                | (modules.index(src.module) << 16))
        lines.append(f"\t.long 0x{src.address | (1 if src.thumb else 0):08x}, 0x{src.size:x}, {host}, 0x{info:08x}")
        if src.object_symbol in profile_names:
            assert src.object_symbol not in profile_ids, src.object_symbol
            profile_ids[src.object_symbol] = count
        count += 1
    assert set(profile_ids) == profile_names
    lines += [f"\t.globl {PREFIX}native_function_count", f"{PREFIX}native_function_count:", f"\t.long {count}"]

    # Public entries observe calls when hooks are installed, and preserve the
    # existing narrow-result ABI even when the hooks are disabled.
    lines += ["\t.text"]
    # the jumps the tables of member-function pointers hold (tools/objrewrite.py), at even
    # addresses: to the method's Native, or to its DS address (the ROM's code)
    # the virtual calls (virtual_calls): `this` is the first word on the stack (cdecl)
    lines += virtual_thunks(vcalls)
    for thunk in thunks:
        method = thunk[len(objrewrite.PMF):]
        target = PREFIX + (objrewrite.NATIVE if method in native else "") + method
        lines += ["\t.p2align 4", f"\t.globl {PREFIX}{thunk}", f"{PREFIX}{thunk}:", f"\tjmp {target}"]
    for name, index in sorted(profile_ids.items()):
        lines += native_profile.wrapper(name, index, PREFIX, widen.get(name))
    lines += ["\t.data"]
    # each body with its wrapper, so the runtime can name the function a fault in a body is in
    lines += [f"\t.globl {PREFIX}native_bodies", f"{PREFIX}native_bodies:"]
    lines += [f"\t.long {PREFIX}{objrewrite.NATIVE}body_{name}, {PREFIX}{objrewrite.NATIVE}{name}"
              for name in sorted(profile_ids)] or ["\t.long 0, 0"]
    lines += [f"\t.globl {PREFIX}native_body_count", f"{PREFIX}native_body_count:", f"\t.long {len(profile_ids)}"]

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
    # A caller that declares a function with a char or short result the definition does not
    # produce (protos.narrowed_results): mwccarm trusts the callee to have extended r0 as
    # declared, so the ROM's code goes on with the whole register (returns it, compares it, adds
    # an offset to it). The source was compiled with those declarations returning int
    # (compile_one), so the PC's code goes on with the whole of eax; one whose declaration
    # protos.widen_declarations could not change stays Reference.
    keep = []
    for (path, _), names in zip(objects, per_object):
        name = C.parse_source(path).object_symbol
        vts = sorted({n[strip:] for n in names if n[strip:].startswith("_ZTV") and n[strip:] not in vtables})
        zero = sorted(n[strip:] for n in code_references(_) & nowhere) if names & nowhere else []
        text = COMMENT.sub(" ", path.read_text(encoding="utf-8", errors="replace"))
        by_value = struct_results(text)
        if "__MWERKS__" in text and ASM_FUNCTION.search(text):
            keep.append(f"{name} matches as assembly (`asm`, under #ifdef __MWERKS__); its C version for the PC "
                        "is a rewrite, and passes registers on differently" + chr(10))
            continue
        inner = sorted(set(re.findall(r"\b(\w+_unk)\s*\(", text)) - {name})
        narrow = sorted(NARROWED.get(path, set()) - WIDENED.get(path, set()))
        if inner:
            keep.append(f"{name} calls {' '.join(inner)}, an entry into the middle of other code: the ROM's code "
                        "there goes on into a function whose Native would not start there" + chr(10))
        elif narrow:
            keep.append(f"{name} declares {' '.join(narrow)} with a narrower result than the definition returns, in a "
                        "declaration not widened for the PC: the ROM's code uses the whole register the callee "
                        "leaves, the PC's only the low bits\n")
        elif by_value:
            keep.append(f"{name} calls {' '.join(by_value)}, which returns a structure by value: mwccarm passes "
                        "a pointer to the result in r0, the PC's compiler returns a small one in registers\n")
        elif pmf_why.get(path):
            keep.append(f"{name} shares member-function pointers with the ROM's code ({pmf_why[path]}), which "
                        "uses a different encoding from the PC's Itanium C++ ABI\n")
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
