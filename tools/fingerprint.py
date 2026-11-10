"""The compiled code of a tree as a few values that do not depend on what anything is called
(tools/gate.py: a change that only renames, and which of the two passes a change needs).

    python tools/fingerprint.py                # build the Clean objects, print the parts
    python tools/fingerprint.py --write FILE   # ... and write them to FILE as JSON, with the
                                               # commit (when nothing is uncommitted) and the
                                               # functions whose Native code a Clean run can run

Two trees with the same parts run the same PC code: every Native and Clean object of one is an
object of the other with the same sections, bytes, relocations and symbols, once each name is
put aside for what it stands for, and the tables the program is linked with (natives.s,
absolute.s, clean_table.c, the Native policy) are the same in the same way. A name stands for

- the game's function or data it is in the symbol table (config/): its module, address, kind
  and size, so a symbol renamed in the table and in every source stands for the same;
- the game function a Clean function is registered for (CLEAN_AS), so a Clean function may
  be renamed;
- the place of its definition, for a name only the PC code has (a helper shared by Clean
  files): the object that defines it, told by its shape, when no other object has that shape;
- nothing else: any other name (the runtime's, the C library's) must be the very same.

Names an object keeps to itself (static functions and data, sections, labels) are left out:
its code refers to them by section and offset. The names of two things never stand for the
same: where two would (two symbols at one address, two Clean functions registered for one
function), both are compared as they are spelled. Whatever a name is part of beyond a symbol
(a string that holds it, an assert's text and line) is in the bytes, and makes the parts
differ. The comparison is one way only: equal parts mean the same code; code that is the same
may still give different parts (sources listed in another order after a file is renamed, a
symbol table sorted by name), and then the gate runs as for any change.

The parts:

    native_objects   the Native objects (build/<version>/native/<host>/objects.txt)
    native_tables    natives.s, absolute.s, the policy of a run without Clean, the resident
                     symbols' addresses, the modules, the ROM
    clean_objects    the Clean objects and their checks' (tools/run.py, build_clean)
    clean_tables     clean_table.c and the policy of a run with every Clean function

A gate that passes on a tree with nothing uncommitted keeps its parts under the commit, in the
cache every checkout shares (record); a later gate compares its own with the record of the
commit it started from (tools/gate.py). Windows objects (COFF) only: elsewhere there are no
parts, and the gate runs as it would without them.
"""
from __future__ import annotations

import hashlib
import json
import pathlib
import re
import struct
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

FORMAT = 1
# the sections a compiler names `<kind>$<name>` for one function or variable: the part after
# the `$` only orders them inside the linked section
STANDARD_SECTIONS = (".text", ".data", ".rdata", ".bss", ".xdata", ".pdata")
# what tools/objrewrite.py, tools/native_clean_profile.py and runtime/diffcheck.h put before a
# name, the longest first
PREFIXES = ("native_body_", "native_call_", "native_pmf_", "native_", "diff_test_", "")
EXTERNAL, WEAK, FILE = 2, 105, 103  # COFF storage classes
TOKEN = re.compile(r"[A-Za-z_$?@.][\w$?@.]*")


