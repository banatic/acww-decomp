/* Driving a run from another program (tools/drive.py), a few frames at a time.
 *
 * With RUN_DRIVE=1 the run reads commands on stdin and answers on stdout, each answer one
 * line starting with "@ok" or "@err" (the run's other output never starts with "@"):
 *
 *     run N [KEYS [TOUCH]]  let N more frames begin; with KEYS (as in a recording: "-" or
 *                           A+B...) and TOUCH ("-" or x,y), hold that input from now on, and
 *                           drop what the recording (RUN_INPUT) still had to play
 *     frame                 the frame number
 *     png PATH              the last frame output (at frame F, frame F-1), upper screen above
 *                           the lower one
 *     peek ADDR LEN         LEN bytes (up to 64 KiB) in hex: main RAM, ITCM and DTCM (up to
 *                           16 KiB), the I/O registers as stored, palette RAM, VRAM and OAM
 *     redraw PATH [no3d]    the 2D engines draw the frame again from the state now (without
 *                           the 3D layer with no3d), as a PNG
 *     video PATH            the I/O registers as stored, then video memory (VRAM's banks in
 *                           LCDC order, palette RAM, OAM): what the screens are drawn from
 *     log PATH              the input so far as a recording (runtime/input.h): played again
 *                           with RUN_INPUT, it gives the same run
 *     snap                  (POSIX) keep a copy of the run as it is now; answers its id
 *     back ID               (POSIX) end this run and continue the copy (which stays, for
 *                           another back); answers like run
 *     seen PATH             the function entries so far, "address word0 word1" per line (the
 *                           function's first 8 bytes tell an overlay's from another's at
 *                           the same address); needs RUN_DRIVE_STARTS, a file of the
 *                           functions' start addresses in hex
 *     quit                  end the run with its report
 *
 * The run stops for commands at the first input read of a frame (input.c), which is where a
 * recording's line for that frame takes effect: input given at frame F reaches the game as a
 * recording's line "F ..." does, so the log replays exactly. */
#ifndef RUNTIME_DRIVE_H
#define RUNTIME_DRIVE_H

#include <stdint.h>

/* Nonzero when RUN_DRIVE is set (read once). */
int drive_enabled(void);

/* Called by input.c when a frame's input is first read; stops for commands when the frames
 * asked for have begun. */
void drive_frame(uint32_t frame);

/* Called by run.c at every branch target while driving. */
void drive_branch(uint32_t address);

#endif
