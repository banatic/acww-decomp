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
    # The furniture-pull state (house-pull): push {r4, lr}, no other stack use, every call
    # at entry SP - 8, one join before the single return.
    ('ov004', 0x0222a28c): Frame(0x8, 0x5c,
        '7ef3d5a85cad364b700cf2f6c34e3318067c5b200e0917bb797a499380b07c9c'),
    # The furniture-pull state that reaches func_0201100c through func_ov004_02229860
    # (house-pull): push {r4, lr}, straight-line calls, one return.
    ('ov004', 0x022297d8): Frame(0x8, 0x26,
        '0bd0d2b2ace1ccd045ad30c9c52953c562bc83ef2140983b6a609a5520cde648'),
    # The other callers of func_0201100c, which reaches the house collider through
    # 02031288 (house-pull reached two of them). Each saves registers with one push and
    # reserves its frame with one sub at entry; its only other SP change is the matching
    # add before the single pop sequence, so every call is at entry SP - extent.
    ('main', 0x02008304): Frame(0x8, 0x26,
        '62ba693b4a4a70952cec9915c3f72087ce06f3ed8e2662396c75970435b46309'),
    ('main', 0x02009fe4): Frame(0x8, 0x48,
        '4ac3d17b29427f0817de837ebdbc5ec20249b9904afe92665bd822e2e811c594'),
    ('main', 0x0200c954): Frame(0x8, 0x24,
        '73521042e9cbf84c098ebaf55e7df392de3a9ea27ac1547548feffabf785756c'),
    ('main', 0x0200c9ec): Frame(0x8, 0x2c,
        'f9e01dde526dea1d7f72d3752ee22bb253b8b2002ec662af38a3b34cd000bd6b'),
    ('ov003', 0x0220d2a4): Frame(0x8, 0x2a,
        '3d17a706dcdd2913b13b1051e38b15ed8608dbf2d47733ddb2a5904eb0adad15'),
    ('ov003', 0x0220d6d4): Frame(0x8, 0x20,
        '7abcc817bb00eff6acd09e08f5b95ba0a39ade8ac2a1420cb6631939164b96a6'),
    ('ov003', 0x0220d8f4): Frame(0x8, 0x20,
        '33fcf541c2275ed1cf839ac34395826399e31d46199b7c81cfca1e75a3490191'),
    ('ov003', 0x0220dbec): Frame(0x8, 0x20,
        'a5930cde357a2f330ad6efe8e81898116cf16d8ac814476b630a802c7c2848f4'),
    ('ov003', 0x0220e938): Frame(0x8, 0x26,
        'f2464354f965fdc6581501ccfeedac6f442912ffd00198f2c0373f924b7da1c4'),
    ('ov003', 0x0220ea78): Frame(0x8, 0x26,
        '4b58b8b62e2d6f98e888f3e714a40cdc229da44f413505e9aad02cc918971e8c'),
    ('ov003', 0x02210fa0): Frame(0x18, 0x6c,
        '8b078ab26130122b4a6dd0ed5c2dc0383b87e271172b1974abee2a8f37e6ac3d'),
    ('ov003', 0x022119f0): Frame(0x18, 0x5c,
        '425408a719667043b019ebbeb26f925c2c8223dac60fc3756b545dc8a6a10536'),
    ('ov003', 0x02211db0): Frame(0x10, 0x46,
        '24a6f7df1147878c4300be0d9ed651c5d515b148b6fa7945b9f272743bae7ef4'),
    ('ov003', 0x02212308): Frame(0x10, 0x40,
        'debb0f51291c4360419e2feac63ce1b5260c269d4605e8d37039335160c395bb'),
    ('ov003', 0x022124c4): Frame(0x20, 0xb0,
        '3da211a6a74ff68ec844895661e841c56bcfb9c4dfc0c943e2d260b3662a970f'),
    ('ov003', 0x02212884): Frame(0x10, 0xa8,
        'd8203e2e95dfbb911115310d74c220b88819b48260e5df17380044d1bafda904'),
    ('ov003', 0x02213b28): Frame(0x28, 0xc8,
        '38646c21741d150edb88530a5f760341cb20940d4f889beeff42e5f03a92e09e'),
    ('ov003', 0x02215394): Frame(0x10, 0x52,
        'cf162f7bfa862b27ae2828a360d566c77e7a5dd3a278a8d04e919ab0733192ce'),
    ('ov003', 0x02215bf8): Frame(0x10, 0x4c,
        'b4c426e8e30629210ebfab6c55f05f5da7f6b54a91916e268892c0e53efd2000'),
    ('ov003', 0x02215d1c): Frame(0x10, 0x9c,
        'b3365dc6c3c3d7b004560ce4b4cba0b8407da8f571f462a1e9edafabc0c5f9b9'),
    ('ov003', 0x0221615c): Frame(0x8, 0x20,
        '9a2f13f5b1b14d2db096279eb24caf196197425d08510a368a7d1b3f2b8a2afe'),
    ('ov003', 0x022166f8): Frame(0x10, 0x46,
        '1b1377b784146c45b002ee5efdba4710757c267ebf11db5e3b102a57af0d9f61'),
    ('ov003', 0x02216bfc): Frame(0x10, 0xa0,
        '2e215a3a0b5912fd7ed50d56bdbf267e364f2d232c8a0896f6ca5b5b38b28fdc'),
    ('ov003', 0x02216eec): Frame(0x18, 0xc4,
        'e24d85a5781b5d1fc04463555d3d9b1e3eaf0c4522078440778d7d670055f6a7'),
    ('ov003', 0x022172c4): Frame(0x8, 0x48,
        'dfc6c7ab08c9578be0228addb2ca5f0cefbe2e400865c219fd81f1326923c7ee'),
    ('ov003', 0x02218ff0): Frame(0x80, 0xc0,
        '392dc13e8918e6a83a39b77f3957d65f3ff89e77df2b22faf82a5f2fe8a60b63'),
    ('ov004', 0x02229860): Frame(0x18, 0x58,
        '2ea98790671d81038495be5b46c8babb71bf9fa432eb24593f4a200922af6602'),
    ('ov004', 0x02229a7c): Frame(0x8, 0x26,
        'd93c8a6b471c772043e9db18f22ea30e0511d8ba68a4b6a162ad12252228cb8f'),
    ('ov004', 0x02229bec): Frame(0x8, 0x26,
        '8dc3505f43a72f2cd744212d0394b233d0c93208775026b7b5ed88cc01453f2f'),
    ('ov004', 0x02229f60): Frame(0x8, 0x58,
        'a5a654be33fcbd1b334b38b937ca057dd2bb4137057042c4dd93e589ead774a9'),
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
    # A second caller of the consumer (house-pull): push {r4, lr}; sub sp, #0x10 at entry,
    # add sp, #0x10 before its one pop.
    ('ov004', 0x0223df48): Frame(0x18, 0x40,
        'cfce995cc8ebba032568775655a7651791870485812ed1e407aca59f602b4aa0'),
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


