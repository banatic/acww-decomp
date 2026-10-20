"""Enable only source/header/ROM-audited aggregate return adapters."""
import hashlib
import json

import common as C

SPECS = json.loads((C.ROOT / 'runtime/native-aggregate.json').read_text())
CLEAN_SOURCE = 'clean/main/event_calendar.c'
SCALAR_CALLER = 'ov050/func_ov050_02261ed0.cpp'
SCALAR_DECLARATION = '''struct NativeAggregateDate { unsigned char bytes[4]; };
extern NativeAggregateDate func_020afa48(void *a);
static unsigned int native_aggregate_date_word(void *a)
{
    NativeAggregateDate result = func_020afa48(a);
    return (unsigned int) result.bytes[0] | ((unsigned int) result.bytes[1] << 8) |
           ((unsigned int) result.bytes[2] << 16) | ((unsigned int) result.bytes[3] << 24);
}
'''


# Callers of a function their source declares returning a structure by value, audited
# against the ROM: source (under src/) -> (SHA-256 of the source, the callees the entry covers,
# exact replacements for the PC copy). An entry without replacements declares the callee with
# its definition's layout, whose crossings the return kinds above adapt; the others make the
# call as the ROM's code makes it.
CALLERS = {
    # 3-byte structure of three bytes, as func_02013304 defines it (kind 8 at the crossings)
    "main/func_02012e58.c": ("852815330e291566a3e090a8c71f3621e6efad8c591fe317bebebf2a4cb0bb52",
                             ("func_02013304",), ()),
    # func_020404b4 with its definition's union (kind 9). The function itself returns that
    # union, which the ROM returns in r0 (020404a6 ldr r0, [sp, #0x20]) and its callers
    # func_0204019c and func_02040180 declare as int: the copy returns the union's word.
    "main/func_020401b8.c": ("b8d304daa3059d7e61944ddb47bccc718416adbb934b56f575b438bcf0b613f2",
                             ("func_020404b4",), (
        ("UnkStruct_020401b8 func_020401b8(UnkStruct_020401b8_3 *p, int a1, UnkStruct_020401b8_2 q, int a3)\n{",
         "unsigned int func_020401b8(UnkStruct_020401b8_3 *p, int a1, UnkStruct_020401b8_2 q, int a3)\n{"),
        ("    return d;\n}", "    return d.w;\n}"))),
    # func_0204019c and func_02040180 return int; the ROM's caller stores r0 as the structure's
    # word (0203ffc4, 0203ffe8)
    "main/func_0203ff98.c": ("ee66a2c5b5ad994b5c0108586afdb1cb61529531f15c074023ddaaed18a3ff14",
                             ("func_0204019c", "func_02040180"), (
        ("extern UnkStruct_0203ff98 func_0204019c(", "extern unsigned int func_0204019c("),
        ("extern UnkStruct_0203ff98 func_02040180(", "extern unsigned int func_02040180("),
        ("r1 = func_0204019c(", "r1.v = func_0204019c("),
        ("r2 = func_02040180(", "r2.v = func_02040180("))),
    # The library's FS_GetOverlayFileID returns its 8-byte FSFileID through a pointer in r0,
    # the overlay's information in r1 (0204f972-0204f976); the PC passes the same two.
    "main/func_0204f934.c": ("eb9b4d8c16002ae422978db54663bd8a7e3ab3e4db96189e078c6e18bd4be58f",
                             ("FS_GetOverlayFileID",), (
        ("extern FSFileID FS_GetOverlayFileID(const void *overlay);",
         "extern void FS_GetOverlayFileID(FSFileID *result, const void *overlay);"),
        ("path = FS_GetOverlayFileID(buffer);", "FS_GetOverlayFileID(&path, buffer);"))),
    # func_020bbf00 returns a short; the ROM's callers store r0's halfword as the colour
    # (02065684 and 020656ba strh r0)
    "main/func_02065604.c": ("938f423126252493a47534f1ac8dd2f888949d35360b805d73ac7420abcdf6fd",
                             ("func_020bbf00",), (
        ("extern Col func_020bbf00(int);", "extern unsigned short func_020bbf00(int);"),
        ("x = func_020bbf00(2);", "*(unsigned short *) &x = func_020bbf00(2);"))),
    "main/func_020656ac.c": ("46d2e505af5cad111a923181e520880b24cca665072aa3d93b64188342c0138b",
                             ("func_020bbf00",), (
        ("extern Col func_020bbf00(int);", "extern unsigned short func_020bbf00(int);"),
        ("x = func_020bbf00(3);", "*(unsigned short *) &x = func_020bbf00(3);"))),
    # Virtual methods returning a structure: mwccarm passes the result's address in r0 and
    # `this` in r1 (0205b2e2-0205b2ec, 0205b2f6-0205b300; 02263da0-02263daa; 022650d8-022650e2).
    # The objects' vtables are the ROM's: 020dd3a4 and 020dd3b8 (installed by func_0205bb48
    # and func_0205bbc4 for func_0205b868 and func_0205b8e0, func_0205b270's two callers),
    # whose slots 1 and 2 are C functions (out, unused, index); and Obj_ov009_022658dc's,
    # whose slot 45 is func_ov009_02262ec4 (out, this), which writes three words (the other
    # vtables with that slot hold func_0201ce34, which writes nothing). The copies call the
    # slot with those arguments as a C function: the same words on the PC's stack, which a
    # Native target takes as they are and the trampoline hands the ROM's code in r0-r2.
    "main/func_0205b270.cpp": ("a0bf8a7444bfa5ab6232bd9fd124a774e96a8a2f88d78bfbba2c282368e70469",
                               ("f4", "f8"), (
        ("        Half roomA = p6->f4(t);\n",
         "        Half roomA;\n"
         "        ((void (*)(Half *, UnkStruct_0205b270 *, int))(*(void ***) p6)[1])(&roomA, p6, t);\n"),
        ("        Half roomB = p6->f8(t);\n",
         "        Half roomB;\n"
         "        ((void (*)(Half *, UnkStruct_0205b270 *, int))(*(void ***) p6)[2])(&roomB, p6, t);\n"))),
    "ov009/func_ov009_02263c84.cpp": ("602bc0bf0da184fa11337410f8ff84e34679ed24f9337c8493e193e8ee7553e6",
                                      ("Fnb4",), (
        ("    const Buf &buf = self->Fnb4();\n",
         "    Buf buf;\n"
         "    ((void (*)(Buf *, UnkStruct_02263c84 *))(*(void ***) self)[45])(&buf, self);\n"),)),
    "ov009/func_ov009_02263e58.cpp": ("8dfab9b22c92d1094727117f705ddd64fcf5cc48cfaa282944a58dd444c205f8",
                                      ("Fnb4",), (
        ("    const Buf &buf = self->Fnb4();\n",
         "    Buf buf;\n"
         "    ((void (*)(Buf *, UnkStruct_02263e58 *))(*(void ***) self)[45])(&buf, self);\n"),)),
    # the 8-byte Vec gets the three words in a buffer of their size (the ROM's frame has them)
    "ov009/func_ov009_022650d0.cpp": ("3866cd762f44afdedf81cc181e70395e2ff3ed974772c9f5fb5440c18c826754",
                                      ("v45",), (
        ("    const Vec &v = self->v45();\n",
         "    int words[3];\n"
         "    ((void (*)(int *, UnkStruct_022650d0_2 *))(*(void ***) self)[45])(words, self);\n"
         "    const Vec &v = *(const Vec *) words;\n"),)),
}


