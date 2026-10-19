/* The keyboard entry scene of overlay 126 (keyboard_entry.h): its screens, the setup by the mode,
 * the frames, the states (KeyboardEntryState), the vtable's slots and the constructor. */
#include "autoload_2/heap.h"
#include "autoload_2/network.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "keyboard_entry_calls.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/group_params.h"
#include "main/message_reader.h"
#include "main/oam_buffer.h"
#include "main/session.h"
#include "main/state_flags.h"
#include "main/text_base.h"
#include "main/text_string.h"
#include "ov004/member_pointer.h"
#include "ov090/menu_tabs.h"
#include "ov092/menu_dispatch.h"
#include "ov095/soft_keyboard.h"
#include "ov124/han_panel.h"

/* The heap the scene loads its files with. */
extern Heap *data_021fbe94;

/* The network session (main/session.h). */
extern NetSession *data_020ccf94;

/* The scene's vtable and files: "menu/han/obj.bpl", "menu/chat2/b_cht.bch",
 * "menu/letter/b_key.bsc"; and the hint's cell. */
extern const u8 data_ov126_022a20c8[];
extern const char data_ov126_022a2140[];
extern const char data_ov126_022a2154[];
extern const char data_ov126_022a216c[];
extern const OamEntry data_ov126_022a20b0[];

/* The labels' constructor and destructor, handed to __cxa_vec_ctor (the game's symbols). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void *func_02070c08(void *label);
extern int **func_02070be8(void *label);

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants. */
extern u32 data_ov126_022a21a0; /* the sub states' guard */
extern u32 data_ov126_022a21a4; /* the states' guard */
extern MemberPointer data_ov126_022a21a8[KEYBOARD_ENTRY_STATES];
extern MemberPointer data_ov126_022a2208[KEYBOARD_ENTRY_SUB_STATES];
extern const MemberPointer data_ov126_022a1fc8, data_ov126_022a1fd0, data_ov126_022a1fd8, data_ov126_022a1fe0,
    data_ov126_022a1fe8, data_ov126_022a1ff0, data_ov126_022a1ff8, data_ov126_022a2000, data_ov126_022a2008,
    data_ov126_022a2010, data_ov126_022a2018, data_ov126_022a2020, data_ov126_022a2028, data_ov126_022a2030,
    data_ov126_022a2038, data_ov126_022a2040, data_ov126_022a2048, data_ov126_022a2050, data_ov126_022a2058,
    data_ov126_022a2060, data_ov126_022a2068, data_ov126_022a2070, data_ov126_022a2078, data_ov126_022a2080,
    data_ov126_022a2088, data_ov126_022a2090, data_ov126_022a2098, data_ov126_022a20a0, data_ov126_022a20a8;

/* The menu's tabs the friend modes switch to (ov090/menu_tabs.h). */
#define KEYBOARD_ENTRY_TAB_6 6
#define KEYBOARD_ENTRY_TAB_CLOSE 7
#define KEYBOARD_ENTRY_TAB_10 10
#define KEYBOARD_ENTRY_TAB_12 12
#define KEYBOARD_ENTRY_TAB_14 14

/* What overlay 92's dispatcher is told when the scene ends (MENU_DISPATCH_MODE_CLOSE). */
#define KEYBOARD_ENTRY_DISPATCH_CLOSE 0x44

#define KEYBOARD_ENTRY_WIPE_MARGIN 0x30

static Process *keyboard_entry_parent(KeyboardEntry *self)
{
    return Process_GetParent((Process *) (void *) self);
}

static int keyboard_entry_is_friend_mode(unsigned int mode)
{
    return mode >= KEYBOARD_ENTRY_FIRST_FRIEND_MODE && mode <= KEYBOARD_ENTRY_LAST_FRIEND_MODE;
}

/* --- The screens --- */

/* func_ov126_022a12d4: the keyboard's files and the field's, the palettes of "menu/han/obj.bpl"
 * on the sub screen's objects, the panel's text colours; with the hint, its message (0x80 for
 * a constellation, else 0x66, after main's message part 0 is set from an empty label) opened in
 * its box and shown. */
