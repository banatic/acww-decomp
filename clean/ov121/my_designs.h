/* The scene of overlay 121 (vtable 0x0229c3a8, include/cpp/ov121/Obj_ov121_0229c3a8.h; its
 * profile at 0x0229c300 names the constructor MyDesigns_New, 0x1194 bytes): the "my designs"
 * tab of the pause menu, as the evidence says:
 *
 * - overlay 90's tab bar opens it as tab 1 (overlay group 3, ov090/menu_tabs.h);
 * - its files are "menu/desi/b_myd_obj.bch"/".bpl" (the designs' OBJs) and
 *   "menu/desi/b_myd_bg.bch"/".bpl" with the screen "menu/desi/b_myd_a_bg.bsc" (its buttons);
 * - it shows the current player's eight designs (main/design_sets.h) in the order the player
 *   keeps (`order`, a copy of PlayerDesigns' DesignOrder), each drawn from its own pixels and
 *   palette (MyDesigns_LoadDesignObjs).
 *
 * The screen has eight design places in two rows of four (MyDesignsPlace 0-7), eight buttons
 * (8-15) and, above them, the tab bar of overlay 90 (0x10-0x17). A design is picked up (by the
 * pen, or by A on the d-pad's cursor) and put down on another design (the two swap places) or on
 * a button, which uses it: as the menu backdrop's piece of clothing, as the room's carpet or
 * wallpaper, as clothes, head item or held item, as a piece of furniture of the room, or as a
 * pattern on the ground. Some buttons open a choice (ov002/paged_choice.h) of how; which ones
 * can be used depends on where the player is (`where`, MyDesigns_Setup).
 *
 * A pointer sprite (`pointer`, a Glider0 of ov002/glide.h) shows the d-pad's cursor; a popup
 * (`popup`) names the design under it or under the pen (`hover`). */
#ifndef CLEAN_OV121_MY_DESIGNS_H
#define CLEAN_OV121_MY_DESIGNS_H

#include "main/layer_load_task.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"
#include "ov002/popup.h"
#include "types.h"

/* In `flags`. */
enum MyDesignsFlag {
    MY_DESIGNS_FLAG_SHOWN = 0x0001,        /* the scene is drawn (MyDesigns_Draw) */
    MY_DESIGNS_FLAG_SCREEN_DIRTY = 0x0002, /* `screen` changed: it is queued to the buttons' layer */
    MY_DESIGNS_FLAG_CARRYING = 0x0004,     /* the design at place `picked` is carried */
    MY_DESIGNS_FLAG_TARGET_SHOWN = 0x0008, /* the mark over place `target` is drawn */
    MY_DESIGNS_FLAG_POINTER_JUMP = 0x0010, /* the pointer jumps to the cursor instead of easing, once
                                            * (nothing in this overlay sets it) */
    MY_DESIGNS_FLAG_WRAPPED_LEFT = 0x0020, /* this move wrapped the cursor around to the left */
    MY_DESIGNS_FLAG_WRAPPED_RIGHT = 0x0040,
    MY_DESIGNS_FLAG_PUT_BACK = 0x0080, /* the design carried by the d-pad is put back (B) */
    MY_DESIGNS_FLAG_BLINKING = 0x0200  /* button `blink_button` blinks (MyDesigns_StepBlink) */
};

#define MY_DESIGNS_FLAGS_WRAPPED (MY_DESIGNS_FLAG_WRAPPED_LEFT | MY_DESIGNS_FLAG_WRAPPED_RIGHT)

/* The places of the screen (`cursor`, `target`, ...), at the pixels of the tables
 * data_ov121_0229c248 (x) and data_ov121_0229c238 (y). */
