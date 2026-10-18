"""Actual ARM versus PC keyed dispatch, including original zero-key negative controls."""
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
base = C.BUILD/'native-member-keyed-check'
base.mkdir(exist_ok=True)
paths = {'ov049/func_ov049_02261848.cpp': ('table',11,'func_ov049_02261848(static_cast<UnkStruct_02261848 *>(p))'),
         'ov051/func_ov051_022604a8.cpp': ('table',14,'func_ov051_022604a8(static_cast<UnkStruct_022604a8 *>(p))'),
         'ov068/func_ov068_02274358.cpp': ('tbl',3,'static_cast<Obj_ov068_02277dc0 *>(p)->func_ov068_02274358(nullptr)')}
specs = {}
reports = []
for relative, (name,count,call) in paths.items():
    path = C.SRC/relative
    parsed = C.parse_source(path)
    source = path.read_bytes().decode()
    case = int(parsed.module[2:])
    mod = C.modules()[parsed.module]
    image = C.module_image(parsed.module)
    spec = boundary.specifications()[relative]['keyed_tables']
    keys = spec[name]['keys']
    specs[relative] = spec
    for baseline in (True,False):
        folder = base/(host+('-baseline-' if baseline else '-fixed-')+str(case))
        folder.mkdir(exist_ok=True)
        header = (f'#define CASE_ID {case}\n#define MODULE_BASE {mod["base"]:#x}u\n#define MODULE_BSS {mod["bss"]}\n'
                  f'#define OWNER {parsed.address:#x}u\n#define OWNER_SIZE {parsed.size}\n'
                  f'#define HAS_ARGUMENT {int(case!=68)}\n#define KEY_COUNT {count}\n'
                  'static const unsigned keys[] = {'+','.join(map(str,keys))+'};\n'
                  'static const unsigned char module_rom[] = {'+','.join(hex(b) for b in image)+'};\n')
        (folder/'keyed_rom.h').write_text(header,newline='\n')
        chosen = json.loads(json.dumps(boundary.specifications()))
        if baseline: chosen[relative].pop('keyed_tables')
        copy, headers = boundary.checked_copy(relative,source,C.ROOT,C.modules(),C.module_image,specs=chosen)
        assert not headers
        copy+='\nextern "C" void keyed_invoke(void *p) { '+call+'; }\n'
        body=folder/'body.cpp'; body.write_text(copy,newline='\n')
        obj=folder/'body.o'
        subprocess.run([*native.compiler(),*native.flags_for(path),'-I'+str(C.ROOT/'runtime'),'-c',str(body),'-o',str(obj)],check=True)
        names=set(re.findall(r'\bdata_(?:ov\d+_)?[0-9a-f]{8}\b',source))
        symbols=[(name,int(name[-8:],16)) for name in sorted(names)]
        prefix='_' if os.name=='nt' else ''
        asm=''.join(f'.globl {prefix}{name}\n.set {prefix}{name},{at:#x}\n' for name,at in symbols)
        if os.name=='nt':
            asm+='.data\n'
            for name in ('__cxa_guard_acquire','__cxa_guard_release'):
                asm+=f'.globl __imp_{prefix}{name}\n__imp_{prefix}{name}:\n.long {prefix}{name}\n'
        else: asm+='.section .note.GNU-stack,"",@progbits\n'
        absolute=folder/'absolute.s'; absolute.write_text(asm,newline='\n')
        abs_obj=folder/'absolute.o'
        subprocess.run([*diffcheck.compiler(),'-c',str(absolute),'-o',str(abs_obj)],check=True)
        flags=['-std=c11','-O2','-Wall','-Wextra','-fwrapv','-fno-strict-aliasing','-D_CRT_SECURE_NO_WARNINGS',
               '-I'+str(C.ROOT/'runtime'),'-I'+str(folder)]
        if os.name=='nt': link=['-Wl,/SAFESEH:NO','-Wl,/DYNAMICBASE:NO','-Wl,/FIXED']
        else:
            flags+=['-D_DEFAULT_SOURCE']
            link=['-no-pie','-pthread','-Wl,-z,noexecstack','-Wl,-Ttext-segment=0x400000','-Wl,--section-start=.heap_floor=0x10000000']
        exe=folder/('keyed.exe' if os.name=='nt' else 'keyed')
        subprocess.run([*diffcheck.compiler(),*flags,str(C.ROOT/'tests/native/member_keyed.c'),
                        *[str(C.ROOT/'runtime'/n) for n in ('arm.c','memory.c','native_os.c')],str(obj),str(abs_obj),
                        *link,'-o',str(exe)],check=True)
        result=subprocess.run([str(exe)],capture_output=True,text=True,timeout=30)
        row={'source':relative,'host':host,'baseline':baseline,'exit':result.returncode,'stdout':result.stdout,'stderr':result.stderr}
        reports.append(row)
        (folder/'result.json').write_text(json.dumps(row,indent=2)+'\n')
        print(json.dumps(row),flush=True)
        if baseline: assert result.returncode==2 and 'expected_count' in result.stderr
        else: assert result.returncode==0
(base/'candidate-keyed-tables.json').write_text(json.dumps(specs,indent=2)+'\n')
(base/f'results-{host}.json').write_text(json.dumps(reports,indent=2)+'\n')