void KeyboardEntry_LoadField(KeyboardEntry *self)
{
    SoftKeyboard_LoadObjGraphics(keyboard_entry_keyboard(self));
    HanPanel_LoadSign((HanPanel *) (void *) self->field, KEYBOARD_ENTRY_LAYER);
    DisplayLayer_LoadPalettesFromFile(data_ov126_022a2140, data_021fbe94, LAYER_SUB_OBJ, 5, 5, 5);
    ButtonPanel_LoadTextColors(&self->panel);
    if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_HINT) != 0) {
        TextLabel empty;
        TextLabel_Construct(&empty);
        TextBase_Clear(&empty);
        MessageReader_SetPart(0, (int) (uintptr_t) &empty);
        if (GroupParams_Mode() == KEYBOARD_ENTRY_MODE_CONSTELLATION) {
            TextLabel_LoadMenuMessage((int) (uintptr_t) &self->hint, (char) 0x80);
        } else {
            TextLabel_LoadMenuMessage((int) (uintptr_t) &self->hint, 0x66);
        }
        TextLabel_OpenStyledBox2(&self->hint, 8, 0x1c0, 6, 15, 0, 0);
        TextLabel_Show(&self->hint, 0, 0);
        TextLabel_Destruct(&empty);
    }
}
CLEAN_AS(func_ov126_022a12d4, KeyboardEntry_LoadField)

/* func_ov126_022a1394: the field's screen on background 1, the characters
 * "menu/chat2/b_cht.bch" there, the keyboard's screen "menu/letter/b_key.bsc", the keys the text
 * allows, and the keyboard's own on background 3. */
void KeyboardEntry_LoadScreens(KeyboardEntry *self)
{
    HanPanel_LoadStyledBackground((HanPanel *) (void *) self->field, KEYBOARD_ENTRY_FIELD_LAYER);
    DisplayLayer_LoadCharsFromFile(data_ov126_022a2154, data_021fbe94, KEYBOARD_ENTRY_FIELD_LAYER, 0x13d, 0x13d, 0x1e9);
    SoftKeyboard_ReadScreen(keyboard_entry_keyboard(self), (const char *) (void *) data_ov126_022a216c);
    KeyboardEntry_UpdateKeys(self);
    SoftKeyboard_LoadScreenNow(keyboard_entry_keyboard(self), KEYBOARD_ENTRY_LAYER);
    SoftKeyboard_LoadLetterChars(keyboard_entry_keyboard(self), KEYBOARD_ENTRY_LAYER);
}
CLEAN_AS(func_ov126_022a1394, KeyboardEntry_LoadScreens)

/* func_ov126_022a13fc: the sub screen in background mode 0, background 1 at priority 3 and
 * background 3 at priority 2, both in their first size with 16 colours from characters 0. */
void KeyboardEntry_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(KEYBOARD_ENTRY_FIELD_LAYER, 3);
    DisplayLayer_SetBgControl(KEYBOARD_ENTRY_FIELD_LAYER, 0, 0, 0);
    DisplayLayer_SetPriority(KEYBOARD_ENTRY_LAYER, 2);
    DisplayLayer_SetBgControl(KEYBOARD_ENTRY_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov126_022a13fc, KeyboardEntry_SetUpLayers)

/* --- The frames --- */

/* func_ov126_022a1434: a frame's end: the keyboard drawn on background 3. */
void KeyboardEntry_EndFrame(KeyboardEntry *self)
{
    SoftKeyboard_QueueScreen(keyboard_entry_keyboard(self), KEYBOARD_ENTRY_LAYER);
}
CLEAN_AS(func_ov126_022a1434, KeyboardEntry_EndFrame)

/* func_ov126_022a1448: a frame's start: the field not yet shown, and the boxes of the field, the
 * panel and the hint closed. */
void KeyboardEntry_BeginFrame(KeyboardEntry *self)
{
    KeyboardEntry_ClearFlags(self, KEYBOARD_ENTRY_FLAG_FIELD_SHOWN);
    HanPanel_CloseTexts((HanPanel *) (void *) self->field);
    ButtonPanel_CloseTexts(&self->panel);
    TextLabel_CloseBox(&self->hint);
}
CLEAN_AS(func_ov126_022a1448, KeyboardEntry_BeginFrame)

/* func_ov126_022a1478: the input's frame end. */
void KeyboardEntry_EndInputFrame(KeyboardEntry *self)
{
    KeyboardEntry_EndFrame(self);
}
CLEAN_AS(func_ov126_022a1478, KeyboardEntry_EndInputFrame)

/* func_ov126_022a1480: the input's frame start, and the pointer updated (vtable slot 3). */
void KeyboardEntry_BeginInputFrame(KeyboardEntry *self)
{
    KeyboardEntry_BeginFrame(self);
    keyboard_entry_update_pointer(self);
}
CLEAN_AS(func_ov126_022a1480, KeyboardEntry_BeginInputFrame)

/* func_ov126_022a149c: the members' boxes closed and the keyboard's own teardown. */
void KeyboardEntry_Teardown(KeyboardEntry *self)
{
    HanPanel_CloseTexts((HanPanel *) (void *) self->field);
    SoftKeyboard_Finish(keyboard_entry_keyboard(self));
    ButtonPanel_CloseTexts(&self->panel);
    TextLabel_CloseBox(&self->hint);
}
CLEAN_AS(func_ov126_022a149c, KeyboardEntry_Teardown)

