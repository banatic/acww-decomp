# Observable fishing layouts in Native

Some matching sources declare separate locals even though the ROM passes a
pointer that covers more than one of them. The ARM stack gives those locals a
specific order. Independent host locals have no such ordering guarantee.
tools/native_layout.py groups only the two audited fishing layouts in PC source
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

tools/test_native_layout.py compiles both exact copied game functions, the real
vector consumer and the real request payload writer. Its fixture checks the
coordinates and payload received by their callees, returned values, and rejection
of changed source digests. Full recording and scene gates remain required.
