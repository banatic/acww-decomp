/* The boot screen (boot_screen.h). */
#include "boot_screen.h"

#include "clean.h"
#include "main/display_frame.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/player_records.h"
#include "main/scene_sound.h"
#include "main/scene_tables.h"
#include "main/sound.h"
#include "main/villager_state.h"
#include "activity_card.h"
#include "card_save.h"
#include "save_stamp.h"
#include "scene_exit.h"
#include "scene_heaps.h"
#include "state_block.h"
#include "transfer_queue.h"

static_assert(offsetof(BootScreen, state) == 0x50, "state");
static_assert(offsetof(BootScreen, shown_tick) == 0x54, "shown tick");
static_assert(offsetof(BootScreen, read_result) == 0x5c, "read result");
static_assert(offsetof(BootScreen, read_step) == 0x5f, "read step");
static_assert(offsetof(BootScreen, copies) == 0x64, "copies");
static_assert(sizeof(BootScreen) == 0x6c, "boot screen");

#define REG32(addr) (*(volatile u32 *) (uintptr_t) (addr))
#define REG_DISPCNT 0x04000000u
#define REG_DB_DISPCNT 0x04001000u
/* DISPCNT: the OBJ characters' 1D mapping and its boundary; the main engine's character base. */
#define DISPCNT_OBJ_1D_MAPPING 0x00300010u
#define DISPCNT_CHAR_BASE 0x38000000u

/* VRAM banks: F for the main backgrounds, H for the sub ones (GX_VRAM_*). */
#define BOOT_SCREEN_BANK_BG 0x20
#define BOOT_SCREEN_BANK_SUB_BG 0x80
/* The pictures' last characters. */
#define BOOT_SCREEN_NIN_LAST_CHAR 0x2ff
#define BOOT_SCREEN_ARR_LAST_CHAR 0x13f

#define BOOT_SCREEN_FADE_FRAMES 16
#define BOOT_SCREEN_SOUND 0x88c
/* How long the pictures stay at least, in OS ticks (one second at 33.513982 MHz / 64). */
#define BOOT_SCREEN_SHOW_TICKS 523656u
/* The size of the save (and of the state block), and of the heap made while it is applied. */
#define BOOT_SCREEN_SAVE_SIZE 0x173fc
#define BOOT_SCREEN_APPLY_HEAP_SIZE 0x5000
/* The scene gone to after the boot screen, and what the process between scenes is asked for
 * with. */
#define BOOT_SCREEN_NEXT_SCENE 0x2c
#define BOOT_SCREEN_CHANGE_PARAM 3
#define BOOT_SCREEN_CHANGE_KEEP 2
/* The VBlanks a frame takes from now on (itcm/interrupts.c). */
#define BOOT_SCREEN_FRAME_VBLANKS 3
/* The state block's steps (func_0209e6ec): after a new state, after a loaded one. */
#define BOOT_SCREEN_BLOCK_STEP_NEW 3
#define BOOT_SCREEN_BLOCK_STEP_LOADED 4

/* The class's vtable, the scene base class's and the processes' root class's. */
extern const u32 data_020e5320[];
extern const u32 data_020e3c94[];
extern const u32 data_020da13c[];

extern const char data_020e5368[]; /* "menu/nin/nin.bch" */
extern const char data_020e537c[]; /* "menu/nin/nin.bpl" */
extern const char data_020e5390[]; /* "menu/nin/nin.bsc" */
extern const char data_020e53a4[]; /* "menu/nin/arr.bch" */
extern const char data_020e53b8[]; /* "menu/nin/arr.bpl" */
extern const char data_020e53cc[]; /* "menu/nin/arr.bsc" */

/* The game's heap; the VBlanks a frame takes. */
extern Heap *data_021fbe94;
extern int data_020dd828;
/* The state block (state_block.h) and a record func_0209fb28 looks at. */
extern u8 data_021dc7a8[];
extern u8 data_021f3ba0[];

