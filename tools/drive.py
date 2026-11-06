"""Play the game a few frames at a time from the command line, to find and record new scenes
(runtime/drive.h). A run is started in the background, in the interpreter only, and stays
there between commands:

    python tools/drive.py start town --save rod                 # a derived save (tools/scenes.py SAVES)
    python tools/drive.py start town --save PATH --rtc "2026-09-12 20:00:00"
    python tools/drive.py start town --save rod --prefix fish-cast --until 2700
                                         # play a scene's recording up to frame 2700 first
    python tools/drive.py town run 60                  # 60 frames, input unchanged
    python tools/drive.py town run 30 A                # hold A for 30 frames (then still held)
    python tools/drive.py town run 8 - 120,80          # touch the lower screen at 120,80
    python tools/drive.py town press A                 # A for 2 frames, then 20 frames released
    python tools/drive.py town png look.png            # the screens now
    python tools/drive.py town gx3d frame.gx3d         # the last 3D frame and its input (runtime/gpu3d.h)
    python tools/drive.py town peek 021f3a10 16
    python tools/drive.py town snap                    # keep this moment; prints its id
    python tools/drive.py town back ID                 # return to it (as often as wanted)
    python tools/drive.py town new                     # Clean functions entered that no scene enters
    python tools/drive.py town log scene.txt           # the input so far, as a recording
    python tools/drive.py town stop

Two consoles linked by their wireless (docs/multi-console.md): `start` with --peer-save (and
--peer-prefix, a recording for console 1 to play first) runs both, joined as tools/run.py
--peer-save joins them. Each `run` runs both consoles; its input is console 0's, and `@1 KEYS
[PEN]` after it gives console 1's (without it, console 1 goes on with its recording or its input
unchanged). Any other command is console 0's, or console 1's after a leading `@1`. --peer-save
and --peer-prefix again add a third console (`@2`), and a fourth:

    python tools/drive.py start link --save seed --prefix gate-visit-host --peer-save other-town \
        --peer-prefix gate-visit-guest --until 12000
    python tools/drive.py link run 30 - - @1 UP     # console 1 walks up, console 0 waits
    python tools/drive.py link @1 png guest.png     # console 1's screens
    python tools/drive.py link @1 log guest.txt     # console 1's input so far

`new` compares with the lists of tools/coverage.py (build/adm-kr/scenes/*/functions-seen.txt, or
--lists DIR at start). On Windows `snap` keeps the input so far and `back` plays it again
from the start (seconds); on Linux the run is forked and `back` is immediate, so on Windows it
pays to drive from WSL (`wsl -e bash -c 'cd /mnt/c/...; python3 tools/drive.py ...'`, with the
Linux compiler set up as for the Linux build). A recording from `log` is a
scene's recording as is: add it with its frame count to tools/scenes.py and run it there, which
checks Native and Clean against the Reference.
"""
from __future__ import annotations

import argparse
import json
import os
import pathlib
import re
import socket
import socketserver
import subprocess
import sys
import threading
import time

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

HOME = C.BUILD / "drive"
AT = re.compile(r"@[0-9]")  # a console after the first: `@1`, `@2`


def port_file(name: str) -> pathlib.Path:
    return HOME / f"{name}.json"


# ------------------------------------------------------------------------------ the server

