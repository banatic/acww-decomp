"""Point a Native object's references at the game's memory.

A Native object (tools/native.py) refers to functions and data by the names the symbol table
has. On the DS, a name is an address in the game's memory, and Native code has to agree with
the ROM's code about every one of them: a function pointer it stores, a vtable it installs and
a global it writes must be the DS's, or the ROM's code reading them later goes wrong. Only a
direct call may go straight to another Native function.

So every reference is rewritten by its kind:
- a branch (`call`/`jmp`, a PC-relative relocation) to a function with a Native definition
  goes to that definition, renamed `native_<name>`;
- every other reference to a name the symbol table has (an address loaded, stored or used to
  call through) goes to the plain name, which absolute.s places at its DS address;
- a definition of such a name in the object is renamed to `native_<name>`, so the plain name
  always means the DS's.

COFF (32-bit Windows objects) and ELF (32-bit x86 Linux objects) are handled.
"""

from __future__ import annotations

import struct

NATIVE = "native_"
# Functions whose definition is renamed `native_body_<name>`: tools/native.py puts a wrapper
# under `native_<name>` that widens their narrow result (see native.py, WIDEN).
BODY: set[str] = set()

# relocation types meaning "relative branch target"
COFF_REL32 = 0x14
ELF_R_386_PC32 = 2
ELF_R_386_PLT32 = 4


class Strings:
    """A string table that can grow."""

    def __init__(self, data: bytes, base: int):
        self.data = bytearray(data)
        self.base = base

    def get(self, offset: int) -> str:
        end = self.data.index(b"\0", offset - self.base)
        return self.data[offset - self.base:end].decode("latin-1")

    def add(self, name: str) -> int:
        offset = self.base + len(self.data)
        self.data += name.encode("latin-1") + b"\0"
        return offset


def rewrite_coff(data: bytes, known: set[str], native: set[str], prefix: str) -> tuple[bytes, set[str]]:
    """`known`: plain names the symbol table has; `native`: the plain names of functions with
    a Native definition anywhere. Names in the object carry `prefix` ("_" on i386). Returns
    the new object and the known names it now refers to by their DS address."""
    machine, nsec, stamp, symptr, nsym, opt, chars = struct.unpack_from("<HHIIIHH", data, 0)
    if machine != 0x14C:
        raise ValueError("not an i386 COFF object")
    out = bytearray(data[:symptr])
    strsize, = struct.unpack_from("<I", data, symptr + 18 * nsym)
    strings = Strings(data[symptr + 18 * nsym + 4:symptr + 18 * nsym + strsize], 4)

    def plain(sym_name: str) -> str | None:
        return sym_name[len(prefix):] if sym_name.startswith(prefix) else None

    symbols = []  # (raw record, name)
    i = 0
    while i < nsym:
        raw = bytearray(data[symptr + 18 * i:symptr + 18 * (i + 1)])
        if raw[:4] == b"\0\0\0\0":
            name = strings.get(struct.unpack_from("<I", raw, 4)[0])
        else:
            name = raw[:8].rstrip(b"\0").decode("latin-1")
        aux = raw[17]
        symbols.append((raw, name))
        for k in range(aux):
            symbols.append((bytearray(data[symptr + 18 * (i + 1 + k):symptr + 18 * (i + 2 + k)]), None))
        i += 1 + aux

    def set_name(raw: bytearray, name: str) -> None:
        raw[0:8] = struct.pack("<II", 0, strings.add(name))

    extra: dict[str, int] = {}

    def symbol_for(name: str) -> int:
        """Index of an undefined external symbol `name`, added if needed."""
        if name not in extra:
            raw = bytearray(18)
            set_name(raw, name)
            struct.pack_into("<IhHBB", raw, 8, 0, 0, 0x20 if name.startswith(prefix + NATIVE) else 0, 2, 0)
            extra[name] = len(symbols)
            symbols.append((raw, name))
        return extra[name]

    # A C++ source's static initializer is the game's own (its __sinit), which the ROM's code
    # calls when it starts the module; the PC must not run it when the program starts, before
    # the DS memory it writes exists. Its .CRT$XC* entry (the table the C runtime runs)
    # becomes a section of another name, which the C runtime does not see.
    for s in range(nsec):
        hdr = 20 + opt + 40 * s
        raw_name = bytes(out[hdr:hdr + 8])
        if raw_name.startswith(b"/"):
            at = int(raw_name[1:].rstrip(b"\0")) - 4
            name = bytes(strings.data[at:at + 8])
            if name.startswith(b".CRT$XC") or name.startswith(b".ctors"):
                strings.data[at + 1] = ord("x")
        elif raw_name.startswith(b".CRT$XC") or raw_name.startswith(b".ctors"):
            out[hdr + 1] = ord("x")

    # definitions of known names become native$ names
    renamed: dict[int, str] = {}
    for idx, (raw, name) in enumerate(symbols):
        if name is None:
            continue
        section, = struct.unpack_from("<h", raw, 12)
        storage = raw[16]
        p = plain(name)
        if storage == 2 and section > 0 and p in known:
            set_name(raw, prefix + NATIVE + ("body_" if p in BODY else "") + p)
            renamed[idx] = p

    # relocations
    for s in range(nsec):
        hdr = 20 + opt + 40 * s
        relptr, nrel = struct.unpack_from("<I", data, hdr + 24)[0], struct.unpack_from("<H", data, hdr + 32)[0]
        for r in range(nrel):
            off = relptr + 10 * r
            vaddr, symidx, rtype = struct.unpack_from("<IIH", data, off)
            raw, name = symbols[symidx]
            p = renamed.get(symidx) or plain(name or "")
            if p is None or p not in known:
                continue
            if rtype == COFF_REL32 and p in native:
                target = symidx if symidx in renamed else symbol_for(prefix + NATIVE + p)
            else:
                target = symbol_for(prefix + p)
            struct.pack_into("<I", out, off + 4, target)

    body = b"".join(bytes(raw) for raw, _ in symbols)
    struct.pack_into("<I", out, 8, len(out))  # PointerToSymbolTable
    struct.pack_into("<I", out, 12, len(symbols))  # NumberOfSymbols
    table = bytes(strings.data)
    to_ds = {n[len(prefix):] for n in extra if not n.startswith(prefix + NATIVE)}
    return bytes(out) + body + struct.pack("<I", len(table) + 4) + table, to_ds


