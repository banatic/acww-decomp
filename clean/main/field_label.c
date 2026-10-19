/* The field's label window (field_label.h). */
#include "field_label.h"

#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/camera_control.h"
#include "main/camera_view.h"
#include "main/message_reader.h"

#include <string.h>

#include "autoload_2/heap.h"
#include "main/caution_window.h"
#include "main/field_label_window.h"
#include "main/overlay_groups.h"
#include "main/scene_query.h"
#include "event_queue.h"
#include "globe.h"
#include "message_receiver.h"
#include "name_texts.h"
#include "ov004/member_pointer.h"
#include "player_actor_ops.h"
#include "sliding_window.h"
#include "state_flags.h"
#include "talk_object.h"

static_assert(offsetof(FieldLabel, item) == 0xf4, "FieldLabel");
static_assert(offsetof(FieldLabel, notice_renewed) == 0x10d, "FieldLabel");

/* Where the message and the notice are placed in the window. */
#define FIELD_LABEL_MESSAGE_X 18
#define FIELD_LABEL_TOP_Y (-48)
/* How far above player 4's feet the item's name is placed (3.75). */
#define FIELD_LABEL_HEAD_HEIGHT 0x3c00
/* The second texts of messages 1 and 2. */
#define FIELD_LABEL_SECOND_TEXT_1 0x93
#define FIELD_LABEL_SECOND_TEXT_2 0x94
#define FIELD_LABEL_NOTICE_FRAMES 60

/* A message part (func_020a8228, 0x5c bytes) and an item's name (func_02062f90, 0x28 bytes). */
typedef struct FieldLabelText {
    u32 words[0x5c / 4];
} FieldLabelText;
typedef struct FieldLabelItemName {
    u32 words[0x28 / 4];
} FieldLabelItemName;

extern const u8 data_020d226c[];  /* per notice: its text in the menu messages */
extern const u8 data_020d2270[];  /* per message: its text */
extern const u8 data_020d227c[];  /* per message: the window's mode */
extern const s16 data_020d2298[]; /* per message: how many frames it stays (-1: for ever) */
extern Mtx43 data_021fbe48;       /* a copy of the camera's view matrix */
extern CameraControl *data_021c67a4;

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);

static void *window_of(FieldLabel *label)
{
    return label->window;
}

/* func_020b866c (state MESSAGE): counts the timer down; back to CLOSED once the window is shut.
 * A message still up redraws its text when the window's count reaches 29; an ended one closes
 * the window unless its mode keeps it the first 25 frames. */
void FieldLabel_UpdateMessage(FieldLabel *label)
{
    if (label->timer > 0) {
        label->timer--;
    }
    if (SlidingWindow_State(window_of(label)) == 0) {
        FieldLabel_EnterClosed(label);
    } else if (!FieldLabel_MessageActive(label)) {
        if (FieldLabelWindow_MarkerBlinkShown(window_of(label)) == 0) {
            SlidingWindow_RequestClose(window_of(label));
        }
    } else if (FieldLabelWindow_MarkerBlinkLast(window_of(label)) != 0) {
        FieldLabel_ShowMessageText(label, 0);
    }
}
CLEAN_AS(func_020b866c, FieldLabel_UpdateMessage)

/* func_020b86d0 */
void FieldLabel_EnterMessage(FieldLabel *label)
{
    FieldLabelWindow_RequestMarker(window_of(label));
    label->state = FIELD_LABEL_MESSAGE;
}
CLEAN_AS(func_020b86d0, FieldLabel_EnterMessage)

/* func_020b86e4 (state NOTICE): counts the timer down; back to CLOSED once the window is shut.
 * The window stays while the notice does and was not renewed this frame, and no message came. */
void FieldLabel_UpdateNotice(FieldLabel *label)
{
    if (label->timer > 0) {
        label->timer--;
    }
    if (SlidingWindow_State(window_of(label)) == 0) {
        FieldLabel_EnterClosed(label);
        return;
    }
    if (!FieldLabel_MessageActive(label) && FieldLabel_NoticeActive(label) && label->notice_renewed == 0) {
        return;
    }
    SlidingWindow_RequestClose(window_of(label));
}
CLEAN_AS(func_020b86e4, FieldLabel_UpdateNotice)

