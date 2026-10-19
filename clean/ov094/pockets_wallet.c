/* Overlay 094's display of the wallet (pockets_wallet.h). */
#include "pockets_wallet.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/c_library.h"
#include "main/display_layers.h"
#include "main/message_reader.h"
#include "main/player_id.h"
#include "main/player_pockets.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/screen_map.h"
#include "main/sound.h"
#include "main/text_base.h"
#include "main/town_name.h"

static_assert(offsetof(PocketsWallet, dirty) == 0x08 && offsetof(PocketsWallet, layer) == 0x0e, "wallet");
static_assert(offsetof(PocketsWallet, count_left) == 0x13 && offsetof(PocketsWallet, picture) == 0x14, "wallet");
static_assert(sizeof(LayerTaskPair) == 0x38 && offsetof(PocketsWallet, tasks) == 0x38, "wallet tasks");
static_assert(sizeof(TextLabel) == 0x6c && offsetof(PocketsWallet, labels) == 0xe0, "wallet labels");
static_assert(offsetof(PocketsWallet, screen) == 0x1b8 && offsetof(PocketsWallet, picture_chars) == 0x9b8, "wallet");
static_assert(sizeof(PocketsWallet) == 0x1638, "wallet size");
static_assert(sizeof(TownNameText) == 0x20 && sizeof(PlayerIdText) == 0x20, "texts");

/* The heap the scenes load into (autoload_2/heap.c). */
extern Heap *data_021fbe94;

/* The label's constructor and destructor, handed to the vector helpers as the game's own. */
extern void func_02070c08(void *label);
extern void func_02070be8(void *label);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The player's pictures ("menu/inventory/itmp/m%d.bch", "menu/inventory/itmp/w%d.bch"). */
extern const char data_ov094_0229be20[];
extern const char data_ov094_0229be3c[];
/* The OBJ files ("menu/inventory/b_obj_itm.bpl", "menu/icon/b_obj_itm.bpl",
 * "menu/inventory/obj0.bch", "menu/inventory/obj1.bch"). */
extern const char data_ov094_0229be58[];
extern const char data_ov094_0229be78[];
extern const char data_ov094_0229be90[];
extern const char data_ov094_0229bea8[];
/* "menu/inventory/b_itm2.bch" */
extern const char data_ov094_0229bec0[];
/* The background ("menu/inventory/b_itm.bpl", "menu/inventory/b_itm_bg_a.bsc",
 * "menu/inventory/b_itm_bg_c.bsc", "menu/inventory/b_itm0.bch", "menu/inventory/b_itm1.bch"). */
extern const char data_ov094_0229bedc[];
extern const char data_ov094_0229bef8[];
extern const char data_ov094_0229bf18[];
extern const char data_ov094_0229bf38[];
extern const char data_ov094_0229bf54[];

#define POCKETS_WALLET_DIGITS 5
#define POCKETS_WALLET_DIGIT_ROW 10
#define POCKETS_WALLET_DIGIT_LAST_COLUMN 11
#define POCKETS_WALLET_DIGIT_TOP_TILE 0x2d8 /* + 2 * digit; the bottom half is the next tile */
#define POCKETS_WALLET_TILE_KEEP 0xfc00     /* the palette and the flips */
#define POCKETS_WALLET_COUNT_FRAMES 14
#define POCKETS_WALLET_COUNT_SHORT 30 /* a smaller change ends at the next frame */
#define POCKETS_WALLET_COUNT_STEPS 13
#define POCKETS_WALLET_BLINK_FRAMES 14
#define POCKETS_WALLET_SOUND_COUNT 0x2d
#define POCKETS_WALLET_SOUND_COUNTED 0x3e
#define POCKETS_WALLET_NO_PICTURE 8
#define POCKETS_WALLET_SCREEN_BYTES 0x800
#define POCKETS_WALLET_MESSAGE_TOWN 102

#define WALLET_TASK_SCREEN 0
#define WALLET_TASK_PICTURE 1