# The same for Clean sources, whose PC copies tools/run.py compiles: source (from the root) ->
# (SHA-256, replacements).
# (source, its SHA-256, [(before, after)]): a Clean source whose PC copy must call a ROM function
# returning a structure as the ROM's code does; none now, overlay_slots.c declares it so itself
CLEAN_CALLERS: dict[str, tuple[str, tuple]] = {}


def clean_caller_copy(relative: str, text: str) -> str:
    """The PC copy of a Clean source (`relative` from the root): `text` itself unless
    CLEAN_CALLERS has it."""
    spec = CLEAN_CALLERS.get(relative)
    if spec is None:
        return text
    if hashlib.sha256(text.encode()).hexdigest() != spec[0]:
        raise ValueError('Aggregate Clean caller source changed; repeat the ROM audit: ' + relative)
    for before, after in spec[1]:
        if text.count(before) != 1:
            raise ValueError('Aggregate Clean caller source changed; repeat the ROM audit: ' + relative)
        text = text.replace(before, after)
    return text


def handled(relative: str) -> set[str]:
    """The callees the audited copy of `relative` (under src/) calls as the ROM's code does."""
    spec = CALLERS.get(relative)
    return set(spec[1]) if spec else set()


def returns_word(relative: str) -> bool:
    """Whether the PC copy of `relative` returns a word where the source returns a structure."""
    return any(before.endswith("\n{") and after.startswith("unsigned int ")
               for before, after in CALLERS.get(relative, ("", (), ()))[2])