extern u64 OS_GetTick(void);
extern void GX_SetBankForBG(int banks);
extern void GX_SetBankForSubBG(int banks);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_020b5650 (vtable slot 16): the destructor: the class's vtable, the scene base class's
 * and the root class's in turn, then the process destructor. */
BootScreen *BootScreen_Destruct(BootScreen *screen)
{
    screen->base.vtable = data_020e5320;
    screen->base.vtable = data_020e3c94;
    screen->base.vtable = data_020da13c;
    Process_Destruct(&screen->base);
    return screen;
}
CLEAN_AS(func_020b5650, BootScreen_Destruct)

/* func_020b5678 (slot 17): destroyed (BootScreen_Destruct) and freed. */
BootScreen *BootScreen_Delete(BootScreen *screen)
{
    screen->base.vtable = data_020e5320;
    screen->base.vtable = data_020e3c94;
    screen->base.vtable = data_020da13c;
    Process_Destruct(&screen->base);
    Heap_FreeAux(screen);
    return screen;
}
CLEAN_AS(func_020b5678, BootScreen_Delete)

/* func_020b56a8: what was read put to use, in a background heap of its own: when a read failed
 * or both copies are bad a new state is started (with both bad, func_0209fb28's record may set
 * a flag first, and the save gets func_020a16b0's step), and the state block's step 3 follows;
 * else the loaded copy gets step 4. Either way the state is then put to use. */
void BootScreen_ApplySave(BootScreen *screen)
{
    SceneHeaps_CreateBgModels(BOOT_SCREEN_APPLY_HEAP_SIZE, NULL);
    u8 status = screen->save_status;
    if (status == BOOT_SCREEN_SAVE_BOTH_BAD || status == BOOT_SCREEN_SAVE_FAILED) {
        if (status == BOOT_SCREEN_SAVE_BOTH_BAD && SaveStamp_HasNoWrite((const SaveStamp *) (void *) data_021f3ba0) == 0) {
            SaveStamp_SetLostFlag(1);
        }
        if (screen->save_status == BOOT_SCREEN_SAVE_BOTH_BAD) {
            CardSave_ClearByte3FFFC();
        }
        StateBlock_Init((StateBlock *) (void *) data_021dc7a8);
        PlayerRecords_ClearGuests();
        VillagerState_Reset();
        StateBlock_Start((StateBlock *) (void *) data_021dc7a8, BOOT_SCREEN_BLOCK_STEP_NEW);
    } else {
        StateBlock_Start((StateBlock *) (void *) data_021dc7a8, BOOT_SCREEN_BLOCK_STEP_LOADED);
    }
    StateBlock_FinishStart((StateBlock *) (void *) data_021dc7a8);
    VillagerState_CallNoOp();
    SceneHeaps_DestroyBgModels();
}
CLEAN_AS(func_020b56a8, BootScreen_ApplySave)

/* func_020b5724: the copy to use, from the two reads: a failed read (result 1, which the read
 * never gives) makes status 1 and two bad copies status 4; else the good copy, or with both
 * good the one func_020a16e0 picks, goes into the state block (status 0). */
void BootScreen_PickSave(BootScreen *screen)
{
    u8 first = screen->read_result[0];
    u8 second = screen->read_result[1];

    if (first == BOOT_SCREEN_READ_FAILED || second == BOOT_SCREEN_READ_FAILED) {
        screen->save_status = BOOT_SCREEN_SAVE_FAILED;
        return;
    }
    if (first != BOOT_SCREEN_READ_GOOD && second != BOOT_SCREEN_READ_GOOD) {
        screen->save_status = BOOT_SCREEN_SAVE_BOTH_BAD;
        return;
    }

    int use_second;
    if (first != BOOT_SCREEN_READ_GOOD) {
        use_second = 1;
    } else if (second != BOOT_SCREEN_READ_GOOD) {
        use_second = 0;
    } else {
        use_second = CardSave_SameSerial();
    }
    MI_CpuCopy8(screen->copies[use_second != 0 ? 1 : 0], data_021dc7a8, BOOT_SCREEN_SAVE_SIZE);
    screen->save_status = BOOT_SCREEN_SAVE_LOADED;
}
CLEAN_AS(func_020b5724, BootScreen_PickSave)