enum MyDesignsPlace {
    MY_DESIGNS_DESIGN_FIRST = 0, /* 0-3: the top row of designs, 4-7 the bottom one */
    MY_DESIGNS_DESIGN_LAST = 7,
    MY_DESIGNS_BUTTON_BACKDROP = 8,   /* the menu backdrop's clothing (MyDesigns_UseAsBackdrop) */
    MY_DESIGNS_BUTTON_FURNITURE = 9,  /* furniture of the series 0x3f24 (MyDesigns_PlaceFurniture) */
    MY_DESIGNS_BUTTON_CARPET = 10,    /* the room's carpet, by a choice */
    MY_DESIGNS_BUTTON_WALLPAPER = 11, /* the room's wallpaper, by a choice */
    MY_DESIGNS_BUTTON_HEAD = 12,      /* the head item, or in the player's own room a choice */
    MY_DESIGNS_BUTTON_CLOTHES = 13,   /* the clothes, or in the player's own room a choice */
    MY_DESIGNS_BUTTON_HELD = 14,      /* the held item, or in the player's own room furniture */
    MY_DESIGNS_BUTTON_GROUND = 15,    /* a pattern on the ground (MyDesigns_DropOnGround) */
    MY_DESIGNS_TAB_FIRST = 0x10,      /* 0x10-0x17: the tab bar's tabs 0-7 */
    MY_DESIGNS_TAB_LAST = 0x17,
    MY_DESIGNS_NO_PLACE = 0x18
};

#define MY_DESIGNS_COUNT 8

/* Where the player is (`where`), which decides the buttons that cannot be used (`disabled`). */
enum MyDesignsWhere {
    MY_DESIGNS_OUTSIDE = 0,  /* not in a room (data_020e54a8 clear): no 9-11, no 15 for a guest */
    MY_DESIGNS_OWN_ROOM = 1, /* a house's room, not as a linked guest (MyDesigns_InOwnRoom): no 15 */
    MY_DESIGNS_ROOM = 2      /* another room: no 9-11, 14 or 15 */
};

/* What a row of the choice does (`action`, MyDesigns_RunChoiceAction). */
enum MyDesignsAction {
    MY_DESIGNS_ACTION_CARPET_0 = 0, /* the carpet, option 0 */
    MY_DESIGNS_ACTION_CARPET_1 = 1,
    MY_DESIGNS_ACTION_WALLPAPER_0 = 2,
    MY_DESIGNS_ACTION_WALLPAPER_1 = 3,
    MY_DESIGNS_ACTION_BACKDROP = 4,
    MY_DESIGNS_ACTION_CLOTHES = 5,
    MY_DESIGNS_ACTION_FURNITURE = 6,
    MY_DESIGNS_ACTION_HEAD = 7,
    MY_DESIGNS_ACTION_CANCEL = 8
};

/* What is worn (`wear_kind`, MyDesigns_WornItem). */
enum MyDesignsWearKind { MY_DESIGNS_WEAR_CLOTHES = 0, MY_DESIGNS_WEAR_HEAD = 1, MY_DESIGNS_WEAR_HELD = 2 };

/* The scene's sub states (MenuScene.sub_state), each run by its handler of the table of
 * MyDesigns_RunSubState. */
enum MyDesignsSubState {
    MY_DESIGNS_SUB_TOUCH = 0,             /* func_ov121_0229b764: the pen, until it touches a design */
    MY_DESIGNS_SUB_TOUCH_HOLD = 1,        /* func_ov121_0229b6f0: until the pen lifts or moves */
    MY_DESIGNS_SUB_DRAG = 2,              /* func_ov121_0229b64c: the pen carries a design */
    MY_DESIGNS_SUB_CHOICE_TOUCH = 3,      /* func_ov121_0229b574: the choice, by the pen */
    MY_DESIGNS_SUB_KEYS = 4,              /* func_ov121_0229b484: the d-pad's cursor */
    MY_DESIGNS_SUB_KEYS_CARRY = 5,        /* func_ov121_0229b40c: the cursor carries a design */
    MY_DESIGNS_SUB_POINTER_GLIDE = 6,     /* func_ov121_0229b3e0: until the pointer stops, then
                                           * `return_sub_state` */
    MY_DESIGNS_SUB_TAB_PRESS = 7,         /* func_ov121_0229b3a4: A on a tab */
    MY_DESIGNS_SUB_TAB_RELEASE = 8,       /* func_ov121_0229b37c */
    MY_DESIGNS_SUB_PICK_UP = 9,           /* func_ov121_0229b340: A on a design */
    MY_DESIGNS_SUB_PICKED_UP = 10,        /* func_ov121_0229b31c */
    MY_DESIGNS_SUB_PUT_DOWN = 11,         /* func_ov121_0229b2a4: A (or B) with a design carried */
    MY_DESIGNS_SUB_CHOICE_KEYS = 12,      /* func_ov121_0229b214: the choice, by the d-pad */
    MY_DESIGNS_SUB_CHOICE_KEY_PRESS = 13, /* func_ov121_0229b184: A on a row */
    MY_DESIGNS_SUB_CHOICE_OPENING = 14,   /* func_ov121_0229b148 */
    MY_DESIGNS_SUB_CHOICE_PICKED = 15,    /* func_ov121_0229b104 */
    MY_DESIGNS_SUB_CHOICE_CLOSING = 16,   /* func_ov121_0229b0e4: then the row's action */
    MY_DESIGNS_SUB_CHANGE_REQUEST = 17,   /* func_ov121_0229b0bc: until the player takes the change */
    MY_DESIGNS_SUB_CHANGE_WAIT = 18,      /* func_ov121_0229b09c: until the player is done */
    MY_DESIGNS_SUB_ERROR = 19,            /* func_ov121_0229b078: an error message */
    MY_DESIGNS_SUB_DROP_WAIT = 20,        /* func_ov121_0229b020: until the ground answers */
    MY_DESIGNS_SUB_STATES = 21
};

