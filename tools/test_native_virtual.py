"""Execute the actual shop copy through the production virtual dispatch thunk."""
from __future__ import annotations

import subprocess

import common as C
import diffcheck
import native
import native_virtual


def main() -> None:
    relative = "ov100/func_ov100_0229e3b0.cpp"
    source = C.SRC / relative
    text = source.read_bytes().decode()
    assert native_virtual.translate(relative, text) is not None
    assert native_virtual.translate("unknown.cpp", text) is None
    try:
        native_virtual.translate(relative, text + "\n")
    except ValueError:
        pass
    else:
        raise AssertionError("changed sources must require a new ROM audit")
    _, obj, error = native.compile_one(source)
    assert obj is not None, error
    _, undefined = native.nm(obj)
    calls = native.virtual_calls([(source, obj)], undefined)
    assert calls == {native.PREFIX + "_ZN4CSub2f3Ev": (12, 0)}, calls
    folder = C.BUILD / "native-virtual-check"
    folder.mkdir(parents=True, exist_ok=True)
    asm = folder / "dispatch.s"
    asm.write_text("\n".join(["\t.text", *native.virtual_thunks(calls), ""]), newline="\n")
    thunk = folder / "dispatch.o"
    subprocess.run([*native.compiler(), "-c", str(asm), "-o", str(thunk)], check=True)
    fixture = C.ROOT / "tests/native/virtual_dispatch.c"
    exe = folder / ("virtual.exe" if native.WINDOWS else "virtual")
    flags = ["-Wl,/SAFESEH:NO"] if native.WINDOWS else ["-no-pie"]
    subprocess.run([*diffcheck.compiler(), "-std=c11", str(fixture), str(obj), str(thunk),
                    *flags, "-o", str(exe)], check=True)
    subprocess.run([str(exe)], check=True)
    print("Actual shop copy passes call order, adjusted this, dynamic slot 3 and source audit guard checks")


if __name__ == "__main__":
    main()
