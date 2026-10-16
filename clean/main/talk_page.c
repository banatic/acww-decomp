/* The page a talk's window shows, and the handlers of its measurer (talk_page.h).
 *
 * REQUIRES: the page at a word-aligned address, as every object of the game is. */
#include "talk_page.h"

#include "clean.h"
#include "label_box.h"
#include "mail_text.h"
#include "message_tag.h"
#include "message_walker.h"
#include "text_codes.h"
#include "text_draw.h"

static_assert(offsetof(TalkPage, used) == 0x400, "page used");
static_assert(offsetof(TalkPage, lines) == 0x410, "page lines");
static_assert(offsetof(TalkPage, box) == 0x420, "page box");
static_assert(offsetof(TalkPage, dirty) == 0x438, "page dirty");
static_assert(offsetof(TalkPage, centred) == 0x43b, "page centred");
static_assert(offsetof(TalkPage, measurer) == 0x43c, "page measurer");
static_assert(sizeof(TalkPage) == 0x490, "page");
static_assert(offsetof(TalkPageMeasurer, talk) == 0x2c, "measurer talk");
static_assert(offsetof(TalkPageMeasurer, tag) == 0x34, "measurer tag");
static_assert(offsetof(TalkPageMeasurer, return_at) == 0x48, "measurer return_at");
static_assert(sizeof(TalkPageMeasurer) == 0x54, "measurer");

/* The boxes of the lines: their first tiles, size and colours. */
#define TALK_PAGE_FIRST_TILE 0x11
#define TALK_PAGE_TILES_PER_LINE 0x28
#define TALK_PAGE_BOX_CELLS 0x14
#define TALK_PAGE_BOX_ROWS 2
#define TALK_PAGE_BOX_BACKGROUND 0x0e

/* The parts of the talk the measurer reads. */
#define TALK_PAGE_TALK_NAMES 0x18ac /* four names (text objects of 0x5c bytes) */
#define TALK_PAGE_TALK_NAME_SIZE 0x5c
#define TALK_PAGE_TALK_PARTICLES 0x1a58 /* MailTextParticles */

/* The first Hangul syllable, the finals per syllable, and the final rieul. */
#define TALK_PAGE_HANGUL_FIRST 0xac00
#define TALK_PAGE_HANGUL_FINALS 28
#define TALK_PAGE_FINAL_RIEUL 8
/* The particle "(eu)ro", which follows a final rieul in its after-vowel form. */
#define TALK_PAGE_PARTICLE_RO 6

extern void MI_CpuFill8(void *dst, int value, unsigned int size);

/* The box colour of a line colour: 9 as 2, then plus one. */
extern unsigned char func_02068bc8(int colour);
/* The measurer measures `characters` centred in its box: the line's start in pixels (0 when
 * `centred` is 0 or it has no box). */
extern u32 func_0206d56c(TalkPageMeasurer *measurer, int characters, int centred);
/* The measurer built for `talk`, and destroyed. */
extern void *func_0206d5e4(TalkPageMeasurer *measurer, u8 *talk);
extern void *func_0206d5c0(TalkPageMeasurer *measurer);
/* Empty: a name of the talk met by the measurer. */
extern void func_0206d420(void *measurer, void *name);
/* 1 when the setting func_0203d4a8 reads is off: the characters after a 0xff/2 tag are shown,
 * else the tag's own text. */
extern int func_02068114(void);

/* func_0206c038: the line being written marked for drawing. */
void TalkPage_MarkLine(TalkPage *page)
{
    u32 lines = page->lines;
    if (lines != 0 && lines <= TALK_PAGE_LINES) {
        page->dirty[lines - 1] = 1;
    }
}
CLEAN_AS(func_0206c038, TalkPage_MarkLine)

/* func_0206c058: nothing. */
void TalkPage_Nothing(void) {}
CLEAN_AS(func_0206c058, TalkPage_Nothing)

/* The word at `offset` in the page: the loops below index the page's arrays by the line count
 * as the ROM does, whatever it is. */
