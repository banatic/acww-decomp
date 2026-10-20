"""Block-scope statics of Native sources at the ROM's DS addresses.

mwccarm keeps a function's block-scope statics in its module's .bss or .data. One with a
dynamic initializer (a table of member-function pointers, objects built by a constructor,
values read from other data) is filled the first time control reaches it, behind a guard word
of its own whose bit 0 says done. A PC copy compiled as it is keeps the static, and the PC's
own guard, in PC storage instead, which differs from the ROM in three ways:

- the ROM's copy is never written, so memory differs from the Reference's, and ROM code that
  reads it (the owner run as Reference, a twin overlay's owner at the same address) finds zero;
- loading an overlay again clears its .bss and restores its .data, and the ROM's code fills
  the static again; a PC copy keeps its old guard and values (stale pointers into an old object);
- a pointer into the static that the owner hands out is a PC address, not the DS one.

`runtime/native-rom-statics.json` pins, per source, each such static: its DS address and the
literals of the owner's ROM body that name it (and its guard), its size and, for .data, the
bytes the ROM's image holds there. `translate` checks all of them against the ROM and makes
the PC copy name that storage: the declaration becomes a macro for the DS object (an lvalue of
the declared type, array types included), with its initializer run under the ROM's guard word
as mwccarm's code runs it. Plain statics take their initial value from the DS image, as the
ROM's code does.

`python tools/native_statics.py` derives the entries from the mwccarm objects of the sources
(MWCC_ROOT): the static's and its guard's symbols (`name$N`, `_ZGVname$N`), the owner's
relocations naming them, and the words at those literals in the ROM. It also derives the
member-pointer constants of sources that build their tables from `&Class::method` and are not
yet in the member boundary (`runtime/native-member-boundary.json`), so their PC copies write
the ROM's two-word encodings. `--check` only compares (tools/test_native_statics.py).
"""
from __future__ import annotations

import hashlib
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402

MANIFEST = C.ROOT / 'runtime' / 'native-rom-statics.json'
BOUNDARY = C.ROOT / 'runtime' / 'native-member-boundary.json'
# mwccarm's local data symbols: a block-scope static (name$N, its guard _ZGVname$N) or a
# file-scope one (name); its constants are @N
LOCAL = re.compile(r'(?P<guard>_ZGV)?(?P<name>[A-Za-z_]\w*)(?P<block>\$\d+)?')
# Statics the member boundary already places (shared_storage, retained_storage, rom_statics).
BOUNDARY_KINDS = ('shared_storage', 'retained_storage', 'rom_statics')


def specifications() -> dict:
    if not MANIFEST.exists():
        return {}
    manifest = json.loads(MANIFEST.read_text())
    if manifest['version'] != 1:
        raise ValueError('Unsupported ROM statics manifest')
    return manifest['sources']


SPECS = specifications()


def paths() -> set[str]:
    return set(SPECS)


# ------------------------------------------------------------------------------ source text

def masked(text: str) -> str:
    """`text` with comments, string and character literals blanked (same length, same lines)."""
    out, i, n = list(text), 0, len(text)
    while i < n:
        if text.startswith('//', i):
            j = text.find('\n', i)
            j = n if j < 0 else j
        elif text.startswith('/*', i):
            j = text.find('*/', i + 2)
            j = n if j < 0 else j + 2
        elif text[i] in '"\'':
            j = i + 1
            while j < n and text[j] != text[i]:
                j += 2 if text[j] == '\\' else 1
            j += 1
        else:
            i += 1
            continue
        for k in range(i, min(j, n)):
            if out[k] != '\n':
                out[k] = ' '
        i = j
    return ''.join(out)


def _close(text: str, start: int, stop: str) -> int:
    """Index of the first `stop` character at nesting depth 0 from `start` (brackets of all kinds)."""
    depth = 0
    for i in range(start, len(text)):
        c = text[i]
        if c in '([{':
            depth += 1
        elif c in ')]}':
            if depth == 0:
                if c == stop:
                    return i
                raise ValueError('Unbalanced static declaration')
            depth -= 1
        elif c == stop and depth == 0:
            return i
    raise ValueError('Unterminated static declaration')


