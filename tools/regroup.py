"""Join sources of one function each into a unit: one file of several functions, as the original
source file held them (common.UNIT_HEADER).

    python tools/regroup.py <module> <unit> FILE...    # writes src/<module>/<unit>.c(pp)
    python tools/regroup.py --plan <module>            # the units the module's sources make

The functions go in the original file's order, the last address first (mwccarm writes a file's
functions into its object last first, and the linker keeps the object's order). All the files
must share the compiler, its options, ARM or Thumb, and C or C++.

Each file declared what it uses in its own way; in the unit every name is declared once:
- `#include` lines and `#define`s go to the top, once; a type defined alike in several files is
  kept once. In C, a type that a later file defines differently is renamed in that file
  (`Name_<address>`); in C++ that could change the names the compiler emits, so it is refused.
- Every other declaration goes to the top, one per name: a unit function is declared by its
  definition, data the unit defines as it is defined, a function with a 64-bit result keeps it
  (the divide helpers' quotient and remainder), data as an array if any file declared it so
  (non-const first), anything else as most files declared it (non-const first, then the first).
- In C, where a function's own file declared a name differently, its calls cast each argument
  whose parameter differs, and the result to the type its file expected, and its uses of data
  read the object as the type its file declared. A struct passed by value under another name is
  read as the unit's type (`*(Pair *) &arg`): no cast converts one struct type to another. In
  C++ every file must already agree.
- A unit function or datum named above its definition (a call to a lower address) gets a
  prototype above all the bodies, copied from its definition: gcc 14 and later refuse an
  implicit declaration even with -w, and tools/lint.py checks for it.
- What else a file defines (data, static helpers, the comments before its code) stays just
  before its function.

It refuses, writing nothing, rather than guess: a `#pragma` (mwccarm applies an optimisation
pragma to every function of a file), `#if` or `#undef`; a macro or a static name another file
uses otherwise; two definitions of one helper or datum; a declaration it cannot read; an `asm`
function (tools/native.py cannot compile it for the PC, and would leave the whole unit out);
and any change inside a function a Native table pins (tools/native_tables.py). Those stay
sources of their own. Then tools/verify.py, tools/link.py and tools/lint.py must pass; a
function that no longer verifies beside the others stays a source of its own as well.

--plan lists, for each run of address-adjacent sources of one function compiled alike, the
units it makes: split where the Clean files (clean/<module>/) file the functions apart, and
before a function the settling refuses to add; each named for its Clean file, numbered on where
a source of any module already has the name (dsd refuses one file name in two modules).
"""

from __future__ import annotations

import collections
import dataclasses
import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

KEYWORDS = {"unsigned", "signed", "int", "char", "short", "long", "void", "const", "volatile",
            "struct", "union", "enum", "float", "double", "class", "extern", "static", "inline"}
TYPE_WORDS = KEYWORDS | {"u8", "u16", "u32", "u64", "s8", "s16", "s32", "s64", "BOOL", "f32"}


class Refused(Exception):
    """The files cannot be settled into one unit without a guess."""


def _flat(code: str) -> str:
    return " ".join(C.masked(code).split())


def declared_name(decl: str) -> str | None:
    """The name a declaration declares (a function's or an object's)."""
    t = re.sub(r"^extern\b\s*", "", _flat(decl)).rstrip(";").split("=", 1)[0].strip()
    ptr = re.search(r"\(\s*(?:\w+::)?\*\s*(\w+)\s*[\)\[]", t)
    fn = re.search(r"\b(\w+)\s*\(", t)
    # `void (*name[])(int)`: the first parenthesis is the pointer's, after its type
    if ptr and (fn is None or ptr.start() <= fn.end() - 1):
        return ptr.group(1)
    if fn and fn.group(1) not in KEYWORDS:
        return fn.group(1)
    m = re.search(r"(\w+)\s*(?:\[[^\]]*\]\s*)*$", t)
    return m.group(1) if m else None


# ------------------------------------------------------------------------------ declarations

def norm(t: str) -> str:
    """A type written one way: `unsigned` is `unsigned int`, `short int` is `short`."""
    t = re.sub(r"\s*\*\s*", " * ", t)
    t = " ".join(t.split())
    t = re.sub(r"\bunsigned\b(?! (?:int|char|short|long))", "unsigned int", t)
    t = re.sub(r"\b(short|long) int\b", r"\1", t)
    t = t.replace("signed int", "int") if not t.startswith("unsigned") else t
    return t.replace(" *", "*").replace("* ", "*")


def split_top(s: str) -> list[str]:
    out, depth, start = [], 0, 0
    for i, c in enumerate(s):
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif c == "," and depth == 0:
            out.append(s[start:i])
            start = i + 1
    out.append(s[start:])
    return [x.strip() for x in out]


def param_type(p: str) -> str:
    """A parameter's type, without its name."""
    p = p.strip()
    if p in ("void", "...", ""):
        return p
    m = re.match(r"(.*\(\s*\*)\s*\w*\s*(\).*)", p, re.S)
    if m:
        return (m.group(1) + m.group(2)).strip()
    m = re.match(r"(.*?)\s*\b(\w+)\s*\[[^\]]*\]$", p)
    if m:
        return m.group(1) + " *"
    toks = re.findall(r"\w+|\*", p)
    if len(toks) > 1 and re.fullmatch(r"\w+", toks[-1]) and toks[-1] not in KEYWORDS \
            and toks[-2] not in ("struct", "union", "enum", "class"):
        return re.sub(r"\s*\b" + toks[-1] + r"\s*$", "", p).strip()
    return p


