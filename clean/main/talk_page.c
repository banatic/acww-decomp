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

/* ---- The rest of the measurer's handlers, and its tables by kind */

#include "mail_particles.h"
#include "message_query.h"
#include "ov004/member_pointer.h"

/* The parts of the talk the handlers below read. */
#define TALK_PAGE_TALK_RECEIVER 0x14a8 /* the receiver (Base_02066994) */
#define TALK_PAGE_TALK_PARTS 0x14b8    /* eleven parts (text objects of 0x5c bytes), then the names */
#define TALK_PAGE_TALK_PART_SIZE 0x5c
#define TALK_PAGE_TALK_CATCHPHRASE 0x1c70  /* the villager's catchphrase (func_02067a74) */
#define TALK_PAGE_TALK_TOWN_NAME 0x1c8c    /* the town's name (func_02067a3c) */
#define TALK_PAGE_TALK_PLAYER_NAME 0x1cac  /* this system's player's name (func_020679fc) */
#define TALK_PAGE_TALK_LIKED_NPC 0x1ccc    /* (func_020679b0) */
#define TALK_PAGE_TALK_DISLIKED_NPC 0x1cec /* (func_02067964) */
#define TALK_PAGE_TALK_RANDOM_NPC 0x1d0c   /* (func_020678f8) */
#define TALK_PAGE_TALK_OTHER_PLAYER 0x1d2c /* another resident's player name (func_0206786c) */
#define TALK_PAGE_TALK_BOOM 0x1d4c         /* (func_0206781c) */
#define TALK_PAGE_TALK_IMPRESSION 0x1da8   /* (func_020677d0) */
#define TALK_PAGE_TALK_NICKNAME 0x1e04     /* (func_0206777c) */
#define TALK_PAGE_TALK_PRAISE 0x1e24       /* (func_02067728) */
#define TALK_PAGE_TALK_REMEMBERED 0x1e4c   /* the text the villager remembers of the player (func_020676d0) */

/* The vtable slot of a text object that answers its characters. */
#define TALK_PAGE_SLOT_CHARACTERS 0x0c

/* The tag that ends the text a tag 1/6 may replace. */
#define TALK_PAGE_REMEMBERED_END_GROUP 1
#define TALK_PAGE_REMEMBERED_END_KIND 7

/* The texts of the villager (and of the players and the town) loaded into the talk: 0 when
 * they could not be (the measurer does not look). */
extern int func_0206781c(u8 *talk);
extern int func_02067728(u8 *talk);
extern int func_0206777c(u8 *talk);
extern int func_020677d0(u8 *talk);
extern int func_0206786c(u8 *talk);
extern int func_020678f8(u8 *talk);
extern int func_02067964(u8 *talk);
extern int func_020679b0(u8 *talk);
extern int func_02067a3c(u8 *talk);
extern int func_02067a74(u8 *talk);
extern int func_020679fc(u8 *talk);
extern int func_020676d0(u8 *talk);
/* The talk's texts of the date and time it began, each set and answered by these: the second,
 * the minute, the hour on a 12-hour clock, the weekday's name, the day, the month and the
 * year. */
extern void *func_02067f74(u8 *talk);
extern void *func_02067fa4(u8 *talk);
extern void *func_02067fd4(u8 *talk);
extern void *func_02068010(u8 *talk);
extern void *func_02068034(u8 *talk);
extern void *func_02068058(u8 *talk);
extern void *func_0206807c(u8 *talk);
/* The text of the receiver's name (the receiver plus 0x20). */
extern void *func_020668d4(void *receiver);
/* The talk's name `index` (0 to 3) and its part `index` (0 to 10) walked by the measurer. */
extern void func_0206d428(TalkPageMeasurer *measurer, int index);
extern void func_0206d484(TalkPageMeasurer *measurer, int index);
/* Empty (tag 11/4). */
extern void func_0206d424(void);