/* func_020b5794: the display reset, the VRAM banks for the backgrounds given, the pictures'
 * files loaded into the two backgrounds and both shown.
 * HW: DISPCNT of both engines loses the OBJ 1D mapping bits, then the main one its character
 * base, at these points between the calls. */
void BootScreen_SetUpPictures(BootScreen *screen)
{
    (void) screen;
    DisplayFrame_ResetState();
    TransferQueue_ClearMain();
    TransferQueue_ClearVBlank();
    DisplayFrame_ReleaseVram();
    GX_SetBankForBG(BOOT_SCREEN_BANK_BG);
    GX_SetBankForSubBG(BOOT_SCREEN_BANK_SUB_BG);
    REG32(REG_DISPCNT) &= ~DISPCNT_OBJ_1D_MAPPING;
    REG32(REG_DB_DISPCNT) &= ~DISPCNT_OBJ_1D_MAPPING;
    Display_SetMainBgModeNow(0);
    Display_SetSubBgModeNow(0);
    REG32(REG_DISPCNT) &= ~DISPCNT_CHAR_BASE;
    DisplayLayer_SetBgControl(LAYER_SUB_BG3, 0, 0, 0);
    DisplayLayer_SetBgControl(LAYER_MAIN_BG3, 0, 0, 0);

    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_020e5368, heap, LAYER_SUB_BG3, 0, 0, BOOT_SCREEN_NIN_LAST_CHAR);
    DisplayLayer_LoadPalettesFromFile(data_020e537c, heap, LAYER_SUB_BG3, 0, 0, 0);
    DisplayLayer_LoadScreenFromFile(data_020e5390, heap, LAYER_SUB_BG3);
    DisplayLayer_LoadCharsFromFile(data_020e53a4, heap, LAYER_MAIN_BG3, 0, 0, BOOT_SCREEN_ARR_LAST_CHAR);
    DisplayLayer_LoadPalettesFromFile(data_020e53b8, heap, LAYER_MAIN_BG3, 0, 0, 0);
    DisplayLayer_LoadScreenFromFile(data_020e53cc, heap, LAYER_MAIN_BG3);
    DisplayLayer_Show(LAYER_SUB_BG3);
    DisplayLayer_Show(LAYER_MAIN_BG3);
}
CLEAN_AS(func_020b5794, BootScreen_SetUpPictures)

/* The save's reading: copy 0 once the fade-in has started, then copy 1, a step a frame. */
static void boot_screen_read(BootScreen *screen)
{
    int result;

    switch (screen->read_step) {
        case BOOT_SCREEN_READ_WAIT:
            if (screen->state == BOOT_SCREEN_FADE_IN) {
                screen->read_step = BOOT_SCREEN_READ_FIRST;
            }
            break;
        case BOOT_SCREEN_READ_FIRST:
            result = ActivityCard_StepReadCopy(0, screen->copies[0]);
            if (result != BOOT_SCREEN_READ_BUSY) {
                screen->read_result[0] = (u8) result;
                screen->read_step = BOOT_SCREEN_READ_SECOND;
            }
            break;
        case BOOT_SCREEN_READ_SECOND:
            result = ActivityCard_StepReadCopy(1, screen->copies[1]);
            if (result != BOOT_SCREEN_READ_BUSY) {
                screen->read_result[1] = (u8) result;
                screen->read_step = BOOT_SCREEN_READ_DONE;
            }
            break;
        default:
            break;
    }
}

