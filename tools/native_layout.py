"""PC copies for locals whose adjacency is observable in the ROM.

Only audited declarations are grouped. Values and calls are unchanged; source
digests require a new audit whenever the matching source changes.
"""
from __future__ import annotations

import pathlib
import re
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402


# function key -> digest of its text (common.function_sha256), original declarations, grouped fields, names, second-field offset
VERIFIED = {
    # Request state 0x5e: header at sp, flag/point payload at sp+12.
    # ROM 02211d58/02211d7a/02211d86 construct, fill and submit it.
    "ov003/func_ov003_02211d4c": (
        "3b5300b8e76a9ff323713a793eee45981648a82296567fc2bce3eb591921fd56",
        "UnkStruct_02211d4c local1;\n    Buf local3;",
        "UnkStruct_02211d4c local1; Buf local3;", ("local1", "local3"), 12,
    ),
    # Request state 0x5f: header at sp+4 and payload at sp+16.
    # ROM 02211904/02211926/02211952 preserve their 12-byte adjacency.
    "ov003/func_ov003_022118f8": (
        "9ca613106d42e4ca859c33a4750b93e3a29dbab890cf6c0b456b9bfa879186e3",
        "struct Buf buf;\n    struct UnkStruct_022118f8_2 out;",
        "struct Buf buf; struct UnkStruct_022118f8_2 out;", ("buf", "out"), 12,
    ),
    # The no-item state 0x5f request uses sp and sp+12 instead.
    # ROM 0221198c/022119ae/022119bc construct, fill and submit it.
    "ov003/func_ov003_02211980": (
        "91a537b5195f40116bee267ecebb780bb6a4f98bc6464699b2506647e7eebe4e",
        "char local[12];\n    char local2[16];",
        "char local[12]; char local2[16];", ("local", "local2"), 12,
    ),
    # ROM 0201c2da/0201c2dc pass sp+8 and sp+16. 0201c2ec passes sp+8
    # as a vector whose Z at +8 is the second output of func_02096614.
    "main/func_0201c2c8": (
        "b6dfcfe48a040d796cdc1a6d91efb6560b13e5f1d9f81cd5cb9e148fab9cf819",
        "unsigned int dataA[2];\n    unsigned int dataB[2];",
        "unsigned int dataA[2]; unsigned int dataB[2];", ("dataA", "dataB"), 8,
    ),
    # ROM 02215f0c constructs the request at sp; 02215f2a fills its payload
    # at sp+12, and 02215f34 submits that same request at sp.
    "ov003/func_ov003_02215f00": (
        "5525a52ac9c5cbbad010af7ece2f399dbf777eec0f8a39d5393bd5db9314c0f1",
        "char ctx[12];\n    int out[4];",
        "char ctx[12]; int out[4];", ("ctx", "out"), 12,
    ),
    # ROM 020a96a8 passes sp to func_02064658, which reads eight bytes there; 020a96d6 passes
    # sp+4, the second word, to func_020a9ae4.
    "main/func_020a967c": (
        "7b454f0525365e6ffbf53b4177c1c5f725d9829d06eda20772c838496ae2b220",
        "int local1;\n    int local2;",
        "int local1; int local2;", ("local1", "local2"), 4,
    ),
    # ROM 0201357a/0201357c pass sp+0x2c and sp+0x30 to func_0204f818 as the two outputs;
    # 02013614 passes sp+0x2c to func_020137ec as a two-word point.
    "main/func_0201354c": (
        "3b6455d01a951b50cb463716f7dd99340422f61bf6d9c2842606b6660847a955",
        "u32 s2c;\n    u32 s30;",
        "u32 s2c; u32 s30;", ("s2c", "s30"), 4,
    ),
    # Request builders: func_0200e92c/func_0200e90c construct a 12-byte header that
    # func_0200e894 submits; it reads the payload right after it, which the source keeps in the
    # next local. Each ROM body passes the header and the payload 12 bytes apart.
    # ROM 02009a44: the header at sp+0x4 goes to func_0200e894, func_02009a9c fills the payload at sp+0x10.
    "main/func_02009a44": (
        "c98a56c54ec2aca5088e8a96013b197f89d7cf5c8519e24e25488f52a1a6892a",
        "char bufA[12];\n    char bufB[20];",
        "char bufA[12]; char bufB[20];", ("bufA", "bufB"), 12,
    ),
    # ROM 0200a6a0: the header at sp+0x8 goes to func_0200e894, func_0200a6f0 fills the payload at sp+0x14.
    "main/func_0200a6a0": (
        "23b8dbef21853e09f11e3b5ab00e8d08b807be8f181985b94d0444ca6301df1b",
        "char local1[12];\n    char local2[16];",
        "char local1[12]; char local2[16];", ("local1", "local2"), 12,
    ),
    # ROM 0200acd4: the header at sp+0xc goes to func_0200e894, func_0200ad78 fills the payload at sp+0x18.
    "main/func_0200acd4": (
        "45230bddf7bc6ea3d9e75a9552e0f58098e9a382edc2b209b46e432802914d8a",
        "char buf1[12];\n    char buf2[20];",
        "char buf1[12]; char buf2[20];", ("buf1", "buf2"), 12,
    ),
    # ROM 0200ad24: the header at sp+0x8 goes to func_0200e894, func_0200ad78 fills the payload at sp+0x14.
    "main/func_0200ad24": (
        "d6c3aaabf10256e646da9fe99a35fb819911f9f840fa9ee7ead3f64e0ef808c9",
        "char obj[12];\n    char out[16];",
        "char obj[12]; char out[16];", ("obj", "out"), 12,
    ),
    # ROM 0200b7e8: the header at sp+0x10 goes to func_0200e894, func_0200b894 fills the payload at sp+0x1c.
    "main/func_0200b7e8": (
        "ee48589f1fd751f09340c1d7db06e24810292fdd8dd4a55386d38518458e2fe1",
        "char obj[12];\n    char tmp[16];",
        "char obj[12]; char tmp[16];", ("obj", "tmp"), 12,
    ),
    # ROM 0200c3b0: the header at sp+0x0 goes to func_0200e894, func_0200c3f0 fills the payload at sp+0xc.
    "main/func_0200c3b0": (
        "98a1c3f0375d436d4acd8e98381d260c3087aedba8bbc5ab85a001bcf39937d4",
        "char a[0xc];\n    char b[0x10];",
        "char a[0xc]; char b[0x10];", ("a", "b"), 12,
    ),
    # ROM 0200cc00: the header at sp+0x0 goes to func_0200e894, func_0200cc40 fills the payload at sp+0xc.
    "main/func_0200cc00": (
        "59c9f181b4171c5257ad1ba0c36ac5b4c4b92513b45dea9653cb9b6e6c40d699",
        "char s1[12];\n    char s2[16];",
        "char s1[12]; char s2[16];", ("s1", "s2"), 12,
    ),
    # ROM 0200dbb4: the header at sp+0x0 goes to func_0200e894, func_0200dc00 fills the payload at sp+0xc.
    "main/func_0200dbb4": (
        "8737fa836a06112f9928209977ccf3b31b5cf0ecfa1ccae5e0a3356e26d82917",
        "int stack0[3];\n    int stack1[4];",
        "int stack0[3]; int stack1[4];", ("stack0", "stack1"), 12,
    ),
    # ROM 0220fb30: the header at sp+0x8 goes to func_0200e894, func_ov003_0220fb80 fills the payload at sp+0x14.
    "ov003/func_ov003_0220fb30": (
        "b16e876877779246dbb8d148063293390a533594ecc0407f97201ad8fac1aa65",
        "char buf1[12];\n    char buf2[16];",
        "char buf1[12]; char buf2[16];", ("buf1", "buf2"), 12,
    ),
    # ROM 0220fda0: the header at sp+0x0 goes to func_0200e894, func_ov003_0220fdf4 fills the payload at sp+0xc.
    "ov003/func_ov003_0220fda0": (
        "0279d661e67f4974134df5dd05527040f616768a0911da5ed77f1a3ad0a9495c",
        "int buf[3];\n    int out[4];",
        "int buf[3]; int out[4];", ("buf", "out"), 12,
    ),
    # ROM 02212830: the header at sp+0x8 goes to func_0200e894, func_ov003_02212878 fills the payload at sp+0x14.
    "ov003/func_ov003_02212830": (
        "34a2651ceede6faeb5e6e7b70cdd3d47e939b74364da0b6323208f54b8cb91a2",
        "unsigned char buf2[12];\n    unsigned char buf3[16];",
        "unsigned char buf2[12]; unsigned char buf3[16];", ("buf2", "buf3"), 12,
    ),
    # ROM 02212c10: the header at sp+0x4 goes to func_0200e894, func_ov003_02212d04 fills the payload at sp+0x10.
    "ov003/func_ov003_02212c10": (
        "2d287109661ae2e97406cc3603d05f33416f8b641c6d46d20a78b4d4402bdbab",
        "char local1[12];\n    char local2[20];",
        "char local1[12]; char local2[20];", ("local1", "local2"), 12,
    ),
    # ROM 02215624: the header at sp+0x0 goes to func_0200e894, func_ov003_02215664 fills the payload at sp+0xc.
    "ov003/func_ov003_02215624": (
        "9573b1637019397b93f6437db284f724323ee415bbec9e820593c18a5edf2305",
        "char s1[12];\n    char s2[16];",
        "char s1[12]; char s2[16];", ("s1", "s2"), 12,
    ),
    # ROM 02216410: the header at sp+0x8 goes to func_0200e894, func_ov003_02216460 fills the payload at sp+0x14.
    "ov003/func_ov003_02216410": (
        "9128395781b18c67f8069d8fa4c1bf8e5533ea008c270d84e4e2f017564462f0",
        "char obj[12];\n    char out[16];",
        "char obj[12]; char out[16];", ("obj", "out"), 12,
    ),
    # ROM 02216698: the header at sp+0xc goes to func_0200e894, func_ov003_022166e8 fills the payload at sp+0x18.
    "ov003/func_ov003_02216698": (
        "55860f7567c62db71fb9b016203d89cca7f489485c950a4116dc325c8fb40af9",
        "char buf1[12];\n    char buf2[20];",
        "char buf1[12]; char buf2[20];", ("buf1", "buf2"), 12,
    ),
    # ROM 02216ab8: the header at sp+0xc goes to func_0200e894, func_ov003_02216b08 fills the payload at sp+0x18.
    "ov003/func_ov003_02216ab8": (
        "a8d58f335f79ae2e71ac79137cd825766200ffa403cff400f7e4ae4b531e43b4",
        "char buf1[12];\n    char buf2[20];",
        "char buf1[12]; char buf2[20];", ("buf1", "buf2"), 12,
    ),
    # ROM 022171ec: the header at sp+0x4 goes to func_0200e894, func_ov003_022172bc fills the payload at sp+0x10.
    "ov003/func_ov003_022171ec": (
        "801bd25d41ed7ae57c574280ebe37c8a0b386cbbca3d1a399550c7a743d71173",
        "char buf1[12];\n    char buf2[20];",
        "char buf1[12]; char buf2[20];", ("buf1", "buf2"), 12,
    ),
    # ROM 02217838: the header at sp+0xc goes to func_0200e894, func_ov003_02217894 fills the payload at sp+0x18.
    "ov003/func_ov003_02217838": (
        "a04815430e1098de374285d34545349a46c482e4757ac4c6f5e7ef1458eb96d3",
        "char buf1[12];\n    char out[20];",
        "char buf1[12]; char out[20];", ("buf1", "out"), 12,
    ),
    # ROM 022186cc: the header at sp+0x8 goes to func_0200e894, func_ov003_0221871c fills the payload at sp+0x14.
    "ov003/func_ov003_022186cc": (
        "1cc696eec4f491dfb2262b7bfa534fb196edbf783cd24c034216517f8a0db8bd",
        "char buf0[12];\n    char buf1[16];",
        "char buf0[12]; char buf1[16];", ("buf0", "buf1"), 12,
    ),
    # ROM 022188d0: the header at sp+0x4 goes to func_0200e894, func_ov003_02218918 fills the payload at sp+0x10.
    "ov003/func_ov003_022188d0": (
        "7732876ac5cd64002d30b74854d2fa36107c618850ed6d0a650b008bd3b1b8ea",
        "struct {\n        int data[3];\n    } loc1;\n    struct {\n        int data[5];\n    } loc2;",
        "struct { int data[3]; } loc1; struct { int data[5]; } loc2;", ("loc1", "loc2"), 12,
    ),
    # ROM 02228628: the header at sp+0x8 goes to func_0200e894, func_ov004_02228678 fills the payload at sp+0x14.
    "ov004/func_ov004_02228628": (
        "1704243820d3d7e414071b9670f5e082ea026241ff07de1a9c622ad97f790446",
        "char buf0[12];\n    char buf1[16];",
        "char buf0[12]; char buf1[16];", ("buf0", "buf1"), 12,
    ),
    # ROM 0222ac24: the header at sp+0x8 goes to func_0200e894, func_ov004_0222ac74 fills the payload at sp+0x14.
    "ov004/func_ov004_0222ac24": (
        "3f9e970f70e0b17261cdb9be32cd867c6561a44018fa24584bb9f96d323dfac2",
        "char local1[12];\n    char local2[16];",
        "char local1[12]; char local2[16];", ("local1", "local2"), 12,
    ),
    # ROM 0200a448: header at sp+0x8 to func_0200e894, payload at sp+0x14 to func_0200a4ac.
    "main/func_0200a448": (
        "49136b324689f87badff5118caee1822317bcbab7114cb95f0483c1466498697",
        "UnkStruct_0200a448_2 s;\n    UnkStruct_0200a448_3 t;",
        "UnkStruct_0200a448_2 s; UnkStruct_0200a448_3 t;", ("s", "t"), 12,
    ),
    # ROM 0200b83c: header at sp+0x10 to func_0200e894, payload at sp+0x1c to func_0200b894.
    "main/func_0200b83c": (
        "7b04360ea3be5e1a0fe52f10551b062c33d18ce62387b18bf3b7a0b1bbf31b4e",
        "UnkStruct_0200b83c obj;\n    int out[4];",
        "UnkStruct_0200b83c obj; int out[4];", ("obj", "out"), 12,
    ),
    # ROM 0200bdbc: header at sp+0x8 to func_0200e894, payload at sp+0x14 to func_0200be0c.
    "main/func_0200bdbc": (
        "b194a5a896cb769e4930327ee72a53fd390c2064cee784fd8970af0132decc09",
        "UnkStruct_0200bdbc obj;\n    Other other;",
        "UnkStruct_0200bdbc obj; Other other;", ("obj", "other"), 12,
    ),
    # ROM 0200c904: header at sp+0x4 to func_0200e894, payload at sp+0x10 to func_0200c94c.
    "main/func_0200c904": (
        "3eabbcb179af5d9bf8ee89ac6a3fa4d52b1f2437c05ad293eac87463119a4710",
        ("QueueEntry local1;", "\n    UnkStruct_0200c904 local2;"),
        "QueueEntry local1; UnkStruct_0200c904 local2;", ("local1", "local2"), 12,
    ),
    # ROM 0200d1a0: header at sp+0x0 to func_0200e894, payload at sp+0xc to func_0200d1e0.
    "main/func_0200d1a0": (
        "44d3a422562e8ef79647c877bd716767efb5dbe304888cf90c7db2ab35127eb7",
        "UnkStruct_0200d1a0 v1;\n    UnkStruct_0200d1a0_2 v2;",
        "UnkStruct_0200d1a0 v1; UnkStruct_0200d1a0_2 v2;", ("v1", "v2"), 12,
    ),
    # ROM 0200d4e8: header at sp+0x0 to func_0200e894, payload at sp+0xc to func_0200d528.
    "main/func_0200d4e8": (
        "a1a42b6e9b7547f0ba31155cd91e4ef352ee5a77c73e96083ce943db4f5f476c",
        "UnkStruct_0200d4e8 s1;\n    UnkStruct_0200d4e8_2 s2;",
        "UnkStruct_0200d4e8 s1; UnkStruct_0200d4e8_2 s2;", ("s1", "s2"), 12,
    ),
    # ROM 0220f768: header at sp+0x8 to func_0200e894, payload at sp+0x14 to func_ov003_0220f7b8.
    "ov003/func_ov003_0220f768": (
        "550d41c8410ee46ef0a2d297d4b8116506fba8eb898c7fadfe70afc32fc7da50",
        "CType c;\n    DType d;",
        "CType c; DType d;", ("c", "d"), 12,
    ),
    # ROM 022100c4: header at sp+0x8 to func_0200e894, payload at sp+0x14 to func_ov003_02210114.
    "ov003/func_ov003_022100c4": (
        "4218952b71c97b08285794c62c167b7f3956abd9411869944770cc85fc2d8b13",
        "struct UnkStruct_022100c4 s12;\n    char out[16];",
        "struct UnkStruct_022100c4 s12; char out[16];", ("s12", "out"), 12,
    ),
    # ROM 022122ac: header at sp+0x8 to func_0200e894, payload at sp+0x14 to func_ov003_022122fc.
    "ov003/func_ov003_022122ac": (
        "e9670e4415134380732b06af0597b5b5eaa9783fe8808557ff3bae572b0a5e27",
        "UnkStruct_022122ac obj;\n    Result result;",
        "UnkStruct_022122ac obj; Result result;", ("obj", "result"), 12,
    ),
    # ROM 02218ec4: header at sp+0x8 to func_0200e894, payload at sp+0x14 to func_ov003_02218f0c.
    "ov003/func_ov003_02218ec4": (
        "b9275777394d928c5655cceb96742597215db239121857db19e4b17894e49823",
        "UnkStruct_02218ec4 obj;\n    UnkStruct_02218ec4_2 out;",
        "UnkStruct_02218ec4 obj; UnkStruct_02218ec4_2 out;", ("obj", "out"), 12,
    ),
    # ROM 02218fac: header at sp+0x0 to func_0200e894, payload at sp+0xc to func_ov003_02218fec.
    "ov003/func_ov003_02218fac": (
        "72572b9da4988f0eb8146102e3e7da53c93fbd9ebb04f52fffd18009789a111f",
        "UnkStruct_02218fac l1;\n    UnkStruct_02218fac_2 l2;",
        "UnkStruct_02218fac l1; UnkStruct_02218fac_2 l2;", ("l1", "l2"), 12,
    ),
    # ROM 02228100: header at sp+0x8 to func_0200e894, payload at sp+0x14 to func_ov004_02228164.
    "ov004/func_ov004_02228100": (
        "3d8ee22732fabd2affa32dee6e127412a073e11958b5d6b01d6f73828ee624b0",
        "UnkStruct_02228100_2 s;\n    UnkStruct_02228100_3 t;",
        "UnkStruct_02228100_2 s; UnkStruct_02228100_3 t;", ("s", "t"), 12,
    ),
    # ROM 02229010: header at sp+0x4 to func_0200e894, payload at sp+0x10 to func_ov004_02229078.
    "ov004/func_ov004_02229010": (
        "3a5f4d31e1b6a8b691eeb52f5b65bb006b77f4d105fc38b56949594a9066270c",
        "struct UnkStruct_02229010_2 ctx;\n    struct UnkStruct_02229010_3 obj;",
        "struct UnkStruct_02229010_2 ctx; struct UnkStruct_02229010_3 obj;", ("ctx", "obj"), 12,
    ),
    # ROM 02229258: header at sp+0x4 to func_0200e894, payload at sp+0x10 to func_ov004_022292c0.
    "ov004/func_ov004_02229258": (
        "6664c85e598ef20ec6cb2d14ae71abfccc587555baa394560b9a3b16807af279",
        "struct UnkStruct_02229258_2 ctx;\n    struct UnkStruct_02229258_3 obj;",
        "struct UnkStruct_02229258_2 ctx; struct UnkStruct_02229258_3 obj;", ("ctx", "obj"), 12,
    ),
    # ROM 022294a0: header at sp+0x4 to func_0200e894, payload at sp+0x10 to func_ov004_02229508.
    "ov004/func_ov004_022294a0": (
        "f25a8c57243deeaaf2585a6f5a259211e9b0883abab160001f381620c07bdec2",
        "struct UnkStruct_022294a0_2 ctx;\n    struct UnkStruct_022294a0_3 obj;",
        "struct UnkStruct_022294a0_2 ctx; struct UnkStruct_022294a0_3 obj;", ("ctx", "obj"), 12,
    ),
    # ROM 02229774: header at sp+0x8 to func_0200e894, payload at sp+0x14 to func_ov004_022297c4.
    "ov004/func_ov004_02229774": (
        "022c4f9e13991c44686821d41ca298488748e168542a76f598134a619a37b72c",
        "CType c;\n    DType d;",
        "CType c; DType d;", ("c", "d"), 12,
    ),
    # ROM 0222a494: header at sp+0x4 to func_0200e894, payload at sp+0x10 to func_ov004_0222a4dc.
    "ov004/func_ov004_0222a494": (
        "b9d3a78327434312a8fc6e78ea459cd216a157b17ab026acbc36d926d170cd0a",
        ("QueueEntry local1;", "\n    UnkStruct_0222a494 local2;"),
        "QueueEntry local1; UnkStruct_0222a494 local2;", ("local1", "local2"), 12,
    ),
    # ROM 0222af6c: header at sp+0x8 to func_0200e894, payload at sp+0x14 to func_ov004_0222afbc.
    "ov004/func_ov004_0222af6c": (
        "ebd1c5d2b1fe2978a77d64b060c7194ad896807d808e6fba00cd2d06521d74ac",
        "CType c;\n    DType d;",
        "CType c; DType d;", ("c", "d"), 12,
    ),
}