def declaration(text: str, name: str) -> dict:
    """The one block-scope declaration `static TYPE name[COUNT] = INIT;` of `name` in `text`.

    Returns its span, type, count (None for a scalar, '' for `[]`), initializer (None when it
    has none), the initializer's top-level element count and the end of the enclosing block.
    """
    plain = masked(text)
    pattern = (r'\bstatic\s+(?P<type>(?:[A-Za-z_][\w:]*(?:\s*<[^;{}()]*>)?[\s*&]*)+?)\s*\b'
               + re.escape(name) + r'\s*(?:\[(?P<count>[^\[\]]*)\])?\s*(?P<after>[=;])')
    # (start, end of `= ` or `;`, type, count, `=` or `;`, definition of the type it declares)
    found = []
    for m in re.finditer(pattern, plain):
        found.append((m.start(), m.end(), ' '.join(m['type'].split()), m['count'], m['after'], None))
    # a structure defined in the declaration; an unnamed one is given a name for the PC copy
    defined = r'\bstatic\s+(?P<tag>struct|class)\s+(?P<tag_name>\w+\s*)?\{'
    for m in re.finditer(defined, plain):
        close = _close(plain, m.end(), '}')
        rest = re.compile(r'\s*\b' + re.escape(name) + r'\s*(?:\[(?P<count>[^\[\]]*)\])?\s*(?P<after>[=;])')
        r = rest.match(plain, close + 1)
        if r:
            tag = (m['tag_name'] or '').strip() or 'native_static_' + name
            body = text[m.start('tag_name') if m['tag_name'] else m.end('tag'):close + 1].strip()
            found.append((m.start(), r.end(), tag, r['count'], r['after'],
                          f"{m['tag']} {body if m['tag_name'] else tag + ' ' + body};"))
    found = [f for f in found
             if plain.count('{', 0, f[0]) - plain.count('}', 0, f[0]) >= 1]
    if len(found) != 1:
        raise ValueError(f'ROM static declaration changed: {name} ({len(found)} declarations)')
    start, after_end, kind, count, after, definition = found[0]
    if not kind or kind.split()[0] in ('inline', 'void') and '*' not in kind or kind.startswith('extern'):
        raise ValueError('Unsupported static declaration: ' + name)
    count = None if count is None else count.strip()
    init, elements, end = None, None, after_end
    if after == '=':
        stop = _close(plain, after_end, ';')
        init = text[after_end:stop].strip()
        end = stop + 1
        # template arguments (the PC member type of a translated constant) hold commas
        body = re.sub(r'NativeMember<[^<>;{}]*>', 'NativeMember', masked(init))
        if count is not None:
            if not (body.startswith('{') and body.endswith('}')):
                raise ValueError('Unsupported array initializer: ' + name)
            inner, parts, depth, last = body[1:-1], [], 0, 0
            for i, c in enumerate(inner):
                depth += c in '([{'
                depth -= c in ')]}'
                if c == ',' and depth == 0:
                    parts.append(inner[last:i])
                    last = i + 1
            parts.append(inner[last:])
            elements = len([p for p in parts if p.strip()])
    # the enclosing block ends at the first unmatched closing brace
    depth, block = 0, None
    for i in range(end, len(plain)):
        if plain[i] == '{':
            depth += 1
        elif plain[i] == '}':
            if depth == 0:
                block = i
                break
            depth -= 1
    if block is None:
        raise ValueError('Static outside a block: ' + name)
    scope = plain[end:block]
    if re.search(r'(?:\.|->|::)\s*' + re.escape(name) + r'\b|\b' + re.escape(name) + r'\s*::', scope):
        raise ValueError('Static name used as a member: ' + name)
    if re.search(r'\bstatic\b[^;{}]*\b' + re.escape(name) + r'\b', scope):
        raise ValueError('Static name declared again: ' + name)
    return {'start': start, 'end': end, 'type': kind, 'count': count, 'init': init,
            'elements': elements, 'block': block, 'definition': definition}


