"""PC copies for locals whose adjacency is observable in the ROM.

Only audited declarations are grouped. Values and calls are unchanged; source
digests require a new audit whenever the matching source changes.
"""
from __future__ import annotations

import hashlib
import re


# path -> digest, original declarations, grouped fields, names, second-field offset
VERIFIED = {
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
