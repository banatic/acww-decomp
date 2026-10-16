/* The menu scenes' error message (error_message.h). */
#include "error_message.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "clean.h"
#include "main/display_shadow.h"
#include "main/text_label.h"

static_assert(offsetof(MessageReceiver, message) == 0x1e && offsetof(MessageReceiver, talk) == 0x40, "receiver");
static_assert(sizeof(MessageReceiver) == 0x48, "receiver");
static_assert(offsetof(ErrorMessage, receiver) == 0xd0 && offsetof(ErrorMessage, step) == 0x118, "error message");
static_assert(offsetof(ErrorMessage, fatal) == 0x119, "error message");

/* "obj_etc_error", the receiver's message file */
extern const char data_ov002_0220bea0[];

/* The talks */
extern Talk *func_020682e0(int index);                                     /* talk `index`, null when there are none */
extern void func_02068340(Talk *talk, MessageReceiver *receiver);          /* the receiver it shows; links both */
extern void func_02068320(Talk *talk);                                     /* unlinks its receiver, if any */
extern void func_02068314(Talk *talk);                                     /* byte 0x1e98 = 1 */
extern void func_02068308(Talk *talk);                                     /* byte 0x1e99 = 1 */
extern void func_02068440(Talk *talk);                                     /* byte 0x1e93 = 1 */
extern void func_02068434(Talk *talk);                                     /* byte 0x1e93 = 0 */
extern void func_02068428(Talk *talk);                                     /* byte 0x1e92 = 1 */
extern int func_02068484(Talk *talk, const u8 *message, const char *name); /* see ErrorMessage_EndTalk */
/* The message number ErrorMessage_EndTalk gives func_02068484. */
extern u8 data_021f43e8;

/* The message receiver */
extern MessageReceiver *func_02066a04(MessageReceiver *receiver);       /* constructor */
extern MessageReceiver *func_020669e0(MessageReceiver *receiver);       /* destructor */
extern void func_020a8164(MessageReceiver *receiver, const char *name); /* names its file */

/* main's sliding window, under the popup */
extern void func_0208aa48(Popup *popup, TextLabel *label); /* copies the label's text in */
extern void func_0208aa60(Popup *popup, int x, int y);     /* words 0x3c and 0x40: an offset */
extern void func_0208aa98(Popup *popup);                   /* byte 0x58 = 1 */

/* Flag 0x80 of the state flags (StateFlags_Test), 0 while the byte at 0x021cfc54 is set. */
extern int func_0206f56c(void);

extern PadState data_021fbe40;
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */

/* The talk the error message uses. */
#define ERROR_TALK 1

/* The popup's text: a message of "2d_menu", placed 0x40 lower. */
#define WINDOW_MESSAGE 100
#define WINDOW_OFFSET_Y 0x40

/* How much the sub screen is darkened (of 16). */
#define DIM_BRIGHTNESS (-10)

/* The buttons that close the message. */
#define BUTTON_A 0x0001
#define BUTTON_B 0x0002
#define BUTTON_X 0x0400
#define BUTTON_Y 0x0800

/* The vtable entries called here: the popup's draw, the receiver's reset. */
#define SLOT_DRAW 2
#define SLOT_RESET 2

typedef void PopupMethod(Popup *popup);
typedef void ReceiverMethod(MessageReceiver *receiver);

/* The function in vtable slot `slot` of an object whose first word is its vtable. */
static uintptr_t virtual_slot(const void *vtable, int slot)
{
    return ((const u32 *) vtable)[slot];
}

static void draw_popup(ErrorMessage *error)
{
    ((PopupMethod *) virtual_slot(error->popup.vtable, SLOT_DRAW))(&error->popup);
}

/* Gives the popup its text through `label` and queues it to show. */
static void queue_window(ErrorMessage *error, TextLabel *label)
{
    TextLabel_Construct(label);
    TextLabel_LoadMenuMessage((int) (uintptr_t) label, WINDOW_MESSAGE);
    func_0208aa48(&error->popup, label);
    func_0208aa60(&error->popup, 0, WINDOW_OFFSET_Y);
    Popup_Queue(&error->popup);
    func_0208aa98(&error->popup);
    Popup_SetDrawValue(&error->popup, 0);
}

/* func_ov002_0220b6b0: the sub screen back to normal brightness. */
void ErrorMessage_Undim(ErrorMessage *error)
{
    (void) error;
    DisplayShadow_EndSubObjWindowBrightness();
}
CLEAN_AS(func_ov002_0220b6b0, ErrorMessage_Undim)

/* func_ov002_0220b6b8: darkens the sub screen outside its OBJ window. */
void ErrorMessage_Dim(ErrorMessage *error)
{
    (void) error;
    DisplayShadow_BeginSubObjWindowBrightness();
    DisplayShadow_SetSubBrightness((u8) DIM_BRIGHTNESS);
}
CLEAN_AS(func_ov002_0220b6b8, ErrorMessage_Dim)

