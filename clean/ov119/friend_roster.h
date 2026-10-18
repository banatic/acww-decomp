/* The friend roster of the menu (overlay 119, overlay group 36, the menu's tab 6: ov090's
 * MenuTabs opens it; vtable 0x0229cea0, include/cpp/ov119/Obj_ov119_0229cea0.h; constructor
 * FriendRoster_New, 0x2018 bytes): a menu scene (ov002/menu_scene.h) that shows the current
 * player's Wi-Fi friend roster (main/wifi_friends.h, 32 friends) with the graphics of
 * "menu/friend/...". As the evidence says:
 *
 * - six page tabs on the right: pages 0-3 list eight friends each (an icon, the friend's town
 *   by message 0x66 and the friend's name), page 4 shows this user's own friend key in twelve
 *   digits with the player's town and name, page 5 the other players of the session
 *   (main/session.h). Switching pages fades two palettes out and back (FriendRoster_Fade);
 * - picking a friend opens a choice (ov002/paged_choice.h) whose rows carry an action
 *   (FriendRosterAction): three of them open another tab of the menu with the friend's index
 *   in GroupParams' argument, one deletes the friend after a question;
 * - the button below the list opens a choice of the session's other players, to add one as a
 *   friend, or to register a friend by friend key (the menu's tab 14);
 * - a change to the roster is told to the menu (MenuTabs_MarkRosterChanged), which writes it to
 *   the card when it closes. While connected to Nintendo Wi-Fi Connection (network mode 3 or
 *   4, FriendRoster_IsOnline) NitroDWC's friend list is changed too, retried each frame until
 *   NitroDWC allows it.
 *
 * The cursor (`cursor`, FriendRosterPlace) walks the rows, the page tabs, the menu's tab bar
 * and the button, by the d-pad; the pen picks places directly. A Glider of ov002's points at
 * it (`cursor_sprite`). */
#ifndef CLEAN_OV119_FRIEND_ROSTER_H
#define CLEAN_OV119_FRIEND_ROSTER_H

#include "main/bbs.h"
#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "main/wifi_friends.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"
#include "types.h"

/* In `flags`. */
enum FriendRosterFlag {
    FRIEND_ROSTER_FLAG_DRAWN = 0x01,      /* the scene is drawn (FriendRoster_Draw) */
    FRIEND_ROSTER_FLAG_MAP_DIRTY = 0x02,  /* `map` is queued to the screen (FriendRoster_EndFrame) */
    FRIEND_ROSTER_FLAG_ROWS_DIRTY = 0x04, /* the rows' palettes are set again, the highlighted row's 4 */
    FRIEND_ROSTER_FLAG_HEADER = 0x08,     /* the header's three lines are made once (FriendRoster_ShowHeader) */
    FRIEND_ROSTER_FLAG_QUESTION = 0x10,   /* the choice's first row is a question, not picked */
    FRIEND_ROSTER_FLAG_FADED = 0x20       /* the faded palettes are queued, every frame once set */
};

/* The pages (`page`, `tab`). */
enum FriendRosterPage {
    FRIEND_ROSTER_PAGE_FRIENDS_LAST = 3, /* 0-3: eight friends each */
    FRIEND_ROSTER_PAGE_OWN_KEY = 4,      /* this user's friend key, town and name */
    FRIEND_ROSTER_PAGE_PLAYERS = 5,      /* the session's other players */
    FRIEND_ROSTER_PAGE_NONE = 0xff       /* `page` before any */
};

#define FRIEND_ROSTER_ROWS 8 /* a page's rows */
#define FRIEND_ROSTER_PAGE_TABS 6
#define FRIEND_ROSTER_NO_SLOT WIFI_FRIENDS /* in `slots`: past the set friends */
#define FRIEND_ROSTER_LABELS 19            /* the text labels; the last one is handed out again */
#define FRIEND_ROSTER_FADE_STEPS 5

