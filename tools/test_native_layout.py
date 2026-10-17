"""Exercise ROM-observable local layouts using the actual copied functions."""
from __future__ import annotations

import subprocess

import common as C
import diffcheck
import native
import native_layout


def main() -> None:
    folder = C.BUILD / "native-layout-check"
    folder.mkdir(parents=True, exist_ok=True)
    objects = []
    for relative in sorted(native_layout.paths()):
        source = C.SRC / relative
        text = source.read_bytes().decode("utf-8")
        result = native_layout.translate(relative, text)
        assert result is not None
        try:
            native_layout.translate(relative, text + "\n")
        except ValueError:
            pass
        else:
            raise AssertionError("changed sources must require a new audit")
        copied = folder / source.name
        copied.write_bytes(result.encode())
        obj = copied.with_suffix(".o")
        subprocess.run([*native.compiler(), *native.flags_for(source), "-iquote", str(source.parent),
                        "-c", str(copied), "-o", str(obj)], check=True)
        objects.append(str(obj))
    # Use the game's actual vector consumer and fishing/tool payload writers.
    for relative in ("main/func_0200322c.c", "ov003/func_ov003_02215f4c.c",
                     "ov003/func_ov003_02211da0.c", "ov003/func_ov003_022119d8.c"):
        source = C.SRC / relative
        obj = folder / (source.stem + ".o")
        subprocess.run([*native.compiler(), *native.flags_for(source),
                        "-c", str(source), "-o", str(obj)], check=True)
        objects.append(str(obj))
    source = C.ROOT / "tests/native/stack_layout.c"
    exe = folder / ("layout.exe" if native.WINDOWS else "layout")
    flags = [str(C.ROOT / 'runtime/native_rt.c'), *(["-Wl,/SAFESEH:NO"] if native.WINDOWS else ["-no-pie"])]
    subprocess.run([*diffcheck.compiler(), str(source), *objects, *flags, "-o", str(exe)], check=True)
    subprocess.run([str(exe)], check=True)
    print(f"{len(native_layout.paths())} copied game functions pass runtime fixtures; source audit guards pass")


if __name__ == "__main__":
    main()
