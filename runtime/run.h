/* What the run (run.c) offers a front end that shows the game as it runs (runtime/play.c). */
#ifndef RUNTIME_RUN_H
#define RUNTIME_RUN_H

#include <stdint.h>

/* The headless program's main: run <rom.nds> <modules.txt> <symbols.txt> [max_instructions]
 * [max_frames], configured by the environment (tools/run.py). A front end built with
 * RUN_FRONT_END has its own main, which sets the environment and calls this one. It returns
 * only on an error before the run starts; the run ends with exit(). */
int run_main(int argc, char **argv);

/* Called on the emulation's thread once per frame, at the first slice boundary after the
 * display clock enters it (`frame` is io_frame's new value): a front end paces the run there
 * and hands over the player's input (input_live). NULL in the headless runs. */
extern void (*run_frame_hook)(uint32_t frame);

#endif
