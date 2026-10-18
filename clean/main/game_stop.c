/* The latch that stops the game's scenes (game_stop.h). */
#include "game_stop.h"

#include "clean.h"
#include "music_queue.h" /* Music_Reset */
#include "text_draw.h"   /* TextDraw_ReleaseBoxes */
#include "quick_message.h"

extern u8 data_021dc6c4; /* set: the scenes stop */
extern u8 data_021dc6c8; /* data_021fbe38 was set the frame before */
extern u8 data_021fbe38;

/* func_0209d36c: once a frame, after the pad is read. While the latch is open, a rise of
 * data_021fbe38 closes it; its fall is noted. Once closed nothing changes. */
void GameStop_Update(void)
{
    if (data_021dc6c4 != 0) {
        return;
    }
    if (data_021dc6c8 != 0) {
        if (data_021fbe38 == 0) {
            data_021dc6c8 = 0;
        }
    } else if (data_021fbe38 != 0) {
        data_021dc6c4 = 1;
        data_021dc6c8 = 1;
    }
}
CLEAN_AS(func_0209d36c, GameStop_Update)

/* func_0209dad0: what a stopped scene leaves released: func_020397f0, the music reset and the
 * text boxes released. */
void GameStop_Release(void)
{
    QuickMessage_ResetCurrent();
    Music_Reset();
    TextDraw_ReleaseBoxes();
}
CLEAN_AS(func_0209dad0, GameStop_Release)