/* func_ov126_022a14d0: the scene set up for GroupParams' mode: the panel's kind (the two buttons
 * and other sounds for a friend being added), the keyboard's mode by it, the field's size and
 * place by its kind, the text loaded (kept only when not blank) and the hint for modes 0x10,
 * 0x12, 0x18 and 0x19. A mode not listed keeps the panel's kind the scene had. */
void KeyboardEntry_Setup(KeyboardEntry *self)
{
    self->flags = 0;
    self->hint_x = 0;
    int mode = GroupParams_Mode();
    switch (mode) {
        case KEYBOARD_ENTRY_MODE_DESIGN_TITLE:
        case KEYBOARD_ENTRY_MODE_GENERAL_WORD:
        case KEYBOARD_ENTRY_MODE_SONG:
        case KEYBOARD_ENTRY_MODE_PASSWORD:
        case KEYBOARD_ENTRY_MODE_PLAYER_NAME:
        case KEYBOARD_ENTRY_MODE_TOWN_NAME:
        case KEYBOARD_ENTRY_MODE_11:
        case KEYBOARD_ENTRY_MODE_CONSTELLATION:
        case KEYBOARD_ENTRY_MODE_13:
        case KEYBOARD_ENTRY_MODE_RECORD_DESIGN_TITLE:
        case KEYBOARD_ENTRY_MODE_15:
        case 0x16:
        case KEYBOARD_ENTRY_MODE_17:
        case KEYBOARD_ENTRY_MODE_FRIEND_TEXT_18:
        case KEYBOARD_ENTRY_MODE_FRIEND_TEXT_0C:
            self->panel_kind = KEYBOARD_ENTRY_PANEL_OK;
            break;
        case KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_18:
        case KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_0C:
            KeyboardEntry_SetFlags(self, KEYBOARD_ENTRY_FLAG_NEW_FRIEND);
            self->panel_kind = KEYBOARD_ENTRY_PANEL_OK_CANCEL;
            break;
    }
    switch (self->panel_kind) {
        case KEYBOARD_ENTRY_PANEL_OK_CANCEL:
            SoftKeyboard_Init(keyboard_entry_keyboard(self), 5);
            break;
        case KEYBOARD_ENTRY_PANEL_CANCEL:
        case KEYBOARD_ENTRY_PANEL_OK:
            SoftKeyboard_Init(keyboard_entry_keyboard(self), 4);
            break;
        case KEYBOARD_ENTRY_PANEL_NONE:
            SoftKeyboard_Init(keyboard_entry_keyboard(self), 3);
            break;
    }
    switch (HanPanel_TextStyle((HanPanel *) (void *) self->field)) {
        case KEYBOARD_ENTRY_FIELD_10:
            self->max_chars = 10;
            self->field_left = 0x52;
            self->field_right = 0xb8;
            self->field_width = 0x68;
            break;
        case KEYBOARD_ENTRY_FIELD_6:
            self->max_chars = 6;
            self->field_left = 0x62;
            self->field_right = 0xa0;
            self->field_width = 0x40;
            break;
        case KEYBOARD_ENTRY_FIELD_16:
            self->max_chars = 16;
            self->field_left = 0x30;
            self->field_right = 0xd0;
            self->field_width = 0xa0;
            break;
        case KEYBOARD_ENTRY_FIELD_4:
            self->max_chars = 4;
            self->field_left = 0x68;
            self->field_right = 0x90;
            self->field_width = 0x28;
            break;
        case KEYBOARD_ENTRY_FIELD_8:
            self->max_chars = 8;
            self->field_left = 0x58;
            self->field_right = 0xa8;
            self->field_width = 0x50;
            break;
    }
    TextString_ClearChars(self->text, KEYBOARD_ENTRY_TEXT_CHARS);
    TextString_ClearChars(self->clipboard, KEYBOARD_ENTRY_TEXT_CHARS);
    KeyboardEntry_LoadText(self);
    if (TextString_TrimmedLength(self->text, self->max_chars) == 0) {
        TextString_ClearChars(self->text, KEYBOARD_ENTRY_TEXT_CHARS);
    }
    if (mode == KEYBOARD_ENTRY_MODE_TOWN_NAME || mode == KEYBOARD_ENTRY_MODE_FRIEND_TEXT_18 ||
        mode == KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_18 || mode == KEYBOARD_ENTRY_MODE_CONSTELLATION) {
        KeyboardEntry_SetFlags(self, KEYBOARD_ENTRY_FLAG_HINT);
    }
}
CLEAN_AS(func_ov126_022a14d0, KeyboardEntry_Setup)