/* func_020b873c */
void FieldLabel_EnterNotice(FieldLabel *label)
{
    label->state = FIELD_LABEL_NOTICE;
}
CLEAN_AS(func_020b873c, FieldLabel_EnterNotice)

/* func_020b8744 (state ITEM): back to CLOSED once the window is shut. The name follows player
 * 4's head while the item stays the same and no message or notice came; else the window
 * closes. */
void FieldLabel_UpdateItem(FieldLabel *label)
{
    if (SlidingWindow_State(window_of(label)) == 0) {
        FieldLabel_EnterClosed(label);
        return;
    }
    if (label->item != NULL && (label->previous_item == FIELD_LABEL_NO_ITEM || label->previous_item == *label->item) &&
        !FieldLabel_MessageActive(label) && !FieldLabel_NoticeActive(label)) {
        FieldLabel_PlaceOverPlayer(label);
        return;
    }
    SlidingWindow_RequestClose(window_of(label));
}
CLEAN_AS(func_020b8744, FieldLabel_UpdateItem)

/* func_020b87a4 */
void FieldLabel_EnterItem(FieldLabel *label)
{
    label->state = FIELD_LABEL_ITEM;
}
CLEAN_AS(func_020b87a4, FieldLabel_EnterItem)

/* func_020b87ac (state CLOSED): prepares the first of the message, the notice and the item
 * there is, and goes to its state if the window opens. */
void FieldLabel_UpdateClosed(FieldLabel *label)
{
    if (FieldLabel_MessageActive(label)) {
        FieldLabel_PlaceForMessage(label);
        FieldLabel_ShowMessageText(label, 1);
        FieldLabel_SetMessageMode(label);
        if (SlidingWindow_RequestOpen(window_of(label)) != NULL) {
            FieldLabel_EnterMessage(label);
        }
    } else if (FieldLabel_NoticeActive(label)) {
        FieldLabel_PlaceForNotice(label);
        FieldLabel_ShowNoticeText(label);
        FieldLabelWindow_SetMode(window_of(label), 0);
        if (SlidingWindow_RequestOpen(window_of(label)) != NULL) {
            FieldLabel_EnterNotice(label);
        }
    } else if (label->item != NULL) {
        FieldLabel_PlaceOverPlayer(label);
        FieldLabel_ShowItemName(label);
        FieldLabelWindow_SetMode(window_of(label), 0);
        if (SlidingWindow_RequestOpen(window_of(label)) != NULL) {
            FieldLabel_EnterItem(label);
        }
    }
}
CLEAN_AS(func_020b87ac, FieldLabel_UpdateClosed)

/* func_020b884c */
void FieldLabel_EnterClosed(FieldLabel *label)
{
    label->state = FIELD_LABEL_CLOSED;
}
CLEAN_AS(func_020b884c, FieldLabel_EnterClosed)

/* func_020b8854: a message is set and its time is not over. */
int FieldLabel_MessageActive(FieldLabel *label)
{
    return label->message != 0 && label->timer != 0;
}
CLEAN_AS(func_020b8854, FieldLabel_MessageActive)

/* func_020b8878: a notice is set and its time is not over. QUIRK: the message and the notice
 * share the timer. */
int FieldLabel_NoticeActive(FieldLabel *label)
{
    return label->notice != 0 && label->timer != 0;
}
CLEAN_AS(func_020b8878, FieldLabel_NoticeActive)

/* func_020b889c: starts the message set in `message` for its number of frames. */
void FieldLabel_StartMessage(FieldLabel *label)
{
    label->timer = data_020d2298[label->message];
    label->message_started = 1;
}
CLEAN_AS(func_020b889c, FieldLabel_StartMessage)

/* func_020b88c0: (re)starts the notice set in `notice` for 60 frames. */
void FieldLabel_RenewNotice(FieldLabel *label)
{
    label->timer = FIELD_LABEL_NOTICE_FRAMES;
    label->notice_renewed = 1;
}
CLEAN_AS(func_020b88c0, FieldLabel_RenewNotice)

/* func_020b88d8: the window's mode for the message. */
void FieldLabel_SetMessageMode(FieldLabel *label)
{
    FieldLabelWindow_SetMode(window_of(label), data_020d227c[label->message]);
}
CLEAN_AS(func_020b88d8, FieldLabel_SetMessageMode)

