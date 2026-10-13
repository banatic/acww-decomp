"""List sources that match but do not yet read like normal code.

    python tools/quality.py --verify build/adm-kr/verify.json    # whole tree
    python tools/quality.py src/ov003 --top 40                    # a subset, 40 worst

Writes build/adm-kr/quality.json and a ranked quality-worklist.tsv; never edits a file.
Flags include placeholder names, redundant masks and arithmetic, dead branches, volatile
locals, hardcoded RAM addresses, LINK problems, unused declarations, process notes in
comments and FAKEMATCH notes.
"""

from __future__ import annotations

import argparse
import collections
import json
import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

WEIGHTS = {
    "placeholder-names": 15, "stack-names": 4, "redundant-mask": 15, "redundant-arith": 6,
    "self-assign": 10, "dup-operand": 12, "empty-if": 12, "const-if": 10,
    "same-branches": 8, "void-cast": 4, "double-cast": 2, "volatile-local": 5,
    "hardcoded-ram": 12, "bad-extern-name": 15, "local-data-differs": 20, "pasted-types": 0, "goto-heavy": 3,
    "process-notes": 6, "asm-body": 0, "fakematch": 5,
}


# ------------------------------------------------------------------------------ lexing

def split_comments(text: str) -> tuple[str, str]:
    """(code, comments): two strings the length of `text`. In `code` every comment and
    string/char literal body is blanked to spaces (newlines kept, so line numbers hold);
    `comments` holds only the comment text."""
    code, com = list(text), [" " if c != "\n" else "\n" for c in text]
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and text.startswith("/*", i):
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if text[k] != "\n":
                    com[k], code[k] = text[k], " "
            i = j
        elif c == "/" and text.startswith("//", i):
            j = text.find("\n", i)
            j = n if j < 0 else j
            for k in range(i, j):
                com[k], code[k] = text[k], " "
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and text[j] != c and text[j] != "\n":
                j += 2 if text[j] == "\\" else 1
            for k in range(i + 1, min(j, n)):
                code[k] = " "
            i = j + 1
        else:
            i += 1
    return "".join(code), "".join(com)


IDENT = re.compile(r"[A-Za-z_]\w*")
KEYWORDS = set("""auto break case char const continue default do double else enum extern float
for goto if int long register return short signed sizeof static struct switch typedef union
unsigned void volatile while inline __inline asm class public private protected virtual 
operator template typename namespace using friend""".split())


def top_level_items(code: str) -> list[tuple[int, int, str]]:
    """Split comment-free code into top-level items: (start, end, kind) where kind is
    `pp` (a preprocessor line), `func` (a definition with a body) or `decl`."""
    items, i, n = [], 0, len(code)
    while i < n:
        while i < n and code[i] in " \t\r\n":
            i += 1
        if i >= n:
            break
        opener = re.match(r'(extern\s+"[^"\n]*"|namespace(\s+\w+)?)\s*\{', code[i:i + 200])
        if opener:                      # extern "C" { / namespace {: look inside
            items.append((i, i + opener.end(), "pp"))
            i += opener.end()
            continue
        if code[i] == "}":              # ...and its closing brace
            items.append((i, i + 1, "pp"))
            i += 1
            continue
        if code[i] == "#":
            j = i
            while True:
                e = code.find("\n", j)
                e = n if e < 0 else e
                if code[j:e].rstrip().endswith("\\") and e < n:
                    j = e + 1
                    continue
                break
            items.append((i, e, "pp"))
            i = e
            continue
        depth, j, kind = 0, i, "decl"
        paren = 0
        while j < n:
            c = code[j]
            if c == "#" and depth == 0 and (j == 0 or code[j - 1] == "\n"):
                break
            if c == "(":
                paren += 1
            elif c == ")":
                paren -= 1
            elif c == "{":
                if depth == 0 and paren == 0 and re.search(r"\)\s*(const\s*)?(:[^;{}]*)?$",
                                                           code[i:j].rstrip()):
                    kind = "func"
                depth += 1
            elif c == "}":
                depth -= 1
                if depth == 0 and kind == "func":
                    j += 1
                    break
            elif c == ";" and depth == 0 and paren == 0:
                j += 1
                break
            j += 1
        items.append((i, j, kind))
        i = j
    return items