/* func_ov126_022a16ac: backgrounds 1 and 3 follow the wipe, whose y is kept. */
void KeyboardEntry_ScrollWipe(KeyboardEntry *self)
{
    MenuScene_ScrollWipe(keyboard_entry_scene(self), KEYBOARD_ENTRY_FIELD_LAYER, 0, 0);
    MenuScene_ScrollWipe(keyboard_entry_scene(self), KEYBOARD_ENTRY_LAYER, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(keyboard_entry_scene(self));
}
CLEAN_AS(func_ov126_022a16ac, KeyboardEntry_ScrollWipe)

/* --- The states, from the last --- */

/* func_ov126_022a16d8 (KEYBOARD_ENTRY_STATE_BACK_WIPE_IN): the panel wipes back in; then phase 2
 * and the input. */
void KeyboardEntry_BackWipeIn(KeyboardEntry *self)
{
    if (MenuScene_StepWipeBack(keyboard_entry_scene(self), -1)) {
        MenuScene_SetPhase(keyboard_entry_scene(self), KEYBOARD_ENTRY_PHASE_INPUT);
        KeyboardEntry_BeginInput(self);
    }
}
CLEAN_AS(func_ov126_022a16d8, KeyboardEntry_BackWipeIn)

/* func_ov126_022a16fc (KEYBOARD_ENTRY_STATE_BACK_WIPE_OUT): the question wipes out; then the
 * input's panel set again, wiping in (state 11). */
void KeyboardEntry_BackWipeOut(KeyboardEntry *self)
{
    if (MenuScene_StepWipe(keyboard_entry_scene(self), -1)) {
        MenuScene_StartWipeCovered(keyboard_entry_scene(self), 0, 0);
        KeyboardEntry_SetPanelLayout(self);
        MenuScene_SetState(keyboard_entry_scene(self), KEYBOARD_ENTRY_STATE_BACK_WIPE_IN);
    }
}
CLEAN_AS(func_ov126_022a16fc, KeyboardEntry_BackWipeOut)

/* func_ov126_022a172c (KEYBOARD_ENTRY_STATE_BACK): the question starts to wipe out (state 10). */
void KeyboardEntry_StartBack(KeyboardEntry *self)
{
    MenuScene_StartWipe(keyboard_entry_scene(self), 0, 0);
    MenuScene_SetState(keyboard_entry_scene(self), KEYBOARD_ENTRY_STATE_BACK_WIPE_OUT);
}
CLEAN_AS(func_ov126_022a172c, KeyboardEntry_StartBack)

/* func_ov126_022a1748 (KEYBOARD_ENTRY_STATE_ASK_WIPE_IN): the question wipes in; then phase 2
 * and its buttons. */
void KeyboardEntry_AskWipeIn(KeyboardEntry *self)
{
    if (MenuScene_StepWipeBack(keyboard_entry_scene(self), -1)) {
        MenuScene_SetPhase(keyboard_entry_scene(self), KEYBOARD_ENTRY_PHASE_INPUT);
        KeyboardEntry_BeginAsk(self);
    }
}
CLEAN_AS(func_ov126_022a1748, KeyboardEntry_AskWipeIn)

/* func_ov126_022a176c (KEYBOARD_ENTRY_STATE_ASK_WIPE_OUT): the panel wipes out; then the question
 * (layout 9 with message 0x87 when cancelling, else 0x22) wipes in (state 8). */
void KeyboardEntry_AskWipeOut(KeyboardEntry *self)
{
    if (MenuScene_StepWipe(keyboard_entry_scene(self), -1) == 0) {
        return;
    }
    MenuScene_StartWipeCovered(keyboard_entry_scene(self), 0, 0);
    if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_CANCELLED) != 0) {
        ButtonPanel_SetLayout9(&self->panel, 0x87);
    } else {
        ButtonPanel_SetLayout9(&self->panel, 0x22);
    }
    MenuScene_SetState(keyboard_entry_scene(self), KEYBOARD_ENTRY_STATE_ASK_WIPE_IN);
}
CLEAN_AS(func_ov126_022a176c, KeyboardEntry_AskWipeOut)

/* func_ov126_022a17bc (KEYBOARD_ENTRY_STATE_ASK): the panel starts to wipe out (state 7). */
void KeyboardEntry_StartAsk(KeyboardEntry *self)
{
    MenuScene_StartWipe(keyboard_entry_scene(self), 0, 0);
    MenuScene_SetState(keyboard_entry_scene(self), KEYBOARD_ENTRY_STATE_ASK_WIPE_OUT);
}
CLEAN_AS(func_ov126_022a17bc, KeyboardEntry_StartAsk)

