"""PC copy mechanics for the remaining ROM member-pointer boundary.

The caller must validate source/header/ROM hashes and supply audited method
constants. This module does not select functions or change the keep policy.
"""
from __future__ import annotations

import re
import hashlib
import json
from pathlib import Path


# A declaration, an inline parameter, an array, or a pointer-to-member type-id.
# Restrict types to the shapes in the audited sources. Reject leftovers rather
# than allowing an unchanged host member pointer into the translated copy.
MEMBER = re.compile(
    r'(?P<result>\b(?:void|int|bool|Pair)\s*\*?)\s*'
    r'\(\s*(?P<class>\w+)\s*::\s*\*\s*(?P<indirect>\*)?\s*'
    r'(?P<name>\w+)?\s*(?P<array>\[[^\[\]]*\])?\s*\)\s*'
    r'\((?P<args>[^()]*)\)')
METHOD = re.compile(r'&\s*(?P<class>\w+)\s*::\s*(?P<name>\w+)')
REGISTER_CALLS = {'main/func_0201f40c.cpp': {'func_020819bc'}}
# Headers whose member-pointer declarations are translated in PC copies (each pinned by
# digest in every manifest entry that includes it).
MEMBER_HEADERS = {'include/cpp/main/Base_02027460.h', 'include/cpp/main/Base_02038828.h'}

PAIR_CALL = '''template<> struct NativeMemberCall<UnkStruct_02013948, Pair, void *, int> {
    static Pair invoke(unsigned int target, UnkStruct_02013948 *object, void *arg, int number)
    {
        Pair result;
        reinterpret_cast<void (*)(Pair *, UnkStruct_02013948 *, void *, int)>(target)(
            &result, object, arg, number);
        return result;
    }
};
'''


def argument_type(argument: str) -> str:
    """Remove an optional parameter name, preserving its actual type."""
    argument = ' '.join(argument.split())
    if not argument or argument == 'void':
        return ''
    # Named pointer parameters and named primitive parameters are the only
    # named shapes accepted here. A bare user-defined type remains intact.
    argument = re.sub(r'([*&])\s*\w+$', r'\1', argument)
    argument = re.sub(r'^(void|bool|int|unsigned int|signed int|char|unsigned char)\s+\w+$',
                      r'\1', argument)
    if not re.fullmatch(r'(?:const\s+)?(?:\w+::)*\w+(?:\s+\w+)?\s*[*&]*', argument):
        raise ValueError(f'Unaudited member parameter: {argument}')
    return argument


def declarations(text: str) -> tuple[str, dict[str, str]]:
    """Replace all member declarations in one already-audited source/header."""
    types = {}

    def replace(match):
        result = match['result'].strip()
        if result == 'Pair' and match['class'] != 'UnkStruct_02013948':
            raise ValueError('Aggregate member result needs its ARM return adapter')
        args = [argument_type(arg) for arg in match['args'].split(',')]
        params = ', '.join([match['class'], result, *(arg for arg in args if arg)])
        member = f'NativeMember<{params}>'
        if match['class'] in types and types[match['class']] != member:
            # Multiple types are legal. Such sources cannot use the implicit
            # one-type-per-class shorthand for method constants below.
            types[match['class']] = ''
        else:
            types[match['class']] = member
        return member + (' *' if match['indirect'] else '') + (
            ' ' + match['name'] if match['name'] else '') + (match['array'] or '')

    result, count = MEMBER.subn(replace, text)
    if not count:
        raise ValueError('No member declarations in this source/header')
    if re.search(r'::\s*\*', result):
        raise ValueError('Untranslated member-pointer type')
    return result, types


