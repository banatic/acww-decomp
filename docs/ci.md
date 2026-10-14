# CI

Two workflows run on every push to `main`:

- `lint.yml` needs nothing private and runs on any fork.
- `build.yml` extracts, verifies, relinks and uploads `build/adm-kr/report.json` (objdiff
  report format) as the artifact `adm-kr_report`. It runs inside a **private** container image
  that holds the base ROM and the compiler, so neither ever appears in the repository or in a
  public image.

## The build image

Build it on your own machine and push it to the GitHub Container Registry of the account that
owns the repository. Keep the package private.

```dockerfile
FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN dpkg --add-architecture i386 && apt-get update \
    && apt-get install -y --no-install-recommends python3 git ca-certificates wine wine32:i386 \
    && rm -rf /var/lib/apt/lists/*
# wibo runs the Windows compiler on Linux: https://github.com/decompals/wibo/releases
COPY wibo /usr/local/bin/wibo
RUN chmod +x /usr/local/bin/wibo
COPY mwccarm/ /mwccarm/
COPY baserom.nds /extract/adm-kr.nds
ENV WINEDEBUG=-all
RUN wine /mwccarm/1.2/base/mwccarm.exe -help >/dev/null 2>&1 || true
```

The workflow compiles with wibo, which is fast, and recompiles any function that does not
match with Wine (`MWCC_FALLBACK`): on a few functions with large `switch` statements wibo's
output differs from the Windows compiler's, and Wine's does not.

with this layout next to the Dockerfile:

```
wibo                 the wibo release binary (chmod +x)
mwccarm/1.2/base/    compiler drops, as in INSTALL.md, plus license.dat
mwccarm/1.2/sp2/
mwccarm/1.2/sp2p3/
baserom.nds          your dump, SHA-1 as in adm-kr.sha1
```

```sh
docker build -t ghcr.io/<owner>/acww-build:main .
echo <token with write:packages> | docker login ghcr.io -u <owner> --password-stdin
docker push ghcr.io/<owner>/acww-build:main
```

Then, on GitHub, open the package's settings, keep its visibility private, and under
"Manage Actions access" give this repository read access. The workflow logs in with its own
`GITHUB_TOKEN`; no other secret is needed.

Workflows triggered from forks cannot read the package, so `build.yml` fails on pull requests
from forks; `lint.yml` still runs there.

