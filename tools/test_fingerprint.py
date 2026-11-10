"""tools/fingerprint.py on made-up objects: what leaves an object's shape as it was (the time, the
source's name, the names of its own symbols, an external name spelled otherwise) and what
changes it; which names stand for the same thing in two trees; and that two programs compare
equal exactly when one is the other with names changed one for one."""
from __future__ import annotations

import pathlib
import struct
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import fingerprint as F  # noqa: E402

TEXT, DATA = 0x60500020, 0xC0300040
REL32, DIR32 = 0x14, 0x06


def coff(sections: list[tuple], symbols: list[tuple], stamp: int = 0) -> bytes:
    """An i386 COFF object. sections: (name, bytes, flags, [(offset, symbol, type)]); symbols:
    (name, value, section, storage) or (name, value, section, storage, aux bytes); a relocation
    names its symbol by its place in `symbols`."""
    strings = bytearray()

    def name8(name: str, section: bool) -> bytes:
        raw = name.encode("latin-1")
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        offset = 4 + len(strings)
        strings.extend(raw + b"\0")
        return f"/{offset}".encode().ljust(8, b"\0") if section else struct.pack("<II", 0, offset)
    index, at = [], 0
    for symbol in symbols:  # (an auxiliary record takes a place of its own)
        index.append(at)
        at += 1 + (len(symbol[4]) // 18 if len(symbol) > 4 else 0)
    where = 20 + 40 * len(sections)
    headers, bodies = b"", b""
    for name, body, flags, relocations in sections:
        table = b"".join(struct.pack("<IIH", offset, index[symbol], how) for offset, symbol, how in relocations)
        headers += name8(name, True) + struct.pack("<IIIIIIHHI", 0, 0, len(body), where if body else 0,
                                                   where + len(body) if table else 0, 0, len(relocations), 0, flags)
        bodies += body + table
        where += len(body) + len(table)
    records = b""
    for symbol in symbols:
        name, value, section, storage = symbol[:4]
        aux = symbol[4] if len(symbol) > 4 else b""
        records += name8(name, False) + struct.pack("<IhHBB", value, section, 0x20 if section > 0 else 0, storage,
                                                    len(aux) // 18) + aux
    header = struct.pack("<HHIIIHH", 0x14C, len(sections), stamp, where, at, 0, 0)
    return header + headers + bodies + records + struct.pack("<I", 4 + len(strings)) + bytes(strings)


def caller(defines: str, calls: str, helper: str = "_helper", code: bytes = b"\xe8\0\0\0\0\xc3", stamp: int = 0,
           section: str = ".text", source: str = "one.c", reads: str | None = None) -> bytes:
    """An object that defines `defines` (a call to `calls`, then to its own `helper`)."""
    relocations = [(1, 3, REL32), (7, 1, REL32)] + ([(12, 4, DIR32)] if reads else [])
    symbols = [(".file", 0, -2, 103, source.encode().ljust(18, b"\0")), (helper, 8, 1, 3), (defines, 0, 1, 2),
               (calls, 0, 0, 2)] + ([(reads, 0, 0, 2)] if reads else [])
    return coff([(section, code + b"\xe8\0\0\0\0\xc3\x90\x90" + b"\xa1\0\0\0\0", TEXT, relocations)], symbols, stamp)


def shape(data: bytes) -> dict:
    out = F.coff_shape(data)
    assert out is not None
    return out


def check_shapes() -> list[str]:
    bad = []
    base = caller("_native_alpha", "_native_beta")

    def same(what: str, other: bytes, want: bool = True) -> None:
        if (shape(base)["shape"] == shape(other)["shape"]) != want:
            bad.append(f"{what}: the shape {'changed' if want else 'stayed'}")
    same("another time", caller("_native_alpha", "_native_beta", stamp=77))
    same("another source name", caller("_native_alpha", "_native_beta", source="two.c"))
    same("its own helper renamed", caller("_native_alpha", "_native_beta", helper="_helper_with_a_long_name"))
    same("externals renamed", caller("_native_first", "_native_second_with_a_long_name"))
    same("a function's section renamed", caller("_native_alpha", "_native_beta", section=".text$b"), False)
    if shape(caller("_native_alpha", "_native_beta", section=".text$a"))["shape"] != shape(
            caller("_native_alpha", "_native_beta", section=".text$b"))["shape"]:
        bad.append("the name after `.text$` is in the shape")
    if shape(caller("_native_alpha", "_native_beta", section=".CRT$XCA"))["shape"] == shape(
            caller("_native_alpha", "_native_beta", section=".CRT$XCU"))["shape"]:
        bad.append("the name after `.CRT$` is not in the shape")
    same("a byte of code", caller("_native_alpha", "_native_beta", code=b"\xe8\0\0\0\0\xc2"), False)
    same("another reference", caller("_native_alpha", "_native_beta", reads="_data_1"), False)
    got = shape(base)
    if got["names"] != ["_native_beta", "_native_alpha"] or got["defined"] != [1]:
        bad.append(f"names {got['names']}, defined {got['defined']}")
    # one external used twice against two externals used once each
    one = coff([(".text", bytes(10), TEXT, [(1, 0, REL32), (6, 0, REL32)])], [("_a", 0, 0, 2), ("_b", 0, 0, 2)])
    two = coff([(".text", bytes(10), TEXT, [(1, 0, REL32), (6, 1, REL32)])], [("_a", 0, 0, 2), ("_b", 0, 0, 2)])
    if shape(one)["shape"] == shape(two)["shape"]:
        bad.append("which external a relocation names is not in the shape")
    if F.coff_shape(b"\x7fELF" + bytes(60)) is not None or F.coff_shape(b"") is not None:
        bad.append("something that is no COFF object was read")
    # symbols only (as absolute.s gives): in any order
    first = coff([(".text", b"", TEXT, [])], [("_a", 0x02000000, -1, 2), ("_b", 0x02000010, -1, 2)])
    second = coff([(".text", b"", TEXT, [])], [("_b", 0x02000010, -1, 2), ("_a", 0x02000000, -1, 2)])
    moved = coff([(".text", b"", TEXT, [])], [("_a", 0x02000000, -1, 2), ("_b", 0x02000014, -1, 2)])
    labels = F.Labels({}, {}, "_")
    if F.object_hash(shape(first), labels) != F.object_hash(shape(second), labels):
        bad.append("symbols placed in another order compare different")
    if F.object_hash(shape(first), labels) == F.object_hash(shape(moved), labels):
        bad.append("a symbol placed elsewhere compares the same")
    return bad


def table(**names: int) -> dict[str, list[tuple]]:
    return {name: [("main", f"{address:08x}", "function", "10", 0)] for name, address in names.items()}


def check_labels() -> list[str]:
    bad = []
    old = F.Labels(table(alpha=0x100, beta=0x200, twin_a=0x300, twin_b=0x300), {"Alpha_Run": "alpha", "Twin_Run": "twin_a"}, "_")
    new = F.Labels(table(first=0x100, beta=0x200, twin_a=0x300, twin_b=0x300), {"Alpha_Start": "first", "Twin_Run": "twin_a"}, "_")
    for what, a, b, want in (
            ("a symbol renamed in the table", "_native_alpha", "_native_first", True),
            ("its body", "_native_body_alpha", "_native_body_first", True),
            ("its plain name", "_alpha", "_first", True),
            ("the Native and the plain name", "_native_alpha", "_first", False),
            ("another symbol", "_native_alpha", "_native_beta", False),
            ("a Clean function renamed", "_Alpha_Run", "_Alpha_Start", True),
            ("a Clean function's body", "_native_body_Alpha_Run", "_native_body_Alpha_Start", True),
            ("a Clean function and its game function", "_Alpha_Run", "_first", False),
            ("a check", "_diff_test_alpha", "_diff_test_first", True),
            ("the runtime's name", "_native_guest_enter", "_native_guest_enter", True),
            ("two runtime names", "_memcpy", "_memmove", False),
            ("a name without the prefix", "alpha", "first", False)):
        if (old.canon(a) == new.canon(b)) != want:
            bad.append(f"{what}: {a} and {b} compare {'different' if want else 'the same'}")
    # two symbols at one address stand for the same: each is compared as it is spelled
    if old.canon("_twin_a") != "=_twin_a" or old.canon("_twin_a") == old.canon("_twin_b"):
        bad.append(f"two symbols at one address: {old.canon('_twin_a')}, {old.canon('_twin_b')}")
    both = F.Labels(table(alpha=0x100), {"One_Run": "alpha", "Two_Run": "alpha"}, "_")
    if both.canon("_One_Run") != "=_One_Run":
        bad.append("two Clean functions registered for one function stand for the same")
    shadow = F.Labels(table(alpha=0x100, beta=0x200), {"beta": "alpha"}, "_")
    if shadow.canon("_beta") != "=_beta":
        bad.append("a Clean function named like a game symbol was not compared as spelled")
    line = "\t.long 0x02000101, 0x10, _native_alpha, 0x00000015\n\tjmp _native_call_beta\n\tcall _memcpy\n"
    if old.text(line) != new.text(line.replace("alpha", "first")) or "_memcpy" not in old.text(line):
        bad.append(f"an assembly line: {old.text(line)!r}")
    row = "    {0x02000101u, 0x10u, (const void *) Alpha_Run, 0x00000015u},\n"
    if old.text(row, c=True) != new.text(row.replace("Alpha_Run", "Alpha_Start"), c=True) or "Alpha" in old.text(row, c=True):
        bad.append(f"a C line: {old.text(row, c=True)!r}")
    return bad


def program(labels: F.Labels, native: list[bytes], clean: list[bytes]) -> dict[str, str]:
    shapes = {"native_objects": [shape(o) for o in native], "clean_objects": [shape(o) for o in clean]}
    labels.add_definitions([s for group in shapes.values() for s in group])
    return F.objects_part(shapes, labels)


def check_programs() -> list[str]:
    bad = []

    def old() -> F.Labels:
        return F.Labels(table(alpha=0x100, beta=0x200, gamma=0x300), {"Alpha_Run": "alpha"}, "_")

    def new() -> F.Labels:
        return F.Labels(table(first=0x100, beta=0x200, gamma=0x300), {"Alpha_Start": "first"}, "_")
    helper = coff([(".text", b"\x31\xc0\xc3", TEXT, [])], [("_Helper_Sum", 0, 1, 2)])
    helper_renamed = coff([(".text", b"\x31\xc0\xc3", TEXT, [])], [("_Helper_Add", 0, 1, 2)])
    native = [caller("_native_alpha", "_native_beta"), caller("_native_beta", "_native_call_gamma", code=b"\xe8\0\0\0\0\x90")]
    clean = [caller("_native_body_Alpha_Run", "_Helper_Sum", code=b"\xe8\0\0\0\0\xcc", reads="_alpha"), helper]
    base = program(old(), native, clean)
    renamed_native = [caller("_native_first", "_native_beta"), caller("_native_beta", "_native_call_gamma", code=b"\xe8\0\0\0\0\x90")]
    renamed_clean = [caller("_native_body_Alpha_Start", "_Helper_Add", code=b"\xe8\0\0\0\0\xcc", reads="_first"), helper_renamed]

    def same(what: str, got: dict[str, str], native_same: bool = True, clean_same: bool = True) -> None:
        if (got["native_objects"] == base["native_objects"]) != native_same or (
                got["clean_objects"] == base["clean_objects"]) != clean_same:
            bad.append(f"{what}: native {'same' if got['native_objects'] == base['native_objects'] else 'different'}, "
                       f"clean {'same' if got['clean_objects'] == base['clean_objects'] else 'different'}")
    same("renamed throughout", program(new(), renamed_native, renamed_clean))
    same("the objects in another order", program(new(), renamed_native[::-1], renamed_clean[::-1]))
    same("a Native object calls another function", program(
        new(), [caller("_native_first", "_native_call_gamma"), renamed_native[1]], renamed_clean), native_same=False)
    same("a Clean object reads another symbol", program(new(), renamed_native, [caller(
        "_native_body_Alpha_Start", "_Helper_Add", code=b"\xe8\0\0\0\0\xcc", reads="_beta"), helper_renamed]), clean_same=False)
    same("a Clean object's code", program(new(), renamed_native, [caller(
        "_native_body_Alpha_Start", "_Helper_Add", code=b"\xe8\0\0\0\0\xc3", reads="_first"), helper_renamed]), clean_same=False)
    same("a name of the table renamed in the sources alone", program(old(), renamed_native, clean), native_same=False)
    same("the helper's code", program(new(), renamed_native, [renamed_clean[0], coff(
        [(".text", b"\x31\xc9\xc3", TEXT, [])], [("_Helper_Add", 0, 1, 2)])]), clean_same=False)
    # a helper whose object has a twin of the same shape is compared as spelled
    twin = coff([(".text", b"\x31\xc0\xc3", TEXT, [])], [("_Helper_Other", 0, 1, 2)])
    with_twin = program(old(), native, [*clean, twin])
    if with_twin["clean_objects"] == program(new(), renamed_native, [*renamed_clean, twin])["clean_objects"]:
        bad.append("a helper renamed beside a twin of its object's shape compares the same")
    if with_twin["clean_objects"] != program(new(), renamed_native, [renamed_clean[0].replace(b"_Helper_Add", b"_Helper_Sum"),
                                                                      helper, twin])["clean_objects"]:
        bad.append("a helper not renamed beside a twin compares different")
    # one name defined twice, differently: the linker keeps the first, so the order counts
    one, other = (coff([(".text", code, TEXT, [])], [("_shared", 0, 1, 2)]) for code in (b"\xc3", b"\x90\xc3"))
    if program(old(), [*native, one, other], clean)["native_objects"] == program(old(), [*native, other, one], clean)["native_objects"]:
        bad.append("two definitions of a name in another order compare the same")
    return bad


def main() -> int:
    bad = check_shapes() + check_labels() + check_programs()
    for line in bad:
        print(f"FAIL: {line}")
    print("fingerprint: shapes, names and programs: " + ("FAIL" if bad else "ok"))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
