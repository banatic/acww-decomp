/* Overlay 094's display of the wallet (0x1638 bytes), the third of the objects the pockets
 * scenes keep (at 0xde0 of ov096's PocketsScreen, 0xb54 of ov099's PocketsView, 0xd84 of ov105's
 * LetterStorage). It draws on one 2D layer (6, the sub screen's background 3, in every scene)
 * from a screen kept in the object:
 *
 * - the current player's bells as five digits (columns 7 to 11 of rows 10 and 11), which count
 *   towards a new amount over 14 frames with sound 0x2d (PocketsWallet_StartCount), and a
 *   choice of their last three, four or five digits marked in palette 8 (PocketsWallet_MarkDigits);
 * - a rectangle (columns 14 to 23 of rows 3 to 12) in palette 2, 6 or 7 (`frame`), which can
 *   blink (PocketsWallet_StartBlink);
 * - a picture of the player ("menu/inventory/itmp/m%d.bch" or ".../w%d.bch", by the player's
 *   byte 0x1c) chosen by the item the player holds;
 * - the town's and the player's names in two labels.
 *
 * Changes are kept in `dirty` and sent to VRAM from the main loop's queue (main/layer_load_task.h)
 * by PocketsWallet_Update. */
#ifndef CLEAN_OV094_POCKETS_WALLET_H
#define CLEAN_OV094_POCKETS_WALLET_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "types.h"

/* In `dirty`. */
enum PocketsWalletDirty {
    POCKETS_WALLET_DIRTY_SCREEN = 0x1, /* the screen is to be queued */
    POCKETS_WALLET_DIRTY_DIGITS = 0x2, /* the digits are to be written into the screen */
    POCKETS_WALLET_DIRTY_CHARS = 0x4   /* the player's picture is to be queued */
};

/* `frame` and `wanted_frame`: the rectangle's palette. */
enum PocketsWalletFrame {
    POCKETS_WALLET_FRAME_PALETTE_7 = 0,
    POCKETS_WALLET_FRAME_PALETTE_6 = 1,
    POCKETS_WALLET_FRAME_PLAIN = 2 /* palette 2 */
};

#define POCKETS_WALLET_SCREEN_ENTRIES 0x400 /* 32 x 32 */
#define POCKETS_WALLET_PICTURE_SIZE 0xc80
#define POCKETS_WALLET_TASKS 3
#define POCKETS_WALLET_LABELS 2

typedef struct PocketsWallet {
    s32 bells;                                     /* 0x00: the amount shown */
    s32 step;                                      /* 0x04: added or taken each frame while counting */
    u16 dirty;                                     /* 0x08: PocketsWalletDirty */
    u8 unk_0a[4];                                  /* 0x0a */
    u8 layer;                                      /* 0x0e: enum DisplayLayer */
    u8 frame;                                      /* 0x0f: PocketsWalletFrame shown */
    u8 wanted_frame;                               /* 0x10: PocketsWalletFrame to show */
    u8 blink_frame;                                /* 0x11: the frame a blink shows */
    u8 blink_left;                                 /* 0x12: frames of the blink left */
    u8 count_left;                                 /* 0x13: frames of the count left, 0 when not counting */
    u8 picture;                                    /* 0x14: the number of the player's picture (8 until one is loaded) */
    u8 unk_15[0x23];                               /* 0x15 */
    LayerTaskPair tasks[POCKETS_WALLET_TASKS];     /* 0x38: the screen's, the picture's, a third */
    TextLabel labels[POCKETS_WALLET_LABELS];       /* 0xe0: the town's name, the player's name */
    u16 screen[POCKETS_WALLET_SCREEN_ENTRIES];     /* 0x1b8 */
    u8 picture_chars[POCKETS_WALLET_PICTURE_SIZE]; /* 0x9b8 */
} PocketsWallet;

void PocketsWallet_ClearDirty(PocketsWallet *wallet, int bits);
void PocketsWallet_SetDirty(PocketsWallet *wallet, int bits);
int PocketsWallet_TestDirty(PocketsWallet *wallet, int bits);
void PocketsWallet_ShowPlainFrame(PocketsWallet *wallet);
void PocketsWallet_SetFrame(PocketsWallet *wallet, int frame);
void PocketsWallet_ApplyFrame(PocketsWallet *wallet);
void PocketsWallet_UpdateCount(PocketsWallet *wallet);
void PocketsWallet_ResetCount(PocketsWallet *wallet);
int PocketsWallet_PlayerBells(void);
void PocketsWallet_MarkDigits(PocketsWallet *wallet, int choice);
void PocketsWallet_StartCount(PocketsWallet *wallet, int choice);
void PocketsWallet_StopBlink(PocketsWallet *wallet);
int PocketsWallet_StepBlink(PocketsWallet *wallet);
void PocketsWallet_StartBlink(PocketsWallet *wallet, int frame);
void PocketsWallet_Draw(PocketsWallet *wallet, int offset_y);
void PocketsWallet_UpdateNothing(PocketsWallet *wallet);
void PocketsWallet_QueuePicture(PocketsWallet *wallet);
void PocketsWallet_LoadPicture(PocketsWallet *wallet, int picture, int w_set);
void PocketsWallet_LoadHeldItemPicture(PocketsWallet *wallet);
void PocketsWallet_SetFramePalette6(PocketsWallet *wallet);
void PocketsWallet_SetFramePalette7(PocketsWallet *wallet);
void PocketsWallet_SetFramePalette2(PocketsWallet *wallet);
void PocketsWallet_QueueScreen(PocketsWallet *wallet);
void PocketsWallet_CloseLabels(PocketsWallet *wallet);
void PocketsWallet_EndTasks(PocketsWallet *wallet);
void PocketsWallet_Teardown(PocketsWallet *wallet);
void PocketsWallet_Update(PocketsWallet *wallet);
void PocketsWallet_BeginFrame(PocketsWallet *wallet);
int PocketsWallet_LoadObjFiles(PocketsWallet *wallet);
void PocketsWallet_ShowNames(PocketsWallet *wallet);
void PocketsWallet_SetUpContents(PocketsWallet *wallet);
void PocketsWallet_LoadBackground(PocketsWallet *wallet, int screen_a);
void PocketsWallet_SetUp(PocketsWallet *wallet, int screen_a);
void PocketsWallet_Init(PocketsWallet *wallet, u8 layer);
PocketsWallet *PocketsWallet_Destruct(PocketsWallet *wallet);
PocketsWallet *PocketsWallet_Construct(PocketsWallet *wallet);

#endif
