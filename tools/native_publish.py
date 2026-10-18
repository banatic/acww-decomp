"""Audited PC copies for stores that publish completed scanline buffers."""
from __future__ import annotations

import hashlib


SOURCE = 'main/func_020bb090.c'
SOURCE_SHA = 'ccfdb7873410e0e4c066aea06188ca634bb00a181e78f929773ca826b2ba7cb2'
ROM_SHA = '0e56508ec23321fef512dcc348a0b5a583ccc34b8f7ac3eae3cbcbd10baffe36'
CLEAN_SOURCE = 'clean/main/sky.c'
CLEAN_SHA = '8b15629efdee4be7594a1f44cc97d75d50f542b3180f4f8a4e6a8e57a1b00b5d'
ADDRESS, SIZE = 0x020bb090, 0xfc
STORE_PC, DESTINATION = 0x020bb16e, 0x021f6f70
SHIFT_SOURCE = 'main/func_020ba340.c'
SHIFT_SOURCE_SHA = '861686f60cde8bdf4b8663119049733bf1102aa887099f9fb119a6e81a6ff9d6'
SHIFT_ADDRESS, SHIFT_SIZE = 0x020ba340, 0x1c
SHIFT_ROM_SHA = 'e19d915eb69968b7788f25ce6e8d469777e178f40132e333c7ba216d48ae9ad1'
ROM_SITES = ((ADDRESS, SIZE, ROM_SHA), (SHIFT_ADDRESS, SHIFT_SIZE, SHIFT_ROM_SHA))


def validate_rom(code: bytes, address: int = ADDRESS) -> None:
    expected = next(((size, sha) for at, size, sha in ROM_SITES if at == address), None)
    if expected is None or (len(code), hashlib.sha256(code).hexdigest()) != expected:
        raise ValueError('Native publication ROM changed; audit the complete store path again')


def paths() -> set[str]:
    return {SOURCE, SHIFT_SOURCE}


def translate(relative: str, text: str) -> str | None:
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
    elif relative == CLEAN_SOURCE:
        digest = CLEAN_SHA
        changes = [('    gradient->shown = (u32) set;',
                    '    native_publish_word(0x020bb16eu, (uint32_t *) &gradient->shown, (uint32_t) set);'),
                   ('    data_021f75b0.shift_index ^= 1;',
                    '    native_publish_word(0x020ba348u, (uint32_t *) &data_021f75b0.shift_index,\n'
                    '                        data_021f75b0.shift_index ^ 1u);')]
    else:
        return None
    if hashlib.sha256(text.encode()).hexdigest() != digest:
        raise ValueError(f'Native publication source changed; repeat the store audit: {relative}')
    for old, new in changes:
        assert text.count(old) == 1
        text = text.replace(old, new)
    return '#include "native_publish.h"\n' + text
