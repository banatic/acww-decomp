# CI

Two workflows run on every push to `main`:

- `lint.yml` needs nothing private and runs on any fork.
- `build.yml` extracts, verifies, relinks and uploads `build/adm-kr/report.json` as the artifact
  `adm-kr_report`, which [decomp.dev](https://decomp.dev) reads to draw the progress map and
  badges. It runs inside a **private** container image that holds the base ROM and the
  compiler, so neither ever appears in the repository or in a public image.

## The build image

Build it on your own machine and push it to the GitHub Container Registry of the account that
owns the repository. Keep the package private.

```dockerfile
FROM ubuntu:24.04
RUN apt-get update && apt-get install -y --no-install-recommends python3 ca-certificates \
    && rm -rf /var/lib/apt/lists/*
# wibo runs the Windows compiler on Linux: https://github.com/decompals/wibo/releases
COPY wibo /usr/local/bin/wibo
COPY mwccarm/ /mwccarm/
COPY baserom.nds /extract/adm-kr.nds
```

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

## decomp.dev

Once a `build` run on `main` has uploaded `adm-kr_report`, sign in at decomp.dev with GitHub and
add the repository. The progress map can then be embedded with

```markdown
[![Progress](https://decomp.dev/<owner>/<repo>.svg?w=512&h=256)](https://decomp.dev/<owner>/<repo>)
```
