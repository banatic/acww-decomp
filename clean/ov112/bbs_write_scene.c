/* The bulletin board writing scene of overlay 112 (bbs_write_scene.h): its graphics and setup,
 * the frame's start and end, its states (the wipes in and out of the keyboard and the panel's
 * question), the tables its states and sub states run from, its draw, and its constructor. */
#include "bbs_write_scene.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "bbs_write_keyboard.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/dual_cell_sprite.h"
#include "main/message_reader.h"
#include "main/oam_buffer.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/screen_map.h"
#include "main/state_flags.h"
#include "main/text_base.h"
#include "main/text_string.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

/* The scene's vtable. */
extern const u8 data_ov112_022a20d0[];

/* The heap the scene loads its files with. */
extern Heap *data_021fbe94;

/* The scene's files. */
extern const char data_ov112_022a2130[]; /* "menu/chat2/b_bbs.bpl" */
extern const char data_ov112_022a2148[]; /* "menu/chat2/b_bbs.bsc" */
extern const char data_ov112_022a2160[]; /* "menu/chat2/b_cht.bch" */
extern const char data_ov112_022a2178[]; /* "menu/chat2/b_bbs.bch" */
extern const char data_ov112_022a2190[]; /* "menu/chat2/b_bbs2.bch" */
extern const char data_ov112_022a21a8[]; /* "menu/chat2/b_key0.bsc" */

/* The OBJs drawn above the keyboard, and over it with the keys in use. */
extern const OamEntry data_ov112_022a2098[];
extern const OamEntry data_ov112_022a2080[];

/* The labels' constructor and destructor, handed to __cxa_vec_ctor (the game's symbols). */
extern void *func_02070c08(void *label);
extern int **func_02070be8(void *label);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The characters before a 0, at most `max` (main's). */
extern int func_02051c8c_unk(u16 *text, int max);

/* The tables of member functions the states and sub states run from (the overlay's .bss, filled
 * once from the constants after them) and their guards. The sub states' table runs on into the
 * .bss symbol data_ov112_022a22b8 (its entries 16-22). */
extern u32 data_ov112_022a21c0; /* the states' guard */
extern u32 data_ov112_022a21c4; /* the sub states' guard */
extern MemberPointer data_ov112_022a21c8[BBS_WRITE_STATES];
extern MemberPointer data_ov112_022a2238[BBS_WRITE_SUB_STATES];
extern const MemberPointer data_ov112_022a1f60, data_ov112_022a1f68, data_ov112_022a1f70, data_ov112_022a1f80,
    data_ov112_022a1f88, data_ov112_022a1f90, data_ov112_022a1f98, data_ov112_022a1fa0, data_ov112_022a1fa8,
    data_ov112_022a1fb0, data_ov112_022a1fb8, data_ov112_022a1fc0, data_ov112_022a1fc8, data_ov112_022a1fd0,
    data_ov112_022a1fd8, data_ov112_022a1fe0, data_ov112_022a1fe8, data_ov112_022a1ff0, data_ov112_022a1ff8,
    data_ov112_022a2000, data_ov112_022a2008, data_ov112_022a2010, data_ov112_022a2018, data_ov112_022a2020,
    data_ov112_022a2028, data_ov112_022a2030, data_ov112_022a2038, data_ov112_022a2040, data_ov112_022a2048,
    data_ov112_022a2050, data_ov112_022a2058, data_ov112_022a2060, data_ov112_022a2068, data_ov112_022a2070,
    data_ov112_022a2078, data_ov112_022a2088, data_ov112_022a2090;

/* The text's layer (LAYER_SUB_BG1), the keyboard's (LAYER_SUB_BG3), and the margin of the wipes
 * on window 2. */
#define BBS_WRITE_TEXT_LAYER LAYER_SUB_BG1
#define BBS_WRITE_WIPE_MARGIN 0x30
#define BBS_WRITE_WIPE_TEXT 2     /* the wipes' layers: the text's */
#define BBS_WRITE_WIPE_KEYBOARD 8 /* the keyboard's */

/* The panel's messages for the two questions, and the mode the scene tells its parent it ends
 * with (MENU_DISPATCH_MODE_CLOSE). */
#define BBS_WRITE_MESSAGE_QUIT 0x87
#define BBS_WRITE_MESSAGE_POST 0x22
#define BBS_WRITE_PARENT_CLOSE 0x44

/* The signature: menu message 0x89 with the player's name, padded with wide spaces. */
#define BBS_WRITE_SIGNATURE_MESSAGE 0x89
#define BBS_WRITE_WIDE_SPACE 0x3000

static MenuScene *bbs_write_scene(BbsWriteScene *self)
{
    return &self->base;
}

static MenuDispatch *bbs_write_parent(BbsWriteScene *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

static DualCellSprite *bbs_write_button_cells(BbsWriteScene *self)
{
    /* The knob's base is main's second sprite class (push_button.h). */
    return (DualCellSprite *) (void *) &self->scroll_button;
}

/* An object's virtual function at `slot` of its vtable, called with nothing more. */
static void bbs_write_call_slot(void *object, int slot)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[slot])(object);
}

