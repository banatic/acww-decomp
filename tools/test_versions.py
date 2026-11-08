"""tools/versions.py: how a tool's command line and ACWW_VERSION name the version, and the
default's paths (the ones every tool used before there were versions)."""
from __future__ import annotations

import os
import pathlib
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT


def option(argv: list[str]) -> tuple[str | None, list[str]]:
    argv = list(argv)
    return versions.take_option(argv), argv


def main() -> int:
    problems = []
    checks = [0]

    def expect(what: str, got, want) -> None:
        checks[0] += 1
        if got != want:
            problems.append(f"{what}: {got!r}, expected {want!r}")

    expect("no option", option(["tool", "a", "-j", "4"]), (None, ["tool", "a", "-j", "4"]))
    expect("--version X", option(["tool", "a", "--version", "adm-xx", "b"]), ("adm-xx", ["tool", "a", "b"]))
    expect("--version=X", option(["tool", "--version=adm-xx", "b"]), ("adm-xx", ["tool", "b"]))
    expect("after --", option(["tool", "--", "--version", "adm-xx"]), (None, ["tool", "--", "--version", "adm-xx"]))
    expect("the tool's name", option(["--version"]), (None, ["--version"]))

    if os.environ.get("ACWW_VERSION", versions.DEFAULT) == versions.DEFAULT:
        expect("default config", versions.CONFIG, ROOT / "config" / "adm-kr" / "arm9")
        expect("default build", versions.BUILD, ROOT / "build" / "adm-kr")
        expect("default ROM", versions.ROM, ROOT / "extract" / "adm-kr.nds")
        expect("default SHA-1 file", versions.SHA1_FILE, ROOT / "adm-kr.sha1")
        expect("default recordings", versions.RECORDINGS, ROOT / "runtime" / "recordings")

    # a version without a configuration is refused, and the choice reaches the tools started
    code = "import sys; sys.path.insert(0, 'tools'); import versions, os; print(os.environ['ACWW_VERSION'])"
    env = {k: v for k, v in os.environ.items() if k != "ACWW_VERSION"}
    p = subprocess.run([sys.executable, "-c", code, "--version", "no-such-version"], cwd=ROOT, env=env,
                       capture_output=True, text=True)
    expect("unknown version refused", (p.returncode != 0, "no config/no-such-version/" in p.stderr), (True, True))
    p = subprocess.run([sys.executable, "-c", code, "--version", versions.DEFAULT], cwd=ROOT, env=env,
                       capture_output=True, text=True)
    expect("ACWW_VERSION set for children", p.stdout.strip(), versions.DEFAULT)

    for line in problems:
        print(line)
    print(f"{checks[0] - len(problems)} of {checks[0]} version checks pass")
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