class Decl:
    """A declaration of a function or an object: its kind ('func', 'array' or 'scalar'), the
    type of its result or object, and its parameters' types."""

    def __init__(self, text: str):
        self.text = text.strip() + "\n"
        self.linkage = "C" if re.match(r'extern\s+"C"', " ".join(text.split())) else ""
        t = re.sub(r"^extern\b\s*", "", _flat(text)).rstrip(";").strip()
        name = declared_name(text)
        if name is None:
            raise Refused(f"cannot read the declaration {' '.join(text.split())!r}")
        self.name = name
        self.fnptr = re.search(r"\(\s*(?:\w+::)?\*\s*" + name + r"\b", t) is not None
        if self.fnptr:
            # a pointer to a function: the whole declarator is its type
            self.kind, self.ret, self.params = "scalar", t.replace(name, "", 1), None
            return
        m = re.match(r"(.*?)\b" + name + r"\s*\((.*)\)\s*$", t, re.S)
        if m:
            self.kind, self.ret = "func", m.group(1).strip()
            ps = split_top(m.group(2))
            self.params = [] if ps in (["void"], [""]) else [param_type(p) for p in ps]
            return
        m = re.match(r"(.*?)\b" + name + r"\s*((?:\[[^\]]*\]\s*)*)$", t)
        if m is None:
            raise Refused(f"cannot read the declaration {' '.join(text.split())!r}")
        self.kind = "array" if m.group(2) else "scalar"
        self.ret, self.params = m.group(1).strip(), None

    def key(self) -> tuple:
        return (self.kind, norm(self.ret), tuple(norm(p) for p in self.params or ()))

    def same(self, other: "Decl") -> bool:
        return self.key() == other.key()


def majority(ds: list[Decl]) -> Decl:
    """The declaration most files made (the fewest casts), a non-const one first."""
    count = collections.Counter(d.key() for d in ds)
    return max(ds, key=lambda d: (count[d.key()], "const" not in d.ret, -ds.index(d)))


def choose(ds: list[Decl]) -> Decl:
    """The unit's declaration of a name it does not define, from the files' own."""
    # a 64-bit result (the divide helpers' quotient and remainder) keeps both words
    return next((d for d in ds if d.kind == "func" and re.search(r"64|long long", d.ret)), None) \
        or next((d for d in ds if d.kind == "array" and "const" not in d.ret), None) \
        or next((d for d in ds if d.kind == "array"), None) \
        or majority(ds)


def pointers_differ(d: Decl, ch: Decl) -> bool:
    """Whether the function declarations `d` and `ch` differ only in pointer types (a parameter
    or the result), which a cast converts in C++ as in C."""
    def ptr(t: str) -> bool:
        return "*" in t and not re.search(r"[&(]|\.\.\.", t)
    if d.kind != "func" or ch.kind != "func" or len(d.params) != len(ch.params):
        return False
    return all(norm(a) == norm(b) or (ptr(a) and ptr(b)) for a, b in zip(d.params + [d.ret], ch.params + [ch.ret]))


def simple(a: str) -> bool:
    return re.fullmatch(r"(?:[\w.\[\]]|->)+", a) is not None


def call_args(s: str, i: int) -> tuple[list[tuple[int, int]], int]:
    """(argument spans, index of the closing parenthesis) for the call whose '(' is at s[i]."""
    depth, start, out = 0, i + 1, []
    j = i
    while j < len(s):
        c = s[j]
        if c in "\"'":
            k = j + 1
            while s[k] != c:
                k += 2 if s[k] == "\\" else 1
            j = k
        elif c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
            if depth == 0:
                out.append((start, j))
                return out, j
        elif c == "," and depth == 1:
            out.append((start, j))
            start = j + 1
        j += 1
    raise Refused("an unbalanced call")


def _cast_before(before: str) -> bool:
    """Whether `before` (masked text) ends with a cast, `(void *)`: an & after it is unary."""
    if not before.endswith(")"):
        return False
    depth = 0
    for k in range(len(before) - 1, -1, -1):
        depth += (before[k] == ")") - (before[k] == "(")
        if depth == 0:
            inner = before[k + 1:-1].strip()
            m = re.fullmatch(r"(?:(?:const|volatile|struct|union|enum)\s+)*(\w+)(?:\s+\w+)*\s*(\**)\s*", inner)
            return m is not None and (bool(m.group(2)) or m.group(1) in TYPE_WORDS)
    return False


def by_value(t: str, aggregates: frozenset[str] | set[str]) -> bool:
    """Whether the parameter type `t` is a struct or union passed by value; `aggregates` are the
    typedef names the unit's files define as one."""
    t = " ".join(re.sub(r"\b(?:const|volatile)\b", "", t).split())
    return "*" not in t and "(" not in t and (re.match(r"(?:struct|union)\b", t) is not None or t in aggregates)