def paths() -> set[str]:
    return set(VERIFIED)


def translate(relative: str, text: str, base: str | None = None) -> str | None:
    """The PC copy of the function `relative` (its key) whose source is `text`; `base`, when
    given, is the copy so far that the edit applies to (tools/native.py). Only the function's
    own definition (common.function_span) changes."""
    spec = VERIFIED.get(relative)
    if spec is None:
        return None
    digest, before, fields, names, offset = spec
    # (declaration, later declaration): the second local is declared after statements; the
    # copy declares both in the first one's place
    before, later = before if isinstance(before, tuple) else (before, None)
    name = relative.partition("/")[2]
    text_ok = C.pinned_sha256(relative, text) == digest
    text = text if base is None else base
    start, end = C.function_span(text, name) or (0, len(text))
    own = text[start:end]
    if not text_ok or own.count(before) != 1 or later is not None and own.count(later) != 1:
        raise ValueError(f"Native local layout changed; repeat the ROM audit: {relative}")
    if later is not None:
        own = own.replace(later, "")
    head, tail = own.split(before)
    pattern = r"\b(" + "|".join(map(re.escape, names)) + r")\b"
    tail = re.sub(pattern, lambda m: "native_frame." + m.group(), tail)
    assertion = "static_assert" if C.key_path(relative).suffix == ".cpp" else "_Static_assert"
    return (text[:start] + head + "struct { " + fields + " } native_frame;\n    "
            + assertion + '(__builtin_offsetof(__typeof__(native_frame), '
            + names[1] + f') == {offset}, "ROM local adjacency");' + tail + text[end:])
