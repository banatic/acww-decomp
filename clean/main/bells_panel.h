/* The fourth screen panel (screen_panels.h, the member at 0x2c4 of data_021d3258, so the object
 * at data_021d351c): a sprite (vtable data_020e21fc, 0x84 bytes, derived from main's screen
 * sprite base, screen_sprite.h) that shows the player's bells, the money in the pockets plus
 * the bells held on the pockets screen's cursor (data_021cfc74), in a text box of 8 tiles.
 *
 * Its states, stepped by its update (BellsPanel_Update, through a table of member functions):
 * - closed: once `shown` is set, the bells taken as they are, the text box made and the
 *   opening animation started;
 * - opening: until the opening animation is done;
 * - open: the number shown counts toward the bells (unless `frozen`), with the counting sound
 *   playing while it moves and a sound when it stops; once `shown` is cleared it closes;
 * - closing: until the closing animation is done, then the text box is freed.
 *
 * It is drawn lower while state flag 4's value is below 1.0 (up to 192 pixels at 0), and 40
 * pixels lower, eased in and out, while another system's quick message balloon is out
 * (QuickMessage_OtherBalloonBusy) and state flag 4 is set. */
#ifndef CLEAN_MAIN_BELLS_PANEL_H
#define CLEAN_MAIN_BELLS_PANEL_H

#include "message_texts.h" /* MessageText46 */
#include "screen_icon.h"   /* CellAnim */
#include "screen_sprite.h"
#include "text_draw.h" /* TextDrawBox */
#include "types.h"

enum BellsPanelState {
    BELLS_PANEL_CLOSED = 0,
    BELLS_PANEL_OPENING = 1,
    BELLS_PANEL_OPEN = 2,
    BELLS_PANEL_CLOSING = 3,
};

typedef struct BellsPanel {
    ScreenSprite base;  /* vtable data_020e21fc */
    CellAnim anim;      /* 0x0c: data_020d5c54 opening, data_020d5c5c closing */
    int state;          /* 0x20: BellsPanelState */
    int lift;           /* 0x24: pixels lower, from state flag 4's value */
    int shift;          /* 0x28: 20.12 pixels lower, eased toward `shift_target` */
    int shift_target;   /* 0x2c: 0, or 40 pixels while another balloon is out */
    int shift_speed;    /* 0x30: the ease's largest step */
    int shift_wait;     /* 0x34: frames a new target has waited, -1 for none since the reset */
    TextDrawBox *box;   /* 0x38: the number's text box, or NULL */
    MessageText46 text; /* 0x3c: the number's characters */
    int bells;          /* 0x7c: the number shown */
    u8 shown;           /* 0x80: the panel is asked to be shown */
    u8 counting;        /* 0x81: the counting sound plays */
    u8 frozen;          /* 0x82: the number shown is not counted toward the bells */
    u8 pad_83;
} BellsPanel;

void BellsPanel_ResetShift(BellsPanel *panel);
void BellsPanel_UpdateShift(BellsPanel *panel);
void BellsPanel_UpdateLift(BellsPanel *panel);
int BellsPanel_Bells(BellsPanel *panel);
void BellsPanel_SetCounting(BellsPanel *panel, int counting);
void BellsPanel_FormatBells(BellsPanel *panel);
int BellsPanel_Count(BellsPanel *panel);
void BellsPanel_TakeBells(BellsPanel *panel);
void BellsPanel_FreeTextBox(BellsPanel *panel);
void BellsPanel_OpenTextBox(BellsPanel *panel);
void BellsPanel_StepClosing(BellsPanel *panel);
void BellsPanel_EnterClosing(BellsPanel *panel);
void BellsPanel_StepOpen(BellsPanel *panel);
void BellsPanel_EnterOpen(BellsPanel *panel);
void BellsPanel_StepOpening(BellsPanel *panel);
void BellsPanel_EnterOpening(BellsPanel *panel);
void BellsPanel_StepClosed(BellsPanel *panel);
void BellsPanel_EnterClosed(BellsPanel *panel);
void BellsPanel_Unfreeze(BellsPanel *panel);
void BellsPanel_Freeze(BellsPanel *panel);
int BellsPanel_IsClosed(BellsPanel *panel);
void BellsPanel_Hide(BellsPanel *panel);
void BellsPanel_Show(BellsPanel *panel);
void BellsPanel_CallDraw(BellsPanel *panel);
void BellsPanel_CallUpdate(BellsPanel *panel);
void BellsPanel_Rewind(BellsPanel *panel);
void BellsPanel_Reset(BellsPanel *panel);
void BellsPanel_Update(BellsPanel *panel);
void BellsPanel_Draw(BellsPanel *panel);
BellsPanel *BellsPanel_Delete(BellsPanel *panel);
BellsPanel *BellsPanel_Destruct(BellsPanel *panel);
BellsPanel *BellsPanel_Construct(BellsPanel *panel);

#endif