/* The tables of the handlers (function-local statics of the game, filled on the first call):
 * the guard, the table, and the constants it is filled from. */
extern const MemberPointer __ptmf_null;
extern u32 data_021cda84;
extern MemberPointer data_021cdaa4[3];
extern const MemberPointer data_020dedac;
extern u32 data_021cda4c;
extern MemberPointer data_021cdf74[21];
extern const MemberPointer data_020dee04, data_020dee0c, data_020dee14, data_020dee24, data_020dee2c, data_020dee3c,
    data_020dee44, data_020dee54, data_020dee5c, data_020dee6c, data_020dee84, data_020dedfc, data_020dedf4, data_020dedec,
    data_020dede4, data_020deddc, data_020dedd4, data_020dedcc, data_020de9ec;
extern u32 data_021cda44;
extern MemberPointer data_021ce1dc[35];
extern const MemberPointer data_020deee4, data_020de8e4, data_020de834, data_020dec84, data_020dec8c, data_020deeec,
    data_020debdc, data_020de874, data_020de8ec, data_020de8f4, data_020dec24, data_020def04, data_020def14, data_020def0c,
    data_020dec44, data_020deefc, data_020deef4, data_020decbc, data_020decc4, data_020deedc, data_020deed4, data_020deecc,
    data_020decf4, data_020deebc, data_020deeb4, data_020deeac, data_020ded2c, data_020dee9c, data_020dee94, data_020ded54,
    data_020ded84, data_020dee7c, data_020dee74, data_020dedb4;
extern u32 data_021cda48;
extern MemberPointer data_021cdeec[17];
extern const MemberPointer data_020de86c, data_020deb64;

typedef int TalkPageCharactersFunction(const void *object);
typedef int TalkPageLoadFunction(u8 *talk);
typedef void *TalkPageTextFunction(u8 *talk);

static u8 *talk_page_talk_at(TalkPageMeasurer *measurer, u32 offset)
{
    return measurer->talk + offset;
}

static MailTextParticles *talk_page_particles(TalkPageMeasurer *measurer)
{
    return (MailTextParticles *) (void *) talk_page_talk_at(measurer, TALK_PAGE_TALK_PARTICLES);
}

/* The characters of a text object (its vtable's slot 3), as an address. */
static int talk_page_characters(const void *object)
{
    const u8 *vtable = *(const u8 *const *) object;
    u32 code = *(const u32 *) (const void *) (vtable + TALK_PAGE_SLOT_CHARACTERS);
    return ((TalkPageCharactersFunction *) (uintptr_t) code)(object);
}

/* The text object `text` walked in place of the tag, its last syllable kept for the particles,
 * and the particles' ro_after_rieul set to `ro_after_rieul`. The object is asked for its
 * characters twice, as the ROM does. */
static void talk_page_measurer_walk(TalkPageMeasurer *measurer, u32 text, s32 ro_after_rieul)
{
    MessageWalker_Enter(&measurer->walker.base, talk_page_characters(talk_page_talk_at(measurer, text)));
    MailParticles_TakeLastSyllable(talk_page_particles(measurer),
                                   (const char *) (uintptr_t) talk_page_characters(talk_page_talk_at(measurer, text)));
    talk_page_particles(measurer)->ro_after_rieul = ro_after_rieul;
}

/* A text `load` loads into the talk (whether it could is not looked at), walked as above. */
static void talk_page_measurer_walk_loaded(TalkPageMeasurer *measurer, TalkPageLoadFunction *load, u32 text,
                                           s32 ro_after_rieul)
{
    load(measurer->talk);
    talk_page_measurer_walk(measurer, text, ro_after_rieul);
}

/* The text `text` sets in the talk (it is set twice, as the ROM does) walked in place of the
 * tag, its last syllable kept, and ro_after_rieul set. */
