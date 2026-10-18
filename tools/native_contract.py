"""Source/ROM-audited ARM call words for shared member-pointer boundaries.

The encoding is an argument count in bits0..7 and pointer roles in bits8..23.
Zero means the legacy, untyped policy. Every non-pointer word compares exactly;
in particular, a high or negative member adjustment is never a host pointer.
"""
from __future__ import annotations

from dataclasses import dataclass
import hashlib
from pathlib import Path


@dataclass(frozen=True)
class Contract:
    module: str
    address: int
    size: int
    source: str
    source_sha256: str
    rom_sha256: str
    roles: tuple[str, ...]

    @property
    def encoding(self) -> int:
        assert 0 < len(self.roles) <= 16
        mask = sum(1 << i for i, role in enumerate(self.roles) if role.endswith('_pointer'))
        return len(self.roles) | mask << 8


CONTRACTS = (
    Contract('itcm', 0x01ffd44c, 0xc0, 'itcm/func_01ffd44c.cpp',
             '5496584b555608c38dbfa20773f6cc16d91fd94bef8cce6115f02ca548facbd3',
             '97be9e9481e520004c748417f3408881cf9e8cffe7d0df642eda1d75c3469269',
             ('object_pointer', 'a_function', 'a_adjustment', 'b_function',
              'b_adjustment', 'c_function', 'c_adjustment')),
    Contract('main', 0x02034e28, 0x50, 'main/func_02034e28.cpp',
             'fa0007464683225f8b51dc817ddc764490e8f67e1f42e2c7bc15186d071860da',
             '28b07fefedbd4186d1606348bceeb40e677c327f2a7a06721a23e0f3edf2e2ca',
             ('object_pointer', 'function', 'adjustment')),
    Contract('main', 0x0202dbf0, 0x14, 'main/func_0202dbf0.c',
             '187890dfd518c0ef87cd9399a90b1bee60d87af5dcae368edea74ae793f5daeb',
             '7219f29b7a87413b7b19d26c5e0b1cee9a290953f4dd90a8824624da049146a6',
             ('object_pointer', 'pair_first', 'pair_second')),
    Contract('main', 0x0207fc7c, 0x4c, 'main/func_0207fc7c.c',
             '1a8d5b9025351de2c263105fae0a7618ff611d30e4cb76dc0631c2f413661b39',
             '3c0e3bc974cec8a19644e077343ffc2b3483c95dc794b295ba289a668a2c7942',
             ('output_pointer', 'unused', 'category')),
)


def validate(contract: Contract, source: bytes, code: bytes) -> None:
    if hashlib.sha256(source).hexdigest() != contract.source_sha256:
        raise ValueError(f'Native call-contract source changed: {contract.source}')
    if len(code) != contract.size or hashlib.sha256(code).hexdigest() != contract.rom_sha256:
        raise ValueError(f'Native call-contract ROM changed: {contract.module}:{contract.address:08x}')


def audited(root: Path, modules: dict, image) -> dict[tuple[str, int], int]:
    """Validate complete original bodies before adding metadata to a policy."""
    result = {}
    images = {}
    for contract in CONTRACTS:
        if contract.module not in images:
            images[contract.module] = image(contract.module)
        offset = contract.address - modules[contract.module]['base']
        code = images[contract.module][offset:offset + contract.size]
        validate(contract, (root / 'src' / contract.source).read_bytes(), code)
        result[(contract.module, contract.address)] = contract.encoding
    return result