def placed(text: str, name: str, item: dict, cpp: bool) -> str:
    """`text` with the static `name` at its DS address (`item`: one manifest entry)."""
    d = declaration(text, name)
    count, size, kind = item.get('count'), item['size'], d['type']
    if (d['count'] is None) != (count is None) or d['count'] and int(d['count'], 0) != count:
        raise ValueError('ROM static declaration changed: ' + name)
    if count is not None and d['count'] == '' and d['elements'] != count:
        raise ValueError('ROM static initializer changed: ' + name)
    guarded = 'guard' in item
    # mwccarm guards a dynamic initializer; a plain static's initial value is the DS image's
    # (.data, pinned by its bytes) or zero (.bss)
    if guarded and d['init'] is None or not guarded and item['section'] == 'bss' and d['init'] is not None \
            and not re.fullmatch(r'\{?\s*0?\s*\}?', masked(d['init'])):
        raise ValueError('ROM static guard changed: ' + name)
    address = int(item['address'], 16)
    shape = f'({kind} (*)[{count}])' if count is not None else f'({kind} *)'
    total = f'sizeof({kind}) * {count}' if count is not None else f'sizeof({kind})'
    check = 'static_assert' if cpp else '_Static_assert'
    lines = ([d['definition']] if d['definition'] else []) + [
             f'#define {name} (*{shape} 0x{address:08x}u)',
             f'{check}({total} == {size}, "ROM static size");']
    if guarded:
        initial = f'native_initial_{name}'
        constant = kind if re.search(r'(?:^|\s)const(?:\s|$)', kind) else kind + ' const'
        array = f'[{count}]' if count is not None else ''
        lines += ['{',
                  f'    unsigned int *const native_guard_{name} = (unsigned int *) 0x{item["guard"]}u;',
                  f'    unsigned int native_previous_{name} = *native_guard_{name};',
                  f'    if ((native_previous_{name} & 1u) == 0) {{',
                  f'        {constant} {initial}{array} = {d["init"]};',
                  f'        __builtin_memcpy((void *) &{name}, &{initial}, sizeof {initial});',
                  f'        *native_guard_{name} = native_previous_{name} | 1u;',
                  '    }',
                  '}']
    replacement = '\n' + '\n'.join(lines) + '\n'
    block = d['block']
    return (text[:d['start']] + replacement + text[d['end']:block + 1] + f'\n#undef {name}\n'
            + text[block + 1:])


# ------------------------------------------------------------------------------ checks

def _literal(at: int, addend: int) -> str:
    """A literal's address, and the offset into the static it names when not 0."""
    return f'{at:08x}' + (f'+{addend}' if addend else '')


def _word(data: bytes, base: int, at: int) -> int:
    return int.from_bytes(data[at - base:at - base + 4], 'little') if base <= at <= base + len(data) - 4 else -1