/* func_020b88f0: puts the message's text in the window: always when `first` (which also starts
 * with the first text), else when the message was started again or alternates (messages 1 and
 * 2, whose second text is 0x93 or 0x94); a redraw that is not the first also calls
 * func_0208a9e4 (with 1) and func_020b8fe0 on the window. An alternating message then turns to
 * its other text. */
void FieldLabel_ShowMessageText(FieldLabel *label, int first)
{
    FieldLabelText text;
    u8 message_text;

    MessagePart_Construct((MessagePart *) &text);
    message_text = data_020d2270[label->message];
    int is_1 = label->message == 1;
    int is_2 = label->message == 2;
    int alternates = is_1 || is_2;

    u8 started = label->message_started;
    label->message_started = 0;
    int show;
    if (first != 0) {
        label->alternate = 0;
        show = 1;
    } else {
        show = started != 0 || alternates;
    }

    if (show) {
        if (label->alternate == 1) {
            if (is_1) {
                message_text = FIELD_LABEL_SECOND_TEXT_1;
            } else if (is_2) {
                message_text = FIELD_LABEL_SECOND_TEXT_2;
            }
        }
        MessageReader_LoadMenuMessage(&text, &message_text, NULL);
        SlidingWindow_SetText(window_of(label), (struct TextObject *) &text);
        if (first == 0) {
            SlidingWindow_RefreshText(window_of(label), 1);
            FieldLabelWindow_StartMarker(window_of(label));
        }
    }

    if (alternates) {
        label->alternate++;
        if (label->alternate >= 2) {
            label->alternate = 0;
        }
    }
    MessagePart_Destruct((MessagePart *) &text);
}
CLEAN_AS(func_020b88f0, FieldLabel_ShowMessageText)

/* func_020b89cc: puts the notice's text in the window. */
void FieldLabel_ShowNoticeText(FieldLabel *label)
{
    FieldLabelText text;
    u8 notice_text = data_020d226c[label->notice];

    MessagePart_Construct((MessagePart *) &text);
    MessageReader_LoadMenuMessage(&text, &notice_text, NULL);
    SlidingWindow_SetText(window_of(label), (struct TextObject *) &text);
    MessagePart_Destruct((MessagePart *) &text);
}
CLEAN_AS(func_020b89cc, FieldLabel_ShowNoticeText)

/* func_020b8a10: puts the item's name in the window. */
void FieldLabel_ShowItemName(FieldLabel *label)
{
    FieldLabelItemName name;

    NameText_ConstructItem((NameText *) &name, (u16 *) label->item);
    SlidingWindow_SetText(window_of(label), (struct TextObject *) &name);
    NameText_Destruct((NameText *) &name);
}
CLEAN_AS(func_020b8a10, FieldLabel_ShowItemName)

/* func_020b8a3c */
void FieldLabel_PlaceForMessage(FieldLabel *label)
{
    SlidingWindow_SetPlace(window_of(label), FIELD_LABEL_MESSAGE_X, FIELD_LABEL_TOP_Y);
}
CLEAN_AS(func_020b8a3c, FieldLabel_PlaceForMessage)

/* func_020b8a4c */
void FieldLabel_PlaceForNotice(FieldLabel *label)
{
    SlidingWindow_SetPlace(window_of(label), 0, FIELD_LABEL_TOP_Y);
}
CLEAN_AS(func_020b8a4c, FieldLabel_PlaceForNotice)

/* func_020b8a5c: places the window over player 4's head: the point 3.75 above the player,
 * through the camera's view (copied to data_021fbe48) onto the near plane, in pixels from the
 * screen's middle (Y up). Nothing when there is no player 4. */
void FieldLabel_PlaceOverPlayer(FieldLabel *label)
{
    data_021fbe48 = *CameraControl_ViewMatrix();

    const Vec3 *player = PlayerActorOps_StartPosition(4);
    if (player != NULL) {
        Vec3 head = *player;
        Vec3 drawn;
        Vec3 view;

        head.y += FIELD_LABEL_HEAD_HEIGHT;
        Globe_Bend(&drawn, &head);
        MTX_MultVec43(&drawn, &data_021fbe48, &view);
        fx32 near = FX_Div(0x60000, (fx32) CameraControl_Projection(data_021c67a4));
        Vec_Scale(&view, FX_Div(-near, view.z));
        SlidingWindow_SetPlace(window_of(label), view.x >> 12, -view.y >> 12);
    }
}
CLEAN_AS(func_020b8a5c, FieldLabel_PlaceOverPlayer)