/* func_ov126_022a17d8 (KEYBOARD_ENTRY_STATE_WIPE_OUT): the scene wipes out, backgrounds 1 and 3
 * following; when done they are hidden, the scene no longer drawn, phase 5 (the end), and main
 * told the outcome: cancelled (0), or done (1) with the text committed and handed to main; the
 * friend modes but 0x1b tell the menu the roster changed. */
void KeyboardEntry_WipeOut(KeyboardEntry *self)
{
    if (MenuScene_StepWipe(keyboard_entry_scene(self), 0) == 0) {
        KeyboardEntry_ScrollWipe(self);
        return;
    }
    DisplayLayer_HideAndResetScroll(KEYBOARD_ENTRY_FIELD_LAYER);
    DisplayLayer_HideAndResetScroll(KEYBOARD_ENTRY_LAYER);
    KeyboardEntry_ClearFlags(self, KEYBOARD_ENTRY_FLAG_DRAWN);
    MenuScene_SetPhase(keyboard_entry_scene(self), KEYBOARD_ENTRY_PHASE_END);
    if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_CANCELLED)) {
        GroupParams_SetC4C(KEYBOARD_ENTRY_OUTCOME_CANCELLED);
        return;
    }
    GroupParams_SetC4C(KEYBOARD_ENTRY_OUTCOME_DONE);
    KeyboardEntry_Commit(self);
    GroupParams_SetText(self->text, self->max_chars);
    int mode = GroupParams_Mode();
    if (mode == KEYBOARD_ENTRY_MODE_FRIEND_TEXT_18 || mode == KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_18 ||
        mode == KEYBOARD_ENTRY_MODE_FRIEND_TEXT_0C) {
        MenuTabs_MarkRosterChanged((MenuTabs *) (void *) keyboard_entry_parent(self));
    }
}
CLEAN_AS(func_ov126_022a17d8, KeyboardEntry_WipeOut)

/* func_ov126_022a185c (KEYBOARD_ENTRY_STATE_ADD_FRIEND): the friend's data handed to the
 * connection, each frame until it takes it; then the scene wipes out on window 2 (state 5). */
void KeyboardEntry_AddFriend(KeyboardEntry *self)
{
    WifiFriend *entry = KeyboardEntry_Friend();
    int index = GroupParams_Arg();
    WifiFriendData *data = WifiFriendData_GetData(WifiFriend_GetFriendData(entry));
    if (Wfc_SetFriend(index, data) != 0) {
        MenuScene_StartWipeOnWindow2(keyboard_entry_scene(self), 10, 0, 0, KEYBOARD_ENTRY_WIPE_MARGIN);
        KeyboardEntry_ScrollWipe(self);
        MenuScene_SetState(keyboard_entry_scene(self), KEYBOARD_ENTRY_STATE_WIPE_OUT);
    }
}
CLEAN_AS(func_ov126_022a185c, KeyboardEntry_AddFriend)

/* func_ov126_022a18ac (KEYBOARD_ENTRY_STATE_FINISH): the text cursor hidden and the parent told
 * what comes next. The friend modes switch overlay 90's menu to a tab: 6 (for 0x18 and 0x1a, and
 * 0x19 when not cancelled, with state flag 0x200 set unless cancelled), 12 (0x19 cancelled), 10 or
 * 14 (0x1b, done or cancelled); a friend added (0x19) while the session's own slot is taken and
 * the network is in mode 3 or 4 goes to the connection first (state 4). Overlay 92's dispatcher
 * is told the scene closes. Then the scene wipes out on window 2 (state 5). */