static int screen_address(PocketsWallet *wallet)
{
    return (int) (uintptr_t) wallet->screen;
}

/* func_ov094_022999a0 */
void PocketsWallet_ClearDirty(PocketsWallet *wallet, int bits)
{
    wallet->dirty &= (u16) ~bits;
}
CLEAN_AS(func_ov094_022999a0, PocketsWallet_ClearDirty)

/* func_ov094_022999a8 */
void PocketsWallet_SetDirty(PocketsWallet *wallet, int bits)
{
    wallet->dirty |= (u16) bits;
}
CLEAN_AS(func_ov094_022999a8, PocketsWallet_SetDirty)

/* func_ov094_022999b0 */
int PocketsWallet_TestDirty(PocketsWallet *wallet, int bits)
{
    return (wallet->dirty & bits) != 0;
}
CLEAN_AS(func_ov094_022999b0, PocketsWallet_TestDirty)

/* func_ov094_02299ac4 */
void PocketsWallet_ShowPlainFrame(PocketsWallet *wallet)
{
    wallet->wanted_frame = POCKETS_WALLET_FRAME_PLAIN;
}
CLEAN_AS(func_ov094_02299ac4, PocketsWallet_ShowPlainFrame)

/* func_ov094_02299acc */
void PocketsWallet_SetFrame(PocketsWallet *wallet, int frame)
{
    wallet->wanted_frame = (u8) frame;
}
CLEAN_AS(func_ov094_02299acc, PocketsWallet_SetFrame)

/* func_ov094_02299ad0: a change of the wanted frame drawn: the rectangle in palette 2, then
 * in 7 or 6 for frames 0 and 1. */
void PocketsWallet_ApplyFrame(PocketsWallet *wallet)
{
    if (wallet->wanted_frame == wallet->frame) {
        return;
    }
    wallet->frame = wallet->wanted_frame;
    PocketsWallet_SetFramePalette2(wallet);
    switch (wallet->frame) {
        case POCKETS_WALLET_FRAME_PALETTE_7:
            PocketsWallet_SetFramePalette7(wallet);
            break;
        case POCKETS_WALLET_FRAME_PALETTE_6:
            PocketsWallet_SetFramePalette6(wallet);
            break;
    }
}
CLEAN_AS(func_ov094_02299ad0, PocketsWallet_ApplyFrame)

/* func_ov094_02299b74: a frame of the count, then the digits written when they changed.
 * While counting, the amount moves by `step` towards the player's bells each frame, and the
 * last frame sets it to them, unmarks the digits, stops sound 0x2d and plays 0x3e. QUIRK: the
 * amount moves down whenever it is not below the bells, also when it equals them. The digits
 * are the amount's last five, units at column 11. */
void PocketsWallet_UpdateCount(PocketsWallet *wallet)
{
    int bells = PocketsWallet_PlayerBells();

    if (wallet->count_left != 0) {
        wallet->count_left--;
        if (wallet->count_left == 0) {
            wallet->bells = bells;
            PocketsWallet_MarkDigits(wallet, 0);
            SoundSys_StopSound(POCKETS_WALLET_SOUND_COUNT, 1);
            SoundSys_PlaySe(POCKETS_WALLET_SOUND_COUNTED);
        } else if (wallet->bells >= bells) {
            wallet->bells -= wallet->step;
        } else {
            wallet->bells += wallet->step;
        }
        PocketsWallet_SetDirty(wallet, POCKETS_WALLET_DIRTY_DIGITS);
    }

    if (PocketsWallet_TestDirty(wallet, POCKETS_WALLET_DIRTY_DIGITS) != 0) {
        int value = wallet->bells;
        int column = POCKETS_WALLET_DIGIT_LAST_COLUMN;

        PocketsWallet_SetDirty(wallet, POCKETS_WALLET_DIRTY_SCREEN);
        for (int i = 0; i < POCKETS_WALLET_DIGITS; i++, column--) {
            int tile = POCKETS_WALLET_DIGIT_TOP_TILE + value % 10 * 2;
            u16 *top = &wallet->screen[POCKETS_WALLET_DIGIT_ROW * 32 + column];
            u16 *bottom = top + 32;

            *top = (u16) ((*top & POCKETS_WALLET_TILE_KEEP) | tile);
            *bottom = (u16) ((*bottom & POCKETS_WALLET_TILE_KEEP) | (tile + 1));
            value /= 10;
        }
        PocketsWallet_ClearDirty(wallet, POCKETS_WALLET_DIRTY_DIGITS);
    }
}
CLEAN_AS(func_ov094_02299b74, PocketsWallet_UpdateCount)