/* --- Graphics, setup and the frame --- */

/* func_ov112_022a1104: the scene's graphics loaded on the text's layer: the board's palettes
 * 8-14, its screen (palette 10 set on its map from (6, 5) to (25, 6)), the chat, board and
 * second board characters; the keyboard's screen, keys and characters on its layer. */
void BbsWrite_LoadScreens(BbsWriteScene *self)
{
    Heap *heap = data_021fbe94;

    DisplayLayer_LoadPalettesFromFile(data_ov112_022a2130, heap, BBS_WRITE_TEXT_LAYER, 8, 8, 14);
    RomFile_Read(data_ov112_022a2148, self->screen, sizeof(self->screen));
    ScreenMap_SetPalette(self->screen, 6, 5, 25, 6, 10);
    DisplayLayer_LoadScreen(self->screen, BBS_WRITE_TEXT_LAYER, sizeof(self->screen), 0);
    DisplayLayer_LoadCharsFromFile(data_ov112_022a2160, heap, BBS_WRITE_TEXT_LAYER, 317, 317, 489);
    DisplayLayer_LoadCharsFromFile(data_ov112_022a2178, heap, BBS_WRITE_TEXT_LAYER, 16, 16, 319);
    DisplayLayer_LoadCharsFromFile(data_ov112_022a2190, heap, BBS_WRITE_TEXT_LAYER, 257, 257, 272);
    func_ov095_0229c000(self->keyboard, data_ov112_022a21a8);
    BbsWrite_UpdateKeys(self);
    func_ov095_0229bfd8(self->keyboard, BBS_WRITE_KEYBOARD_LAYER);
    func_ov095_0229c01c(self->keyboard, BBS_WRITE_KEYBOARD_LAYER);
    func_ov095_0229b324(self->keyboard);
}
CLEAN_AS(func_ov112_022a1104, BbsWrite_LoadScreens)

/* func_ov112_022a11f4: the sub screen in BG mode 0, the text's background (priority 3) and the
 * keyboard's (priority 1) set up. */
void BbsWrite_SetLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(BBS_WRITE_TEXT_LAYER, 3);
    DisplayLayer_SetBgControl(BBS_WRITE_TEXT_LAYER, 0, 0, 0);
    DisplayLayer_SetPriority(BBS_WRITE_KEYBOARD_LAYER, 1);
    DisplayLayer_SetBgControl(BBS_WRITE_KEYBOARD_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov112_022a11f4, BbsWrite_SetLayers)

/* func_ov112_022a122c: run at the end of each frame of the scene in use: the keyboard drawn;
 * line labels set again are shown, and the lines' characters queued for the layer when they
 * changed. */
void BbsWrite_EndFrame(BbsWriteScene *self)
{
    func_ov095_0229bf7c(self->keyboard, BBS_WRITE_KEYBOARD_LAYER);
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_LINES_DIRTY) != 0) {
        BbsWrite_ShowLines(self);
        BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_LINES_DIRTY);
        BbsWrite_SetFlags(self, BBS_WRITE_FLAG_CHARS_DIRTY);
    }
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_08) != 0) {
        BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_08);
        BbsWrite_SetFlags(self, BBS_WRITE_FLAG_CHARS_DIRTY);
    }
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_CHARS_DIRTY) != 0) {
        BbsWrite_Idle(self);
        BbsWrite_QueueLineChars(self);
        BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_CHARS_DIRTY);
    }
}
CLEAN_AS(func_ov112_022a122c, BbsWrite_EndFrame)

/* func_ov112_022a12a4: run at the start of each frame of the scene in use: the line labels'
 * boxes closed, the knob and the pointer updated (their vtables' slot 3), the panel's texts
 * closed. */
void BbsWrite_UpdateSprites(BbsWriteScene *self)
{
    BbsWrite_CloseLineBoxes(self);
    bbs_write_call_slot(&self->scroll_button, 3);
    bbs_write_call_slot(&self->pointer, 3);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov112_022a12a4, BbsWrite_UpdateSprites)

