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

#include "popup.h"
#include "types.h"

/* The first words of a talk, one of the 0x1e9c-byte entries at the word 0x021cda88 points to
 * (func_020682e0 gives one). */
typedef struct Talk {
    u32 unk_00;
    s32 state;   /* 0x04: TalkState */
    s32 request; /* 0x08: set to 1 to start the talk */
} Talk;

/* The values of a talk's `state` read here. */
enum TalkState { TALK_CLOSED = 0, TALK_UP = 2 };

/* A message receiver of main (class vtable 0x020df008: constructor func_02066a04, destructor
 * func_020669e0; the receiver of Base_02066994): the name of a message file and the number
 * of a message in it, which a talk shows. */
typedef struct MessageReceiver {
    const void *vtable; /* data_020df008 */
    char name[26];      /* 0x04: the file, written by func_020a8164 (25 characters at most) */
    u8 message;         /* 0x1e: the message's number in it */
    u8 unk_1f;
    u8 member_20[0x20]; /* 0x20: constructed by func_02066a9c */
    Talk *talk;         /* 0x40: the talk showing it, set by func_02068340 */
    u8 unk_44;
    u8 pad_45[3];
} MessageReceiver;

/* The error message's steps, in `step`. */
enum ErrorMessageStep {
    ERROR_MESSAGE_STARTING = 0, /* the talk was asked for; waiting for it to come up */
    ERROR_MESSAGE_SHOWN = 1,    /* waiting for a button or the pen */
    ERROR_MESSAGE_CLOSING = 2,  /* the talk was asked to end; waiting for it to close */
    ERROR_MESSAGE_DONE = 3      /* also the step after construction */
};

typedef struct ErrorMessage {
    Popup popup;              /* 0x00 */
    MessageReceiver receiver; /* 0xd0 */
    u8 step;                  /* 0x118: ErrorMessageStep */
    u8 fatal;                 /* 0x119: not 0: the message never closes */
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