def coff_shape(data: bytes) -> dict | None:
    """An i386 COFF object without its names, or None for anything else: `shape`, a SHA-1 of its
    sections (kind, sizes, flags, bytes, relocations) and symbols, in which an external symbol
    is the number of its first use and a symbol of the object's own is its section and offset;
    `names`, the external names by that number; `defined`, the numbers of those it defines.
    The time in the header, the source's name and the string table are left out. An object
    that holds only symbols (absolute.s) has `flat`, its symbols in no order, instead."""
    if len(data) < 20:
        return None
    machine, nsec, _stamp, symptr, nsym, opt, chars = struct.unpack_from("<HHIIIHH", data, 0)
    if machine != 0x14C or symptr + 18 * nsym + 4 > len(data):
        return None
    strings = symptr + 18 * nsym

    def text(offset: int) -> str:
        return data[strings + offset:data.index(b"\0", strings + offset)].decode("latin-1")
    symbols: list[tuple | None] = []
    i = 0
    while i < nsym:
        raw = data[symptr + 18 * i:symptr + 18 * (i + 1)]
        name = text(struct.unpack_from("<I", raw, 4)[0]) if raw[:4] == b"\0\0\0\0" else raw[:8].rstrip(b"\0").decode("latin-1")
        value, section, kind, storage, aux = struct.unpack_from("<IhHBB", raw, 8)
        symbols.append((name, value, section, kind, storage, data[symptr + 18 * (i + 1):symptr + 18 * (i + 1 + aux)]))
        symbols.extend([None] * aux)
        i += 1 + aux
    names: list[str] = []
    numbers: dict[str, int] = {}

    def token(index: int) -> tuple:
        symbol = symbols[index]
        if symbol is None:
            raise ValueError("a relocation against an auxiliary record")
        name, value, section, _kind, storage, _aux = symbol
        if storage in (EXTERNAL, WEAK):
            if name not in numbers:
                numbers[name] = len(names)
                names.append(name)
            return ("external", numbers[name])
        return ("own", section, value, storage)
    h = hashlib.sha1()

    def add(*fields) -> None:
        h.update(repr(fields).encode() + b"\n")
    add("coff", machine, nsec, chars, opt)
    only_symbols = True
    for s in range(nsec):
        header = 20 + opt + 40 * s
        raw = data[header:header + 8]
        name = text(int(raw[1:].rstrip(b"\0"))) if raw[:1] == b"/" else raw.rstrip(b"\0").decode("latin-1")
        vsize, vaddr, size, at, relocations, _lines, count, lines, flags = struct.unpack_from("<IIIIIIHHI", data, header + 8)
        kind, dollar, _ = name.partition("$")
        if dollar and kind in STANDARD_SECTIONS:
            name = kind + "$"
        if count == 0xFFFF and flags & 0x01000000:  # more than 65534: the first record holds the count
            count = struct.unpack_from("<I", data, relocations)[0] - 1
            relocations += 10
        add("section", name, vsize, vaddr, size, flags, lines, hashlib.sha1(data[at:at + size] if at else b"").hexdigest(), count)
        only_symbols = only_symbols and not size and not count
        for r in range(count):
            where, index, how = struct.unpack_from("<IIH", data, relocations + 10 * r)
            add("relocation", where, how, token(index))
    defined: list[int] = []
    flat: list[tuple] = []
    for index, symbol in enumerate(symbols):
        if symbol is None:
            continue
        name, value, section, kind, storage, aux = symbol
        if storage == FILE:  # the source's name
            add("file")
            continue
        extra: object = aux.hex()
        if storage == WEAK and len(aux) >= 8:  # the symbol it falls back on, and how it is searched
            extra = ("weak", token(struct.unpack_from("<I", aux, 0)[0]), struct.unpack_from("<I", aux, 4)[0])
            only_symbols = False
        if storage in (EXTERNAL, WEAK):
            number = token(index)[1]
            add("external", number, value, section, kind, storage, extra)
            if section != 0 or value:  # in a section, absolute, or common
                defined.append(number)
            flat.append((name, value, section, kind, storage, extra))
        else:
            add("own", value, section, kind, storage, extra)
    out = {"shape": h.hexdigest(), "names": names, "defined": defined}
    if only_symbols:
        own = sorted(repr((value, section, kind, storage, aux.hex())) for symbol in symbols if symbol is not None
                     for _name, value, section, kind, storage, aux in [symbol] if storage not in (EXTERNAL, WEAK, FILE))
        out["shape"] = hashlib.sha1(repr(("symbols", machine, nsec, chars, own)).encode()).hexdigest()
        out["flat"] = [list(f) for f in flat]
    return out


class Labels:
    """What each name stands for (see the top of the file). `prefix` is what the host puts
    before a C name in an object ("_" on i386 Windows)."""

    def __init__(self, symbols: dict[str, list[tuple]], clean: dict[str, str], prefix: str):
        """`symbols`: name -> what the symbol table has under it, each (module, address, kind,
        size, thumb); `clean`: registered Clean function -> the game symbol it stands for."""
        self.prefix = prefix
        found: dict[str, str] = {}
        for name, entries in symbols.items():
            found[name] = "ds:" + ";".join(sorted(":".join(str(f) for f in entry) for entry in entries))
        for function, symbol in clean.items():
            if function in symbols or symbol not in symbols:
                found.pop(function, None)  # (a Clean function named like a game symbol: as spelled)
            else:
                found[function] = "clean:" + found.get(symbol, "")
        users: dict[str, list[str]] = {}
        for name, label in found.items():
            users.setdefault(label, []).append(name)
        # two names that would stand for the same thing are both compared as they are spelled
        self.labels = {name: label for name, label in found.items() if len(users[label]) == 1}
        self.defined: dict[str, str] = {}
        self.memo: dict[str, str] = {}

    def of_plain(self, name: str) -> str | None:
        """What a C name stands for behind the prefixes the build puts before it, or None."""
        for before in PREFIXES:
            if name.startswith(before):
                label = self.labels.get(name[len(before):])
                if label is not None:
                    return f"{before}<{label}>"
        return None

    def add_definitions(self, shapes: list[dict]) -> None:
        """The names only the PC code has, each by the object that defines it: the object's shape
        and the name's number in it, when no other object has that shape and no other defines the
        name."""
        count: dict[str, int] = {}
        definers: dict[str, int] = {}
        for shape in shapes:
            count[shape["shape"]] = count.get(shape["shape"], 0) + 1
            for number in shape["defined"]:
                definers[shape["names"][number]] = definers.get(shape["names"][number], 0) + 1
        for shape in shapes:
            if count[shape["shape"]] != 1 or "flat" in shape:
                continue
            for number in shape["defined"]:
                name = shape["names"][number]
                if definers[name] == 1 and self.canon(name).startswith("="):
                    self.defined[name] = f"<defined:{shape['shape']}:{number}>"
        self.memo.clear()

    def canon(self, name: str) -> str:
        """A symbol's name as an object has it -> what it stands for, or `=name` as spelled."""
        out = self.memo.get(name)
        if out is None:
            out = self.defined.get(name)
            if out is None and name.startswith(self.prefix):
                out = self.of_plain(name[len(self.prefix):])
            if out is None:
                out = "=" + name
            self.memo[name] = out
        return out

    def text(self, text: str, c: bool = False) -> str:
        """An assembly file's text (or, with `c`, a C file's, whose names have no prefix) with
        every name that stands for something replaced by that."""
        def one(m: re.Match) -> str:
            out = self.canon(self.prefix + m[0] if c else m[0])
            return m[0] if out.startswith("=") else out
        return TOKEN.sub(one, text)


