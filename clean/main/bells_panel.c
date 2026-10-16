/* The bells panel, the fourth screen panel (bells_panel.h). */
#include "bells_panel.h"

#include "autoload_2/approach.h" /* Approach_S32, Approach_EaseS32MinMax */
#include "autoload_2/heap.h"     /* Heap_OperatorDeleteB */
#include "cell_anim.h"
#include "clean.h"
#include "number_text.h" /* NumberText_Format */
#include "oam_buffer.h"  /* OamBuffer_DrawCell */
#include "ov004/member_pointer.h"
#include "player_pockets.h" /* PlayerPockets_Bells */
#include "player_record.h"  /* PlayerRecord_Pockets */
#include "player_records.h" /* PlayerRecords_Current */
#include "quick_message.h"  /* QuickMessage_OtherBalloonBusy */
#include "sound.h"          /* SoundSys_StopSound2d, SoundSys_StartSound2d, SoundSys_PlaySe */
#include "state_flags.h"    /* StateFlags_Test4, StateFlags_ValueOrOne */
#include "text_draw.h"      /* TextDraw_AlignRight, TextDraw_RequestDraw */
#include "text_label.h"     /* TextVtable */

static_assert(offsetof(BellsPanel, anim) == 0x0c && offsetof(BellsPanel, state) == 0x20, "BellsPanel");
static_assert(offsetof(BellsPanel, shift) == 0x28 && offsetof(BellsPanel, box) == 0x38, "BellsPanel");
static_assert(offsetof(BellsPanel, text) == 0x3c && offsetof(BellsPanel, bells) == 0x7c, "BellsPanel");
static_assert(offsetof(BellsPanel, shown) == 0x80 && offsetof(BellsPanel, frozen) == 0x82, "BellsPanel");
static_assert(sizeof(BellsPanel) == 0x84, "BellsPanel");

extern const u32 data_020e21fc[]; /* the class's vtable */
/* The animations: opening, closing. */
extern const CellAnimData data_020d5c54, data_020d5c5c;
/* The font the number is drawn with (fontD). */
extern TextFont data_021c81d4;

/* The member function table of BellsPanel_Update (a function-local static of the game): its
 * guard, the table, and the constants it is filled from. */
extern u32 data_021d3160;
extern MemberPointer data_021d31b0[4];
extern const MemberPointer data_020e20f4, data_020e20e4, data_020e2154, data_020e2114;

extern fx32 FX_MulFunc(fx32 a, fx32 b);
/* The bells held on the pockets screen's cursor (data_021cfc74). */
extern int func_0206f854(void);
/* A text box from VRAM tile `first_tile`, `cells` tiles wide and `rows` high, in the boxes'
 * heap (NULL when it is full); a box destroyed and freed. */
extern TextDrawBox *func_020a9034(int first_tile, int cells, int rows);
extern void func_020a8fb8(TextDrawBox *box);

/* The ease of `shift`: 40 pixels lower while another balloon is out, eased by 0x600 of the
 * distance a frame, the step from 0x2300 up to `shift_speed`, which grows by 0xa00 a frame
 * from 0x2300 to 0x5000. A new target waits 5 frames, except the first after a reset. */
#define SHIFT_BALLOON 0x28000
#define SHIFT_RATE 0x600
#define SHIFT_SPEED_ADD 0xa00
#define SHIFT_SPEED_MIN 0x2300
#define SHIFT_SPEED_MAX 0x5000
#define SHIFT_WAIT 5
/* The lift at state flag 4's value 0 (192 pixels, 20.12). */
#define LIFT_AT_ZERO 0x000c0000
#define FX_ONE 0x1000

/* The number: 7 digits, not padded, no unit, half-width characters. */
#define BELLS_DIGITS 7
#define BELLS_FORMAT 0
#define BELLS_UNIT 0
#define BELLS_HALF_WIDTH 1

/* The text box: from VRAM tile 0x80, 8 tiles by 1, on OBJs of the main screen. */
#define BOX_FIRST_TILE 0x80
#define BOX_CELLS 8
#define BOX_ROWS 1
#define BOX_LAYER_OBJECTS 4
#define BOX_BACKGROUND 0
#define BOX_COLOR 0xc

