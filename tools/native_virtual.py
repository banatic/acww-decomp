"""Preserve audited ROM virtual calls erased by matching placeholder bodies."""
from __future__ import annotations

import hashlib


VERIFIED = {
    "ov100/func_ov100_0229e3b0.cpp": (
        "db0ddfce3cc9d6f6edb8266ce1119bb65199b3379a9d58649a439fd20e1a271b",
        "virtual void f3() {}", "virtual void f3();",
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
