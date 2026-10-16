/* A span of a talk's text walked beside the talk's own walk (talk_span.h). */
#include "talk_span.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "message_walker.h"
#include "talk_page.h"
#include "text_walker.h"

static_assert(offsetof(TalkSpan, talk) == 0x24, "span talk");
static_assert(offsetof(TalkSpan, mode) == 0x2c, "span mode");
static_assert(offsetof(TalkSpan, stepping) == 0x38, "span stepping");
static_assert(offsetof(TalkSpan, to_page) == 0x39, "span to_page");
static_assert(sizeof(TalkSpan) == 0x3c, "span");

/* The vtables of this class and of its base class. */
extern const u8 data_020def9c[];
extern const u8 data_020e3e68[];

/* The character pushed onto the talk's last characters (the talk's 0x1a2c). */
extern void func_02068104(u8 *talk, int character);

/* func_0206be6c: the span stopped and its walk cleared. */
void TalkSpan_Reset(TalkSpan *span)
{
    span->mode = TALK_SPAN_IDLE;
    span->end = 0;
    span->left = 0;
    span->stepping = 0;
    span->to_page = 0;
    MessageWalker_Reset(&span->base);
}
CLEAN_AS(func_0206be6c, TalkSpan_Reset)

/* func_0206be88 (slot 6): go on while the step has not handed its character yet. */
unsigned char TalkSpan_WantsMore(TalkSpan *span)
{
    return span->stepping;
}
CLEAN_AS(func_0206be88, TalkSpan_WantsMore)

/* func_0206be90 (slot 5): a tag: nothing. */
void TalkSpan_OnTag(void) {}
CLEAN_AS(func_0206be90, TalkSpan_OnTag)

/* func_0206be94 (slot 4): a character: put into the page when the span shows, then counted
 * (a counted span stops after its last) or, for a span up to an address, pushed onto the
 * talk's last characters. */
void TalkSpan_OnCharacter(TalkSpan *span, int character)
{
    if (span->to_page != 0) {
        TalkPage_PutChar(span->page, character);
    }
    span->stepping = 0;
    if (span->mode == TALK_SPAN_COUNTED) {
        span->left--;
        if (span->left <= 0) {
            TalkSpan_Reset(span);
        }
    } else if (span->mode == TALK_SPAN_TO_END) {
        func_02068104(span->talk, character);
    }
}
CLEAN_AS(func_0206be94, TalkSpan_OnCharacter)

/* func_0206bee0 (slot 3): the end: a span up to an address stops. */
void TalkSpan_OnEnd(TalkSpan *span)
{
    if (span->mode == TALK_SPAN_TO_END) {
        TalkSpan_Reset(span);
    }
}
CLEAN_AS(func_0206bee0, TalkSpan_OnEnd)

/* func_0206bef4 (slot 2): the text was set: nothing. */
void TalkSpan_OnText(void) {}
CLEAN_AS(func_0206bef4, TalkSpan_OnText)

/* func_0206bef8: whether the span is stopped. */
int TalkSpan_IsIdle(TalkSpan *span)
{
    return span->mode == TALK_SPAN_IDLE;
}
CLEAN_AS(func_0206bef8, TalkSpan_IsIdle)

/* func_0206bf08: the span walked until it hands one character (or ends). */
void TalkSpan_Step(TalkSpan *span)
{
    if (span->mode == TALK_SPAN_COUNTED) {
        span->stepping = 1;
        TextWalker_Run(&span->base, 0);
    } else if (span->mode == TALK_SPAN_TO_END) {
        span->stepping = 1;
        TextWalker_Run(&span->base, (int) span->end);
    }
}
CLEAN_AS(func_0206bf08, TalkSpan_Step)

/* func_0206bf3c: the span started at `start` to stop at `end`, when the end is after the
 * start; `to_page`: its characters also go into the page. */
void TalkSpan_StartRange(TalkSpan *span, unsigned int start, unsigned int end, int to_page)
{
    if (end > start) {
        MessageWalker_Reset(&span->base);
        MessageWalker_Start(&span->base, (int) start);
        span->end = end;
        span->left = 0;
        span->to_page = (u8) to_page;
        span->stepping = 0;
        span->mode = TALK_SPAN_TO_END;
    }
}
CLEAN_AS(func_0206bf3c, TalkSpan_StartRange)

/* func_0206bf78: the span started at `start` for `count` characters, when there are any. */
void TalkSpan_StartCounted(TalkSpan *span, int start, int count, unsigned char to_page)
{
    if (count > 0) {
        MessageWalker_Reset(&span->base);
        MessageWalker_Start(&span->base, start);
        span->end = 0;
        span->left = count;
        span->to_page = to_page;
        span->stepping = 0;
        span->mode = TALK_SPAN_COUNTED;
    }
}
CLEAN_AS(func_0206bf78, TalkSpan_StartCounted)

/* func_0206bfb4 (vtable slot 1): destroyed and freed. */
void *TalkSpan_Delete(void *span)
{
    ((TalkSpan *) span)->base.vtable = data_020e3e68;
    MessageWalker_BaseDestruct(span);
    Heap_OperatorDeleteB(span);
    return span;
}
CLEAN_AS(func_0206bfb4, TalkSpan_Delete)

/* func_0206bfdc (vtable slot 0) */
void *TalkSpan_Destruct(void *span)
{
    ((TalkSpan *) span)->base.vtable = data_020e3e68;
    MessageWalker_BaseDestruct(span);
    return span;
}
CLEAN_AS(func_0206bfdc, TalkSpan_Destruct)

/* func_0206bffc: an idle span of `talk`, writing into `page`. */
TalkSpan *TalkSpan_Construct(TalkSpan *span, u8 *talk, TalkPage *page)
{
    MessageWalker_Construct(&span->base);
    span->base.vtable = data_020def9c;
    span->talk = talk;
    span->page = page;
    span->mode = TALK_SPAN_IDLE;
    span->end = 0;
    span->left = 0;
    span->stepping = 0;
    span->to_page = 0;
    return span;
}
CLEAN_AS(func_0206bffc, TalkSpan_Construct)