/* The sound when the counting stops. */
#define SE_COUNT_DONE 0x2e

/* vtable slots */
#define SLOT_DRAW 2
#define SLOT_UPDATE 3

typedef void BellsPanelMethod(BellsPanel *panel);

static void call_slot(BellsPanel *panel, int slot)
{
    ((BellsPanelMethod *) (uintptr_t) panel->base.vtable[slot])(panel);
}

/* func_0208b648 */
void BellsPanel_ResetShift(BellsPanel *panel)
{
    panel->shift = 0;
    panel->shift_target = 0;
    panel->shift_wait = -1;
    panel->shift_speed = 0;
}
CLEAN_AS(func_0208b648, BellsPanel_ResetShift)

/* func_0208b658: `shift` eased toward its target while state flag 4 is set; reset when not. */
void BellsPanel_UpdateShift(BellsPanel *panel)
{
    if (StateFlags_Test4() == 0) {
        BellsPanel_ResetShift(panel);
        return;
    }
    int target = QuickMessage_OtherBalloonBusy() != 0 ? SHIFT_BALLOON : 0;
    panel->shift_speed += SHIFT_SPEED_ADD;
    if (panel->shift_speed < SHIFT_SPEED_MIN) {
        panel->shift_speed = SHIFT_SPEED_MIN;
    } else if (panel->shift_speed > SHIFT_SPEED_MAX) {
        panel->shift_speed = SHIFT_SPEED_MAX;
    }
    if (target != panel->shift_target) {
        int waited = 0;
        if (panel->shift_wait >= 0) {
            panel->shift_wait++;
            waited = panel->shift_wait > SHIFT_WAIT;
        } else {
            waited = 1;
        }
        if (waited) {
            panel->shift_target = target;
            panel->shift_wait = 0;
        }
    } else {
        panel->shift_wait = 0;
    }
    Approach_EaseS32MinMax(&panel->shift, panel->shift_target, SHIFT_RATE, panel->shift_speed, SHIFT_SPEED_MIN);
}
CLEAN_AS(func_0208b658, BellsPanel_UpdateShift)

/* func_0208b6ec: `lift` from state flag 4's value v: 0 * v + 192 * (1 - v), in whole pixels.
 * QUIRK: the first product is always 0, and still computed. */
void BellsPanel_UpdateLift(BellsPanel *panel)
{
    fx32 value = StateFlags_ValueOrOne();
    fx32 at_one = FX_MulFunc(0, value);
    fx32 at_zero = FX_MulFunc(LIFT_AT_ZERO, FX_ONE - value);
    panel->lift = (at_one + at_zero) >> 12;
}
CLEAN_AS(func_0208b6ec, BellsPanel_UpdateLift)

/* func_0208b720: the bells of this system's player, money bags included, plus the bells held
 * on the pockets screen's cursor; 0 without a player. The panel is not used. */
int BellsPanel_Bells(BellsPanel *panel)
{
    (void) panel;
    u8 *record = PlayerRecords_Current();
    if (record == NULL) {
        return 0;
    }
    int bells = PlayerPockets_Bells(PlayerRecord_Pockets(record), 1);
    return bells + func_0206f854();
}
CLEAN_AS(func_0208b720, BellsPanel_Bells)

/* func_0208b748: the counting sound started when the counting starts; stopped, with its end
 * sound, when it stops. */
void BellsPanel_SetCounting(BellsPanel *panel, int counting)
{
    if (panel->counting != 0) {
        if (counting == 0) {
            SoundSys_StopSound2d();
            SoundSys_PlaySe(SE_COUNT_DONE);
        }
    } else if (counting != 0) {
        SoundSys_StartSound2d();
    }
    panel->counting = (u8) counting;
}
CLEAN_AS(func_0208b748, BellsPanel_SetCounting)