/* func_ov112_022a12dc: what the line labels, the keyboard, the characters' task and the panel
 * hold let go. */
void BbsWrite_Release(BbsWriteScene *self)
{
    BbsWrite_CloseLineBoxes(self);
    func_ov095_0229c05c(self->keyboard);
    LayerTask_End(&self->chars_task);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov112_022a12dc, BbsWrite_Release)

/* func_ov112_022a1310: the scene set up: no flags, the keyboard in mode 2, the text emptied and
 * given its signature line (menu message 0x89 with the current player's name, at most 16
 * characters, padded with wide spaces to 16) that the cursor stays after; the knob up, the
 * lines' characters filled with 0xdd, the scroll at the top. */
void BbsWrite_Setup(BbsWriteScene *self)
{
    TextLabel message;
    PlayerIdText name;
    WideText wide;

    self->flags = 0;
    func_ov095_0229c084(self->keyboard, 2);
    TextString_ClearChars(self->text, BBS_POST_LENGTH);

    TextLabel_Construct(&message);
    u8 *record = PlayerRecords_Current();
    PlayerIdText_Construct(&name);
    PlayerId_NameToText(PlayerRecord_Player(record), (TextBase *) (void *) &name);
    MessageReader_SetPart(0, (int) (uintptr_t) &name);
    TextLabel_LoadMenuMessage((int) (uintptr_t) &message, BBS_WRITE_SIGNATURE_MESSAGE);
    WideText_Construct(&wide);
    TextBase_BytesToWide((WideTextBase *) (void *) &wide, (TextBase *) (void *) &message);

    int length = func_02051c8c_unk(wide.text, BBS_WRITE_LINE_CHARS);
    TextString_CopyChars(wide.text, self->text, length);
    for (; length < BBS_WRITE_LINE_CHARS; length++) {
        self->text[length] = BBS_WRITE_WIDE_SPACE;
    }
    self->first_position = BBS_WRITE_FIRST_POSITION;

    PushButton_ShowUp(&self->scroll_button);
    MI_CpuFill8(self->line_chars, 0xdd, sizeof(self->line_chars));
    self->scroll = 0;
    self->scroll_target = 0;
    self->knob = 0;

    WideText_Destruct(&wide);
    PlayerIdText_Destruct(&name);
    TextLabel_Destruct(&message);
}
CLEAN_AS(func_ov112_022a1310, BbsWrite_Setup)

/* --- The states --- */

/* func_ov112_022a13f4 (BBS_WRITE_STATE_CLOSE_WIPE_OUT): the text and the keyboard wipe out
 * (scrolled up 8 pixels); when done, both layers hidden and the scene ends (phase 5). */
void BbsWrite_CloseWipeOut(BbsWriteScene *self)
{
    if (MenuScene_StepWipe(bbs_write_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(BBS_WRITE_TEXT_LAYER);
        DisplayLayer_HideAndResetScroll(BBS_WRITE_KEYBOARD_LAYER);
        MenuScene_SetPhase(bbs_write_scene(self), BBS_WRITE_PHASE_END);
    } else {
        MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_TEXT_LAYER, 0, -8);
        MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_KEYBOARD_LAYER, 0, -8);
    }
    self->unk_a4 = MenuScene_WipeOffsetY(bbs_write_scene(self));
    self->panel_y = self->unk_a4;
    self->keyboard_y = self->unk_a4;
}
CLEAN_AS(func_ov112_022a13f4, BbsWrite_CloseWipeOut)

/* func_ov112_022a145c (BBS_WRITE_STATE_CLOSE): once the scroll has stopped, the cursor hidden,
 * the screen no longer dimmed, the parent told the scene closes, and the text and the keyboard
 * start to wipe out on window 2 (state 13). */
void BbsWrite_StartCloseWipeOut(BbsWriteScene *self)
{
    if (BbsWrite_IsScrolling(self) != 0) {
        return;
    }
    BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_CURSOR_SHOWN);
    BbsWrite_EndDim(self);
    MenuDispatch_SetMode(bbs_write_parent(self), BBS_WRITE_PARENT_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(bbs_write_scene(self), BBS_WRITE_WIPE_TEXT | BBS_WRITE_WIPE_KEYBOARD, 0, 0,
                                 BBS_WRITE_WIPE_MARGIN);
    MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_TEXT_LAYER, 0, -8);
    MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_KEYBOARD_LAYER, 0, -8);
    MenuScene_SetState(bbs_write_scene(self), BBS_WRITE_STATE_CLOSE_WIPE_OUT);
    self->unk_a4 = MenuScene_WipeOffsetY(bbs_write_scene(self));
    self->panel_y = self->unk_a4;
}
CLEAN_AS(func_ov112_022a145c, BbsWrite_StartCloseWipeOut)

