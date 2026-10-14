/* The DS 3D hardware: the geometry engine (command FIFO, matrices, lighting, vertex
 * transformation, clipping, the tests) and the rendering engine (rasterisation of the swapped
 * polygon list into a 256x192 colour/alpha/depth/attribute buffer), as GBATEK's "DS 3D"
 * chapters describe them. io.c forwards the geometry ports (0x04000400-0x040005ff) and the
 * result registers (0x04000600-0x040006ff) here and calls gpu3d_vblank at the start of each
 * VBlank, when a pending SWAP_BUFFERS takes effect and the new list is rendered. io_init calls
 * gpu3d_init.
 *
 * The per-frame rendering registers (DISP3DCNT, EDGE_COLOR, ALPHA_TEST_REF, CLEAR_*, FOG_*,
 * TOON_TABLE, DISP_1DOT_DEPTH) stay in io.c's register file and are read here at render time;
 * textures and palettes come from the VRAM banks mapped as texture image / texture palette
 * (io_vram_texture, io_vram_texture_palette).
 */
#ifndef RUNTIME_GPU3D_H
#define RUNTIME_GPU3D_H

#include <stdint.h>
#include <stdio.h>

/* Clears the engine as a reset does. Reads RUN_DUMP3D (see gpu3d_dump_png) and RUN_TRACE:
 * with "gx" in it, every rendered list prints a line on stderr (polygons, vertices,
 * DISP3DCNT, clear colour, pixels drawn). */
void gpu3d_init(void);

/* A 32-bit write to geometry port `offset` (0x400-0x5ff from 0x04000000): the packed FIFO at
 * 0x400-0x43f or a command port. Commands execute as soon as their parameters are complete;
 * only after SWAP_BUFFERS do they wait in the FIFO, until the swap at VBlank, as on the
 * hardware. io.c re-evaluates the GX FIFO interrupt after each write. */
void gpu3d_write(uint32_t offset, uint32_t value);

/* GXSTAT (0x600, without the IRQ-select bits 30-31, which io.c keeps), RAM_COUNT (0x604) and
 * the test and matrix result registers (0x620-0x6a3). Other offsets read zero. */
uint32_t gpu3d_read(uint32_t offset);

/* A write to GXSTAT: bit 15 set acknowledges the matrix stack error and resets the
 * projection and texture stack pointers. */
void gpu3d_gxstat_write(uint32_t value);

/* The start of VBlank (line 192): a swap requested since the last one takes effect and the
 * list it hands over is rendered into the output buffer. */
void gpu3d_vblank(void);

/* The last rendered frame, as the 2D engine's BG0 sees it: 256 pixels of RGB555 with bit 15
 * set where the pixel has any alpha (an opaque polygon, a translucent one or the rear plane),
 * and the 5-bit alpha of each pixel for the 2D blender. */
const uint16_t *gpu3d_line(int y);
const uint8_t *gpu3d_line_alpha(int y);

/* Writes the last rendered frame alone as a 256x192 RGB PNG (frame.c's writer), with a grey
 * checkerboard where the layer has no alpha. 0 on success. RUN_DUMP3D=<dir>[:<list>] in the
 * environment does this at each VBlank of the listed frames as <dir>/3d-<frame>.png; the
 * list is n, a-b or a-b/step, comma-separated, and defaults to RUN_PNG_FRAMES, then to every
 * frame (tools/run.py --png3d DIR --frames LIST). */
int gpu3d_dump_png(const char *path);

/* Counters for the run report: commands, polygons, swaps, render time. */
void gpu3d_report(FILE *out);

#endif