static void talk_page_measurer_walk_set_text(TalkPageMeasurer *measurer, TalkPageTextFunction *text)
{
    MessageWalker_Enter(&measurer->walker.base, talk_page_characters(text(measurer->talk)));
    MailParticles_TakeLastSyllable(talk_page_particles(measurer),
                                   (const char *) (uintptr_t) talk_page_characters(text(measurer->talk)));
    talk_page_particles(measurer)->ro_after_rieul = 1;
}

/* The talk's part `index` handed to the empty func_0206d420. */
static void talk_page_measurer_part(TalkPageMeasurer *measurer, int index)
{
    func_0206d420(measurer, talk_page_talk_at(measurer, TALK_PAGE_TALK_PARTS + (u32) index * TALK_PAGE_TALK_PART_SIZE));
}

/* The handler of the tag's kind in a table (filled on the first call); a null entry does
 * nothing.
 * REQUIRES: the kind is within the table (the ROM indexes it unchecked). */
static void talk_page_measurer_dispatch(TalkPageMeasurer *measurer, u32 *guard, MemberPointer *table,
                                        const MemberPointer *const *constants, int count)
{
    MemberTable_InitOnce(guard, table, constants, count);
    MemberPointer handler = table[measurer->tag.kind];
    if (handler.function != 0) {
        MemberPointer_CallVoid(&handler, measurer);
    }
}

/* func_0206c4d8 (tag 11/15): part 10 handed to the empty func_0206d420. */
void TalkPageMeasurer_Part10(TalkPageMeasurer *measurer)
{
    talk_page_measurer_part(measurer, 10);
}
CLEAN_AS(func_0206c4d8, TalkPageMeasurer_Part10)

/* func_0206c4f4 (tag 11/14): part 9, likewise. */
void TalkPageMeasurer_Part9(TalkPageMeasurer *measurer)
{
    talk_page_measurer_part(measurer, 9);
}
CLEAN_AS(func_0206c4f4, TalkPageMeasurer_Part9)

/* func_0206c510 (tag 11/13): part 8, likewise. */
void TalkPageMeasurer_Part8(TalkPageMeasurer *measurer)
{
    talk_page_measurer_part(measurer, 8);
}
CLEAN_AS(func_0206c510, TalkPageMeasurer_Part8)

/* func_0206c52c (tag 11/12): part 7, likewise. */
void TalkPageMeasurer_Part7(TalkPageMeasurer *measurer)
{
    talk_page_measurer_part(measurer, 7);
}
CLEAN_AS(func_0206c52c, TalkPageMeasurer_Part7)

/* func_0206c548 (tag 11/11): part 6, likewise. */
void TalkPageMeasurer_Part6(TalkPageMeasurer *measurer)
{
    talk_page_measurer_part(measurer, 6);
}
CLEAN_AS(func_0206c548, TalkPageMeasurer_Part6)

/* func_0206c564 (tag 11/10): part 5, likewise. */
void TalkPageMeasurer_Part5(TalkPageMeasurer *measurer)
{
    talk_page_measurer_part(measurer, 5);
}
CLEAN_AS(func_0206c564, TalkPageMeasurer_Part5)

/* func_0206c580 (tag 11/9): part 4, likewise. */
void TalkPageMeasurer_Part4(TalkPageMeasurer *measurer)
{
    talk_page_measurer_part(measurer, 4);
}
CLEAN_AS(func_0206c580, TalkPageMeasurer_Part4)

/* func_0206c59c (tag 11/8): part 3, likewise. */
void TalkPageMeasurer_Part3(TalkPageMeasurer *measurer)
{
    talk_page_measurer_part(measurer, 3);
}
CLEAN_AS(func_0206c59c, TalkPageMeasurer_Part3)

/* func_0206c5b8 (tag 11/7): part 2, likewise. */
void TalkPageMeasurer_Part2(TalkPageMeasurer *measurer)
{
    talk_page_measurer_part(measurer, 2);
}
CLEAN_AS(func_0206c5b8, TalkPageMeasurer_Part2)