def aggregate_typedefs(types: dict[str, str]) -> set[str]:
    """The typedef names among `types` (name -> definition) that name a struct or union itself
    (not a pointer to one)."""
    out = set()
    for tn, code in types.items():
        if " " not in tn and re.match(r"typedef\s+(?:const\s+|volatile\s+)*(?:struct|union)\b", code) \
                and re.search(r"[}\w]\s*\b" + re.escape(tn) + r"\s*;$", code) \
                and not re.search(r"[*(]\s*" + re.escape(tn) + r"\b", code):
            out.add(tn)
    return out


def rewrite(s: str, local: dict[str, Decl], chosen: dict[str, Decl], where: str,
            aggregates: frozenset[str] | set[str] = frozenset()) -> str:
    """`s` (C) with its calls and its uses of data cast from the declarations its file made
    (`local`) to the unit's (`chosen`); `aggregates` are the typedef names of structs and
    unions (aggregate_typedefs)."""
    names = [n for n in local if n in chosen and not local[n].same(chosen[n])]
    if not names:
        return s
    for n in names:
        if local[n].fnptr or chosen[n].fnptr:
            raise Refused(f"{where}: declares the pointer to a function {n} unlike another file")
    pat = re.compile(r"(&\s*)?\b(" + "|".join(map(re.escape, names)) + r")\b")
    plain = C.masked(s)
    out, i = [], 0
    while True:
        m = pat.search(plain, i)
        if m is None:
            out.append(s[i:])
            return "".join(out)
        name = m.group(2)
        before = plain[:m.start()].rstrip()
        if before.endswith(("->", ".")):
            out.append(s[i:m.end()])  # a member of the same name
            i = m.end()
            continue
        if m.group(1) and (before.endswith("&") or re.search(r"[\w)\]]$", before)
                           and not re.search(r"\b(?:return|case)$", before) and not _cast_before(before)):
            # `a & name` or `a && name`: the & is not the name's address
            out.append(s[i:m.start(2)])
            i = m.start(2)
            m = pat.search(plain, i)
            name = m.group(2)
        lo, ch = local[name], chosen[name]
        out.append(s[i:m.start()])
        after = s[m.end():]
        if lo.kind == "func" and ch.kind == "func":
            k = m.end() + len(after) - len(after.lstrip())
            if k >= len(s) or s[k] != "(" or m.group(1):
                # the function as a value: the pointer type its file declared
                ps = ", ".join(lo.params) or "void"
                out.append(f"({lo.ret} (*)({ps})) {name}" if not m.group(1) else s[m.start():m.end()])
                i = m.end()
                continue
            spans, close = call_args(s, k)
            args = [rewrite(s[a:b], local, chosen, where, aggregates).strip() for a, b in spans]
            if args == [""]:
                args = []
            new = []
            for n, a in enumerate(args):
                lt = lo.params[n] if n < len(lo.params) and lo.params[n] != "..." else None
                ct = ch.params[n] if n < len(ch.params) else None
                if ct is None or ct == "..." or (lt is not None and norm(lt) == norm(ct)) or a == "0":
                    new.append(a)
                elif lt is not None and (by_value(lt, aggregates) or by_value(ct, aggregates)):
                    # a struct passed by value: no cast converts one struct type to another, so
                    # the argument object is read as the unit's type
                    if not (by_value(lt, aggregates) and by_value(ct, aggregates)):
                        raise Refused(f"{where}: {name} takes {ct}, its file said {lt}")
                    new.append(f"*({ct} *) &{a}" if simple(a) else f"*({ct} *) &({a})")
                elif lt is not None and "*" not in lt + ct and "(" not in lt + ct:
                    # numbers: the conversion this file made, then the implicit one to the
                    # unit's parameter
                    new.append(a if norm(lt) in ("int", "unsigned int", "s32", "u32") else
                               (f"({lt}) {a}" if simple(a) else f"({lt}) ({a})"))
                else:
                    new.append(f"({ct}) {a}" if simple(a) else f"({ct}) ({a})")
            call = f"{name}({', '.join(new)})"
            before = "".join(out).rstrip()
            statement = before.endswith((";", "{", "}", ")", "else")) and s[close + 1:].lstrip().startswith(";")
            if not statement and norm(lo.ret) != norm(ch.ret):
                if "void" in (norm(lo.ret), norm(ch.ret)):
                    raise Refused(f"{where}: {name} returns {ch.ret}, its file said {lo.ret}")
                # a member, element or call of the result applies to the cast result
                post = re.match(r"\s*(?:->|\.|\[|\()", s[close + 1:]) is not None
                call = f"(({lo.ret}) {call})" if post else f"({lo.ret}) {call}"
            out.append(call)
            i = close + 1
            continue
        if "func" in (lo.kind, ch.kind):
            raise Refused(f"{where}: {name} is a function in one file and data in another")
        # data: read the unit's object as the type this file declared
        lt, addr = lo.ret, "" if ch.kind == "array" else "&"
        member = re.match(r"\s*(?:\[|\.|->)", after) is not None
        if m.group(1) and member:
            out.append(s[m.start():m.start(2)])  # the address of an element or a member
        if (m.group(1) and not member) or lo.kind == "array":
            out.append(f"(({lt} *) {addr}{name})")
        else:
            out.append(f"(*({lt} *) {addr}{name})")
        i = m.end()


# ------------------------------------------------------------------------------ items