/* The field's label, the vtable of its class and the messages chosen by index
 * (FieldLabel_ShowTableMessage). */
extern FieldLabel data_021f6b20;
extern const u32 data_020e5848[];
extern const int data_020d2288[];

extern u8 data_020e54a8; /* 0 outdoors, 1 in a room */
typedef struct FieldLabelTalk {
    u32 unk_00;
    s32 state;
} FieldLabelTalk;

/* The kind of an item (the code's top four bits). */
#define FIELD_LABEL_ITEM_KIND(code) (((code) & 0xf000) >> 12)
/* The session state player 4 must be in for its item to show. */
#define FIELD_LABEL_PLAYER 4
#define FIELD_LABEL_PLAYER_STATE 2
/* The messages FieldLabel_ShowMessage9 and 10 start; 10 is not replaced by
 * FieldLabel_ChooseMessage. */
#define FIELD_LABEL_MESSAGE_9 9
#define FIELD_LABEL_MESSAGE_10 10
/* FieldLabel_ChooseMessage's own messages, and the size of the table it reads by index. */
#define FIELD_LABEL_MESSAGE_1 1
#define FIELD_LABEL_MESSAGE_2 2
#define FIELD_LABEL_TABLE_MESSAGES 4

/* The window's vtable slots called here. */
#define FIELD_LABEL_WINDOW_SLOT_DRAW 2
#define FIELD_LABEL_WINDOW_SLOT_UPDATE 3

typedef void FieldLabelWindowMethod(FieldLabelWindow *window);

static FieldLabelWindow *label_window(FieldLabel *label)
{
    return (FieldLabelWindow *) (void *) label->window;
}

static void call_window(FieldLabel *label, int slot)
{
    FieldLabelWindow *window = label_window(label);

    ((FieldLabelWindowMethod *) (uintptr_t) window->vtable[slot])(window);
}

/* The object's first word: its vtable. */
static void set_vtable(FieldLabel *label)
{
    u32 vtable = (u32) (uintptr_t) data_020e5848;

    memcpy(label->unk_00, &vtable, sizeof vtable);
}

/* Scenes 12-14, 46 and 47 show no notice and no chosen message. */
static int scene_without_label(void)
{
    u8 scene = SceneQuery_Current();

    return (scene >= 12 && scene <= 14) || scene == 46 || scene == 47;
}

/* func_020b8af0: the item whose name shows this frame: the one under player 4 while that player
 * is in session state 2 and the item is of a kind shown there (outdoors kinds 1, 3 and 4, in a
 * room only kind 1). The item code shown the frame before goes to `previous_item` (NO_ITEM
 * when there was none). */
void FieldLabel_PickItem(FieldLabel *label)
{
    const u16 *item = NULL;

    if (PlayerActorOps_InState(FIELD_LABEL_PLAYER_STATE, FIELD_LABEL_PLAYER) != 0) {
        item = PlayerActorOps_ItemAhead();
    }
    if (item != NULL) {
        int kind = FIELD_LABEL_ITEM_KIND(*item);
        int shown = data_020e54a8 == 0 ? kind == 1 || kind == 3 || kind == 4 : kind == 1;
        if (!shown) {
            item = NULL;
        }
    }
    label->previous_item = label->item != NULL ? *label->item : FIELD_LABEL_NO_ITEM;
    label->item = item;
}
CLEAN_AS(func_020b8af0, FieldLabel_PickItem)

/* func_020b8b74: the window drawn (its vtable slot 2). */
void FieldLabel_Draw(FieldLabel *label)
{
    call_window(label, FIELD_LABEL_WINDOW_SLOT_DRAW);
}
CLEAN_AS(func_020b8b74, FieldLabel_Draw)

/* The states func_020b8b88 calls through: a function-local static the game fills from these
 * constants on its first call (ov004/member_pointer.h). */