/* func_ov094_02299c40: the amount set to the player's bells at once, the count stopped. */
void PocketsWallet_ResetCount(PocketsWallet *wallet)
{
    wallet->bells = PocketsWallet_PlayerBells();
    wallet->count_left = 0;
    PocketsWallet_SetDirty(wallet, POCKETS_WALLET_DIRTY_DIGITS);
}
CLEAN_AS(func_ov094_02299c40, PocketsWallet_ResetCount)

/* func_ov094_02299c5c: the current player's bells, without their bags. */
int PocketsWallet_PlayerBells(void)
{
    return PlayerPockets_Bells(PlayerRecord_Pockets(PlayerRecords_Current()), 0);
}
CLEAN_AS(func_ov094_02299c5c, PocketsWallet_PlayerBells)

/* func_ov094_02299c74: choice 1, 2 or 3 gives the last three, four or five digits palette 8;
 * any other choice gives all five palette 9 (unmarked). QUIRK: a choice only paints its own
 * digits, so going from 3 to 1 leaves the first two in palette 8. */
void PocketsWallet_MarkDigits(PocketsWallet *wallet, int choice)
{
    int left = 7;
    u32 palette = 9;

    switch (choice) {
        case 1:
            left = 9;
            palette = 8;
            break;
        case 2:
            left = 8;
            palette = 8;
            break;
        case 3:
            palette = 8;
            break;
    }
    ScreenMap_SetPalette(wallet->screen, left, POCKETS_WALLET_DIGIT_ROW, POCKETS_WALLET_DIGIT_LAST_COLUMN,
                         POCKETS_WALLET_DIGIT_ROW + 1, palette);
    PocketsWallet_SetDirty(wallet, POCKETS_WALLET_DIRTY_SCREEN);
}
CLEAN_AS(func_ov094_02299c74, PocketsWallet_MarkDigits)

/* func_ov094_02299cd0: a count towards the player's bells started, when they differ from the
 * amount shown. A difference below 30 ends at the next frame (with the end of the count's
 * stop and sound 0x3e), the digits unmarked and sound 0x2d not started; a larger one
 * counts over 14 frames by a thirteenth of it (one less when that is a multiple of 5, so that
 * the units roll), with the digits of `choice` marked and sound 0x2d started. QUIRK: a step
 * of 1 or less (which a difference of 30 or more cannot give) would also end the count at the
 * next frame, still marked and with the sound. */
void PocketsWallet_StartCount(PocketsWallet *wallet, int choice)
{
    int bells = PocketsWallet_PlayerBells();
    int difference;

    if (bells == wallet->bells) {
        return;
    }
    difference = bells > wallet->bells ? bells - wallet->bells : wallet->bells - bells;
    if (difference < POCKETS_WALLET_COUNT_SHORT) {
        wallet->count_left = 1;
        return;
    }
    wallet->count_left = POCKETS_WALLET_COUNT_FRAMES;
    wallet->step = difference / POCKETS_WALLET_COUNT_STEPS;
    if (wallet->step % 5 == 0) {
        wallet->step--;
    }
    if (wallet->step <= 1) {
        wallet->count_left = 1;
    }
    PocketsWallet_MarkDigits(wallet, choice);
    SoundSys_StartOnHandle38(POCKETS_WALLET_SOUND_COUNT);
}
CLEAN_AS(func_ov094_02299cd0, PocketsWallet_StartCount)