def copy(text: str, constants: dict[str, tuple[int, int]], *,
         pair_result: bool = False, array_receiver: bool = False, register_argument: bool = False,
         header_types: bool = False) -> str:
    """Translate an audited body with exact ROM (function, adjustment) pairs.

    ``constants`` is keyed by the fully qualified C++ method spelling, including
    methods used through DISCARD_HANDLER. All entries must be consumed. With
    ``header_types``, the member types may all come from translated header copies.
    """
    if header_types and not MEMBER.search(text):
        if re.search(r'::\s*\*', text) or METHOD.search(text):
            raise ValueError('Untranslated member-pointer type')
        types = {}
    else:
        text, types = declarations(text)
    if register_argument:
        declaration = 'extern "C" int func_020819bc(void);'
        call = 'func_020819bc()'
        if text.count(declaration) != 1 or text.count(call) != 1:
            raise ValueError('Audited register-only call changed')
        text = text.replace(declaration, 'extern "C" int func_020819bc(void *);').replace(
            call, 'func_020819bc(reinterpret_cast<void *>(static_cast<unsigned int>(p->unk_12C)))')
    used = set()
    macro = '#define DISCARD_HANDLER(Class, Method) (PMF) & Class::Method'
    if macro in text:
        text = text.replace(macro, '')
        text = re.sub(r'DISCARD_HANDLER\(\s*(\w+)\s*,\s*(\w+)\s*\)', r'&\1::\2', text)

    def method(match):
        name = match['class'] + '::' + match['name']
        if name not in constants:
            raise ValueError(f'Missing audited ROM member constant: {name}')
        member = types.get(match['class'])
        if not member:
            raise ValueError(f'Ambiguous destination member type for {name}')
        function, adjustment = constants[name]
        if not 0 <= function <= 0xffffffff or not -0x80000000 <= adjustment <= 0x7fffffff:
            raise ValueError(f'Out-of-range ROM member constant: {name}')
        used.add(name)
        return f'{member}{{0x{function:08x}u, {adjustment}}}'

    text = METHOD.sub(method, text)
    if used != constants.keys():
        raise ValueError('Unused audited ROM member constants: ' + ', '.join(constants.keys() - used))
    if pair_result:
        marker = 'struct Entry {'
        if text.count(marker) != 1 or 'NativeMember<UnkStruct_02013948, Pair, void *, int>' not in text:
            raise ValueError('Pair-return member source changed')
        text = text.replace(marker, PAIR_CALL + marker)
    elif 'NativeMember<UnkStruct_02013948, Pair,' in text:
        raise ValueError('Missing ARM Pair-return adapter')
    if array_receiver:
        before = '(self->arr[i].*pmf)();'
        if text.count(before) != 1:
            raise ValueError('Array member receiver source changed')
        text = text.replace(before, '((&self->arr[i])->*pmf)();')
    if re.search(r'(?<!\.)\.\*', text):
        raise ValueError('Untranslated object member call')
    return '#include "native_member.h"\n' + text


def specifications() -> dict:
    path = Path(__file__).resolve().parents[1] / 'runtime/native-member-boundary.json'
    manifest = json.loads(path.read_text())
    if manifest['version'] != 1:
        raise ValueError('Unsupported member boundary manifest')
    return manifest['sources']


def keyed_copy(text: str, tables: dict) -> str:
    """Use pinned ROM keys where the matching source declares zero placeholders.

    A source that already writes the keys must write exactly the pinned ROM keys.
    """
    for name, spec in tables.items():
        pattern = r'\b' + re.escape(name) + r'\[(\d+)\]\s*=\s*\{'
        matches = list(re.finditer(pattern, text))
        if len(matches) != 1 or int(matches[0][1]) != spec['count']:
            raise ValueError('Keyed member table declaration changed: ' + name)
        match = matches[0]
        start = position = match.end()
        depth = 1
        while position < len(text) and depth:
            depth += (text[position] == '{') - (text[position] == '}')
            position += 1
        terminator = re.match(r'\s*;', text[position:])
        if depth or terminator is None:
            raise ValueError('Keyed member initializer changed: ' + name)
        initializer = text[start:position-1]
        row = r'(\{\s*)(0x[0-9a-fA-F]+|\d+)(\s*,)'
        rows = [int(m[2], 0) for m in re.finditer(row, initializer)]
        if len(rows) != len(spec['keys']) or any(rows) and rows != spec['keys']:
            raise ValueError('Keyed member initializer rows changed: ' + name)
        keys = iter(spec['keys'])
        initializer = re.sub(row, lambda m: m[1] + str(next(keys)) + m[3], initializer)
        end = position + terminator.end()
        assertion = (f'\n    static_assert(sizeof({name}[0]) == 12, "ROM keyed member stride");\n'
                     f'    static_assert(__builtin_offsetof(Entry, pmf) == 4, "ROM keyed member offset");')
        text = text[:start] + initializer + text[position-1:end] + assertion + text[end:]
    return text