extern u32 data_021f6af0;
extern MemberPointer data_021f6b00[4];
extern const MemberPointer data_020e5820, data_020e5828, data_020e5830, data_020e5838;

/* func_020b8b88: one frame: the item picked, the state's handler run, the notice's renewal
 * forgotten, and the window updated (its vtable slot 3).
 * REQUIRES: `state` is a FieldLabelState (the original calls through a table of four). */
void FieldLabel_Update(FieldLabel *label)
{
    static const MemberPointer *const states[4] = {
        &data_020e5830,
        &data_020e5820,
        &data_020e5838,
        &data_020e5828,
    };
    MemberTable_InitOnce(&data_021f6af0, data_021f6b00, states, 4);
    FieldLabel_PickItem(label);
    switch (label->state) {
        case FIELD_LABEL_CLOSED:
            FieldLabel_UpdateClosed(label);
            break;
        case FIELD_LABEL_ITEM:
            FieldLabel_UpdateItem(label);
            break;
        case FIELD_LABEL_NOTICE:
            FieldLabel_UpdateNotice(label);
            break;
        case FIELD_LABEL_MESSAGE:
            FieldLabel_UpdateMessage(label);
            break;
    }
    label->notice_renewed = 0;
    call_window(label, FIELD_LABEL_WINDOW_SLOT_UPDATE);
}
CLEAN_AS(func_020b8b88, FieldLabel_Update)

/* func_020b8c24 */
void FieldLabel_ResetWindow(FieldLabel *label)
{
    FieldLabelWindow_Reset(label_window(label));
}
CLEAN_AS(func_020b8c24, FieldLabel_ResetWindow)

/* func_020b8c30: closed, with nothing to show; the window's byte at 0x5c set
 * (func_0208aa40). */
void FieldLabel_Reset(FieldLabel *label)
{
    label->state = FIELD_LABEL_CLOSED;
    SlidingWindow_CenterText((SlidingWindow *) label_window(label));
    label->item = NULL;
    label->previous_item = FIELD_LABEL_NO_ITEM;
    label->message = 0;
    label->notice = 0;
    label->alternate = 0;
    label->timer = 0;
    label->message_started = 0;
    label->notice_renewed = 0;
}
CLEAN_AS(func_020b8c30, FieldLabel_Reset)

/* func_020b8c88 */
void FieldLabel_DrawGlobal(void)
{
    FieldLabel_Draw(&data_021f6b20);
}
CLEAN_AS(func_020b8c88, FieldLabel_DrawGlobal)

/* func_020b8c98 */
void FieldLabel_UpdateGlobal(void)
{
    FieldLabel_Update(&data_021f6b20);
}
CLEAN_AS(func_020b8c98, FieldLabel_UpdateGlobal)

/* func_020b8ca8 */
void FieldLabel_ResetGlobalWindow(void)
{
    FieldLabel_ResetWindow(&data_021f6b20);
}
CLEAN_AS(func_020b8ca8, FieldLabel_ResetGlobalWindow)

/* func_020b8cb8 */
void FieldLabel_ResetGlobal(void)
{
    FieldLabel_Reset(&data_021f6b20);
}
CLEAN_AS(func_020b8cb8, FieldLabel_ResetGlobal)

/* func_020b8cc8 (vtable slot 1): destroyed and freed. */
FieldLabel *FieldLabel_Delete(FieldLabel *label)
{
    set_vtable(label);
    FieldLabelWindow_Destroy(label_window(label));
    Heap_OperatorDeleteB(label);
    return label;
}
CLEAN_AS(func_020b8cc8, FieldLabel_Delete)

/* func_020b8cec (vtable slot 0): the destructor. */
FieldLabel *FieldLabel_Destroy(FieldLabel *label)
{
    set_vtable(label);
    FieldLabelWindow_Destroy(label_window(label));
    return label;
}
CLEAN_AS(func_020b8cec, FieldLabel_Destroy)

/* func_020b8d08: the constructor (the field's label is built at start-up). */
FieldLabel *FieldLabel_Construct(FieldLabel *label)
{
    set_vtable(label);
    label->state = FIELD_LABEL_CLOSED;
    FieldLabelWindow_Construct(label_window(label));
    label->item = NULL;
    label->previous_item = FIELD_LABEL_NO_ITEM;
    label->message = 0;
    label->notice = 0;
    label->alternate = 0;
    label->timer = 0;
    label->message_started = 0;
    label->notice_renewed = 0;
    return label;
}
CLEAN_AS(func_020b8d08, FieldLabel_Construct)