def declared_names(item: str, kind: str) -> set[str]:
    """Names an item introduces (best effort, good enough for reachability)."""
    if kind == "pp":
        m = re.match(r"#\s*define\s+(\w+)", item)
        return {m.group(1)} if m else set()
    if kind == "func":
        head = item[:item.find("{")]
        m = re.search(r"(~?[A-Za-z_][\w:~]*)\s*\([^()]*(\([^()]*\)[^()]*)*\)\s*(const\s*)?$",
                      head.strip())
        if m:
            return {m.group(1).split("::")[-1], m.group(1)}
        return set()
    names = set()
    s = item
    for m in re.finditer(r"\b(struct|union|enum|class)\s+(\w+)\s*(\{|:)", s):
        names.add(m.group(2))
    if re.match(r"\s*(typedef\s+)?enum\b", s):
        body = s[s.find("{") + 1:s.rfind("}")] if "{" in s else ""
        for part in body.split(","):
            m = re.match(r"\s*(\w+)", part)
            if m:
                names.add(m.group(1))
    # the declarator(s) after the last closing brace, or the whole item
    tail = s[s.rfind("}") + 1:] if "}" in s else s
    names |= declarators(tail)
    return names


def declarators(tail: str) -> set[str]:
    """Declared names in `T a, *b[3], (*c)(int), d(void) = ...;`."""
    parts, depth, cur = [], 0, ""
    for ch in tail:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch in ",;" and depth == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += ch
    parts.append(cur)
    out = set()
    for d in parts:
        eq = re.search(r"(?<![=!<>])=(?!=)", d)
        if eq:
            d = d[:eq.start()]
        if "(" in d:
            m = re.match(r"[^(]*\(\s*[*&\s]*(?:const\s+)?(\w+)\s*(\[[^\]]*\]\s*)*\)\s*\(", d)
            if m:
                name = m.group(1)            # (*name)(...) or (name)(...)
            else:
                ids = [w for w in IDENT.findall(d[:d.find("(")]) if w not in KEYWORDS]
                name = ids[-1] if ids else None
        else:
            ids = [w for w in IDENT.findall(re.sub(r"\[[^\]]*\]", "", d)) if w not in KEYWORDS]
            name = ids[-1] if ids else None
        if name:
            out.add(name)
    return out


def dead_declarations(code: str, root: str, keep=None):
    """Top-level items not reachable from `root` (the header's function) through
    identifier references. Returns (items, dead item indexes). Conditional directives
    are roots and both arms count as present, so the answer errs towards "live"."""
    items = top_level_items(code)
    texts = [code[a:b] for a, b, _ in items]
    names = [declared_names(t, k) for t, (_, _, k) in zip(texts, items)]
    refs = [set(IDENT.findall(t)) for t in texts]
    owner = collections.defaultdict(list)
    for idx, ns in enumerate(names):
        for nm in ns:
            owner[nm].append(idx)
    live, work = set(), []
    for idx, (t, (_, _, k)) in enumerate(zip(texts, items)):
        # roots: the function itself, anything declaring nothing we recognise, pragmas,
        # and non-static definitions with bodies (they are code that ships).
        if (root in names[idx] or not names[idx] or (keep is not None and keep(t, k))
                or (k == "pp" and not t.lstrip("# \t").startswith("define"))):
            live.add(idx)
            work.append(idx)
        elif k == "func" and not re.match(r"\s*(static|inline|__inline)\b", t):
            live.add(idx)
            work.append(idx)
    while work:
        idx = work.pop()
        for r in refs[idx] - names[idx]:
            for o in owner.get(r, ()):
                if o not in live:
                    live.add(o)
                    work.append(o)
        # a struct referenced by tag is also reached through its typedef name and back
        for nm in names[idx]:
            for o in owner.get(nm, ()):
                if o not in live:
                    live.add(o)
                    work.append(o)
    dead = [i for i in range(len(items)) if i not in live]
    return items, dead