/* func_ov112_022a14d8 (BBS_WRITE_STATE_FINISH_WIPE_OUT): the text wipes out; when done, its layer
 * hidden and the scene ends (phase 5). */
void BbsWrite_FinishWipeOut(BbsWriteScene *self)
{
    if (MenuScene_StepWipe(bbs_write_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(BBS_WRITE_TEXT_LAYER);
        MenuScene_SetPhase(bbs_write_scene(self), BBS_WRITE_PHASE_END);
    } else {
        MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_TEXT_LAYER, 0, -8);
    }
    self->unk_a4 = MenuScene_WipeOffsetY(bbs_write_scene(self));
    self->panel_y = self->unk_a4;
}
CLEAN_AS(func_ov112_022a14d8, BbsWrite_FinishWipeOut)

/* func_ov112_022a1520 (BBS_WRITE_STATE_ANSWER_YES): once quitting, or once the post has reached
 * the session's other players: the cursor hidden, the screen no longer dimmed, the parent told
 * the scene closes, and the text starts to wipe out on window 2 (state 11). */
void BbsWrite_FinishAfterAnswer(BbsWriteScene *self)
{
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_QUITTING) == 0 && BbsWrite_PostDelivered(self) == 0) {
        return;
    }
    BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_CURSOR_SHOWN);
    BbsWrite_EndDim(self);
    MenuDispatch_SetMode(bbs_write_parent(self), BBS_WRITE_PARENT_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(bbs_write_scene(self), BBS_WRITE_WIPE_TEXT, 0, 0, BBS_WRITE_WIPE_MARGIN);
    MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_TEXT_LAYER, 0, -8);
    MenuScene_SetState(bbs_write_scene(self), BBS_WRITE_STATE_FINISH_WIPE_OUT);
    self->unk_a4 = MenuScene_WipeOffsetY(bbs_write_scene(self));
    self->panel_y = self->unk_a4;
}
CLEAN_AS(func_ov112_022a1520, BbsWrite_FinishAfterAnswer)

/* func_ov112_022a15a0 (BBS_WRITE_STATE_KEYBOARD_WIPE_IN): the keyboard wipes in; when done, the
 * cursor at the text's start and the input begins again (phase 2), the lines drawn. */
void BbsWrite_KeyboardWipeIn(BbsWriteScene *self)
{
    if (MenuScene_StepWipeBack(bbs_write_scene(self), 0) != 0) {
        BbsWrite_StartEditing(self);
        MenuScene_SetPhase(bbs_write_scene(self), BBS_WRITE_PHASE_INTERACTIVE);
        BbsWrite_BeginInput(self);
        BbsWrite_Refresh(self);
        BbsWrite_EndFrame(self);
        BbsWrite_SetFlags(self, BBS_WRITE_FLAG_80);
    }
    MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_KEYBOARD_LAYER, 0, 0);
    self->keyboard_y = MenuScene_WipeOffsetY(bbs_write_scene(self));
    self->panel_y = self->keyboard_y;
}
CLEAN_AS(func_ov112_022a15a0, BbsWrite_KeyboardWipeIn)

/* func_ov112_022a1600 (BBS_WRITE_STATE_BACK): the keyboard shown and wiping in on window 2
 * (state 9), drawn; the panel's two buttons. */
void BbsWrite_StartKeyboardWipeIn(BbsWriteScene *self)
{
    MenuScene_StartWipeCoveredOnWindow2(bbs_write_scene(self), BBS_WRITE_WIPE_KEYBOARD, 0, 0, BBS_WRITE_WIPE_MARGIN);
    DisplayLayer_Show(BBS_WRITE_KEYBOARD_LAYER);
    MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_KEYBOARD_LAYER, 0, 0);
    MenuScene_SetState(bbs_write_scene(self), BBS_WRITE_STATE_KEYBOARD_WIPE_IN);
    self->keyboard_y = MenuScene_WipeOffsetY(bbs_write_scene(self));
    self->panel_y = self->keyboard_y;
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_DRAWN);
    ButtonPanel_SetLayout2(&self->panel);
}
CLEAN_AS(func_ov112_022a1600, BbsWrite_StartKeyboardWipeIn)

/* func_ov112_022a1664 (BBS_WRITE_STATE_QUESTION_WIPE_OUT): the panel's question wipes out; when
 * done, state 8. */