/* The places of the cursor (`cursor`) and of the pen (FriendRoster_PlaceAt). */
enum FriendRosterPlace {
    FRIEND_ROSTER_PLACE_ROW_LAST = 7, /* 0-7: the rows */
    FRIEND_ROSTER_PLACE_TAB = 8,      /* 8-13: the page tabs, 8 + page */
    FRIEND_ROSTER_PLACE_TAB_LAST = 13,
    FRIEND_ROSTER_PLACE_BAR = 14,      /* 14-21: the menu's tab bar, 14 + MenuTab */
    FRIEND_ROSTER_PLACE_BAR_SELF = 20, /* the bar's place of this tab (MENU_TAB_6) */
    FRIEND_ROSTER_PLACE_BAR_LAST = 21,
    FRIEND_ROSTER_PLACE_BUTTON = 22, /* the button below the list */
    FRIEND_ROSTER_PLACE_NONE = 23    /* the pen is on nothing */
};

/* The values of the choice rows (`action`), run by FriendRoster_RunAction. */
enum FriendRosterAction {
    FRIEND_ROSTER_ACTION_ASK_DELETE = 0, /* FriendRoster_AskDelete */
    FRIEND_ROSTER_ACTION_DELETE = 1,     /* FriendRoster_DeleteFriend */
    FRIEND_ROSTER_ACTION_TAB_9 = 2,      /* 2-4: the menu's tab 9, 11 or 13 with the friend's index */
    FRIEND_ROSTER_ACTION_TAB_11 = 3,
    FRIEND_ROSTER_ACTION_TAB_13 = 4,
    FRIEND_ROSTER_ACTION_REGISTER = 5, /* FriendRoster_OpenRegister: the menu's tab 14 */
    FRIEND_ROSTER_ACTION_PLAYER = 6,   /* 6-9: add the session's player (action - 6) */
    FRIEND_ROSTER_ACTION_PLAYER_LAST = 9,
    FRIEND_ROSTER_ACTION_CANCEL = 10
};

/* The sub states (MenuScene.sub_state), run by FriendRoster_RunSubState. */
enum FriendRosterSubState {
    FRIEND_ROSTER_SUB_TOUCH = 0x00,        /* FriendRoster_IdleByTouch */
    FRIEND_ROSTER_SUB_CHOICE_TOUCH = 0x01, /* FriendRoster_ChooseByTouch */
    FRIEND_ROSTER_SUB_KEYS = 0x02,         /* FriendRoster_BrowseByKeys */
    FRIEND_ROSTER_SUB_SPRITE_MOVE = 0x03,  /* FriendRoster_WaitCursorSprite */
    FRIEND_ROSTER_SUB_PRESS = 0x04,        /* FriendRoster_PressPlace */
    FRIEND_ROSTER_SUB_PRESS_END = 0x05,    /* FriendRoster_FinishPress */
    FRIEND_ROSTER_SUB_CHOICE_KEYS = 0x06,  /* FriendRoster_ChooseByKeys */
    FRIEND_ROSTER_SUB_CHOICE_PRESS = 0x07, /* FriendRoster_PressChoiceRow */
    FRIEND_ROSTER_SUB_OPEN_DELAY = 0x08,   /* FriendRoster_WaitToOpenChoice */
    FRIEND_ROSTER_SUB_DELETED = 0x09,      /* FriendRoster_FinishDelete */
    FRIEND_ROSTER_SUB_CHOICE_OPEN = 0x0a,  /* FriendRoster_WaitChoiceShown */
    FRIEND_ROSTER_SUB_CHOICE_CLOSE = 0x0b, /* FriendRoster_CloseChoice */
    FRIEND_ROSTER_SUB_CHOICE_RUN = 0x0c,   /* FriendRoster_RunActionWhenIdle */
    FRIEND_ROSTER_SUB_ERROR = 0x0d,        /* FriendRoster_WaitError */
    FRIEND_ROSTER_SUB_FADE_OUT = 0x0e,     /* FriendRoster_FadeOut */
    FRIEND_ROSTER_SUB_FADE_IN = 0x0f,      /* FriendRoster_FadeIn */
    FRIEND_ROSTER_SUB_RETRY_SET = 0x10,    /* FriendRoster_RetrySetFriend */
    FRIEND_ROSTER_SUB_RETRY_DELETE = 0x11, /* FriendRoster_RetryDeleteFriend */
    FRIEND_ROSTER_SUB_STATES = 0x12
};

