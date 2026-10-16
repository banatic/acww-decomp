/* The backdrop behind the menus that overlays 90 and 92 open (the pockets among them): a tiled
 * picture on background 2 of each engine, brought in and out in thirteen steps run once a
 * frame (MenuBackdrop_Update) while it scrolls diagonally.
 *
 * The picture is "menu/inventory/b_itm_back.bsc" with the characters and palette either of
 * "menu/bas/b_bas_<n>.bch"/".bpl" (style n, 0 to 3) or, in style 4, of the piece of clothing
 * the player put there (items 0x11a8-0x12af; the item at 0x2410 of the player's record, set
 * by MenuBackdrop_QueueDesign), its palette lightened halfway to white.
 *
 * Opening (MenuBackdrop_Open, style 4 unless the menu sets another): the picture is loaded on
 * the main engine and swept in from the right by window 1, whose left edge, one per line in a
 * pattern of 48 lines (itcm/line_effects.h), a line handler moves 20 pixels a frame. Then,
 * once the camera stands still, the picture is loaded on the sub engine, the screens are
 * swapped (POWCNT1's swap bit, display_frame.c) and the state flags' value (state_flags.h)
 * eases from 0 to 1. Closing (MenuBackdrop_Close) runs it backwards: the value eases back to
 * 0 and, once the menu lets go of the hold closing sets (MenuBackdrop_ReleaseClose), the
 * screens are swapped back and, once the camera is back in its previous mode, the picture is
 * swept out to the right. */
#ifndef CLEAN_MAIN_MENU_BACKDROP_H
#define CLEAN_MAIN_MENU_BACKDROP_H

#include "layer_load_task.h"
#include "types.h"

/* data_021cfc20: the step; the handlers are data_020df2a4's. */
enum MenuBackdropState {
    MENU_BACKDROP_IDLE = 0,
    MENU_BACKDROP_LOAD_MAIN = 1, /* loading the main engine's picture */
    MENU_BACKDROP_WIPE_IN = 2,   /* sweeping it in */
    MENU_BACKDROP_STILL = 3,     /* waiting for the camera to stand still */
    MENU_BACKDROP_LOAD_SUB = 4,  /* loading the sub engine's picture */
    MENU_BACKDROP_EASE_IN = 5,   /* the value going to 1 */
    MENU_BACKDROP_SHOW = 6,      /* the windows put away */
    MENU_BACKDROP_OPEN = 7,
    MENU_BACKDROP_CLOSE = 8,     /* closing begun */
    MENU_BACKDROP_EASE_OUT = 9,  /* the value going to 0 */
    MENU_BACKDROP_RESTORE = 10,  /* waiting for the camera's previous mode */
    MENU_BACKDROP_WIPE_OUT = 11, /* sweeping the picture out */
    MENU_BACKDROP_CLOSED = 12,
    MENU_BACKDROP_STATES = 13
};

/* data_021cfc10: the picture's style. */
#define MENU_BACKDROP_STYLE_CLOTHING 4

/* data_021cfc0c: holds; hold 1, set as closing begins, keeps it at its ease-out step. */
#define MENU_BACKDROP_HOLD_CLOSE 0x01

void MenuBackdrop_SetStyle(char style);
int MenuBackdrop_IsHeld(int mask);
void MenuBackdrop_Release(unsigned int mask);
void MenuBackdrop_Hold(unsigned char mask);
void MenuBackdrop_LightenPalette(u16 *source, u16 *lightened);
int MenuBackdrop_StepWipeOut(void);
int MenuBackdrop_StepRestore(void);
int MenuBackdrop_StepEaseOut(void);
int MenuBackdrop_StepClose(void);
int MenuBackdrop_StepShow(void);
int MenuBackdrop_StepEaseIn(void);
int MenuBackdrop_StepLoadSub(void);
int MenuBackdrop_StepStill(void);
int MenuBackdrop_StepWipeIn(void);
int MenuBackdrop_StepLoadMain(void);
int MenuBackdrop_StepStay(void);
int MenuBackdrop_StepIdle(void);
void MenuBackdrop_Update(void);
void MenuBackdrop_End(void);
void MenuBackdrop_Reset(void);
void MenuBackdrop_ReleaseClose(void);
void MenuBackdrop_Open(void);
void MenuBackdrop_Close(void);
int MenuBackdrop_LoadLayer(int layer);
int MenuBackdrop_LoadFiles(int layer);
void MenuBackdrop_SetUpSubLayer(void);
void MenuBackdrop_SetUpMainLayer(void);
void MenuBackdrop_QueueDesign(u16 *item, LayerTaskPair *task, u8 *chars, u16 *palette);
int MenuBackdrop_IsClosed(void);
int MenuBackdrop_IsUp(void);
int MenuBackdrop_IsWiping(void);
void MenuBackdrop_BeginWipeOut(void);
void MenuBackdrop_BeginWipeIn(void);
void MenuBackdrop_StopWipe(void);
void MenuBackdrop_WipeOutFrame(void);
void MenuBackdrop_WipeInFrame(void);

#endif
