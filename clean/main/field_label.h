/* A label window main keeps on the field (data_021f6b20, class Base_020b8b88 of
 * include/cpp/main/Base_020b8b88.h): a sliding window (func_0208a844's) that shows one of
 * three things, run each frame by func_020b8b88 through one handler per state:
 * - a message (`message` 1-10, for `timer` frames from data_020d2298, set by func_020b889c),
 *   placed at (18, -48); messages 1 and 2 alternate with a second text while they stay up;
 * - a notice (`notice` 1-3, for 60 frames, set by func_020b88c0), placed at (0, -48);
 * - the name of an item (`item`, chosen by func_020b8af0 each frame), over player 4's head.
 * The message goes before the notice and the notice before the item; the window closes when
 * what it shows ends or something before it comes.
 *
 * The window (0xec bytes from 0x08) derives from the sliding window: at 0xe0 in it a frame count,
 * at 0xe4 a request to show, at 0xe8 a mode (func_020b9068) from data_020d227c. */
#ifndef CLEAN_MAIN_FIELD_LABEL_H
#define CLEAN_MAIN_FIELD_LABEL_H

#include "types.h"

/* The states (FieldLabel.state, the order of func_020b8b88's table). */
enum FieldLabelState {
    FIELD_LABEL_CLOSED = 0,
    FIELD_LABEL_ITEM = 1,
    FIELD_LABEL_NOTICE = 2,
    FIELD_LABEL_MESSAGE = 3,
};

/* The previous item when there was none. */
#define FIELD_LABEL_NO_ITEM 0xfff1

typedef struct FieldLabel {
    u8 unk_00[4];
    int state;         /* 0x04: FieldLabelState */
    u8 window[0xec];   /* 0x08 */
    const u16 *item;   /* 0xf4: the item whose name shows, or NULL */
    u16 previous_item; /* 0xf8: the code `item` had the frame before, or NO_ITEM */
    u8 unk_fa[2];
    u32 message;        /* 0xfc: 0 for none */
    u32 notice;         /* 0x100: 0 for none */
    int alternate;      /* 0x104: messages 1 and 2: 1 while the second text shows */
    int timer;          /* 0x108: frames the message or notice stays; -1 for ever */
    u8 message_started; /* 0x10c: a message was started since its text was last shown */
    u8 notice_renewed;  /* 0x10d: a notice was renewed this frame */
} FieldLabel;

void FieldLabel_UpdateMessage(FieldLabel *label);
void FieldLabel_EnterMessage(FieldLabel *label);
void FieldLabel_UpdateNotice(FieldLabel *label);
void FieldLabel_EnterNotice(FieldLabel *label);
void FieldLabel_UpdateItem(FieldLabel *label);
void FieldLabel_EnterItem(FieldLabel *label);
void FieldLabel_UpdateClosed(FieldLabel *label);
void FieldLabel_EnterClosed(FieldLabel *label);
int FieldLabel_MessageActive(FieldLabel *label);
int FieldLabel_NoticeActive(FieldLabel *label);
void FieldLabel_StartMessage(FieldLabel *label);
void FieldLabel_RenewNotice(FieldLabel *label);
void FieldLabel_SetMessageMode(FieldLabel *label);
void FieldLabel_ShowMessageText(FieldLabel *label, int first);
void FieldLabel_ShowNoticeText(FieldLabel *label);
void FieldLabel_ShowItemName(FieldLabel *label);
void FieldLabel_PlaceForMessage(FieldLabel *label);
void FieldLabel_PlaceForNotice(FieldLabel *label);
void FieldLabel_PlaceOverPlayer(FieldLabel *label);

/* The object (field_label_window.h for its window), its frame, the field's label
 * (data_021f6b20) and what the rest of the game shows in it. */
void FieldLabel_PickItem(FieldLabel *label);
void FieldLabel_Draw(FieldLabel *label);
void FieldLabel_Update(FieldLabel *label);
void FieldLabel_ResetWindow(FieldLabel *label);
void FieldLabel_Reset(FieldLabel *label);
void FieldLabel_DrawGlobal(void);
void FieldLabel_UpdateGlobal(void);
void FieldLabel_ResetGlobalWindow(void);
void FieldLabel_ResetGlobal(void);
FieldLabel *FieldLabel_Delete(FieldLabel *label);
FieldLabel *FieldLabel_Destroy(FieldLabel *label);
FieldLabel *FieldLabel_Construct(FieldLabel *label);
void FieldLabel_RaiseEndFailure(void);
void FieldLabel_ShowNotice(int notice);
void FieldLabel_ClearMessage(void);
void FieldLabel_ShowMessage10(void);
void FieldLabel_ShowMessage9(void);
void FieldLabel_ShowTableMessage(int index);
void FieldLabel_ChooseMessage(int index);

#endif
