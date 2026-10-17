"""Conservative word counts for Native calls into the ROM.

Unknown signatures retain the legacy bridge extent. A parameter count alone
cannot describe structures, member pointers, 64-bit arguments or varargs.
"""
from __future__ import annotations

import re

import protos

COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
QUALIFIERS = {"const", "volatile", "register", "static", "inline", "extern", "__arm", "__thumb"}
WORD_TYPES = {
    "char", "signed char", "unsigned char", "short", "short int", "signed short",
    "signed short int", "unsigned short", "unsigned short int", "int", "signed",
    "signed int", "unsigned", "unsigned int", "long", "long int", "signed long",
    "signed long int", "unsigned long", "unsigned long int", "u8", "s8", "u16", "s16",
    "u32", "s32", "BOOL", "bool", "float", "f32", "fx16", "fx32", "size_t",
}
WIDE_RESULTS = {"long long", "long long int", "unsigned long long", "unsigned long long int",
                "signed long long", "signed long long int", "u64", "s64", "double", "f64"}


def scalar_type(declaration: str, named: bool) -> str | None:
    """A proven one-word type, or a scalar result type; never infer typedefs."""
    # A default expression can contain '*' or '&' without declaring a pointer.
    # Reject unsupported declarators before inspecting pointer/array syntax.
    if (re.search(r"::\s*\*", declaration) or "..." in declaration
            or any(token in declaration for token in ("<", "=", "{", "}", "?"))):
        return None
    if "*" in declaration or "&" in declaration or "[" in declaration:
        return "pointer"
    words = [w for w in declaration.split() if w not in QUALIFIERS]
    kind = " ".join(words)
    if kind in WORD_TYPES | WIDE_RESULTS | {"void"}:
        return kind
    if named and words and re.fullmatch(r"\w+", words[-1]):
        return " ".join(words[:-1])
    return kind


def word_arguments(text: str, name: str) -> int | None:
    """Count words for explicit scalar/pointer free-function definitions.

    Assembly definitions and unknown result types may use an undocumented ABI.
    Structures returned by value can add a hidden argument, so they stay unknown.
    """
    text = COMMENT.sub(" ", text).replace('extern "C"', " ")
    pattern = (r"(?:^|[;}])\s*((?:[\w<>]+[\s\*&]+)+?)((?:\w+::)?)" + re.escape(name)
               + r"\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*(?:const\s*)?\{")
    matches = list(re.finditer(pattern, text, re.M))
    if len(matches) != 1:
        return None
    match = matches[0]
    if "asm" in match[1].split() or match[2]:
        return None
    # A qualified definition alone cannot distinguish static from instance
    # members. An inline class definition can also hide an implicit `this`.
    if any(start <= match.start(1) < end for start, end in protos.class_bodies(text)):
        return None
    if scalar_type(match[1], False) not in WORD_TYPES | WIDE_RESULTS | {"void", "pointer"}:
        return None
    params = match[3].strip()
    if params in ("", "void"):
        return 0
    parts, depth, start = [], 0, 0
    for index, ch in enumerate(params):
        depth += ch == "("
        depth -= ch == ")"
        if ch == "," and depth == 0:
            parts.append(params[start:index])
            start = index + 1
    parts.append(params[start:])
    if any(scalar_type(part, True) not in WORD_TYPES | {"pointer"} for part in parts):
        return None
    return len(parts)