def rewrite_elf(data: bytes, known: set[str], native: set[str]) -> tuple[bytes, set[str]]:
    """The same for a 32-bit x86 ELF relocatable object (no name prefix there). The symbol and
    string tables grow, so they and the section header table are written again at the end."""
    if data[4] != 1 or data[5] != 1 or struct.unpack_from("<H", data, 18)[0] != 3:
        raise ValueError("not a 32-bit little-endian x86 ELF object")
    shoff, = struct.unpack_from("<I", data, 0x20)
    shentsize, shnum = struct.unpack_from("<HH", data, 0x2E)
    sections = [list(struct.unpack_from("<10I", data, shoff + i * shentsize)) for i in range(shnum)]
    symtab_index = next(i for i, s in enumerate(sections) if s[1] == 2)
    symtab = sections[symtab_index]
    strtab = sections[symtab[6]]
    strings = Strings(data[strtab[4]:strtab[4] + strtab[5]], 0)
    symbols = [bytearray(data[symtab[4] + 16 * i:symtab[4] + 16 * (i + 1)]) for i in range(symtab[5] // 16)]
    out = bytearray(data)

    # A C++ source's static initializer is the game's own (its __sinit), which the ROM's code
    # calls when it starts the module; the PC must not run it when the program starts, before
    # the DS memory it writes exists. Its .init_array entry becomes plain data under another
    # name, which the linker does not collect.
    shstrndx, = struct.unpack_from("<H", data, 0x32)
    for s in sections:
        if s[1] in (14, 15, 16):  # SHT_INIT_ARRAY, SHT_FINI_ARRAY, SHT_PREINIT_ARRAY
            s[1] = 1  # SHT_PROGBITS
            out[sections[shstrndx][4] + s[0]] = ord("x")  # ".init_array" -> "xinit_array"
            if shstrndx == symtab[6]:
                strings.data[s[0]] = ord("x")

    def name_of(raw: bytearray) -> str:
        return strings.get(struct.unpack_from("<I", raw, 0)[0])

    extra: dict[str, int] = {}

    def symbol_for(name: str) -> int:
        if name not in extra:
            info = (1 << 4) | (2 if name.startswith(NATIVE) else 0)  # global; a function or nothing
            extra[name] = len(symbols)
            symbols.append(bytearray(struct.pack("<IIIBBH", strings.add(name), 0, 0, info, 0, 0)))
        return extra[name]

    renamed: dict[int, str] = {}
    for idx, raw in enumerate(symbols):
        bind, shndx = raw[12] >> 4, struct.unpack_from("<H", raw, 14)[0]
        name = name_of(raw)
        if bind in (1, 2) and shndx not in (0, 0xFFF1) and name in known:
            struct.pack_into("<I", raw, 0, strings.add(NATIVE + ("body_" if name in BODY else "") + name))
            renamed[idx] = name

    for s in sections:
        if s[1] != 9 or s[6] != symtab_index:  # SHT_REL against this symbol table
            continue
        for off in range(s[4], s[4] + s[5], 8):
            r_info, = struct.unpack_from("<I", data, off + 4)
            symidx, rtype = r_info >> 8, r_info & 0xFF
            name = renamed.get(symidx) or name_of(symbols[symidx])
            if name not in known:
                continue
            if rtype in (ELF_R_386_PC32, ELF_R_386_PLT32) and name in native:
                target = symidx if symidx in renamed else symbol_for(NATIVE + name)
            else:
                target = symbol_for(name)
            struct.pack_into("<I", out, off + 4, (target << 8) | rtype)

    # the grown tables and a new section header table go at the end
    def place(blob: bytes, align: int = 4) -> int:
        while len(out) % align:
            out.append(0)
        at = len(out)
        out.extend(blob)
        return at

    table = bytes(strings.data)
    strtab[4], strtab[5] = place(table, 1), len(table)
    body = b"".join(bytes(raw) for raw in symbols)
    symtab[4], symtab[5] = place(body), len(body)
    struct.pack_into("<I", out, 0x20, place(b"".join(struct.pack("<10I", *s) for s in sections)))
    return bytes(out), {n for n in extra if not n.startswith(NATIVE)}


def rewrite(data: bytes, known: set[str], native: set[str], prefix: str) -> tuple[bytes, set[str]]:
    if data[:4] == b"\x7fELF":
        return rewrite_elf(data, known, native)
    return rewrite_coff(data, known, native, prefix)