@dataclasses.dataclass
class Item:
    """A top-level piece of a source. `lead` is the comments and blank lines before its code."""
    kind: str  # include define pp | type decl block | func helper data static comment | other
    lead: str
    code: str
    names: list[str]
    children: list["Item"] = dataclasses.field(default_factory=list)


def _matching(plain: str, i: int) -> int:
    depth = 0
    for k in range(i, len(plain)):
        depth += (plain[k] in "([{") - (plain[k] in ")]}")
        if depth == 0:
            return k
    raise Refused("unbalanced braces")


def _depth0(flat: str) -> str:
    """`flat` without what its brackets hold."""
    while True:
        new = re.sub(r"\([^()]*\)|\[[^\[\]]*\]|\{[^{}]*\}", "", flat)
        if new == flat:
            return flat
        flat = new


def type_names(code: str) -> list[str]:
    """The names a type definition defines: its tag, its typedef name, its enumerators."""
    plain = _flat(code)
    names = []
    m = re.match(r"(?:typedef\s+)?(struct|union|enum|class)\s+(\w+)\s*[{;:]", plain)
    if m:
        names.append(f"{m.group(1)} {m.group(2)}")
    if plain.startswith("typedef"):
        ptr = re.search(r"\(\s*(?:\w+::)?\*\s*(\w+)\s*\)", plain)
        m = ptr or re.search(r"(\w+)\s*(?:\[[^\]]*\]\s*)*;\s*$", plain)
        if m:
            names.append(m.group(1))
    if re.match(r"(?:typedef\s+)?enum\b", plain) and "{" in plain:
        inner = plain[plain.index("{") + 1:plain.rindex("}")]
        names += [e.split("=")[0].strip() for e in inner.split(",") if e.strip()]
    return names


def split_declarators(code: str) -> list[str] | None:
    """`extern T a, *b, c[];` as one declaration a line (`extern T a;` ...), or None for anything
    else: a definition, an initializer, a function or a pointer to one, a comment."""
    flat = " ".join(code.split())
    if C.masked(code) != code or not flat.startswith("extern ") or not flat.endswith(";") \
            or re.search(r'[(){}=]|extern\s*"', flat):
        return None
    parts = split_top(flat[:-1])
    first = re.search(r"[\s*]*\b(\w+)\s*(?:\[[^\]]*\]\s*)*$", parts[0])
    if first is None:
        return None
    base = parts[0][:first.start()].rstrip()
    declarators = [parts[0][first.start():].strip()] + parts[1:]
    if base in ("extern", "") or not all(re.fullmatch(r"\**\s*\w+\s*(?:\[[^\]]*\]\s*)*", d) for d in declarators):
        return None
    return [f"{base} {d};\n" for d in declarators]


def items(body: str) -> list[Item]:
    """The top-level pieces of a source's text after its header, in order."""
    plain = C.masked(body)
    out: list[Item] = []
    i, n = 0, len(body)
    while True:
        j = i
        while j < n and plain[j].isspace():
            j += 1
        if j >= n:
            if body[i:].strip():
                out.append(Item("comment", body[i:], "", [""]))
            return out
        lead = body[i:j]
        if plain[j] == "#":
            k = j
            while True:
                e = body.find("\n", k)
                e = n if e < 0 else e
                if body[k:e].rstrip().endswith("\\"):
                    k = e + 1
                    continue
                break
            end = min(e + 1, n)
            code = body[j:end]
            word = re.match(r"#\s*(\w*)", code).group(1)
            if word == "include":
                out.append(Item("include", lead, code, []))
            elif word == "define":
                out.append(Item("define", lead, code, [re.match(r"#\s*define\s+(\w+)", code).group(1)]))
            else:
                out.append(Item("pp", lead, code, [word]))
            i = end
            continue
        m = re.match(r'extern\s*"C"\s*\{', body[j:])
        if m:
            close = _matching(plain, j + m.end() - 1)
            end = close + 1
            e = body.find("\n", end)
            end = e + 1 if e >= 0 and not plain[end:e].strip() else end
            inner = items(body[j + m.end():close])
            out.append(Item("block", lead, body[j:end], [x for it in inner for x in it.names], inner))
            i = end
            continue
        depth, k, kind = 0, j, None
        while k < n:
            c = plain[k]
            if c == "{" and depth == 0 and re.search(r"\)\s*(?:const\s*)?$", plain[j:k]):
                k = _matching(plain, k)
                kind = "func"
                break
            if c in "([{":
                depth += 1
            elif c in ")]}":
                depth -= 1
            elif c == ";" and depth == 0:
                break
            k += 1
        if k >= n:
            raise Refused(f"cannot read {' '.join(body[j:j + 60].split())!r}")
        end = k + 1
        e = body.find("\n", end)
        end = n if e < 0 else (e + 1 if not plain[end:e].strip() else end)
        code = body[j:end]
        flat = _flat(code)
        i = end
        if kind == "func":
            head = flat[:flat.index("{")]
            f = re.search(r"([\w:~]+)\s*\(", head)
            static = re.match(r"(?:extern\s+)?(?:static|inline)\b", head)
            out.append(Item("helper" if static else "func", lead, code, [f.group(1) if f else ""]))
        elif re.match(r"(?:namespace|using|template)\b", flat):
            out.append(Item("other", lead, code, []))
        elif flat.startswith("typedef") or re.match(r"(?:struct|union|enum|class)\s+\w*\s*(?:\{|;|:)", flat):
            ok = "{" not in flat or re.search(r"\}\s*\w*\s*;$", flat)
            out.append(Item("type" if ok else "other", lead, code, type_names(code) if ok else []))
        elif "," in _depth0(flat):
            # several declarators: a declaration of names of one type is one declaration each
            one_each = split_declarators(code)
            if one_each is None:
                out.append(Item("other", lead, code, []))
            for index, part in enumerate(one_each or ()):
                out.append(Item("decl", lead if index == 0 else "", part, [declared_name(part)]))
        else:
            name = declared_name(code)
            depth0 = _depth0(flat)
            if flat.startswith("static"):
                out.append(Item("static", lead, code, [name]))
            elif "=" in depth0 or not (flat.startswith("extern") or "(" in flat):
                out.append(Item("data", lead, code, [name]))  # a definition: it has storage
            else:
                out.append(Item("decl", lead, code, [name]))