void BbsWrite_QuestionWipeOut(BbsWriteScene *self)
{
    if (MenuScene_StepWipe(bbs_write_scene(self), 0) != 0) {
        MenuScene_SetState(bbs_write_scene(self), BBS_WRITE_STATE_BACK);
    }
    self->panel_y = MenuScene_WipeOffsetY(bbs_write_scene(self));
}
CLEAN_AS(func_ov112_022a1664, BbsWrite_QuestionWipeOut)

/* func_ov112_022a168c (BBS_WRITE_STATE_ANSWER_NO): the screen no longer dimmed, the question
 * starts to wipe out on window 2 (state 7). */
void BbsWrite_AnswerNoWipeOut(BbsWriteScene *self)
{
    BbsWrite_EndDim(self);
    MenuScene_StartWipeOnWindow2(bbs_write_scene(self), 0, 0, 0, BBS_WRITE_WIPE_MARGIN);
    MenuScene_SetState(bbs_write_scene(self), BBS_WRITE_STATE_QUESTION_WIPE_OUT);
    self->panel_y = MenuScene_WipeOffsetY(bbs_write_scene(self));
}
CLEAN_AS(func_ov112_022a168c, BbsWrite_AnswerNoWipeOut)

/* func_ov112_022a16c0 (BBS_WRITE_STATE_QUESTION_WIPE_IN): the panel's question wipes in; when
 * done, its answer by the pen or by the buttons, as main's state flag 2 says (phase 2). */
void BbsWrite_QuestionWipeIn(BbsWriteScene *self)
{
    if (MenuScene_StepWipeBack(bbs_write_scene(self), -1) != 0) {
        MenuScene_SetPhase(bbs_write_scene(self), BBS_WRITE_PHASE_INTERACTIVE);
        if (StateFlags_IsClear2()) {
            BbsWrite_BeginPanelTouch(self);
        } else {
            BbsWrite_BeginPanelKeys(self);
        }
    }
    self->panel_y = MenuScene_WipeOffsetY(bbs_write_scene(self));
}
CLEAN_AS(func_ov112_022a16c0, BbsWrite_QuestionWipeIn)

/* func_ov112_022a1700 (BBS_WRITE_STATE_QUESTION): the screen dimmed, the panel's question (message
 * 0x87 to quit, 0x22 to post) wiping in over 5 frames (state 5). */
void BbsWrite_ShowQuestion(BbsWriteScene *self)
{
    BbsWrite_BeginDim(self);
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_QUITTING) != 0) {
        ButtonPanel_SetLayout8(&self->panel, BBS_WRITE_MESSAGE_QUIT);
    } else {
        ButtonPanel_SetLayout8(&self->panel, BBS_WRITE_MESSAGE_POST);
    }
    MenuScene_StartWipeCovered(bbs_write_scene(self), 5, 0);
    self->panel_y = MenuScene_WipeOffsetY(bbs_write_scene(self));
    MenuScene_SetState(bbs_write_scene(self), BBS_WRITE_STATE_QUESTION_WIPE_IN);
}
CLEAN_AS(func_ov112_022a1700, BbsWrite_ShowQuestion)

/* func_ov112_022a1758 (BBS_WRITE_STATE_KEYBOARD_WIPE_OUT): the keyboard wipes out; when done, its
 * layer hidden, no longer drawn, and the question (state 4). */
void BbsWrite_KeyboardWipeOut(BbsWriteScene *self)
{
    if (MenuScene_StepWipe(bbs_write_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(BBS_WRITE_KEYBOARD_LAYER);
        BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_DRAWN);
        MenuScene_SetState(bbs_write_scene(self), BBS_WRITE_STATE_QUESTION);
    } else {
        MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_KEYBOARD_LAYER, 0, 0);
    }
    self->keyboard_y = MenuScene_WipeOffsetY(bbs_write_scene(self));
    self->panel_y = self->keyboard_y;
}
CLEAN_AS(func_ov112_022a1758, BbsWrite_KeyboardWipeOut)

/* func_ov112_022a17a8 (BBS_WRITE_STATE_ASK): the cursor hidden, the keyboard starts to wipe out
 * on window 2 (state 3), the scroll back to the top. */
void BbsWrite_StartKeyboardWipeOut(BbsWriteScene *self)
{
    BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_CURSOR_SHOWN);
    MenuScene_StartWipeOnWindow2(bbs_write_scene(self), BBS_WRITE_WIPE_KEYBOARD, 0, 0, BBS_WRITE_WIPE_MARGIN);
    MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_KEYBOARD_LAYER, 0, 0);
    MenuScene_SetState(bbs_write_scene(self), BBS_WRITE_STATE_KEYBOARD_WIPE_OUT);
    self->keyboard_y = MenuScene_WipeOffsetY(bbs_write_scene(self));
    self->panel_y = self->keyboard_y;
    BbsWrite_ScrollTo(self, 0);
    BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_80);
}
CLEAN_AS(func_ov112_022a17a8, BbsWrite_StartKeyboardWipeOut)