def object_hash(shape: dict, labels: Labels) -> str:
    """One object: its shape with what each of its external names stands for."""
    if "flat" in shape:
        rows = sorted(repr((labels.canon(name), *rest)) for name, *rest in shape["flat"])
        return hashlib.sha1(repr((shape["shape"], rows)).encode()).hexdigest()
    return hashlib.sha1(repr((shape["shape"], [labels.canon(n) for n in shape["names"]])).encode()).hexdigest()


def objects_part(groups: dict[str, list[dict]], labels: Labels) -> dict[str, str]:
    """A value for each group of objects (given in link order, the groups too): the objects'
    hashes in no order, and for each name more than one object defines (the linker keeps the
    first: a class's destructor in every file of the class), the hash of the first. A name
    defined in two groups counts for the later one."""
    hashes = {group: [object_hash(shape, labels) for shape in shapes] for group, shapes in groups.items()}
    first: dict[str, str] = {}
    again: dict[str, str] = {}  # label -> the last group that defines it again
    for group, shapes in groups.items():
        for shape, digest in zip(shapes, hashes[group]):
            for number in shape["defined"]:
                label = labels.canon(shape["names"][number])
                if label in first:
                    again[label] = group
                else:
                    first[label] = digest
    out = {}
    for group in groups:
        repeated = sorted((label, first[label]) for label, where in again.items() if where == group)
        out[group] = hashlib.sha1(repr((sorted(hashes[group]), repeated)).encode()).hexdigest()
    return out


def shapes_of(paths: list[pathlib.Path]) -> list[dict] | None:
    """coff_shape of each object, kept by the file's size and time (build/<version>/fingerprint);
    None when one is not a COFF object."""
    memo_path = C.BUILD / "fingerprint" / "shapes.json"
    try:
        memo = json.loads(memo_path.read_text())
        memo = memo["shapes"] if memo.get("format") == FORMAT else {}
    except (OSError, ValueError, KeyError):
        memo = {}
    out, kept = [], {}
    for path in paths:
        st = path.stat()
        stamp = [st.st_size, st.st_mtime_ns]
        entry = memo.get(str(path))
        if entry is None or entry[0] != stamp:
            shape = coff_shape(path.read_bytes())
            if shape is None:
                return None
            entry = [stamp, shape]
        kept[str(path)] = entry
        out.append(entry[1])
    memo_path.parent.mkdir(parents=True, exist_ok=True)
    memo.update(kept)
    memo_path.write_text(json.dumps({"format": FORMAT, "shapes": memo}), newline="\n")
    return out


def native_in_clean(policy: str, cleaned: set[tuple[str, int]]) -> list[str]:
    """The functions whose Native code can run in a run with every Clean function (`policy`, as
    tools/run.py writes it for one): those the policy lets run that have no Clean version. A
    function with one never runs its Native code there (the runtime sends every call of it to
    the Clean code), and one kept Reference runs the ROM's code in every run."""
    out = []
    for line in policy.splitlines():
        address, module, _size, status = line.split()[:4]
        if status in ("N", "C") and (module, int(address, 16) & ~1) not in cleaned:
            out.append(f"{module} {int(address, 16) & ~1:08x}")
    return out


