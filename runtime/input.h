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
 * releasing it. Three more names are the console's, not buttons: LID while the lid is closed,
 * LOWBAT while the battery is low, NORADIO while the wireless hears and sends nothing (out of
 * range of the other console; input_hardware), and BEACONLOSS as NORADIO, except that both
 * consoles' radios notice it: a connection held that long ends (runtime/wm.c).
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

/* The console's state the recording holds: bit 0 the lid closed (LID), bit 1 the battery low
 * (LOWBAT), bit 2 the radio out of range (NORADIO), bit 3 out of range with the beacon's loss
 * noticed (BEACONLOSS). Only a recording sets them (not input_live). */
uint32_t input_hardware(void);

/* The pen: nonzero when touching, with the screen position. */
int input_touch(int *x, int *y);

/* For tools/drive.py (drive.h): hold `keys` and `touch` (as in a recording) from `frame` on,
 * dropping what the recording still had to play; 0 on success. And the input applied so far,
 * as a recording; 0 on success. */
int input_drive_set(uint32_t frame, const char *keys, const char *touch);
int input_write_log(const char *path);

/* Live input from a front end (runtime/play.c), held on top of the recording: `keys` in the
 * recording's bits (0-9 as KEYINPUT, 10-11 X and Y) are added to the recording's, and a pen
 * down here (`touch` nonzero, x,y on the lower screen) takes the place of the recording's.
 * The front end sets it at the start of a frame, so what the game reads still depends only on
 * the emulated time. Without a call nothing is added. */
void input_live(uint32_t keys, int touch, int x, int y);

#endif
