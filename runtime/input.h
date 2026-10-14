/* The player's input, from a recording: the buttons as KEYINPUT and the ARM7's KEYXY see
 * them, and the touch panel as the ARM7 samples it.
 *
 * A recording is a text file with one line per change of state:
 *
 *     <frame> <keys> <touch>
 *
 * `frame` is the frame number the state takes effect at (frames are counted by the display
 * clock from the start of the run); `keys` is `-` for nothing held or button names joined
 * by `+` (A B SELECT START RIGHT LEFT UP DOWN R L X Y); `touch` is `-` for the pen up or
 * `x,y` in screen pixels of the lower screen. Lines starting with `#` are comments. The
 * state holds until the next line, so a press is two lines: one holding the key, one
 * releasing it.
 */
#ifndef RUNTIME_INPUT_H
#define RUNTIME_INPUT_H

#include <stdint.h>

/* Loads a recording; 0 on success. Without one, nothing is ever pressed. */
int input_load(const char *path);

/* Moves the state to `frame` (frames only advance). The readers below do this themselves
 * with the display clock's frame number, so the state a register shows depends only on the
 * emulated time, never on when the host asks. */
void input_frame(uint32_t frame);

/* The buttons held now as KEYINPUT bits 0-9 (1 = held; the register inverts them), and X
 * and Y as the ARM7's KEYXY bits 0-1 (1 = held). */
uint32_t input_keys(void);
uint32_t input_keys_xy(void);

/* The pen: nonzero when touching, with the screen position. */
int input_touch(int *x, int *y);

#endif