# The Clean consumer (HouseRoach_Move) zero-fills the centres; the ROM leaves their Y words
# as the stack held them. The mixed Native/Clean build compiles a copy that keeps the four
# centres at the same guest slot as the Native consumer, so they read the same residue.
CLEAN_SOURCE = 'clean/ov004/house_roach.c'
CLEAN_SHA = '8f67dcec77f544092fa1997e53c1d0ef1ce4384d3bf9d8b9ddd002e7ef8da5b6'


def clean_copy(text: str) -> str:
    if hashlib.sha256(text.encode()).hexdigest() != CLEAN_SHA:
        raise ValueError(f'Clean stack source changed; repeat the stack effect audit: {CLEAN_SOURCE}')
    declaration = '    Vec3 centres[HOUSE_ROACH_KEEP_OUT_BOXES] = {{0, 0, 0}};'
    # after the four box constructors, before any centre is set (as in the Native consumer)
    use = '\n'.join(['        CollisionBox_Construct(&boxes[i]);', '    }',
                     '    Vec3 *position = &roach->actor.position;'])
    assert text.count(declaration) == text.count(use) == 1
    text = text.replace(declaration, '    Vec3 *centres;')
    slot = '\n'.join([
        '    _Static_assert(HOUSE_ROACH_KEEP_OUT_BOXES == 4 && sizeof(Vec3) == 12, "house centre storage");',
        '    centres = (Vec3 *) (uintptr_t) native_guest_stack_slot(0x0223df88u, 0x28u, sizeof(Vec3) * 4);',
        '    Vec3 *position'])
    text = text.replace(use, use.replace('    Vec3 *position', slot))
    return '\n'.join(['#include "native_guest.h"', text])


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