def shared_copy(text: str, storage: dict) -> str:
    """Initialize audited local tables at their observable DS addresses.

    A PC compiler can discard unused local arrays even when another ROM table
    points at their original storage. Private storage may also remain visible
    after another overlay replaces its owner. Preserve the ARM guard word and its low
    initialization bit, including after an overlay reload clears the DS data.
    """
    edits = []
    for name, spec in storage.items():
        # a typedef name, or the member type declarations() wrote for an inline declarator
        pattern = r'\bstatic\s+(\w+|NativeMember<[^;{}<>]*>)\s+' + re.escape(name) + r'\[(\d+)\]\s*=\s*\{'
        matches = list(re.finditer(pattern, text))
        if len(matches) != 1:
            raise ValueError('Shared member array declaration changed: ' + name)
        match = matches[0]
        if int(match[2]) != spec['count']:
            raise ValueError('Shared member array size changed: ' + name)
        start = position = match.end()
        depth = 1
        while position < len(text) and depth:
            depth += (text[position] == '{') - (text[position] == '}')
            position += 1
        terminator = re.match(r'\s*;', text[position:])
        if depth or terminator is None:
            raise ValueError('Shared member initializer changed: ' + name)
        end = position + terminator.end()
        values = text[start:position-1]
        kind, count = match[1], spec['count']
        replacement = f'''{kind} *const {name} = reinterpret_cast<{kind} *>(0x{spec['address']}u);
    {{
        static_assert(sizeof({kind}) == 8, "ROM shared member table stride");
        unsigned int *const guard = reinterpret_cast<unsigned int *>(0x{spec['guard_address']}u);
        unsigned int previous = *guard;
        if ((previous & 1u) == 0) {{
            const {kind} initial[{count}] = {{{values}}};
            for (unsigned int i = 0; i < {count}; ++i) {name}[i] = initial[i];
            *guard = previous | 1u;
        }}
    }}'''
        edits.append((match.start(), end, replacement))
    for start, end, replacement in sorted(edits, reverse=True):
        text = text[:start] + replacement + text[end:]
    return text


def _literal(data: bytes, base: int, start: int, size: int, literal: int, value: int) -> bool:
    """Whether the body's literal pool word at `literal` holds `value`."""
    return (literal % 4 == 0 and start <= literal <= start + size - 4
            and data[literal - base:literal - base + 4] == value.to_bytes(4, 'little'))


