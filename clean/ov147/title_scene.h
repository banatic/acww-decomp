/* The title screen, overlay 147: a process of its own (vtable data_ov147_0229aa28, 0xf8 bytes,
 * include/cpp/ov147/Obj_ov147_0229aa28.h) derived from main's process root class
 * (data_020da13c), not from ov002's menu scene. Its create function, TitleScene_New, is the
 * constant at data_ov147_0229a91c; the boot screen asks for scene 0x2c (main/boot_screen.h) and
 * the activity's job 0xc enters it again after a town player is removed. Its parts:
 *
 * - the logo ("menu/title/bg.bch" with its palettes and screen, on the sub screen's
 *   background 2, characters 0x140-0x2ff), which wipes in tile by tile along the screen's
 *   diagonals (the 15 characters of "menu/title/mask1.bch" ANDed into the logo's characters)
 *   and out through the 7 masks of "menu/title/mask0.bch" (title_logo.c);
 * - a message on the main screen's background 3, one of two screens of "/a_mes/" ("a0" or
 *   "b0", TitleMes, at 0xb0) blended in and out over the 3D (title_mes.c);
 * - a talk receiver (TitleReceiver, at 0x54) whose messages of "sp_etc_sequence1" (or of
 *   "sp_etc_sequence2" when the card's first copy has an unreadable stamp) make the title's menu:
 *   starting the game, making a new town or a new player, removing a town player
 *   (title_menu.c);
 * - its states (TitleSceneState): waiting for the player, the talk, and one way out of the
 *   title each (title_scene.c).
 *
 * The scene's states are a table of twelve pairs of member functions {entry, frame}
 * (data_ov147_0229ad4c, filled by the overlay's static initializer TitleScene_InitStateTable).
 * TitleScene_SetState runs a state's entry; TitleScene_Update runs its frame, then the logo's
 * step and the message's. */
#ifndef CLEAN_OV147_TITLE_SCENE_H
#define CLEAN_OV147_TITLE_SCENE_H

#include "autoload_2/process.h"
#include "main/layer_load_task.h"
#include "main/talk_receiver.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct TitleScene;

/* The scene's states (TitleScene.state), each a pair of the table data_ov147_0229ad4c. */
enum TitleSceneState {
    TITLE_STATE_WAIT = 0,           /* TitleScene_ResetIdleTimer, TitleScene_WaitForPress */
    TITLE_STATE_START_TALK = 1,     /* TitleScene_EnterStartTalk, TitleScene_StartTalk */
    TITLE_STATE_TALK = 2,           /* TitleScene_EnterTalk, TitleScene_RunTalk: the receiver acts */
    TITLE_STATE_END_TALK = 3,       /* TitleScene_EnterEndTalk, TitleScene_WaitTalkClosed */
    TITLE_STATE_EXIT_JOB_6 = 4,     /* TitleScene_EnterExitJob6, TitleScene_ExitForJob6 */
    TITLE_STATE_EXIT_JOB_5 = 5,     /* TitleScene_EnterExitJob5, TitleScene_ExitForJob5 */
    TITLE_STATE_EXIT_SCENE_6 = 6,   /* TitleScene_EnterExitScene6, TitleScene_ExitToScene6 */
    TITLE_STATE_EXIT_NEW = 7,       /* TitleScene_EnterExitNew, TitleScene_ExitToScene2d */
    TITLE_STATE_EXIT_REQUEST = 8,   /* TitleScene_EnterExitRequest, TitleScene_ExitByRequest */
    TITLE_STATE_EXIT_JOB_1C = 9,    /* TitleScene_EnterExitJob1c, TitleScene_ExitForJob1c */
    TITLE_STATE_EXIT_SCENE_30 = 10, /* TitleScene_EnterExitScene30, TitleScene_ExitToScene30 */
    TITLE_STATE_IDLE_RESTART = 11,  /* TitleScene_EnterIdleRestart, TitleScene_RestartTitle */
    TITLE_STATES = 12
};

/* The logo's steps (TitleScene.logo_state, TitleLogo_Update). */
enum TitleLogoState {
    TITLE_LOGO_LOAD = 0,     /* once the screen is shown: loaded, then the wipe in */
    TITLE_LOGO_WIPE_IN = 1,  /* TitleLogo_StepWipeIn */
    TITLE_LOGO_SHOWN = 2,    /* for `logo_timer` frames */
    TITLE_LOGO_WIPE_OUT = 3, /* TitleLogo_StepWipeOut */
    TITLE_LOGO_GONE = 4,     /* wiped out */
    TITLE_LOGO_HIDDEN = 5,   /* hidden at once, or never shown */
    TITLE_LOGO_SKIPPED = 6   /* the scene began with main's event flag 0x10: no logo */
};