void KeyboardEntry_Finish(KeyboardEntry *self)
{
    KeyboardEntry_ClearFlags(self, KEYBOARD_ENTRY_FLAG_CURSOR_SHOWN);
    unsigned int mode = GroupParams_Mode();
    if (keyboard_entry_is_friend_mode(mode)) {
        MenuTabs *menu = (MenuTabs *) (void *) keyboard_entry_parent(self);
        switch (mode) {
            case KEYBOARD_ENTRY_MODE_FRIEND_TEXT_18:
            case KEYBOARD_ENTRY_MODE_FRIEND_TEXT_0C:
                MenuTabs_SelectTab(menu, KEYBOARD_ENTRY_TAB_6);
                if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_CANCELLED) == 0) {
                    StateFlags_Set200();
                }
                break;
            case KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_18:
                if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_CANCELLED) != 0) {
                    MenuTabs_SelectTab(menu, KEYBOARD_ENTRY_TAB_12);
                    break;
                }
                MenuTabs_SelectTab(menu, KEYBOARD_ENTRY_TAB_6);
                StateFlags_Set200();
                if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
                    int net_mode = Net_GetMode();
                    if (net_mode == 3 || net_mode == 4) {
                        MenuScene_SetState(keyboard_entry_scene(self), KEYBOARD_ENTRY_STATE_ADD_FRIEND);
                        KeyboardEntry_AddFriend(self);
                        return;
                    }
                }
                break;
            case KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_0C:
                if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_CANCELLED) != 0) {
                    MenuTabs_SelectTab(menu, KEYBOARD_ENTRY_TAB_14);
                } else {
                    MenuTabs_SelectTab(menu, KEYBOARD_ENTRY_TAB_10);
                }
                break;
        }
    } else {
        MenuDispatch_SetMode((MenuDispatch *) (void *) keyboard_entry_parent(self), KEYBOARD_ENTRY_DISPATCH_CLOSE, 1);
    }
    MenuScene_StartWipeOnWindow2(keyboard_entry_scene(self), 10, 0, 0, KEYBOARD_ENTRY_WIPE_MARGIN);
    KeyboardEntry_ScrollWipe(self);
    MenuScene_SetState(keyboard_entry_scene(self), KEYBOARD_ENTRY_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov126_022a18ac, KeyboardEntry_Finish)

/* func_ov126_022a19a8 (KEYBOARD_ENTRY_STATE_WIPE_IN): the scene wipes in, backgrounds 1 and 3
 * following; then phase 2, the input and the text cursor shown. */
void KeyboardEntry_WipeIn(KeyboardEntry *self)
{
    if (MenuScene_StepWipeBack(keyboard_entry_scene(self), 0) != 0) {
        MenuScene_SetPhase(keyboard_entry_scene(self), KEYBOARD_ENTRY_PHASE_INPUT);
        KeyboardEntry_BeginInput(self);
        KeyboardEntry_ShowCursor(self);
    }
    KeyboardEntry_ScrollWipe(self);
}
CLEAN_AS(func_ov126_022a19a8, KeyboardEntry_WipeIn)

/* func_ov126_022a19d8 (KEYBOARD_ENTRY_STATE_START_WIPE_IN): the keyboard set up in main's mode on
 * background 3, the field's files, the field shown, the panel's layout; backgrounds 1 and 3 shown
 * and wiping in on window 2 (state 2), the scene drawn. */
void KeyboardEntry_StartWipeIn(KeyboardEntry *self)
{
    SoftKeyboard_LoadSavedLayout(keyboard_entry_keyboard(self), KEYBOARD_ENTRY_LAYER);
    KeyboardEntry_LoadField(self);
    KeyboardEntry_ShowField(self);
    KeyboardEntry_SetPanelLayout(self);
    MenuScene_StartWipeCoveredOnWindow2(keyboard_entry_scene(self), 10, 4, 0, KEYBOARD_ENTRY_WIPE_MARGIN);
    DisplayLayer_Show(KEYBOARD_ENTRY_FIELD_LAYER);
    DisplayLayer_Show(KEYBOARD_ENTRY_LAYER);
    KeyboardEntry_ScrollWipe(self);
    KeyboardEntry_SetFlags(self, KEYBOARD_ENTRY_FLAG_DRAWN);
    MenuScene_SetState(keyboard_entry_scene(self), KEYBOARD_ENTRY_STATE_WIPE_IN);
}
CLEAN_AS(func_ov126_022a19d8, KeyboardEntry_StartWipeIn)

/* func_ov126_022a1a38 (KEYBOARD_ENTRY_STATE_LOAD): the layers set up and the screens loaded,
 * then state 1. */