/* func_020b5898 (slot 6): a frame: the save's reading, then the screen's step; always 1. */
int BootScreen_Update(BootScreen *screen)
{
    boot_screen_read(screen);

    switch (screen->state) {
        case BOOT_SCREEN_START:
            BootScreen_SetUpPictures(screen);
            Display_SetBrightnessNow((unsigned int) -BOOT_SCREEN_FADE_FRAMES);
            screen->state = BOOT_SCREEN_FADE_IN;
            screen->timer = BOOT_SCREEN_FADE_FRAMES;
            SoundSys_PlaySe(BOOT_SCREEN_SOUND);
            break;
        case BOOT_SCREEN_FADE_IN:
            if (screen->timer != 0) {
                screen->timer--;
                Display_SetBrightnessNow((unsigned int) -(int) screen->timer);
            } else {
                screen->state = BOOT_SCREEN_SHOW;
                u64 now = OS_GetTick();
                screen->shown_tick[0] = (u32) now;
                screen->shown_tick[1] = (u32) (now >> 32);
            }
            break;
        case BOOT_SCREEN_SHOW: {
            u64 now = OS_GetTick();
            if (screen->read_step < BOOT_SCREEN_READ_APPLIED) {
                if (screen->read_step < BOOT_SCREEN_READ_DONE) {
                    break;
                }
                BootScreen_PickSave(screen);
                BootScreen_ApplySave(screen);
                screen->read_step = BOOT_SCREEN_READ_APPLIED;
            }
            u64 shown = (u64) screen->shown_tick[1] << 32 | screen->shown_tick[0];
            if (now - shown < BOOT_SCREEN_SHOW_TICKS) {
                break;
            }
            screen->state = BOOT_SCREEN_FADE_OUT;
            screen->timer = BOOT_SCREEN_FADE_FRAMES;
            break;
        }
        case BOOT_SCREEN_FADE_OUT:
            if (screen->timer != 0) {
                screen->timer--;
                Display_SetBrightnessNow((unsigned int) ((int) screen->timer - BOOT_SCREEN_FADE_FRAMES));
            } else {
                DisplayShadow_SetMainPlanes(0);
                DisplayShadow_SetSubPlanes(0);
                screen->state = BOOT_SCREEN_DONE;
                SceneExit_SetToSceneOnly((SceneExit *) (void *) ((u8 *) (uintptr_t) SceneTables_EntryRecord()),
                                         BOOT_SCREEN_NEXT_SCENE);
                SceneExit_RequestChange(BOOT_SCREEN_CHANGE_PARAM, BOOT_SCREEN_CHANGE_KEEP);
            }
            break;
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_020b5898, BootScreen_Update)

/* func_020b5a18 (slot 3): the two buffers freed; done. */
int BootScreen_End(BootScreen *screen)
{
    Heap_Free(screen->heap, screen->copies[0]);
    Heap_Free(screen->heap, screen->copies[1]);
    return 1;
}
CLEAN_AS(func_020b5a18, BootScreen_End)

/* func_020b5a34 (slot 0): frames of 3 VBlanks from now on, the scene's sound made, and two
 * buffers for the save's copies taken from the game's heap; done. */
int BootScreen_Init(BootScreen *screen)
{
    data_020dd828 = BOOT_SCREEN_FRAME_VBLANKS;
    SceneSound_Create();
    screen->state = BOOT_SCREEN_START;
    screen->heap = data_021fbe94;
    screen->copies[0] = Heap_Alloc(screen->heap, BOOT_SCREEN_SAVE_SIZE);
    screen->copies[1] = Heap_Alloc(screen->heap, BOOT_SCREEN_SAVE_SIZE);
    return 1;
}
CLEAN_AS(func_020b5a34, BootScreen_Init)

/* func_020b5a78 (the profile's create): a new screen, zeroed and constructed: the process
 * constructor, then the scene base class's part (flags 1 and 4 set) and the class's vtable;
 * NULL when there is no memory. */
BootScreen *BootScreen_New(void)
{
    BootScreen *screen = Heap_AllocAuxZeroed(sizeof(BootScreen));
    if (screen != NULL) {
        Process_Construct(&screen->base);
        screen->base.vtable = data_020da13c;
        screen->base.vtable = data_020e3c94;
        screen->base.flags |= PROCESS_EXECUTE_STOPPED;
        screen->base.flags |= PROCESS_DRAW_STOPPED;
        screen->base.vtable = data_020e5320;
    }
    return screen;
}
CLEAN_AS(func_020b5a78, BootScreen_New)
