"""Audited ROM frames and the observable stack storage of the collision boxes (the house's
cockroach and the museum's insect room), of the room music cue and of a talk's reply (a villager's
house).

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
    # The museum's insect room (scene museum-halls): push {r4-r7, lr}; sub sp, #0x1fc; sub sp,
    # #0x18 at entry, the matching adds before its one pop; every call at entry SP - 0x228.
    # It is reached through 020ee934, 020ee9a0, 020ee834, 01ffd14c and 01ffd44c, audited above.
    ('ov004', 0x0223f218): Frame(0x228, 0x180,
        '2c62b38831f3358aafc8e2eb42494207c91cb7bb7b6cb213157b70d015145f65'),
    # The room music cue of a villager's house (scenes villager-birthday, sick-villager,
    # letter-errand): a room object's update (02210abc, through 01ffd44c, audited above) calls
    # 02215374 by its vtable, which calls 022150b8, which calls 02214c50 or 02214d34 through its
    # state table, each of which calls 02215298, then 020040bc, then the cue's update 020f9ea4.
    # Each saves registers with one push and reserves its frame with one sub at entry (02215374,
    # 022150b8 and 020f9b50 push only); its only other SP changes are the matching adds before
    # its pops, conditional ones (ARM addeq/popeq/bxeq) included; no computed branch; every call
    # at entry SP - extent.
    ('ov004', 0x02210abc): Frame(0x18, 0xd8,
        'dfa69a011e1311919bebefc431b6c68e199fe74e726bf50dda614d5ee7267fce'),
    ('ov004', 0x02215374): Frame(0x8, 0x20,
        '5a9b708cef4438944185e2ea02b0eee4af8ca57bc2450d83f75057016f6ba6c5'),
    ('ov004', 0x022150b8): Frame(0x10, 0x7c,
        '32820c06c82373786870adee11a96cb97bb8ab49e0b263e6e6439c3b3d52a5ad'),
    ('ov004', 0x02214c50): Frame(0x18, 0x88,
        'a56255c65ac0299bb03226831e2fa0f8681163c8a7c5ce7c2bca96c7321cd0ce'),
    ('ov004', 0x02214d34): Frame(0x18, 0xc4,
        '3035a4bc2cd2247e02a638ba271910b1cab491ba7b4ff207241af5ddaf350890'),
    ('ov004', 0x02215298): Frame(0x10, 0x38,
        'b6fc3143ddd15db31aed22fe4bdb6856ced9838de28edef094b0b26d1ff0b9fd'),
    ('main', 0x020040bc): Frame(0x18, 0x4c,
        '2389c80ac354f1aaddc5af4820f542ac7be3ee2ef46fe1b538cb75ab366bc1ac'),
    ('autoload_2', 0x020f9ea4): Frame(0x18, 0xa4,
        'ab74e3e41d13d121418ee4953c8b44a6e14d28359f0e84e96eba738e72a5dcda'),
    ('autoload_2', 0x020f9d00): Frame(0x18, 0x100,
        'e5da395294eea1c1157b5c34159d1edc556bbedb71e3d76f42bbfb5a9516ef53'),
    ('autoload_2', 0x020f9948): Frame(0x18, 0x208,
        '474c03d2dcfbc98c63eb1cd588251dfcc8a3e9cc2dfa9b98bd86b4615d3a292b'),
    ('autoload_2', 0x020f9b50): Frame(0x10, 0xbc,
        '9b0ad61ce0f94066054dc87bc7972914818b2f625d8ef7067a4366d6008d164e'),
    # push {r4, r5, lr}; sub sp, #4; four returns, each add sp, #4 before its pop
    ('autoload_2', 0x020f5e50): Frame(0x10, 0x158,
        '0b23d10c3d809b492f225c282f7bde29f2c54fa251b760f4f83ab4d3980880be'),
    # The matrix helpers the room object's matrix is built with: push {r4, lr}; sub sp, #0x30;
    # mov r4, r0; two calls; add sp, #0x30 before the one pop.
    ('autoload_2', 0x020e9744): Frame(0x38, 0x30,
        'f5cb33697b36f15ae5fb0728202d4125e691c811cbab34ffa5ec24b4f7025ade'),
    ('autoload_2', 0x020e9868): Frame(0x38, 0x30,
        '42811ed129b793d336f4723e585b05e690aa58d3703057495be41ad8a905ea60'),
    # The room object's matrix: push {r4-r7, lr}; sub sp, #0xc; add sp, #0xc before the one pop.
    ('ov004', 0x0220fc98): Frame(0x20, 0xf4,
        '56fe8d858dd701bb69a45294fc7f712f03b0bc1202cec1c7df4bf1397e7ff233'),
    # A talk's reply (scene letter-errand): the talk update (020a9ba0, from 01ffd44c, audited
    # above) through 0206823c, 02068144 (by its state table), 02066dc4 and 020671b0, which calls
    # 020673e0 (the picked answer's text walker, at body SP + 0) and then 02067504, which calls
    # 0201ce68 by its vtable, which calls 020288bc by a member pointer. One push and one sub at
    # entry each (0206823c, 02068144, 02067504 and 0201ce68 push only), the matching add before
    # the one pop; no computed branch; every call at entry SP - extent.
    ('main', 0x020a9ba0): Frame(0x8, 0x18,
        '4f8c79e69b2739ee7fb5acef092426ce7f46dfb5ae0df8dc2f9a65ab3a84d0f0'),
    ('main', 0x0206823c): Frame(0x10, 0x30,
        'd1f4895939d87f75b74e2b2d5785230bb7ff82a2661767ce7eab90759d0bbd52'),
    ('main', 0x02068144): Frame(0x10, 0xc8,
        'dbf9450e3abb1060d1a7a29d99d621698222e8f314905fd5e4523a34dbda98cc'),
    ('main', 0x02066dc4): Frame(0x18, 0x15c,
        '53531b4562c1127d5d5258e4b42b9af387151eca0d6fa2d2c2a711c77991b4bf'),
    ('main', 0x020671b0): Frame(0x10, 0x4c,
        '19ca9cf8b5c1922ffe258dd8264515015db88a78fa8e83f330c8c1c513891f0f'),
    ('main', 0x020673e0): Frame(0x50, 0x3c,
        '391a2896b38f6bcee2a124f42324e2e4423b3c16a35719d0bdd92a1c3bd69881'),
    ('main', 0x02067504): Frame(0x8, 0x3c,
        '3cf4c44c94ebe216077dc38629f7c25deebeeb490a512241f2cbe680f1249e04'),
    ('main', 0x0201ce68): Frame(0x10, 0x60,
        '6e8f74574a257f16125899e8cfea718e709a436497016f269b52874c901323af'),
    ('main', 0x020288bc): Frame(0x18, 0x68,
        '591019f2c2a1da40f78a5d577d5ab483aaeb5dec4e358e507d09e5b12e9e5135'),
}

# The registers a function's entry push saves (bit n: rn), for audited frames above. Its
# code changes no other register of r4-r11, so its callees find those as its caller left
# them; and the push stores the caller's values of these below the entry SP, lowest first.
# The runtime knows a register's value where a PC copy says what the ROM's code puts there
# (native_guest_register): its callees' pushes then store it on the ROM's stack, and a call
# from Native code into the ROM's code hands it in that register.
SAVES: dict[tuple[str, int], int] = {
    ('autoload_2', 0x020e9744): (1 << 4) | (1 << 14),
    ('autoload_2', 0x020e9868): (1 << 4) | (1 << 14),
    ('autoload_2', 0x020f5e50): (1 << 4) | (1 << 5) | (1 << 14),
}

SOURCES = {
    'ov004/func_ov004_0223df88.cpp': 'f83678a3e49cb33c093f9187915bc3630a7241ac452719b8cd7aa5aa592a432d',
    'ov004/func_ov004_0220dd80.cpp': '2f88fa901fa5fd612e351526a20dc5960b608c3ca7dc45bfdc6b7a8df14f9da2',
    'ov004/func_ov004_0223f218.c': '1cc7f0ec2ec6ac9bc48d217a7ec4563a201af55c4f820ea666432981efe7b08b',
    'ov004/func_ov004_0220fc98.c': 'f47d4d5a656fce404914d68fabd46902e4ccec9157e1005a9651aaf0095d2df3',
    'main/func_020040bc.c': '96751c4d7cb3c180e22a6c66cc24776c71c015e57e7934b0a24e47c380d391ee',
    'autoload_2/func_020f9d00.c': 'ba4aca4075e533e87827e8cfd6ec8fe68dd4b47232c717498530b7ccbf243815',
    'autoload_2/func_020f9948.c': 'bb7691589316d5ff734817e02d2a7432768ecf6e5d1127e0b38c1b8ee583b9f1',
    'autoload_2/func_020f9b50.c': '8ee9d17fa55087735aa61ca4167de0d86317cc2b59e0196261b966626ad2bbe8',
    'autoload_2/func_020e9744.c': '695a45d63baf6a0380f74f3c00242cffbd0fe9fa6de1b029dfea1b13f98745c5',
    'autoload_2/func_020e9868.c': 'f984fae7452a68938700f472c97aa46ae0706bdfd2036713a493c6b18d17cfc7',
    'main/func_020673e0.cpp': 'cd577805cab4c936f30abf96ffc8073c98375c13d2a2c74a821386c54b5bc542',
    'main/func_020288bc.cpp': '73a4105a8d434eff733a727ec79a3c01263d4c3b60050947c8c5de18125ca8ce',
}
CONSUMER = 'ov004/func_ov004_0223df88.cpp'
# The insect room's three cases (func_ov004_0223f218) are collision boxes whose centres it
# sets x and z of and leaves y as the ROM's stack held it, at body SP + 0x18 (0x18-0x3c, below
# the first box at + 0x3c): the same uninitialized-centre reuse as the house's consumer.
INSECT_ROOM = 'ov004/func_ov004_0223f218.c'
# 0220dd8a stores incoming r3 at SP+0x14 before the first call. Apply the
# same spill to Native and Clean entries; its value comes from their input.
SPILLS = {('ov004', 0x0220dd80): (3, 0x14)}


# The Clean consumer (HouseRoach_Move) zero-fills the centres; the ROM leaves their Y words
# as the stack held them. The mixed Native/Clean build compiles a copy that keeps the four
# centres at the same guest slot as the Native consumer, so they read the same residue.
CLEAN_SOURCE = 'clean/ov004/house_roach.c'
CLEAN_SHA = '8f67dcec77f544092fa1997e53c1d0ef1ce4384d3bf9d8b9ddd002e7ef8da5b6'
# The Clean insect room (InsectRoom_Update) sets the cases' centres' y to 0 (its BUG: note); the
# copy keeps the centres at the Native one's guest slot instead.
CLEAN_INSECT_ROOM = 'clean/ov004/museum_insects.c'
CLEAN_INSECT_ROOM_SHA = '45e08a82912b7318462828f88a8bb2b2b4433cf6448fef92c250b8d45d508ef3'
# The Clean versions of the cue's functions and of the room object's matrix (CUE_EDITS): the
# Clean sources keep 0 where the ROM reads its stack (their BUG: notes); the mixed Native/Clean
# build compiles copies with the Native ones' guest slots and registers.
CLEAN_CUE_SHA = {
    'clean/autoload_2/music_cue.c': '5e0d82994301bbde71bb4747d619c4a7ebf8558c757f9285fc36420a0c6a9dd1',
    'clean/main/sound.c': 'a3586d017d1904fff5767fccdfa204d284d592d3d1d01561bb1d63012235f1e3',
    'clean/ov004/room_object_body.c': 'a81d9c712679eaee62c0fcb2753f87672e39372fd1d63528c74ca141e8da2f5b',
    'clean/main/talk_object.c': '37cfd8f848a074074c8b6042f162dda826f4a00098f969c8c9eda449a5517d9d',
    'clean/main/villager_talk_offers.c': '432ba2c273a6b6d71b482ec0d814d1e527956447099b3845a7a1cf4aa87b85df',
    'clean/autoload_2/matrix.c': '6e4e1fe2d50a238897e20e224004b63f073337a296a08fa10158644c8527cf18',
}
CLEAN_CUE_EDITS: dict[str, tuple[tuple[str, str], ...]] = {
    'clean/autoload_2/music_cue.c': (
        ('    int position;\n\n    if (cue->layout == 1 || cue->layout == 3) {\n'
         '        progress = shl(beats_since((s16) cue->start), 14);\n',
         '    int position;\n'
         '    s16 *stack = (s16 *) (uintptr_t) native_guest_stack_slot(0x020f9948u, 0, 2 * sizeof(s16));\n\n'
         '    if (cue->layout == 1 || cue->layout == 3) {\n'
         '        stack[0] = (s16) cue->start;\n'
         '        progress = shl(beats_since(stack[0]), 14);\n'),
        ('    s16 start = 0;\n    s16 unused = 0;\n    NNS_SndPlayerReadVariable(&cue->handle, 7, &start);\n'
         '    NNS_SndPlayerReadVariable(&cue->handle, 12, &unused);\n    beats = beats_since(start);\n',
         '    NNS_SndPlayerReadVariable(&cue->handle, 7, &stack[0]);\n'
         '    NNS_SndPlayerReadVariable(&cue->handle, 12, &stack[1]);\n    beats = beats_since(stack[0]);\n'),
        ('    int ratio;\n\n    if (pos == NULL) {\n',
         '    int ratio;\n\n'
         '    native_guest_register(0x020f9b50u, 5, (uint32_t) (uintptr_t) pos);\n'
         '    native_guest_register(0x020f9b50u, 4, (uint32_t) (uintptr_t) cue);\n'
         '    if (pos == NULL) {\n'),
        ('    volume = SoundPosition_VolumeAt(SoundPosition_Distance(pos, 0));\n    pan = SoundPosition_Pan(pos, 0);\n',
         '    volume = SoundPosition_VolumeAt(SoundPosition_Distance(pos, 0));\n'
         '    native_guest_register(0x020f9b50u, 6, (uint32_t) volume);\n'
         '    pan = SoundPosition_Pan(pos, 0);\n'
         '    native_guest_register(0x020f9b50u, 5, (uint32_t) pan);\n'),
        ('    s16 beat_no = 0;\n    s16 position = 0;\n    s16 target = 0;\n    s16 start = 0;\n    s16 next = 0;\n'
         '    s16 length = 0;\n\n    if (cue->layout <= 0) {\n        MusicCue_ReadMarks(cue);\n    }\n'
         '    NNS_SndPlayerReadGlobalVariable(2, &beat_no);\n    NNS_SndPlayerReadGlobalVariable(1, &position);\n'
         '    NNS_SndPlayerReadVariable(&cue->handle, 8, &target);\n    NNS_SndPlayerReadVariable(&cue->handle, 7, &start);\n'
         '    NNS_SndPlayerReadVariable(&cue->handle, 12, &next);\n    NNS_SndPlayerReadVariable(&cue->handle, 6, &length);\n\n'
         '    data_021fd26c = beat_no;\n    data_021fd270 = position;\n    cue->target = (s8) target;\n'
         '    cue->start = (s8) start;\n    cue->next = (s8) next;\n    cue->length = (s8) length;\n',
         '    s16 *vars = (s16 *) (uintptr_t) native_guest_stack_slot(0x020f9d00u, 0, 6 * sizeof(s16));\n\n'
         '    if (cue->layout <= 0) {\n        MusicCue_ReadMarks(cue);\n    }\n'
         '    NNS_SndPlayerReadGlobalVariable(2, &vars[0]);\n    NNS_SndPlayerReadGlobalVariable(1, &vars[1]);\n'
         '    NNS_SndPlayerReadVariable(&cue->handle, 8, &vars[2]);\n    NNS_SndPlayerReadVariable(&cue->handle, 7, &vars[3]);\n'
         '    NNS_SndPlayerReadVariable(&cue->handle, 12, &vars[4]);\n    NNS_SndPlayerReadVariable(&cue->handle, 6, &vars[5]);\n\n'
         '    data_021fd26c = vars[0];\n    data_021fd270 = vars[1];\n    cue->target = (s8) vars[2];\n'
         '    cue->start = (s8) vars[3];\n    cue->next = (s8) vars[4];\n    cue->length = (s8) vars[5];\n')),
    'clean/main/sound.c': (
        ('    Vec3 rel = relative(pos);\n    return MusicCue_Update(cue, &rel);\n',
         '    Vec3 *rel = (Vec3 *) (uintptr_t) native_guest_stack_slot(0x020040bcu, 0, sizeof(Vec3));\n'
         '    *rel = relative(pos);\n    return MusicCue_Update(cue, rel);\n'),),
    'clean/ov004/room_object_body.c': (
        ('void RoomObject_BuildMatrix(RoomObject *object, Vec3 *offset, int turn)\n{\n',
         'void RoomObject_BuildMatrix(RoomObject *object, Vec3 *offset, int turn)\n{\n'
         '    native_guest_register(0x0220fc98u, 5, (uint32_t) (uintptr_t) object);\n'
         '    native_guest_register(0x0220fc98u, 4, (uint32_t) (uintptr_t) offset);\n'
         '    native_guest_register(0x0220fc98u, 6, (uint32_t) turn);\n'),
        ('        void *objects = RoomObjects_Table();\n        RoomObject *below',
         '        void *objects = RoomObjects_Table();\n'
         '        native_guest_register(0x0220fc98u, 7, (uint32_t) (uintptr_t) objects);\n        RoomObject *below'),
        ('        fx32 z = Mount_Offset(&object->mount)->z;\n',
         '        fx32 z = Mount_Offset(&object->mount)->z;\n        native_guest_register(0x0220fc98u, 6, (uint32_t) z);\n'),
        ('        fx32 y = Mount_Offset(&object->mount)->y;\n',
         '        fx32 y = Mount_Offset(&object->mount)->y;\n        native_guest_register(0x0220fc98u, 4, (uint32_t) y);\n'),
        ('        s16 angle = (s16) (object->angle + turn);\n',
         '        s16 angle = (s16) (object->angle + turn);\n'
         '        native_guest_register(0x0220fc98u, 4, (uint32_t) (int) angle);\n')),
    'clean/autoload_2/matrix.c': (
        ('void Mtx43_RotateY(Mtx43 *mtx, int angle)\n{\n',
         'void Mtx43_RotateY(Mtx43 *mtx, int angle)\n{\n'
         '    native_guest_register(0x020e9744u, 4, (uint32_t) (uintptr_t) mtx);\n'),
        ('void Mtx43_Translate(Mtx43 *mtx, fx32 x, fx32 y, fx32 z)\n{\n',
         'void Mtx43_Translate(Mtx43 *mtx, fx32 x, fx32 y, fx32 z)\n{\n'
         '    native_guest_register(0x020e9868u, 4, (uint32_t) (uintptr_t) mtx);\n')),
    'clean/main/talk_object.c': (
        ('    u32 walker[TALK_OBJECT_ANSWER_WALKER_SIZE / sizeof(u32)];\n',
         '    u32 host_walker[TALK_OBJECT_ANSWER_WALKER_SIZE / sizeof(u32)];\n'
         '    u32 *walker = (u32 *) (uintptr_t) native_guest_stack_slot_if(0x020673e0u, 0, sizeof(host_walker));\n'
         '    if (walker == NULL) {\n        walker = host_walker;\n    }\n'),),
    'clean/main/villager_talk_offers.c': (
        ('    VillagerTalkLine line = {0};\n    if (offer_set_line(talk, &line) && line.text != 0) {\n'
         '        u8 message = line.message;\n'
         '        TalkObject_SetMessageIfNone((TalkObject *) (void *) offer_talk(talk), &message,\n'
         '                                    (const char *) (uintptr_t) ((int) line.text));\n',
         '    _Static_assert(sizeof(VillagerTalkLine) == 8, "the line");\n'
         '    u8 *message = (u8 *) (uintptr_t) native_guest_stack_slot(0x020288bcu, 0, 4 + sizeof(VillagerTalkLine));\n'
         '    VillagerTalkLine *line = (VillagerTalkLine *) (void *) (message + 4);\n'
         '    if (offer_set_line(talk, line) && line->text != 0) {\n'
         '        *message = line->message;\n'
         '        TalkObject_SetMessageIfNone((TalkObject *) (void *) offer_talk(talk), message,\n'
         '                                    (const char *) (uintptr_t) ((int) line->text));\n'),),
}
CLEAN_SOURCES = (CLEAN_SOURCE, CLEAN_INSECT_ROOM, *CLEAN_CUE_SHA)


# The room music cue (docs/native-guest-stack.md). Its first update in a villager's house finds
# the cue's handle without a player, so NNS_SndPlayerReadVariable leaves its out-parameters
# alone. func_020f9d00 then keeps in the cue (bytes 0xb-0xe) what its frame (body SP + 4 to
# + 0xb) held: r5 and r6 of the room object's matrix code (func_ov004_0220fc98: the object
# and its turn, or its mount's z), which MTX_Concat43's entry push stored there when
# func_020e9744 and func_020e9868 called it just before, at the same depth. func_020f9948 goes
# on from body SP + 0 and + 2: r5 of func_020f9b50 (its `pos`, the address of
# func_020040bc's local copy of the position), stored there by func_020f5e50's entry push.
# The PC copies keep those locals in the ROM's frames and say what the ROM's code holds in
# the registers those pushes store.
CUE_EDITS: dict[str, tuple[tuple[str, str], ...]] = {
    # 0220fc9c-0220fca0: r5 = the object, r4 = `p1`, r6 = `p2`; mounted: r7 = the objects'
    # table (0220fcb2), r6 = the mount's z (0220fcf0), r4 its y (0220fcfa); else r4 = the angle
    # (0220fd44).
    'ov004/func_ov004_0220fc98.c': (
        ('    short h;\n\n',
         '    short h;\n\n'
         '    native_guest_register(0x0220fc98u, 5, (uint32_t) (uintptr_t) self);\n'
         '    native_guest_register(0x0220fc98u, 4, (uint32_t) (uintptr_t) p1);\n'
         '    native_guest_register(0x0220fc98u, 6, (uint32_t) p2);\n'),
        ('        o = func_ov004_0223cd58(func_ov004_0223ce84(), func_ov004_0220d4c0(self + 0x17c));\n',
         '        int *table = func_ov004_0223ce84();\n'
         '        native_guest_register(0x0220fc98u, 7, (uint32_t) (uintptr_t) table);\n'
         '        o = func_ov004_0223cd58(table, func_ov004_0220d4c0(self + 0x17c));\n'),
        ('        pz = func_ov004_0220d4bc(self + 0x17c)->z;\n',
         '        pz = func_ov004_0220d4bc(self + 0x17c)->z;\n'
         '        native_guest_register(0x0220fc98u, 6, (uint32_t) pz);\n'),
        ('        py = func_ov004_0220d4bc(self + 0x17c)->y;\n',
         '        py = func_ov004_0220d4bc(self + 0x17c)->y;\n'
         '        native_guest_register(0x0220fc98u, 4, (uint32_t) py);\n'),
        ('        h = (short) (*(short *) (self + 0x8e) + p2);\n',
         '        h = (short) (*(short *) (self + 0x8e) + p2);\n'
         '        native_guest_register(0x0220fc98u, 4, (uint32_t) (int) h);\n')),
    # 020e974c / 020e9870: r4 = the matrix
    'autoload_2/func_020e9744.c': (
        ('{\n    char local[0x30];\n',
         '{\n    char local[0x30];\n    native_guest_register(0x020e9744u, 4, (uint32_t) param);\n'),),
    'autoload_2/func_020e9868.c': (
        ('{\n    char buf[0x30];\n',
         '{\n    char buf[0x30];\n    native_guest_register(0x020e9868u, 4, (uint32_t) (uintptr_t) arg);\n'),),
    # 020f9b54-020f9b58: r5 = `b`, r4 = `a`; r6 = the volume (020f9b74), r5 = the pan (020f9b84)
    'autoload_2/func_020f9b50.c': (
        ('    unsigned int flag;\n\n',
         '    unsigned int flag;\n\n'
         '    native_guest_register(0x020f9b50u, 5, (uint32_t) (uintptr_t) b);\n'
         '    native_guest_register(0x020f9b50u, 4, (uint32_t) (uintptr_t) a);\n'),
        ('    r6 = func_020f5e24(func_020f5e50(b, 0));\n    r5 = func_020f5c64(b, 0);\n',
         '    r6 = func_020f5e24(func_020f5e50(b, 0));\n'
         '    native_guest_register(0x020f9b50u, 6, (uint32_t) r6);\n'
         '    r5 = func_020f5c64(b, 0);\n'
         '    native_guest_register(0x020f9b50u, 5, (uint32_t) r5);\n')),
    # the position relative to the camera at body SP + 0 (020040da-020040ea)
    'main/func_020040bc.c': (
        ('    UnkStruct_020040bc t;\n', '    UnkStruct_020040bc *t;\n'),
        ('        t.x = v->x - data_021c67b8.x;\n',
         '        t = (UnkStruct_020040bc *) (uintptr_t) native_guest_stack_slot(0x020040bcu, 0, sizeof(*t));\n'
         '        t->x = v->x - data_021c67b8.x;\n'),
        ('        t.y = v->y - data_021c67b8.y;\n', '        t->y = v->y - data_021c67b8.y;\n'),
        ('        t.z = v->z - data_021c67b8.z;\n', '        t->z = v->z - data_021c67b8.z;\n'),
        ('        return func_020f9ea4(self, &t);\n', '        return func_020f9ea4(self, t);\n')),
    # the six variables at body SP + 0 to + 0xb (020f9d1c-020f9d6c)
    'autoload_2/func_020f9d00.c': (
        ('    signed short vars[6];\n', '    signed short *vars;\n'),
        ('    if (((signed char *) self)[9] <= 0) {\n',
         '    vars = (signed short *) (uintptr_t) native_guest_stack_slot(0x020f9d00u, 0, 6 * sizeof(*vars));\n'
         '    if (((signed char *) self)[9] <= 0) {\n')),
    # v0 and v1 at body SP + 0 and + 2 (020f9970, 020f9a08, 020f9a14). Unset on some paths: in
    # the layouts other than 1 and 3, a span (self->unk_0A) other than 1, 2, 4 and 0x63 leaves
    # r5 as it came (020f9a3c-020f9a74), and a beat variable 6 other than 0 and 1 leaves r4
    # (020f9a94-020f9acc). The one caller, func_020f9ea4, calls it at 020f9ef8 with r4 = the
    # cue (020f9eac) and r5 = -0x1000 (020f9ec0, its default result).
    'autoload_2/func_020f9948.c': (
        ('    short v0, v1;\n    int d, r5, r4, t;\n',
         '    short *v = (short *) (uintptr_t) native_guest_stack_slot(0x020f9948u, 0, 2 * sizeof(short));\n'
         '    int d, r5 = -0x1000, r4 = (int) self, t;\n'),
        ('        v0 = self->unk_0C;\n        d = data_021fd26c - v0;\n',
         '        v[0] = self->unk_0C;\n        d = data_021fd26c - v[0];\n'),
        ('        NNS_SndPlayerReadVariable(self, 7, &v0);\n        NNS_SndPlayerReadVariable(self, 0xc, &v1);\n'
         '        d = data_021fd26c - v0;\n',
         '        NNS_SndPlayerReadVariable(self, 7, &v[0]);\n        NNS_SndPlayerReadVariable(self, 0xc, &v[1]);\n'
         '        d = data_021fd26c - v[0];\n')),
    # A talk's reply (func_020288bc) takes the line its line function gives (out, at body SP + 4,
    # and the message byte at + 0); the letter's (func_02027cc8) gives none, and the ROM goes on
    # with what that stack held: the text walker that func_020673e0 had at its body SP + 0 for
    # the answer picked just before, its fields at + 0x24 and + 0x28 (the talk object, 0). The
    # walker lives in the ROM's frame where its path is audited (else the PC's stack, as before:
    # it is used on many paths); the reply's locals always (a reply off the audited path stops).
    'main/func_020673e0.cpp': (
        ('{\n    char buf[0x44];\n',
         '{\n    char host_buf[0x44];\n'
         '    char *buf = (char *) (uintptr_t) native_guest_stack_slot_if(0x020673e0u, 0, sizeof(host_buf));\n'
         '    if (buf == 0) {\n        buf = host_buf;\n    }\n'),),
    'main/func_020288bc.cpp': (
        ('    unsigned char arg;\n    UnkStruct_020288bc out;\n',
         '    static_assert(sizeof(UnkStruct_020288bc) == 8, "the line");\n'
         '    unsigned char *arg = (unsigned char *) (uintptr_t) native_guest_stack_slot(0x020288bcu, 0, 0xc);\n'
         '    UnkStruct_020288bc *out = (UnkStruct_020288bc *) (arg + 4);\n'),
        ('        (self->*(self->pmf))(&out);\n        if (out.n) {\n            arg = out.b;\n'
         '            func_02068484(self->unk_40, &arg, out.n);\n',
         '        (self->*(self->pmf))(out);\n        if (out->n) {\n            *arg = out->b;\n'
         '            func_02068484(self->unk_40, arg, out->n);\n')),
}


def edit(text: str, edits: tuple[tuple[str, str], ...], relative: str) -> str:
    for before, after in edits:
        if text.count(before) != 1:
            raise ValueError(f'Stack effect edit no longer applies; repeat the stack effect audit: {relative}')
        text = text.replace(before, after)
    return text


def clean_copy(text: str, relative: str = CLEAN_SOURCE) -> str:
    if relative == CLEAN_INSECT_ROOM:
        return clean_insect_room_copy(text)
    if relative in CLEAN_CUE_SHA:
        if hashlib.sha256(text.encode()).hexdigest() != CLEAN_CUE_SHA[relative]:
            raise ValueError(f'Clean stack source changed; repeat the stack effect audit: {relative}')
        return '\n'.join(['#include "native_guest.h"', edit(text, CLEAN_CUE_EDITS[relative], relative)])
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


def clean_insect_room_copy(text: str) -> str:
    if hashlib.sha256(text.encode()).hexdigest() != CLEAN_INSECT_ROOM_SHA:
        raise ValueError(f'Clean stack source changed; repeat the stack effect audit: {CLEAN_INSECT_ROOM}')
    # after the three box constructors, before any centre is set (as in the Native consumer)
    use = '    CollisionBox_Construct(&boxes[2]);\n'
    centre = '        Vec3 centre = {cases[i].x, 0, cases[i].z};\n'
    call = 'INSECT_CASE_HEIGHT, &centre, 0, NULL);'
    assert text.count(use) == text.count(centre) == text.count(call) == 1
    text = text.replace(use, use + '\n'.join([
        '    _Static_assert(sizeof(Vec3) == 12, "insect room centre storage");',
        '    Vec3 *centres = (Vec3 *) (uintptr_t) native_guest_stack_slot(0x0223f218u, 0x18u, sizeof(Vec3) * 3);', '']))
    text = text.replace(centre, '        centres[i].x = cases[i].x;\n        centres[i].z = cases[i].z;\n')
    text = text.replace(call, 'INSECT_CASE_HEIGHT, &centres[i], 0, NULL);')
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
    return {CONSUMER, INSECT_ROOM, *CUE_EDITS}


def translate(relative: str, text: str, base: str | None = None) -> str | None:
    """The PC copy of `text`; `base`, when given, is another transform's copy of it (a member
    pointer's, tools/native_pmf.py) that the stack effect edits instead."""
    if relative in CUE_EDITS:
        validate_source(relative, text)
        text = text if base is None else base
        return '#include "native_guest.h"\n' + edit(text, CUE_EDITS[relative], relative)
    if relative == INSECT_ROOM:
        validate_source(relative, text)
        declaration = '    Vec centers[3];\n'
        use = '    func_020324fc(&collision[2]);\n'
        assert text.count(declaration) == text.count(use) == 1
        text = text.replace(declaration, '    Vec *centers;\n')
        text = text.replace(use, use + '    centers = (Vec *) (uintptr_t) native_guest_stack_slot(0x0223f218u, 0x18u, '
                            'sizeof(Vec) * 3);\n')
        return '#include "native_guest.h"\n' + text
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
