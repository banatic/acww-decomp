/* A latch that stops the game's scenes (data_021dc6c4). Once set, OverlayTask_Update does no
 * more than its loading each frame, the scene process (func_020a529c) asks for scene 0xd4 and
 * deletes itself, func_020a5430 asks for a different scene change, and the deletion
 * (func_020a553c) releases the scene's leftovers with GameStop_Release.
 *
 * GameStop_Update sets it on the first frame the flag data_021fbe38 is set while it was clear
 * the frame before (data_021dc6c8 keeps that). Pad_Update clears data_021fbe38 each frame, just
 * before (func_0206e670); no other writer of it is known. */
#ifndef CLEAN_MAIN_GAME_STOP_H
#define CLEAN_MAIN_GAME_STOP_H

#include "types.h"

void GameStop_Update(void);
void GameStop_Release(void);

#endif