/* func_0208b77c: the number shown written into the text. */
void BellsPanel_FormatBells(BellsPanel *panel)
{
    NumberText_Format(&panel->text, panel->bells, BELLS_DIGITS, BELLS_FORMAT, BELLS_UNIT, BELLS_HALF_WIDTH);
}
CLEAN_AS(func_0208b77c, BellsPanel_FormatBells)

/* func_0208b79c: unless frozen, the number shown counted toward the bells, by about a sixth of
 * the distance rounded to tens, plus 7, and the text box redrawn. Whether it moved. */
int BellsPanel_Count(BellsPanel *panel)
{
    if (panel->frozen != 0) {
        return 0;
    }
    int bells = BellsPanel_Bells(panel);
    if (panel->bells == bells) {
        return 0;
    }
    /* the distance; the ROM's subtraction and negation wrap */
    int distance = (int) ((u32) bells - (u32) panel->bells);
    if (distance < 0) {
        distance = (int) (0u - (u32) distance);
    }
    int tens = (distance / 6 + 50) / 10;
    Approach_S32(&panel->bells, bells, tens * 10 + 7);
    BellsPanel_FormatBells(panel);
    if (panel->box != NULL) {
        TextDraw_AlignRight(panel->box);
        TextDraw_RequestDraw(panel->box);
    }
    return 1;
}
CLEAN_AS(func_0208b79c, BellsPanel_Count)

/* func_0208b800: the number shown set to the bells at once; the counting and the freeze
 * cleared (the counting sound left as it is). */
void BellsPanel_TakeBells(BellsPanel *panel)
{
    panel->bells = BellsPanel_Bells(panel);
    BellsPanel_FormatBells(panel);
    panel->counting = 0;
    panel->frozen = 0;
}
CLEAN_AS(func_0208b800, BellsPanel_TakeBells)

/* func_0208b824 */
void BellsPanel_FreeTextBox(BellsPanel *panel)
{
    if (panel->box != NULL) {
        func_020a8fb8(panel->box);
        panel->box = NULL;
    }
}
CLEAN_AS(func_0208b824, BellsPanel_FreeTextBox)

/* func_0208b83c: the text box made, unless there is one: the number's characters (through the
 * text's vtable), right-aligned, drawn by the text process. Nothing when the boxes' heap is
 * full. */
void BellsPanel_OpenTextBox(BellsPanel *panel)
{
    if (panel->box != NULL) {
        return;
    }
    panel->box = func_020a9034(BOX_FIRST_TILE, BOX_CELLS, BOX_ROWS);
    TextDrawBox *box = panel->box;
    if (box == NULL) {
        return;
    }
    box->layer = BOX_LAYER_OBJECTS;
    box->screens = TEXT_DRAW_TO_MAIN;
    box->rows_full_width = 1;
    box->background = BOX_BACKGROUND;
    box->color = BOX_COLOR;
    const TextVtable *vtable = (const TextVtable *) panel->text.vtable;
    box->text = (const char *) (uintptr_t) ((int (*)(MessageText46 *))(uintptr_t) vtable->buffer)(&panel->text);
    box->font = &data_021c81d4;
    TextDraw_AlignRight(box);
    TextDraw_RequestDraw(box);
}
CLEAN_AS(func_0208b83c, BellsPanel_OpenTextBox)

/* func_0208b8a8: once the closing animation is done, the text box freed and closed. */
void BellsPanel_StepClosing(BellsPanel *panel)
{
    CellAnim_Advance(&panel->anim);
    if (CellAnim_IsDone(&panel->anim) != 0) {
        BellsPanel_FreeTextBox(panel);
        BellsPanel_EnterClosed(panel);
    }
}
CLEAN_AS(func_0208b8a8, BellsPanel_StepClosing)

/* func_0208b8d0 */
void BellsPanel_EnterClosing(BellsPanel *panel)
{
    panel->state = BELLS_PANEL_CLOSING;
    CellAnim_SetData(&panel->anim, &data_020d5c5c);
    CellAnim_SetHold(&panel->anim, 1);
    CellAnim_Restart(&panel->anim);
}
CLEAN_AS(func_0208b8d0, BellsPanel_EnterClosing)

/* func_0208b900: the number counted; once `shown` is cleared, closing, and the counting sound
 * stopped. */