/* The states (MenuScene.state), run by FriendRoster_RunState. */
enum FriendRosterState {
    FRIEND_ROSTER_STATE_LOAD = 0,       /* FriendRoster_Load */
    FRIEND_ROSTER_STATE_WIPE_IN = 1,    /* FriendRoster_StartWipeIn */
    FRIEND_ROSTER_STATE_WIPING_IN = 2,  /* FriendRoster_WipeIn */
    FRIEND_ROSTER_STATE_WIPE_OUT = 3,   /* FriendRoster_StartWipeOut; FriendRoster_SelectTab sets it */
    FRIEND_ROSTER_STATE_WIPING_OUT = 4, /* FriendRoster_WipeOut */
    FRIEND_ROSTER_STATES = 5
};

/* The phases the scene sets (MenuScene.phase), as ov090's menu_tabs.h maps them: 0 the base's
 * wait (slot 0x48), 1 FriendRoster_RunState (0x4c), 2 FriendRoster_RunInteractive (0x50),
 * 3 and 4 nothing (0x54, 0x58), 5 FriendRoster_End (0x5c). */
enum FriendRosterPhase {
    FRIEND_ROSTER_PHASE_WAIT = 0,
    FRIEND_ROSTER_PHASE_STATES = 1,
    FRIEND_ROSTER_PHASE_INTERACTIVE = 2,
    FRIEND_ROSTER_PHASE_END = 5
};

#define FRIEND_ROSTER_TASKS 3 /* the screen's, the BG palette's and the OBJ palette's */

typedef struct FriendRoster {
    MenuScene base;                         /* 0x00 */
    s32 wipe_y;                             /* 0x94: MenuScene_WipeOffsetY's, the objects' offset */
    u16 flags;                              /* 0x98: FriendRosterFlag */
    s16 highlight;                          /* 0x9a: the row picked, -1 for none */
    u8 page;                                /* 0x9c: FriendRosterPage shown */
    u8 tab;                                 /* 0x9d: the page tab selected */
    u8 labels_used;                         /* 0x9e: of `labels` (FriendRoster_NextLabel) */
    u8 return_sub_state;                    /* 0x9f: once the cursor sprite stops */
    u8 cursor;                              /* 0xa0: FriendRosterPlace */
    u8 key_digits[WIFI_FRIEND_KEY_DIGITS];  /* 0xa1: this user's friend key, 10 for blank */
    u8 action;                              /* 0xad: FriendRosterAction */
    u8 choice_row;                          /* 0xae: the choice row the cursor is on */
    u8 rows_shown;                          /* 0xaf: the friends shown on the page */
    u8 button_palette;                      /* 0xb0: 7, 8 while pressed */
    u8 delay;                               /* 0xb1: frames before the choice opens; 1 after a delete */
    u8 player_rows;                         /* 0xb2: bit n: row n shows a player (page 5) */
    u8 blink;                               /* 0xb3: frames into the rows' blink, 0-24 */
    u8 friend_index;                        /* 0xb4: the friend acted on */
    u8 pad_b5[3];                           /* 0xb5 */
    s32 fade;                               /* 0xb8: 0 (faded) to 5 (as loaded) */
    u8 slots[WIFI_FRIENDS];                 /* 0xbc: the set friends' indices, then FRIEND_ROSTER_NO_SLOT */
    u8 choice[0x3e8];                       /* 0xdc: a PagedChoice */
    ChoiceEntries entries;                  /* 0x4c4 */
    u8 pad_4cf;                             /* 0x4cf */
    TextLabel labels[FRIEND_ROSTER_LABELS]; /* 0x4d0 */
    BbsLabel header;                        /* 0xcd4 */
    Glider cursor_sprite;                   /* 0xda8: a Glider0 */
    u16 list_map[0x400];                    /* 0xe0c: "menu/friend/b_bg.bsc" */
    u16 key_map[0x400];                     /* 0x160c: "menu/friend/d_bg.bsc" (page 4) */
    u16 *map;                               /* 0x1e0c: the one shown */
    u16 obj_palette[16];                    /* 0x1e10: "menu/friend/obj1.bpl" */
    u16 bg_palette[16];                     /* 0x1e30: "menu/friend/bg2.bpl" */
    u16 obj_faded[16];                      /* 0x1e50 */
    u16 bg_faded[16];                       /* 0x1e70 */
    LayerTask tasks[FRIEND_ROSTER_TASKS];   /* 0x1e90 */
    ErrorMessage error;                     /* 0x1efc */
} FriendRoster;

