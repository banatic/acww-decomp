"""Join sources of one function each into a unit: one file of several functions, as the original
source file held them (common.UNIT_HEADER).

    python tools/regroup.py <module> <unit> FILE...    # writes src/<module>/<unit>.c(pp)

The functions go in the original file's order, the last address first (mwccarm writes a file's
functions into its object last first, and the linker keeps the object's order). Each file's
`#include` lines move to the top, and an `extern` declaration that several files share is kept
once, at the top; whatever else a file declares stays before its function. A unit function
named above its definition (a call to a lower address) gets a prototype, copied from the
definition, above all the bodies: gcc 14 and later refuse an implicit declaration even with -w,
and tools/lint.py checks for it. The files are removed. Two files that declare one name differently, or define the same type or helper, do not
compile together: those are listed, and are for the person regrouping to settle (one type for
both, a cast at a call) before tools/verify.py, tools/link.py and tools/lint.py pass.

All the files must share the compiler, its options, ARM or Thumb, and C or C++.
"""

from __future__ import annotations

import collections
import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

EXTERN = re.compile(r"^extern\b[^;{]*;\n(?:[ \t]+[^\n]*;\n)?", re.M)  # one, maybe wrapped once


def declared_name(decl: str) -> str | None:
    """The name an extern declaration declares (a function's or an object's)."""
    head = decl.split("(", 1)[0] if "(" in decl.split("=", 1)[0] else decl
    m = re.search(r"(\w+)\s*(?:\[[^\]]*\]\s*)*;?\s*$", head.strip().rstrip(";"))
    return m.group(1) if m else None


def regroup(module: str, unit: str, paths: list[pathlib.Path]) -> tuple[pathlib.Path, list[str]]:
    srcs = []
    for p in paths:
        found = C.parse_sources(p)
        if len(found) != 1 or found[0].module != module:
            raise SystemExit(f"{p}: not a source of one function of {module}")
        srcs.append(found[0])
    kinds = {(s.drop, s.opt, s.thumb, s.lang) for s in srcs}
    if len(kinds) != 1:
        raise SystemExit(f"the files are compiled differently: {sorted(kinds)}")
    srcs.sort(key=lambda s: s.address, reverse=True)
    first = srcs[0]
    head = [f"/* {unit}: {len(srcs)} functions, module {module}", f" * mwccarm {first.drop} {first.opt}"]
    head += [f" * {s.name} @ 0x{s.address:08x}, 0x{s.size:x} bytes, {'Thumb' if s.thumb else 'ARM'}"
             + (f", emits {s.emitted}" if s.emitted else "") for s in srcs]
    head.append(" */")
    includes, bodies = [], []
    externs: collections.Counter = collections.Counter()
    for s in srcs:
        text = s.path.read_text(encoding="utf-8")
        body = text[C.header_end(text):]
        for inc in re.findall(r"^#\s*include[^\n]*\n", body, re.M):
            if inc not in includes:
                includes.append(inc)
        body = re.sub(r"^#\s*include[^\n]*\n", "", body, flags=re.M)
        externs.update(set(EXTERN.findall(body)))
        bodies.append(body)
    shared = [d for d in externs if externs[d] > 1]
    out = "\n".join(head) + "\n"
    if includes:
        out += "\n" + "".join(includes)
    if shared:
        out += "\n" + "".join(sorted(shared, key=lambda d: (declared_name(d) or "", d)))
    joined = ""
    for body in bodies:
        for d in shared:
            body = body.replace(d, "")
        joined += "\n" + re.sub(r"\n{3,}", "\n\n", body).strip("\n") + "\n"
    # a function the unit defines below a use of it (the order is last address first) gets a
    # prototype above all the bodies, copied from its definition: C99 has no implicit
    # declarations, and gcc 14 and later refuse them even with -w
    problems = []
    protos = []
    typedefs = set(re.findall(r"^typedef\b[^;]*?\b(\w+)\s*;", joined, re.M | re.S))
    for name in C.undeclared_uses(joined, [s.name for s in srcs]):
        m = C.unit_definition(joined, name)
        if m is None:
            problems.append(f"{name} is used before it is declared and has no definition to copy")
            continue
        proto = " ".join(m.group(0).rstrip("{").split()) + ";"
        protos.append(proto + "\n")
        problems += [f"the prototype of {name} uses {t}, defined further down: move the type up"
                     for t in sorted(typedefs & set(re.findall(r"\w+", proto)))]
    if protos:
        out += "\n" + "".join(protos)
    out += joined
    # what cannot compile together: one name declared two ways, a type or helper defined twice
    seen: dict[str, set[str]] = collections.defaultdict(set)
    for d in externs:
        name = declared_name(d)
        if name:
            seen[name].add(" ".join(d.split()))
    problems += [f"{n} is declared {len(v)} ways" for n, v in sorted(seen.items()) if len(v) > 1]
    names = collections.Counter(n for b in bodies for n in set(re.findall(
        r"^(?:typedef\s+struct\s+\w*\s*\{[^}]*\}\s*(\w+)\s*;|static\s[^;{(]*?\b(\w+)\s*\()", b, re.M | re.S)))
    problems += [f"{a or b} is defined in {k} of the files" for (a, b), k in sorted(names.items()) if k > 1]
    dest = C.SRC / module / f"{unit}{first.path.suffix}"
    if dest.exists():
        raise SystemExit(f"{dest} exists")
    dest.write_text(out, encoding="utf-8", newline="\n")
    for s in srcs:
        s.path.unlink()
    return dest, problems


def main() -> None:
    if len(sys.argv) < 5:
        raise SystemExit(__doc__)
    module, unit = sys.argv[1], sys.argv[2]
    dest, problems = regroup(module, unit, [pathlib.Path(a).resolve() for a in sys.argv[3:]])
    print(f"wrote {dest.relative_to(C.ROOT).as_posix()}")
    for p in problems:
        print(f"  to settle: {p}")


if __name__ == "__main__":
    main()