/* func_020b8d6c: called when the network library could not end; raises the session's error
 * flag for it (CautionWindow_RaiseEndFailure). */
void FieldLabel_RaiseEndFailure(void)
{
    CautionWindow_RaiseEndFailure();
}
CLEAN_AS(func_020b8d6c, FieldLabel_RaiseEndFailure)

/* func_020b8d74: notice `notice` shown in the field's label (renewed for 60 frames), except in
 * scenes 12-14, 46 and 47. */
void FieldLabel_ShowNotice(int notice)
{
    if (!scene_without_label()) {
        data_021f6b20.notice = (u32) notice;
        FieldLabel_RenewNotice(&data_021f6b20);
    }
}
CLEAN_AS(func_020b8d74, FieldLabel_ShowNotice)

/* func_020b8db4: the field's label's message cleared (its timer is left). */
void FieldLabel_ClearMessage(void)
{
    data_021f6b20.message = 0;
}
CLEAN_AS(func_020b8db4, FieldLabel_ClearMessage)

/* func_020b8dc0 */
void FieldLabel_ShowMessage10(void)
{
    data_021f6b20.message = FIELD_LABEL_MESSAGE_10;
    FieldLabel_StartMessage(&data_021f6b20);
}
CLEAN_AS(func_020b8dc0, FieldLabel_ShowMessage10)

/* func_020b8dd8 */
void FieldLabel_ShowMessage9(void)
{
    data_021f6b20.message = FIELD_LABEL_MESSAGE_9;
    FieldLabel_StartMessage(&data_021f6b20);
}
CLEAN_AS(func_020b8dd8, FieldLabel_ShowMessage9)

/* func_020b8df0: message `index` of data_020d2288 (5 to 8 for indexes 0 to 3) started in the
 * field's label. */
void FieldLabel_ShowTableMessage(int index)
{
    data_021f6b20.message = (u32) data_020d2288[index];
    FieldLabel_StartMessage(&data_021f6b20);
}
CLEAN_AS(func_020b8df0, FieldLabel_ShowTableMessage)

/* func_020b8e10: the field's label's message chosen from the game's state, unless message 10
 * is set; a message other than none is started. Outside scenes 12-14, 46 and 47:
 * - when func_0203dff0, func_0203e21c or func_0203e190 holds: with an overlay group owner,
 *   message `index` of data_020d2288 when func_0206f53c holds (none for an index of 4 or more),
 *   else message 1; without one, message 2 while talk 0 is open;
 * - else message `index` of data_020d2288 with an owner and func_0206f53c holding (none for an
 *   index of 4 or more). */
void FieldLabel_ChooseMessage(int index)
{
    u32 message = 0;

    if (!scene_without_label()) {
        BOOL busy = EventQueue_IsObjectEvent() != 0 || EventQueue_IsKind5Unfinished() != 0 || EventQueue_IsKind9() != 0;
        BOOL from_table = FALSE;

        if (busy) {
            FieldLabelTalk *talk = (FieldLabelTalk *) TalkObject_Get(0);
            BOOL talking = talk != NULL && talk->state != 0;

            if (OverlayGroups_HasOwner()) {
                if (StateFlags_Test100() != 0) {
                    from_table = TRUE;
                } else {
                    message = FIELD_LABEL_MESSAGE_1;
                }
            } else if (talking) {
                message = FIELD_LABEL_MESSAGE_2;
            }
        } else if (OverlayGroups_HasOwner() && StateFlags_Test100() != 0) {
            from_table = TRUE;
        }
        if (from_table && index < FIELD_LABEL_TABLE_MESSAGES) {
            message = (u32) data_020d2288[index];
        }
    }
    if (data_021f6b20.message != FIELD_LABEL_MESSAGE_10) {
        data_021f6b20.message = message;
        if (message != 0) {
            FieldLabel_StartMessage(&data_021f6b20);
        }
    }
}
CLEAN_AS(func_020b8e10, FieldLabel_ChooseMessage)