static u32 *talk_page_word(TalkPage *page, u32 offset)
{
    return (u32 *) (void *) ((u8 *) page + offset);
}

/* func_0206c05c: each marked line handed to its box (its start, its colour, where it starts
 * in the box) and redrawn; the box of the line after the last begun told where the text so far
 * ends. */
void TalkPage_Update(TalkPage *page)
{
    for (u32 i = 0; i < page->lines; i++) {
        TextDrawBox *box = (TextDrawBox *) (uintptr_t) *talk_page_word(page, offsetof(TalkPage, box) + 4 * i);
        u8 *dirty = (u8 *) page + offsetof(TalkPage, dirty) + i;
        if (box == NULL || *dirty == 0) {
            continue;
        }
        box->text = (const char *) (uintptr_t) *talk_page_word(page, offsetof(TalkPage, line_start) + 4 * i);
        box->unk_14 = 0;
        box->offset = *talk_page_word(page, offsetof(TalkPage, offset) + 4 * i);
        box->color = func_02068bc8((int) *talk_page_word(page, offsetof(TalkPage, colour) + 4 * i));
        TextDraw_RequestDraw(box);
        *dirty = 0;
    }
    if (page->lines < TALK_PAGE_LINES) {
        LabelBox *next = page->box[page->lines];
        if (next != NULL) {
            next->base.unk_14 = (u32) (uintptr_t) page + page->used;
        }
    }
}
CLEAN_AS(func_0206c05c, TalkPage_Update)

/* func_0206c0f0: each box asked to clear, and left without a text. */
void TalkPage_ClearBoxes(TalkPage *page)
{
    for (u32 i = 0; i < TALK_PAGE_LINES; i++) {
        LabelBox *box = page->box[i];
        if (box != NULL) {
            TextDraw_RequestClear(&box->base, 0);
            box->base.text = NULL;
        }
    }
}
CLEAN_AS(func_0206c0f0, TalkPage_ClearBoxes)

/* func_0206c124: the boxes freed. */
void TalkPage_FreeBoxes(TalkPage *page)
{
    for (u32 i = 0; i < TALK_PAGE_LINES; i++) {
        if (page->box[i] != NULL) {
            LabelBox_Free(page->box[i]);
            page->box[i] = NULL;
        }
    }
}
CLEAN_AS(func_0206c124, TalkPage_FreeBoxes)

/* func_0206c154: a box per line in VRAM, drawn at once onto the main screen with background 14,
 * and cleared (a box that could not be made is not kept). */
void TalkPage_NewBoxes(TalkPage *page)
{
    for (u32 i = 0; i < TALK_PAGE_LINES; i++) {
        LabelBox *box = LabelBox_NewInVram((int) (TALK_PAGE_FIRST_TILE + i * TALK_PAGE_TILES_PER_LINE), TALK_PAGE_BOX_CELLS,
                                           TALK_PAGE_BOX_ROWS);
        if (box != NULL) {
            page->box[i] = box;
            box->base.screens = TEXT_DRAW_TO_MAIN;
            box->base.background = TALK_PAGE_BOX_BACKGROUND;
            TextDraw_RequestClear(&box->base, 0);
        }
    }
}
CLEAN_AS(func_0206c154, TalkPage_NewBoxes)

/* func_0206c19c */
void TalkPage_SetCentred(TalkPage *page, unsigned char centred)
{
    page->centred = centred;
}
CLEAN_AS(func_0206c19c, TalkPage_SetCentred)

/* func_0206c1a8: the colour of the lines not begun yet. */
void TalkPage_SetColourOfNewLines(TalkPage *page, int colour)
{
    for (u32 i = page->lines; i < TALK_PAGE_LINES; i++) {
        page->colour[i] = (u32) colour;
    }
}
CLEAN_AS(func_0206c1a8, TalkPage_SetColourOfNewLines)

/* func_0206c1cc: a line begun where the text so far ends, unless there are three; its start in
 * its box measured from `position` (the message's characters it shows). */