def check(relative: str, original: str, spec: dict, modules: dict, image) -> None:
    """The pinned source, the owner's ROM body, and every literal and DS range it names."""
    if hashlib.sha256(original.encode()).hexdigest() != spec['source_sha256']:
        raise ValueError('ROM statics source changed: ' + relative)
    module = modules[spec['module']]
    data, base = image(spec['module']), module['base']
    begin = int(spec['address'], 16)
    body = data[begin - base:begin - base + spec['size']] if begin >= base else b''
    if len(body) != spec['size'] or hashlib.sha256(body).hexdigest() != spec['rom_sha256']:
        raise ValueError('ROM statics owner body changed: ' + relative)
    end = begin + spec['size']
    for name, item in spec['statics'].items():
        address, size = int(item['address'], 16), item['size']
        named = [(address, item['literals'])]
        if 'guard' in item:
            named.append((int(item['guard'], 16), item['guard_literals']))
        for value, literals in named:
            if not literals:
                raise ValueError('ROM static literal changed: ' + name)
            for literal in literals:
                at, _, addend = literal.partition('+')
                at, addend = int(at, 16), int(addend or '0')
                if (not begin <= at <= end - 4 or at % 4 or not 0 <= addend < max(size, 4)
                        or _word(data, base, at) != value + addend):
                    raise ValueError('ROM static literal changed: ' + name)
        if item['section'] == 'data':
            raw = data[address - base:address - base + size] if address >= base else b''
            if len(raw) != size or hashlib.sha256(raw).hexdigest() != item['rom_data_sha256']:
                raise ValueError('ROM static data changed: ' + name)
        elif item['section'] != 'bss':
            raise ValueError('ROM static section: ' + name)
        elif module['bss']:
            if not base + module['size'] <= address <= base + module['size'] + module['bss'] - size:
                raise ValueError('ROM static outside its module .bss: ' + name)
        elif not 0x02000000 <= address <= 0x02400000 - size:
            raise ValueError('ROM static outside main RAM: ' + name)
        if 'guard' in item:
            guard = int(item['guard'], 16)
            if guard % 4 or module['bss'] and not base + module['size'] <= guard < base + module['size'] + module['bss']:
                raise ValueError('ROM static guard outside its module .bss: ' + name)


def translate(relative: str, original: str, text: str, *, specs: dict | None = None,
              modules: dict | None = None, image=None) -> str:
    """`text` (the PC copy of `relative`, whose source is `original`) with its pinned statics
    at their DS addresses."""
    spec = (SPECS if specs is None else specs)[relative]
    check(relative, original, spec, C.modules() if modules is None else modules,
          C.module_image if image is None else image)
    cpp = relative.endswith('.cpp')
    for name, item in spec['statics'].items():
        text = placed(text, name, item, cpp)
    return text


# ------------------------------------------------------------------------------ derivation

def _object(path: Path):
    src = C.parse_source(path)
    data, log = C.compile_source(src)
    if data is None:
        raise ValueError(f'mwccarm failed on {path}: {log[-300:]}')
    elf = C.Elf(data)
    owner = [s for s in elf.symbols if s.type == 2 and s.size and s.name == src.object_symbol]
    if len(owner) != 1:
        raise ValueError('Owner symbol not found: ' + str(path))
    return src, elf, owner[0]


def _literals(src, elf, owner, data: bytes, base: int) -> dict[str, list[tuple[int, int, int]]]:
    """Local data symbol -> (literal address, DS address, addend) for each owner relocation
    naming it (the literal holds the address plus the addend: a pointer into the object)."""
    out: dict[str, list[tuple[int, int, int]]] = {}
    for offset, kind, symbol, addend in elf.relocations(owner.shndx):
        if symbol.bind != 0 or symbol.type != 1 or not owner.value <= offset < owner.value + owner.size:
            continue
        if kind != 2 or not 0 <= addend < max(symbol.size, 4):
            raise ValueError(f'Unexpected relocation of {symbol.name}')
        at = src.address + offset - owner.value
        out.setdefault(symbol.name, []).append((at, (_word(data, base, at) - addend) & 0xffffffff, addend))
    return out