/* The music the scene started (TitleScene.music, TitleScene_StartMusic). */
enum TitleMusic {
    TITLE_MUSIC_NONE = 0,
    TITLE_MUSIC_STARTED = 1, /* the title's music asked for (priority 2) */
    TITLE_MUSIC_VALUE = 2    /* a value of priority 1 added (main's event flag 0x10) */
};

/* The message's steps (TitleMes.state), run by TitleMes_Update. */
enum TitleMesState {
    TITLE_MES_IDLE = 0,    /* TitleMes_RunIdle: nothing shown */
    TITLE_MES_WAITING = 1, /* TitleMes_RunWaiting: a few frames before it is shown */
    TITLE_MES_SHOWN = 2,   /* TitleMes_RunShown: blended in and out */
    TITLE_MES_STATES = 3
};

/* TitleMes.shown and TitleMes.wanted: one of the two screens, or none. */
#define TITLE_MES_NONE 2

/* The message on the main screen's background 3 (class data_ov147_0229ac1c, 0x20 bytes,
 * include/cpp/ov147/Obj_ov147_0229ac1c.h). */
typedef struct TitleMes {
    const void *vtable; /* 0x00: data_ov147_0229ac1c */
    s32 state;          /* 0x04: TitleMesState */
    s32 shown;          /* 0x08: the screen shown (0 "a0", 1 "b0") or TITLE_MES_NONE */
    s32 wanted;         /* 0x0c: the screen asked for, or TITLE_MES_NONE to take it away */
    s32 level;          /* 0x10: the blend's step, 0 (out) to 10 (in) */
    s32 held;           /* 0x14: frames held at step 10 */
    s32 delay;          /* 0x18: frames left before it is shown */
    u8 fading;          /* 0x1c: the blend steps down */
    u8 pad_1d[3];
} TitleMes;

/* The talk receiver of the title (vtable data_ov147_0229aae4): main's (main/talk_receiver.h)
 * and the scene it belongs to. */
typedef struct TitleReceiver {
    TalkReceiver base;        /* 0x00 */
    struct TitleScene *scene; /* 0x48 */
} TitleReceiver;

/* The answers a message offers (TitleMenu_OfferChoices): their messages and the bytes each
 * answer's unk_70 gets (main/talk_answers.h). */
typedef struct TitleChoices {
    u8 *messages;
    u8 *values;
    u8 count;
    u8 pad_09[3];
} TitleChoices;

typedef struct TitleScene {
    Process base;           /* 0x00 */
    s32 state;              /* 0x50: TitleSceneState */
    TitleReceiver receiver; /* 0x54 */
    u8 unk_a0[2];           /* 0xa0 */
    u8 card_unreadable;     /* 0xa2: the card's first copy has an unreadable stamp */
    u8 music;               /* 0xa3: TitleMusic */
    s32 logo_step;          /* 0xa4: the wipe in's diagonal, the wipe out's mask */
    u16 logo_timer;         /* 0xa8: frames the logo stays (TITLE_LOGO_SHOWN) */
    u8 logo_state;          /* 0xaa: TitleLogoState */
    u8 press_delay;         /* 0xab: frames before the first message is asked for again */
    u16 idle_timer;         /* 0xac: frames without the player before the title restarts */
    u8 pad_ae[2];
    TitleMes mes;         /* 0xb0 */
    LayerTask chars_task; /* 0xd0: the logo's characters to their layer */
    u8 wfc_failed;        /* 0xf4: the Wi-Fi library's start gave result 3 */
    u8 pad_f5[3];
} TitleScene;

/* title_logo.c */
void TitleLogo_MaskCell(TitleScene *self, const u32 *pattern, int column, int row);
void TitleLogo_MaskChar(TitleScene *self, const u32 *pattern, int index);
int TitleLogo_StepWipeOut(TitleScene *self);
void TitleLogo_StartWipeOut(TitleScene *self);
int TitleLogo_StepWipeIn(TitleScene *self);
void TitleLogo_StartWipeIn(TitleScene *self);
void TitleLogo_Hide(TitleScene *self);
void TitleLogo_Dismiss(TitleScene *self);
void TitleLogo_FinishWipeIn(TitleScene *self);
void TitleLogo_Update(TitleScene *self);
void TitleLogo_Load(TitleScene *self);

