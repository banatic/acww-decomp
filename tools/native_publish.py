"""Audited PC copies for stores that publish completed scanline buffers."""
from __future__ import annotations

import hashlib
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402


SOURCE = 'main/func_020bb090'
SOURCE_SHA = 'af6211b06f63f63329391a703d65b5a46e399a3af57f382ccd1606585b77907e'
ROM_SHA = '0e56508ec23321fef512dcc348a0b5a583ccc34b8f7ac3eae3cbcbd10baffe36'
CLEAN_SOURCE = 'clean/main/sky.c'
CLEAN_SHA = 'aeb70849fd840e74b92304c30641c5f06dc8d32f520ba5fda3da4e83a3278d1b'
ADDRESS, SIZE = 0x020bb090, 0xfc
STORE_PC, DESTINATION = 0x020bb16e, 0x021f6f70
SHIFT_SOURCE = 'main/func_020ba340'
SHIFT_SOURCE_SHA = 'f011038349c16674dcd3f5b464e236a7f05e57999f18b138fb57db7c72f26b44'
SHIFT_ADDRESS, SHIFT_SIZE = 0x020ba340, 0x1c
SHIFT_ROM_SHA = 'e19d915eb69968b7788f25ce6e8d469777e178f40132e333c7ba216d48ae9ad1'
CLOUD_SOURCE = 'main/func_020bae60'
CLOUD_SOURCE_SHA = '714fbf2ae416f97428ec62fb0329381bb14bac5dc1f18b5e12c6ee4b2a45a1d7'
CLOUD_ADDRESS, CLOUD_SIZE = 0x020bae60, 0x230
CLOUD_ROM_SHA = '9fa321e37dcc7454d10f71266c4d547a864a61b152a00b6783a0b0db54517f09'
ROM_SITES = ((ADDRESS, SIZE, ROM_SHA), (SHIFT_ADDRESS, SHIFT_SIZE, SHIFT_ROM_SHA),
             (CLOUD_ADDRESS, CLOUD_SIZE, CLOUD_ROM_SHA))


def validate_rom(code: bytes, address: int = ADDRESS) -> None:
    expected = next(((size, sha) for at, size, sha in ROM_SITES if at == address), None)
    if expected is None or (len(code), hashlib.sha256(code).hexdigest()) != expected:
        raise ValueError('Native publication ROM changed; audit the complete store path again')


def paths() -> set[str]:
    return {SOURCE, SHIFT_SOURCE, CLOUD_SOURCE}


def translate(relative: str, text: str, base: str | None = None) -> str | None:
    """The PC copy of the function `relative` (its function key, or a Clean source's path)
    whose source is `text`; `base`, when given, is the copy so far that the edits apply to (the
    unit's other functions' copies, tools/native.py)."""
    if relative == SOURCE:
        digest = SOURCE_SHA
        changes = [('    data_021f6f70 = parity;',
                    '    native_publish_word(0x020bb16eu, (uint32_t *) &data_021f6f70, (uint32_t) parity);')]
    elif relative == SHIFT_SOURCE:
        digest = SHIFT_SOURCE_SHA
        original = '*(int *) ((char *) ((int) &data_021f8ab0) + (28))'
        changes = [(f'    {original} = ({original} ^ 1);',
                    '    uint32_t *selector = (uint32_t *) ((char *) &data_021f8ab0 + 0x1c);\n'
                    '    native_publish_word(0x020ba348u, selector, *selector ^ 1u);')]
    elif relative == CLOUD_SOURCE:
        # 020bb040 str r0, [r1, #4]: the set of cloud tables HBlank shows, after the other set
        # (and its blending) is filled
        digest = CLOUD_SOURCE_SHA
        changes = [('    data_021f75b0.unk_04 = slot;',
                    '    native_publish_word(0x020bb040u, (uint32_t *) &data_021f75b0.unk_04, (uint32_t) slot);')]
    elif relative == CLEAN_SOURCE:
        digest = CLEAN_SHA
        changes = [('    gradient->shown = (u32) set;',
                    '    native_publish_word(0x020bb16eu, (uint32_t *) &gradient->shown, (uint32_t) set);'),
                   ('    data_021f75b0.shift_index ^= 1;',
                    '    native_publish_word(0x020ba348u, (uint32_t *) &data_021f75b0.shift_index,\n'
                    '                        data_021f75b0.shift_index ^ 1u);'),
                   ('    sky->shown = (u32) set;',
                    '    native_publish_word(0x020bb040u, (uint32_t *) &sky->shown, (uint32_t) set);')]
    else:
        return None
    if C.pinned_sha256(relative, text) != digest:
        raise ValueError(f'Native publication source changed; repeat the store audit: {relative}')
    text = text if base is None else base
    for old, new in changes:
        assert text.count(old) == 1
        text = text.replace(old, new)
    return '#include "native_publish.h"\n' + text
