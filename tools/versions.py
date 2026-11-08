"""The ROM version the tools work on (docs/versions.md).

Every tool works on one version of the game at a time: its configuration (config/<version>/),
its ROM (extract/<version>.nds, checked against <version>.sha1), its build (build/<version>/)
and its recordings. The version is chosen by

    python tools/<tool>.py --version adm-kr ...     # on any tool's command line, or
    ACWW_VERSION=adm-kr python tools/<tool>.py ...  # in the environment

and is adm-kr (the Korean release) when neither names one. The `--version` option is taken off
the command line when this module is first imported, before the tool reads its own options, and
the choice is put in ACWW_VERSION so that the tools a tool starts work on the same version.

The paths below are the only place the tools spell a version's name; tools/common.py repeats
them for the tools that import it.
"""

from __future__ import annotations

import dataclasses
import os
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
DEFAULT = "adm-kr"


@dataclasses.dataclass(frozen=True)
class Version:
    name: str          # config/<name>/, build/<name>/, <name>.sha1
    game_code: str     # the ROM header's game code (0x0c)
    revision: int      # the ROM header's revision (0x1e)
    region: str        # what tools/setup.py calls the release
    adjective: str     # "the Korean one"
    used_size: int     # the header's used ROM size (0x80): a dump trimmed to it is padded back
    trimmed_sha1: str  # the SHA-1 of the first used_size bytes


# The versions the project knows. A version is added here with its config/<name>/ and
# <name>.sha1 (docs/versions.md, "Adding a version").
KNOWN = {
    "adm-kr": Version("adm-kr", "ADMK", 0, "Korea", "Korean", 0x1F533C4,
                      "f987baf1db78b9b8c92a98877c62df71f9d049d3"),
}

NAME_FORMAT = re.compile(r"^[a-z0-9]+(?:-[a-z0-9]+)*$")


def take_option(argv: list[str]) -> str | None:
    """The value of `--version X` or `--version=X` in argv (before a `--`), removed from argv."""
    for i, arg in enumerate(argv[1:], 1):
        if arg == "--":
            return None
        if arg.startswith("--version="):
            del argv[i]
            return arg.split("=", 1)[1]
        if arg == "--version":
            if i + 1 >= len(argv):
                raise SystemExit("--version needs a version's name (e.g. --version adm-kr)")
            value = argv[i + 1]
            del argv[i:i + 2]
            return value
    return None


def configured() -> list[str]:
    """Every version with a config/<version>/, in name order."""
    return sorted(p.name for p in (ROOT / "config").iterdir() if (p / "arm9").is_dir())


def resolve(argv: list[str] | None = None) -> str:
    """The version named on the command line, else by ACWW_VERSION, else DEFAULT; checked, and
    put in ACWW_VERSION for the processes a tool starts."""
    name = take_option(sys.argv if argv is None else argv) or os.environ.get("ACWW_VERSION") or DEFAULT
    if not NAME_FORMAT.match(name):
        raise SystemExit(f"version {name!r}: not a version's name (lower case, e.g. adm-kr)")
    if not (ROOT / "config" / name).is_dir():
        raise SystemExit(f"version {name}: no config/{name}/ (the versions configured: {', '.join(configured())})")
    os.environ["ACWW_VERSION"] = name
    return name


NAME = resolve()
VERSION = KNOWN.get(NAME)
CONFIG_ROOT = ROOT / "config" / NAME
CONFIG = CONFIG_ROOT / "arm9"
BUILD = ROOT / "build" / NAME
EXTRACT = ROOT / "extract"
ROM = EXTRACT / f"{NAME}.nds"        # the checked copy of the ROM
ROM_TREE = EXTRACT / NAME            # ds-decomp's extraction of it (tools/link.py)
SHA1_FILE = ROOT / f"{NAME}.sha1"
# The input recordings, their expected frames and the lists the scenes record. The first
# version's stay where they were before there were versions; another version's are in a
# directory of its own name.
RECORDINGS = ROOT / "runtime" / "recordings" if NAME == DEFAULT else ROOT / "runtime" / "recordings" / NAME


def info() -> Version:
    """The current version's ROM facts; a version without them in KNOWN cannot be set up."""
    if VERSION is None:
        raise SystemExit(f"version {NAME}: not in tools/versions.py's KNOWN (its game code, size, ...)")
    return VERSION


def rel(path: pathlib.Path) -> str:
    """A path as the tools print and pass it: from the root, with forward slashes."""
    return path.relative_to(ROOT).as_posix()