/* friend_roster.c */
FriendRoster *FriendRoster_Destroy(FriendRoster *self);
FriendRoster *FriendRoster_Delete(FriendRoster *self);
void FriendRoster_ClearFlags(FriendRoster *self, unsigned short flags);
void FriendRoster_SetFlags(FriendRoster *self, unsigned short flags);
int FriendRoster_TestFlags(FriendRoster *self, unsigned int flags);
int FriendRoster_HasFriend(FriendRoster *self, const void *friend_data);
int FriendRoster_FreeIndex(FriendRoster *self);
int FriendRoster_SyncFromNetwork(FriendRoster *self);
void FriendRoster_Compact(FriendRoster *self);
int FriendRoster_HasGap(FriendRoster *self);
void FriendRoster_BuildSlots(FriendRoster *self);
unsigned char FriendRoster_SlotAtCursor(FriendRoster *self);
WifiFriend *FriendRoster_FriendAtCursor(FriendRoster *self);
WifiFriend *FriendRoster_Friends(FriendRoster *self);
int FriendRoster_IsOnline(FriendRoster *self);
void FriendRoster_SetUpLayers(void);
void FriendRoster_EndInteractiveFrame(FriendRoster *self);
void FriendRoster_BeginInteractiveFrame(FriendRoster *self);
void FriendRoster_EndFrame(FriendRoster *self);
void FriendRoster_BeginFrame(FriendRoster *self);
void FriendRoster_Teardown(FriendRoster *self);
void FriendRoster_Setup(FriendRoster *self);
void FriendRoster_WipeOut(FriendRoster *self);
void FriendRoster_StartWipeOut(FriendRoster *self);
void FriendRoster_WipeIn(FriendRoster *self);
void FriendRoster_StartWipeIn(FriendRoster *self);
void FriendRoster_Load(FriendRoster *self);
int FriendRoster_End(FriendRoster *self);
int FriendRoster_Phase4Idle(void);
int FriendRoster_Phase3Idle(void);
int FriendRoster_RunInteractive(FriendRoster *self);
void FriendRoster_RunSubState(FriendRoster *self);
int FriendRoster_RunState(FriendRoster *self);
int FriendRoster_Draw(FriendRoster *self);
int FriendRoster_Close(FriendRoster *self);
int FriendRoster_Start(FriendRoster *self);
FriendRoster *FriendRoster_New(void);

/* friend_roster_page.c */
void FriendRoster_StepBlink(FriendRoster *self);
void FriendRoster_ResetRowPalettes(FriendRoster *self);
void FriendRoster_BlinkPlayerRows(FriendRoster *self);
void FriendRoster_LoadKeyDigits(FriendRoster *self);
int FriendRoster_PageOfFriend(FriendRoster *self, int index);
void FriendRoster_ShowPage(FriendRoster *self, unsigned char page);
void FriendRoster_RedrawPage(FriendRoster *self);
void FriendRoster_DrawFriendRows(FriendRoster *self);
void FriendRoster_SetRowIcon(int unused, u16 *map, unsigned short tile);
void FriendRoster_ShowHeader(FriendRoster *self);
void FriendRoster_DrawOwnInfo(FriendRoster *self);
void FriendRoster_DrawPlayerRows(FriendRoster *self);
void FriendRoster_Fade(FriendRoster *self, int level);
u16 FriendRoster_BlendColour(int unused, int colour, int toward, int weight, int total);
void FriendRoster_UpdateGraphics(FriendRoster *self);
void FriendRoster_ShowPageTitle(FriendRoster *self, int message);
void FriendRoster_ShowTitle(FriendRoster *self);
TextLabel *FriendRoster_NextLabel(FriendRoster *self);
void FriendRoster_ReleaseLabels(FriendRoster *self);
void FriendRoster_LoadObjGraphics(FriendRoster *self);
void FriendRoster_LoadBgGraphics(FriendRoster *self);

