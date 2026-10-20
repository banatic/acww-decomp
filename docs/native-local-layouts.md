# Observable local layouts in Native

Some matching sources declare separate locals even though the ROM passes a
pointer that covers more than one of them. The ARM stack gives those locals a
specific order. Independent host locals have no such ordering guarantee.
tools/native_layout.py groups only the 29 audited layouts below in PC source
copies. Values and calls are unchanged. Source digests and exact declarations
reject an unaudited source change, and each copy asserts the observed offset.

## Fishing state request: func_ov003_02215f00

The request starts at sp (02215f0c, 02215f12). Its X/Z payload is written at sp+12
(02215f2a), and the pointer passed to func_0200e894 is sp (02215f34). The C source
declares char ctx[12] and int out[4] separately, fills out, and submits ctx.
The PC copy groups them as successive fields of one structure, with out at 12.

## Target coordinates: func_0201c2c8

At 0201c2da and 0201c2dc the ROM passes sp+8 and sp+16 to func_02096614. These are
the X and Z outputs. At 0201c2ec it passes sp+8 as a vector to func_0200322c, which
reads X at offset 0 and Z at offset 8. The matching source declares two separate
two-word arrays, dataA and dataB. The PC copy places these arrays in one
structure, with dataB at 8. The unused intermediate word is not initialized.

The Windows fish-cast investigation found an angle target of -32768 where the
Reference passes 0 at frame 3487. Keeping only the angle helper Reference moves
the first pixel difference to 3490; the caller's local layout must be preserved.

## Validation

tools/test_native_layout.py compiles all 29 exact copied game functions, the
real vector consumer and three real request payload writers. Its fixture checks
the coordinates, tags, item identifiers and signed header arguments received by
the request consumer, returned values, and rejection of changed source digests.
It also checks both branches of the tool request's actor-item clearing logic.
Full recording and scene gates remain required.

## Tool state requests

The tool-shovel investigation traced invalid particle inputs back to separate
request header and payload locals. The three audited tool request constructors
submit the header pointer to func_0200e894, which expects the payload immediately
after the 12-byte header. Their ARM stack addresses establish that relationship:

| Function | Header construction | Payload destination | Submitted header |
|---|---|---|---|
| func_ov003_02211d4c | sp at 02211d58 | sp+12 at 02211d7a | sp at 02211d86 |
| func_ov003_022118f8 | sp+4 at 02211904 | sp+16 at 02211926 | sp+4 at 02211952 |
| func_ov003_02211980 | sp at 0221198c | sp+12 at 022119ae | sp at 022119bc |

The first request uses state 0x5e and func_ov003_02211da0 writes its tag and
three coordinates. The other two use state 0x5f and func_ov003_022119d8 writes
three coordinates, a 16-bit item and an 8-bit tag. The no-item form supplies
0xfff1. Grouping only each header/payload pair preserves these fields without
changing their values, calls, or the independent coordinate-copy local.

## Two-word outputs: func_020a967c and func_0201354c

At 020a96a8 the ROM passes sp to func_02064658, which reads eight bytes there, and at
020a96d6 it passes sp+4, the second word, to func_020a9ae4; the source declares the words as
the separate locals local1 and local2. At 0201357a/0201357c the ROM passes sp+0x2c and
sp+0x30 to func_0204f818 as its two outputs, and at 02013614 it passes sp+0x2c to
func_020137ec as a two-word point; the source declares s2c and s30. The PC copies group each
pair with the second word at 4. The layout fixture checks both: the second word read through
the first local's address is the second local.

## Other request builders

Twenty-two more request builders keep the header and the payload in separate locals. In
each ROM body the header's stack offset goes to func_0200e894 and the payload, 12 bytes
further, to the function that fills it (an `add rN, sp, #x` before each call):

| Function | Header | Payload writer |
|---|---|---|
| func_02009a44 | sp+4 | func_02009a9c |
| func_0200a6a0 | sp+8 | func_0200a6f0 |
| func_0200acd4 | sp+12 | func_0200ad78 |
| func_0200ad24 | sp+8 | func_0200ad78 |
| func_0200b7e8 | sp+16 | func_0200b894 |
| func_0200c3b0 | sp | func_0200c3f0 |
| func_0200cc00 | sp | func_0200cc40 |
| func_0200dbb4 | sp | func_0200dc00 |
| func_ov003_0220fb30 | sp+8 | func_ov003_0220fb80 |
| func_ov003_0220fda0 | sp | func_ov003_0220fdf4 |
| func_ov003_02212830 | sp+8 | func_ov003_02212878 |
| func_ov003_02212c10 | sp+4 | func_ov003_02212d04 |
| func_ov003_02215624 | sp | func_ov003_02215664 |
| func_ov003_02216410 | sp+8 | func_ov003_02216460 |
| func_ov003_02216698 | sp+12 | func_ov003_022166e8 |
| func_ov003_02216ab8 | sp+12 | func_ov003_02216b08 |
| func_ov003_022171ec | sp+4 | func_ov003_022172bc |
| func_ov003_02217838 | sp+12 | func_ov003_02217894 |
| func_ov003_022186cc | sp+8 | func_ov003_0221871c |
| func_ov003_022188d0 | sp+4 | func_ov003_02218918 |
| func_ov004_02228628 | sp+8 | func_ov004_02228678 |
| func_ov004_0222ac24 | sp+8 | func_ov004_0222ac74 |

tests/native/request_layout.c runs the 22 copies with payload writers that mark their
payload and a submission that must find the mark 12 bytes after the header it receives.
Built from the original sources instead, 10 of them fail on Windows.