def derive(path: Path, skip: set[str] = frozenset()) -> dict | None:
    """The manifest entry of one source (None when it has no block-scope static to place)."""
    src, elf, owner = _object(path)
    modules = C.modules()
    data, base = C.module_image(src.module), modules[src.module]['base']
    literals = _literals(src, elf, owner, data, base)
    text = path.read_bytes().decode()
    declared = text
    if re.search(r'::\s*\*', masked(text)):
        import native_pmf_boundary as boundary
        try:
            declared = boundary.declarations(text)[0]  # inline member declarators as their PC type
        except ValueError:
            pass
    statics = {}
    for symbol in elf.symbols:
        m = LOCAL.fullmatch(symbol.name)
        if not m or m['guard'] or symbol.type != 1 or symbol.bind != 0:
            continue
        name = m['name']
        if name in skip:
            continue
        if not m['block']:
            raise ValueError(f'File-scope static {name} in {path}: not placed by the member boundary')
        if name in statics:
            raise ValueError(f'Two block-scope statics named {name} in {path}')
        refs = literals.get(symbol.name, [])
        addresses = {a for _, a, _ in refs}
        if len(addresses) != 1:
            raise ValueError(f'{symbol.name}: {len(addresses)} DS addresses in {path}')
        section = elf.sections[symbol.shndx].name.lstrip('.')
        if section not in ('bss', 'data'):
            raise ValueError(f'{symbol.name} in {section}')
        address = addresses.pop()
        item = {'symbol': symbol.name, 'section': section, 'address': f'{address:08x}', 'size': symbol.size,
                'literals': [_literal(at, addend) for at, _, addend in refs]}
        d = declaration(declared, name)
        if d['count'] is not None:
            count = int(d['count'], 0) if d['count'] else d['elements']
            if not count or symbol.size % count:
                raise ValueError(f'{symbol.name}: {symbol.size} bytes in {count} elements')
            item['count'] = count
        guard = '_ZGV' + symbol.name
        if any(s.name == guard for s in elf.symbols):
            grefs = literals.get(guard, [])
            gaddresses = {a for _, a, _ in grefs}
            if len(gaddresses) != 1:
                raise ValueError(f'{guard}: {len(gaddresses)} DS addresses in {path}')
            item['guard'] = f'{gaddresses.pop():08x}'
            item['guard_literals'] = [_literal(at, addend) for at, _, addend in grefs]
        if section == 'data':
            raw = data[address - base:address - base + symbol.size]
            expected = bytearray(elf.section_bytes(symbol.shndx)[symbol.value:symbol.value + symbol.size])
            relocated = {offset for offset, _, _, _ in elf.relocations(symbol.shndx)}
            # the object's bytes, apart from relocated words, are the ROM's
            for offset in relocated:
                if symbol.value <= offset < symbol.value + symbol.size:
                    expected[offset - symbol.value:offset - symbol.value + 4] = raw[offset - symbol.value:offset - symbol.value + 4]
            if bytes(expected) != raw:
                raise ValueError(f'{symbol.name}: the ROM data differs from the object')
            item['rom_data_sha256'] = hashlib.sha256(raw).hexdigest()
        statics[name] = item
    if not statics:
        return None
    begin = src.address - base
    return {'source_sha256': hashlib.sha256(text.encode()).hexdigest(), 'module': src.module,
            'address': f'{src.address:08x}', 'size': src.size,
            'rom_sha256': hashlib.sha256(data[begin:begin + src.size]).hexdigest(), 'statics': statics}


MANGLED = re.compile(r'_ZN(?:\d+[A-Za-z_]\w*?)+E')


def _method_name(mangled: str) -> str | None:
    """The last name of an Itanium nested name (_ZN<len><id>...E...)."""
    if not mangled.startswith('_ZN'):
        return None
    i, names = 3, []
    while i < len(mangled) and mangled[i].isdigit():
        j = i
        while mangled[j].isdigit():
            j += 1
        length = int(mangled[i:j])
        names.append(mangled[j:j + length])
        i = j + length
    return names[-1] if names and i < len(mangled) and mangled[i] == 'E' else None