void KeyboardEntry_LoadState(KeyboardEntry *self)
{
    KeyboardEntry_SetUpLayers();
    KeyboardEntry_LoadScreens(self);
    MenuScene_SetState(keyboard_entry_scene(self), KEYBOARD_ENTRY_STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov126_022a1a38, KeyboardEntry_LoadState)

/* --- The vtable's slots --- */

/* func_ov126_022a1a54 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int KeyboardEntry_End(KeyboardEntry *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov126_022a1a54, KeyboardEntry_End)

/* func_ov126_022a1a64 (vtable slot 0x58): nothing. Answers 1. */
int KeyboardEntry_Slot58(void)
{
    return 1;
}
CLEAN_AS(func_ov126_022a1a64, KeyboardEntry_Slot58)

/* func_ov126_022a1a68 (vtable slot 0x54): nothing. Answers 1. */
int KeyboardEntry_Slot54(void)
{
    return 1;
}
CLEAN_AS(func_ov126_022a1a68, KeyboardEntry_Slot54)

/* Obj_ov126_022a20c8::func_ov126_022a1a6c (vtable slot 0x50, phase 2): a frame of the input. The
 * menu close's delay is counted first; when the menu is asked to close in a friend mode, in a sub
 * state other than the question's (3, 5), the glide (8) and 15 and 16, the input ends cancelled:
 * the cursor hidden, the pointer at rest, the menu closed (tab 7), the scene wiping out on window
 * 2 (state 5, phase 1), and a friend being added cleared from the roster. Then the frame's start,
 * its sub state and its end. Answers 1. */
int KeyboardEntry_RunInput(KeyboardEntry *self)
{
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked()) {
        unsigned int mode = GroupParams_Mode();
        if (keyboard_entry_is_friend_mode(mode)) {
            switch (self->base.sub_state) {
                case KEYBOARD_ENTRY_SUB_TOUCH:
                case KEYBOARD_ENTRY_SUB_MARK_DRAG:
                case KEYBOARD_ENTRY_SUB_KEY_TOUCH_HELD:
                case KEYBOARD_ENTRY_SUB_KEYS:
                case KEYBOARD_ENTRY_SUB_TEXT_KEYS:
                case KEYBOARD_ENTRY_SUB_MARK_KEYS:
                case KEYBOARD_ENTRY_SUB_KEY_PRESS:
                case KEYBOARD_ENTRY_SUB_KEY_REPEAT:
                case KEYBOARD_ENTRY_SUB_BACK_TO_KEYS:
                case KEYBOARD_ENTRY_SUB_BACKSPACE:
                case KEYBOARD_ENTRY_SUB_WHILE_L:
                case KEYBOARD_ENTRY_SUB_WHILE_R:
                    KeyboardEntry_ClearFlags(self, KEYBOARD_ENTRY_FLAG_CURSOR_SHOWN);
                    KeyboardEntry_RestPointer(self);
                    MenuTabs_SelectTab((MenuTabs *) (void *) keyboard_entry_parent(self), KEYBOARD_ENTRY_TAB_CLOSE);
                    KeyboardEntry_SetFlags(self, KEYBOARD_ENTRY_FLAG_CANCELLED);
                    MenuScene_StartWipeOnWindow2(keyboard_entry_scene(self), 10, 0, 0, KEYBOARD_ENTRY_WIPE_MARGIN);
                    KeyboardEntry_ScrollWipe(self);
                    MenuScene_SetState(keyboard_entry_scene(self), KEYBOARD_ENTRY_STATE_WIPE_OUT);
                    MenuScene_SetPhase(keyboard_entry_scene(self), KEYBOARD_ENTRY_PHASE_STATES);
                    if (mode == KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_18 || mode == KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_0C) {
                        WifiFriend_Clear(KeyboardEntry_Friend());
                    }
                    break;
                default:
                    break;
            }
        }
    }
    KeyboardEntry_BeginInputFrame(self);
    KeyboardEntry_RunSubState(self);
    KeyboardEntry_EndInputFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov126_022a20c819func_ov126_022a1a6cEv, KeyboardEntry_RunInput)