class Runtime:
    """The run (one console, or two linked by their wireless), and the copies `snap` keeps."""

    def __init__(self, base_envs: list[dict], prefixes: list[pathlib.Path | None], until: int,
                 workdir: pathlib.Path):
        import run  # noqa: PLC0415
        self.run = run
        self.manifest, self.table = run.generate()
        self.exe = run.build(native=False)
        self.base_envs = base_envs
        self.workdir = workdir
        self.procs: list[subprocess.Popen] = []
        self.forks = None  # unknown until the first snap
        self.snaps: dict[str, tuple[int, list[pathlib.Path]]] = {}
        self.copies: dict[str, list[str]] = {}  # forked: a snap's copy of each console
        self.output = open(workdir / "run.log", "a", encoding="utf-8", errors="replace")
        self.start(prefixes, 0)
        if any(p is not None for p in prefixes) and until:
            self.command(f"run {until}")

    def start(self, recordings: list[pathlib.Path | None], frame: int) -> str:
        for p in self.procs:
            p.kill()
            p.wait()
        self.procs = []
        linked = len(self.base_envs) >= 2
        fds, links = self.run.link_pipes(len(self.base_envs)) if linked else ([], [])  # as tools/run.py run_linked
        try:
            for i, base in enumerate(self.base_envs):
                env = dict(base)
                if recordings[i] is not None:
                    env["RUN_INPUT"] = str(recordings[i])
                else:
                    env.pop("RUN_INPUT", None)
                kwargs: dict = {}
                if linked:
                    env["RUN_LINK"], kwargs = links[i]
                    env["RUN_WIRELESS"] = "1"
                self.procs.append(subprocess.Popen(
                    [str(self.exe), str(self.run.ROM), str(self.manifest), str(self.table), "0"], cwd=C.ROOT,
                    env=env, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=self.output, text=True,
                    bufsize=1, **kwargs))
        finally:
            for fd in fds:  # each process holds its own ends
                os.close(fd)
        answers = [self.read(i) for i in range(len(self.procs))]
        if frame:
            return self.command(f"run {frame}")
        return answers[0]

    def read(self, i: int = 0) -> str:
        stdout = self.procs[i].stdout
        assert stdout is not None
        for line in stdout:
            if line.startswith("@"):
                return line.strip()
            self.output.write(line)
        self.output.flush()
        return "@err the run ended (see run.log)"

    def send(self, i: int, line: str) -> None:
        stdin = self.procs[i].stdin
        assert stdin is not None
        stdin.write(line + "\n")
        stdin.flush()

    def everyone(self, lines: list[str]) -> str:
        """One command to each console at once (a linked console waits for the other's frame),
        then their answers: the first that is not @ok, else console 0's."""
        for i, line in enumerate(lines):
            self.send(i, line)
        answers = [self.read(i) for i in range(len(lines))]
        bad = [a for a in answers if not a.startswith("@ok")]
        return bad[0] if bad else answers[0]

    def command(self, line: str) -> str:
        """A command: `run` goes to every console (console k's input after `@k`); any other to
        console 0, or to console k after a leading `@k`."""
        if not self.forks and any(p.poll() is not None for p in self.procs):
            return "@err the run ended (see run.log)"
        words = line.split()
        target = 0
        if words and AT.fullmatch(words[0]):
            target, words = int(words[0][1:]), words[1:]
        if words and words[0] == "run" and len(self.procs) >= 2:
            count = words[1] if len(words) > 1 else "1"
            lines = [["run", count] for _ in self.procs]
            k, part = 0, []
            for w in words + ["@end"]:
                if AT.fullmatch(w) or w == "@end":
                    if k < len(lines):
                        lines[k] = part if k == 0 else ["run", count, *part]
                    k, part = (int(w[1:]) if w != "@end" else 0), []
                else:
                    part.append(w)
            return self.everyone([" ".join(line) for line in lines])
        if target >= len(self.procs):
            return f"@err {len(self.procs)} console(s) only"
        self.send(target, " ".join(words))
        return self.read(target)

    def frame(self) -> int:
        return int(self.command("frame").split()[-1])

    def snap(self) -> str:
        if self.forks is not False:
            if len(self.procs) == 1:
                answer = self.command("snap")
                if answer.startswith("@ok"):
                    self.forks = True
                    return answer
            else:
                for i in range(len(self.procs)):
                    self.send(i, "snap")
                answers = [self.read(i) for i in range(len(self.procs))]
                if all(a.startswith("@ok") for a in answers):
                    self.forks = True
                    sid = str(len(self.copies) + 1)
                    self.copies[sid] = [a.split()[1] for a in answers]
                    return f"@ok {sid}"
            self.forks = False
        sid = str(len(self.snaps) + 1)
        logs = [self.workdir / (f"snap-{sid}.txt" if i == 0 else f"snap-{sid}-{i}.txt") for i in range(len(self.procs))]
        for i, log in enumerate(logs):
            self.command(f"{f'@{i} ' if i else ''}log {log}")
        self.snaps[sid] = (self.frame(), logs)
        return f"@ok {sid}"

    def back(self, sid: str) -> str:
        if self.forks:
            # the copy continues; this process ends, and the copy's frame line comes on the
            # same pipes (they are inherited); two linked consoles go back together, so their
            # copies, made at the same frame, find the link as it was
            if len(self.procs) == 1:
                self.send(0, f"back {sid}")
                return self.read(0)
            if sid not in self.copies:
                return f"@err no snap {sid}"
            return self.everyone([f"back {c}" for c in self.copies[sid]])
        if sid not in self.snaps:
            return f"@err no snap {sid}"
        frame, logs = self.snaps[sid]
        return self.start(list(logs), frame)