/* func_0206c5cc (tag 11/6): part 1, likewise. */
void TalkPageMeasurer_Part1(TalkPageMeasurer *measurer)
{
    talk_page_measurer_part(measurer, 1);
}
CLEAN_AS(func_0206c5cc, TalkPageMeasurer_Part1)

/* func_0206c5e0 (tag 11/5): part 0, likewise. */
void TalkPageMeasurer_Part0(TalkPageMeasurer *measurer)
{
    talk_page_measurer_part(measurer, 0);
}
CLEAN_AS(func_0206c5e0, TalkPageMeasurer_Part0)

/* func_0206c5f4 (tag 11/4): the empty func_0206d424. */
void TalkPageMeasurer_Nothing11_4(void)
{
    func_0206d424();
}
CLEAN_AS(func_0206c5f4, TalkPageMeasurer_Nothing11_4)

/* func_0206c5fc (tag 11/2): the measurer's word 0x50 set to 2 (the tag walker sets its own
 * word 0xe0 likewise). */
void TalkPageMeasurer_Set50Two(TalkPageMeasurer *measurer)
{
    measurer->unk_50 = 2;
}
CLEAN_AS(func_0206c5fc, TalkPageMeasurer_Set50Two)

/* func_0206c604 (tag 11/1): the word 0x50 set to 1. */
void TalkPageMeasurer_Set50One(TalkPageMeasurer *measurer)
{
    measurer->unk_50 = 1;
}
CLEAN_AS(func_0206c604, TalkPageMeasurer_Set50One)

/* func_0206c60c (tag 4/34): the villager's boom text. */
void TalkPageMeasurer_PutBoom(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_loaded(measurer, func_0206781c, TALK_PAGE_TALK_BOOM, 1);
}
CLEAN_AS(func_0206c60c, TalkPageMeasurer_PutBoom)

/* func_0206c65c (tag 4/33): the villager's praise word. */
void TalkPageMeasurer_PutPraise(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_loaded(measurer, func_02067728, TALK_PAGE_TALK_PRAISE, 1);
}
CLEAN_AS(func_0206c65c, TalkPageMeasurer_PutPraise)

/* func_0206c6ac (tag 4/31): the nickname the villager gave the player. */
void TalkPageMeasurer_PutNickname(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_loaded(measurer, func_0206777c, TALK_PAGE_TALK_NICKNAME, 1);
}
CLEAN_AS(func_0206c6ac, TalkPageMeasurer_PutNickname)

/* func_0206c6fc (tag 4/30): the villager's impression. */
void TalkPageMeasurer_PutImpression(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_loaded(measurer, func_020677d0, TALK_PAGE_TALK_IMPRESSION, 1);
}
CLEAN_AS(func_0206c6fc, TalkPageMeasurer_PutImpression)

/* func_0206c74c (tag 4/29): the talk's name 3. */
void TalkPageMeasurer_PutName3(TalkPageMeasurer *measurer)
{
    func_0206d428(measurer, 3);
}
CLEAN_AS(func_0206c74c, TalkPageMeasurer_PutName3)

/* func_0206c758 (tag 4/28): name 2. */
void TalkPageMeasurer_PutName2(TalkPageMeasurer *measurer)
{
    func_0206d428(measurer, 2);
}
CLEAN_AS(func_0206c758, TalkPageMeasurer_PutName2)

/* func_0206c764 (tag 4/27): name 1. */
void TalkPageMeasurer_PutName1(TalkPageMeasurer *measurer)
{
    func_0206d428(measurer, 1);
}
CLEAN_AS(func_0206c764, TalkPageMeasurer_PutName1)

/* func_0206c770 (tag 4/26): name 0. */
void TalkPageMeasurer_PutName0(TalkPageMeasurer *measurer)
{
    func_0206d428(measurer, 0);
}
CLEAN_AS(func_0206c770, TalkPageMeasurer_PutName0)

