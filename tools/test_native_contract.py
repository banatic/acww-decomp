"""Check audited source/ROM guards and real recording/replay argument validation."""
import os
import subprocess
import unittest

import common as C
import diffcheck
import native_contract
import run


class ContractGuards(unittest.TestCase):
    def test_original_bodies_and_mutations(self):
        self.assertEqual(len(native_contract.audited(C.ROOT, C.modules(), C.module_image)), 4)
        for contract in native_contract.CONTRACTS:
            source = (C.SRC / contract.source).read_bytes()
            offset = contract.address - C.modules()[contract.module]['base']
            code = C.module_image(contract.module)[offset:offset + contract.size]
            with self.assertRaises(ValueError):
                native_contract.validate(contract, source + b'\n', code)
            with self.assertRaises(ValueError):
                native_contract.validate(contract, source, bytes([code[0] ^ 1]) + code[1:])
            self.assertEqual(contract.encoding >> 8, 1)
        self.assertEqual(native_contract.CONTRACTS[0].encoding & 255, 7)


def fixture():
    folder = C.BUILD / 'native-call-contract-check'
    folder.mkdir(parents=True, exist_ok=True)
    runtime = C.ROOT / 'runtime'
    loop = folder / 'loop.c'
    loop.write_text('#define main call_contract_game_main\n#include "' + (runtime / 'run.c').as_posix() + '"\n', newline='\n')
    sources = [runtime / name for name in run.SOURCES if name not in ('run.c', 'native_run.c')]
    sources += [runtime / 'native_rt.c', loop, C.ROOT / 'tests/native/call_contract.c']
    flags = ['-std=c11', '-O2', '-Wall', '-Wextra', '-fwrapv', '-fno-strict-aliasing',
             '-D_CRT_SECURE_NO_WARNINGS', '-D_CRT_NONSTDC_NO_WARNINGS', '-I' + str(runtime)]
    if os.name == 'nt':
        link = ['-Wl,/SAFESEH:NO', '-Wl,/DYNAMICBASE:NO', '-Wl,/FIXED']
    else:
        flags += ['-D_DEFAULT_SOURCE']
        link = ['-no-pie', '-Wl,-z,noexecstack', '-Wl,-Ttext-segment=0x400000',
                '-Wl,--section-start=.heap_floor=0x10000000']
    exe = folder / ('contract.exe' if os.name == 'nt' else 'contract')
    subprocess.run([*diffcheck.compiler(), *flags, *map(str, sources), *link, '-o', str(exe)], check=True)
    original_out = run.OUT
    try:
        run.OUT = folder
        policy = run.write_policy('all')
    finally:
        run.OUT = original_out
    generated = subprocess.run([str(exe), 'policy-file', str(policy)], capture_output=True, text=True, timeout=15)
    assert generated.returncode == 0, (generated.stdout, generated.stderr)
    assert 'Actual generated policy has all four audited contracts' in generated.stdout
    positives = ['valid', 'call-in-valid', 'object-host', 'maximum', 'call-in-maximum']
    negatives = ['negative', 'negative-high', 'high', 'host-target', 'stack-b', 'stack-target',
                 'stack-adjustment', 'array-tail', 'setter-tail', 'return-category', 'return-unused',
                 'object-null', 'object-different-ds', 'object-inaccessible',
                 'unavailable-owner', 'detached-parent', 'call-in-high', 'call-in-stack', 'maximum-stack-tail']
    malformed = ['missing', 'duplicate', 'stream', 'parent', 'kind', 'function', 'offset', 'count',
                 'padding', 'reorder', 'truncated', 'unexpected']
    policies = ['valid', 'legacy', 'word-count', 'zero-words', 'pointer-mask', 'too-many',
                'overlay', 'duplicate', 'invalid-number']
    for case in (positives + negatives + ['record-' + name for name in malformed]
                 + ['policy-' + name for name in policies]):
        result = subprocess.run([str(exe), case, str(folder / 'trace.bin')], capture_output=True, text=True, timeout=15)
        expected = 7 if case in negatives else 0
        assert result.returncode == expected, (case, result.returncode, result.stdout, result.stderr)
        if case in negatives:
            assert 'native: ARGUMENT audited' in result.stderr, (case, result.stderr)
        elif case.startswith('record-'):
            assert 'Rejected malformed argument attachment' in result.stdout
        elif case.startswith('policy-'):
            assert 'Policy contract checked' in result.stdout
        else:
            assert 'Audited arguments agree' in result.stdout
    print(f'Audited call-in/out register and stack words: {len(positives)} valid, '
          f'{len(negatives)} incorrect calls, {len(malformed)} malformed traces and {len(policies)} policies checked')


if __name__ == '__main__':
    tests = unittest.main(exit=False)
    if not tests.result.wasSuccessful():
        raise SystemExit(1)
    fixture()
