/* Drawing on a second thread.
 *
 * The display clock (io.c) asks for a line at each HBlank, for the end of a frame at VBlank
 * and for a 3D frame at a swap; the renderers (gpu2d.c, gpu3d.c) read the registers, palettes,
 * OAM and VRAM as they are at that moment. With the thread, each request goes into a queue
 * together with what changed in that state since the request before (the display and 3D
 * registers whole, the video memory by the 256-byte pieces written), and the thread keeps its
 * own copy of that state up to date from the queue: each line is drawn from exactly what it
 * would have read, while the emulation goes on. A frame with a display capture (DISPCAPCNT),
 * which writes VRAM the CPU reads back, is drawn where it is asked for, the thread idle.
 *
 * RUN_RENDER_THREAD=0 in the environment turns the thread off: the requests are then drawn
 * at once, as they are when RUN_DUMP3D or RUN_TRACE=gx (which print from the renderer) are
 * set. The frames are the same either way.
 */
#ifndef RUNTIME_RENDER_H
#define RUNTIME_RENDER_H

#include <stdint.h>
#include <stdio.h>

/* Starts the thread unless the environment says otherwise (above). */
void render_init(void);

/* The display clock's requests (io.c): line `y` of both 2D engines at the start of its
 * HBlank, the frame complete (VCOUNT 192, frame number `frame`), a write to a display
 * register (gpu2d_register_written's events), and the 3D frame of a swap (list `list`). */
void render_line(uint32_t y);
void render_frame_end(uint32_t frame);
void render_register_written(uint32_t offset, uint32_t value);
void render_3d(int list);

/* Everything asked for is drawn and output: before the run's report, and at exit. */
void render_finish(void);

/* With the thread: how many frames it drew, and how many were drawn here. */
void render_report(FILE *out);

#endif
