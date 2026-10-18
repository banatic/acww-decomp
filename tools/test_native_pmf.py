"""Check the verified transformation and its 32-bit PC calling boundary.

Run with the same CC/NATIVE_CC environment as the runtime on each host.
Does not build or run a game gate.
"""
from __future__ import annotations

import subprocess

import common as C
import diffcheck
import native
import native_pmf


def check_rom_subset() -> None:
    """Guard the small single-dispatch subset used by the manifest audit.

    These opcode counts are a regression guard, not a dataflow proof. The source
    digest, copied layout checks and full game gates remain necessary.
    """
    modules = C.modules()
    images = {}
    for relative in sorted(native_pmf.READ_ONLY):
        source = C.parse_source(C.SRC / relative)
        assert source is not None and source.size <= 0x80, relative
        if source.module not in images:
            images[source.module] = C.module_image(source.module)
        offset = source.address - modules[source.module]['base']
        code = images[source.module][offset:offset + source.size]
        assert len(code) == source.size, relative
        width = 2 if source.thumb else 4
        words = [int.from_bytes(code[i:i + width], 'little')
                 for i in range(0, len(code), width)]
        if source.thumb:
            shifts = sum((word & 0xffc0) == 0x1040 for word in words)
            calls = sum((word & 0xff87) == 0x4780 for word in words)
        else:
            shifts = sum((word & 0x02000ff0) == 0xc0 for word in words)
            calls = sum((word & 0x0ffffff0) == 0x012fff30 for word in words)
        assert (shifts, calls) == (1, 1), (relative, shifts, calls)


def main() -> None:
    check_rom_subset()
    for relative in native_pmf.paths():
        source = (C.SRC / relative).read_text()
        result = native_pmf.translate(relative, source, {})
        assert result is not None
        if relative in native_pmf.VERIFIED:
            _, before, after, _ = native_pmf.VERIFIED[relative]
            assert before not in result and after in result
        try:
            native_pmf.translate(relative, source + "\n", {})
        except ValueError:
            pass
        else:
            raise AssertionError("changed sources must require a new audit")
    assert native_pmf.translate("unknown.cpp", "unchanged") is None
    folder = C.BUILD / "native-member-check"
    folder.mkdir(parents=True, exist_ok=True)
    obj = folder / "member.o"
    source = C.ROOT / "tests/native/member_pointer.cpp"
    subprocess.run([*native.compiler(), *native.flags_for(source), "-I" + str(C.ROOT / "runtime"),
                    "-c", str(source), "-o", str(obj)], check=True)
    exe = folder / ("member.exe" if native.WINDOWS else "member")
    flags = [str(C.ROOT / 'runtime/native_rt.c'), *(["-Wl,/SAFESEH:NO"] if native.WINDOWS else ["-no-pie"])]
    subprocess.run([*diffcheck.compiler(), str(obj), *flags, "-o", str(exe)], check=True)
    subprocess.run([str(exe)], check=True)
    for relative in sorted(native_pmf.paths()):
        # Compile the exact audited game copy independently of the game's object
        # cache, so this check can run while an existing scene gate is active.
        source = C.SRC / relative
        copied = folder / source.name
        headers = {}
        copied.write_text(native_pmf.translate(relative, source.read_text(), headers), newline='\n')
        header_root = folder / 'headers' / source.relative_to(C.SRC).with_suffix('')
        for name, text in headers.items():
            destination = header_root / name
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_text(text, newline='\n')
        header_flags = ['-I' + str(header_root)] if headers else []
        subprocess.run([*native.compiler(), *header_flags, *native.flags_for(source),
                        "-I" + str(C.ROOT / "runtime"), "-iquote", str(source.parent),
                        "-c", str(copied), "-o", str(copied.with_suffix(".o"))], check=True)
    source = C.ROOT / "tests/native/member_null.cpp"
    obj = folder / "member-null.o"
    subprocess.run([*native.compiler(), *native.flags_for(source),
                    "-c", str(source), "-o", str(obj)], check=True)
    null_copies = [folder / ("func_" + name + ".o") for name in
                   ("ov046_02261590", "ov051_02260f94", "ov070_0227986c",
                    "ov073_02278f98", "ov076_02278fa8")]
    exe = folder / ("member-null.exe" if native.WINDOWS else "member-null")
    subprocess.run([*diffcheck.compiler(), str(obj), *map(str, null_copies),
                    *flags, "-o", str(exe)], check=True)
    subprocess.run([str(exe)], check=True)
    print(f"{len(native_pmf.paths())} copies compile; layout, direct/virtual calls, signed adjustments, null, Thumb bits and audit guards pass")


if __name__ == "__main__":
    main()
