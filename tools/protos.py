"""Compare every function declaration in the sources with the function's definition.

    python tools/protos.py          # summary; the full list in build/adm-kr/protos.txt

On the DS a call through a wrong prototype often still works, because the arguments a caller
forgot are left in the registers. Compiled for the PC (docs/runtime.md, M2) it does not, so
every declaration must agree with its definition: the number of parameters, and whether the
function returns a value.
"""

from __future__ import annotations

import collections
import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
# `<return type> name(params)` followed by `;` (declaration) or `{` (definition), at top level
FUNC = re.compile(r"(?:^|[;}])\s*((?:\w+[\s\*]+)+)([A-Za-z_]\w*)\s*"
                  r"\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*([;{])", re.M)
# a statement that calls the function, not a declaration of it
STATEMENT = {"return", "else", "case", "do", "goto", "sizeof"}
# The library functions' signatures (name, parameter count or -1, 1 when it returns a value),
# for a checkout without the library sources (libs/README.md).
LIBRARY = C.ROOT / "runtime" / "library-signatures.txt"


def params(text: str) -> int | None:
    text = " ".join(text.split())
    if text in ("", "void"):
        return 0
    if "..." in text:
        return None
    depth, n = 0, 1
    for ch in text:
        depth += ch == "("
        depth -= ch == ")"
        n += ch == "," and depth == 0
    return n


def returns(ret: str) -> bool:
    words = [w for w in ret.replace("*", " * ").split() if w not in ("extern", "static", "inline", "asm", "virtual", "__arm", "__thumb")]
    return not (words == ["void"])


# `extern "C"` in a C++ source: what it marks is a C function of the game, read as if the
# source said `extern` (the "C" becomes spaces, so offsets stay)
LINKAGE = re.compile(r'(?<=\bextern)(\s*)"C"')


def plain_linkage(text: str) -> str:
    return LINKAGE.sub(lambda m: m.group(1) + "   ", text)


CLASS_BODY = re.compile(r"\b(?:class|struct|union)\b[^;{}()=]*\{")


def class_bodies(text: str) -> list[tuple[int, int]]:
    """The spans of the class, struct and union bodies in `text`: what is declared there is a
    member, not the function of that name elsewhere."""
    spans = []
    for m in CLASS_BODY.finditer(text):
        depth, i = 1, m.end()
        while i < len(text) and depth:
            depth += {"{": 1, "}": -1}.get(text[i], 0)
            i += 1
        spans.append((m.end(), i))
    return spans


NARROW_RESULTS = {("unsigned", "char"): (1, False), ("u8",): (1, False), ("char",): (1, True),
                  ("signed", "char"): (1, True), ("s8",): (1, True), ("unsigned", "short"): (2, False),
                  ("unsigned", "short", "int"): (2, False), ("u16",): (2, False), ("short",): (2, True),
                  ("short", "int"): (2, True), ("signed", "short"): (2, True), ("s16",): (2, True)}


def result_width(ret: str) -> tuple[int, bool] | None:
    """(bytes, signed) of a char or short result, (4, False) for a word-sized one (an int, a
    long, a pointer), None for anything else (void, floating point, 64 bits, structures)."""
    words = [w for w in ret.replace("*", " * ").split()
             if w not in ("extern", "static", "inline", "const", "volatile", "virtual", "__arm", "__thumb")]
    if "*" in words:
        return 4, False
    if tuple(words) in NARROW_RESULTS:
        return NARROW_RESULTS[tuple(words)]
    if words in (["int"], ["unsigned"], ["unsigned", "int"], ["signed"], ["signed", "int"], ["long"],
                 ["unsigned", "long"], ["long", "int"], ["unsigned", "long", "int"], ["u32"], ["s32"], ["BOOL"]):
        return 4, False
    return None


def narrowed_results() -> list[tuple[str, str]]:
    """(declaring source, function) for each declaration of a game function with a char or
    short result that the definition does not produce: a word, or another width or sign.
    The DS's caller trusts the callee to have extended r0 as the declaration says, so it uses
    the whole register where it needs more than the narrow value; the PC's caller extends the
    low bits itself. tools/native.py compiles such a source with the declarations widened
    (widen_declarations)."""
    defs: dict[str, tuple[int, bool]] = {}
    decls: list[tuple[str, str, tuple[int, bool]]] = []
    for path in C.all_sources():
        if C.SRC not in path.parents:
            continue
        rel = path.relative_to(C.ROOT).as_posix()
        text = plain_linkage(COMMENT.sub(" ", path.read_text(encoding="utf-8", errors="replace")))
        local = {m.group(2) for m in FUNC.finditer(text) if "static" in m.group(1).split()}
        members = class_bodies(text)
        for m in FUNC.finditer(text):
            ret, name, end = m.group(1), m.group(2), m.group(4)
            if STATEMENT & set(ret.replace("*", " ").split()) or name in local or "asm" in ret.split():
                continue
            if any(start <= m.start(2) < stop for start, stop in members):
                continue
            width = result_width(ret)
            if width is None:
                continue
            if end == "{":
                defs[name] = width
            elif width[0] < 4:
                decls.append((rel, name, width))
    out = []
    for rel, name, (n, signed) in decls:
        if name not in defs:
            continue
        dn, dsigned = defs[name]
        # a narrower definition extended the same way gives the same value
        if dn < n and (not dsigned or signed) or (dn, dsigned) == (n, signed):
            continue
        out.append((rel, name))
    return out


