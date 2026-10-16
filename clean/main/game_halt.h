/* How the game stops for good (its OS_Terminate): the caller's registers saved as an exception
 * context, interrupts disabled, word 1 sent to the ARM7 on PXI tag 14 (the card's), and, the
 * first time, the debug screen run on that context (debug_screen.h); the stop flag
 * data_021cfb64 (also raised when the card is pulled out, card_pulled.h) then keeps the
 * processor halted. */
#ifndef CLEAN_MAIN_GAME_HALT_H
#define CLEAN_MAIN_GAME_HALT_H

#include "main/debug_screen.h"
#include "types.h"

void GameHalt_SaveContextAndHalt(void);
void GameHalt_Terminate(void);
void GameHalt_Halt(ExceptionContext *context);
void GameHalt_SendToArm7(int data, int wait);
void GameHalt_ShowDebugScreen(ExceptionContext *context, void *launcher);

#endif