# ------------------------------------------------------------------------------ settling

def _words(text: str) -> set[str]:
    return set(re.findall(r"\b\w+\b", C.masked(text)))


def _pinned() -> set[str]:
    import native_tables
    return {k for _, k, _ in native_tables.pinned()}


_BASIC: dict[str, str] = {}


def _basic() -> dict[str, str]:
    """include/types.h's typedefs, by name."""
    if not _BASIC:
        text = (C.INCLUDE / "types.h").read_text(encoding="utf-8")
        _BASIC.update({m.group(1): _flat(m.group(0)) for m in re.finditer(r"^typedef\b[^;]*?\b(\w+)\s*;", text, re.M)})
    return _BASIC


def _all(its: list[Item]) -> list[Item]:
    return [x for it in its for x in [it] + it.children]


def _is_forward(it: Item) -> bool:
    return "{" not in it.code and not _flat(it.code).startswith("typedef")


CHUNK = ("func", "helper", "data", "static", "comment")


@dataclasses.dataclass
class File:
    src: C.Source
    body: str               # the text after the header, its types renamed where needed
    lead: str               # the comments before its first piece (a FAKEMATCH note)
    pre: list[Item]         # what goes to the top: includes, macros, types, declarations
    chunk: list[Item]       # what stays: its function and what it defines beside it


def _rename_types(srcs: list[C.Source], cpp: bool) -> dict[str, str]:
    """Each file's text after its header, a type that an earlier file defines differently
    renamed (C)."""
    types: dict[str, str] = {}
    bodies = {}
    for s in srcs:
        text = s.path.read_text(encoding="utf-8")
        body = text[C.header_end(text):]
        try:
            its = items(body)
        except Refused as e:
            raise Refused(f"{s.name}: {e}") from None
        renames = {}
        for it in _all(its):
            if it.kind == "type" and not _is_forward(it):
                for tn in it.names:
                    if tn in types and types[tn] != _flat(it.code) and tn not in _basic():
                        if cpp:
                            raise Refused(f"{s.name}: defines {tn} unlike another file (C++)")
                        word = tn.split()[-1]
                        renames[word] = f"{word}_{s.address:08x}"
        if renames:
            pat = re.compile(r"(?<![.>])\b(" + "|".join(map(re.escape, renames)) + r")\b")
            body = pat.sub(lambda m: renames[m.group(1)], body)
            its = items(body)
        for it in _all(its):
            if it.kind == "type" and not _is_forward(it):
                for tn in it.names:
                    types.setdefault(tn, _flat(it.code))
        bodies[s.name] = body
    return bodies


def _split(s: C.Source, body: str) -> File:
    its = items(body)
    pre, chunk, lead = [], [], ""
    for n, it in enumerate(its):
        if n == 0 and it.lead.strip():
            lead, it.lead = it.lead, ""
        if it.kind in ("pp", "other"):
            what = (it.code or it.lead).strip().split("\n")[0]
            raise Refused(f"{s.name}: {' '.join(what.split())!r}"
                          + (", which applies to the whole file" if it.names == ["pragma"] else ""))
        for ch in it.children:
            if ch.kind not in ("decl", "type"):
                raise Refused(f"{s.name}: an extern \"C\" block holds {' '.join(ch.code.split())[:60]!r}")
        (chunk if it.kind in CHUNK else pre).append(it)
    defs = [it.names[0].split("::")[-1] for it in chunk if it.kind == "func"]
    if defs != [s.name.split("::")[-1]]:
        raise Refused(f"{s.name}: its file defines {defs or 'no function the tools find'}")
    if any(re.search(r"\basm\b", _flat(it.code)) for it in chunk):
        # tools/native.py cannot compile it for the PC, and would leave the whole unit out
        raise Refused(f"{s.name}: an asm function, which Native leaves out")
    return File(s, body, lead, pre, chunk)