/* friend_roster_input.c */
void FriendRoster_CancelChoiceOnClose(FriendRoster *self);
void FriendRoster_ShowChoice(FriendRoster *self, int question);
void FriendRoster_RunAction(FriendRoster *self);
unsigned char FriendRoster_EntryValue(FriendRoster *self, int row);
int FriendRoster_PlaceAt(FriendRoster *self, int x, int y);
int FriendRoster_PressCursorPlace(FriendRoster *self);
void FriendRoster_Refresh(FriendRoster *self, int index);
void FriendRoster_AddPlayer(FriendRoster *self);
void FriendRoster_OpenRegister(FriendRoster *self);
void FriendRoster_OpenTabWithFriend(FriendRoster *self, int tab);
void FriendRoster_DeleteFriend(FriendRoster *self);
void FriendRoster_AskDelete(FriendRoster *self);
void FriendRoster_OpenFriendChoice(FriendRoster *self);
void FriendRoster_OpenButtonChoice(FriendRoster *self);
int FriendRoster_MoveCursor(FriendRoster *self, int keys);
void FriendRoster_ShowCursorSprite(FriendRoster *self);
void FriendRoster_ReleaseCursorSprite(FriendRoster *self);
void FriendRoster_PressCursorSprite(FriendRoster *self);
void FriendRoster_PointAtChoice(FriendRoster *self);
int FriendRoster_CancelChoice(FriendRoster *self);
void FriendRoster_MoveToChoiceRow(FriendRoster *self);
void FriendRoster_EaseToCursor(FriendRoster *self);
void FriendRoster_HideCursorSprite(FriendRoster *self);
int FriendRoster_CursorY(FriendRoster *self);
int FriendRoster_CursorX(FriendRoster *self);
void FriendRoster_PlaceCursorSprite(FriendRoster *self);
void FriendRoster_ShowError(FriendRoster *self, unsigned char message);
void FriendRoster_ReturnToIdle(FriendRoster *self);
void FriendRoster_EnterKeys(FriendRoster *self);
void FriendRoster_EnterTouch(FriendRoster *self);
void FriendRoster_RetryDeleteFriend(FriendRoster *self);
void FriendRoster_RetrySetFriend(FriendRoster *self);
void FriendRoster_FadeIn(FriendRoster *self);
void FriendRoster_FadeOut(FriendRoster *self);
void FriendRoster_WaitError(FriendRoster *self);
void FriendRoster_RunActionWhenIdle(FriendRoster *self);
void FriendRoster_CloseChoice(FriendRoster *self);
void FriendRoster_WaitChoiceShown(FriendRoster *self);
void FriendRoster_FinishDelete(FriendRoster *self);
void FriendRoster_WaitToOpenChoice(FriendRoster *self);
void FriendRoster_PressChoiceRow(FriendRoster *self);
void FriendRoster_ChooseByKeys(FriendRoster *self);
void FriendRoster_FinishPress(FriendRoster *self);
void FriendRoster_PressPlace(FriendRoster *self);
void FriendRoster_WaitCursorSprite(FriendRoster *self);
void FriendRoster_BrowseByKeys(FriendRoster *self);
void FriendRoster_ChooseByTouch(FriendRoster *self);
void FriendRoster_IdleByTouch(FriendRoster *self);
void FriendRoster_SlideBarOut(FriendRoster *self);
int FriendRoster_SelectTab(FriendRoster *self, int tab);
int FriendRoster_TakeMenuKeys(FriendRoster *self);

#endif