# ------------------------------------------------------------------------------ checks

LIBRARY_HINT = re.compile(r"__LO\(|__HI\(")
RAM_PTR = re.compile(r"\(\s*[\w\s]+\*+\s*\)\s*\(?\s*(0x0?(?:2[0-3][0-9a-fA-F]{5}|1ff[0-9a-fA-F]{4}"
                     r"|27e[0-9a-fA-F]{4}))\b")
DEREF_INT = re.compile(r"\*\s*\(\s*[\w\s]+\*+\s*\)\s*(0x0?2[0-3][0-9a-fA-F]{5})\b")
PROCESS_NOTES = re.compile(r"\b(scores?\s+\d\.\d+|0\.\d{4}|size_delta|near[- ]miss|"
                           r"byte[- ]identical|candidate\s+v?\d+|docs/kb\b|src/matched\b|"
                           r"is_match|tools/\w+\.py)", re.I)


def check_file(path: pathlib.Path, verify: dict | None) -> dict:
    text = path.read_text(encoding="utf-8", errors="replace")
    src = C.parse_source(path)
    m = C.HEADER.match(text)
    body = text[text.index("*/", m.end() - 3) + 2:] if m else text
    code, comments = split_comments(body)
    flags: dict[str, object] = {}

    def hit(flag, n=1):
        flags[flag] = flags.get(flag, 0) + n

    if re.search(r"^\s*asm\b|\basm\s+\w[\w\s\*]*\(", code, re.M):
        hit("asm-body")
    if "FAKEMATCH:" in comments:
        hit("fakematch")

    n = len(re.findall(r"\b(new_var\d*|temp_r\d+|phi_\w+|var_r\d+)\b", code))
    if n:
        hit("placeholder-names", n)
    n = len(set(re.findall(r"\bsp[0-9A-Fa-f]{1,3}\b", code)))
    if n:
        hit("stack-names", n)

    for line in code.splitlines():
        if re.search(r"&\s*0x[fF]{8}\b", line) and not LIBRARY_HINT.search(line):
            hit("redundant-mask")
    for mm in re.finditer(r"([\w\)\]])\s*(\+|-|\||<<|>>)\s*0(?![.xX\w])|([\w\)\]])\s*\*\s*1(?![.xX\w])",
                          code):
        line_start = code.rfind("\n", 0, mm.start()) + 1
        line_end = code.find("\n", mm.end())
        line = code[line_start:line_end if line_end >= 0 else None]
        pre = code[line_start:mm.start() + 1]
        post = code[mm.end():line_end if line_end >= 0 else None].lstrip()
        if post[:1] == ")" and re.search(r"\*\s*\(\s*\(?[^;]*$", pre):
            continue          # *(p + 0) next to *(p + 1)
        if re.search(r"\[\s*[^\]]*$", pre) and post[:1] == "]":
            continue          # a[i + 0]
        if line.lstrip().startswith("#"):
            continue          # macros: `(8 * 1)` style shifts in SDK macros
        hit("redundant-arith")

    for mm in re.finditer(r"(?<![\w.>])([A-Za-z_][\w.\->\[\]]*)\s*=\s*([A-Za-z_][\w.\->\[\]]*)\s*;",
                          code):
        if mm.group(1) == mm.group(2):
            hit("self-assign")
    for mm in re.finditer(r"(!?\s*[A-Za-z_][\w.\->]*)\s*(&&|\|\||==)\s*(!?\s*[A-Za-z_][\w.\->]*)"
                          r"(?![\w(\[.])", code):
        a, b = mm.group(1).replace(" ", ""), mm.group(3).replace(" ", "")
        if a == b:
            hit("dup-operand")
    # `if (c) { } else { ... }` is just an inverted test, not a dead branch
    n = len(re.findall(r"\bif\s*\((?:[^()]|\((?:[^()]|\([^()]*\))*\))*\)\s*(?:\{\s*\}|;)"
                       r"(?!\s*else\b)", code))
    if n:
        hit("empty-if", n)
    n = len(re.findall(r"\bif\s*\(\s*[01]\s*\)", code))
    n += len(re.findall(r"(?<!\})\s*\bwhile\s*\(\s*0\s*\)\s*\{", code))
    n += len(re.findall(r"\bdo\s*\{\s*\}\s*while\s*\(\s*0\s*\)", code))
    if n:
        hit("const-if", n)
    for mm in re.finditer(r"\bif\s*\((?:[^()]|\([^()]*\))*\)\s*\{([^{}]*)\}\s*else\s*\{([^{}]*)\}",
                          code):
        a, b = " ".join(mm.group(1).split()), " ".join(mm.group(2).split())
        if a and a == b:
            hit("same-branches")

    # (void)x on a local only
    roots = []
    for a, b, k in top_level_items(code):
        if k == "func":
            roots.append(code[a:b])
    params = set()
    for f in roots:
        head = f[:f.find("{")]
        params |= set(IDENT.findall(head[head.find("("):]))
    for mm in re.finditer(r"\(void\)\s*(\w+)\s*;", code):
        if mm.group(1) not in params:
            hit("void-cast")
    n = len(re.findall(r"\(\s*(u16|unsigned short)\s*\)\s*\(\s*(s16|short|signed short)\s*\)"
                       r"|\(\s*(u8|unsigned char)\s*\)\s*\(\s*(s8|char|signed char)\s*\)"
                       r"|\(\s*(s16|short)\s*\)\s*\(\s*(u16|unsigned short)\s*\)"
                       r"|\(\s*(s8|signed char)\s*\)\s*\(\s*(u8|unsigned char)\s*\)"
                       r"|\(\s*(u32|unsigned int|unsigned long)\s*\)\s*\(\s*(s32|int|long)\s*\)"
                       r"|\(\s*(s32|int)\s*\)\s*\(\s*(u32|unsigned int)\s*\)", code))
    if n:
        hit("double-cast", n)
    for f in roots:
        inner = f[f.find("{"):]
        n = len(re.findall(r"(?:^|[;{]\s*)volatile\s+[\w\s]+?\b\w+\s*(?:[;,=\[])", inner, re.M))
        n -= len(re.findall(r"(?:^|[;{]\s*)volatile\s+[\w\s]+\*", inner, re.M))
        if n > 0:
            hit("volatile-local", n)

    n = len(RAM_PTR.findall(code)) + len(DEREF_INT.findall(code))
    if n:
        hit("hardcoded-ram", n)
    if verify:
        if verify.get("hardcoded"):
            flags["hardcoded-ram"] = max(flags.get("hardcoded-ram", 0), verify["hardcoded"])
        probs = verify.get("problems") or []
        names = [p for p in probs if p["kind"] in ("unknown-name", "wrong-target")]
        if names:
            hit("bad-extern-name", len(names))
        local = [p for p in probs if p["kind"] == "local-data-differs"]
        if local:
            hit("local-data-differs", len(local))

    n = len(re.findall(r"\bgoto\b", code))
    if n >= 3:
        hit("goto-heavy", n)

    n = len(PROCESS_NOTES.findall(comments))
    if n:
        hit("process-notes", n)

    if src is not None:
        res = dead_declarations(code, src.object_symbol)
        if res is None and src.object_symbol != src.name:
            res = None
        if res is not None:
            items, dead = res
            dead_lines = sum(code[a:b].count("\n") + 1 for i, (a, b, _) in enumerate(items)
                             if i in set(dead))
            if dead_lines >= 40:
                flags["pasted-types"] = dead_lines

    return {"file": path.relative_to(C.ROOT).as_posix(), "lines": text.count("\n") + 1,
            "flags": flags, "score": score(flags)}