/* func_ov112_022a1808 (BBS_WRITE_STATE_WIPE_IN): on its first frame today's date drawn; the text
 * and the keyboard wipe in (the text scrolled up 8 pixels); when done, the cursor at the text's
 * start and the input begins (phase 2), the lines drawn. */
void BbsWrite_WipeIn(BbsWriteScene *self)
{
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_DATE_PENDING) != 0) {
        BbsWrite_ShowDate(self);
        BbsWrite_ClearDateLabel(self);
        BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_DATE_PENDING);
    }
    if (MenuScene_StepWipeBack(bbs_write_scene(self), 0) != 0) {
        BbsWrite_StartEditing(self);
        MenuScene_SetPhase(bbs_write_scene(self), BBS_WRITE_PHASE_INTERACTIVE);
        BbsWrite_BeginInput(self);
        BbsWrite_Refresh(self);
        BbsWrite_EndFrame(self);
    }
    MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_TEXT_LAYER, 0, -8);
    MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_KEYBOARD_LAYER, 0, 0);
    self->keyboard_y = MenuScene_WipeOffsetY(bbs_write_scene(self));
    self->unk_a4 = self->keyboard_y;
    self->panel_y = self->unk_a4;
}
CLEAN_AS(func_ov112_022a1808, BbsWrite_WipeIn)

/* func_ov112_022a189c (BBS_WRITE_STATE_START): the backgrounds set up and the graphics loaded,
 * the lines' characters queued, the date to be drawn; the keyboard set up and drawn on its layer;
 * the text and the keyboard shown and wiping in on window 2 over 7 frames (state 1); drawn, the
 * panel's two buttons, the lines drawn. */
void BbsWrite_StartWipeIn(BbsWriteScene *self)
{
    BbsWrite_SetLayers();
    BbsWrite_LoadScreens(self);
    BbsWrite_QueueLineChars(self);
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_DATE_PENDING);
    func_ov095_0229c420(self->keyboard, BBS_WRITE_KEYBOARD_LAYER);
    func_ov095_0229bf7c(self->keyboard, BBS_WRITE_KEYBOARD_LAYER);
    MenuScene_StartWipeCoveredOnWindow2(bbs_write_scene(self), BBS_WRITE_WIPE_TEXT | BBS_WRITE_WIPE_KEYBOARD, 7, 0,
                                        BBS_WRITE_WIPE_MARGIN);
    DisplayLayer_Show(BBS_WRITE_TEXT_LAYER);
    DisplayLayer_Show(BBS_WRITE_KEYBOARD_LAYER);
    MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_TEXT_LAYER, 0, -8);
    MenuScene_ScrollWipe(bbs_write_scene(self), BBS_WRITE_KEYBOARD_LAYER, 0, 0);
    MenuScene_SetState(bbs_write_scene(self), BBS_WRITE_STATE_WIPE_IN);
    self->keyboard_y = MenuScene_WipeOffsetY(bbs_write_scene(self));
    self->unk_a4 = self->keyboard_y;
    self->panel_y = self->unk_a4;
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_DRAWN | BBS_WRITE_FLAG_80);
    ButtonPanel_SetLayout2(&self->panel);
    BbsWrite_Refresh(self);
    BbsWrite_EndFrame(self);
}
CLEAN_AS(func_ov112_022a189c, BbsWrite_StartWipeIn)

/* --- The vtable's phases --- */

/* func_ov112_022a1960 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int BbsWrite_End(BbsWriteScene *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov112_022a1960, BbsWrite_End)

/* func_ov112_022a1970 (vtable slot 0x58, phase 4): nothing. */
int BbsWrite_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov112_022a1970, BbsWrite_Phase4Idle)

/* func_ov112_022a1974 (vtable slot 0x54, phase 3): nothing. */
int BbsWrite_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov112_022a1974, BbsWrite_Phase3Idle)

/* func_ov112_022a1978 (vtable slot 0x50, phase 2): the menu close's delay counted; when main
 * asked the menu to close in a sub state that may be left (0-6, 9, 0x0b-0x0f, 0x11 and 0x13),
 * the scene closes (BbsWrite_CloseOnRequest). Else a frame of the scene in use: its start, its
 * sub state, its end. Answers 1. */