/* func_ov094_02299d34: the blink stopped, the plain frame wanted. */
void PocketsWallet_StopBlink(PocketsWallet *wallet)
{
    wallet->blink_left = 0;
    PocketsWallet_ShowPlainFrame(wallet);
}
CLEAN_AS(func_ov094_02299d34, PocketsWallet_StopBlink)

/* func_ov094_02299d40: a frame of the blink; 1 when it is over (nothing left), else 0. Of
 * every five frames left, the one leaving 3 wants the blink's frame and the one leaving 0 the
 * plain frame. */
int PocketsWallet_StepBlink(PocketsWallet *wallet)
{
    if (wallet->blink_left == 0) {
        return 1;
    }
    wallet->blink_left--;
    switch (wallet->blink_left % 5) {
        case 3:
            PocketsWallet_SetFrame(wallet, wallet->blink_frame);
            break;
        case 0:
            PocketsWallet_ShowPlainFrame(wallet);
            break;
    }
    return 0;
}
CLEAN_AS(func_ov094_02299d40, PocketsWallet_StepBlink)

/* func_ov094_02299d7c: a blink of `frame` started, 14 frames. */
void PocketsWallet_StartBlink(PocketsWallet *wallet, int frame)
{
    wallet->blink_frame = (u8) frame;
    wallet->blink_left = POCKETS_WALLET_BLINK_FRAMES;
}
CLEAN_AS(func_ov094_02299d7c, PocketsWallet_StartBlink)

/* func_ov094_02299d84: the scenes' draw at a vertical offset; the wallet has no OBJs and
 * draws nothing. */
void PocketsWallet_Draw(PocketsWallet *wallet, int offset_y)
{
    (void) wallet;
    (void) offset_y;
}
CLEAN_AS(func_ov094_02299d84, PocketsWallet_Draw)

/* func_ov094_02299d88: the last step of PocketsWallet_Update, which does nothing. */
void PocketsWallet_UpdateNothing(PocketsWallet *wallet)
{
    (void) wallet;
}
CLEAN_AS(func_ov094_02299d88, PocketsWallet_UpdateNothing)

/* func_ov094_02299d8c: a changed picture queued as characters 0x35-0x98 of the layer; it
 * stays dirty until the queue takes it. */
void PocketsWallet_QueuePicture(PocketsWallet *wallet)
{
    if (PocketsWallet_TestDirty(wallet, POCKETS_WALLET_DIRTY_CHARS) != 0) {
        if (LayerTask_QueueChars(&wallet->tasks[WALLET_TASK_PICTURE].first, (int) (uintptr_t) wallet->picture_chars,
                                 wallet->layer, 0x35, 0x35, 0x98) != 0) {
            PocketsWallet_ClearDirty(wallet, POCKETS_WALLET_DIRTY_CHARS);
        }
    }
}
CLEAN_AS(func_ov094_02299d8c, PocketsWallet_QueuePicture)

/* func_ov094_02299dcc: picture `picture` read (the "m" set, or the "w" set when `w_set` is
 * not 0) and marked to be queued. */
void PocketsWallet_LoadPicture(PocketsWallet *wallet, int picture, int w_set)
{
    char path[0x2c];

    if (w_set == 0) {
        CLib_SPrintf(path, data_ov094_0229be20, picture);
    } else {
        CLib_SPrintf(path, data_ov094_0229be3c, picture);
    }
    RomFile_Read(path, wallet->picture_chars, POCKETS_WALLET_PICTURE_SIZE);
    wallet->picture = (u8) picture;
    PocketsWallet_SetDirty(wallet, POCKETS_WALLET_DIRTY_CHARS);
}
CLEAN_AS(func_ov094_02299dcc, PocketsWallet_LoadPicture)

/* func_ov094_02299e1c: the picture of the item the current player holds loaded, in the set of
 * the player's byte 0x1c: 1 for items 0x1369-0x136a, 2 for 0x136b-0x1373, 3 for
 * 0x1374-0x1375, 4 for 0x1380-0x13a7, 5 for 0x1376-0x1377, 6 for 0x1378-0x1379, 7 for
 * 0x137a-0x137b, 0 for any other. */