/* func_ov002_0220b6d0: once the receiver's talk has closed, unlinks the receiver from it and
 * returns 1; 0 while it is open.
 * REQUIRES: the receiver is linked to a talk (ErrorMessage_StartTalk ran). */
int ErrorMessage_ReleaseTalkIfClosed(ErrorMessage *error)
{
    Talk *talk = error->receiver.talk;

    if (talk->state == TALK_CLOSED) {
        func_02068320(talk);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov002_0220b6d0, ErrorMessage_ReleaseTalkIfClosed)

/* func_ov002_0220b6f4: asks the error's talk to end. When its message is the one at
 * 0x021f43f8, func_02068484 sets the message at 0x021f43e8 with no file name; the bytes at
 * 0x1e92 and 0x1e93 are then set to 1 and 0. */
void ErrorMessage_EndTalk(void)
{
    Talk *talk = func_020682e0(ERROR_TALK);

    func_02068484(talk, &data_021f43e8, NULL);
    func_02068428(talk);
    func_02068434(talk);
}
CLEAN_AS(func_ov002_0220b6f4, ErrorMessage_EndTalk)

/* func_ov002_0220b71c: whether the error's talk is up.
 * REQUIRES: the talks exist (func_020682e0 does not give null). */
int ErrorMessage_IsTalkUp(ErrorMessage *error)
{
    (void) error;
    return func_020682e0(ERROR_TALK)->state == TALK_UP;
}
CLEAN_AS(func_ov002_0220b71c, ErrorMessage_IsTalkUp)

/* func_ov002_0220b738: the sub screen back to normal brightness, after the popup alone. */
void ErrorMessage_UndimWindow(ErrorMessage *error)
{
    ErrorMessage_Undim(error);
}
CLEAN_AS(func_ov002_0220b738, ErrorMessage_UndimWindow)

/* func_ov002_0220b740: closes the popup; 1 when it is already closed. */
int ErrorMessage_HideWindow(ErrorMessage *error)
{
    return Popup_Hide(&error->popup, 0);
}
CLEAN_AS(func_ov002_0220b740, ErrorMessage_HideWindow)

/* func_ov002_0220b74c: a frame of the popup, which it then draws. */
void ErrorMessage_UpdateWindow(ErrorMessage *error)
{
    Popup_Update(&error->popup);
    draw_popup(error);
}
CLEAN_AS(func_ov002_0220b74c, ErrorMessage_UpdateWindow)

/* func_ov002_0220b764: shows the popup alone, at once, and darkens the sub screen.
 * QUIRK: returns what the destructor of its temporary label returns, the label's address on
 * the stack. */
int ErrorMessage_ShowWindow(ErrorMessage *error)
{
    TextLabel label;

    queue_window(error, &label);
    ErrorMessage_Dim(error);
    Popup_ShowQueued(&error->popup);
    return (int) (uintptr_t) TextLabel_Destruct(&label);
}
CLEAN_AS(func_ov002_0220b764, ErrorMessage_ShowWindow)

/* func_ov002_0220b7b8: while closing, waits for the talk to close, then brings the sub
 * screen back and is done. 1 when done (or not closing), 0 while waiting. */
int ErrorMessage_WaitClosed(ErrorMessage *error)
{
    if (error->step != ERROR_MESSAGE_CLOSING) {
        return 1;
    }
    if (!ErrorMessage_ReleaseTalkIfClosed(error)) {
        return 0;
    }
    ErrorMessage_Undim(error);
    error->step = ERROR_MESSAGE_DONE;
    return 1;
}
CLEAN_AS(func_ov002_0220b7b8, ErrorMessage_WaitClosed)

/* func_ov002_0220b7ec: asks the talk to end and starts closing.
 * QUIRK: returns 0x118, the offset of `step`; the callers ignore it. */
int ErrorMessage_Close(ErrorMessage *error)
{
    ErrorMessage_EndTalk();
    error->step = ERROR_MESSAGE_CLOSING;
    return (int) offsetof(ErrorMessage, step);
}
CLEAN_AS(func_ov002_0220b7ec, ErrorMessage_Close)

/* func_ov002_0220b804: while starting, waits for the talk to come up, then is shown. 1 when
 * shown (or not starting), 0 while waiting. */
int ErrorMessage_WaitUp(ErrorMessage *error)
{
    if (error->step != ERROR_MESSAGE_STARTING) {
        return 1;
    }
    if (!ErrorMessage_IsTalkUp(error)) {
        return 0;
    }
    error->step = ERROR_MESSAGE_SHOWN;
    return 1;
}
CLEAN_AS(func_ov002_0220b804, ErrorMessage_WaitUp)

/* func_ov002_0220b830: resets the receiver to message `*message` of "obj_etc_error", gives it
 * to the error's talk and starts the talk (without `flag`, the talk's byte 0x1e99 is set
 * too); a message that is not fatal darkens the sub screen now. */
void ErrorMessage_StartTalk(ErrorMessage *error, const u8 *message, int flag)
{
    Talk *talk = func_020682e0(ERROR_TALK);
    MessageReceiver *receiver = &error->receiver;

    ((ReceiverMethod *) virtual_slot(receiver->vtable, SLOT_RESET))(receiver);
    func_020a8164(receiver, data_ov002_0220bea0);
    receiver->message = *message;
    func_02068340(talk, receiver);
    func_02068314(talk);
    if (flag == 0) {
        func_02068308(talk);
    }
    talk->request = 1;
    func_02068440(talk);
    error->step = ERROR_MESSAGE_STARTING;
    if (error->fatal == 0) {
        ErrorMessage_Dim(error);
    }
}
CLEAN_AS(func_ov002_0220b830, ErrorMessage_StartTalk)

/* Whether the player closes the message this frame: with `check_flag80`, flag 0x80 of the
 * state flags (func_0206f56c); the pen going down; A, B, X or Y pressed. */
static int closing_input(int check_flag80)
{
    if (check_flag80 && func_0206f56c()) {
        return 1;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        return 1;
    }
    return (data_021fbe40.pressed & (BUTTON_A | BUTTON_B | BUTTON_X | BUTTON_Y)) != 0;
}

/* func_ov002_0220b8ac: a frame of the error message, then of its popup, which is drawn
 * unless the error is fatal. 1 once done (and then nothing else runs), else 0.
 *
 * The talk coming up shows the queued popup (and darkens the sub screen for a fatal error);
 * the player's input ends the talk and closes the popup; the talk closing brings the sub
 * screen back.
 * QUIRK: a fatal error, once its talk is up, loops forever here: the game stops. */
int ErrorMessage_Update(ErrorMessage *error, int check_flag80)
{
    switch (error->step) {
        case ERROR_MESSAGE_STARTING:
            if (ErrorMessage_IsTalkUp(error)) {
                error->step = ERROR_MESSAGE_SHOWN;
                Popup_ShowQueued(&error->popup);
                if (error->fatal != 0) {
                    ErrorMessage_Dim(error);
                }
            }
            break;
        case ERROR_MESSAGE_SHOWN:
            if (error->fatal != 0) {
                for (;;) {
                }
            }
            if (closing_input(check_flag80)) {
                ErrorMessage_EndTalk();
                error->step = ERROR_MESSAGE_CLOSING;
                Popup_Hide(&error->popup, 0);
            }
            break;
        case ERROR_MESSAGE_CLOSING:
            if (ErrorMessage_ReleaseTalkIfClosed(error)) {
                ErrorMessage_Undim(error);
                error->step = ERROR_MESSAGE_DONE;
            }
            break;
        case ERROR_MESSAGE_DONE:
            return 1;
        default:
            break;
    }
    Popup_Update(&error->popup);
    if (error->fatal == 0) {
        draw_popup(error);
    }
    return 0;
}
CLEAN_AS(func_ov002_0220b8ac, ErrorMessage_Update)

/* func_ov002_0220b9b8: opens the error message: talk 1 shows message `*message` of
 * "obj_etc_error" (ErrorMessage_StartTalk with `flag`), and the popup is queued to show once
 * the talk is up.
 * QUIRK: returns what the destructor of the popup's temporary label returns, the label's
 * address on the stack. */
int ErrorMessage_Open(ErrorMessage *error, const u8 *message, int flag, int fatal)
{
    error->fatal = (u8) fatal;
    ErrorMessage_StartTalk(error, message, flag);

    TextLabel label;
    queue_window(error, &label);
    return (int) (uintptr_t) TextLabel_Destruct(&label);
}
CLEAN_AS(func_ov002_0220b9b8, ErrorMessage_Open)

/* func_ov002_0220ba0c */
ErrorMessage *ErrorMessage_Destruct(ErrorMessage *error)
{
    func_020669e0(&error->receiver);
    Popup_Destroy(&error->popup);
    return error;
}
CLEAN_AS(func_ov002_0220ba0c, ErrorMessage_Destruct)

/* func_ov002_0220ba24 */
ErrorMessage *ErrorMessage_Construct(ErrorMessage *error)
{
    Popup_Construct(&error->popup);
    func_02066a04(&error->receiver);
    error->step = ERROR_MESSAGE_DONE;
    error->fatal = 0;
    return error;
}
CLEAN_AS(func_ov002_0220ba24, ErrorMessage_Construct)
