/* The talk scene of overlay 55's exchange character (XctExchangeTalk, xct_exchange.h; class
 * vtable 0x02260f44, derived from the scene class 0x020d9ff8). Its lines are of
 * "sp_etc_sequence1" (through the pointer data_ov055_02260e60):
 *   0x38  the line a talk starts with (slot 0x78, XctExchangeTalk_Line);
 *   0x39  once it ends, the exchange starts (unless a save of the exchange block failed: then
 *         0x36), and the talk is held while it runs (step 1);
 *   0x3a  said when the player stops the exchange (A, a tap, or opening the lid); answering it
 *         with the second choice ends the session's exchange;
 *   0x3b  once it ends, the town gets its own exchange block back (XctExchange_RestoreBlock);
 *   0x3c  said when the exchange is done; once it ends, what came is put in place
 *         (XctExchange_TakeReceived).
 *
 * While the talk is held its step (XctExchangeTalk.step, the table data_ov055_02260f0c of a C++
 * member and a flag each) runs before each step of the scene (its slot 0x80); a step whose flag
 * is clear would run instead when a command of the scene ends (slot 0x84), and then step 0:
 *   0  none;
 *   1  exchanging: when the exchange is done, the session's exchange ends, line 0x3c (step 2);
 *      when the player stops it, the library is told to stop and line 0x3a (step 3);
 *   2  done: once the lid is open, sound 0x69 and the talk released (step 0);
 *   3  stopping: once the lid is open: when the exchange was done after all, sound 0x69, the
 *      session's exchange ends and line 0x3c; while the library still runs, it is told to stop
 *      again and the talk stays; then the talk is released (step 0). */
#ifndef CLEAN_OV055_XCT_EXCHANGE_TALK_H
#define CLEAN_OV055_XCT_EXCHANGE_TALK_H

#include "ov004/member_pointer.h"
#include "types.h"
#include "xct_exchange.h"

/* XctExchangeTalk.step. */
#define XCT_EXCHANGE_TALK_STEP_NONE 0
#define XCT_EXCHANGE_TALK_STEP_EXCHANGING 1
#define XCT_EXCHANGE_TALK_STEP_DONE 2
#define XCT_EXCHANGE_TALK_STEP_STOPPING 3
#define XCT_EXCHANGE_TALK_STEPS 4

/* A step's function in data_ov055_02260f0c (12 bytes). */
typedef struct XctExchangeTalkStep {
    MemberPointer run; /* 0x00: void (talk) */
    u8 before_step;    /* 0x08: run before each step of the scene; else once a command ends */
    u8 unk_09[3];
} XctExchangeTalkStep;

/* What the talk starts with (its slot 0x78): the message file and the line. */
typedef struct XctExchangeTalkStart {
    const char *name;
    u8 message;
    u8 unk_05[3];
} XctExchangeTalkStart;

/* The class. */
XctExchangeTalk *XctExchangeTalk_Construct(XctExchangeTalk *talk);
XctExchangeTalk *XctExchangeTalk_Destruct(XctExchangeTalk *talk);
XctExchangeTalk *XctExchangeTalk_DestructDelete(XctExchangeTalk *talk);
void XctExchangeTalk_Begin(XctExchangeTalk *talk, XctExchange *owner);
void XctExchangeTalk_SetStep(XctExchangeTalk *talk, u32 step);
void XctExchangeTalk_RunStep(XctExchangeTalk *talk);
void XctExchangeTalk_OnCommandEnded(XctExchangeTalk *talk);

/* Its lines. */
int XctExchangeTalk_Line(XctExchangeTalk *talk, XctExchangeTalkStart *out);
void XctExchangeTalk_OnAnswer(XctExchangeTalk *talk);
void XctExchangeTalk_OnLineEnd(XctExchangeTalk *talk);

/* Its steps. */
void XctExchangeTalk_StepExchanging(XctExchangeTalk *talk);
void XctExchangeTalk_StepDone(XctExchangeTalk *talk);
void XctExchangeTalk_StepStopping(XctExchangeTalk *talk);

#endif