void PocketsWallet_LoadHeldItemPicture(PocketsWallet *wallet)
{
    u8 *record = PlayerRecords_Current();
    int w_set = PlayerId_Byte1c((const s8 *) PlayerRecord_Player(record));
    unsigned int item = *PlayerRecord_HeldItem(record);
    int picture = 0;

    if (item >= 0x1369 && item <= 0x136a) {
        picture = 1;
    } else if (item >= 0x136b && item <= 0x1373) {
        picture = 2;
    } else if (item >= 0x1374 && item <= 0x1375) {
        picture = 3;
    } else if (item >= 0x1380 && item <= 0x13a7) {
        picture = 4;
    } else if (item >= 0x1376 && item <= 0x1377) {
        picture = 5;
    } else if (item >= 0x1378 && item <= 0x1379) {
        picture = 6;
    } else if (item >= 0x137a && item <= 0x137b) {
        picture = 7;
    }
    PocketsWallet_LoadPicture(wallet, picture, w_set);
}
CLEAN_AS(func_ov094_02299e1c, PocketsWallet_LoadHeldItemPicture)

/* The rectangle of the frame: columns 14 to 23, rows 3 to 12. */
static void paint_frame(PocketsWallet *wallet, u32 palette)
{
    ScreenMap_SetPalette(wallet->screen, 14, 3, 23, 12, palette);
}

/* func_ov094_02299f40: the frame in palette 6 (not marked dirty). */
void PocketsWallet_SetFramePalette6(PocketsWallet *wallet)
{
    paint_frame(wallet, 6);
}
CLEAN_AS(func_ov094_02299f40, PocketsWallet_SetFramePalette6)

/* func_ov094_02299f64: the frame in palette 7 (not marked dirty). */
void PocketsWallet_SetFramePalette7(PocketsWallet *wallet)
{
    paint_frame(wallet, 7);
}
CLEAN_AS(func_ov094_02299f64, PocketsWallet_SetFramePalette7)

/* func_ov094_02299f88: the frame in palette 2, the screen marked to be queued. */
void PocketsWallet_SetFramePalette2(PocketsWallet *wallet)
{
    paint_frame(wallet, 2);
    PocketsWallet_SetDirty(wallet, POCKETS_WALLET_DIRTY_SCREEN);
}
CLEAN_AS(func_ov094_02299f88, PocketsWallet_SetFramePalette2)

/* func_ov094_02299fb8: a changed screen queued; it stays dirty until the queue takes it. */
void PocketsWallet_QueueScreen(PocketsWallet *wallet)
{
    if (PocketsWallet_TestDirty(wallet, POCKETS_WALLET_DIRTY_SCREEN) != 0) {
        if (LayerTask_QueueScreen(&wallet->tasks[WALLET_TASK_SCREEN].first, screen_address(wallet), wallet->layer,
                                  POCKETS_WALLET_SCREEN_BYTES, 0) != 0) {
            PocketsWallet_ClearDirty(wallet, POCKETS_WALLET_DIRTY_SCREEN);
        }
    }
}
CLEAN_AS(func_ov094_02299fb8, PocketsWallet_QueueScreen)

/* func_ov094_02299ff8 */
void PocketsWallet_CloseLabels(PocketsWallet *wallet)
{
    for (int i = 0; i < POCKETS_WALLET_LABELS; i++) {
        TextLabel_CloseBox(&wallet->labels[i]);
    }
}
CLEAN_AS(func_ov094_02299ff8, PocketsWallet_CloseLabels)

/* func_ov094_0229a018 */
void PocketsWallet_EndTasks(PocketsWallet *wallet)
{
    for (int i = 0; i < POCKETS_WALLET_TASKS; i++) {
        LayerTask_End(&wallet->tasks[i].first);
    }
}
CLEAN_AS(func_ov094_0229a018, PocketsWallet_EndTasks)