def serve(args) -> None:
    workdir = HOME / args.name
    workdir.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, RUN_DRIVE="1", RUN_RENDER_THREAD="0")
    env["RUN_RTC"] = args.rtc
    def save_of(name: str) -> str:
        save = pathlib.Path(name)
        if not save.is_file():
            import scenes  # noqa: PLC0415
            seed = pathlib.Path(args.seed or os.environ.get("ACWW_SCENE_SEED", ""))
            save = scenes.derive_save(seed, name)
        return str(save.resolve())

    def prefix_of(name: str | None, out: pathlib.Path) -> pathlib.Path | None:
        if not name:
            return None
        rec = pathlib.Path(name)
        if not rec.is_file():
            rec = C.ROOT / "runtime" / "recordings" / "scenes" / f"{name}.txt"
        lines = [ln for ln in rec.read_text().splitlines()
                 if ln.strip() and (ln.startswith("#") or not args.until or int(ln.split()[0]) < args.until)]
        out.write_text("\n".join(lines) + "\n")
        return out

    if args.save:
        env["RUN_SAVE"] = save_of(args.save)
    starts = workdir / "starts.txt"
    syms = C.symbol_table(C.modules())
    starts.write_text("".join(f"{a:08x}\n" for a in sorted({s.address & ~1 for ss in syms.by_module.values()
                                                             for s in ss if s.kind == "function" and s.size})))
    env["RUN_DRIVE_STARTS"] = str(starts)
    envs = [env]
    prefixes = [prefix_of(args.prefix, workdir / "prefix.txt")]
    for k, peer_save in enumerate(args.peer_save or [], 1):  # consoles linked to the first
        rtc = args.peer_rtc[k - 1] if args.peer_rtc and k - 1 < len(args.peer_rtc) else args.rtc
        prefix = args.peer_prefix[k - 1] if args.peer_prefix and k - 1 < len(args.peer_prefix) else None
        envs.append(dict(env, RUN_SAVE=save_of(peer_save), RUN_RTC=rtc))
        prefixes.append(prefix_of(prefix, workdir / f"prefix-{k}.txt"))
    rt = Runtime(envs, prefixes, args.until, workdir)
    lock = threading.Lock()

    class Handler(socketserver.StreamRequestHandler):
        def handle(self):
            line = self.rfile.readline().decode().strip()
            with lock:
                if line == "stop":
                    for p in rt.procs:
                        p.kill()
                    self.wfile.write(b"@ok\n")
                    threading.Thread(target=server.shutdown).start()
                    return
                if line == "snap":
                    answer = rt.snap()
                elif line.startswith("back "):
                    answer = rt.back(line.split()[1])
                else:
                    answer = rt.command(line)
            self.wfile.write((answer + "\n").encode())

    server = socketserver.TCPServer(("127.0.0.1", 0), Handler)
    port_file(args.name).write_text(json.dumps({"port": server.server_address[1], "pid": os.getpid(),
                                                "lists": str(args.lists)}))
    server.serve_forever()
    port_file(args.name).unlink(missing_ok=True)


# ------------------------------------------------------------------------------ the client

def send(name: str, line: str, timeout: float = 3600) -> str:
    info = json.loads(port_file(name).read_text())
    with socket.create_connection(("127.0.0.1", info["port"]), timeout=timeout) as s:
        s.sendall((line + "\n").encode())
        data = b""
        while not data.endswith(b"\n"):
            chunk = s.recv(1 << 16)
            if not chunk:
                break
            data += chunk
    return data.decode().strip()


def resolve(path: pathlib.Path) -> set[tuple[str, int]]:
    """The (module, address) of each entry of a `seen` list, told apart by its first bytes."""
    mods = C.modules()
    syms = C.symbol_table(mods)
    by_addr: dict[int, list[str]] = {}
    for m, ss in syms.by_module.items():
        for s in ss:
            if s.kind == "function" and s.size:
                by_addr.setdefault(s.address & ~1, []).append(m)
    images = {}
    out = set()
    for line in path.read_text().splitlines():
        a, w0, w1 = (int(x, 16) for x in line.split())
        want = w0.to_bytes(4, "little") + w1.to_bytes(4, "little")
        for m in by_addr.get(a, ()):
            if m not in images:
                images[m] = C.module_image(m)
            off = a - mods[m]["base"]
            if images[m][off:off + 8] == want:
                out.add((m, a))
    return out


