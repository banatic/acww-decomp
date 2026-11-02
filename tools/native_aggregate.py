"""Enable only source/header/ROM-audited aggregate return adapters."""
import hashlib
import json

import common as C

SPECS = json.loads((C.ROOT / 'runtime/native-aggregate.json').read_text())
CLEAN_SOURCE = 'clean/main/event_calendar.c'
SCALAR_CALLER = 'ov050/func_ov050_02261ed0'
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
# against the ROM: function key (common.function_key) -> (SHA-256 of the function's text
# (common.function_sha256), the callees the entry covers,
# exact replacements for the PC copy). An entry without replacements declares the callee with
# its definition's layout, whose crossings the return kinds above adapt; the others make the
# call as the ROM's code makes it.
CALLERS = {
    # 3-byte structure of three bytes, as func_02013304 defines it (kind 8 at the crossings)
    "main/func_02012e58": ("2e411f6bf321190fd0c34e2aeb8f25349828ec25188bf4edb22f1de2b252f58c",
                             ("func_02013304",), ()),
    # func_020404b4 with its definition's union (kind 9). The function itself returns that
    # union, which the ROM returns in r0 (020404a6 ldr r0, [sp, #0x20]) and its callers
    # func_0204019c and func_02040180 declare as int: the copy returns the union's word.
    "main/func_020401b8": ("1d29ee8d7c97e5c7a62c8b1fc76b46b13f08480abb3ecd9df8f1837a4e0b9a1c",
                             ("func_020404b4",), (
        ("UnkStruct_020401b8 func_020401b8(UnkStruct_020401b8_3 *p, int a1, UnkStruct_020401b8_2 q, int a3)\n{",
         "unsigned int func_020401b8(UnkStruct_020401b8_3 *p, int a1, UnkStruct_020401b8_2 q, int a3)\n{"),
        ("    return d;\n}", "    return d.w;\n}"))),
    # func_0204019c and func_02040180 return int; the ROM's caller stores r0 as the structure's
    # word (0203ffc4, 0203ffe8)
    "main/func_0203ff98": ("89d081a436a092b1f0a17e8ed9f3f622b6e2303e6458db260cac7c4dd7f7fd8f",
                             ("func_0204019c", "func_02040180"), (
        ("extern UnkStruct_0203ff98 func_0204019c(", "extern unsigned int func_0204019c("),
        ("extern UnkStruct_0203ff98 func_02040180(", "extern unsigned int func_02040180("),
        ("r1 = func_0204019c(", "r1.v = func_0204019c("),
        ("r2 = func_02040180(", "r2.v = func_02040180("))),
    # The library's FS_GetOverlayFileID returns its 8-byte FSFileID through a pointer in r0,
    # the overlay's information in r1 (0204f972-0204f976); the PC passes the same two.
    "main/func_0204f934": ("6501fcaae29a8f8407b16e9311fab41b667dc8d33dee0c4fad57efc6f256ff86",
                             ("FS_GetOverlayFileID",), (
        ("extern FSFileID FS_GetOverlayFileID(const void *overlay);",
         "extern void FS_GetOverlayFileID(FSFileID *result, const void *overlay);"),
        ("path = FS_GetOverlayFileID(buffer);", "FS_GetOverlayFileID(&path, buffer);"))),
    # func_020bbf00 returns a short; the ROM's callers store r0's halfword as the colour
    # (02065684 and 020656ba strh r0)
    "main/func_02065604": ("24ffd96ca6470e58006e1628ffbdd56f31db0db792eed06f01ccaca365c0065c",
                             ("func_020bbf00",), (
        ("extern Col func_020bbf00(int);", "extern unsigned short func_020bbf00(int);"),
        ("x = func_020bbf00(2);", "*(unsigned short *) &x = func_020bbf00(2);"))),
    "main/func_020656ac": ("c89cc6134692fb50ca62096b131ce8edab93df47c7c0f9f0bab1f09bebbba71a",
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
    "main/func_0205b270": ("7a671471a206f575663eea16830e7957ca055ba0fe47c47c3e090dc69fc15041",
                               ("f4", "f8"), (
        ("        Half roomA = p6->f4(t);\n",
         "        Half roomA;\n"
         "        ((void (*)(Half *, UnkStruct_0205b270 *, int))(*(void ***) p6)[1])(&roomA, p6, t);\n"),
        ("        Half roomB = p6->f8(t);\n",
         "        Half roomB;\n"
         "        ((void (*)(Half *, UnkStruct_0205b270 *, int))(*(void ***) p6)[2])(&roomB, p6, t);\n"))),
    "ov009/func_ov009_02263c84": ("8ead6227e9e387db18c9e33efec5e581e56b4621b3ab8457100c712bcb2f24a8",
                                      ("Fnb4",), (
        ("    const Buf &buf = self->Fnb4();\n",
         "    Buf buf;\n"
         "    ((void (*)(Buf *, UnkStruct_02263c84 *))(*(void ***) self)[45])(&buf, self);\n"),)),
    "ov009/func_ov009_02263e58": ("da1b1927beccef84804abe701c96148ceb35525c0cfaafcc5511073a6e5a5386",
                                      ("Fnb4",), (
        ("    const Buf &buf = self->Fnb4();\n",
         "    Buf buf;\n"
         "    ((void (*)(Buf *, UnkStruct_02263e58 *))(*(void ***) self)[45])(&buf, self);\n"),)),
    # the 8-byte Vec gets the three words in a buffer of their size (the ROM's frame has them)
    "ov009/func_ov009_022650d0": ("358565b931a61126daf4ecaf5ce0e8a653bd38992f7c999055ed618cebdf0a6a",
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
    """The callees the audited copy of the function `relative` (its key) calls as the ROM's
    code does."""
    spec = CALLERS.get(relative)
    return set(spec[1]) if spec else set()


def returns_word(relative: str) -> bool:
    """Whether the PC copy of `relative` returns a word where the source returns a structure."""
    return any(before.endswith("\n{") and after.startswith("unsigned int ")
               for before, after in CALLERS.get(relative, ("", (), ()))[2])


def caller_copy(relative: str, text: str, base: str | None = None) -> str | None:
    """The PC copy of the function `relative` (its key) whose source is `text`, or None; `base`,
    when given, is the copy so far that the replacements apply to (tools/native.py)."""
    spec = CALLERS.get(relative)
    if spec is not None:
        if C.pinned_sha256(relative, text) != spec[0]:
            raise ValueError('Aggregate caller source changed; repeat the ROM audit: ' + relative)
        text = text if base is None else base
        if not spec[2]:
            return None
        for before, after in spec[2]:
            if text.count(before) != 1:
                raise ValueError('Aggregate caller source changed; repeat the ROM audit: ' + relative)
            text = text.replace(before, after)
        return text
    if relative != SCALAR_CALLER:
        return None
    if C.pinned_sha256(relative, text) != 'e15eb28eb56d8156fade0e85977d66a050d4da38ef8a80d35fd901d06ad4ee7e':
        raise ValueError('Aggregate scalar caller source changed')
    text = text if base is None else base
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


def return_kind(path, name: str | None = None) -> int | None:
    """The return kind of the function `name` (the first of the source when None) that `path`
    defines, when runtime/native-aggregate.json has it (by its function key)."""
    if not path.is_relative_to(C.SRC):
        return None
    source = next((s for s in C.parse_sources(path) if name is None or s.name == name), None)
    if source is None:
        return None
    relative = C.function_key(source)
    spec = SPECS.get(relative)
    if spec is None:
        return None
    if C.pinned_sha256(relative, path.read_bytes().decode()) != spec['function_sha256']:
        raise ValueError('Aggregate return source changed: ' + relative)
    for name, digest in spec['headers'].items():
        if hashlib.sha256((C.ROOT / name).read_bytes()).hexdigest() != digest:
            raise ValueError('Aggregate return header changed: ' + name)
    image = C.module_image(source.module)
    offset = source.address - C.modules()[source.module]['base']
    body = image[offset:offset + source.size]
    if len(body) != spec['size'] or hashlib.sha256(body).hexdigest() != spec['rom_sha256']:
        raise ValueError('Aggregate return ROM changed: ' + relative)
    return spec['kind']