def score(flags: dict) -> int:
    s = 0
    for f, v in flags.items():
        if f == "pasted-types":
            s += 20 if v >= 150 else 10 if v >= 80 else 3
        elif f in ("placeholder-names", "redundant-arith", "empty-if", "dup-operand",
                   "hardcoded-ram", "bad-extern-name", "process-notes", "stack-names",
                   "local-data-differs"):
            s += WEIGHTS[f] * min(1 + (v - 1) * 0.25, 2)
        else:
            s += WEIGHTS[f]
    return min(100, round(s))


# ------------------------------------------------------------------------------ main

def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("paths", nargs="*", type=pathlib.Path)
    ap.add_argument("--top", type=int, default=25, help="worst files to print")
    ap.add_argument("--verify", type=pathlib.Path, action="append",
                    help="verify.py result JSON to read (default build/adm-kr/verify.json); "
                         "repeatable, later files override earlier ones per source")
    args = ap.parse_args()

    files: list[pathlib.Path] = []
    for p in args.paths or [r for r in C.SOURCE_ROOTS if r.is_dir()]:
        p = p.resolve()
        files += sorted(x for x in p.rglob("*") if x.suffix in (".c", ".cpp")) if p.is_dir() \
            else [p]

    verify = {}
    for vpath in args.verify or [C.BUILD / "verify.json"]:
        if vpath.exists():
            for r in json.loads(vpath.read_text()):
                verify[r["file"]] = r
        else:
            print(f"note: {vpath} not found; bad-extern-name and verify's hardcoded counts "
                  "may be missing")

    results = []
    for i, f in enumerate(files, 1):
        rel = f.relative_to(C.ROOT).as_posix()
        results.append(check_file(f, verify.get(rel)))
        if i % 5000 == 0:
            print(f"  {i}/{len(files)}", flush=True)

    whole = not args.paths
    C.BUILD.mkdir(parents=True, exist_ok=True)
    out = C.BUILD / ("quality.json" if whole else "quality-partial.json")
    out.write_text(json.dumps({r["file"]: r["flags"] for r in results if r["flags"]},
                              indent=1, sort_keys=True) + "\n")
    ranked = sorted(results, key=lambda r: (-r["score"], r["file"]))
    tsv = C.BUILD / ("quality-worklist.tsv" if whole else "quality-worklist-partial.tsv")
    with tsv.open("w", encoding="utf-8") as fh:
        fh.write("file\tflags\tscore\n")
        for r in ranked:
            if r["score"] > 0:
                fh.write(f"{r['file']}\t"
                         + ",".join(f"{k}={v}" for k, v in sorted(r["flags"].items()))
                         + f"\t{r['score']}\n")

    files_with = collections.Counter()
    hits = collections.Counter()
    for r in results:
        for k, v in r["flags"].items():
            files_with[k] += 1
            hits[k] += v
    print(f"\n{len(results)} sources, {sum(1 for r in results if r['score'] > 0)} with a "
          f"nonzero score\n")
    print(f"  {'flag':<24}{'files':>8}{'hits':>10}")
    for k in WEIGHTS:
        if files_with[k]:
            print(f"  {k:<24}{files_with[k]:>8}{hits[k]:>10}")
    print(f"\nworst {args.top}:")
    for r in ranked[:args.top]:
        print(f"  {r['score']:>3}  {r['file']}  "
              + " ".join(f"{k}={v}" for k, v in sorted(r["flags"].items())))
    print(f"\n  -> {out.relative_to(C.ROOT)}, {tsv.relative_to(C.ROOT)}")


if __name__ == "__main__":
    main()