/* func_ov094_0229a038: the tasks ended and the labels closed before the scene closes; a count
 * still running has its sound stopped. */
void PocketsWallet_Teardown(PocketsWallet *wallet)
{
    PocketsWallet_EndTasks(wallet);
    PocketsWallet_CloseLabels(wallet);
    if (wallet->count_left != 0) {
        SoundSys_StopSound(POCKETS_WALLET_SOUND_COUNT, 1);
    }
}
CLEAN_AS(func_ov094_0229a038, PocketsWallet_Teardown)

/* func_ov094_0229a05c: the end of a frame: the count, the frame, then the screen and the
 * picture queued. */
void PocketsWallet_Update(PocketsWallet *wallet)
{
    PocketsWallet_UpdateCount(wallet);
    PocketsWallet_ApplyFrame(wallet);
    PocketsWallet_QueueScreen(wallet);
    PocketsWallet_QueuePicture(wallet);
    PocketsWallet_UpdateNothing(wallet);
}
CLEAN_AS(func_ov094_0229a05c, PocketsWallet_Update)

/* func_ov094_0229a084: the start of a frame: last frame's tasks ended, the labels closed. */
void PocketsWallet_BeginFrame(PocketsWallet *wallet)
{
    PocketsWallet_EndTasks(wallet);
    PocketsWallet_CloseLabels(wallet);
}
CLEAN_AS(func_ov094_0229a084, PocketsWallet_BeginFrame)

/* func_ov094_0229a098: the sub screen's OBJ palettes 4-6 and 7-14 and characters 0xc0-0x1ff
 * loaded from their files; the answer of the last load. */
int PocketsWallet_LoadObjFiles(PocketsWallet *wallet)
{
    Heap *heap = data_021fbe94;

    (void) wallet;
    DisplayLayer_LoadPalettesFromFile(data_ov094_0229be58, heap, LAYER_SUB_OBJ, 4, 4, 6);
    DisplayLayer_LoadPalettesFromFile(data_ov094_0229be78, heap, LAYER_SUB_OBJ, 7, 7, 0xe);
    DisplayLayer_LoadCharsFromFile(data_ov094_0229be90, heap, LAYER_SUB_OBJ, 0xc0, 0xc0, 0x15f);
    return DisplayLayer_LoadCharsFromFile(data_ov094_0229bea8, heap, LAYER_SUB_OBJ, 0x160, 0x160, 0x1ff);
}
CLEAN_AS(func_ov094_0229a098, PocketsWallet_LoadObjFiles)

/* func_ov094_0229a110: the labels shown: the current player's town in menu message 102 (as
 * message part 0) and the player's name. */
void PocketsWallet_ShowNames(PocketsWallet *wallet)
{
    TownNameText town;
    PlayerIdText name;
    DesignCreator *player = PlayerRecord_Player(PlayerRecords_Current());
    TextLabel *town_label = &wallet->labels[0];
    TextLabel *name_label = &wallet->labels[1];

    TownNameText_Construct(&town);
    TownName_ToText(PlayerId_Town(player), (TextBase *) &town);
    MessageReader_SetPart(0, (int) (uintptr_t) &town);
    TextLabel_OpenStyledBox2(town_label, wallet->layer, 17, 10, 15, 12, 0);
    TextLabel_LoadMenuMessage(town_label, POCKETS_WALLET_MESSAGE_TOWN);
    TextLabel_Show(town_label, 1, 0);

    PlayerIdText_Construct(&name);
    PlayerId_NameToText(player, (TextBase *) &name);
    TextLabel_OpenStyledBox2(name_label, wallet->layer, 37, 8, 15, 12, 0);
    TextBase_Copy((TextBase *) name_label, (TextBase *) &name);
    TextLabel_Show(name_label, 1, 0);

    PlayerIdText_Destruct(&name);
    TownNameText_Destruct(&town);
}
CLEAN_AS(func_ov094_0229a110, PocketsWallet_ShowNames)

