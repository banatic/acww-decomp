"""Short declarations whose missing arguments the ROM's callee never reads.

A source that declares a function with fewer parameters than its definition leaves the other
argument registers as the DS holds them; the PC passes nothing there. tools/native.py keeps
such a source Reference, unless the callee's ROM code never reads those registers: then
neither the DS's leftovers nor the PC's matter. UNREAD holds that fact per ROM function, as
`python tools/native_args.py --audit` derives it from the ROM's code (with capstone, which
only the audit needs): an argument register is read when an instruction uses the value it
held at entry, a call is made while it still holds it (and the callee reads it in turn), or
it is returned in r0. A function whose code the audit cannot follow (a computed jump, a call
into the middle of other code) has no entry.

A declaration with a result whose definition returns nothing is harmless when the definition
is a library function: library code always runs as the ROM's code, and the PC's call into it
(runtime/native_tramp.S) hands back r0 as the ROM's code left it, which the ROM's caller uses
too.
"""
from __future__ import annotations

import argparse
import collections
import functools
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

# (module, address) -> argument registers r0-r3 (bit k for rk) the ROM's code never reads
UNREAD = {
    ("ov065", 0x0227E67C): 0b1111,  # func_ov065_0227e67c: stores to stOptSCBlock, returns its address
    ("ov065", 0x0227F22C): 0b1111,  # func_ov065_0227f22c: loads stpInetCntl into r0 first
    ("ov065", 0x0227F380): 0b1111,  # func_ov065_0227f380
    ("autoload_2", 0x02107CD4): 0b1110,  # NNS_G3dGetVisAnmSet: sets r1, r2; its callee takes three
    ("ov002", 0x0220B71C): 0b1111,  # func_ov002_0220b71c: calls func_020682e0(1) first
    ("ov009", 0x02264C40): 0b1111,  # func_ov009_02264c40
}


def library(defining: str) -> bool:
    """Whether a definition (protos.disagreements' defining source) is library code."""
    return defining == "libs" or defining.startswith("libs/")


def harmless(syms: C.SymbolTable, module: str, callee: str, declared: int | None, defined: int | None,
             result: bool, defined_result: bool | None, defining: str) -> bool:
    """Whether a declaration of `callee` in a source of `module` that disagrees with the
    definition (protos.disagreements) still gives the PC's code the ROM's arguments and
    result."""
    if result and not defined_result and not library(defining):
        return False
    if declared is not None and defined is not None and declared < defined:
        if defined > 4:
            return False
        sym = syms.lookup(callee, module)
        if sym is None or sym.kind != "function":
            return False
        missing = sum(1 << k for k in range(declared, defined))
        if UNREAD.get((sym.module, sym.address), 0) & missing != missing:
            return False
    return True


# ------------------------------------------------------------------------------ the audit


SUFFIXES: dict[int, tuple[str, ...]] = {}


class Unfollowed(Exception):
    """Code the audit cannot follow."""


def _audit_tools():
    import capstone  # noqa: F401  (the audit only)
    from capstone import arm as A
    return capstone, A


