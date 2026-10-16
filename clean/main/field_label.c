/* The field's label window (field_label.h). */
#include "field_label.h"

#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/camera_control.h"
#include "main/camera_view.h"
#include "main/message_reader.h"

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

/* The sliding window: its state (0 closed), asking it to close when open and to open when
 * closed (each says whether it did), its text, its place, and func_0208a9e4. */
extern int func_0208a844(void *window);
extern void *func_0208a9ac(void *window);
extern void *func_0208a9c8(void *window);
extern void func_0208aa48(void *window, void *text);
extern void func_0208aa60(void *window, int x, int y);
extern void func_0208a9e4(void *window, int flag);
/* The derived window: func_020b8fe0, whether it is in a mode and
 * under 25 frames or at frame 29, setting its mode, and asking it to show. */
extern void func_020b8fe0(void *window);
extern int func_020b9030(void *window);
extern int func_020b904c(void *window);
extern void func_020b9068(void *window, u8 mode);
extern void func_020b90a4(void *window);
/* Message parts, and items' names: built and destroyed. */
extern void *func_020a8228(FieldLabelText *text);
extern void *func_020a8210(FieldLabelText *text);
extern void *func_02062f90(FieldLabelItemName *name, const u16 *item);
extern void *func_02062f4c(FieldLabelItemName *name);
/* The bend of a map point into the drawn world (touch_pick_shapes.h), and an actor's
 * position. */
extern int func_0203f844(Vec3 *out, const Vec3 *map);
extern const Vec3 *func_02095794(int actor);

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
    if (func_0208a844(window_of(label)) == 0) {
        FieldLabel_EnterClosed(label);
    } else if (!FieldLabel_MessageActive(label)) {
        if (func_020b9030(window_of(label)) == 0) {
            func_0208a9ac(window_of(label));
        }
    } else if (func_020b904c(window_of(label)) != 0) {
        FieldLabel_ShowMessageText(label, 0);
    }
}
CLEAN_AS(func_020b866c, FieldLabel_UpdateMessage)

/* func_020b86d0 */
void FieldLabel_EnterMessage(FieldLabel *label)
{
    func_020b90a4(window_of(label));
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
    if (func_0208a844(window_of(label)) == 0) {
        FieldLabel_EnterClosed(label);
        return;
    }
    if (!FieldLabel_MessageActive(label) && FieldLabel_NoticeActive(label) && label->notice_renewed == 0) {
        return;
    }
    func_0208a9ac(window_of(label));
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
    if (func_0208a844(window_of(label)) == 0) {
        FieldLabel_EnterClosed(label);
        return;
    }
    if (label->item != NULL && (label->previous_item == FIELD_LABEL_NO_ITEM || label->previous_item == *label->item) &&
        !FieldLabel_MessageActive(label) && !FieldLabel_NoticeActive(label)) {
        FieldLabel_PlaceOverPlayer(label);
        return;
    }
    func_0208a9ac(window_of(label));
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
        if (func_0208a9c8(window_of(label)) != NULL) {
            FieldLabel_EnterMessage(label);
        }
    } else if (FieldLabel_NoticeActive(label)) {
        FieldLabel_PlaceForNotice(label);
        FieldLabel_ShowNoticeText(label);
        func_020b9068(window_of(label), 0);
        if (func_0208a9c8(window_of(label)) != NULL) {
            FieldLabel_EnterNotice(label);
        }
    } else if (label->item != NULL) {
        FieldLabel_PlaceOverPlayer(label);
        FieldLabel_ShowItemName(label);
        func_020b9068(window_of(label), 0);
        if (func_0208a9c8(window_of(label)) != NULL) {
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
    func_020b9068(window_of(label), data_020d227c[label->message]);
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

    func_020a8228(&text);
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
        MessageReader_LoadMenuMessage((int) (uintptr_t) &text, &message_text, NULL);
        func_0208aa48(window_of(label), &text);
        if (first == 0) {
            func_0208a9e4(window_of(label), 1);
            func_020b8fe0(window_of(label));
        }
    }

    if (alternates) {
        label->alternate++;
        if (label->alternate >= 2) {
            label->alternate = 0;
        }
    }
    func_020a8210(&text);
}
CLEAN_AS(func_020b88f0, FieldLabel_ShowMessageText)

/* func_020b89cc: puts the notice's text in the window. */
void FieldLabel_ShowNoticeText(FieldLabel *label)
{
    FieldLabelText text;
    u8 notice_text = data_020d226c[label->notice];

    func_020a8228(&text);
    MessageReader_LoadMenuMessage((int) (uintptr_t) &text, &notice_text, NULL);
    func_0208aa48(window_of(label), &text);
    func_020a8210(&text);
}
CLEAN_AS(func_020b89cc, FieldLabel_ShowNoticeText)

/* func_020b8a10: puts the item's name in the window. */
void FieldLabel_ShowItemName(FieldLabel *label)
{
    FieldLabelItemName name;

    func_02062f90(&name, label->item);
    func_0208aa48(window_of(label), &name);
    func_02062f4c(&name);
}
CLEAN_AS(func_020b8a10, FieldLabel_ShowItemName)

/* func_020b8a3c */
void FieldLabel_PlaceForMessage(FieldLabel *label)
{
    func_0208aa60(window_of(label), FIELD_LABEL_MESSAGE_X, FIELD_LABEL_TOP_Y);
}
CLEAN_AS(func_020b8a3c, FieldLabel_PlaceForMessage)

/* func_020b8a4c */
void FieldLabel_PlaceForNotice(FieldLabel *label)
{
    func_0208aa60(window_of(label), 0, FIELD_LABEL_TOP_Y);
}
CLEAN_AS(func_020b8a4c, FieldLabel_PlaceForNotice)

/* func_020b8a5c: places the window over player 4's head: the point 3.75 above the player,
 * through the camera's view (copied to data_021fbe48) onto the near plane, in pixels from the
 * screen's middle (Y up). Nothing when there is no player 4. */
void FieldLabel_PlaceOverPlayer(FieldLabel *label)
{
    data_021fbe48 = *CameraControl_ViewMatrix();

    const Vec3 *player = func_02095794(4);
    if (player != NULL) {
        Vec3 head = *player;
        Vec3 drawn;
        Vec3 view;

        head.y += FIELD_LABEL_HEAD_HEIGHT;
        func_0203f844(&drawn, &head);
        MTX_MultVec43(&drawn, &data_021fbe48, &view);
        fx32 near = FX_Div(0x60000, (fx32) CameraControl_Projection(data_021c67a4));
        Vec_Scale(&view, FX_Div(-near, view.z));
        func_0208aa60(window_of(label), view.x >> 12, -view.y >> 12);
    }
}
CLEAN_AS(func_020b8a5c, FieldLabel_PlaceOverPlayer)
