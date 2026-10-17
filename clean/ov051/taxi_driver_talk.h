/* The taxi driver's talk scene (taxi_driver.h: TaxiDriverTalk, vtable 0x02261804), the
 * questions of a new game, in the lines of "sp_etc_sequence3".
 *
 * Its vtable slots, beyond the scene base's: 0x00 and 0x04 its destructors, 0x10 a line
 * begins (TaxiDriverTalk_OnLineBegins), 0x14 a line ended (TaxiDriverTalk_OnLineEnded), 0x18
 * the player's answer (TaxiDriverTalk_OnAnswer), 0x1c a message's tag 1/11 to 1/15
 * (TaxiDriverTalk_OnTag: 0 stops the taxi's rain), 0x78 the line the talk starts with
 * (TaxiDriverTalk_Line) and 0x84 a command of the scene ended (TaxiDriverTalk_RunAfter).
 *
 * The answers and the ends of lines go to the handlers of two tables keyed by the line shown
 * (function-local statics filled from the overlay's constants on the first call, bit 0 of a
 * guard word saying they were). Many lines come in two, one for each kind of player (byte
 * 0x1c of the current player's id, PlayerId_Byte1c: 0 or 1, set by the answers to the lines
 * 0x0b and 0x0c): the handlers add that kind to the line they pick (TaxiDriverTalk_KindLine).
 *
 * Some ends of lines open screen 2 (GroupParams_Open) in a mode and set the work done once it
 * closes (TaxiDriverTalk_SetAfter, its slot 0x84): after mode 0x30 line 2 (the time told
 * again), after mode 0x0f line 0x29 or 9 (by GroupParams_C4CIs2), after mode 0x10 line 0x11.
 * The three questions at the lines 0x03/0x05/0x28, 0x19/0x1a and 0x1f/0x20 add 4, 2 and 1
 * points to the driver when answered with the second choice; at the lines 0x25 and 0x26 the
 * points pick the player's face, hair and clothes (TaxiDriverTalk_SetLooks) and the driver
 * leaves (state 4). */
#ifndef CLEAN_OV051_TAXI_DRIVER_TALK_H
#define CLEAN_OV051_TAXI_DRIVER_TALK_H

#include "taxi_driver.h"
#include "types.h"

/* The work done once a command ends (TaxiDriverTalk_SetAfter). */
enum TaxiDriverTalkAfter {
    TAXI_DRIVER_TALK_AFTER_SCREEN_10 = 0, /* line 0x11 + kind, after screen mode 0x10 */
    TAXI_DRIVER_TALK_AFTER_SCREEN_0F = 1, /* line 0x29 or 9, after screen mode 0x0f */
    TAXI_DRIVER_TALK_AFTER_TIME = 2,      /* line 2, after screen mode 0x30 */
    TAXI_DRIVER_TALK_AFTERS = 3
};

/* What its line function gives: the message file's name (an address) and the line. */
typedef struct TaxiDriverTalkStart {
    u32 text;
    u8 message;
    u8 unk_05[3];
} TaxiDriverTalkStart;

unsigned char TaxiDriverTalk_KindLine(TaxiDriverTalk *talk, int line);
void TaxiDriverTalk_OnAnswer(TaxiDriverTalk *talk);
void TaxiDriverTalk_OnAnswerPoints1(TaxiDriverTalk *talk, int answer);
void TaxiDriverTalk_OnAnswerPoints2(TaxiDriverTalk *talk, int answer);
void TaxiDriverTalk_OnAnswerPoints4(TaxiDriverTalk *talk, int answer);
void TaxiDriverTalk_OnAnswer30(TaxiDriverTalk *talk, int answer);
void TaxiDriverTalk_OnAnswerTown(TaxiDriverTalk *talk, void *answer);
void TaxiDriverTalk_OnAnswer0b(TaxiDriverTalk *talk, int answer);
void TaxiDriverTalk_OnAnswer0c(TaxiDriverTalk *talk, int answer);
void TaxiDriverTalk_OnAnswer11(TaxiDriverTalk *talk, int answer);
void TaxiDriverTalk_OnLineEnded(TaxiDriverTalk *talk);
void TaxiDriverTalk_SetLooks(TaxiDriverTalk *talk);
void TaxiDriverTalk_EndLooksLine(TaxiDriverTalk *talk);
void TaxiDriverTalk_End17(TaxiDriverTalk *talk);
void TaxiDriverTalk_End0e(TaxiDriverTalk *talk);
void TaxiDriverTalk_End0d(TaxiDriverTalk *talk);
void TaxiDriverTalk_End2b(TaxiDriverTalk *talk);
void TaxiDriverTalk_End1b(TaxiDriverTalk *talk);
void TaxiDriverTalk_End06(TaxiDriverTalk *talk);
void TaxiDriverTalk_AskScreen10(void *talk);
void TaxiDriverTalk_AskScreen0f(void *talk);
void TaxiDriverTalk_AskTime(void *talk);
void TaxiDriverTalk_OnLineBegins(TaxiDriverTalk *talk);
void TaxiDriverTalk_AfterTime(TaxiDriverTalk *talk);
void TaxiDriverTalk_AfterScreen0f(TaxiDriverTalk *talk);
void TaxiDriverTalk_AfterScreen10(TaxiDriverTalk *talk);
void TaxiDriverTalk_SetAfter(TaxiDriverTalk *talk, int after);
void TaxiDriverTalk_RunAfter(TaxiDriverTalk *talk);
void TaxiDriverTalk_Line(int talk, TaxiDriverTalkStart *out);
void TaxiDriverTalk_OnTag(int talk, int value);
void TaxiDriverTalk_Begin(TaxiDriverTalk *talk, TaxiDriver *owner);
void *TaxiDriverTalk_Delete(void *talk);
TaxiDriverTalk *TaxiDriverTalk_Destroy(TaxiDriverTalk *talk);
void *TaxiDriverTalk_Construct(void *talk);

#endif
