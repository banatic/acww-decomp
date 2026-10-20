"""PC copies for locals whose adjacency is observable in the ROM.

Only audited declarations are grouped. Values and calls are unchanged; source
digests require a new audit whenever the matching source changes.
"""
from __future__ import annotations

import hashlib
import re


# path -> digest, original declarations, grouped fields, names, second-field offset
VERIFIED = {
    # Request state 0x5e: header at sp, flag/point payload at sp+12.
    # ROM 02211d58/02211d7a/02211d86 construct, fill and submit it.
    "ov003/func_ov003_02211d4c.c": (
        "78573d87ff144b3390d3349dab731cedbd277a0dfcf1acf84ac5aec94d23fb4c",
        "UnkStruct_02211d4c local1;\n    Buf local3;",
        "UnkStruct_02211d4c local1; Buf local3;", ("local1", "local3"), 12,
    ),
    # Request state 0x5f: header at sp+4 and payload at sp+16.
    # ROM 02211904/02211926/02211952 preserve their 12-byte adjacency.
    "ov003/func_ov003_022118f8.c": (
        "79d5e07c746786857237fdb4360f4ea3f038809f28c0f953758b2aeae3856302",
        "struct Buf buf;\n    struct UnkStruct_022118f8_2 out;",
        "struct Buf buf; struct UnkStruct_022118f8_2 out;", ("buf", "out"), 12,
    ),
    # The no-item state 0x5f request uses sp and sp+12 instead.
    # ROM 0221198c/022119ae/022119bc construct, fill and submit it.
    "ov003/func_ov003_02211980.c": (
        "800f4556da5246cc57cc399d0587fbea612a6481b3bbc96a0541f0fe7a8b3ef6",
        "char local[12];\n    char local2[16];",
        "char local[12]; char local2[16];", ("local", "local2"), 12,
    ),
    # ROM 0201c2da/0201c2dc pass sp+8 and sp+16. 0201c2ec passes sp+8
    # as a vector whose Z at +8 is the second output of func_02096614.
    "main/func_0201c2c8.c": (
        "8019fa3f73ce1b12030668d4eb3d340cc7c61cd7c0a7867fbb472c24a6b3764d",
        "unsigned int dataA[2];\n    unsigned int dataB[2];",
        "unsigned int dataA[2]; unsigned int dataB[2];", ("dataA", "dataB"), 8,
    ),
    # ROM 02215f0c constructs the request at sp; 02215f2a fills its payload
    # at sp+12, and 02215f34 submits that same request at sp.
    "ov003/func_ov003_02215f00.c": (
        "128cf5d73d2ea2f1074c3f4bf9b59ed5d1c3111f3078c2cc1432b63174c8f4b9",
        "char ctx[12];\n    int out[4];",
        "char ctx[12]; int out[4];", ("ctx", "out"), 12,
    ),
    # ROM 020a96a8 passes sp to func_02064658, which reads eight bytes there; 020a96d6 passes
    # sp+4, the second word, to func_020a9ae4.
    "main/func_020a967c.c": (
        "ca88991a5cbe2d7ac890b5e8a99f420b2e0e0ebb0d68528aa9b9cef67ff8d735",
        "int local1;\n    int local2;",
        "int local1; int local2;", ("local1", "local2"), 4,
    ),
    # ROM 0201357a/0201357c pass sp+0x2c and sp+0x30 to func_0204f818 as the two outputs;
    # 02013614 passes sp+0x2c to func_020137ec as a two-word point.
    "main/func_0201354c.c": (
        "6973828aef4f4b7f1d1cd3dffe1a89e9a09709d97486f0b1967995945f5afd77",
        "u32 s2c;\n    u32 s30;",
        "u32 s2c; u32 s30;", ("s2c", "s30"), 4,
    ),
    # Request builders: func_0200e92c/func_0200e90c construct a 12-byte header that
    # func_0200e894 submits; it reads the payload right after it, which the source keeps in the
    # next local. Each ROM body passes the header and the payload 12 bytes apart.
    # ROM 02009a44: the header at sp+0x4 goes to func_0200e894, func_02009a9c fills the payload at sp+0x10.
    "main/func_02009a44.c": (
        "5a2ff452fc464f776ecf32b6ff841d3750d0b3f1cf153f4f575d8f5ac29c4556",
        "char bufA[12];\n    char bufB[20];",
        "char bufA[12]; char bufB[20];", ("bufA", "bufB"), 12,
    ),
    # ROM 0200a6a0: the header at sp+0x8 goes to func_0200e894, func_0200a6f0 fills the payload at sp+0x14.
    "main/func_0200a6a0.c": (
        "61ba529c067e3fab5561f9470437fa5df60b98bc75b9a0c7a63172c4a86b0c3f",
        "char local1[12];\n    char local2[16];",
        "char local1[12]; char local2[16];", ("local1", "local2"), 12,
    ),
    # ROM 0200acd4: the header at sp+0xc goes to func_0200e894, func_0200ad78 fills the payload at sp+0x18.
    "main/func_0200acd4.c": (
        "b6b847093b184cf4060cf29bb912a7216c51ca44705eefe6797fe1a987039fe8",
        "char buf1[12];\n    char buf2[20];",
        "char buf1[12]; char buf2[20];", ("buf1", "buf2"), 12,
    ),
    # ROM 0200ad24: the header at sp+0x8 goes to func_0200e894, func_0200ad78 fills the payload at sp+0x14.
    "main/func_0200ad24.c": (
        "32b771f0924bc0dfdcca236a65017ec55dadbe29809123cf18a34b367557efac",
        "char obj[12];\n    char out[16];",
        "char obj[12]; char out[16];", ("obj", "out"), 12,
    ),
    # ROM 0200b7e8: the header at sp+0x10 goes to func_0200e894, func_0200b894 fills the payload at sp+0x1c.
    "main/func_0200b7e8.c": (
        "410ae993d855d118d0e30d4d56f4cc8429e88e1a2dfde4ddff6d36b827e93de2",
        "char obj[12];\n    char tmp[16];",
        "char obj[12]; char tmp[16];", ("obj", "tmp"), 12,
    ),
    # ROM 0200c3b0: the header at sp+0x0 goes to func_0200e894, func_0200c3f0 fills the payload at sp+0xc.
    "main/func_0200c3b0.c": (
        "558489ac5dc2fe11bb13252cf0c3fa0cc4b1be10eabf6b8c406338216cccaeb6",
        "char a[0xc];\n    char b[0x10];",
        "char a[0xc]; char b[0x10];", ("a", "b"), 12,
    ),
    # ROM 0200cc00: the header at sp+0x0 goes to func_0200e894, func_0200cc40 fills the payload at sp+0xc.
    "main/func_0200cc00.c": (
        "64a88ecb28fa2ec3a4dba3c0a4b6f9403d4e00597b874c06aeb8b9188e0c9a26",
        "char s1[12];\n    char s2[16];",
        "char s1[12]; char s2[16];", ("s1", "s2"), 12,
    ),
    # ROM 0200dbb4: the header at sp+0x0 goes to func_0200e894, func_0200dc00 fills the payload at sp+0xc.
    "main/func_0200dbb4.c": (
        "ffa8c29957543b55b470676850a0b64cd328cc97b328652b6a0a79edec0e017f",
        "int stack0[3];\n    int stack1[4];",
        "int stack0[3]; int stack1[4];", ("stack0", "stack1"), 12,
    ),
    # ROM 0220fb30: the header at sp+0x8 goes to func_0200e894, func_ov003_0220fb80 fills the payload at sp+0x14.
    "ov003/func_ov003_0220fb30.c": (
        "4108b456655138bbc3d48115549a424379fd10166d2980fa7340ba4447726b6e",
        "char buf1[12];\n    char buf2[16];",
        "char buf1[12]; char buf2[16];", ("buf1", "buf2"), 12,
    ),
    # ROM 0220fda0: the header at sp+0x0 goes to func_0200e894, func_ov003_0220fdf4 fills the payload at sp+0xc.
    "ov003/func_ov003_0220fda0.c": (
        "c06c918086cd83e07dec264c9b1bb8ce25fbd793dd7207068442bae3929873e2",
        "int buf[3];\n    int out[4];",
        "int buf[3]; int out[4];", ("buf", "out"), 12,
    ),
    # ROM 02212830: the header at sp+0x8 goes to func_0200e894, func_ov003_02212878 fills the payload at sp+0x14.
    "ov003/func_ov003_02212830.c": (
        "bbf4e2a5713c020bb7a2b18a487868b71db4687edeb713e5bc4b9fe36cec3d8e",
        "unsigned char buf2[12];\n    unsigned char buf3[16];",
        "unsigned char buf2[12]; unsigned char buf3[16];", ("buf2", "buf3"), 12,
    ),
    # ROM 02212c10: the header at sp+0x4 goes to func_0200e894, func_ov003_02212d04 fills the payload at sp+0x10.
    "ov003/func_ov003_02212c10.c": (
        "75d5f56dc0a8d42d1acb856d96002c3a7b1e3127949f7d7fe3d85d8f0992a312",
        "char local1[12];\n    char local2[20];",
        "char local1[12]; char local2[20];", ("local1", "local2"), 12,
    ),
    # ROM 02215624: the header at sp+0x0 goes to func_0200e894, func_ov003_02215664 fills the payload at sp+0xc.
    "ov003/func_ov003_02215624.c": (
        "27b7012d8eb70b19028249fa56a6a68f004ce70691d3076c86f2b8ddb024e240",
        "char s1[12];\n    char s2[16];",
        "char s1[12]; char s2[16];", ("s1", "s2"), 12,
    ),
    # ROM 02216410: the header at sp+0x8 goes to func_0200e894, func_ov003_02216460 fills the payload at sp+0x14.
    "ov003/func_ov003_02216410.c": (
        "1ef90141a083b68b6b536d15888eae6a12d605cabe90b6c0b5eccaa08063cfcb",
        "char obj[12];\n    char out[16];",
        "char obj[12]; char out[16];", ("obj", "out"), 12,
    ),
    # ROM 02216698: the header at sp+0xc goes to func_0200e894, func_ov003_022166e8 fills the payload at sp+0x18.
    "ov003/func_ov003_02216698.c": (
        "e0692de5c45c9aaf46f17a899360ba5bd004060719361274455787680803da8d",
        "char buf1[12];\n    char buf2[20];",
        "char buf1[12]; char buf2[20];", ("buf1", "buf2"), 12,
    ),
    # ROM 02216ab8: the header at sp+0xc goes to func_0200e894, func_ov003_02216b08 fills the payload at sp+0x18.
    "ov003/func_ov003_02216ab8.c": (
        "568678a5890b35bb0f7dc0789c5c9af396aea6a86756621c6091e68f5d9fecde",
        "char buf1[12];\n    char buf2[20];",
        "char buf1[12]; char buf2[20];", ("buf1", "buf2"), 12,
    ),
    # ROM 022171ec: the header at sp+0x4 goes to func_0200e894, func_ov003_022172bc fills the payload at sp+0x10.
    "ov003/func_ov003_022171ec.c": (
        "d517927b917a1f461b8074f2e3b7d7695d3a54c667bd53280e673a801887a29a",
        "char buf1[12];\n    char buf2[20];",
        "char buf1[12]; char buf2[20];", ("buf1", "buf2"), 12,
    ),
    # ROM 02217838: the header at sp+0xc goes to func_0200e894, func_ov003_02217894 fills the payload at sp+0x18.
    "ov003/func_ov003_02217838.c": (
        "4c5480b169e1bcf3c54bb7416838e56a7858fcf53e4e91d8c6dd4574987211dc",
        "char buf1[12];\n    char out[20];",
        "char buf1[12]; char out[20];", ("buf1", "out"), 12,
    ),
    # ROM 022186cc: the header at sp+0x8 goes to func_0200e894, func_ov003_0221871c fills the payload at sp+0x14.
    "ov003/func_ov003_022186cc.c": (
        "3126a96f51ee3ec71a8ba0d0d4de61ad7b2403ddc6f700da061ea7b52944e255",
        "char buf0[12];\n    char buf1[16];",
        "char buf0[12]; char buf1[16];", ("buf0", "buf1"), 12,
    ),
    # ROM 022188d0: the header at sp+0x4 goes to func_0200e894, func_ov003_02218918 fills the payload at sp+0x10.
    "ov003/func_ov003_022188d0.c": (
        "e4f1c33a52cc7c09692d1710568e1e1443ba20f80d21eb5d7d3bfc238eaf9425",
        "struct {\n        int data[3];\n    } loc1;\n    struct {\n        int data[5];\n    } loc2;",
        "struct { int data[3]; } loc1; struct { int data[5]; } loc2;", ("loc1", "loc2"), 12,
    ),
    # ROM 02228628: the header at sp+0x8 goes to func_0200e894, func_ov004_02228678 fills the payload at sp+0x14.
    "ov004/func_ov004_02228628.c": (
        "e2d7de0dfed5ac48671ebe89aa958570226087bc6c391a847be8652ce9577eee",
        "char buf0[12];\n    char buf1[16];",
        "char buf0[12]; char buf1[16];", ("buf0", "buf1"), 12,
    ),
    # ROM 0222ac24: the header at sp+0x8 goes to func_0200e894, func_ov004_0222ac74 fills the payload at sp+0x14.
    "ov004/func_ov004_0222ac24.c": (
        "37d2b88cbcb602824554c7f9a0f6f5eed7f6007dca3c16b80ce00e3ac0e15006",
        "char local1[12];\n    char local2[16];",
        "char local1[12]; char local2[16];", ("local1", "local2"), 12,
    ),
}


def paths() -> set[str]:
    return set(VERIFIED)


def translate(relative: str, text: str) -> str | None:
    spec = VERIFIED.get(relative)
    if spec is None:
        return None
    digest, before, fields, names, offset = spec
    if hashlib.sha256(text.encode()).hexdigest() != digest or text.count(before) != 1:
        raise ValueError(f"Native local layout changed; repeat the ROM audit: {relative}")
    head, tail = text.split(before)
    pattern = r"\b(" + "|".join(map(re.escape, names)) + r")\b"
    tail = re.sub(pattern, lambda m: "native_frame." + m.group(), tail)
    return (head + "struct { " + fields + " } native_frame;\n    "
            + '_Static_assert(__builtin_offsetof(__typeof__(native_frame), '
            + names[1] + f') == {offset}, "ROM local adjacency");' + tail)
