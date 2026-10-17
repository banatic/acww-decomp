/* The faceless cat's talk scene (mystery_cat.h: MysteryCatTalk, vtable 0x02279bd8).
 *
 * Its vtable slots, beyond the scene base's: 0x00 and 0x04 its destructors, 0x14 a line ended
 * (MysteryCatTalk_OnLineEnded), 0x18 the player's answer (MysteryCatTalk_OnAnswer), 0x78 the
 * line the talk starts with (MysteryCatTalk_Line) and 0x84 a command of the scene ended
 * (MysteryCatTalk_RunAfter: the function the scene keeps at 0xb4 runs once).
 *
 * Its lines, of "sp_npc_mysterycat" (MYSTERY_CAT_LINE_*), as the code reads them: she asks
 * (line 3) while the daily bit 0x2b is clear, and on one talk in two when it is set; else she
 * thanks the one who drew her face (0x18 to 0x1b) or anyone else (0x11 to 0x14), naming the
 * face's maker, the maker's town, the impression she imitates ("st_impress") and the face's
 * title. Answered at line 3, the first answer leads to 0x0a when the player drew her face, else
 * 0x09; the second to 0x0c or 0x0b; each of those then to 0x0d, whose second answer leads to
 * 0x0e. Once 0x0e ends, the design screen (mode 3) opens; then line 0x1c when the player gave
 * a design (her face shown again), else 0x0f. Once 0x1c ends, screen mode 0x14 opens; once the
 * player confirms, she takes an impression of the player (VillagerImpression_Pick), the town's
 * record is marked to be sent, the daily bit 0x2b is set and one of the lines 5 to 7 follows. */
#ifndef CLEAN_OV074_MYSTERY_CAT_TALK_H
#define CLEAN_OV074_MYSTERY_CAT_TALK_H

#include "mystery_cat.h"
#include "types.h"

/* The lines of "sp_npc_mysterycat". */
#define MYSTERY_CAT_LINE_THANKS 0x05       /* 0x05 to 0x07, after the impression was taken */
#define MYSTERY_CAT_LINE_ASK 0x03          /* the line the talk starts with when she asks */
#define MYSTERY_CAT_LINE_OTHER_FIRST 0x09  /* the first answer, the face not the player's */
#define MYSTERY_CAT_LINE_OWN_FIRST 0x0a    /* the first answer, the player drew the face */
#define MYSTERY_CAT_LINE_OTHER_SECOND 0x0b /* the second answer, the face not the player's */
#define MYSTERY_CAT_LINE_OWN_SECOND 0x0c   /* the second answer, the player drew the face */
#define MYSTERY_CAT_LINE_ASK_AGAIN 0x0d    /* after 0x09 to 0x0c */
#define MYSTERY_CAT_LINE_DRAW 0x0e         /* ends with the design screen */
#define MYSTERY_CAT_LINE_NO_DESIGN 0x0f    /* no design given */
#define MYSTERY_CAT_LINE_SHOWN_OTHER 0x11  /* 0x11 to 0x14: the face not the player's */
#define MYSTERY_CAT_LINE_SHOWN_OWN 0x18    /* 0x18 to 0x1b: the player drew the face */
#define MYSTERY_CAT_LINE_NEW_FACE 0x1c     /* a design given; ends with screen mode 0x14 */

/* What its line function gives: the message file's name (an address) and the message. */
typedef struct MysteryCatLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} MysteryCatLine;

void MysteryCatTalk_OnAnswer(MysteryCatTalk *talk);
void MysteryCatTalk_OnLineEnded(MysteryCatTalk *talk);
void MysteryCatTalk_Line(MysteryCatTalk *talk, MysteryCatLine *out);
void MysteryCatTalk_Begin(MysteryCatTalk *talk, MysteryCat *owner);
void *MysteryCatTalk_Delete(void *talk);
void *MysteryCatTalk_Destroy(void *talk);
void *MysteryCatTalk_Construct(void *talk);
void MysteryCatTalk_TakeImpression(MysteryCatTalk *talk);
void MysteryCatTalk_TakeDesign(MysteryCatTalk *talk);
void MysteryCatTalk_SetAfter(MysteryCatTalk *talk, int which);
void MysteryCatTalk_RunAfter(MysteryCatTalk *talk);

#endif