/* Obj_ov126_022a20c8::func_ov126_022a1b4c: the sub state's function (KeyboardEntrySubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 17; the game reads past the table for others. */
void KeyboardEntry_RunSubState(KeyboardEntry *self)
{
    static const MemberPointer *const sub_states[KEYBOARD_ENTRY_SUB_STATES] = {
        &data_ov126_022a1ff0, &data_ov126_022a2038, &data_ov126_022a2028, &data_ov126_022a2040, &data_ov126_022a2020,
        &data_ov126_022a2018, &data_ov126_022a2010, &data_ov126_022a2008, &data_ov126_022a2000, &data_ov126_022a2048,
        &data_ov126_022a1fc8, &data_ov126_022a2030, &data_ov126_022a1fe8, &data_ov126_022a1fd8, &data_ov126_022a1fd0,
        &data_ov126_022a1ff8, &data_ov126_022a1fe0,
    };
    MemberTable_InitOnce(&data_ov126_022a21a0, data_ov126_022a2208, sub_states, KEYBOARD_ENTRY_SUB_STATES);
    MemberPointer_CallVoid(&data_ov126_022a2208[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov126_022a20c819func_ov126_022a1b4cEv, KeyboardEntry_RunSubState)

/* Obj_ov126_022a20c8::func_ov126_022a1c8c (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (KeyboardEntryState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 12; the game reads past the table for others. */
int KeyboardEntry_RunState(KeyboardEntry *self)
{
    static const MemberPointer *const states[KEYBOARD_ENTRY_STATES] = {
        &data_ov126_022a20a8, &data_ov126_022a20a0, &data_ov126_022a2098, &data_ov126_022a2090,
        &data_ov126_022a2088, &data_ov126_022a2080, &data_ov126_022a2078, &data_ov126_022a2070,
        &data_ov126_022a2068, &data_ov126_022a2060, &data_ov126_022a2058, &data_ov126_022a2050,
    };
    MemberTable_InitOnce(&data_ov126_022a21a4, data_ov126_022a21a8, states, KEYBOARD_ENTRY_STATES);
    KeyboardEntry_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov126_022a21a8[self->base.state], self);
    KeyboardEntry_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov126_022a20c819func_ov126_022a1c8cEv, KeyboardEntry_RunState)

/* func_ov126_022a1d90 (vtable slot 0x24): the scene's draw, while it is drawn (else 0): the
 * pointer (with the buttons in use), the field and the panel at the wipe's y, the keyboard's
 * frame cells and mode tabs, the hint's cell after the text, and the text cursor while bit 4 of
 * its blink is set (the blink counts the frames it is shown). Answers 1. */
int KeyboardEntry_Draw(KeyboardEntry *self)
{
    s32 y = self->wipe_y;
    if (!KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_DRAWN)) {
        return 0;
    }
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->pointer);
    }
    HanPanel_DrawWithSign((HanPanel *) (void *) self->field, 0, y);
    ButtonPanel_Draw(&self->panel, MenuScene_WipeOffsetY(keyboard_entry_scene(self)));
    SoftKeyboard_DrawTabRow(keyboard_entry_keyboard(self), 0x80, y + 0x60, 1);
    SoftKeyboard_DrawSideButtons(keyboard_entry_keyboard(self), 0x80, y + 0x60);
    if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_HINT)) {
        OamBuffer_DrawCell(1, data_ov126_022a20b0, self->hint_x + 0x80, y + 0x60, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_CURSOR_SHOWN)) {
        s32 x = self->cursor_x;
        s32 cursor_y = self->cursor_y;
        self->blink++;
        if ((self->blink & 0x10) != 0) {
            SoftKeyboard_DrawCaret(keyboard_entry_keyboard(self), x, cursor_y, 2);
        }
    }
    return 1;
}
CLEAN_AS(func_ov126_022a1d90, KeyboardEntry_Draw)

/* func_ov126_022a1e8c (vtable slot 0x0c): the scene closes: overlay 90's menu told (in a friend
 * mode; it slides its bar in when the tab it goes back to is 6) or overlay 92's dispatcher, then
 * the teardown. Answers 1. */
int KeyboardEntry_Close(KeyboardEntry *self)
{
    unsigned int mode = GroupParams_Mode();
    if (keyboard_entry_is_friend_mode(mode)) {
        MenuTabs *menu = (MenuTabs *) (void *) keyboard_entry_parent(self);
        if (MenuTabs_ChildClosed(menu) == KEYBOARD_ENTRY_TAB_6) {
            MenuTabs_SlideIn(menu);
        }
    } else {
        MenuDispatch_ChildClosed((MenuDispatch *) (void *) keyboard_entry_parent(self));
    }
    KeyboardEntry_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov126_022a1e8c, KeyboardEntry_Close)

/* func_ov126_022a1ed0 (vtable slot 0x00): the scene starts: its setup, state 0 and phase 0.
 * Answers 1. */
int KeyboardEntry_Start(KeyboardEntry *self)
{
    KeyboardEntry_Setup(self);
    self->base.state = KEYBOARD_ENTRY_STATE_LOAD;
    MenuScene_SetPhase(keyboard_entry_scene(self), KEYBOARD_ENTRY_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov126_022a1ed0, KeyboardEntry_Start)

/* func_ov126_022a1ef0: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed in order, the keyboard's two tasks one by
 * one and the two labels by __cxa_vec_ctor. */
KeyboardEntry *KeyboardEntry_New(void)
{
    KeyboardEntry *self = MenuScene_Alloc(sizeof(KeyboardEntry));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov126_022a20c8;
    HanPanel_Construct((HanPanel *) (void *) self->field);
    for (int i = 0; i < 2; i++) {
        LayerTask_Construct(&self->tasks[i]);
    }
    __cxa_vec_ctor(self->labels, 2, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    ButtonPanel_Construct(&self->panel);
    Glider0_Construct(&self->pointer);
    TextLabel_Construct(&self->hint);
    TextLabel_Construct(&self->filter_text);
    WideText_Construct(&self->filter_wide);
    ErrorMessage_Construct(&self->error);
    return self;
}
CLEAN_AS(func_ov126_022a1ef0, KeyboardEntry_New)
