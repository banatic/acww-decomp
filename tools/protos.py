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
    words = [w for w in ret.replace("*", " * ").split() if w not in ("extern", "static", "inline", "asm")]
    return not (words == ["void"])


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
        text = COMMENT.sub(" ", path.read_text(encoding="utf-8", errors="replace"))
        # a file's own static functions are its business, whatever other files name theirs
        local = {m.group(2) for m in FUNC.finditer(text) if "static" in m.group(1).split()}
        for m in FUNC.finditer(text):
            ret, name, ps, end = m.group(1), m.group(2), m.group(3), m.group(4)
            if STATEMENT & set(ret.replace("*", " ").split()) or name in local:
                continue
            entry = (params(ps), returns(ret))
            if end == "{":
                (defs if game else library)[name] = (*entry, rel)
            elif game:
                decls.append((rel, name, *entry))
    if library:
        LIBRARY.write_text("".join(f"{name} {-1 if n is None else n} {int(ret)}\n"
                                   for name, (n, ret, _) in sorted(library.items())), newline="\n")
    elif LIBRARY.exists():
        for line in LIBRARY.read_text().splitlines():
            name, n, ret = line.split()
            library[name] = (None if n == "-1" else int(n), ret == "1", "libs")
    for name, entry in library.items():
        defs.setdefault(name, entry)
    out = []
    for rel, name, n, ret in decls:
        if name not in defs:
            continue
        dn, dret, drel = defs[name]
        if (n is not None and dn is not None and n != dn) or ret != dret:
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
