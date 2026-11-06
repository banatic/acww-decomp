# Several consoles

The runtime plays one console; the game's local wireless (town visits, moving in through
another town, the gatekeeper's DS-wireless visit, the session and link jobs, the other
console's field actors) needs a second one. This document describes how two (and later more)
simulated consoles run together, how the ARM7's wireless manager is simulated, and how a
scene of several consoles is checked. Phase 1 (this document's "done" parts) is local wireless
between two consoles; phase 2 is Nintendo Wi-Fi Connection through a simulated access point,
network and servers, all inside the process ("Wi-Fi Connection" below).

## One process per console

Each console is a process of its own, the program `tools/run.py` builds for one console, with
its own save, input recording and clock. The consoles exchange messages through pipes once a
frame, at the same emulated moment on each.

Why not one process with several machines: the runtime's state is global by design. Native code
runs in a 32-bit process whose memory holds the DS's main RAM at its real address
(0x02000000, `runtime/memory.c`), so one process can map one console's memory only; and the
interpreter, the hardware model (`io.c`, `gpu2d.c`, `gpu3d.c`, `render.c`), the ARM7 model
(`arm7.c`, `sequencer.c`) and the Native dispatcher (`native_run.c`, with its crossings record
and host fibers per guest thread) all keep file-scope statics, several hundred of them. Making
them per machine would touch every file; one process per console touches none of them.

Why it stays deterministic: the exchange happens at the first ARM7 step of each frame
(`wm_step`, called from `arm7_step` between slices and while the CPU halts), so at the same
emulated cycle in a Reference run and in a Native run of the same console (the Native run
keeps the Reference's timing through its crossings record). What a console sends depends only
on its own emulated state; what it receives is the other console's message for the same
frame. Wall-clock speed, scheduling and pipe buffering never reach the game.

The order of the exchange is fixed: console 0 writes its message then reads console 1's;
console 1 reads first, then writes. Neither can wait on a full pipe, whatever the message
sizes. With more consoles the same order extends to a star with console 0 in the middle
(console 0 writes to each, then reads from each; it forwards what one child sends to another),
which phase 1 does not need: two consoles are a parent and one child.

A message is the frame number, a length and records (kind, length, bytes): the parent's
beacon, a child's request to connect, the parent's answer (the AID or a refusal), a
disconnection, and one MP turn's data. A console whose pipe closes (the other ended or
crashed) is alone from then on, and says so on stderr.

## The wireless manager

`runtime/wm.c` answers PXI tag 0xa as the ARM7's WM does, at the level of the ARM9's WM library
in the ROM (autoload_2, read from its code; no ARM7 code is run or copied):

- `WMi_SendCommand` sends the address of a 256-byte command buffer: the API id in the first
  halfword, then the arguments as words, or a request structure copied from `fifo9to7`.
- `WmReceiveFifo` takes the address of a callback structure back. A command's callback is
  written into that command's buffer (the ARM9 then sets bit 15 of its first halfword, which
  frees the buffer for a later command). A notification that belongs to no command (a beacon
  sent, a child connected, an MP turn, data received on a port) goes through the shared
  `fifo7to9` buffer, one at a time: bit 0 of `wm_callback_control` (0x027fff96) is set while the
  ARM9 has not taken it, and `WmClearFifoRecvFlag` clears it.
- The status the ARM9 reads (`WMStatus`, at the address `WM_Enable` names) is written where its
  fields are: the state, the AID, the children's bitmap, the MP flag and sizes, the link level.

The commands and what they do:

