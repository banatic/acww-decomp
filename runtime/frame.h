/* Frame output: a PNG writer and SHA-1, both dependency-free, for saving and comparing the
 * screens the 2D engines produce (docs/runtime.md, M3: the same recording gives the same
 * frames on every run). */
#ifndef RUNTIME_FRAME_H
#define RUNTIME_FRAME_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Writes `width` x `height` pixels of 0x00RRGGBB as an 8-bit RGB PNG (stored, uncompressed
 * deflate blocks). 0 on success. */
int png_write(const char *path, const uint32_t *pixels, int width, int height);

/* The SHA-1 of `size` bytes as 40 lowercase hex digits plus the terminator in `hex`. */
void sha1_hex(const void *data, size_t size, char hex[41]);

/* The run's frame output, configured from the environment (tools/run.py sets it):
 *   RUN_PNG=<dir>         save chosen frames as <dir>/frame-<n>.png, 256x384 with the upper
 *                         screen above the lower one
 *   RUN_PNG_FRAMES=<list> which frames: n, a-b or a-b/step, comma-separated (every frame
 *                         when unset)
 *   RUN_HASH=<file>|-     write "frame <n> <sha1 upper> <sha1 lower>" for every frame, to a
 *                         file or stdout; the SHA-1s are over the screens' RGB bytes
 * A frame is numbered by the display clock (io_frame) and output when its last visible line
 * is drawn. */
void frame_output_init(void);
void frame_output(uint32_t frame, const uint32_t *upper, const uint32_t *lower);

/* One line for the run report: frames output, PNGs written, and a SHA-1 over every frame's
 * pair of hashes in order, so two runs compare with one line. */
void frame_report(FILE *out);

#endif