class Rom:
    def __init__(self):
        self.cs, self.A = _audit_tools()
        A = self.A
        SUFFIXES.update({A.ARM_CC_EQ: ("eq",), A.ARM_CC_NE: ("ne",), A.ARM_CC_HS: ("hs", "cs"), A.ARM_CC_LO: ("lo", "cc"),
                         A.ARM_CC_MI: ("mi",), A.ARM_CC_PL: ("pl",), A.ARM_CC_VS: ("vs",), A.ARM_CC_VC: ("vc",),
                         A.ARM_CC_HI: ("hi",), A.ARM_CC_LS: ("ls",), A.ARM_CC_GE: ("ge",), A.ARM_CC_LT: ("lt",),
                         A.ARM_CC_GT: ("gt",), A.ARM_CC_LE: ("le",)})
        self.mods = C.modules()
        self.syms = C.SymbolTable(self.mods)
        self.images: dict[str, bytes] = {}

    def image(self, mod: str) -> bytes:
        if mod not in self.images:
            self.images[mod] = C.module_image(mod)
        return self.images[mod]

    def function(self, mod: str, address: int):
        for m in [mod, *C.RESIDENT]:
            s = self.syms.function(m, address & ~1)
            if s is not None:
                return s
        return None

    @functools.lru_cache(None)
    def code(self, mod: str, address: int, size: int, thumb: bool):
        cs = self.cs
        base = self.mods[mod]["base"]
        data = self.image(mod)[address - base:address - base + size]
        md = cs.Cs(cs.CS_ARCH_ARM, cs.CS_MODE_THUMB if thumb else cs.CS_MODE_ARM)
        md.detail = True
        out, off = [], 0
        while off < len(data):
            got = list(md.disasm(data[off:], address + off, 1))
            out.append(got[0] if got else None)
            off += got[0].size if got else (2 if thumb else 4)
        return out

    def reg(self, ins, r) -> int | None:
        n = ins.reg_name(r)
        n = {"sb": "r9", "sl": "r10", "fp": "r11", "ip": "r12"}.get(n, n)
        return int(n[1:]) if n[0] == "r" and n[1:].isdigit() else None

    def literal(self, mod: str, thumb: bool, ins) -> int | None:
        """The word `ldr rd, [pc, #x]` loads."""
        A = self.A
        if ins.mnemonic.split(".")[0] != "ldr" or len(ins.operands) != 2:
            return None
        o = ins.operands[1]
        if o.type != A.ARM_OP_MEM or ins.reg_name(o.mem.base) != "pc" or o.mem.index != 0:
            return None
        a = ((ins.address + 4) & ~3 if thumb else ins.address + 8) + o.mem.disp
        base = self.mods[mod]["base"]
        return int.from_bytes(self.image(mod)[a - base:a - base + 4], "little")

    def conditional(self, ins) -> bool:
        return ins.cc not in (self.A.ARM_CC_AL, self.A.ARM_CC_INVALID)

    def mnemonic(self, ins) -> str:
        """The mnemonic without its condition (`bne` -> `b`, `movne` -> `mov`)."""
        m = ins.mnemonic.split(".")[0]
        if self.conditional(ins):
            for suffix in SUFFIXES.get(ins.cc, ()):
                if m.endswith(suffix):
                    return m[:-len(suffix)]
        return m

    @functools.lru_cache(None)
    def reads(self, mod: str, address: int, depth: int = 0) -> frozenset[int]:
        """The argument registers r0-r3 whose entry values the function's code reads."""
        s = self.function(mod, address)
        if s is None or s.address != address & ~1:
            raise Unfollowed(f"no function starts at {address:08x}")
        if depth > 8:
            raise Unfollowed("calls nested too deep")
        code = self.code(s.module, s.address, s.size, s.thumb)
        index = {ins.address: k for k, ins in enumerate(code) if ins is not None}
        end = s.address + s.size
        used: set[int] = set()
        entry = tuple(frozenset([r]) if r < 4 else frozenset() for r in range(15))
        states = {s.address: entry}
        work = [s.address]
        visits: collections.Counter = collections.Counter()

        def join(target: int, state: tuple) -> None:
            if target not in index:
                raise Unfollowed(f"branch to {target:08x}")
            old = states.get(target)
            new = state if old is None else tuple(a | b for a, b in zip(old, state))
            if new != old:
                states[target] = new
                work.append(target)

        def call(state: list, target: int | None) -> None:
            if target is None:
                for r in range(4):
                    used.update(state[r])
                return
            if not any(state[r] for r in range(4)):
                return  # no argument register holds an entry value any more
            callee = self.function(s.module, target)
            try:
                if callee is None or callee.address != target & ~1:
                    raise Unfollowed(f"call to {target:08x}")
                read = self.reads(callee.module, callee.address | int(callee.thumb), depth + 1)
            except Unfollowed:
                read = range(4)  # a callee the audit cannot follow reads all four
            for r in read:
                used.update(state[r])

        while work:
            at = work.pop()
            visits[at] += 1
            if visits[at] > 100:
                raise Unfollowed("no fixed point")
            state = list(states[at])
            k = index[at]
            while True:
                ins = code[k] if k < len(code) else None
                if ins is None:
                    raise Unfollowed("runs into data")
                m = self.mnemonic(ins)
                cond = self.conditional(ins)
                imm = ins.operands[-1].imm if ins.operands and ins.operands[-1].type == self.A.ARM_OP_IMM else None
                reads_, writes = ins.regs_access()
                reads_ = [r for r in (self.reg(ins, x) for x in reads_) if r is not None]
                writes = [r for r in (self.reg(ins, x) for x in writes) if r is not None]
                stop = False
                first = ins.op_str.split(",")[0].strip()
                if m in ("bl", "blx"):
                    if imm is None:
                        for r in reads_:
                            used.update(state[r])
                    call(state, imm)
                    for r in (0, 1, 2, 3, 12, 14):
                        state[r] = frozenset()
                elif m == "b" and imm is not None:
                    if s.address <= imm < end:
                        join(imm, tuple(state))
                    else:
                        call(state, imm)
                    stop = not cond
                elif m == "bx" and first == "lr" or m in ("pop", "ldm", "ldmia", "ldmfd") and "pc" in ins.op_str \
                        or m == "ldr" and first == "pc" or m == "mov" and ins.op_str.replace(" ", "") == "pc,lr":
                    used.update(state[0])
                    stop = not cond
                elif m == "bx":
                    how, target = self._bx(s, code, k)
                    if how == "return":
                        used.update(state[0])
                    elif how == "tail":
                        call(state, target)
                    else:
                        raise Unfollowed(f"computed jump at {ins.address:08x}")
                    stop = not cond
                elif 15 in writes:
                    raise Unfollowed(f"computed jump at {ins.address:08x}")
                elif m in ("mov", "movs") and len(ins.operands) == 2 and ins.operands[1].type == self.A.ARM_OP_REG \
                        and ins.operands[1].shift.type == 0:
                    src, dst = self.reg(ins, ins.operands[1].reg), self.reg(ins, ins.operands[0].reg)
                    if m == "movs":
                        used.update(state[src])
                    state[dst] = state[dst] | state[src] if cond else state[src]
                else:
                    if m in ("cbz", "cbnz"):
                        raise Unfollowed("cbz")
                    for r in reads_:
                        if r < 15:
                            used.update(state[r])
                    for r in writes:
                        if r < 15 and not cond:
                            state[r] = frozenset()
                if stop:
                    break
                nxt = ins.address + ins.size
                if nxt >= end or nxt not in index:
                    raise Unfollowed("runs past its end")
                k = index[nxt]
        return frozenset(used)

    def _bx(self, s, code, k):
        """`bx rN`: a return when rN was just popped (Thumb's pop {rN}; bx rN), a tail call
        when it was loaded from the literal pool."""
        ins = code[k]
        rn = self.reg(ins, ins.operands[0].reg)
        for j in range(k - 1, -1, -1):
            p = code[j]
            if p is None:
                break
            pm = self.mnemonic(p)
            if pm in ("b", "bl", "blx", "bx"):
                break
            if rn in [self.reg(p, r) for r in p.regs_access()[1]]:
                if pm == "pop":
                    return "return", None
                word = self.literal(s.module, s.thumb, p)
                if word is not None and not self.conditional(p):
                    return "tail", word
                return None, None
        return None, None


def audit() -> list[str]:
    """The UNREAD entries the current sources' short declarations need, from the ROM."""
    import native as native_build  # noqa: F401
    import protos
    rom = Rom()
    out = []
    for rel, callee, n, dn, ret, dret, drel in protos.disagreements():
        if not rel.startswith("src/") or n is None or dn is None or n >= dn or dn > 4:
            continue
        src = C.parse_source(C.ROOT / rel)
        sym = rom.syms.lookup(callee, src.module)
        if sym is None:
            out.append(f"# {rel}: {callee}: no symbol")
            continue
        try:
            read = rom.reads(sym.module, sym.address | int(sym.thumb))
        except Unfollowed as e:
            out.append(f"# {rel}: {callee}: not followed ({e})")
            continue
        mask = sum(1 << k for k in range(4) if k not in read)
        out.append(f'("{sym.module}", 0x{sym.address:08X}): 0b{mask:04b},  # {callee}, declared with {n} of {dn} in {rel}')
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--audit", action="store_true", help="derive UNREAD from the ROM (needs capstone)")
    args = parser.parse_args()
    if args.audit:
        print("\n".join(audit()))


if __name__ == "__main__":
    main()