def member_entry(path: Path) -> dict:
    """A member-boundary entry for a source whose tables hold `&Class::method` constants.

    Each constant's two words are the ROM's, at the literal of the owner that names the
    mwccarm constant (`@N`) whose first word is relocated to that method.
    """
    import native_pmf_boundary as boundary
    src, elf, owner = _object(path)
    modules = C.modules()
    data, base = C.module_image(src.module), modules[src.module]['base']
    literals = _literals(src, elf, owner, data, base)
    text = path.read_bytes().decode()
    spelled = boundary.methods(boundary.discard_handlers(text))
    by_method: dict[str, list[tuple[int, int, int]]] = {}
    for symbol in elf.symbols:
        if not re.fullmatch(r'@\d+', symbol.name) or symbol.type != 1 or symbol.size != 8:
            continue
        relocations = [r for r in elf.relocations(symbol.shndx) if symbol.value <= r[0] < symbol.value + 8]
        raw = elf.section_bytes(symbol.shndx)[symbol.value:symbol.value + 8]
        if len(relocations) != 1 or relocations[0][0] != symbol.value or relocations[0][3]:
            raise ValueError(f'{symbol.name}: not one relocated method word in {path}')
        method = _method_name(relocations[0][2].name)
        for at, address, _ in literals.get(symbol.name, []):
            words = (_word(data, base, address), int.from_bytes(data[address - base + 4:address - base + 8], 'little', signed=True))
            if words[1] != int.from_bytes(raw[4:], 'little', signed=True):
                raise ValueError(f'{symbol.name}: adjustment differs from the ROM')
            by_method.setdefault(method, []).append((address, *words))
    constants = {}
    for name in sorted(set(spelled), key=spelled.index):
        found = by_method.get(name.split('::')[1], [])
        words = {(f, a) for _, f, a in found}
        if len(words) != 1:
            raise ValueError(f'{name}: {len(words)} ROM constants in {path}')
        function, adjustment = words.pop()
        suffix = re.search(r'_([0-9a-f]{8})$', name)
        if suffix and function & ~1 != int(suffix[1], 16) or adjustment:
            raise ValueError(f'{name}: ROM constant {function:08x}/{adjustment} does not name it')
        constants[name] = {'words': [function, adjustment],
                           'literal_addresses': sorted({f'{a:08x}' for a, _, _ in found})}
    headers = {}
    for header in C.included_files(path):
        if C.INCLUDE in header.parents:
            headers[header.relative_to(C.ROOT).as_posix()] = hashlib.sha256(header.read_bytes()).hexdigest()
    begin = src.address - base
    return {'source_sha256': hashlib.sha256(text.encode()).hexdigest(), 'module': src.module,
            'address': f'{src.address:08x}', 'size': src.size,
            'rom_sha256': hashlib.sha256(data[begin:begin + src.size]).hexdigest(),
            'headers': headers, 'constants': constants}


def candidates() -> list[Path]:
    """Native sources whose text declares anything static (the rest have no local statics)."""
    return [p for p in C.all_sources() if C.SRC in p.parents
            and re.search(r'\bstatic\b', masked(p.read_bytes().decode('utf-8', 'replace')))]


def derive_all() -> tuple[dict, dict]:
    """(ROM statics entries, new member-boundary entries) for every Native source."""
    boundary = json.loads(BOUNDARY.read_text())['sources']
    statics, members = {}, {}
    for path in candidates():
        relative = path.relative_to(C.SRC).as_posix()
        known = boundary.get(relative, {})
        skip = {name for kind in BOUNDARY_KINDS for name in known.get(kind, {})}
        entry = derive(path, skip)
        if entry is None:
            continue
        statics[relative] = entry
        if relative not in boundary and re.search(r'::\s*\*', masked(path.read_bytes().decode())):
            members[relative] = member_entry(path)
    return statics, members


def main() -> None:
    only_check = sys.argv[1:] == ['--check']
    statics, members = derive_all()
    current = specifications()
    manifest = {'version': 1, 'sources': dict(sorted(statics.items()))}
    boundary = json.loads(BOUNDARY.read_text())
    changed = current != manifest['sources'] or bool(members)
    if only_check:
        if changed:
            raise SystemExit('runtime/native-rom-statics.json or the member boundary is not what the ROM gives')
        print(f'{len(statics)} sources, {sum(len(e["statics"]) for e in statics.values())} statics agree')
        return
    MANIFEST.write_text(json.dumps(manifest, indent=2) + '\n', newline='\n')
    if members:
        boundary['sources'] = dict(sorted({**boundary['sources'], **members}.items()))
        BOUNDARY.write_text(json.dumps(boundary, indent=2) + '\n', newline='\n')
    print(f'{len(statics)} sources, {sum(len(e["statics"]) for e in statics.values())} statics; '
          f'{len(members)} new member-boundary sources')


if __name__ == '__main__':
    main()