/* The scene's states (MenuScene.state), run in phase 1 (MyDesigns_RunState). */
enum MyDesignsState {
    MY_DESIGNS_STATE_START = 0,    /* MyDesigns_StartWipeIn */
    MY_DESIGNS_STATE_WIPE_IN = 1,  /* MyDesigns_WipeIn: then phase 2 */
    MY_DESIGNS_STATE_LEAVE = 2,    /* MyDesigns_StartWipeOut: the menu switched tabs */
    MY_DESIGNS_STATE_WIPE_OUT = 3, /* MyDesigns_WipeOut: then phase 5 */
    MY_DESIGNS_STATES = 4
};

/* The phases the scene sets (MenuScene.phase; ov090/menu_tabs.h). */
enum MyDesignsPhase {
    MY_DESIGNS_PHASE_STATES = 1,      /* vtable slot 0x4c: MyDesigns_RunState */
    MY_DESIGNS_PHASE_INTERACTIVE = 2, /* vtable slot 0x50: MyDesigns_RunInteractive */
    MY_DESIGNS_PHASE_DELETE = 5       /* vtable slot 0x5c: MyDesigns_End */
};

typedef struct MyDesigns {
    MenuScene base;             /* 0x00 */
    s32 wipe_y;                 /* 0x94: MenuScene_WipeOffsetY's, the designs drawn this far down */
    s32 drop_request;           /* 0x98: the ground's request (TileRequests_AskDrop), -1 none */
    u32 disabled;               /* 0x9c: bit n: place n cannot be used (MyDesigns_IsDisabled) */
    u16 item;                   /* 0xa0: the design item worn or dropped */
    u16 flags;                  /* 0xa2: MyDesignsFlag */
    s16 held_x;                 /* 0xa4: where the carried design is drawn */
    s16 held_y;                 /* 0xa6 */
    s16 grab_dx;                /* 0xa8: from the pen to the touched design's place */
    s16 grab_dy;                /* 0xaa */
    u8 where;                   /* 0xac: MyDesignsWhere */
    u8 hover;                   /* 0xad: the design place the popup names */
    u8 picked;                  /* 0xae: the design place carried (or MY_DESIGNS_NO_PLACE) */
    u8 target;                  /* 0xaf: the place the design is put down on */
    u8 highlighted;             /* 0xb0: the button lit under the pen (MY_DESIGNS_NO_PLACE: none) */
    u8 cursor;                  /* 0xb1: the d-pad's place */
    u8 action;                  /* 0xb2: MyDesignsAction of the row picked */
    u8 choice_row;              /* 0xb3 */
    u8 return_sub_state;        /* 0xb4: after MY_DESIGNS_SUB_POINTER_GLIDE */
    u8 blink_button;            /* 0xb5 */
    u8 blink_count;             /* 0xb6: frames left */
    u8 wear_kind;               /* 0xb7: MyDesignsWearKind */
    u16 backdrop_palette[16];   /* 0xb8: the backdrop's design (MenuBackdrop_QueueDesign) */
    u8 backdrop_chars[0x200];   /* 0xd8 */
    Popup popup;                /* 0x2d8 */
    Glider pointer;             /* 0x3a8: a Glider0 */
    ErrorMessage error;         /* 0x40c */
    u8 choice[0x3e8];           /* 0x528: a PagedChoice */
    ChoiceEntries entries;      /* 0x910: the choice's rows (MyDesigns_SetChoice) */
    LayerTaskPair tasks[2];     /* 0x91c: the buttons' screen, the backdrop's design */
    u16 screen[0x400];          /* 0x98c: the buttons' screen (layer 6) */
    u8 order[MY_DESIGNS_COUNT]; /* 0x118c: the design shown at each place */
} MyDesigns;