def settle(module: str, unit: str, srcs: list[C.Source], pinned: set[str] | None = None) -> tuple[str, list[str]]:
    """The text of the unit of `srcs` (sources of one function each), every name declared
    once, and the functions whose text it changed. Raises Refused."""
    kinds = {(s.drop, s.opt, s.thumb, s.lang) for s in srcs}
    if len(kinds) != 1:
        raise Refused(f"the files are compiled differently: {sorted(kinds)}")
    srcs = sorted(srcs, key=lambda s: s.address, reverse=True)
    cpp = srcs[0].lang == "c++"
    short = {s.name.split("::")[-1] for s in srcs}
    bodies = _rename_types(srcs, cpp)
    files = []
    for s in srcs:
        try:
            files.append(_split(s, bodies[s.name]))
        except Refused as e:
            raise Refused(str(e) if str(e).startswith(s.name) else f"{s.name}: {e}") from None
    basic = _basic()

    # macros: one definition each, and no other file may use the name
    macros: dict[str, str] = {}
    for f in files:
        for it in f.pre:
            if it.kind == "define" and macros.setdefault(it.names[0], _flat(it.code)) != _flat(it.code):
                raise Refused(f"{f.src.name}: #define {it.names[0]} differs from another file's")
    for name in macros:
        for f in files:
            if name in _words(f.body) and not any(it.kind == "define" and it.names[0] == name for it in f.pre):
                raise Refused(f"{f.src.name}: uses {name}, which another file defines as a macro")

    # what the files define beside their functions: once each, a static name no other file's
    defined: dict[str, tuple[File, Item]] = {}
    static_protos: list[Item] = []
    dups: set[int] = set()
    for f in files:
        for it in f.chunk:
            if it.kind in ("func", "comment"):
                continue
            name = it.names[0]
            if it.kind == "static" and "=" not in _depth0(_flat(it.code)) \
                    and Decl(it.code.replace("static", "", 1)).kind == "func":
                static_protos.append(it)
                continue
            if name in defined:
                if it.kind == "helper" and _flat(defined[name][1].code) == _flat(it.code):
                    dups.add(id(it))
                    continue
                raise Refused(f"{f.src.name}: {name} is defined in two of the files")
            defined[name] = (f, it)
    for name, (f0, it0) in defined.items():
        if it0.kind != "data":
            for f in files:
                if f is not f0 and name in _words(f.body) and not any(
                        id(it) in dups and it.names[0] == name for it in f.chunk):
                    raise Refused(f"{f.src.name}: uses {name}, static in another file")

    # types
    types = {tn: _flat(it.code) for f in files for it in _all(f.pre) if it.kind == "type" for tn in it.names}
    aggregates = aggregate_typedefs(types)
    need_types_h = False
    for f in files:
        for it in _all(f.pre):
            if it.kind == "type":
                for tn in it.names:
                    if tn in basic:
                        if _flat(it.code) != basic[tn]:
                            raise Refused(f"{f.src.name}: defines {tn} unlike include/types.h")
                        need_types_h = True

    # declarations: each file's view, and the unit's, one per name
    local: dict[str, dict[str, Decl]] = {}
    seen: dict[str, list[Decl]] = collections.defaultdict(list)
    for f in files:
        view = local.setdefault(f.src.name, {})
        for top in f.pre:
            for it in [top] + top.children:
                if it.kind == "decl":
                    d = Decl(it.code)
                    d.linkage = "C" if top.kind == "block" else d.linkage
                    view[d.name] = d
                    seen[d.name].append(d)
        for it in f.chunk:
            if it in static_protos:
                view[it.names[0]] = Decl(it.code.replace("static", "", 1))
    for name in seen:
        if name in macros or name in types or (name in defined and defined[name][1].kind != "data"):
            raise Refused(f"{name} is declared in one file and is a type, macro or static in another")
    chosen: dict[str, Decl] = {}
    proto: dict[str, tuple[str, str]] = {}  # name -> (prototype, linkage)
    for f in files:
        it = next(it for it in f.chunk if it.kind == "func")
        head = " ".join(it.code[:C.masked(it.code).index("{")].split())
        if "::" in it.names[0]:
            continue
        d = Decl(head + ";")
        chosen[d.name] = d
        c_linkage = cpp and f.src.emitted is None
        proto[d.name] = (re.sub(r'^extern\s+"C"\s*', "", head) + ";" if c_linkage else head + ";",
                         "C" if c_linkage else "")
    for name, (f, it) in defined.items():
        if it.kind == "data":
            head = it.code[:C.masked(it.code).index("=")] if "=" in _depth0(_flat(it.code)) else it.code
            d = Decl("extern " + " ".join(head.split()).rstrip(";").strip() + ";")
            chosen[name] = d
            proto[name] = (d.text.strip(), "")
    for name, ds in seen.items():
        if name not in chosen:
            chosen[name] = choose(ds)
    # C++: every file must agree, but for a C function whose declarations differ only in the
    # pointers it takes or returns (one function, no overloads), which its calls cast to as in C
    cast_in_cpp: dict[str, set[str]] = collections.defaultdict(set)
    if cpp:
        for f in files:
            for name, d in local[f.src.name].items():
                ch = chosen[name]
                if d.same(ch) and (name in short or name in defined or d.linkage == ch.linkage):
                    continue
                c_both = d.linkage == "C" and (ch.linkage == "C" or proto.get(name, ("", ""))[1] == "C")
                if c_both and pointers_differ(d, ch):
                    cast_in_cpp[f.src.name].add(name)
                    continue
                raise Refused(f"{f.src.name}: declares {name} unlike another file (C++)")

    # each file's function and what it defines beside it, cast where its file declared a name
    # otherwise (C)
    parts: list[tuple[File, Item, str]] = []
    for f in files:
        view = dict(local[f.src.name])
        view.pop(f.src.name.split("::")[-1], None)
        for it in f.chunk:
            if id(it) in dups or it in static_protos:
                continue
            code = it.code
            if it.kind == "func":
                # an extern declaration inside the function is its file's view too; one the unit
                # makes otherwise goes, and the function's uses of the name are cast
                for m in list(re.finditer(r"^[ \t]+(extern\b[^;{]*;)[ \t]*\n", code, re.M)):
                    d = Decl(m.group(1))
                    if d.name in chosen and not d.same(chosen[d.name]):
                        if cpp:
                            raise Refused(f"{f.src.name}: declares {d.name} unlike another file (C++)")
                        view[d.name] = d
                        code = code.replace(m.group(0), "", 1)
            if not cpp:
                code = rewrite(code, view, chosen, f.src.name, aggregates)
            elif cast_in_cpp[f.src.name]:
                code = rewrite(code, {n: view[n] for n in cast_in_cpp[f.src.name] if n in view}, chosen, f.src.name)
            parts.append((f, it, code))

    # the top: includes, then macros, types and declarations (C), or the files' own order (C++)
    includes = []
    for f in files:
        for it in f.pre:
            if it.kind == "include" and it.code not in includes:
                includes.append(it.code)
    if need_types_h and not any('"types.h"' in i for i in includes):
        includes.insert(0, '#include "types.h"\n')
    done: set[str] = set()

    def emit(it: Item, linkage: str) -> str:
        """The text `it` adds to the top, or nothing where another file's says it."""
        lead = it.lead.lstrip("\n")
        if it.kind == "define":
            key = "#" + it.names[0]
        elif it.kind == "type":
            if any(tn in basic for tn in it.names):
                return ""
            key = "type " + _flat(it.code)
        elif it.kind == "decl":
            name = it.names[0]
            d = Decl(it.code)
            if name in short or name in defined or not d.same(chosen[name]) or \
                    (cpp and (linkage or d.linkage) != chosen[name].linkage):
                return ""
            key = "decl " + name
        elif it.kind == "block":
            inner = "".join(x for x in (emit(c, "C") for c in it.children) if x)
            return lead + 'extern "C" {\n' + inner + "}\n" if inner else ""
        else:
            return ""
        if key in done:
            return ""
        done.add(key)
        return lead + it.code.strip("\n") + "\n"

    # declarations and macros one to a line, a blank line around a type or a block
    groups = [("define",), ("type",), ("decl",)] if not cpp else [("define", "type", "decl", "block")]
    top, prev = "", None
    for kinds_ in groups:
        for f in files:
            for it in f.pre:
                text = emit(it, "") if it.kind in kinds_ else ""
                if text:
                    tight = it.kind in ("define", "decl") and prev == it.kind and not it.lead.strip()
                    top += ("" if tight or not top else "\n") + text
                    prev = it.kind
    for it in static_protos:
        key = "decl " + it.names[0]
        if key not in done:
            done.add(key)
            top += ("" if prev == "decl" or not top else "\n") + it.lead.lstrip("\n") + it.code.strip("\n") + "\n"
            prev = "decl"

    first = srcs[0]
    head = [f"/* {unit}: {len(srcs)} functions, module {module}", f" * mwccarm {first.drop} {first.opt}"]
    head += [f" * {s.name} @ 0x{s.address:08x}, 0x{s.size:x} bytes, {'Thumb' if s.thumb else 'ARM'}"
             + (f", emits {s.emitted}" if s.emitted else "") for s in srcs]
    head.append(" */")
    preamble = "\n".join(x for x in ["\n".join(head) + "\n", "".join(includes), top] if x)

    # the bodies, and where each function and datum is defined
    joined, at, last = "", {}, None
    for f, it, code in parts:
        lead = it.lead.lstrip("\n")
        if f is not last and f.lead.strip():
            lead = f.lead.strip("\n") + "\n" + lead
        joined += "\n" + lead
        last = f
        at[it.names[0].split("::")[-1]] = len(joined)
        joined += code.strip("\n") + "\n"
    needed = []
    for f in files:
        for it in f.chunk:
            name = it.names[0].split("::")[-1]
            if it.kind not in ("func", "data") or id(it) in dups or name not in proto:
                continue
            used = re.search(r"\b" + re.escape(name) + r"\b", C.masked(preamble + joined[:at[name]]))
            # in C++, a function of C linkage whose definition does not say so has it from a
            # declaration before it
            unsaid = proto[name][1] == "C" and not _flat(it.code).startswith("extern")
            if used or unsaid:
                needed.append(proto[name])
    protos = ""
    if any(link == "C" for _, link in needed):
        protos += 'extern "C" {\n' + "".join(p + "\n" for p, link in needed if link == "C") + "}\n"
    protos += "".join(p + "\n" for p, link in needed if link != "C")
    text = preamble + ("\n" + protos if protos else "") + joined

    # what changed inside the functions: nothing a Native table pins may
    pinned = _pinned() if pinned is None else pinned
    edited = []
    for f in files:
        name = f.src.name
        if C.function_text(f.src.path.read_text(encoding="utf-8"), name) != C.function_text(text, name):
            if f"{module}/{name}" in pinned:
                raise Refused(f"{name}: a Native table pins it, and it would change")
            edited.append(name)
    left = C.undeclared_uses(text[C.header_end(text):], [s.name for s in srcs])
    if left:
        raise Refused(f"used before they are declared: {left}")
    # the Native tables' audited edits must still apply to the unit's text (a member-pointer
    # copy translates the whole source, one member type per class)
    import native
    try:
        native.source_copy([f"{module}/{s.name}" for s in srcs], text)
    except ValueError as e:
        raise Refused(f"the Native tables' edits do not apply to the unit: {e}") from None
    return text, edited


