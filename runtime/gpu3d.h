/* The DS 3D hardware: the geometry engine (command FIFO, matrices, lighting, vertex
 * transformation, clipping, the tests) and the rendering engine (rasterisation of the swapped
 * polygon list into a 256x192 colour/alpha/depth/attribute buffer), as GBATEK's "DS 3D"
 * chapters describe them. io.c forwards the geometry ports (0x04000400-0x040005ff) and the
 * result registers (0x04000600-0x040006ff) here and calls gpu3d_vblank at the start of each
 * VBlank, when a pending SWAP_BUFFERS takes effect and the new list is rendered. io_init calls
 * gpu3d_init.
 *
 * The per-frame rendering registers (DISP3DCNT, EDGE_COLOR, ALPHA_TEST_REF, CLEAR_*, FOG_*,
 * TOON_TABLE) stay in io.c's register file and are read here at render time (DISP_1DOT_DEPTH
 * is forwarded: the geometry engine applies it as polygons are given);
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

/* A write to DISP_1DOT_DEPTH (0x610): the w beyond which a polygon on one dot is dropped. */
void gpu3d_dot_depth_write(uint32_t value);

/* GXSTAT (0x600, without the IRQ-select bits 30-31, which io.c keeps), RAM_COUNT (0x604) and
 * the test and matrix result registers (0x620-0x6a3). Other offsets read zero. */
uint32_t gpu3d_read(uint32_t offset);

/* A write to GXSTAT: bit 15 set acknowledges the matrix stack error and resets the
 * projection and texture stack pointers. */
void gpu3d_gxstat_write(uint32_t value);

/* The start of VBlank (line 192): a swap requested since the last one takes effect and the
 * list it hands over is rendered into the output buffer. */
void gpu3d_vblank(void);

/* Draws list `list` (0 or 1), which a swap handed over, into the output buffer (render.c
 * calls it, on the drawing thread or at once, from gpu3d_vblank). */
void gpu3d_render(int list);

/* The last rendered frame: as the 2D engine's BG0 sees it, 256 pixels of red | green << 8 |
 * blue << 16 (6 bits each) | alpha << 24 (5 bits, nonzero where an opaque polygon, a
 * translucent one or the rear plane is); and in RGB555 with bit 15 set where the alpha is
 * nonzero, as the display capture takes it. */
const uint32_t *gpu3d_line_rgb6(int y);
const uint16_t *gpu3d_line(int y);

/* Writes the last rendered frame alone as a 256x192 RGB PNG (frame.c's writer), with a grey
 * checkerboard where the layer has no alpha. 0 on success. RUN_DUMP3D=<dir>[:<list>] in the
 * environment does this at each VBlank of the listed frames as <dir>/3d-<frame>.png; the
 * list is n, a-b or a-b/step, comma-separated, and defaults to RUN_PNG_FRAMES, then to every
 * frame (tools/run.py --png3d DIR --frames LIST). */
int gpu3d_dump_png(const char *path);

/* The 3D check (build/ext's melonDS driver gives its 3D engine the same input and compares):
 * from gpu3d_capture_start on (drive.c calls it when driving), each list keeps the input it was
 * made from, and gpu3d_capture_write writes that of the last list rendered (render_finish
 * first, so that it is drawn) as little-endian 32-bit words unless said otherwise:
 *
 *     "GX3D" (0x44335847), version 1, S, L
 *     S words of state at the list's start (after the swap before it): matrix mode; the
 *         projection, position, vector and texture matrices (16 each); the projection stack
 *         (16), position and vector stacks (32 x 16 each), texture stack (16); the projection,
 *         position and texture stack pointers; the stack error flag; the current vertex (3);
 *         the vertex colour (3, 5 bits); TEXCOORD as written (2) and after its transformation
 *         (2); the polygon attributes in effect and the last written; TEXIMAGE_PARAM;
 *         PLTT_BASE; the last LIGHT_VECTOR parameter of each light (4) and the vector matrix
 *         it went through (4 x 16); the light colours (4 x 3); diffuse, ambient, specular,
 *         emission (3 each, 5 bits); the shininess table flag; the shininess table (128);
 *         VIEWPORT; the primitive type of the last BEGIN_VTXS; the vertices given of a
 *         polygon not yet complete, plus 0x100 while a strip goes on; the parameter of the last
 *         swap; the 1-dot w limit (DISP_1DOT_DEPTH * 0x200 + 0x1ff, 0xffffff before a write); the
 *         polygons of the strip so far; the four vertices of the polygon being given (clip
 *         coordinates (4), colour with 12 fractional bits (3), texture coordinates (2), made
 *         by clipping (1))
 *     L words of log: per command executed, cmd | params << 8 | results << 16, the parameters,
 *         then the test results (BOX_TEST 1, POS_TEST 4, VEC_TEST 3); cmd 0x80 with one
 *         parameter is a write of GXSTAT bit 15 (the stack error acknowledgement), cmd 0x81
 *         one of DISP_1DOT_DEPTH; the last command is the SWAP_BUFFERS that ends the list
 *     P, then P words: the polygon list as the rendering engine received it, in the order it
 *         was given: the number of polygons, the words per polygon, then per polygon gpu3d.c's
 *         capture_polygons record
 *     the I/O registers as stored (0x2000 bytes) and video memory (drive.h's `video`) when the
 *         list was rendered
 *     the rendered frame, 256 x 192 words: red | green << 8 | blue << 16 (6 bits each) |
 *         alpha << 24 (5 bits)
 *
 * gpu3d_capture_write returns 0 when written, 1 when no list has been followed from its start
 * yet, -1 when the file cannot be written. */
void gpu3d_capture_start(void);
int gpu3d_capture_write(const char *path);

/* Counters for the run report: commands, polygons, swaps, render time. */
void gpu3d_report(FILE *out);

#endif