def caller_copy(relative: str, text: str) -> str | None:
    spec = CALLERS.get(relative)
    if spec is not None:
        if hashlib.sha256(text.encode()).hexdigest() != spec[0]:
            raise ValueError('Aggregate caller source changed; repeat the ROM audit: ' + relative)
        if not spec[2]:
            return None
        for before, after in spec[2]:
            if text.count(before) != 1:
                raise ValueError('Aggregate caller source changed; repeat the ROM audit: ' + relative)
            text = text.replace(before, after)
        return text
    if relative != SCALAR_CALLER:
        return None
    if hashlib.sha256(text.encode()).hexdigest() != '0b1efc86089d734414ce77c9de99f3cb4da21ef7781802e7f3331dfb4cd35ada':
        raise ValueError('Aggregate scalar caller source changed')
    if hashlib.sha256((C.INCLUDE / 'types.h').read_bytes()).hexdigest() != '55b3864dec5d21f20dd2869c65a57ce6a4db16c7af033c69783b8b65aaddd5a7':
        raise ValueError('Aggregate scalar caller header changed')
    image = C.module_image('ov050')
    start = 0x02261ed0 - C.modules()['ov050']['base']
    body = image[start:start + 1864]
    if hashlib.sha256(body).hexdigest() != '8f45ba505c55d0b0c88ffe9bfd0d9e7b0a8204f18e8c5e327de75279bf4a490f':
        raise ValueError('Aggregate scalar caller ROM changed')
    declaration = 'extern int func_020afa48(void *a);'
    call = 'uidx = (unsigned int) func_020afa48(data_021f395c);'
    if text.count(declaration) != 1 or text.count(call) != 1:
        raise ValueError('Aggregate scalar call site changed')
    # ARM 02262340 calls 020afa48 and then extracts four bytes from r0.
    # Make the PC declaration agree with the body, then reproduce that word.
    return text.replace(declaration, SCALAR_DECLARATION).replace(
        call, 'uidx = native_aggregate_date_word(data_021f395c);')


def clean_copy(text: str) -> str:
    """Assert the one scalar Clean ABI in its own translation unit."""
    return text + '''
_Static_assert(sizeof(EventKey) == 4 &&
               _Generic((EventKey) 0, unsigned int: 1, unsigned long: 1, default: 0),
               "Clean event key must remain an unsigned word");
_Static_assert(__builtin_types_compatible_p(__typeof__(&EventCalendar_ScheduleKey),
                                          EventKey (*)(const EventRule *, int, EventKey)),
               "Clean schedule key ABI changed");
'''


def return_kind(path) -> int | None:
    if not path.is_relative_to(C.SRC):
        return None
    relative = path.relative_to(C.SRC).as_posix()
    spec = SPECS.get(relative)
    if spec is None:
        return None
    if hashlib.sha256(path.read_bytes()).hexdigest() != spec['source_sha256']:
        raise ValueError('Aggregate return source changed: ' + relative)
    for name, digest in spec['headers'].items():
        if hashlib.sha256((C.ROOT / name).read_bytes()).hexdigest() != digest:
            raise ValueError('Aggregate return header changed: ' + name)
    source = C.parse_source(path)
    image = C.module_image(source.module)
    offset = source.address - C.modules()[source.module]['base']
    body = image[offset:offset + source.size]
    if len(body) != spec['size'] or hashlib.sha256(body).hexdigest() != spec['rom_sha256']:
        raise ValueError('Aggregate return ROM changed: ' + relative)
    return spec['kind']
