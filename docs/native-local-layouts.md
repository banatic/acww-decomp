# Observable local layouts in Native

Some matching sources declare separate locals even though the ROM passes a
pointer that covers more than one of them. The ARM stack gives those locals a
specific order. Independent host locals have no such ordering guarantee.
tools/native_layout.py groups only the five audited layouts below in PC source
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

tools/test_native_layout.py compiles all five exact copied game functions, the
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