/* my_designs.c */
MyDesigns *MyDesigns_Destroy(MyDesigns *self);
MyDesigns *MyDesigns_Delete(MyDesigns *self);
void MyDesigns_ClearFlags(MyDesigns *self, unsigned short mask);
void MyDesigns_SetFlags(MyDesigns *self, unsigned short mask);
int MyDesigns_TestFlags(MyDesigns *self, int mask);
void MyDesigns_StepBlink(MyDesigns *self);
void MyDesigns_StartBlink(MyDesigns *self, unsigned char button);
int MyDesigns_MoveCursor(MyDesigns *self, int keys, int carrying);
void MyDesigns_MoveCursorVertically(MyDesigns *self, int keys, int carrying);
void MyDesigns_TabDownToDesigns(MyDesigns *self, int tab);
void MyDesigns_UpToTabs(MyDesigns *self);
int MyDesigns_MoveCursorAcross(MyDesigns *self, int keys, int carrying);
int MyDesigns_CursorTab(MyDesigns *self);
int MyDesigns_ShiftCursor(MyDesigns *self, unsigned int first, unsigned int last, int to);
int MyDesigns_ShiftCursor2(MyDesigns *self, unsigned int first, unsigned int last, int to);
int MyDesigns_StepCursorLeft(MyDesigns *self, unsigned int first, unsigned int last);
int MyDesigns_StepCursorRight(MyDesigns *self, unsigned int first, unsigned int last);
void MyDesigns_HeldAtPointer(MyDesigns *self);
void MyDesigns_BeginPutBack(MyDesigns *self);
void MyDesigns_BeginPutDown(MyDesigns *self);
void MyDesigns_BeginPickUp(MyDesigns *self);
void MyDesigns_BeginTabRelease(MyDesigns *self);
void MyDesigns_BeginTabPress(MyDesigns *self);
void MyDesigns_PointerFirstOfSet(MyDesigns *self);
void MyDesigns_PlacePointerAtCursor(MyDesigns *self);
void MyDesigns_PointAtFirstRow(MyDesigns *self);
void MyDesigns_CancelChoice(MyDesigns *self);
void MyDesigns_GlideToChoiceRow(MyDesigns *self);
void MyDesigns_GlidePointer(MyDesigns *self);
void MyDesigns_ResetPointer(MyDesigns *self);
int MyDesigns_PointerY(MyDesigns *self);
int MyDesigns_PointerX(MyDesigns *self);
void MyDesigns_ShowPointerAtCursor(MyDesigns *self);
void MyDesigns_QueuePopupAtCursor(MyDesigns *self);
void MyDesigns_SetPopupText(MyDesigns *self);
void MyDesigns_CloseChoiceOnRequest(MyDesigns *self);
void MyDesigns_OpenChoice(MyDesigns *self);
void MyDesigns_HeldAtPen(MyDesigns *self);
int MyDesigns_PenMoved(void);
int MyDesigns_IsDisabled(MyDesigns *self, int place);
void MyDesigns_Disable(MyDesigns *self, int place);
int MyDesigns_PlaceUnderHeld(MyDesigns *self);
int MyDesigns_DesignUnderPen(MyDesigns *self);
int MyDesigns_PlaceNear(MyDesigns *self, unsigned char x, unsigned char y, unsigned int last);
void MyDesigns_Highlight(MyDesigns *self, int place);
void MyDesigns_SetButtonPalette(MyDesigns *self, int button, int palette);
int MyDesigns_PlaceY(MyDesigns *self, unsigned int place);
int MyDesigns_PlaceX(MyDesigns *self, unsigned int place);
void MyDesigns_ShowError(MyDesigns *self, char message, int flag);
unsigned char *MyDesigns_BackToIdle(MyDesigns *self);
unsigned char *MyDesigns_EnterKeysIdle(MyDesigns *self);
unsigned char *MyDesigns_EnterTouchIdle(MyDesigns *self);
int MyDesigns_WaitError(MyDesigns *self);
void MyDesigns_WaitChoiceClosed(MyDesigns *self);
void MyDesigns_ChoicePicked(MyDesigns *self);
void MyDesigns_WaitChoiceOpen(MyDesigns *self);
void MyDesigns_ChoiceKeyPress(MyDesigns *self);
void MyDesigns_RunChoiceKeys(MyDesigns *self);
void MyDesigns_PutDown(MyDesigns *self);
void MyDesigns_PickedUp(MyDesigns *self);
void MyDesigns_PickUp(MyDesigns *self);
void MyDesigns_TabReleased(MyDesigns *self);
void MyDesigns_TabPressed(MyDesigns *self);
void MyDesigns_WaitPointer(MyDesigns *self);
void MyDesigns_RunKeysCarry(MyDesigns *self);
void MyDesigns_RunKeys(MyDesigns *self);
void MyDesigns_RunChoiceTouch(MyDesigns *self);
void MyDesigns_RunDrag(MyDesigns *self);
void MyDesigns_RunTouchHold(MyDesigns *self);
void MyDesigns_RunTouch(MyDesigns *self);
void MyDesigns_LoadDesignObjs(MyDesigns *self);
void MyDesigns_LoadButtons(MyDesigns *self);
void MyDesigns_SetUpLayer(void);
void MyDesigns_Update(MyDesigns *self);
void MyDesigns_Nothing(void *self);
void MyDesigns_UpdateAfterSubState(MyDesigns *self);
void MyDesigns_UpdatePointerFirst(MyDesigns *self);
void MyDesigns_Release(MyDesigns *self);
void MyDesigns_Setup(MyDesigns *self);
void MyDesigns_WipeOut(MyDesigns *self);
void MyDesigns_StartWipeOut(MyDesigns *self);
void MyDesigns_WipeIn(MyDesigns *self);
void MyDesigns_StartWipeIn(MyDesigns *self);
int MyDesigns_SwitchTab(MyDesigns *self, int tab);
int MyDesigns_CloseOrSwitchOnRequest(MyDesigns *self);
int MyDesigns_End(MyDesigns *self);
int MyDesigns_Phase4(void);
int MyDesigns_Phase3(void);
int MyDesigns_RunInteractive(MyDesigns *self);
void MyDesigns_RunSubState(MyDesigns *self);
int MyDesigns_RunState(MyDesigns *self);
int MyDesigns_Draw(MyDesigns *self);
int MyDesigns_Close(MyDesigns *self);
int MyDesigns_Begin(MyDesigns *self);
MyDesigns *MyDesigns_New(void);

