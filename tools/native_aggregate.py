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


def caller_copy(relative: str, text: str) -> str | None:
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
