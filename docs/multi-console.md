# Several consoles

The runtime plays one console; the game's local wireless (town visits, moving in through
another town, the gatekeeper's DS-wireless visit, the session and link jobs, the other
console's field actors) needs a second one. This document describes how two (and later more)
simulated consoles run together, how the ARM7's wireless manager is simulated, and how a
scene of several consoles is checked. Phase 1 (this document's "done" parts) is local wireless
between two consoles; Nintendo Wi-Fi Connection through a simulated server is a later phase.

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
| StartConnect | CONNECT_START; the request goes to the parent; its answer gives CONNECTED with the AID (or a failure) |
| StartMP | MP_START, the receive and send buffers kept |
| SetMPDataToPort | queued for the next MP turn; PORT_SEND once it went out |
| EndMP, EndParent, Disconnect, EndScan | SUCCESS, and the other console told where it concerns it |
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

`tools/drive.py` drives one console; with `RUN_WIRELESS=1` in its environment the console has
its wireless, which is how the recordings of a scene's consoles are made one at a time and then
played together.

## Status

Done (phase 1): the WM simulation for one console and for two; `--wireless` and the linked run
in `tools/run.py`; the scenes `title-move-in-alone` and `gate-visit-alone` (one console, the
search finds nobody) and `gate-visit-link` (the seed town opens its gate, another town's player
finds it, connects, receives the town over MP and walks through the gate into it).

Later: more than two consoles (the star above); the beacon lost when a parent stops beaconing
without a disconnection; the MP frequency (one turn a frame here); DCF and Wi-Fi Connection
through a simulated access point and server (phase 2).