def new_functions(name: str) -> None:
    import coverage  # noqa: PLC0415
    info = json.loads(port_file(name).read_text())
    path = HOME / name / "seen.txt"
    print(send(name, f"seen {path}"))
    entered = resolve(path)
    for k in range(1, 4):  # two or more consoles: what any entered
        peer = HOME / name / f"seen-{k}.txt"
        if not send(name, f"@{k} seen {peer}").startswith("@ok"):
            break
        entered |= resolve(peer)
    syms = C.symbol_table(C.modules())
    clean = coverage.clean_functions(syms)
    known = set()
    for seen in coverage.scene_lists(pathlib.Path(info["lists"])).values():
        known |= seen
    fresh = sorted(k for k in entered if k in clean and k not in known)
    print(f"{len(entered)} functions entered, {len([k for k in entered if k in clean])} with a Clean version; "
          f"{len(fresh)} of them no scene enters")
    by_file: dict[str, list[str]] = {}
    for k in fresh:
        by_file.setdefault(clean[k][0], []).append(clean[k][1])
    for f, names in sorted(by_file.items(), key=lambda kv: -len(kv[1])):
        print(f"  {len(names):4}  {f}: {', '.join(names[:4])}{' ...' if len(names) > 4 else ''}")


def main() -> None:
    if len(sys.argv) > 1 and sys.argv[1] in ("start", "_serve"):
        ap = argparse.ArgumentParser()
        ap.add_argument("mode")
        ap.add_argument("name")
        ap.add_argument("--save", help="a save file, or a derived save's name (tools/scenes.py SAVES)")
        ap.add_argument("--seed", help="the seed save (default ACWW_SCENE_SEED)")
        ap.add_argument("--rtc", default="2026-09-11 11:30:00")
        ap.add_argument("--prefix", help="a recording (or a scene's name) to play first")
        ap.add_argument("--until", type=int, default=0, help="with --prefix: play it up to this frame")
        ap.add_argument("--peer-save", action="append",
                        help="a second console linked to the first: its save (or a derived save); again for a third")
        ap.add_argument("--peer-prefix", action="append",
                        help="with --peer-save: a recording for the second console to play first; again for a third")
        ap.add_argument("--peer-rtc", action="append",
                        help="with --peer-save: the second console's clock (default --rtc); again for a third")
        ap.add_argument("--lists", default=str(C.BUILD / "scenes"), help="the scenes' lists, for `new`")
        args = ap.parse_args()
        if args.mode == "_serve":
            serve(args)
            return
        HOME.mkdir(parents=True, exist_ok=True)
        if port_file(args.name).exists():
            try:
                send(args.name, "frame", timeout=5)
                raise SystemExit(f"{args.name} is running already (drive.py {args.name} stop)")
            except OSError:
                port_file(args.name).unlink()
        log = open(HOME / f"{args.name}.server.log", "w")
        flags = subprocess.CREATE_NEW_PROCESS_GROUP | subprocess.DETACHED_PROCESS if os.name == "nt" else 0
        subprocess.Popen([sys.executable, __file__, "_serve", *sys.argv[2:]], stdout=log, stderr=log,
                         stdin=subprocess.DEVNULL, creationflags=flags, start_new_session=os.name != "nt")
        for _ in range(1200):
            if port_file(args.name).exists():
                break
            time.sleep(0.25)
        else:
            raise SystemExit(f"the run did not start: {HOME / (args.name + '.server.log')}")
        print(send(args.name, "frame"))
        return
    if len(sys.argv) < 3:
        raise SystemExit(__doc__)
    name, cmd = sys.argv[1], sys.argv[2:]
    if cmd[0] == "new":
        new_functions(name)
        return
    if cmd[0] == "press":  # a short press, then a pause for the game to react
        hold = int(cmd[2]) if len(cmd) > 2 else 2
        wait = int(cmd[3]) if len(cmd) > 3 else 20
        print(send(name, f"run {hold} {cmd[1]} -"))
        print(send(name, f"run {wait} - -"))
        return
    at = 1 if AT.fullmatch(cmd[0]) else 0
    if len(cmd) > at + 1 and cmd[at] in ("png", "log", "seen", "redraw", "video", "gx3d"):
        cmd[at + 1] = str(pathlib.Path(cmd[at + 1]).resolve())
    print(send(name, " ".join(cmd)))


if __name__ == "__main__":
    main()