| Command | Answer |
|---|---|
| Initialize, Enable, Disable, PowerOn, PowerOff, Reset, End | the state (READY, STOP, IDLE) and SUCCESS; Reset ends a parent, a child and MP |
| SetParentParameter | the parameters copied into the status |
| StartParent | PARENT_START; then BEACON_SENT every beacon period; the beacon goes on the air every frame |
| SetGameInfo, SetEntry | the beacon's game info and its entry flag |
| MeasureChannel | after the time asked, the channel with nothing busy |
| StartScan | after the channel's time, PARENT_FOUND with the parent's WMBssDesc written to the scan buffer when a parent's beacon on that channel came in this frame, else PARENT_NOT_FOUND |
| StartScanEx | (without Wi-Fi Connection, on a linked console) after the channels' time, as StartScan for the channels asked for: the other console's parent when its beacon came on one of them in that frame and its MAC is the BSSID asked for (or broadcast), its WMBssDesc in the scan buffer (the passing exchange's library, ov067, scans this way) |
| StartConnect | CONNECT_START; the request goes to the parent; its answer gives CONNECTED with the AID (or a failure) |
| StartMP | MP_START, the receive and send buffers kept |
| SetMPDataToPort | queued for the next MP turn; PORT_SEND once it went out |
| EndMP, EndParent, Disconnect, EndScan | SUCCESS, and the other console told where it concerns it (a child that leaves, by Disconnect or Reset, is DISCONNECTED on its parent's side) |
| the rest (lifetimes, beacon indication) | SUCCESS |

An MP turn is one a frame, with a fixed latency of one frame each way. At the exchange of
frame N the parent sends what was queued during frame N-1; the child receives it in the same
exchange (its ports' PORT_RECV, then MP_IND and MPACK_IND), and sends what it queued during
frame N-1, which the parent receives (PORT_RECV, then MPEND_IND). Data received is written into
the game's MP receive buffer, the two halves in turn, and the port callbacks point at it.

The firmware of a console with its wireless has a MAC address (Nintendo's 00:09:BF block, the
last byte the console's number) and the channels local play uses (1, 7 and 13): the ARM7
publishes them at 0x027ffcf4 and 0x027ffcfa, where `OS_GetMacAddress`,
`WM_IsExistAllowedChannel` and `WM_GetAllowedChannel` read them. Without them the game's local
library finds no channel, frees its control block and goes on using it (a `BUG:` in
`clean/ov066/local_wireless.c`), which ends in a failed allocation and the game's stop: that is
what scenes without the wireless (`title-move-in-halt`, `gate-visit-halt`) show.

The wireless is off unless asked for (`tools/run.py --wireless`, `RUN_WIRELESS=1`), so every
scene without it plays as before. WVR (tag 0xf, the wireless VRAM image) is answered as before:
the start and the end with SUCCESS.

## Scenes of several consoles

A scene names its consoles in `tools/scenes.py`: console 0 is the scene's own save and
recording, `peer=(save, recording)` the second console's (`scene(..., peer=("other-town",
"gate-visit-guest"))`); both have the scene's frame count, checkpoints and clock, and both have
their wireless. A save of another town is made from the seed (`other-town`: the seed town's id
and name and its player's number replaced wherever the bank names them, the checksum made
good), under the run directory like every derived save, never committed.

`tools/run.py --peer-save FILE --peer-input FILE` runs both consoles at once: the Reference pass
of both, linked, then the Native pass of both, linked. Each console is compared with its own
Reference frame by frame and in memory at the checkpoints; the scene passes when both agree.
The frame sequence it prints, and the `.sha1` of the scene, is a SHA-1 over the two consoles'
sequences in order. Console 1's logs and hashes are in `peer/` beside console 0's; the functions
the scene ran (for `tools/coverage.py`) and the Clean functions it entered are the union of
both consoles'. The Reference cache is not used for a linked run, as one console's run depends
on the other's.

The check holds both ways, as for one console: with every Clean function (the default) and
with Native alone (`--clean none`). A difference in one console changes what it sends, so the
other console may differ too; the first console to differ is the one to look at.

`tools/drive.py` drives one console, or two linked as a scene links them (`start` with
--peer-save and --peer-prefix): each `run` runs both, console 1's input after `@1`, and any
other command is console 0's or, after a leading `@1`, console 1's. That is how the recordings of
the scenes below were made (`log` and `@1 log` give the two recordings).

## Wi-Fi Connection

`tools/run.py --wifi[=MODE]` (`RUN_WIFI`, which implies the wireless) lets the game's own Nintendo
Wi-Fi Connection code run offline: an access point, the network behind it and the servers the
library asks for are simulated in `runtime/wifi.c`. Nothing touches a real network; there are
no sockets and no wall clock. It is opt-in, so every scene without it plays as before.

The access point. The firmware image gets its first connection setting (the SSID
`acww-offline`, DHCP, no user ID) on the four pages below the user settings, each with its
CRC-16, so the game finds a configured connection. WM's `StartScanEx` finds the access point
(MAC 02:00:41:43:57:01, channel 1) when the request's channels, BSSID and SSID match; a connect
to that MAC associates after 20 ms (AID 1). `StartDCF`, `SetDCFData` and `EndDCF` carry the data
frames: what the ARM9 sends goes to `wifi_send`, and a frame for the console is written into the
DCF receive buffer and announced with DCF_IND, one at a time, once the ARM9 has taken the one
before.

The network. The frames' bodies are LLC/SNAP and an IPv4 packet (or ARP). The router at
192.168.11.1 answers ARP, DHCP (the console gets 192.168.11.2/24), DNS (every name gets an
address 10.0.0.n, numbered in the order names are first asked) and ping. TCP is a small fixed
stack: the initial sequence numbers come from a counter, the segments respect the console's
window and an MSS of 1024, and a server closes after its answer. Each answer leaves 1 ms of
emulated time after the request, so a run is the same on every host and in every mode.

The servers. HTTP on ports 80 and 443 by the `Host` header: the connection test answers 200
with a page; the account server (NAS) answers acctcreate, login and svcloc in its encoding
(the library's Base64 variant), with a fixed challenge, token and date; any other host answers
404. UDP 27900 answers GameSpy's availability check (servers up). The presence server (gpcm, TCP
29900) greets with a challenge, answers the login with the proof the library checks (MD5 over
the NAS challenge's hash, the token and both challenges), and answers getprofile and updatepro
so the library's first registration of its name completes. Other UDP (the QR2 master server) is
not answered.

The SSL shim. HTTPS is plain HTTP here: no certificate is checked and nothing is encrypted. The
library's SSL entries in NitroWiFi's CPS (library code in ov065; no game function) are replaced
by the plain TCP functions they would call underneath: connect, read, write, consume, shutdown
and the pending length. Each is an interpreter hook at the entry's address, taken only when the
CRC-32 of the bytes there is the entry's (the overlay's addresses are shared). Library
functions are interpreted in every mode, so the shim applies the same in Reference, Native and
Clean.

The modes. `--wifi` (1) answers everything; `noap` finds no access point; `nodns` answers every
name with NXDOMAIN; `conntest` answers the connection test with 503; `nas` answers the NAS login
with an error code. `RUN_TRACE=wifi` traces the frames, connections and requests.

The memory comparison also clears the context and stack of a thread that has ended (its
OSThread still marked terminated, with the same stack): the library starts a thread for each
HTTP request, and an ended thread's stack holds what its frames left, which Native code leaves
differently (its frames are on the host's stacks).

## Status

Done (phase 1): the WM simulation for one console and for two; `--wireless` and the linked run
in `tools/run.py`; the scenes `title-move-in-alone` and `gate-visit-alone` (one console, the
search finds nobody) and `gate-visit-link` (the seed town opens its gate, another town's player
finds it, connects, receives the town over MP and walks through the gate into it).

Done (phase 1, second batch): `visit-tools` (gate-visit-link on: host and visitor use each tool
side by side, the visitor drops an item and goes into the town hall and out), `visit-leave` (the
visitor asks the gatekeeper to go home: the host is called to the gatehouse, both save, the
session ends), `visit-chat` (the host's START question of the linked game, both players' chat
lines) and `exchange-link` (the passing exchange of two consoles with a letter in a bottle: the
exchange library, ov067, takes turns as parent and child by its clock; the blocks go over MP).

Done (phase 1, third batch): `host-ends-link` (visit-chat's question answered with "end the
link": both save, the host ends its parent and the guest, which loses it, goes home through its
own gate). A parent that goes away hands the guest's queued MP data back unsent but not failed:
the local wireless library stops the game on a failed send.

Done (phase 2): the access point, the network and the servers above; the scenes
`gate-wfc-online` (the gatekeeper's Wi-Fi visit: connect, NAS and GameSpy logins, up to the
list of towns to visit, empty as no friend is online), `gate-wfc-no-ap`, `gate-wfc-no-dns`,
`gate-wfc-conntest` and `gate-wfc-nas-error` (the error paths).

Out of range: a recording's NORADIO (runtime/input.h) holds a console's wireless out of range.
The consoles still exchange a message each frame, so they stay in step, but the one out of
range sends nothing and takes in nothing, and the other hears nothing from it. The scene
`gate-visit-lost` holds the visitor's NORADIO once the visitor is in the town: both sessions
time out, and the caution window counts down to the reset.

Later: more than two consoles (the star above); the beacon lost when a parent stops beaconing
without a disconnection; the MP frequency (one turn a frame here); for Wi-Fi Connection, the QR2
master server and the matchmaking that would show a friend's town, and two consoles meeting
through it.
