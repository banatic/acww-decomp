"""Audited ROM frames and the house collider's observable stack storage.

Only complete, constant call-site extents are accepted here. Unknown frames
remain unknown; the runtime must not guess through them to supply a slot.
The ROM digests cover whole functions, including both audited jump tables.
"""
from __future__ import annotations

import hashlib
from typing import NamedTuple


class Frame(NamedTuple):
    extent: int
    size: int
    sha256: str


FRAMES: dict[tuple[str, int], Frame] = {
    # Newly Native scheduler/member callbacks reach the audited house slots.
    # 01ffd14c briefly uses 0x1c bytes via ip, but calls at entry SP - 0x18.
    # Its fp-relative epilogue restores the original SP.
    ('autoload_2', 0x020ee834): Frame(0x10, 0x74,
        '8e29bedef588154174b86c441edcb3c34abd3613889a29b6cb6792ac5b768e17'),
    ('autoload_2', 0x020ee934): Frame(0x8, 0x30,
        '0a12ed6a46868a0b6aeedfafda6c3929d472fb127f3e242eb6cd4631b7f24121'),
    ('autoload_2', 0x020ee964): Frame(0x8, 0x3c,
        'a4b23da6aef9377bd83e195491108c8d0c5fea7814705790e78f993d6bd57155'),
    ('autoload_2', 0x020ee9a0): Frame(0x8, 0x9c,
        'c6789f59bce64d6b65a7dae168ad70d92307fc82a428437a87705af098c86bf0'),
    ('autoload_2', 0x020eea4c): Frame(0x10, 0x80,
        '0ed3218904f225ae19e9c989fa06080b5aa2873a81cc89cd2a88615899368492'),
    ('itcm', 0x01ffd14c): Frame(0x18, 0x68,
        '5d9768cabc8bfa50a219a6a7a2132232dbc9817484d8eb55007fbcbf392f6053'),
    ('itcm', 0x01ffd44c): Frame(0x20, 0xc0,
        '97be9e9481e520004c748417f3408881cf9e8cffe7d0df642eda1d75c3469269'),
    ('main', 0x02004c0c): Frame(0x8, 0x10,
        '73456a52c80d7eae4ddfea61c20268567c5eb980a6c45809d02417ec37e4b6cb'),
    ('main', 0x020058e4): Frame(0x28, 0xbe8,
        '3a3db66be4481c605e47283936bec191639d1bb3dad2dde0c0bff64c60919af8'),
    ('main', 0x020095f4): Frame(0x10, 0x2e,
        '3c13edac9170a39a7c1d2756354e736302d30219ff17fea42bae8f8e6337d5b7'),
    ('main', 0x020096ac): Frame(0x18, 0x7c,
        '904b3327a6c46abc227371e5989e9286f11017370b26d760bf5cdb880bcfad19'),
    ('main', 0x0200c200): Frame(0x8, 0x58,
        '8f63d45e4deec412bbffdb24b60815c393497436d3658d5925d3438aa64abf7c'),
    ('main', 0x0200cc44): Frame(0x10, 0x88,
        '2fd5b07e721c64ca58d645c49bcf973b3bc6779d826d804b7606ace4d18e7675'),
    ('main', 0x0200d1e4): Frame(0x10, 0x74,
        'c7ecdd90f13bc9bfcf49cbf218ef7373e76c12c03bb35cddeb6dc26e42883601'),
    ('main', 0x0201100c): Frame(0x50, 0x70,
        '3cb5f03c58fd23a89c88bae429f4684fc0d4b6731f27fef9d599fbd7b7a0011e'),
    ('main', 0x02030ebc): Frame(0x60, 0x190,
        'fdc23bfad547fb36119fe06361d2602142569dde92b441e9083a47f88528c8d1'),
    ('main', 0x02031288): Frame(0xd0, 0x1f0,
        'fc13ffd0ffeac43319b996ac7119e1629ac8addc2316a6721aa329b3107db260'),
    ('main', 0x02032aa8): Frame(0x10, 0x22,
        '08566a2b4b0f2a8d6915ec7b95b93a9fc5d7c02384ba577082ae50fa1e8424a6'),
    ('main', 0x02033678): Frame(0x98, 0x200,
        '4b4ac04c4cc9084946d33f7c58fba302c44914b708e50d3d039fbee325c2c87c'),
    ('ov004', 0x0220dd80): Frame(0xa0, 0x260,
        '5439457113415e7dffbf2a65bb8af9e18429fc9263c2ed75e2f3cf02a8fb392f'),
    ('ov004', 0x0223d610): Frame(0x0, 0x8,
        '0ace2934a377808cb289cc22010424b897e09b43ae02a959f59c6610372229f3'),
    ('ov004', 0x0223d63c): Frame(0x20, 0x1f0,
        'db2d0a11290c2e49887c3e4a2965fb9be1466e50e2690be419e085c65d0b9995'),
    ('ov004', 0x0223db08): Frame(0xd8, 0x160,
        '2f02b1cab1254c2bd730603733dd459e012eed8e65a6eed685f0e7f5c12c4d9b'),
    ('ov004', 0x0223de70): Frame(0x40, 0xd8,
        '61174b6881bec93dfd9ccd2784b9dbd80081dbefb1d0b5807a24e4ef41c95b80'),
    ('ov004', 0x0223df88): Frame(0x2e0, 0x268,
        'b3f0a518910820c672e4df600e3a4dfa4e69e7ea8f6041b106bc3c119535575e'),
    ('ov004', 0x0223e1f0): Frame(0x18, 0x100,
        'b3c9a7e34464ec85bbcd9a13cc90946ee750f4381597dc24d2bf36a5b3f165c2'),
}

SOURCES = {
    'ov004/func_ov004_0223df88.cpp': 'f83678a3e49cb33c093f9187915bc3630a7241ac452719b8cd7aa5aa592a432d',
    'ov004/func_ov004_0220dd80.cpp': '2f88fa901fa5fd612e351526a20dc5960b608c3ca7dc45bfdc6b7a8df14f9da2',
}
CONSUMER = 'ov004/func_ov004_0223df88.cpp'
# 0220dd8a stores incoming r3 at SP+0x14 before the first call. Apply the
# same spill to Native and Clean entries; its value comes from their input.
SPILLS = {('ov004', 0x0220dd80): (3, 0x14)}


def frame_extent(module: str, address: int, code: bytes) -> int | None:
    spec = FRAMES.get((module, address & ~1))
    if spec is None:
        return None
    if len(code) != spec.size or hashlib.sha256(code).hexdigest() != spec.sha256:
        raise ValueError(f'Native stack ROM changed; repeat the full control-flow audit: {module}:{address:08x}')
    return spec.extent


def validate_source(relative: str, text: str) -> None:
    if relative in SOURCES and hashlib.sha256(text.encode()).hexdigest() != SOURCES[relative]:
        raise ValueError(f'Native stack source changed; repeat the stack effect audit: {relative}')


def paths() -> set[str]:
    return {CONSUMER}


def translate(relative: str, text: str) -> str | None:
    if relative != CONSUMER:
        return None
    validate_source(relative, text)
    declaration = '    Vec centers[4];'
    use = '    position = (Vec *) (self + 0x5c);'
    assert text.count(declaration) == text.count(use) == 1
    text = text.replace(declaration, '    Vec *centers;')
    text = text.replace(use,
                        '    centers = (Vec *) (uintptr_t) native_guest_stack_slot(0x0223df88u, 0x28u, sizeof(Vec) * 4);\n'
                        + use)
    return '#include "native_guest.h"\n' + text
