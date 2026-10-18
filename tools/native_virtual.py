"""Preserve audited ROM virtual calls erased by matching placeholder bodies."""
from __future__ import annotations

import hashlib


# Source-relative path -> (source SHA-256, declaration in the source, PC declaration).
# The ov100 source now declares f0-f3 without bodies itself (the link edit: inline
# virtual bodies nothing calls are declarations), which is the PC form already; the
# digest still pins it, so a changed source needs the ROM audit again.
VERIFIED = {
    "ov100/func_ov100_0229e3b0.cpp": (
        "4d8fc9087f59245ca0bc20d27cef461b150af7ab62f956be99fabf19a64f54ba",
        "virtual void f3();", "virtual void f3();",
    ),
}


def paths() -> set[str]:
    return set(VERIFIED)


def translate(relative: str, text: str) -> str | None:
    spec = VERIFIED.get(relative)
    if spec is None:
        return None
    digest, before, after = spec
    if hashlib.sha256(text.encode()).hexdigest() != digest or text.count(before) != 1:
        raise ValueError(f"Native virtual-call source changed; repeat the ROM audit: {relative}")
    # ROM 0229e3ba adjusts this by 0x2274; 0229e3be/0229e3c0 call slot 3.
    # The unresolved direct method call goes through native.virtual_calls.
    return text.replace(before, after)
