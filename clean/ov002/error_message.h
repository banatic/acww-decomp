/* An error message of the menu scenes (those of overlays 090, 096, 099-112, 119, 121, 122,
 * 126, 129, 132 and 144 construct one; ov098 shows only its popup): a popup (popup.h) that
 * shows message 100 of "2d_menu", and a message receiver named "obj_etc_error" through which
 * talk 1 shows one message of that file, the error's. Its constructor is
 * ErrorMessage_Construct, its destructor ErrorMessage_Destruct; it has no vtable of its own
 * (the popup's is at its start).
 *
 * While the talk is up, the sub screen is darkened outside its OBJ window. A fatal error
 * (`fatal`) never ends: once its talk is up the game stays in ErrorMessage_Update. */
#ifndef CLEAN_OV002_ERROR_MESSAGE_H
#define CLEAN_OV002_ERROR_MESSAGE_H

#include "main/talk_receiver.h"
#include "popup.h"
#include "types.h"

/* The error message's steps, in `step`. */
enum ErrorMessageStep {
    ERROR_MESSAGE_STARTING = 0, /* the talk was asked for; waiting for it to come up */
    ERROR_MESSAGE_SHOWN = 1,    /* waiting for a button or the pen */
    ERROR_MESSAGE_CLOSING = 2,  /* the talk was asked to end; waiting for it to close */
    ERROR_MESSAGE_DONE = 3      /* also the step after construction */
};

/* Its message receiver is a talk's receiver (main/talk_receiver.h: class data_020df008, 0x48
 * bytes, the message receiver of main/message_receiver.h at its start); the talk showing it
 * (TalkReceiver.talk) is a talk of main/talk_object.h. */
typedef struct ErrorMessage {
    Popup popup;           /* 0x00 */
    TalkReceiver receiver; /* 0xd0: vtable data_020df008 */
    u8 step;               /* 0x118: ErrorMessageStep */
    u8 fatal;              /* 0x119: not 0: the message never closes */
} ErrorMessage;

void ErrorMessage_Undim(ErrorMessage *error);
void ErrorMessage_Dim(ErrorMessage *error);
int ErrorMessage_ReleaseTalkIfClosed(ErrorMessage *error);
void ErrorMessage_EndTalk(void);
int ErrorMessage_IsTalkUp(ErrorMessage *error);
void ErrorMessage_UndimWindow(ErrorMessage *error);
int ErrorMessage_HideWindow(ErrorMessage *error);
void ErrorMessage_UpdateWindow(ErrorMessage *error);
int ErrorMessage_ShowWindow(ErrorMessage *error);
int ErrorMessage_WaitClosed(ErrorMessage *error);
int ErrorMessage_Close(ErrorMessage *error);
int ErrorMessage_WaitUp(ErrorMessage *error);
void ErrorMessage_StartTalk(ErrorMessage *error, const u8 *message, int flag);
int ErrorMessage_Update(ErrorMessage *error, int check_flag80);
int ErrorMessage_Open(ErrorMessage *error, const u8 *message, int flag, int fatal);
ErrorMessage *ErrorMessage_Destruct(ErrorMessage *error);
ErrorMessage *ErrorMessage_Construct(ErrorMessage *error);

#endif