/* func_0206c77c (tag 4/25): the talk's part 10. */
void TalkPageMeasurer_PutPart10(TalkPageMeasurer *measurer)
{
    func_0206d484(measurer, 10);
}
CLEAN_AS(func_0206c77c, TalkPageMeasurer_PutPart10)

/* func_0206c788 (tag 4/24): part 9. */
void TalkPageMeasurer_PutPart9(TalkPageMeasurer *measurer)
{
    func_0206d484(measurer, 9);
}
CLEAN_AS(func_0206c788, TalkPageMeasurer_PutPart9)

/* func_0206c794 (tag 4/23): part 8. */
void TalkPageMeasurer_PutPart8(TalkPageMeasurer *measurer)
{
    func_0206d484(measurer, 8);
}
CLEAN_AS(func_0206c794, TalkPageMeasurer_PutPart8)

/* func_0206c7a0 (tag 4/22): part 7. */
void TalkPageMeasurer_PutPart7(TalkPageMeasurer *measurer)
{
    func_0206d484(measurer, 7);
}
CLEAN_AS(func_0206c7a0, TalkPageMeasurer_PutPart7)

/* func_0206c7ac (tag 4/21): part 6. */
void TalkPageMeasurer_PutPart6(TalkPageMeasurer *measurer)
{
    func_0206d484(measurer, 6);
}
CLEAN_AS(func_0206c7ac, TalkPageMeasurer_PutPart6)

/* func_0206c7b8 (tag 4/20): part 5. */
void TalkPageMeasurer_PutPart5(TalkPageMeasurer *measurer)
{
    func_0206d484(measurer, 5);
}
CLEAN_AS(func_0206c7b8, TalkPageMeasurer_PutPart5)

/* func_0206c7c4 (tag 4/19): part 4. */
void TalkPageMeasurer_PutPart4(TalkPageMeasurer *measurer)
{
    func_0206d484(measurer, 4);
}
CLEAN_AS(func_0206c7c4, TalkPageMeasurer_PutPart4)

/* func_0206c7d0 (tag 4/18): part 3. */
void TalkPageMeasurer_PutPart3(TalkPageMeasurer *measurer)
{
    func_0206d484(measurer, 3);
}
CLEAN_AS(func_0206c7d0, TalkPageMeasurer_PutPart3)

/* func_0206c7dc (tag 4/17): part 2. */
void TalkPageMeasurer_PutPart2(TalkPageMeasurer *measurer)
{
    func_0206d484(measurer, 2);
}
CLEAN_AS(func_0206c7dc, TalkPageMeasurer_PutPart2)

/* func_0206c7e8 (tag 4/16): part 1. */
void TalkPageMeasurer_PutPart1(TalkPageMeasurer *measurer)
{
    func_0206d484(measurer, 1);
}
CLEAN_AS(func_0206c7e8, TalkPageMeasurer_PutPart1)

/* func_0206c7f4 (tag 4/15): part 0. */
void TalkPageMeasurer_PutPart0(TalkPageMeasurer *measurer)
{
    func_0206d484(measurer, 0);
}
CLEAN_AS(func_0206c7f4, TalkPageMeasurer_PutPart0)

/* func_0206c800 (tag 4/14): another resident's player name. */
void TalkPageMeasurer_PutOtherPlayer(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_loaded(measurer, func_0206786c, TALK_PAGE_TALK_OTHER_PLAYER, 0);
}
CLEAN_AS(func_0206c800, TalkPageMeasurer_PutOtherPlayer)

/* func_0206c850 (tag 4/13): a random villager's name. */
void TalkPageMeasurer_PutRandomNpc(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_loaded(measurer, func_020678f8, TALK_PAGE_TALK_RANDOM_NPC, 0);
}
CLEAN_AS(func_0206c850, TalkPageMeasurer_PutRandomNpc)