void BellsPanel_StepOpen(BellsPanel *panel)
{
    int counting = BellsPanel_Count(panel);
    if (panel->shown == 0) {
        BellsPanel_EnterClosing(panel);
        counting = 0;
    }
    BellsPanel_SetCounting(panel, counting);
}
CLEAN_AS(func_0208b900, BellsPanel_StepOpen)

/* func_0208b928 */
void BellsPanel_EnterOpen(BellsPanel *panel)
{
    panel->state = BELLS_PANEL_OPEN;
}
CLEAN_AS(func_0208b928, BellsPanel_EnterOpen)

/* func_0208b930 */
void BellsPanel_StepOpening(BellsPanel *panel)
{
    CellAnim_Advance(&panel->anim);
    if (CellAnim_IsDone(&panel->anim) != 0) {
        BellsPanel_EnterOpen(panel);
    }
}
CLEAN_AS(func_0208b930, BellsPanel_StepOpening)

/* func_0208b954: the opening animation started, the bells taken and the text box made. */
void BellsPanel_EnterOpening(BellsPanel *panel)
{
    panel->state = BELLS_PANEL_OPENING;
    CellAnim_SetData(&panel->anim, &data_020d5c54);
    CellAnim_SetHold(&panel->anim, 1);
    CellAnim_Restart(&panel->anim);
    BellsPanel_TakeBells(panel);
    BellsPanel_OpenTextBox(panel);
}
CLEAN_AS(func_0208b954, BellsPanel_EnterOpening)

/* func_0208b990 */
void BellsPanel_StepClosed(BellsPanel *panel)
{
    if (panel->shown != 0) {
        BellsPanel_EnterOpening(panel);
    }
}
CLEAN_AS(func_0208b990, BellsPanel_StepClosed)

/* func_0208b9a8 */
void BellsPanel_EnterClosed(BellsPanel *panel)
{
    panel->state = BELLS_PANEL_CLOSED;
}
CLEAN_AS(func_0208b9a8, BellsPanel_EnterClosed)

/* func_0208b9b0 */
void BellsPanel_Unfreeze(BellsPanel *panel)
{
    panel->frozen = 0;
}
CLEAN_AS(func_0208b9b0, BellsPanel_Unfreeze)

/* func_0208b9b8 */
void BellsPanel_Freeze(BellsPanel *panel)
{
    panel->frozen = 1;
}
CLEAN_AS(func_0208b9b8, BellsPanel_Freeze)

/* func_0208b9c0 */
int BellsPanel_IsClosed(BellsPanel *panel)
{
    return panel->state == BELLS_PANEL_CLOSED;
}
CLEAN_AS(func_0208b9c0, BellsPanel_IsClosed)

/* func_0208b9d0 */
void BellsPanel_Hide(BellsPanel *panel)
{
    panel->shown = 0;
}
CLEAN_AS(func_0208b9d0, BellsPanel_Hide)

/* func_0208b9d8 */
void BellsPanel_Show(BellsPanel *panel)
{
    panel->shown = 1;
}
CLEAN_AS(func_0208b9d8, BellsPanel_Show)

/* func_0208b9e0: the lift updated, then the class's draw. */
void BellsPanel_CallDraw(BellsPanel *panel)
{
    BellsPanel_UpdateLift(panel);
    call_slot(panel, SLOT_DRAW);
}
CLEAN_AS(func_0208b9e0, BellsPanel_CallDraw)

/* func_0208b9f8: the class's update, then the shift eased. */
void BellsPanel_CallUpdate(BellsPanel *panel)
{
    call_slot(panel, SLOT_UPDATE);
    BellsPanel_UpdateShift(panel);
}
CLEAN_AS(func_0208b9f8, BellsPanel_CallUpdate)

/* func_0208ba10: the counting sound stopped (with its end sound if it played), the animation
 * restarted and the text box freed. */
void BellsPanel_Rewind(BellsPanel *panel)
{
    BellsPanel_SetCounting(panel, 0);
    CellAnim_Restart(&panel->anim);
    BellsPanel_FreeTextBox(panel);
}
CLEAN_AS(func_0208ba10, BellsPanel_Rewind)