def widen_declarations(text: str, names: set[str]) -> tuple[str, set[str]]:
    """`text` (a source) with its declarations of `names` (narrowed_results) returning int,
    and the names it changed. mwccarm trusts a char or short result to be extended already, so
    the ROM's caller goes on with r0 as the callee left it, as an int (the narrow type's
    promotion); the PC's caller, given int, goes on with eax as the callee left it, which the
    Native, Clean and Reference callees all leave as the definition's result (extended as the
    definition's type). For tools/native.py only: the DS build compiles the source as it is."""
    plain = plain_linkage(COMMENT.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text))  # same offsets
    members = class_bodies(plain)
    edits, done = [], set()
    for m in FUNC.finditer(plain):
        ret, name, end = m.group(1), m.group(2), m.group(4)
        if name not in names or end != ";" or STATEMENT & set(ret.replace("*", " ").split()):
            continue
        if any(start <= m.start(2) < stop for start, stop in members):
            continue
        width = result_width(ret)
        if width is None or width[0] >= 4:
            continue
        keep = [w for w in ret.split() if w in ("extern", "static", "inline", "const", "volatile", "__arm", "__thumb")]
        if LINKAGE.search(text[m.start(1):m.end(1)]):
            keep = ['extern "C"' if w == "extern" else w for w in keep]
        edits.append((m.start(1), m.end(1), " ".join([*keep, "int"]) + " "))
        done.add(name)
    for start, stop, new in reversed(edits):
        text = text[:start] + new + text[stop:]
    return text, done


def disagreements() -> list[tuple[str, str, int | None, int | None, bool, bool, str]]:
    """Every declaration that disagrees with its function's definition: (the declaring source,
    the function, its declared and defined parameter counts, whether it is declared and defined
    with a result, the defining source)."""
    defs: dict[str, tuple[int | None, bool, str]] = {}
    decls: list[tuple[str, str, int | None, bool]] = []
    library: dict[str, tuple[int | None, bool, str]] = {}
    for path in C.all_sources():
        game = C.SRC in path.parents
        rel = path.relative_to(C.ROOT).as_posix()
        text = plain_linkage(COMMENT.sub(" ", path.read_text(encoding="utf-8", errors="replace")))
        # a file's own static functions are its business, whatever other files name theirs
        local = {m.group(2) for m in FUNC.finditer(text) if "static" in m.group(1).split()}
        members = class_bodies(text)
        for m in FUNC.finditer(text):
            ret, name, ps, end = m.group(1), m.group(2), m.group(3), m.group(4)
            if STATEMENT & set(ret.replace("*", " ").split()) or name in local:
                continue
            if any(start <= m.start(2) < stop for start, stop in members):
                continue
            entry = (params(ps), returns(ret))
            if end == ";" and path.suffix == ".c" and not ps.strip():
                # `int f();` in C says nothing of the parameters: a call passes what it names
                entry = (None, entry[1])
            if end == "{" and "asm" in ret.split():
                # an assembly body says nothing of its parameters or result
                entry = (None, None)
            if end == "{":
                (defs if game else library)[name] = (*entry, rel)
            elif game:
                decls.append((rel, name, *entry))
    if library:
        LIBRARY.write_text("".join(f"{name} {-1 if n is None else n} {-1 if ret is None else int(ret)}\n"
                                   for name, (n, ret, _) in sorted(library.items())), newline="\n")
    elif LIBRARY.exists():
        for line in LIBRARY.read_text().splitlines():
            name, n, ret = line.split()
            library[name] = (None if n == "-1" else int(n), None if ret == "-1" else ret == "1", "libs")
    for name, entry in library.items():
        defs.setdefault(name, entry)
    out = []
    for rel, name, n, ret in decls:
        if name not in defs:
            continue
        dn, dret, drel = defs[name]
        if (n is not None and dn is not None and n != dn) or (dret is not None and ret != dret):
            out.append((rel, name, n, dn, ret, dret, drel))
    return out


def main() -> None:
    out, kinds = [], collections.Counter()
    for rel, name, n, dn, ret, dret, drel in disagreements():
        problems = []
        if n is not None and dn is not None and n != dn:
            problems.append(f"{n} parameters, the definition has {dn}")
            kinds["parameter count"] += 1
        if ret != dret:
            what = "declared with a result, defined void" if ret else "declared void, defined with a result"
            problems.append(what)
            kinds[what] += 1
        if problems:
            out.append(f"{rel}: {name}: {'; '.join(problems)} ({drel})")
    (C.BUILD / "protos.txt").write_text("\n".join(out) + "\n", newline="\n")
    files = len({line.split(":")[0] for line in out})
    print(f"{len(out)} declarations disagree with their definitions, in {files} files")
    for k, n in kinds.most_common():
        print(f"  {n:6} {k}")


if __name__ == "__main__":
    main()
