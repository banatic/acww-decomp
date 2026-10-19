"""Verified PC-only replacements for member pointers shared with the ROM.

The allowlist is deliberately tied to source contents and exact declarations. A
changed source needs another ROM/layout audit, never a silent keep-rule bypass.
"""

from __future__ import annotations

import hashlib
import pathlib
import re
import common as C
import native_pmf_boundary


# Source-relative path -> (source SHA-256, original declaration, PC declaration,
# layout assertions). ROM evidence is recorded in docs/native-member-pointers.md.
VERIFIED: dict[str, tuple[str, str, str, str]] = {
    "main/func_02013518.cpp": (
        "a326d42f30f9b1fdf7211ccd05a5e322aa00b97c7fce7c3829c7fe0ae67072ac",
        "typedef void *(UnkStruct_02013518::*PMF)(int);",
        "typedef NativeMember<UnkStruct_02013518, void *, int> PMF;",
        'static_assert(sizeof(PMF) == 8, "ROM member-pointer size");\n'
        'static_assert(__builtin_offsetof(UnkStruct_02013518, unk_28) == 0x28, "ROM field");',
    ),
    "main/func_0201cfe4.cpp": (
        "dd736357200171c19e4b42adedeb6c9475050542a8b2b574551a0187785cefde",
        "typedef void (UnkStruct_0201cfe4::*PMF)(int);",
        "typedef NativeMember<UnkStruct_0201cfe4, void, int> PMF;",
        'static_assert(sizeof(PMF) == 8, "ROM member-pointer size");\n'
        'static_assert(__builtin_offsetof(UnkStruct_0201cfe4, pmf_c0) == 0xc0, "ROM callback");\n'
        'static_assert(__builtin_offsetof(UnkStruct_0201cfe4, pmf_c8) == 0xc8, "ROM callback");\n'
        'static_assert(__builtin_offsetof(UnkStruct_0201cfe4, flag) == 0x15a, "ROM trailing field");\n'
        'static_assert(__is_trivially_copyable(PMF), "ROM null assignment copies two words");',
    ),
    "ov049/func_ov049_02262a94.cpp": (
        "88390edea0ecc9ba5eee477f7b5fff704922c3138a556d2a901026aa0505d705",
        "int (UnkStruct_02262a94::*pmf)();",
        "NativeMember<UnkStruct_02262a94, int> pmf;",
        'static_assert(sizeof(PMFEntry) == 16, "ROM table stride");\n'
        'static_assert(__builtin_offsetof(PMFEntry, pad) == 8, "ROM member-pointer size");\n'
        'static_assert(__is_trivially_copyable(PMFEntry), "ROM table copies are raw words");',
    ),
}

SOURCES = pathlib.Path(__file__).resolve().parents[1] / "runtime/native-member-sources.txt"
READ_ONLY = dict(line.split() for line in SOURCES.read_text().splitlines()
                 if line.strip() and not line.startswith("#")) if SOURCES.exists() else {}
DECLARATION = re.compile(
    r"(?m)^[ \t]*(?P<declaration>(?P<prefix>typedef\s+|extern\s+)?(?P<result>void\s*\*?|int)\s*"
    r"\(\s*(?P<class>\w+)::\*(?P<name>\w+)\)\s*\((?P<args>[^()]*)\)\s*;)")
BOUNDARY = native_pmf_boundary.specifications()


def paths() -> set[str]:
    return VERIFIED.keys() | READ_ONLY.keys() | BOUNDARY.keys()


def read_only_copy(text: str) -> str:
    """One audited member type and, optionally, its external ROM null value."""
    declarations = list(DECLARATION.finditer(text))
    members = [m for m in declarations if (m['prefix'] or '').strip() != 'extern']
    if len(members) != 1:
        raise ValueError("Expected exactly one audited member-pointer declaration")
    m = members[0]
    for other in declarations:
        if other is m:
            continue
        if ((other['prefix'] or '').strip() != 'extern' or other['name'] != '__ptmf_null'
                or any(other[key].strip() != m[key].strip() for key in ('class', 'result', 'args'))):
            raise ValueError("Unaudited external member-pointer declaration")
    args = m['args'].strip()
    params = m['class'] + ', ' + m['result'].strip()
    if args and args != 'void':
        params += ', ' + args
    member = 'NativeMember<' + params + '>'
    result = text
    for declaration in reversed(declarations):
        replacement = (declaration['prefix'] or '') + member + ' ' + declaration['name'] + ';'
        result = (result[:declaration.start('declaration')] + replacement
                  + result[declaration.end('declaration'):])
    # Check the PC declaration's size and alignment as well: all surrounding
    # fields and array strides must be unchanged by the type substitution.
    assertions = (f'\nusing NativeAuditedMember = {member};\n'
                  f"typedef {m['result']} ({m['class']}::*NativeOriginalMember)({m['args']});\n"
                  'static_assert(sizeof(NativeAuditedMember) == 8, "ROM member size");\n'
                  'static_assert(sizeof(NativeOriginalMember) == 8, "original PC field size");\n'
                  'static_assert(alignof(NativeAuditedMember) == alignof(NativeOriginalMember), "field alignment");\n'
                  'static_assert(__is_trivially_copyable(NativeAuditedMember), "raw ROM copying");\n')
    return '#include "native_member.h"\n' + result + assertions


def translate(relative: str, text: str, headers: dict[str, str] | None = None) -> str | None:
    if relative in BOUNDARY:
        body, copies = native_pmf_boundary.checked_copy(relative, text, C.ROOT, C.modules(),
                                                       C.module_image, specs=BOUNDARY)
        if copies and headers is None:
            raise ValueError('Member source requires its translated header copies: ' + relative)
        if headers is not None:
            headers.update(copies)
        return body
    spec = VERIFIED.get(relative)
    if spec is None:
        if relative in READ_ONLY:
            if hashlib.sha256(text.encode()).hexdigest() != READ_ONLY[relative]:
                raise ValueError(f"Native member-pointer source changed; repeat the ROM audit: {relative}")
            return read_only_copy(text)
        return None
    digest, before, after, assertions = spec
    if hashlib.sha256(text.encode()).hexdigest() != digest or text.count(before) != 1:
        raise ValueError(f"Native member-pointer source changed; repeat the ROM audit: {relative}")
    return '#include "native_member.h"\n' + text.replace(before, after) + '\n' + assertions + '\n'