int BbsWrite_RunInteractive(BbsWriteScene *self)
{
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked()) {
        switch (self->base.sub_state) {
            case BBS_WRITE_SUB_TOUCH:
            case BBS_WRITE_SUB_KNOB_DRAG:
            case BBS_WRITE_SUB_BAR_TOUCH:
            case BBS_WRITE_SUB_MARK_DRAG:
            case BBS_WRITE_SUB_KEY_TOUCH_HELD:
            case BBS_WRITE_SUB_PANEL_TOUCH:
            case BBS_WRITE_SUB_KEYS:
            case BBS_WRITE_SUB_KEY_REPEAT:
            case BBS_WRITE_SUB_BACKSPACE_REPEAT:
            case BBS_WRITE_SUB_TEXT_KEYS:
            case BBS_WRITE_SUB_MARK_KEYS:
            case BBS_WRITE_SUB_WHILE_L:
            case BBS_WRITE_SUB_WHILE_R:
            case BBS_WRITE_SUB_SCROLL_HELD:
            case BBS_WRITE_SUB_PANEL_KEYS:
                BbsWrite_CloseOnRequest(self);
                return 1;
            default:
                break;
        }
    }
    BbsWrite_UpdateSprites(self);
    BbsWrite_RunSubState(self);
    BbsWrite_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov112_022a1978, BbsWrite_RunInteractive)

/* func_ov112_022a19ec: the sub state's function (BbsWriteSubState) through the table of member
 * functions, filled once from its constants.
 * REQUIRES: the sub state is below 23; the game reads past the table for others. */
void BbsWrite_RunSubState(BbsWriteScene *self)
{
    static const MemberPointer *const sub_states[BBS_WRITE_SUB_STATES] = {
        &data_ov112_022a2010, &data_ov112_022a2008, &data_ov112_022a2000, &data_ov112_022a1ff8, &data_ov112_022a1f60,
        &data_ov112_022a1fe8, &data_ov112_022a1f90, &data_ov112_022a1fd8, &data_ov112_022a1fd0, &data_ov112_022a1f88,
        &data_ov112_022a1fc8, &data_ov112_022a1fb8, &data_ov112_022a2020, &data_ov112_022a1fa8, &data_ov112_022a1fa0,
        &data_ov112_022a1ff0, &data_ov112_022a1f68, &data_ov112_022a1f80, &data_ov112_022a2018, &data_ov112_022a1fb0,
        &data_ov112_022a1f70, &data_ov112_022a1f98, &data_ov112_022a2040,
    };
    MemberTable_InitOnce(&data_ov112_022a21c4, data_ov112_022a2238, sub_states, BBS_WRITE_SUB_STATES);
    MemberPointer_CallVoid(&data_ov112_022a2238[self->base.sub_state], self);
}
CLEAN_AS(func_ov112_022a19ec, BbsWrite_RunSubState)

/* func_ov112_022a1b80 (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (BbsWriteState) through the table of member functions, filled once from its constants.
 * Answers 1.
 * REQUIRES: the state is below 14; the game reads past the table for others. */
int BbsWrite_RunState(BbsWriteScene *self)
{
    static const MemberPointer *const states[BBS_WRITE_STATES] = {
        &data_ov112_022a2090, &data_ov112_022a2088, &data_ov112_022a1fe0, &data_ov112_022a2078, &data_ov112_022a2070,
        &data_ov112_022a2068, &data_ov112_022a2060, &data_ov112_022a2058, &data_ov112_022a2050, &data_ov112_022a2048,
        &data_ov112_022a1fc0, &data_ov112_022a2038, &data_ov112_022a2030, &data_ov112_022a2028,
    };
    MemberTable_InitOnce(&data_ov112_022a21c0, data_ov112_022a21c8, states, BBS_WRITE_STATES);
    MemberPointer_CallVoid(&data_ov112_022a21c8[self->base.state], self);
    return 1;
}
CLEAN_AS(func_ov112_022a1b80, BbsWrite_RunState)

/* func_ov112_022a1c94 (vtable slot 0x24): the scene's draw.
 *
 * - While the text scrolls, a step of the scroll and the text's layer scrolled by it (and 8).
 * - While drawn, at 0x60 below the keyboard's y: a cell above the keyboard, its mode tabs and
 *   its frame, and, with the keys in use, a cell over it; the knob placed by the keyboard's y and
 *   `knob` (its face kept by the keyboard) and drawn through its class (slot 2).
 * - With the keys in use, the pointer (following the knob's face with
 *   BBS_WRITE_FLAG_POINTER_ON_BUTTON) drawn.
 * - While drawn with the text cursor shown, the blink counted and the cursor drawn at its place
 *   in the text, less the scroll and 8, while bit 4 of the count is set.
 * - The panel at `panel_y`.
 *
 * Answers 1. */