/* func_ov094_0229a1c0: the second step of the setup: characters 0x200-0x2ff of the layer, the
 * names, the amount and the player's picture. */
void PocketsWallet_SetUpContents(PocketsWallet *wallet)
{
    DisplayLayer_LoadCharsFromFile(data_ov094_0229bec0, data_021fbe94, wallet->layer, 0x200, 0x200, 0x2ff);
    PocketsWallet_ShowNames(wallet);
    PocketsWallet_ResetCount(wallet);
    PocketsWallet_LoadHeldItemPicture(wallet);
}
CLEAN_AS(func_ov094_0229a1c0, PocketsWallet_SetUpContents)

/* func_ov094_0229a204: the first step of the setup: the layer's palettes 1-13, its screen
 * (read into the object from "b_itm_bg_a.bsc" when `screen_a` is not 0, else "b_itm_bg_c.bsc")
 * and characters 0x10-0x1ff. */
void PocketsWallet_LoadBackground(PocketsWallet *wallet, int screen_a)
{
    Heap *heap = data_021fbe94;

    DisplayLayer_LoadPalettesFromFile(data_ov094_0229bedc, heap, wallet->layer, 0, 1, 13);
    RomFile_Read(screen_a != 0 ? data_ov094_0229bef8 : data_ov094_0229bf18, wallet->screen, POCKETS_WALLET_SCREEN_BYTES);
    DisplayLayer_LoadScreen(wallet->screen, wallet->layer, POCKETS_WALLET_SCREEN_BYTES, 0);
    DisplayLayer_LoadCharsFromFile(data_ov094_0229bf38, heap, wallet->layer, 0, 0x10, 0xff);
    DisplayLayer_LoadCharsFromFile(data_ov094_0229bf54, heap, wallet->layer, 0x100, 0x100, 0x1ff);
}
CLEAN_AS(func_ov094_0229a204, PocketsWallet_LoadBackground)

/* func_ov094_0229a29c: both steps of the setup at once. */
void PocketsWallet_SetUp(PocketsWallet *wallet, int screen_a)
{
    PocketsWallet_LoadBackground(wallet, screen_a);
    PocketsWallet_SetUpContents(wallet);
}
CLEAN_AS(func_ov094_0229a29c, PocketsWallet_SetUp)

/* func_ov094_0229a2b0: the object given its layer, the amount set (its digits dirty), the
 * plain frame and no picture yet. */
void PocketsWallet_Init(PocketsWallet *wallet, u8 layer)
{
    wallet->layer = layer;
    wallet->dirty = 0;
    PocketsWallet_ResetCount(wallet);
    wallet->frame = POCKETS_WALLET_FRAME_PLAIN;
    wallet->wanted_frame = POCKETS_WALLET_FRAME_PLAIN;
    wallet->picture = POCKETS_WALLET_NO_PICTURE;
}
CLEAN_AS(func_ov094_0229a2b0, PocketsWallet_Init)

/* func_ov094_0229a2d0: the destructor: the labels destructed (the tasks have none). */
PocketsWallet *PocketsWallet_Destruct(PocketsWallet *wallet)
{
    __cxa_vec_cleanup(wallet->labels, POCKETS_WALLET_LABELS, sizeof(TextLabel), func_02070be8);
    return wallet;
}
CLEAN_AS(func_ov094_0229a2d0, PocketsWallet_Destruct)

/* func_ov094_0229a2ec: the constructor: the three tasks and the two labels. */
PocketsWallet *PocketsWallet_Construct(PocketsWallet *wallet)
{
    for (int i = 0; i < POCKETS_WALLET_TASKS; i++) {
        LayerTask_ConstructPair(&wallet->tasks[i]);
    }
    __cxa_vec_ctor(wallet->labels, POCKETS_WALLET_LABELS, sizeof(TextLabel), func_02070c08, func_02070be8);
    return wallet;
}
CLEAN_AS(func_ov094_0229a2ec, PocketsWallet_Construct)