/* title_menu.c */
unsigned char TitleMenu_GreetingMessage(TitleReceiver *self);
void TitleMenu_CheckBottleLetter(TitleReceiver *self);
void TitleMenu_PickTownPlayer(TitleReceiver *self);
void TitleMenu_EndToTitle(TitleReceiver *self);
void TitleMenu_ToScene6(TitleReceiver *self);
void TitleMenu_NewTown(TitleReceiver *self);
void TitleMenu_OnAnswer(TitleReceiver *self);
void TitleMenu_OnClose(TitleReceiver *self);
void TitleMenu_ListTownPlayers(TitleReceiver *self);
void TitleMenu_OfferChoices(TitleReceiver *self, const TitleChoices *choices);
void TitleMenu_AfterMessage(TitleReceiver *self);
void TitleReceiver_SetScene(TitleReceiver *self, TitleScene *scene);
TitleReceiver *TitleReceiver_Delete(TitleReceiver *self);
TitleReceiver *TitleReceiver_Destruct(TitleReceiver *self);
TitleReceiver *TitleReceiver_Construct(TitleReceiver *self);

/* title_scene.c */
void TitleScene_ExitByRequest(TitleScene *self);
void TitleScene_EnterExitRequest(TitleScene *self);
void TitleScene_ExitToScene30(TitleScene *self);
void TitleScene_EnterExitScene30(TitleScene *self);
void TitleScene_ExitForJob1c(TitleScene *self);
void TitleScene_EnterExitJob1c(TitleScene *self);
void TitleScene_ExitToScene2d(TitleScene *self);
void TitleScene_EnterExitNew(TitleScene *self);
void TitleScene_ExitToScene6(TitleScene *self);
void TitleScene_EnterExitScene6(TitleScene *self);
void TitleScene_ExitForJob5(TitleScene *self);
void TitleScene_EnterExitJob5(TitleScene *self);
void TitleScene_ExitForJob6(TitleScene *self);
void TitleScene_EnterExitJob6(TitleScene *self);
void TitleScene_WaitTalkClosed(TitleScene *self);
void TitleScene_EnterEndTalk(void);
void TitleScene_RunTalk(void);
void TitleScene_EnterTalk(void);
void TitleScene_StartTalk(TitleScene *self);
void TitleScene_EnterStartTalk(void);
void TitleScene_RestartTitle(TitleScene *self);
void TitleScene_EnterIdleRestart(void);
void TitleScene_WaitForPress(TitleScene *self);
void TitleScene_ResetIdleTimer(TitleScene *self);
void TitleScene_SetState(TitleScene *self, int state);
void TitleScene_EndMusicOnLeave(TitleScene *self);
void TitleScene_StopMusic(TitleScene *self);
void TitleScene_StartMusic(TitleScene *self, int after_event);
int TitleScene_Update(TitleScene *self);
int TitleScene_End(TitleScene *self);
int TitleScene_Init(TitleScene *self);
TitleScene *TitleScene_Delete(TitleScene *self);
TitleScene *TitleScene_Destruct(TitleScene *self);
TitleScene *TitleScene_Construct(TitleScene *self);
void TitleScene_New(void);
int TitleScene_InitStateTable(void);

/* title_mes.c */
void TitleMes_RunShown(TitleMes *self);
void TitleMes_Show(TitleMes *self);
void TitleMes_RunWaiting(TitleMes *self);
void TitleMes_StartWait(TitleMes *self);
void TitleMes_RunIdle(TitleMes *self);
void TitleMes_SetIdle(TitleMes *self);
void TitleMes_ClearBlend(TitleMes *self);
void TitleMes_ApplyBlend(TitleMes *self);
void TitleMes_HideLayer(void);
void TitleMes_ShowLayer(void);
void TitleMes_SetUpLayer(void);
void TitleMes_UploadScreen(unsigned int data);
void TitleMes_UploadPalette(void *data);
void TitleMes_UploadChars(void *data);
void TitleMes_ReadScreen(void *file, const char *path, void *dst);
void TitleMes_ReadPalette(void *file, const char *path, void *dst);
void TitleMes_ReadChars(void *file, const char *path, void *dst);
void TitleMes_Load(int screen);
void TitleMes_Free(void *data);
int TitleMes_Alloc(unsigned int size);
int TitleMes_Pulse(TitleMes *self);
void TitleMes_ResetBlend(TitleMes *self);
int TitleMes_IsIdle(TitleMes *self);
void TitleMes_Withdraw(TitleMes *self);
void TitleMes_Request(TitleMes *self, int screen);
void TitleMes_Update(TitleMes *self);
void TitleMes_Release(TitleMes *self);
void TitleMes_Init(TitleMes *self);
TitleMes *TitleMes_Delete(TitleMes *self);
void TitleMes_Destruct(TitleMes *self);
void TitleMes_Construct(TitleMes *self);

#endif
