/* The boot screen: process class 1 (vtable data_020e5320, 0x6c bytes, profile data_020e5310),
 * the first scene the game asks for (resident_process.h).
 *
 * It shows the pictures "menu/nin/nin" on the sub screen's background 3 and "menu/nin/arr" on
 * the main screen's background 3, fading them in over 16 frames with a sound. Meanwhile it
 * reads the save's two copies (0x173fc bytes each) into buffers of its own and, once both are
 * read, picks the copy to use and puts it in the state block (state_block.h), or starts a new
 * state when neither copy can be used. At least a second (OS ticks) after the fade-in it fades
 * out over 16 frames, hides both screens' planes, records scene 0x2c as the one to go to and
 * asks for the process between scenes (scene_change.h). */
#ifndef CLEAN_MAIN_BOOT_SCREEN_H
#define CLEAN_MAIN_BOOT_SCREEN_H

#include "autoload_2/process.h"
#include "types.h"

#define BOOT_SCREEN_SAVE_COPIES 2

/* The steps of the screen (BootScreen.state). */
enum BootScreenState {
    BOOT_SCREEN_START = 0,    /* the pictures are set up */
    BOOT_SCREEN_FADE_IN = 1,  /* 16 frames */
    BOOT_SCREEN_SHOW = 2,     /* until the save is in and the time is up */
    BOOT_SCREEN_FADE_OUT = 3, /* 16 frames */
    BOOT_SCREEN_DONE = 4
};

/* The steps of reading the save (BootScreen.read_step). */
enum BootScreenReadStep {
    BOOT_SCREEN_READ_WAIT = 0,   /* until the fade-in starts */
    BOOT_SCREEN_READ_FIRST = 1,  /* copy 0 being read */
    BOOT_SCREEN_READ_SECOND = 2, /* copy 1 being read */
    BOOT_SCREEN_READ_DONE = 3,   /* both read, the result not applied yet */
    BOOT_SCREEN_READ_APPLIED = 5
};

/* What reading a copy gives (func_020a1a40): 0 when it is good, 3 while it is still being read;
 * 1 and 4 are failures. */
enum BootScreenReadResult {
    BOOT_SCREEN_READ_GOOD = 0,
    BOOT_SCREEN_READ_FAILED = 1,
    BOOT_SCREEN_READ_BUSY = 3,
    BOOT_SCREEN_READ_BAD = 4
};

/* What was made of the save (BootScreen.save_status): a copy loaded, or a new state started
 * because a read failed (1) or both copies are bad (4). */
enum BootScreenSaveStatus { BOOT_SCREEN_SAVE_LOADED = 0, BOOT_SCREEN_SAVE_FAILED = 1, BOOT_SCREEN_SAVE_BOTH_BAD = 4 };

typedef struct BootScreen {
    Process base;
    u8 state; /* 0x50: enum BootScreenState */
    u8 timer; /* 0x51: the fade's frames left */
    u8 unk_52[2];
    u32 shown_tick[2];                       /* 0x54: OS_GetTick when the fade-in ended, low word first */
    u8 read_result[BOOT_SCREEN_SAVE_COPIES]; /* 0x5c: enum BootScreenReadResult */
    u8 save_status;                          /* 0x5e: enum BootScreenSaveStatus */
    u8 read_step;                            /* 0x5f: enum BootScreenReadStep */
    Heap *heap;                              /* 0x60: where the buffers are */
    void *copies[BOOT_SCREEN_SAVE_COPIES];   /* 0x64: the save's copies as read */
} BootScreen;

BootScreen *BootScreen_Delete(BootScreen *screen);
BootScreen *BootScreen_Destruct(BootScreen *screen);
void BootScreen_ApplySave(BootScreen *screen);
void BootScreen_PickSave(BootScreen *screen);
void BootScreen_SetUpPictures(BootScreen *screen);
int BootScreen_Update(BootScreen *screen);
int BootScreen_End(BootScreen *screen);
int BootScreen_Init(BootScreen *screen);
BootScreen *BootScreen_New(void);

#endif