def regroup(module: str, unit: str, paths: list[pathlib.Path]) -> tuple[pathlib.Path | None, list[str]]:
    """Write src/<module>/<unit>.c(pp) from `paths` and remove them: (the unit, []). When the
    files cannot be settled into one, nothing is written: (None, the reason)."""
    srcs = []
    for p in paths:
        found = C.parse_sources(p)
        if len(found) != 1 or found[0].module != module:
            raise SystemExit(f"{p}: not a source of one function of {module}")
        srcs.append(found[0])
    dest = C.SRC / module / f"{unit}{srcs[0].path.suffix}"
    if dest.exists():
        raise SystemExit(f"{dest} exists")
    try:
        text, _ = settle(module, unit, srcs)
    except Refused as e:
        return None, [str(e)]
    dest.write_text(text, encoding="utf-8", newline="\n")
    for s in srcs:
        s.path.unlink()
    return dest, []


# ------------------------------------------------------------------------------ planning

def clean_files(module: str) -> dict[str, str]:
    """Object symbol -> the Clean file (its stem) that holds the function."""
    out: dict[str, str] = {}
    for f in sorted((C.ROOT / "clean" / module).glob("*.c*")):
        for name in re.findall(r"CLEAN_AS\((\w+)", f.read_text(encoding="utf-8")):
            out.setdefault(name, f.stem)
    return out


