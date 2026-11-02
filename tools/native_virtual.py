"""Preserve audited ROM virtual calls erased by matching placeholder bodies."""
from __future__ import annotations

import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402


# Function key -> (the function's SHA-256 (common.function_sha256), declaration in the source, PC declaration).
# The ov100 source now declares f0-f3 without bodies itself (the link edit: inline
# virtual bodies nothing calls are declarations), which is the PC form already; the
# digest still pins it, so a changed source needs the ROM audit again.
VERIFIED = {
    "ov100/func_ov100_0229e3b0": (
        "276a280727faeb8ebe866f5b0fccc06a8de87fe2bf9dfa3e808ef68dfb031665",
        "virtual void f3();", "virtual void f3();",
    ),
}


def paths() -> set[str]:
    return set(VERIFIED)


def translate(relative: str, text: str, base: str | None = None) -> str | None:
    spec = VERIFIED.get(relative)
    if spec is None:
        return None
    digest, before, after = spec
    text_ok = C.pinned_sha256(relative, text) == digest
    text = text if base is None else base
    if not text_ok or text.count(before) != 1:
        raise ValueError(f"Native virtual-call source changed; repeat the ROM audit: {relative}")
    # ROM 0229e3ba adjusts this by 0x2274; 0229e3be/0229e3c0 call slot 3.
    # The unresolved direct method call goes through native.virtual_calls.
    return text.replace(before, after)
