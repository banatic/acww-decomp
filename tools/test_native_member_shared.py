"""Actual owners of aliased or retained DS storage; reject the former copies."""
from pathlib import Path
import json
import os
import re
import subprocess
import sys
sys.path.insert(0, 'tools')
import common as C
import diffcheck
import native
import native_pmf_boundary as boundary

host = 'windows' if os.name == 'nt' else 'linux'
baseline = sys.argv[1:] == ['--baseline']
base = C.BUILD/'native-member-shared-check'
base.mkdir(exist_ok=True)
storage = {p: {**s.get('shared_storage', {}), **s.get('retained_storage', {})}
           for p, s in boundary.specifications().items() if s.get('shared_storage') or s.get('retained_storage')}
reports = []
# ov009 owners: the offset of the state their table is indexed by and its size in bytes (0: the
# owner takes the index as its second argument), and the PC call. Every index is tried, and two
# past the table.
OV009 = {
    'ov009/func_ov009_022638d0.cpp': (0x27c, 4, 'static_cast<Obj_ov009_022658dc *>(p)->func_ov009_022638d0()'),
    'ov009/func_ov009_022639a0.cpp': (0x27c, 0, 'static_cast<Obj_ov009_022658dc *>(p)->func_ov009_022639a0(page)'),
    'ov009/func_ov009_022640d8.cpp': (0x134, 1, 'static_cast<Obj_ov009_022658dc *>(p)->Obj_ov009_022658dc::vfunc_74()'),
    'ov009/func_ov009_0226418c.cpp': (0x134, 0, 'func_ov009_0226418c(static_cast<CEx *>(p), page)'),
}
FIXTURES = {'ov054/func_ov054_022608ac.cpp', 'ov147/func_ov147_0229942c.cpp', 'ov147/func_ov147_0229a634.cpp', *OV009}
# The other retained tables are checked by native_pmf_boundary.checked_copy (source, ROM body,
# the guard's, the table's and every constant's literal) and by the game runs.
storage = {relative: tables for relative, tables in storage.items() if relative in FIXTURES}
for relative, tables in storage.items():
    path = C.SRC/relative
    parsed = C.parse_source(path)
    case = int(parsed.module[2:])
    state_table = relative == 'ov147/func_ov147_0229a634.cpp'
    folder = base/(host+('-baseline-' if baseline else '-fixed-')+str(case)+f'-{parsed.address:x}')
    folder.mkdir(exist_ok=True)
    source = path.read_bytes().decode()
    image = C.module_image(parsed.module)
    module_base = C.modules()[parsed.module]['base']
    spec = boundary.specifications()[relative]
    entries = []
    for name, entry in tables.items():
        match = re.search(r'static \w+ '+name+r'\[\d+\]\s*=\s*\{([^}]+)\}', source)
        assert match
        values = []
        for expression in match[1].split(','):
            expression = expression.strip()
            if not expression:
                continue  # after a trailing comma
            if expression.startswith('&'):
                values.extend(spec['constants'][expression[1:]]['words'])
            elif expression.startswith('STATE_'):
                macro = re.search(r'^#define\s+'+re.escape(expression)+r'\s+\(PMF_t\)\s*&\s*(\w+::\w+)',
                                  source, re.M)
                assert macro, expression
                values.extend(spec['constants'][macro[1]]['words'])
            elif expression == '__ptmf_null':
                data = C.module_image('autoload_2')
                offset = 0x0213dd98-C.modules()['autoload_2']['base']
                assert data[offset:offset+8] == bytes(8)
                values.extend((0, 0))
            else:
                address = int(expression[-8:], 16)
                offset = address-module_base
                values.extend(int.from_bytes(image[offset+i:offset+i+4], 'little') for i in (0, 4))
        assert len(values) == entry['count']*2
        entries.append('{'+','.join(['0x'+entry['address'], '0x'+entry['guard_address'], str(entry['count']),
                                     '{'+','.join(hex(v) for v in values)+'}'])+'}')
    storage_start = min(int(entry['guard_address'],16) for entry in tables.values())-4
    storage_end = max(int(entry['address'],16)+entry['count']*8 for entry in tables.values())+4
    selector = OV009.get(relative)
    pages = (3 if state_table else 9 if case == 147 else 5 if selector is None
             else next(iter(tables.values()))['count'] + 2)
    header = (f'#define CASE_ID {case}\n#define STATE_TABLE {int(state_table)}\n'
              + (f'#define STATE_OFFSET {selector[0]:#x}\n#define STATE_BYTES {selector[1]}\n' if selector else '')
              + f'#define PAGES {pages}\n'
              f'#define MODULE_BASE {module_base:#x}u\n#define OWNER {parsed.address:#x}u\n#define OWNER_SIZE {parsed.size}\n'
              f'#define STORAGE_BASE {storage_start:#x}u\n#define STORAGE_SIZE {storage_end-storage_start}\n'
              f'#define TABLE_COUNT {len(tables)}\n'
              'struct Table { unsigned address, guard, count, words[18]; };\n'
              'static const struct Table tables[] = {'+','.join(entries)+'};\n'
              'static const unsigned char module_rom[] = {'+','.join(hex(b) for b in image)+'};\n')
    (folder/'shared_rom.h').write_text(header,newline='\n')
    copy = boundary.checked_copy(relative,source,C.ROOT,C.modules(),C.module_image)[0]
    if baseline:
        copy = boundary.copy(source, {name: tuple(value['words']) for name, value in spec['constants'].items()})
    call = ('static_cast<Obj_ov147_0229ac1c *>(p)->func_ov147_0229a634()' if state_table else
            'static_cast<Obj_ov054_02263004 *>(p)->func_ov054_022608ac(0x80000001u)' if case==54 else
            selector[2] if selector else
            'func_ov147_0229942c(static_cast<UnkStruct_0229942c_2 *>(p))')
    copy += '\nextern "C" void shared_invoke(void *p, unsigned page) { (void) page; '+call+'; }\n'
    body = folder/'body.cpp'; body.write_text(copy,newline='\n')
    obj = folder/'body.o'
    subprocess.run([*native.compiler(),*native.flags_for(path),'-I'+str(C.ROOT/'runtime'),'-c',str(body),'-o',str(obj)],check=True)
    names = set(re.findall(r'\bdata_(?:ov\d+_)?[0-9a-f]{8}\b',source))
    symbols = [(name,int(name[-8:],16)) for name in sorted(names)]
    symbols.append(('__ptmf_null',0x0213dd98))
    prefix = '_' if os.name=='nt' else ''
    asm = ''.join(f'.globl {prefix}{name}\n.set {prefix}{name},{address:#x}\n' for name,address in symbols)
    if os.name=='nt':
        asm += '.data\n'
        for name in ('__cxa_guard_acquire','__cxa_guard_release'):
            asm += f'.globl __imp_{prefix}{name}\n__imp_{prefix}{name}:\n.long {prefix}{name}\n'
    else:
        asm += '.section .note.GNU-stack,"",@progbits\n'
    absolute = folder/'absolute.s'; absolute.write_text(asm,newline='\n')
    abs_obj = folder/'absolute.o'
    subprocess.run([*diffcheck.compiler(),'-c',str(absolute),'-o',str(abs_obj)],check=True)
    flags = ['-std=c11','-O2','-Wall','-Wextra','-fwrapv','-fno-strict-aliasing','-D_CRT_SECURE_NO_WARNINGS',
             '-I'+str(C.ROOT/'runtime'),'-I'+str(folder)]
    if os.name=='nt':
        link = ['-Wl,/SAFESEH:NO','-Wl,/DYNAMICBASE:NO','-Wl,/FIXED']
    else:
        flags += ['-D_DEFAULT_SOURCE']
        link = ['-no-pie','-pthread','-Wl,-z,noexecstack','-Wl,-Ttext-segment=0x400000',
                '-Wl,--section-start=.heap_floor=0x10000000']
    exe = folder/('shared.exe' if os.name=='nt' else 'shared')
    subprocess.run([*diffcheck.compiler(),*flags,str(C.ROOT/'tests/native/member_shared.c'),
                    *[str(C.ROOT/'runtime'/n) for n in ('arm.c','memory.c','native_os.c')],str(obj),str(abs_obj),
                    *link,'-o',str(exe)],check=True)
    result = subprocess.run([str(exe)],capture_output=True,text=True,timeout=30)
    row = {'source':relative,'host':host,'baseline':baseline,'exit':result.returncode,
           'stdout':result.stdout,'stderr':result.stderr}
    reports.append(row)
    (folder/'result.json').write_text(json.dumps(row,indent=2)+'\n')
    print(json.dumps(row),flush=True)
    if baseline:
        assert result.returncode==2 and 'expected_storage' in result.stderr
    else:
        assert result.returncode==0
(base/f'results-{host}-{"baseline" if baseline else "fixed"}.json').write_text(json.dumps(reports,indent=2)+'\n')
