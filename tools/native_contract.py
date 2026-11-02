"""Source/ROM-audited ARM call words for shared member-pointer boundaries.

The encoding is an argument count in bits0..7 and pointer roles in bits8..23.
Zero means the legacy, untyped policy. Every non-pointer word compares exactly;
in particular, a high or negative member adjustment is never a host pointer.
"""
from __future__ import annotations

from dataclasses import dataclass
import hashlib
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402


@dataclass(frozen=True)
class Contract:
    module: str
    address: int
    size: int
    source: str  # the function's key (common.function_key)
    source_sha256: str  # its text's (common.function_sha256)
    rom_sha256: str
    roles: tuple[str, ...]

    @property
    def encoding(self) -> int:
        assert 0 < len(self.roles) <= 16
        mask = sum(1 << i for i, role in enumerate(self.roles) if role.endswith('_pointer'))
        return len(self.roles) | mask << 8


CONTRACTS = (
    Contract('itcm', 0x01ffd44c, 0xc0, 'itcm/func_01ffd44c',
             '805bc8c903f917a98768f71805061e60b23af7416f1e03f92e5a935949c514e0',
             '97be9e9481e520004c748417f3408881cf9e8cffe7d0df642eda1d75c3469269',
             ('object_pointer', 'a_function', 'a_adjustment', 'b_function',
              'b_adjustment', 'c_function', 'c_adjustment')),
    Contract('main', 0x02034e28, 0x50, 'main/func_02034e28',
             'a6d4c91228476fa40a621d9e2e79976bceb3d9d7539a9a3c3bd63132807f4bee',
             '28b07fefedbd4186d1606348bceeb40e677c327f2a7a06721a23e0f3edf2e2ca',
             ('object_pointer', 'function', 'adjustment')),
    Contract('main', 0x0202dbf0, 0x14, 'main/func_0202dbf0',
             'afcc88a28acb80a0f11ba8235676716d2d8b01f15696f11704e9be014a2d1526',
             '7219f29b7a87413b7b19d26c5e0b1cee9a290953f4dd90a8824624da049146a6',
             ('object_pointer', 'pair_first', 'pair_second')),
    Contract('main', 0x0207fc7c, 0x4c, 'main/func_0207fc7c',
             'b988120e6c4aae4dedd1dd7b79d0e4b89f8b44a6b571ffe43bb5b4539947fbe3',
             '3c0e3bc974cec8a19644e077343ffc2b3483c95dc794b295ba289a668a2c7942',
             ('output_pointer', 'unused', 'category')),
)


def validate(contract: Contract, source: bytes, code: bytes) -> None:
    if C.pinned_sha256(contract.source, source.decode()) != contract.source_sha256:
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
        defined = C.function_source(contract.source)
        if defined is None:
            raise ValueError(f'Native call-contract source missing: {contract.source}')
        validate(contract, (root / defined.path.relative_to(C.ROOT)).read_bytes(), code)
        result[(contract.module, contract.address)] = contract.encoding
    return result