def compute() -> dict:
    """{"parts": the parts of this tree, or None on a host whose objects are not COFF;
    "native_in_clean": see native_in_clean}. The Native objects are as tools/native.py left
    them; the Clean objects are built here, in tools/run.py's directory."""
    import run  # noqa: PLC0415 (its directory follows ACWW_RUNTIME_OUT)
    if not (run.NATIVE / "objects.txt").exists():
        raise SystemExit("run `python tools/native.py` first")
    table = run.write_clean_table("all")  # (and clean-profile.s, which build_clean assembles)
    listed = pathlib.Path(run.build_clean(run.runtime_flags())[0][1:])
    groups = {"native_objects": [pathlib.Path(p) for p in (run.NATIVE / "objects.txt").read_text().split()],
              "clean_objects": [pathlib.Path(p) for p in listed.read_text().split()]}
    shapes = {group: shapes_of(paths) for group, paths in groups.items()}
    syms = C.symbol_table(C.modules())
    table_names = {name: [(s.module, f"{s.address:08x}", s.kind, f"{s.size:x}", int(s.thumb)) for s in entries]
                   for name, entries in syms.by_name.items()}
    labels = Labels(table_names, {function: symbol for symbol, function, *_ in run.clean_registrations("all")},
                    "_" if run.WINDOWS else "")
    manifest, symbols = run.generate()
    policy = run.write_policy("all", "all").read_text()
    cleaned = ({(module, address & ~1) for _, module, address, _ in run.clean_checks("all")}
               | {(module, address & ~1) for _, _, module, address, _ in run.clean_registrations("all")})
    extra = {"native_in_clean": native_in_clean(policy, cleaned)}
    policy_clean = run.policy_facts(policy)
    policy_none = run.policy_facts(run.write_policy("all", None).read_text())
    if None in shapes.values():
        return {"parts": None, **extra}
    labels.add_definitions([shape for group in shapes.values() for shape in group])
    out = objects_part(shapes, labels)
    absolute = re.findall(r"^\t\.set (\S+), (0x[0-9a-f]{8})$", (run.NATIVE / "absolute.s").read_text(), re.M)

    def digest(*pieces: bytes) -> str:
        h = hashlib.sha1()
        for piece in pieces:
            h.update(f"{len(piece)}\0".encode() + piece)
        return h.hexdigest()
    out["native_tables"] = digest(
        labels.text((run.NATIVE / "natives.s").read_text()).encode(),
        "\n".join(sorted(f"{labels.canon(name)} {address}" for name, address in absolute)).encode(),
        policy_none, run.symbols_facts(symbols.read_text()), C.tree_free(manifest.read_text()).encode(),
        run.file_sha1(run.ROM).encode())
    out["clean_tables"] = digest(labels.text(table.read_text(), c=True).encode(), policy_clean)
    return {"parts": out, **extra}


# ------------------------------------------------------------------------------ records

def git(*args: str) -> str:
    return subprocess.run(["git", *args], cwd=C.ROOT, capture_output=True, text=True, check=True).stdout.strip()


def head() -> str | None:
    """The commit this tree is, or None when it has anything uncommitted (or is no checkout)."""
    try:
        return None if git("status", "--porcelain") else git("rev-parse", "HEAD")
    except (OSError, subprocess.CalledProcessError):
        return None


def record_path(commit: str) -> pathlib.Path:
    host = "windows" if sys.platform == "win32" else "linux"
    return C.CACHE_DIR / "fingerprint" / commit[:2] / f"{commit}-{C.VERSION}-{host}.json"


def load(commit: str) -> dict[str, str] | None:
    """The parts kept for `commit` (by a gate that passed on it), or None."""
    try:
        kept = json.loads(record_path(commit).read_text())
        return kept["parts"] if kept.get("format") == FORMAT else None
    except (OSError, ValueError, KeyError):
        return None


def record(commit: str, found: dict[str, str]) -> None:
    path = record_path(commit)
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_name(path.name + ".tmp")
    tmp.write_text(json.dumps({"format": FORMAT, "commit": commit, "parts": found}, indent=1) + "\n", newline="\n")
    tmp.replace(path)


def main() -> int:
    args = sys.argv[1:]
    commit = head()
    computed = compute()
    found = computed["parts"]
    if "--write" in args:
        out = pathlib.Path(args[args.index("--write") + 1])
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(json.dumps({"format": FORMAT, "commit": commit, **computed}, indent=1) + "\n", newline="\n")
    if found is None:
        print("fingerprint: none (the objects of this host are not COFF)")
        return 0
    for name, value in found.items():
        print(f"{name} {value}")
    print(f"fingerprint: {len(found)} parts of " + (commit[:12] if commit else "a tree with uncommitted changes"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