def rom_tables(text: str, tables: dict, data: bytes, base: int, start: int, size: int) -> None:
    """Check member tables a source declares extern at the ROM's DS address.

    The matching source fills the ROM's own table under the ROM's own guard word,
    as the ROM body does: the PC copy reads and writes the same two-word entries.
    The body's literal pool must name both, and the declarations must be exact.
    """
    for name, table in tables.items():
        address, guard = int(table['address'], 16), int(table['guard_address'], 16)
        count = table['count']
        if (not re.fullmatch(r'data_(?:ov\d{3}_)?[0-9a-f]{8}', name) or int(name[-8:], 16) != address
                or not re.fullmatch(r'data_(?:ov\d{3}_)?[0-9a-f]{8}', table['guard'])
                or int(table['guard'][-8:], 16) != guard or not 0 < count <= 256
                or address % 4 or guard % 4 or not 0x02000000 <= address <= 0x02400000 - count * 8
                or not 0x02000000 <= guard <= 0x02400000 - 4):
            raise ValueError('Invalid ROM member table: ' + name)
        if not _literal(data, base, start, size, int(table['table_literal'], 16), address):
            raise ValueError('ROM member table literal changed: ' + name)
        if not _literal(data, base, start, size, int(table['guard_literal'], 16), guard):
            raise ValueError('ROM member table guard literal changed: ' + name)
        declared = re.findall(r'\bextern\s+(?:const\s+)?(?:\w+\s*::\s*)*\w+\s+(?:\w+\s*,\s*)*'
                              + re.escape(name) + r'\[(\d+)\]\s*[;,]', text)
        declared += re.findall(r'\bextern\s+\w+\s*\*?\s*\(\s*\w+\s*::\s*\*\s*' + re.escape(name)
                               + r'\[(\d+)\]\s*\)\s*\([^()]*\)\s*;', text)
        if declared != [str(count)]:
            raise ValueError('ROM member table declaration changed: ' + name)
        if len(re.findall(r'\bextern\s+(?:unsigned\s+)?int\s+' + re.escape(table['guard']) + r'\s*;', text)) != 1:
            raise ValueError('ROM member table guard declaration changed: ' + name)


def rom_constants(text: str, constants: dict, modules: dict, image, module: str) -> None:
    """Check the ROM data words of member-pointer constants the source reads extern."""
    for name, constant in constants.items():
        m = re.fullmatch(r'data_(?:ov\d{3}_)?([0-9a-f]{8})', name)
        if not m or not re.search(r'\bextern\b[^;{}]*\b' + re.escape(name) + r'\b', text):
            raise ValueError('ROM member constant declaration changed: ' + name)
        address = int(m[1], 16)
        function, adjustment = constant['words']
        expected = function.to_bytes(4, 'little') + adjustment.to_bytes(4, 'little', signed=True)
        for owner in dict.fromkeys([module, 'main']):
            data, base = image(owner), modules[owner]['base']
            if base <= address <= base + len(data) - 8:
                if data[address - base:address - base + 8] != expected:
                    raise ValueError('ROM member constant changed: ' + name)
                break
        else:
            raise ValueError('ROM member constant outside its module: ' + name)