int BbsWrite_Draw(BbsWriteScene *self)
{
    if (BbsWrite_IsScrolling(self) != 0) {
        BbsWrite_StepScroll(self);
        DisplayLayer_SetScroll(BBS_WRITE_TEXT_LAYER, 0, self->scroll + 8);
    }

    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_DRAWN) != 0) {
        int y = (int) ((u32) self->keyboard_y + 0x60);
        OamBuffer_DrawCell(1, data_ov112_022a2098, 0x80, (int) ((u32) y - 8), -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        func_ov095_0229b1c8(self->keyboard, 0x80, y, 1);
        func_ov095_0229ae84(self->keyboard, (void *) (uintptr_t) 0x80, (void *) (uintptr_t) (u32) y);
        if (StateFlags_Test2()) {
            OamBuffer_DrawObjAffine(1, data_ov112_022a2080, 0x80, y, -1, 1, NULL);
        }
        int knob_y = (int) ((u32) self->knob + ((u32) self->keyboard_y - 0x50));
        DualCellSprite_SetOffset(bbs_write_button_cells(self), 0x5d, knob_y);
        int face_x = PushButton_FaceX(&self->scroll_button);
        int face_y = PushButton_FaceY(&self->scroll_button);
        func_ov095_02299b30((int *) (void *) self->keyboard, face_x, face_y);
        bbs_write_call_slot(&self->scroll_button, 2);
    }

    if (StateFlags_Test2()) {
        if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_POINTER_ON_BUTTON) != 0) {
            int face_x = PushButton_FaceX(&self->scroll_button);
            int face_y = PushButton_FaceY(&self->scroll_button);
            Glider_PlaceAt(&self->pointer, face_x, face_y);
        }
        Glider_DrawWrapped(&self->pointer);
    }

    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_DRAWN) != 0 && BbsWrite_TestFlags(self, BBS_WRITE_FLAG_CURSOR_SHOWN) != 0) {
        int x = self->cursor_x;
        int y = (int) ((u32) self->cursor_y - (u32) (self->scroll + 8));
        self->blink = (u8) (self->blink + 1);
        if (self->blink & 0x10) {
            func_ov095_0229af58((int) (uintptr_t) self->keyboard, x, y, 2);
        }
    }

    ButtonPanel_Draw(&self->panel, self->panel_y);
    return 1;
}
CLEAN_AS(func_ov112_022a1c94, BbsWrite_Draw)

/* func_ov112_022a1e2c (vtable slot 0x0c): the scene closes: the parent told, then what the
 * scene's members hold let go. Answers 1. */
int BbsWrite_Close(BbsWriteScene *self)
{
    MenuDispatch_ChildClosed(bbs_write_parent(self));
    BbsWrite_Release(self);
    return 1;
}
CLEAN_AS(func_ov112_022a1e2c, BbsWrite_Close)

/* func_ov112_022a1e48 (vtable slot 0x00): the scene starts: its setup, state 0 (set as is) and
 * the base's wait (phase 0). Answers 1. */
int BbsWrite_Start(BbsWriteScene *self)
{
    BbsWrite_Setup(self);
    self->base.state = BBS_WRITE_STATE_START;
    MenuScene_SetPhase(bbs_write_scene(self), BBS_WRITE_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov112_022a1e48, BbsWrite_Start)

/* func_ov112_022a1e68: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed in order, the labels by __cxa_vec_ctor.
 * The keyboard at 0x384 has no constructor. */
BbsWriteScene *BbsWrite_New(void)
{
    BbsWriteScene *self = MenuScene_Alloc(sizeof(BbsWriteScene));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov112_022a20d0;
    ErrorMessage_Construct(&self->error);
    LayerTask_Construct(&self->chars_task);
    for (int i = 0; i < 2; i++) {
        LayerTask_Construct((LayerTask *) (void *) self->unk_268c[i]);
    }
    __cxa_vec_ctor(self->unk_26d4, 2, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    __cxa_vec_ctor(self->lines, BBS_WRITE_LINES, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    PushButton_Construct(&self->scroll_button);
    ButtonPanel_Construct(&self->panel);
    Glider0_Construct(&self->pointer);
    BbsLabel_Construct((BbsLabel *) (void *) self->filter_text);
    BbsWideText_Construct(&self->filter_wide);
    return self;
}
CLEAN_AS(func_ov112_022a1e68, BbsWrite_New)
