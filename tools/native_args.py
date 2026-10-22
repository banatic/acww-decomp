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
import hashlib
import pathlib
import re
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


# ------------------------------------------------------------------------------ PC copies

# Sources that call a function with fewer arguments than it reads, where the ROM's call leaves
# a value the source names in the missing argument registers: source (under src/) ->
# (SHA-256 of the source, the callee, what the ROM's call has in the next argument registers,
# as names in the source). The PC copy declares the callee with those arguments too and
# passes them, so the PC's callee gets what the ROM's gets. A name that is a parameter must not
# be assigned in the source (the ROM's register still holds the incoming value).
PASSED = {
    # ROM 0200c8c2-0200c8c8: r0 and r1 reach the bl to func_020778b0 (MI_CpuCopy8(&b, a, 2))
    # as they came in; only r2 and r3 are saved first
    "main/func_0200c8c0.c": ("e10b62af5d672fa487cb16708bd3ca12541cd08a8ae8ff5835d67c48b595a677",
                             "func_020778b0", ("r0", "r1")),
    # ROM 02096488-0209648c: the same, with r0 and r2 saved
    "main/func_02096484.c": ("8642224bab294c63cf0a76cbbda620b5e3ef5c10f90bd33190610f6cd27ccddd",
                             "func_020778b0", ("r0", "r1")),
    # ROM 0229b050-0229b054: sprintf(buf, "menu/icon/pre%d.bch") with r2 as it came in, the
    # third parameter
    "ov094/func_ov094_0229b048.c": ("4c9ec2027721e1e0c95666d46fa6992ac1303ea386ca94640d1601fb91d16123",
                                    "func_02064328", ("unused",)),
    # ROM 0229b090 computes bank (param >> 4) in r2, which the compare and the strb at 0229b09c
    # leave for sprintf(buf, "menu/icon/icon%02d.bch") at 0229b0a2
    "ov094/func_ov094_0229b088.c": ("f47362f2eff378318b4cb63405dbcbb646bb83d94fd7037c13ee2b1bf5fd4787",
                                    "func_02064328", ("bank",)),
    # ROM 020b47d4-020b47d6: r1 reaches the bl to func_020b4950_unk (ENTRIES), which reads it as
    # the buffer's length, as it came in: the second parameter, size
    "main/func_020b47d0.c": ("e7451d7ea7f5fb0adb0412b6008f9ffe3e7756430ce4b370f565b54dadc766ce",
                             "func_020b4950_unk", ("size",)),
}

# Calls into the middle of other code that are the ROM's own function starts: a loop whose
# entry stub (set a register, branch to the loop's test) dsd names with a symbol of size 0,
# and whose body from the loop's start it makes a function of its own, with a source. A
# Native caller reaches the stub through the Reference, as any call to ROM code; when the
# loop goes round, the stub's code branches to the body function's start, and that runs as
# its Native with the registers the ROM's code has there (each body's source takes all of
# them as parameters). name -> (module, address, bytes from the stub to the body's end,
# their SHA-256, the argument registers r0.. the code reads as they came in).
ENTRIES = {
    # 02050bdc ldr r2, =table; b 02050bea (ldrh r1, [r2]; ...; bne func_02050be0 (key, r1, r2))
    "func_02050bdc_unk": ("main", 0x02050BDC, 0x16,
                          "a539b36930f75a284a10cab773dcb37c37feca2cd52639205be52da31bc2c7fb", 1),
    # 02051c8c movs r3, #0; b 02051c9e (cmp r3, r1; blt func_02051c90 (array, count, -, r3))
    "func_02051c8c_unk": ("main", 0x02051C8C, 0x1A,
                          "09c9df6319715e75ced3e40cf4df166b7db1f04389078ac470eb9e4e6a28c77a", 2),
    # 020b4950 movs r3, #0; b 020b4964 (cmp r3, r1; blo func_020b4954 (string, length, -, r3))
    "func_020b4950_unk": ("main", 0x020B4950, 0x1C,
                          "7ff94603db6d452558f78600bf35c7a9ba26c1639a8c325b374d28f928817e74", 2),
}