def checked_copy(relative: str, text: str, root: Path, modules: dict, image, *, specs=None) -> tuple[str, dict[str, str]]:
    """Check the complete original input closure before producing PC copies.

    Returns the body plus include-relative header copies. The build caller must
    put the returned headers before the original include directory and include
    their contents in its cache key. This function does not select a policy.
    """
    spec = (specifications() if specs is None else specs)[relative]
    if hashlib.sha256(text.encode()).hexdigest() != spec['source_sha256']:
        raise ValueError('Member boundary source changed: ' + relative)
    data = image(spec['module'])
    base = modules[spec['module']]['base']
    begin = int(spec['address'], 16) - base
    body = data[begin:begin + spec['size']] if begin >= 0 else b''
    if len(body) != spec['size'] or hashlib.sha256(body).hexdigest() != spec['rom_sha256']:
        raise ValueError('Member boundary ROM body changed: ' + relative)
    headers = {}
    for name, digest in spec['headers'].items():
        raw = (root / name).read_bytes()
        if hashlib.sha256(raw).hexdigest() != digest:
            raise ValueError('Member boundary header changed: ' + name)
        original = raw.decode()
        if re.search(r'::\s*\*', original):
            if name not in MEMBER_HEADERS:
                raise ValueError('Unaudited member boundary header: ' + name)
            translated, _ = declarations(original)
            headers[name.removeprefix('include/')] = '#include "native_member.h"\n' + translated
    constants = {}
    for name, constant in spec['constants'].items():
        function, adjustment = constant['words']
        expected = function.to_bytes(4, 'little') + adjustment.to_bytes(4, 'little', signed=True)
        if not constant['literal_addresses']:
            raise ValueError('Member constant lacks a ROM literal: ' + name)
        for address in constant['literal_addresses']:
            offset = int(address, 16) - base
            if offset < 0 or data[offset:offset + 8] != expected:
                raise ValueError('Member boundary ROM constant changed: ' + name)
        constants[name] = (function, adjustment)
    if relative == 'main/func_020274e0.cpp':
        if not headers or constants or '::*' in text:
            raise ValueError('Header-only member boundary changed')
        return text, headers
    shared = spec.get('shared_storage', {})
    retained = spec.get('retained_storage', {})
    if shared.keys() & retained.keys():
        raise ValueError('Duplicate member storage declaration: ' + relative)
    storage = {**shared, **retained}
    for name, table in storage.items():
        if (not 0 < table['count'] <= 64
                or name in shared and not table.get('pointer_literals')
                or name in retained and 'pointer_literals' in table):
            raise ValueError('Invalid shared member storage: ' + name)
        for address_key, literal_key in [('address', 'table_literal'), ('guard_address', 'guard_literal')]:
            address, literal = int(table[address_key], 16), int(table[literal_key], 16)
            size = table['count'] * 8 if address_key == 'address' else 4
            if (address % 4 or not 0x02000000 <= address <= 0x02400000 - size
                    or literal % 4 or not base + begin <= literal <= base + begin + len(body) - 4):
                raise ValueError('Shared member storage outside audited range: ' + name)
            if data[literal-base:literal-base+4] != address.to_bytes(4, 'little'):
                raise ValueError('Shared member storage literal changed: ' + name)
        for literal in table.get('pointer_literals', []):
            offset = int(literal, 16) - base
            if offset < 0 or data[offset:offset+4] != int(table['address'], 16).to_bytes(4, 'little'):
                raise ValueError('Shared member alias changed: ' + name)
    if retained:
        # A retained table's owner fills it from the constants: its literal pool names each one.
        pool = {int.from_bytes(body[i:i+4], 'little') for i in range(0, len(body) - 3, 2)}
        for name, constant in constants.items():
            if not any(int(address, 16) in pool for address in spec['constants'][name]['literal_addresses']):
                raise ValueError('Retained member constant not loaded by its owner: ' + name)
    keyed = spec.get('keyed_tables', {})
    for name, table in keyed.items():
        address, literal = int(table['address'], 16), int(table['table_literal'], 16)
        count = table['count']
        if (not 0 < count <= 64 or table['stride'] != 12 or len(table['keys']) != count
                or any(not isinstance(key, int) or not 0 <= key <= 255 for key in table['keys'])
                or address % 4 or literal % 4
                or not base + begin <= literal <= base + begin + len(body) - 4):
            raise ValueError('Invalid keyed member table: ' + name)
        if data[literal-base:literal-base+4] != address.to_bytes(4, 'little'):
            raise ValueError('Keyed member table literal changed: ' + name)
        offset = address - base
        raw = data[offset:offset + count * 12] if offset >= 0 else b''
        if len(raw) != count * 12 or hashlib.sha256(raw).hexdigest() != table['rom_sha256']:
            raise ValueError('Keyed member ROM data changed: ' + name)
        keys = [int.from_bytes(raw[i*12:i*12+4], 'little') for i in range(count)]
        if keys != table['keys']:
            raise ValueError('Keyed member ROM keys changed: ' + name)
    rom_tables(text, spec.get('rom_tables', {}), data, base, base + begin, len(body))
    rom_constants(text, spec.get('rom_constants', {}), modules, image, spec['module'])
    translated = copy(text, constants, pair_result=relative == 'main/func_02013948.cpp',
                      array_receiver=relative == 'main/func_02034e28.cpp',
                      register_argument=relative == 'main/func_0201f40c.cpp', header_types=bool(headers))
    return keyed_copy(shared_copy(translated, storage), keyed), headers
