/* The two 2D graphics engines and the frame output.
 *
 * Each engine draws one scanline at a time, at the point where the hardware enters HBlank
 * for that line, from the registers, palettes, OAM and VRAM as they are at that moment.
 * The HBlank interrupt handler then runs and may change registers for the next line, which
 * is why the line is drawn before the interrupt is raised (io.c calls gpu2d_line from its
 * display clock). When VCOUNT reaches 192 the frame is complete and both screens are
 * converted to 8-bit RGB (gpu2d_frame_end).
 *
 * Colours inside the engines are the hardware's 18-bit values (6 bits per channel) so that
 * blending and brightness round as the hardware does (GBATEK, "DS Video"). The register
 * semantics follow GBATEK; comments name the rule where the behaviour is not obvious.
 */
#ifndef RUNTIME_GPU2D_H
#define RUNTIME_GPU2D_H

#include <stdint.h>

#define GPU2D_WIDTH 256
#define GPU2D_HEIGHT 192

void gpu2d_init(void);

/* Draws line `y` (0..191) of both engines; asked for by io.c when HBlank starts (render.c). */
void gpu2d_line(uint32_t y);

/* VCOUNT reached 192 in frame `frame`: the frame is complete. gpu2d_frame_output converts the
 * screens, applies the display swap (POWCNT1 bit 15) and hands the screens to the frame
 * output (frame.h), which saves and hashes the frames the run asked for; gpu2d_capture_end
 * ends a display capture (render.c calls both). */
void gpu2d_frame_output(uint32_t frame);
void gpu2d_capture_end(void);

/* io.c reports a write to a display register at `offset` (0x04000000 + offset): the affine
 * reference points (BGxX, BGxY) reload on a write, the display FIFO takes words. */
void gpu2d_register_written(uint32_t offset, uint32_t value);

/* Frames completed since the start, and the two finished screens as 256x192 pixels of
 * 0x00RRGGBB. `top` selects the screen on the upper LCD (1) or the lower LCD (0). */
uint32_t gpu2d_frames(void);
const uint32_t *gpu2d_screen(int top);

/* BG0's 3D layer is read from gpu3d_line and gpu3d_line_alpha (runtime/gpu3d.h). */

#endif