/* func_0206c8a0 (tag 4/12): the villager on bad terms with the one talked to. */
void TalkPageMeasurer_PutDislikedNpc(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_loaded(measurer, func_02067964, TALK_PAGE_TALK_DISLIKED_NPC, 0);
}
CLEAN_AS(func_0206c8a0, TalkPageMeasurer_PutDislikedNpc)

/* func_0206c8f0 (tag 4/11): the villager on good terms with the one talked to. */
void TalkPageMeasurer_PutLikedNpc(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_loaded(measurer, func_020679b0, TALK_PAGE_TALK_LIKED_NPC, 0);
}
CLEAN_AS(func_0206c8f0, TalkPageMeasurer_PutLikedNpc)

/* func_0206c940 (tag 4/10): the second the talk began at. */
void TalkPageMeasurer_PutSecond(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_set_text(measurer, func_02067f74);
}
CLEAN_AS(func_0206c940, TalkPageMeasurer_PutSecond)

/* func_0206c988 (tag 4/9): the minute. */
void TalkPageMeasurer_PutMinute(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_set_text(measurer, func_02067fa4);
}
CLEAN_AS(func_0206c988, TalkPageMeasurer_PutMinute)

/* func_0206c9d0 (tag 4/8): the hour on a 12-hour clock. */
void TalkPageMeasurer_PutHour12(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_set_text(measurer, func_02067fd4);
}
CLEAN_AS(func_0206c9d0, TalkPageMeasurer_PutHour12)

/* func_0206ca18 (tag 4/7): the weekday's name. */
void TalkPageMeasurer_PutWeekday(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_set_text(measurer, func_02068010);
}
CLEAN_AS(func_0206ca18, TalkPageMeasurer_PutWeekday)

/* func_0206ca60 (tag 4/6): the day. */
void TalkPageMeasurer_PutDay(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_set_text(measurer, func_02068034);
}
CLEAN_AS(func_0206ca60, TalkPageMeasurer_PutDay)

/* func_0206caa8 (tag 4/5): the month. */
void TalkPageMeasurer_PutMonth(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_set_text(measurer, func_02068058);
}
CLEAN_AS(func_0206caa8, TalkPageMeasurer_PutMonth)

/* func_0206caf0 (tag 4/4): the year. */
void TalkPageMeasurer_PutYear(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_set_text(measurer, func_0206807c);
}
CLEAN_AS(func_0206caf0, TalkPageMeasurer_PutYear)

/* func_0206cb38 (tag 4/3): the town's name. */
void TalkPageMeasurer_PutTownName(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_loaded(measurer, func_02067a3c, TALK_PAGE_TALK_TOWN_NAME, 0);
}
CLEAN_AS(func_0206cb38, TalkPageMeasurer_PutTownName)

/* func_0206cb88 (tag 4/2): the catchphrase of the villager talked to. */
void TalkPageMeasurer_PutCatchphrase(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_loaded(measurer, func_02067a74, TALK_PAGE_TALK_CATCHPHRASE, 0);
}
CLEAN_AS(func_0206cb88, TalkPageMeasurer_PutCatchphrase)

/* func_0206cbd8 (tag 4/1): the name of the receiver (the one talked to); the receiver is read
 * once and its name's text asked for twice. */
void TalkPageMeasurer_PutReceiverName(TalkPageMeasurer *measurer)
{
    void *receiver = *(void **) (void *) talk_page_talk_at(measurer, TALK_PAGE_TALK_RECEIVER);
    MessageWalker_Enter(&measurer->walker.base, talk_page_characters(func_020668d4(receiver)));
    MailParticles_TakeLastSyllable(talk_page_particles(measurer),
                                   (const char *) (uintptr_t) talk_page_characters(func_020668d4(receiver)));
    talk_page_particles(measurer)->ro_after_rieul = 0;
}
CLEAN_AS(func_0206cbd8, TalkPageMeasurer_PutReceiverName)