void TalkPage_BeginLine(TalkPage *page, int position)
{
    if (page->lines >= TALK_PAGE_LINES) {
        return;
    }
    page->offset[page->lines] = func_0206d56c(&page->measurer, position, page->centred);
    u32 line = page->lines;
    page->lines = line + 1;
    page->line_start[line] = (u32) (uintptr_t) page + page->used;
}
CLEAN_AS(func_0206c1cc, TalkPage_BeginLine)

/* func_0206c224: the tag's bytes (its head included) put into the text. */
void TalkPage_PutTag(TalkPage *page, MessageTag *tag)
{
    TalkPage_PutBytes(page, (const char *) tag->start, tag->size + 6);
}
CLEAN_AS(func_0206c224, TalkPage_PutTag)

/* func_0206c234: a 16-bit character put into the text, low byte first, when more than two bytes
 * are left; whether it was. The line is marked.
 * The used count is stepped before each byte is written and read again after, as the ROM
 * does: they overlap only for a count the game never has. */
int TalkPage_PutChar(TalkPage *page, int character)
{
    s32 at = (s32) page->used;
    if ((u32) (TALK_PAGE_TEXT_SIZE - at) <= 2) {
        return 0;
    }
    page->used++;
    *((u8 *) page + at) = (u8) character;
    at = (s32) page->used;
    page->used = (u32) at + 1;
    *((u8 *) page + at) = (u8) (character >> 8);
    TalkPage_MarkLine(page);
    return 1;
}
CLEAN_AS(func_0206c234, TalkPage_PutChar)

/* func_0206c278: `count` bytes put into the text when more than that are left; whether they
 * were. The line is marked. */
int TalkPage_PutBytes(TalkPage *page, const char *bytes, unsigned int count)
{
    if (TALK_PAGE_TEXT_SIZE - page->used <= count) {
        return 0;
    }
    for (u32 i = 0; i < count; i++) {
        *((u8 *) page + page->used + i) = (u8) bytes[i];
    }
    page->used += count;
    TalkPage_MarkLine(page);
    return 1;
}
CLEAN_AS(func_0206c278, TalkPage_PutBytes)

/* func_0206c2c4: the colour of every line. */
void TalkPage_SetColours(TalkPage *page, int colour)
{
    for (u32 i = 0; i < TALK_PAGE_LINES; i++) {
        page->colour[i] = (u32) colour;
    }
}
CLEAN_AS(func_0206c2c4, TalkPage_SetColours)

/* func_0206c2e4: the page emptied, its lines in `colour`. */
void TalkPage_Clear(TalkPage *page, int colour)
{
    page->used = 0;
    MI_CpuFill8(page->text, 0, TALK_PAGE_TEXT_SIZE);
    for (u32 i = 0; i < TALK_PAGE_LINES; i++) {
        page->line_start[i] = 0;
        page->dirty[i] = 0;
        page->offset[i] = 0;
    }
    page->lines = 0;
    TalkPage_SetColours(page, colour);
}
CLEAN_AS(func_0206c2e4, TalkPage_Clear)

/* func_0206c340: emptied, its lines in colour 0. */
void TalkPage_ClearPlain(TalkPage *page)
{
    TalkPage_Clear(page, 0);
}
CLEAN_AS(func_0206c340, TalkPage_ClearPlain)

/* func_0206c34c */
TalkPage *TalkPage_Destruct(TalkPage *page)
{
    TalkPage_FreeBoxes(page);
    func_0206d5c0(&page->measurer);
    return page;
}
CLEAN_AS(func_0206c34c, TalkPage_Destruct)

/* func_0206c368: an empty page of `talk`, not centred, without boxes. */
TalkPage *TalkPage_Construct(TalkPage *page, u8 *talk)
{
    page->used = 0;
    page->lines = 0;
    page->centred = 0;
    func_0206d5e4(&page->measurer, talk);
    TalkPage_ClearPlain(page);
    for (u32 i = 0; i < TALK_PAGE_LINES; i++) {
        page->box[i] = NULL;
    }
    return page;
}
CLEAN_AS(func_0206c368, TalkPage_Construct)

