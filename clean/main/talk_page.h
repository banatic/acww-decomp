/* The page a talk's window shows (0x490 bytes, at the talk's 0x684; func_0206c368 builds it):
 * the message text walked so far, kept as bytes (each 16-bit character low byte first, and the
 * colour tags whole), and up to three lines, each drawn by a label box of its own
 * (label_box.h) drawn into the main screen's tiles from 0x11, 0x39 and 0x61, 20 tiles wide and
 * 2 high.
 *
 * The talk's tag walker (talk_tags.h) puts the characters in (TalkPage_PutChar) and begins a
 * line at each newline (TalkPage_BeginLine); a line written to is marked, and each frame the
 * marked lines are handed to their boxes and redrawn (TalkPage_Update). A line can be
 * centred: then its start in the box is measured with the measurer at 0x43c (class
 * data_020def7c, a text walker set as the walker of a box of its own, which handles the tags a
 * line may hold the way the talk shows them). */
#ifndef CLEAN_MAIN_TALK_PAGE_H
#define CLEAN_MAIN_TALK_PAGE_H

#include "label_box.h"
#include "message_decoder.h"
#include "text_walker.h"
#include "types.h"

#define TALK_PAGE_TEXT_SIZE 0x400
#define TALK_PAGE_LINES 3

/* The measurer of the centred lines (class data_020def7c, 0x54 bytes). */
typedef struct TalkPageMeasurer {
    TextWalker walker; /* 0x00 */
    u8 *talk;          /* 0x2c: the talk (0x1e9c bytes) */
    LabelBox *box;     /* 0x30: the box it measures with */
    MessageTag tag;    /* 0x34: the tag being handled */
    u32 return_at;     /* 0x48: where a 0xff/2 tag's own text ends */
    s32 unk_4c;        /* 0x4c */
    s32 unk_50;        /* 0x50 */
} TalkPageMeasurer;

typedef struct TalkPage {
    u8 text[TALK_PAGE_TEXT_SIZE];    /* 0x000 */
    u32 used;                        /* 0x400: the bytes of `text` written */
    u32 line_start[TALK_PAGE_LINES]; /* 0x404: the address in `text` each line begins at */
    u32 lines;                       /* 0x410: the lines begun */
    u32 colour[TALK_PAGE_LINES];     /* 0x414: each line's colour (a 0xff/0 tag's) */
    LabelBox *box[TALK_PAGE_LINES];  /* 0x420: or NULL */
    u32 offset[TALK_PAGE_LINES];     /* 0x42c: where each line starts in its box, in pixels */
    u8 dirty[TALK_PAGE_LINES];       /* 0x438: the line was written to since it was drawn */
    u8 centred;                      /* 0x43b: the lines begun are centred */
    TalkPageMeasurer measurer;       /* 0x43c */
} TalkPage;

void TalkPage_MarkLine(TalkPage *page);
void TalkPage_Nothing(void);
void TalkPage_Update(TalkPage *page);
void TalkPage_ClearBoxes(TalkPage *page);
void TalkPage_FreeBoxes(TalkPage *page);
void TalkPage_NewBoxes(TalkPage *page);
void TalkPage_SetCentred(TalkPage *page, unsigned char centred);
void TalkPage_SetColourOfNewLines(TalkPage *page, int colour);
void TalkPage_BeginLine(TalkPage *page, int position);
void TalkPage_PutTag(TalkPage *page, MessageTag *tag);
int TalkPage_PutChar(TalkPage *page, int character);
int TalkPage_PutBytes(TalkPage *page, const char *bytes, unsigned int count);
void TalkPage_SetColours(TalkPage *page, int colour);
void TalkPage_Clear(TalkPage *page, int colour);
void TalkPage_ClearPlain(TalkPage *page);
TalkPage *TalkPage_Destruct(TalkPage *page);
TalkPage *TalkPage_Construct(TalkPage *page, u8 *talk);

/* The measurer's handlers of tags (the tables of func_0206cd40 and func_0206cdbc). */
void TalkPageMeasurer_AltText(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutParticle(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Name3(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Name2(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Name1(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Name0(TalkPageMeasurer *measurer);

/* ---- The rest of the measurer's handlers, and its tables of them by the tag's kind. The
 * measurer walks the texts the talk's tag walker (talk_tags.h) walks in place of a tag, without
 * the colour tags around names, so that a centred line is measured as it will be shown. Its
 * table by group (func_0206d330) holds group 0 (func_0206d26c), group 1
 * (TalkPageMeasurer_DispatchGroup1), group 2 (TalkPageMeasurer_SkipTexts), group 4
 * (TalkPageMeasurer_DispatchGroup4), group 11 (TalkPageMeasurer_DispatchGroup11) and group 0xff
 * (TalkPageMeasurer_DispatchGroupFF). */

/* Group 11. */
void TalkPageMeasurer_Part10(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Part9(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Part8(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Part7(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Part6(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Part5(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Part4(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Part3(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Part2(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Part1(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Part0(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Nothing11_4(void);
void TalkPageMeasurer_Set50Two(TalkPageMeasurer *measurer);
void TalkPageMeasurer_Set50One(TalkPageMeasurer *measurer);

/* Group 4. */
void TalkPageMeasurer_PutBoom(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPraise(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutNickname(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutImpression(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutName3(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutName2(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutName1(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutName0(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPart10(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPart9(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPart8(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPart7(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPart6(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPart5(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPart4(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPart3(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPart2(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPart1(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPart0(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutOtherPlayer(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutRandomNpc(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutDislikedNpc(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutLikedNpc(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutSecond(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutMinute(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutHour12(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutWeekday(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutDay(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutMonth(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutYear(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutTownName(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutCatchphrase(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutReceiverName(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPlayerName(TalkPageMeasurer *measurer);

/* Group 1. */
void TalkPageMeasurer_RememberedEnd(void);
void TalkPageMeasurer_RememberedText(TalkPageMeasurer *measurer);

/* Group 0. */
void TalkPageMeasurer_PutLeftBrace(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutPercent(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutAmpersand(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutSlash(TalkPageMeasurer *measurer);
void TalkPageMeasurer_PutAsterisk(TalkPageMeasurer *measurer);

/* The tables by kind, and group 2. */
void TalkPageMeasurer_DispatchGroupFF(TalkPageMeasurer *measurer);
void TalkPageMeasurer_DispatchGroup11(TalkPageMeasurer *measurer);
void TalkPageMeasurer_DispatchGroup4(TalkPageMeasurer *measurer);
void TalkPageMeasurer_SkipTexts(TalkPageMeasurer *measurer);
void TalkPageMeasurer_DispatchGroup1(TalkPageMeasurer *measurer);

#endif