/* my_designs_use.c */
int MyDesigns_MayChangeRoom(void);
int MyDesigns_IsChangeDone(MyDesigns *self, int kind);
int MyDesigns_RequestChange(MyDesigns *self, int kind, int item);
unsigned short MyDesigns_SwapWornItem(MyDesigns *self, int kind, unsigned short item);
unsigned short MyDesigns_WornItem(MyDesigns *self, int kind);
int MyDesigns_RestoreCamera(MyDesigns *self);
void MyDesigns_SaveCamera(MyDesigns *self);
void MyDesigns_RunChoiceAction(MyDesigns *self);
void MyDesigns_DropOnGround(MyDesigns *self);
void MyDesigns_PlaceFurniture(MyDesigns *self);
void MyDesigns_WearPicked(MyDesigns *self, u8 kind);
void MyDesigns_UseAsWallpaper(MyDesigns *self, int option);
void MyDesigns_UseAsCarpet(MyDesigns *self, int option);
void MyDesigns_UseAsBackdrop(MyDesigns *self);
unsigned char MyDesigns_RowAction(MyDesigns *self, unsigned int row);
void MyDesigns_SetChoice(MyDesigns *self, int choice);
int MyDesigns_DesignAt(MyDesigns *self, int place);
void MyDesigns_SwapPlaces(MyDesigns *self, int a, int b);
int MyDesigns_UseOnTarget(MyDesigns *self);
void MyDesigns_WaitDrop(MyDesigns *self);
void MyDesigns_WaitChange(MyDesigns *self);
int MyDesigns_WaitChangeRequest(MyDesigns *self);
int MyDesigns_InOwnRoom(void *self);

#endif