def entry_call_ok(relative: str, text: str, name: str) -> bool:
    """Whether the source `relative` (under src/), with text `text`, calls `name` (an
    ENTRIES entry) passing the argument registers its code reads (counting what a PASSED copy
    adds)."""
    if name not in ENTRIES:
        return False
    decl = re.search(r"\bextern\s+(?:\"C\"\s+)?[\w\s\*]*\b" + re.escape(name) + r"\s*\(([^()]*)\)\s*;", text)
    if decl is None:
        return False
    params = decl.group(1).strip()
    count = 0 if params in ("", "void") else params.count(",") + 1
    spec = PASSED.get(relative)
    if spec is not None and spec[1] == name:
        count += len(spec[2])
    return count >= ENTRIES[name][4]

# Audited exact edits to a source's PC copy, where the matching source relies on what the
# ROM's code does beyond C: source (under src/) -> (SHA-256 of the source, the text as
# written, the text of the PC copy), or (SHA-256, ((as written, PC copy), ...)) for several.
EDITS = {
    # Local buffers a callee writes past: func_0209df64 stores four bytes (0209df74: strb r1,
    # [r0, #3]) into three-byte arrays. Each ROM frame has room for the fourth byte (the array
    # has a word of its own); the PC's frame may keep something live there.
    # 02077f1c: the array is sp+4 of a 12-byte frame whose word at sp is the fifth argument
    "main/func_02077f14.c": ("d4a1056abd968089e8725f7aef4d4d16f14dd3cf7b7c20d75cf0affe4567ce08",
                             "unsigned char buffer[3];", "unsigned char buffer[4];"),
    # 020866c0: sp+4 of a 12-byte frame
    "main/func_020866b8.c": ("b8511f08845728a2f9cf254597bc1bb01fcb8320c6699550a8343fb00c339627",
                             "unsigned char arr[3];", "unsigned char arr[4];"),
    # 02088a7e: sp of an 8-byte frame
    "main/func_02088a78.c": ("20b42081d4d42bb8de762acc9cd6d3e682e6239adc867a17ec06486eae7e559c",
                             "unsigned char local[3];", "unsigned char local[4];"),
    # A local buffer a callee reads past: func_0208aa48 copies the field label's line (44
    # bytes, func_02051a94) from the item name's characters at buffer+0x12, 22 bytes past the
    # 40-byte name. The ROM's frame there holds this function's and its callers' saved
    # registers, which go into the line after the name's end; the PC copy reads its own
    # uninitialized bytes there, as for any local the game copies part of (scene pickup).
    "main/func_020b8a10.c": ("3fca14879cc9b89e34bcf5e7212acd8c8842026db133b55ab7f896bce2a37f7a",
                             "    unsigned char buffer[40];", "    unsigned char buffer[0x40];"),
    # func_0204f794 stores a three-word point (x, y, z); func_ov003_02216520 passes it res, an
    # array of two words at sp+0x14 of a 0x20-byte frame (02216570), which has room for the
    # third. The PC's frame keeps a saved register there.
    "ov003/func_ov003_02216520.c": ("8ae485966c75451a492838c3dfcce4cb52336d10fa5388bb180485534a895f4f",
                                    "    int res[2];", "    int res[3];"),
    # A char parameter the ROM's code uses as the whole register (mwccarm trusts the caller to
    # have extended it), where a ROM caller passes a wider value. 0205f126 stores r2 as a word
    # (str r2, [r1, r0]); func_0205ec50 passes a pointer there.
    "main/func_0205f120.c": ("11b431aedf6752d60856e658d2b668b056d4776153732f0208ea9c02f9c67dba",
                             "void func_0205f120(unsigned char *r0, int r1, unsigned char r2)",
                             "void func_0205f120(unsigned char *r0, int r1, unsigned int r2)"),
    # 0229ab1c keeps r0 whole in r7 and passes it on to func_ov123_0229adc8 (0229ab2e, 0229ab3a,
    # 0229ab54, 0229ab60); func_ov123_0229a364 passes the editor pointer there. b and c are used
    # whole too, but that caller passes them from bytes.
    "ov123/func_ov123_0229ab18.c": ("a102da53d76aba8babb402a40937c6d2a102ef5cc6ef67e3878ef836a5fbf33f",
                                    "void func_ov123_0229ab18(unsigned char a,",
                                    "void func_ov123_0229ab18(unsigned int a,"),
    # 0229a89a keeps r0 whole in r6 and passes it on to func_ov094_0229a888 (0229a8a2), which
    # adds 0xa48 and goes on to func_ov094_0229a36c; func_ov104_0229d830, func_ov105_0229d49c,
    # func_ov106_0229d104, func_ov108_0229cbbc and func_ov103_0229cc70 pass a pointer there.
    "ov094/func_ov094_0229a898.c": ("6fa02d9ba9fa620b0a77eaccb9d0a0738c06ce98d8bfa9246dd0e106031496f7", (
        ("extern void func_ov094_0229a888(unsigned char, unsigned char);",
         "extern void func_ov094_0229a888(unsigned int, unsigned char);"),
        ("void func_ov094_0229a898(unsigned char r0,", "void func_ov094_0229a898(unsigned int r0,"),
        ("    unsigned char r6 = r0;", "    unsigned int r6 = r0;"))),
    # The ROM's this-adjusting thunks of RoomObject's destructors (02211574, 02211590) subtract
    # 236 from `this` and go on to the destructors at func_ov004_02210de8 (deleting) and
    # func_ov004_02210ee4, keeping r1-r3. The source defines the destructor itself, whose PC
    # copy would install the PC's vtable (_ZTV10RoomObject; the ROM's are 0224fe6c and
    # 0224ff18, laid out with mwccarm's one destructor slot): the copies define the thunks as
    # the ROM has them.
    "ov004/func_ov004_02211574.cpp": ("b295aae01ffb100857da6ed573eee000340334afe1abb277c1841f9d385b8f86",
                                      '#include "cpp/ov004/RoomObject.h"\n\nRoomObject::~RoomObject() {}\n',
                                      'extern "C" void *func_ov004_02210de8(char *self);\n\n'
                                      'extern "C" void *_ZThn236_N10RoomObjectD0Ev(char *self)\n{\n'
                                      '    return func_ov004_02210de8(self - 236);\n}\n'),
    "ov004/func_ov004_02211590.cpp": ("96e56729c0ab89344476d4da9a7697440e9189b76b2ea9fc279eaddf42460726",
                                      '#include "cpp/ov004/RoomObject.h"\n\nRoomObject::~RoomObject() {}\n',
                                      'extern "C" void *func_ov004_02210ee4(char *self);\n\n'
                                      'extern "C" void *_ZThn236_N10RoomObjectD1Ev(char *self)\n{\n'
                                      '    return func_ov004_02210ee4(self - 236);\n}\n'),
    # A virtual call on a member object, which the PC's compiler makes directly to
    # UnkStruct_02299d58::v2, a method with no address of its own: the ROM's code calls slot 2
    # of the object's vtable (02299d74-02299d78: ldr r1, [r0]; ldr r1, [r1, #8]; blx r1).
    "ov147/func_ov147_02299d58.cpp": ("99b54e29c62c273777f6b2b31ed526cbbe5f4f5df48ec2e724cf22c9048a1755",
                                      "        obj->sub.v2();\n",
                                      "        ((void (*)(void *))(*(void ***) &obj->sub)[2])(&obj->sub);\n"),
    # A fade the source leaves out: func_020f161c (020f161c-020f1624: add r0, r0, #0x3c; bx to
    # NNS_SndPlayerStopSeq) keeps r1 as it came in, and NNS_SndPlayerStopSeq (0210b8c4: ldr r0,
    # [r0]; bx) hands it on to the stop as its fade. The one caller, func_020f1c00, calls it at
    # 020f1c44 with r1 still its own second parameter, `arg`. The PC copies take and pass the
    # fade; the PC's call otherwise left a stale word in r1 (house-music: the heap differed
    # after the stereo's song was stopped).
    "autoload_2/func_020f161c.c": ("9d7a22f80418bed36ce9bb331d51ce26c9cf29cf3003de17c0c7287d60c54ca5", (
        ("extern void *NNS_SndPlayerStopSeq(void *);", "extern void *NNS_SndPlayerStopSeq(void *, int);"),
        ("void *func_020f161c(void *self)\n{\n    return NNS_SndPlayerStopSeq((void *) ((char *) self + 0x3c));",
         "void *func_020f161c(void *self, int fade)\n{\n"
         "    return NNS_SndPlayerStopSeq((void *) ((char *) self + 0x3c), fade);"))),
    "autoload_2/func_020f1c00.cpp": ("91694f815d4818a1174494ca9e4f284f8034bfd9666e110943232a53818d55e7", (
        ('extern "C" void *func_020f161c(void *self);', 'extern "C" void *func_020f161c(void *self, int fade);'),
        ("        func_020f161c(self);\n", "        func_020f161c(self, arg);\n"))),
    # (func_020f9948's unset r4 and r5 are given in its copy in tools/native_stack.py, with
    # the stack words it reads.)
    # A shift by a register: 020ad0f4 asrs r0, r4 shifts by r4's low byte, and a count of 32 or
    # more gives the sign; x86 masks the count to five bits.
    "main/func_020ad0c0.c": ("15b7cf92775c065f2fe439d1af6076ad8e0d15117392c543bffdfb769e337ca8",
                             "    if ((t >> v3) == 0) {",
                             "    if (((v3 & 0xff) < 32 ? t >> (v3 & 0xff) : t >> 31) == 0) {"),
}