def runs(module: str) -> list[list[C.Source]]:
    """Runs of address-adjacent sources of one function compiled alike: a unit, or a change of
    compiler, options, ISA or language, ends one, and so do bytes between two functions beyond
    the padding to a word (code no source defines, such as a second entry point: tools/link.py
    takes a unit's functions as one piece and would find a hole in it)."""
    srcs = sorted((s for p in (C.SRC / module).glob("*.c*") for s in C.parse_sources(p)), key=lambda s: s.address)
    out: list[list[C.Source]] = []
    prev = None
    for s in srcs:
        kind = (s.drop, s.opt, s.thumb, s.lang, s.path.stem == s.name)
        last = out[-1][-1] if out else None
        if out and kind == prev and kind[4] and s.address <= (last.address + last.size + 3) & ~3:
            out[-1].append(s)
        else:
            out.append([s])
        prev = kind
    return [r for r in out if len(r) > 1 and r[0].path.stem == r[0].name]


def plan(module: str, apart: frozenset[str] = frozenset()) -> list[tuple[str, list[C.Source]]]:
    """The units the module's sources of one function make (see the module docstring), each
    named; a function in `apart` stays a source of its own."""
    clean = clean_files(module)
    pinned = _pinned()
    groups: list[list[C.Source]] = []
    for run in runs(module):
        segs: list[list[C.Source]] = [[]]
        for s in run:
            where = clean.get(s.object_symbol)
            if s.name in apart:
                segs.append([])
            elif segs[-1] and (where is None or clean.get(segs[-1][-1].object_symbol) in (None, where)):
                segs[-1].append(s)
            else:
                segs.append([s])
        for seg in segs:
            # grow while the settling takes the next function
            cur: list[C.Source] = []
            for s in seg:
                try:
                    settle(module, "probe", cur + [s], pinned)
                    cur.append(s)
                except Refused:
                    groups.append(cur)
                    cur = [s]
            groups.append(cur)
    # dsd names each object for its source file, and refuses one file name in two modules
    taken = {p.stem for p in C.all_sources()}
    out = []
    count: collections.Counter = collections.Counter()
    for g in (g for g in groups if len(g) > 1):
        where = [clean[s.object_symbol] for s in g if s.object_symbol in clean]
        stem = max(where, key=lambda k: (where.count(k), -where.index(k))) if where else f"{module}_{g[0].address:08x}"
        name = stem
        while name in taken:
            count[stem] += 1
            name = f"{stem}_{count[stem] + 1}"
        taken.add(name)
        out.append((name, g))
    return out


def main() -> None:
    if sys.argv[1:2] == ["--plan"] and len(sys.argv) == 3:
        for name, g in plan(sys.argv[2]):
            print(f"{name}: {len(g)} functions, {g[0].address:08x}-{g[-1].address:08x}")
            print("  " + " ".join(s.path.relative_to(C.ROOT).as_posix() for s in g))
        return
    if len(sys.argv) < 5:
        raise SystemExit(__doc__)
    module, unit = sys.argv[1], sys.argv[2]
    dest, problems = regroup(module, unit, [pathlib.Path(a).resolve() for a in sys.argv[3:]])
    if dest is None:
        for p in problems:
            print(f"refused: {p}")
        raise SystemExit(1)
    print(f"wrote {dest.relative_to(C.ROOT).as_posix()}")


if __name__ == "__main__":
    main()