/* func_0208ba30: not shown, the bells taken, the shift reset, closed. */
void BellsPanel_Reset(BellsPanel *panel)
{
    panel->shown = 0;
    BellsPanel_TakeBells(panel);
    BellsPanel_ResetShift(panel);
    BellsPanel_EnterClosed(panel);
}
CLEAN_AS(func_0208ba30, BellsPanel_Reset)

/* func_0208ba54 (vtable slot 3): the state's step, through the game's table (filled on the
 * first call).
 * REQUIRES: the state is 0-3 (the ROM indexes its table unchecked). */
void BellsPanel_Update(BellsPanel *panel)
{
    static const MemberPointer *const constants[4] = {
        &data_020e20f4, /* BellsPanel_StepClosed */
        &data_020e20e4, /* BellsPanel_StepOpening */
        &data_020e2154, /* BellsPanel_StepOpen */
        &data_020e2114, /* BellsPanel_StepClosing */
    };
    MemberTable_InitOnce(&data_021d3160, data_021d31b0, constants, 4);
    MemberPointer_CallVoid(&data_021d31b0[panel->state], panel);
}
CLEAN_AS(func_0208ba54, BellsPanel_Update)

/* func_0208bad4 (vtable slot 2): unless closed, the animation's cell drawn on the main screen
 * at the sprite's place plus the frame's offset, `lift` and `shift` (rounded) lower. */
void BellsPanel_Draw(BellsPanel *panel)
{
    if (panel->state == BELLS_PANEL_CLOSED) {
        return;
    }
    const OamEntry *cell = CellAnim_Cell(&panel->anim);
    if (cell == NULL) {
        return;
    }
    int x = ScreenSprite_X(&panel->base);
    x += CellAnim_FrameX(&panel->anim, -1);
    int shift = (panel->shift + 0x800) >> 12;
    int y = ScreenSprite_Y(&panel->base);
    y += CellAnim_FrameY(&panel->anim, -1);
    y += panel->lift + shift;
    OamBuffer_DrawCell(0, cell, x, y, -1, -1, FX_ONE, FX_ONE, 0, -1, 0, 0);
}
CLEAN_AS(func_0208bad4, BellsPanel_Draw)

/* The destructor's work (the ROM has it in both destructors). */
static void destruct(BellsPanel *panel)
{
    panel->base.vtable = data_020e21fc;
    BellsPanel_Rewind(panel);
    MessageText46_Destruct(&panel->text);
    CellAnim_Destruct(&panel->anim);
    ScreenSprite_DestructBase(&panel->base);
}

/* func_0208bb58 (vtable slot 1): destructed and freed. */
BellsPanel *BellsPanel_Delete(BellsPanel *panel)
{
    destruct(panel);
    Heap_OperatorDeleteB(panel);
    return panel;
}
CLEAN_AS(func_0208bb58, BellsPanel_Delete)

/* func_0208bb8c (vtable slot 0): the destructor: rewound, then the members and the base. */
BellsPanel *BellsPanel_Destruct(BellsPanel *panel)
{
    destruct(panel);
    return panel;
}
CLEAN_AS(func_0208bb8c, BellsPanel_Destruct)

/* func_0208bbbc: the constructor: closed, nothing shown, the shift reset. */
BellsPanel *BellsPanel_Construct(BellsPanel *panel)
{
    ScreenSprite_Construct(&panel->base);
    panel->base.vtable = data_020e21fc;
    CellAnim_Construct(&panel->anim);
    panel->state = BELLS_PANEL_CLOSED;
    panel->lift = 0;
    panel->shift = 0;
    panel->shift_target = 0;
    panel->shift_speed = 0;
    panel->shift_wait = -1;
    panel->box = NULL;
    MessageText46_Construct(&panel->text);
    panel->bells = 0;
    panel->shown = 0;
    panel->counting = 0;
    panel->frozen = 0;
    return panel;
}
CLEAN_AS(func_0208bbbc, BellsPanel_Construct)
