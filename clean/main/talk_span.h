/* A span of a talk's text walked one character at a time beside the talk's own walk (class
 * data_020def9c, 0x3c bytes; the talk's tag walker holds two, talk_tags.h).
 *
 * A 0xff/2 tag carries a text of its own that may stand in for the characters after it. The
 * talk's walker starts one span on those characters (TalkSpan_StartCounted: so many of them)
 * and one on the tag's own text (TalkSpan_StartRange: up to an address); a setting of the game
 * picks which of the two also goes into the window's page (talk_page.h). Each time the talk
 * shows a character, it steps both spans (TalkSpan_Step): each walks until it has handed one
 * character, which slot 6 (TalkSpan_WantsMore) sees by the flag the character clears.
 *
 * Its vtable after the base class's (message_walker.h): the destructor, the deleting
 * destructor, slots 2 (the text was set: nothing), 3 (the end), 4 (a character), 5 (a tag:
 * nothing) and 6 (whether to go on). */
#ifndef CLEAN_MAIN_TALK_SPAN_H
#define CLEAN_MAIN_TALK_SPAN_H

#include "message_cursor.h"
#include "talk_page.h"
#include "types.h"

/* How a span ends (TalkSpan.mode). */
enum TalkSpanMode {
    TALK_SPAN_IDLE = 0,
    TALK_SPAN_COUNTED = 1, /* after `left` characters */
    TALK_SPAN_TO_END = 2,  /* at the address `end`; its characters also go to the talk */
};

typedef struct TalkSpan {
    MessageWalker base; /* 0x00 */
    u8 *talk;           /* 0x24: the talk (0x1e9c bytes) */
    TalkPage *page;     /* 0x28: the page of the talk's window */
    s32 mode;           /* 0x2c: enum TalkSpanMode */
    u32 end;            /* 0x30: TALK_SPAN_TO_END: where the span stops */
    s32 left;           /* 0x34: TALK_SPAN_COUNTED: the characters still to walk */
    u8 stepping;        /* 0x38: set by a step, cleared by the character it hands */
    u8 to_page;         /* 0x39: the characters also go into the page */
    u8 unk_3a[2];
} TalkSpan;

void TalkSpan_Reset(TalkSpan *span);
unsigned char TalkSpan_WantsMore(TalkSpan *span);
void TalkSpan_OnTag(void);
void TalkSpan_OnCharacter(TalkSpan *span, int character);
void TalkSpan_OnEnd(TalkSpan *span);
void TalkSpan_OnText(void);
int TalkSpan_IsIdle(TalkSpan *span);
void TalkSpan_Step(TalkSpan *span);
void TalkSpan_StartRange(TalkSpan *span, unsigned int start, unsigned int end, int to_page);
void TalkSpan_StartCounted(TalkSpan *span, int start, int count, unsigned char to_page);
void *TalkSpan_Delete(void *span);
void *TalkSpan_Destruct(void *span);
TalkSpan *TalkSpan_Construct(TalkSpan *span, u8 *talk, TalkPage *page);

#endif