/* ---- The measurer's handlers */

/* func_0206c3b8 (tag 0xff/2): when the setting shows the tag's own text, the characters after
 * the tag (as many as its first parameter) are skipped and the tag's text walked in their place,
 * up to the end its parameters give. */
void TalkPageMeasurer_AltText(TalkPageMeasurer *measurer)
{
    u32 count;
    s32 end;
    const s8 *text;
    MessageTag_SplitParams(&measurer->tag, &count, &end, &text);
    if (func_02068114() == 0) {
        u32 start = (u32) (uintptr_t) text;
        MessageWalker_Skip(&measurer->walker.base, (int) (count << 1));
        MessageWalker_Enter(&measurer->walker.base, (int) start);
        /* QUIRK: the end is the text plus (end - text) with its lowest bit flipped. */
        measurer->return_at = start + (((u32) end - start) ^ 1);
    }
}
CLEAN_AS(func_0206c3b8, TalkPageMeasurer_AltText)

/* func_0206c3fc (a particle tag): the particle the tag's first byte names (counted from 1)
 * walked in its form after a vowel or after a consonant, by the talk's last syllable: after a
 * vowel when there is none or it has no final; a final rieul takes "(eu)ro" in its after-vowel
 * form when the talk's ro_after_rieul is 1. */
void TalkPageMeasurer_PutParticle(TalkPageMeasurer *measurer)
{
    u8 particle;
    TextParticle *text;
    MessageTag_GetFirstByte(&measurer->tag, &particle);
    particle--;
    MailTextParticles *particles = (MailTextParticles *) (void *) (measurer->talk + TALK_PAGE_TALK_PARTICLES);
    u32 ro_after_rieul = (u32) particles->ro_after_rieul;
    u32 last = (u32) particles->last_syllable;
    s32 final = (s32) (last - TALK_PAGE_HANGUL_FIRST) % TALK_PAGE_HANGUL_FINALS;
    if (last == 0 || final == 0) {
        text = TextCodes_ParticleAfterVowel(particle);
    } else if (ro_after_rieul == 1 && particle == TALK_PAGE_PARTICLE_RO && final == TALK_PAGE_FINAL_RIEUL) {
        text = TextCodes_ParticleAfterVowel(particle);
    } else {
        text = TextCodes_ParticleAfterConsonant(particle);
    }
    MessageWalker_Enter(&measurer->walker.base, (int) (uintptr_t) text);
}
CLEAN_AS(func_0206c3fc, TalkPageMeasurer_PutParticle)

/* The talk's name `index` handed to the empty func_0206d420. */
static void talk_page_measurer_name(TalkPageMeasurer *measurer, int index)
{
    func_0206d420(measurer, measurer->talk + TALK_PAGE_TALK_NAMES + index * TALK_PAGE_TALK_NAME_SIZE);
}

/* func_0206c480: name 3. */
void TalkPageMeasurer_Name3(TalkPageMeasurer *measurer)
{
    talk_page_measurer_name(measurer, 3);
}
CLEAN_AS(func_0206c480, TalkPageMeasurer_Name3)

/* func_0206c49c: name 2. */
void TalkPageMeasurer_Name2(TalkPageMeasurer *measurer)
{
    talk_page_measurer_name(measurer, 2);
}
CLEAN_AS(func_0206c49c, TalkPageMeasurer_Name2)

/* func_0206c4b0: name 1. */
void TalkPageMeasurer_Name1(TalkPageMeasurer *measurer)
{
    talk_page_measurer_name(measurer, 1);
}
CLEAN_AS(func_0206c4b0, TalkPageMeasurer_Name1)

/* func_0206c4c4: name 0. */
void TalkPageMeasurer_Name0(TalkPageMeasurer *measurer)
{
    talk_page_measurer_name(measurer, 0);
}
CLEAN_AS(func_0206c4c4, TalkPageMeasurer_Name0)
