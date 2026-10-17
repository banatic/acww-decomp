/* The barber's talk scene (BarberTalk, barber.h; class vtable data_ov053_02261b08, derived from
 * the scene class 0x020d9ff8): the line it starts with (slot 0x78, BarberTalk_Line), the player's
 * answers (slot 0x18, BarberTalk_OnAnswer), what follows the end of a line (slot 0x14,
 * BarberTalk_OnLineEnded), the talk's closing (slot 0x70) and its going on in the same window
 * (slot 0x74). Its messages are of "sp_npc_barber".
 *
 * The talk's topic (BarberTalk.topic, BARBER_TOPIC_*) is set by the barber's states and picks
 * the line the talk starts with (the table data_ov053_02261a90):
 *   0  call:         she calls the player as the player comes in (line 0x43);
 *   1  first visit:  the player's first talk with her ever (line 0);
 *   2  welcome:      later talks (line 2);
 *   3  seated, hat:  the player sits in the chair wearing a hat or an accessory (line 0x40,
 *                    whose end takes it off and goes on with the chair's line);
 *   4  seated:       the player sits in the chair (the chair's line, BarberTalk_ChairLine);
 *   5  cut:          her cut is done (line 0xd, whose end compares the hair with the old one);
 *   6  paid:         the cut is paid for and the player has not sat down yet (line 0x3d);
 *   7  not seated:   the player sits elsewhere than in the chair (line 0x45);
 *   8  leaving:      the cut is paid for and the player walks to the door (line 0x42, whose
 *                    end walks the player back, the barber's state 9);
 *   9  hat back:     after the cut, with a hat or accessory in the player's record (line 0x41,
 *                    whose end puts it back on);
 *   10 claimed:      the player stands on the map's claimed object (line 0x46; then the scene's
 *                    exit 0 is taken);
 *   11-13 cut today: lines 5 to 7, at random, once a cut was had today;
 *   14 none:         picked afresh by the talk's line (1, 2, 6 or 11 to 13).
 *
 * A cut costs 3,000 bells (line 8): once paid, the flag 7 of the block 0x021d27ac is set until
 * the cut's last line (0xe or 0x37), which also sets the daily bit 0x13. The player picks a
 * style (lines 0x2f to 0x36, by the player's byte 0x1c; lines 0x17 and 0x18 switch to the other
 * set of styles) and a colour (lines 9 to 0xb and 0x38). */
#ifndef CLEAN_OV053_BARBER_TALK_H
#define CLEAN_OV053_BARBER_TALK_H

#include "main/scene_base.h"
#include "types.h"

struct Barber;

/* The talk's topics (BarberTalk.topic). */
enum BarberTopic {
    BARBER_TOPIC_CALL = 0,
    BARBER_TOPIC_FIRST_VISIT = 1,
    BARBER_TOPIC_WELCOME = 2,
    BARBER_TOPIC_SEATED_HAT = 3,
    BARBER_TOPIC_SEATED = 4,
    BARBER_TOPIC_CUT = 5,
    BARBER_TOPIC_PAID = 6,
    BARBER_TOPIC_NOT_SEATED = 7,
    BARBER_TOPIC_LEAVING = 8,
    BARBER_TOPIC_HAT_BACK = 9,
    BARBER_TOPIC_CLAIMED = 10,
    BARBER_TOPIC_CUT_TODAY = 11, /* to 13 */
    BARBER_TOPIC_NONE = 14,
    BARBER_TOPICS = 14 /* the lines of the table (BARBER_TOPIC_NONE has none) */
};

/* Its talk scene (0xc0 bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h). */
typedef struct BarberTalk {
    SceneBase base;       /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];      /* 0x80: the scene's commands (scene_command.h) */
    u32 topic;            /* 0xb0: enum BarberTopic */
    struct Barber *owner; /* 0xb4 */
    u8 other_styles;      /* 0xb8: the styles offered are the other set's (line 0x17) */
    u8 pages;             /* 0xb9: the pages of the cut's last line gone on in the window */
    u8 style;             /* 0xba: the hair style picked */
    u8 colour;            /* 0xbb: the hair colour picked */
    u8 old_style;         /* 0xbc: the player's hair style when the cut was paid for */
    u8 old_colour;        /* 0xbd: and its colour */
    u8 unk_be[2];         /* 0xbe */
} BarberTalk;

/* What the talk starts with (its slot 0x78): the message file and the line. */
typedef struct BarberTalkStart {
    const char *name;
    u8 message;
    u8 unk_05[3];
} BarberTalkStart;

/* The class (barber_talk.c). */
void *BarberTalk_Destruct(void *talk);
BarberTalk *BarberTalk_DestructDelete(BarberTalk *talk);
void *BarberTalk_Construct(void *talk);
void BarberTalk_Begin(BarberTalk *talk, struct Barber *owner);
u32 BarberTalk_Topic(BarberTalk *talk);
void BarberTalk_SetTopic(BarberTalk *talk, u32 topic);
u8 BarberTalk_Colour(BarberTalk *talk);
u8 BarberTalk_Style(BarberTalk *talk);

/* Its lines and answers (barber_talk.c). */
int BarberTalk_ChairLine(void *unused);
void BarberTalk_OnAnswer(BarberTalk *talk);
void BarberTalk_OnLineEnded(BarberTalk *talk);
void BarberTalk_OnClose(BarberTalk *talk);
void BarberTalk_OnGoOn(BarberTalk *talk);
void BarberTalk_Line(BarberTalk *talk, BarberTalkStart *out);

#endif