/* func_0206cc2c (tag 4/0): this system's player's name. */
void TalkPageMeasurer_PutPlayerName(TalkPageMeasurer *measurer)
{
    talk_page_measurer_walk_loaded(measurer, func_020679fc, TALK_PAGE_TALK_PLAYER_NAME, 0);
}
CLEAN_AS(func_0206cc2c, TalkPageMeasurer_PutPlayerName)

/* func_0206cc7c (tag 1/7): nothing; it ends the text tag 1/6 may replace. */
void TalkPageMeasurer_RememberedEnd(void) {}
CLEAN_AS(func_0206cc7c, TalkPageMeasurer_RememberedEnd)

/* func_0206cc80 (tag 1/6): when a tag 1/7 follows and the villager talked to remembers a text
 * of the player, the walk goes on at that tag 1/7 and that text is walked in place of what was
 * between them. */
void TalkPageMeasurer_RememberedText(TalkPageMeasurer *measurer)
{
    int position = (int) measurer->walker.base.position;
    int end = MessageQuery_FindTag(position, TALK_PAGE_REMEMBERED_END_GROUP, TALK_PAGE_REMEMBERED_END_KIND);
    if (end == 0) {
        return;
    }
    if (func_020676d0(measurer->talk) == 0) {
        return;
    }
    MessageWalker_Skip(&measurer->walker.base, end - position);
    MessageWalker_Enter(&measurer->walker.base, talk_page_characters(talk_page_talk_at(measurer, TALK_PAGE_TALK_REMEMBERED)));
}
CLEAN_AS(func_0206cc80, TalkPageMeasurer_RememberedText)

/* func_0206ccc8 (tag 0/8): "{" walked in place of the tag. */
void TalkPageMeasurer_PutLeftBrace(TalkPageMeasurer *measurer)
{
    MessageWalker_Enter(&measurer->walker.base, TextCodes_LeftBrace());
}
CLEAN_AS(func_0206ccc8, TalkPageMeasurer_PutLeftBrace)

/* func_0206cce0 (tag 0/7): "%". */
void TalkPageMeasurer_PutPercent(TalkPageMeasurer *measurer)
{
    MessageWalker_Enter(&measurer->walker.base, TextCodes_Percent());
}
CLEAN_AS(func_0206cce0, TalkPageMeasurer_PutPercent)

/* func_0206ccf8 (tag 0/6): "&". */
void TalkPageMeasurer_PutAmpersand(TalkPageMeasurer *measurer)
{
    MessageWalker_Enter(&measurer->walker.base, TextCodes_Ampersand());
}
CLEAN_AS(func_0206ccf8, TalkPageMeasurer_PutAmpersand)

/* func_0206cd10 (tag 0/1): "/". */
void TalkPageMeasurer_PutSlash(TalkPageMeasurer *measurer)
{
    MessageWalker_Enter(&measurer->walker.base, TextCodes_Slash());
}
CLEAN_AS(func_0206cd10, TalkPageMeasurer_PutSlash)

/* func_0206cd28 (tag 0/0): "*". */
void TalkPageMeasurer_PutAsterisk(TalkPageMeasurer *measurer)
{
    MessageWalker_Enter(&measurer->walker.base, TextCodes_Asterisk());
}
CLEAN_AS(func_0206cd28, TalkPageMeasurer_PutAsterisk)

/* func_0206cd40 (group 0xff): kinds 0 to 2: kind 2 TalkPageMeasurer_AltText, the others
 * nothing. */
void TalkPageMeasurer_DispatchGroupFF(TalkPageMeasurer *measurer)
{
    static const MemberPointer *const constants[3] = {&__ptmf_null, &__ptmf_null, &data_020dedac};
    talk_page_measurer_dispatch(measurer, &data_021cda84, data_021cdaa4, constants, 3);
}
CLEAN_AS(func_0206cd40, TalkPageMeasurer_DispatchGroupFF)

