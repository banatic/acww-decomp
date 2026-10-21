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

`new` compares with the lists of tools/coverage.py (build/adm-kr/scenes/*/functions-seen.txt, or
--lists DIR at start). On Windows `snap` keeps the input so far and `back` plays it again
from the start; on Linux the run is forked and `back` is immediate. A recording from `log` is a
scene's recording as is: add it with its frame count to tools/scenes.py and run it there, which
checks Native and Clean against the Reference.
"""
from __future__ import annotations

import argparse
import json
import os
import pathlib
import socket
import socketserver
import subprocess
import sys
import threading
import time

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

HOME = C.BUILD / "drive"


def port_file(name: str) -> pathlib.Path:
    return HOME / f"{name}.json"


# ------------------------------------------------------------------------------ the server

class Runtime:
    """The run, and the copies `snap` keeps."""

    def __init__(self, base_env: dict, prefix: pathlib.Path | None, until: int, workdir: pathlib.Path):
        import run  # noqa: PLC0415
        self.run = run
        self.manifest, self.table = run.generate()
        self.exe = run.build(native=False)
        self.base_env = base_env
        self.workdir = workdir
        self.proc: subprocess.Popen | None = None
        self.forks = None  # unknown until the first snap
        self.snaps: dict[str, tuple[int, pathlib.Path]] = {}
        self.output = open(workdir / "run.log", "a", encoding="utf-8", errors="replace")
        self.start(prefix, 0)
        if prefix is not None and until:
            self.command(f"run {until}")

    def start(self, recording: pathlib.Path | None, frame: int) -> str:
        if self.proc is not None:
            self.proc.kill()
            self.proc.wait()
        env = dict(self.base_env)
        if recording is not None:
            env["RUN_INPUT"] = str(recording)
        else:
            env.pop("RUN_INPUT", None)
        self.proc = subprocess.Popen([str(self.exe), str(self.run.ROM), str(self.manifest), str(self.table), "0"],
                                     cwd=C.ROOT, env=env, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                                     stderr=self.output, text=True, bufsize=1)
        answer = self.read()
        if frame:
            answer = self.command(f"run {frame}")
        return answer

    def read(self) -> str:
        assert self.proc is not None and self.proc.stdout is not None
        for line in self.proc.stdout:
            if line.startswith("@"):
                return line.strip()
            self.output.write(line)
        self.output.flush()
        return "@err the run ended (see run.log)"

    def command(self, line: str) -> str:
        assert self.proc is not None and self.proc.stdin is not None
        if not self.forks and self.proc.poll() is not None:
            return "@err the run ended (see run.log)"
        self.proc.stdin.write(line + "\n")
        self.proc.stdin.flush()
        return self.read()

    def frame(self) -> int:
        return int(self.command("frame").split()[-1])

    def snap(self) -> str:
        if self.forks is not False:
            answer = self.command("snap")
            if answer.startswith("@ok"):
                self.forks = True
                return answer
            self.forks = False
        sid = str(len(self.snaps) + 1)
        log = self.workdir / f"snap-{sid}.txt"
        self.command(f"log {log}")
        self.snaps[sid] = (self.frame(), log)
        return f"@ok {sid}"

    def back(self, sid: str) -> str:
        if self.forks:
            # the copy continues; this process ends, and the copy's frame line comes on the
            # same pipes (they are inherited)
            assert self.proc is not None and self.proc.stdin is not None
            self.proc.stdin.write(f"back {sid}\n")
            self.proc.stdin.flush()
            return self.read()
        if sid not in self.snaps:
            return f"@err no snap {sid}"
        frame, log = self.snaps[sid]
        return self.start(log, frame)


def serve(args) -> None:
    workdir = HOME / args.name
    workdir.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, RUN_DRIVE="1", RUN_RENDER_THREAD="0")
    env["RUN_RTC"] = args.rtc
    if args.save:
        save = pathlib.Path(args.save)
        if not save.is_file():
            import scenes  # noqa: PLC0415
            seed = pathlib.Path(args.seed or os.environ.get("ACWW_SCENE_SEED", ""))
            save = scenes.derive_save(seed, args.save)
        env["RUN_SAVE"] = str(save.resolve())
    starts = workdir / "starts.txt"
    syms = C.symbol_table(C.modules())
    starts.write_text("".join(f"{a:08x}\n" for a in sorted({s.address & ~1 for ss in syms.by_module.values()
                                                             for s in ss if s.kind == "function" and s.size})))
    env["RUN_DRIVE_STARTS"] = str(starts)
    prefix = None
    if args.prefix:
        rec = pathlib.Path(args.prefix)
        if not rec.is_file():
            rec = C.ROOT / "runtime" / "recordings" / "scenes" / f"{args.prefix}.txt"
        lines = [ln for ln in rec.read_text().splitlines()
                 if ln.strip() and (ln.startswith("#") or not args.until or int(ln.split()[0]) < args.until)]
        prefix = workdir / "prefix.txt"
        prefix.write_text("\n".join(lines) + "\n")
    rt = Runtime(env, prefix, args.until, workdir)
    lock = threading.Lock()

    class Handler(socketserver.StreamRequestHandler):
        def handle(self):
            line = self.rfile.readline().decode().strip()
            with lock:
                if line == "stop":
                    if rt.proc is not None:
                        rt.proc.kill()
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
    if cmd[0] in ("png", "log", "seen", "redraw", "video", "gx3d") and len(cmd) > 1:
        cmd[1] = str(pathlib.Path(cmd[1]).resolve())
    print(send(name, " ".join(cmd)))


if __name__ == "__main__":
    main()