def replacements(relative: str) -> tuple[tuple[str, str], ...]:
    """The (text as written, text of the PC copy) pairs of an EDITS entry."""
    spec = EDITS[relative]
    return spec[1] if len(spec) == 2 else (spec[1:],)


def edited(relative: str, text: str) -> str:
    if hashlib.sha256(text.encode()).hexdigest() != EDITS[relative][0]:
        raise ValueError(f"Native audited edit no longer applies; repeat the ROM audit: {relative}")
    for before, after in replacements(relative):
        if text.count(before) != 1:
            raise ValueError(f"Native audited edit no longer applies; repeat the ROM audit: {relative}")
        text = text.replace(before, after)
    return text


def paths() -> set[str]:
    return set(PASSED) | set(EDITS)


def _parameter_names(text: str, name: str) -> list[str]:
    m = re.search(r"\b" + re.escape(name) + r"\s*\(([^()]*)\)\s*\{", text)
    if m is None:
        raise ValueError(f"no definition of {name}")
    out = []
    for part in m.group(1).split(","):
        words = re.findall(r"\w+", part)
        out.append(words[-1] if words and words != ["void"] else "")
    return out


def translate(relative: str, text: str) -> str | None:
    """The PC copy of a source in PASSED or EDITS, or None for any other source."""
    if relative in EDITS:
        return edited(relative, text)
    spec = PASSED.get(relative)
    if spec is None:
        return None
    digest, callee, names = spec
    if hashlib.sha256(text.encode()).hexdigest() != digest:
        raise ValueError(f"Native passed-on arguments changed; repeat the ROM audit: {relative}")
    src = C.parse_source(C.SRC / relative)
    parameters = _parameter_names(text, src.name)
    body = text[text.index("{", text.index(src.name + "(")):]
    for name in names:
        if name in parameters and re.search(r"(?:\+\+|--|&)\s*" + name + r"\b|\b" + name
                                            + r"\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)|\b" + name + r"\s*(?:\+\+|--)", body):
            raise ValueError(f"{relative}: {name} is assigned; the ROM's register may not hold it")
    decl = re.compile(r"(\bextern\s+[\w\s\*]*\b" + re.escape(callee) + r"\s*\()([^()]*)(\)\s*;)")
    if len(decl.findall(text)) != 1:
        raise ValueError(f"{relative}: one declaration of {callee} expected")

    def widen(m: re.Match) -> str:
        params = [] if m.group(2).strip() in ("", "void") else [m.group(2).strip()]
        return m.group(1) + ", ".join(params + ["unsigned int"] * len(names)) + m.group(3)

    text = decl.sub(widen, text)
    out, pos = [], 0
    for m in re.finditer(r"\b" + re.escape(callee) + r"\s*\(", text):
        if re.search(r"\bextern\b[^;]*$", text[:m.start()]):
            continue  # the declaration
        depth, i = 1, m.end()
        while depth:
            depth += {"(": 1, ")": -1}.get(text[i], 0)
            i += 1
        inner = text[m.end():i - 1]
        extra = ", ".join(f"(unsigned int) ({n})" for n in names)
        out.append(text[pos:m.end()] + (inner + ", " if inner.strip() else "") + extra + ")")
        pos = i
    if not out:
        raise ValueError(f"{relative}: no call to {callee}")
    return "".join(out) + text[pos:]


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