/* func_0206cdbc (group 11): kinds 0 to 20: 1 and 2 TalkPageMeasurer_Set50One and Set50Two, 4
 * TalkPageMeasurer_Nothing11_4, 5 to 15 the parts (TalkPageMeasurer_Part0 to Part10), 16 to
 * 19 the names (TalkPageMeasurer_Name0 to Name3), 20 TalkPageMeasurer_PutParticle; 0 and 3
 * nothing. */
void TalkPageMeasurer_DispatchGroup11(TalkPageMeasurer *measurer)
{
    static const MemberPointer *const constants[21] = {
        &__ptmf_null,   &data_020dee04, &data_020dee0c, &__ptmf_null,   &data_020dee14, &data_020dee24, &data_020dee2c,
        &data_020dee3c, &data_020dee44, &data_020dee54, &data_020dee5c, &data_020dee6c, &data_020dee84, &data_020dedfc,
        &data_020dedf4, &data_020dedec, &data_020dede4, &data_020deddc, &data_020dedd4, &data_020dedcc, &data_020de9ec,
    };
    talk_page_measurer_dispatch(measurer, &data_021cda4c, data_021cdf74, constants, 21);
}
CLEAN_AS(func_0206cdbc, TalkPageMeasurer_DispatchGroup11)

/* func_0206cf3c (group 4): kinds 0 to 34, the texts walked in place of the tag
 * (TalkPageMeasurer_PutPlayerName to TalkPageMeasurer_PutBoom); kind 32 nothing. */
void TalkPageMeasurer_DispatchGroup4(TalkPageMeasurer *measurer)
{
    static const MemberPointer *const constants[35] = {
        &data_020deee4, &data_020de8e4, &data_020de834, &data_020dec84, &data_020dec8c, &data_020deeec, &data_020debdc,
        &data_020de874, &data_020de8ec, &data_020de8f4, &data_020dec24, &data_020def04, &data_020def14, &data_020def0c,
        &data_020dec44, &data_020deefc, &data_020deef4, &data_020decbc, &data_020decc4, &data_020deedc, &data_020deed4,
        &data_020deecc, &data_020decf4, &data_020deebc, &data_020deeb4, &data_020deeac, &data_020ded2c, &data_020dee9c,
        &data_020dee94, &data_020ded54, &data_020ded84, &data_020dee7c, &__ptmf_null,   &data_020dee74, &data_020dedb4,
    };
    talk_page_measurer_dispatch(measurer, &data_021cda44, data_021ce1dc, constants, 35);
}
CLEAN_AS(func_0206cf3c, TalkPageMeasurer_DispatchGroup4)

/* func_0206d18c (group 2, the choices): the walk goes past the texts after the tag. */
void TalkPageMeasurer_SkipTexts(TalkPageMeasurer *measurer)
{
    MessageWalker_Skip(&measurer->walker.base, (int) MessageTag_TextsSize(&measurer->tag));
}
CLEAN_AS(func_0206d18c, TalkPageMeasurer_SkipTexts)

/* func_0206d1a4 (group 1): kinds 0 to 16: 6 TalkPageMeasurer_RememberedText, 7
 * TalkPageMeasurer_RememberedEnd, the others nothing. */
void TalkPageMeasurer_DispatchGroup1(TalkPageMeasurer *measurer)
{
    static const MemberPointer *const constants[17] = {
        &__ptmf_null,   &__ptmf_null,   &__ptmf_null, &__ptmf_null, &__ptmf_null, &__ptmf_null,
        &data_020de86c, &data_020deb64, &__ptmf_null, &__ptmf_null, &__ptmf_null, &__ptmf_null,
        &__ptmf_null,   &__ptmf_null,   &__ptmf_null, &__ptmf_null, &__ptmf_null,
    };
    talk_page_measurer_dispatch(measurer, &data_021cda48, data_021cdeec, constants, 17);
}
CLEAN_AS(func_0206d1a4, TalkPageMeasurer_DispatchGroup1)
