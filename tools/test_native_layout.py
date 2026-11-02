"""Exercise ROM-observable local layouts using the actual copied functions."""
from __future__ import annotations

import subprocess

import common as C
import diffcheck
import native
import native_layout

# Request builders tests/native/request_layout.c exercises, apart from the other copies.
REQUESTS = {
    "main/func_02009a44", "main/func_0200a6a0", "main/func_0200acd4", "main/func_0200ad24",
    "main/func_0200b7e8", "main/func_0200c3b0", "main/func_0200cc00", "main/func_0200dbb4",
    "ov003/func_ov003_0220fb30", "ov003/func_ov003_0220fda0", "ov003/func_ov003_02212830",
    "ov003/func_ov003_02212c10", "ov003/func_ov003_02215624", "ov003/func_ov003_02216410",
    "ov003/func_ov003_02216698", "ov003/func_ov003_02216ab8", "ov003/func_ov003_022171ec",
    "ov003/func_ov003_02217838", "ov003/func_ov003_022186cc", "ov003/func_ov003_022188d0",
    "ov004/func_ov004_02228628", "ov004/func_ov004_0222ac24",
    "main/func_0200a448", "main/func_0200b83c", "main/func_0200bdbc",
    "main/func_0200c904", "main/func_0200d1a0", "main/func_0200d4e8",
    "ov003/func_ov003_0220f768", "ov003/func_ov003_022100c4", "ov003/func_ov003_022122ac",
    "ov003/func_ov003_02218ec4", "ov003/func_ov003_02218fac", "ov004/func_ov004_02228100",
    "ov004/func_ov004_02229010", "ov004/func_ov004_02229258", "ov004/func_ov004_022294a0",
    "ov004/func_ov004_02229774", "ov004/func_ov004_0222a494", "ov004/func_ov004_0222af6c",
}


def main() -> None:
    folder = C.BUILD / "native-layout-check"
    folder.mkdir(parents=True, exist_ok=True)
    objects = []
    requests = []
    for relative in sorted(native_layout.paths()):
        source = C.key_path(relative)
        text = source.read_bytes().decode("utf-8")
        result = native_layout.translate(relative, text)
        assert result is not None
        try:
            native_layout.translate(relative, C.function_changed(text, relative.partition("/")[2]))
        except ValueError:
            pass
        else:
            raise AssertionError("changed sources must require a new audit")
        copied = folder / source.name
        copied.write_bytes(result.encode())
        obj = copied.with_suffix(".o")
        subprocess.run([*native.compiler(), *native.flags_for(source), "-iquote", str(source.parent),
                        "-c", str(copied), "-o", str(obj)], check=True)
        (requests if relative in REQUESTS else objects).append(str(obj))
    assert len(requests) == len(REQUESTS)
    # Use the game's actual vector consumer and fishing/tool payload writers.
    for relative in ("main/func_0200322c", "ov003/func_ov003_02215f4c",
                     "ov003/func_ov003_02211da0", "ov003/func_ov003_022119d8"):
        source = C.key_path(relative)
        obj = folder / (source.stem + ".o")
        subprocess.run([*native.compiler(), *native.flags_for(source),
                        "-c", str(source), "-o", str(obj)], check=True)
        objects.append(str(obj))
    source = C.ROOT / "tests/native/stack_layout.c"
    exe = folder / ("layout.exe" if native.WINDOWS else "layout")
    flags = [str(C.ROOT / 'runtime/native_rt.c'), *(["-Wl,/SAFESEH:NO"] if native.WINDOWS else ["-no-pie"])]
    subprocess.run([*diffcheck.compiler(), str(source), *objects, *flags, "-o", str(exe)], check=True)
    subprocess.run([str(exe)], check=True)
    exe = folder / ("requests.exe" if native.WINDOWS else "requests")
    subprocess.run([*diffcheck.compiler(), str(C.ROOT / "tests/native/request_layout.c"), *requests, *flags,
                    "-o", str(exe)], check=True)
    subprocess.run([str(exe)], check=True)
    print(f"{len(native_layout.paths())} copied game functions pass runtime fixtures; source audit guards pass")


if __name__ == "__main__":
    main()
