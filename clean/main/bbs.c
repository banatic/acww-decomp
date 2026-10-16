/* The town's bulletin board and its two text classes (bbs.h). */
#include "bbs.h"

#include <stdint.h>

#include "clean.h"

static_assert(offsetof(BbsPost, day) == 0xc0, "post date");
static_assert(offsetof(BbsPost, flags) == 0xc3, "post flags");
static_assert(sizeof(BbsPost) == 0xc4, "post size");
static_assert(offsetof(Bbs, last_notice) == 0xb7c, "last notice");
static_assert(offsetof(Bbs, count) == 0xb7e, "post count");
static_assert(offsetof(BbsWideText, text) == 0xe, "wide text characters");
static_assert(offsetof(BbsLabel, text) == 0x12, "label characters");
static_assert(sizeof(BbsLabel) == 0xd8, "label size");

#define NEWLINE 0x0a

extern Bbs data_021eed68;               /* the town's board */
extern const char *const data_020e1858; /* "bbs_default", the archive of the first posts */
extern const TextVtable data_020e1870;  /* the wide text's vtable */
extern const TextVtable data_020e1888;  /* the label's vtable */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_02051bf8(u16 *dst, int units); /* clears `units` 16-bit units */
extern void func_0209df64(Date *today);         /* today's date (Calendar_Today) */

/* The text base's constructors and destructors (text_label.c). */
extern void *func_020a88ec(void *text);  /* base of a wide text */
extern void *func_020a887c(void *text);  /* its destructor */
extern void *func_020a8cac(void *label); /* base of a label */
extern void func_020a8c1c(void *label);  /* empty a label's text */
extern void *func_020a8c38(void *label); /* its destructor */
extern void func_020edb3c(void *block);  /* operator delete */

/* Load message `*number` of the message archive `archive` into a label. */
extern int func_0203d7d8(BbsLabel *label, const u8 *number, const char *archive);
/* Line `line` of an 8-bit text, 0 when it has none. */
extern int func_020a7bf4(const char *text, int line);
/* Set a label from a line func_020a7bf4 gave. */
extern int func_020a8a34(TextLabel *label, int line);
/* Convert a label's 8-bit text to 16 bits into a wide text. */
extern int func_020a87e0(void *dst, void *src);
/* Copy a text's characters into `count` 16-bit characters, padding with 0. */
extern int func_0205182c(void *src, u16 *dst, int count);

/* The vector helpers are handed the game's own post constructor and destructor. */
extern void func_020782d0(void *post);
extern void func_020782d4(void *post);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* ---- Posting to the town's board */

/* func_02077ec4: the posts on the town's board. */
u8 Bbs_CountTownPosts(void)
{
    return Bbs_Count(&data_021eed68);
}
CLEAN_AS(func_02077ec4, Bbs_CountTownPosts)

/* func_02077ed4: posts `text` (BBS_POST_LENGTH characters) to the town's board, dated today
 * and flagged as a text post. */
void Bbs_PostText(const u16 *text)
{
    BbsPost *post = Bbs_NewPost(&data_021eed68);
    Date today;
    func_0209df64(&today);
    BbsPost_Init(post, &today);
    BbsPost_MarkText(post);
    MI_CpuCopy8(text, BbsPost_Text(post), sizeof(post->text));
}
CLEAN_AS(func_02077ed4, Bbs_PostText)

/* func_02077f14: posts message `number` of the message archive `archive` to the town's board,
 * dated today. Returns what Bbs_PostMessageDated does. */
void *Bbs_PostMessage(int number, const char *archive)
{
    Date today;
    func_0209df64(&today);
    return Bbs_PostMessageDated(number, archive, today.year, today.month, today.day);
}
CLEAN_AS(func_02077f14, Bbs_PostMessage)

/* func_02077f3c: posts message `number` of the message archive `archive` to the town's board
 * with the date given.
 * QUIRK: the original returns what BbsLabel_Destruct does, the address of the label it loaded
 * the message into: a local of its own, gone by then, which no caller uses. Clean returns NULL
 * in its place, as an address of its own stack would mean nothing to the caller either. */
void *Bbs_PostMessageDated(int number, const char *archive, u8 year, u8 month, u8 day)
{
    BbsLabel label;
    BbsLabel_Construct(&label);
    BbsLabel_LoadMessage(&label, number, archive);
    BbsPost *post = Bbs_NewPost(&data_021eed68);
    Date date = {.day = day, .month = month, .year = year};
    BbsPost_Init(post, &date);
    BbsPost_SetTextFromLabel(post, &label);
    BbsLabel_Destruct(&label);
    return NULL;
}
CLEAN_AS(func_02077f3c, Bbs_PostMessageDated)

/* func_02077f8c: the post's text from the label's: its six lines, each cut to 16 characters
 * and ended by a newline unless it has all 16; a line the label lacks leaves only the newline.
 * Returns 1.
 * QUIRK: a line longer than 16 characters moves the text on by its whole length, though only
 * 16 characters of it are copied; the game's messages keep their lines to 16. */
int BbsPost_SetTextFromLabel(BbsPost *post, BbsLabel *label)
{
    TextLabel line_label;
    WideText line_text;
    TextLabel_Construct(&line_label);
    WideText_Construct(&line_text);
    u16 *text = BbsPost_Text(post);
    int length = 0;
    for (int i = 0; i < BBS_POST_LINES; i++) {
        int line = func_020a7bf4(label->text, i);
        if (line == 0) {
            func_020a8c1c(&line_label);
            text[length++] = NEWLINE;
            continue;
        }
        func_020a8a34(&line_label, line);
        func_020a87e0(&line_text, &line_label);
        func_0205182c(&line_text, &text[length], BBS_LINE_LENGTH);
        int line_length = WideText_Length(&line_text);
        length += line_length;
        if (line_length != BBS_LINE_LENGTH) {
            text[length++] = NEWLINE;
        }
    }
    WideText_Destruct(&line_text);
    TextLabel_Destruct(&line_label);
    return 1;
}
CLEAN_AS(func_02077f8c, BbsPost_SetTextFromLabel)

/* ---- The wide text of 96 characters */

/* func_02078018 (vtable entry 3): the address of the characters. */
int BbsWideText_Buffer(int text)
{
    return (int) ((u32) text + offsetof(BbsWideText, text));
}
CLEAN_AS(func_02078018, BbsWideText_Buffer)

/* func_0207801c (vtable entry 2) */
int BbsWideText_Capacity(void)
{
    return BBS_WIDE_TEXT_CAPACITY;
}
CLEAN_AS(func_0207801c, BbsWideText_Capacity)

/* func_02078020 (vtable entry 1) */
BbsWideText *BbsWideText_DestructDelete(BbsWideText *text)
{
    text->vtable = &data_020e1870;
    func_020a887c(text);
    func_020edb3c(text);
    return text;
}
CLEAN_AS(func_02078020, BbsWideText_DestructDelete)

/* func_02078040 (vtable entry 0) */
BbsWideText *BbsWideText_Destruct(BbsWideText *text)
{
    text->vtable = &data_020e1870;
    func_020a887c(text);
    return text;
}
CLEAN_AS(func_02078040, BbsWideText_Destruct)

/* func_02078058 */
BbsWideText *BbsWideText_Construct(BbsWideText *text)
{
    func_020a88ec(text);
    text->vtable = &data_020e1870;
    return text;
}
CLEAN_AS(func_02078058, BbsWideText_Construct)

/* ---- The label of 194 characters */

/* func_02078070: loads message `number` (its low byte) of the message archive `archive`. */
void BbsLabel_LoadMessage(BbsLabel *label, int number, const char *archive)
{
    u8 message = (u8) number;
    func_0203d7d8(label, &message, archive);
}
CLEAN_AS(func_02078070, BbsLabel_LoadMessage)

/* func_02078090 (vtable entry 3): the address of the characters. */
int BbsLabel_Buffer(int label)
{
    return (int) ((u32) label + offsetof(BbsLabel, text));
}
CLEAN_AS(func_02078090, BbsLabel_Buffer)

/* func_02078094 (vtable entry 2) */
int BbsLabel_Capacity(void)
{
    return BBS_LABEL_CAPACITY;
}
CLEAN_AS(func_02078094, BbsLabel_Capacity)

/* func_02078098 (vtable entry 1) */
BbsLabel *BbsLabel_DestructDelete(BbsLabel *label)
{
    label->vtable = &data_020e1888;
    func_020a8c38(label);
    func_020edb3c(label);
    return label;
}
CLEAN_AS(func_02078098, BbsLabel_DestructDelete)

/* func_020780b8 (vtable entry 0) */
BbsLabel *BbsLabel_Destruct(BbsLabel *label)
{
    label->vtable = &data_020e1888;
    func_020a8c38(label);
    return label;
}
CLEAN_AS(func_020780b8, BbsLabel_Destruct)

/* func_020780d0: an empty label. */
BbsLabel *BbsLabel_Construct(BbsLabel *label)
{
    func_020a8cac(label);
    label->vtable = &data_020e1888;
    func_020a8c1c(label);
    return label;
}
CLEAN_AS(func_020780d0, BbsLabel_Construct)

/* ---- The board */

/* func_020780f0: removes post `index`, moving the later ones down.
 * REQUIRES: a board with posts (the only caller removes the oldest of fifteen); on an empty one
 * the count wraps to 255. */
void Bbs_RemovePost(Bbs *bbs, int index)
{
    for (int i = index; i < bbs->count - 1; i++) {
        MI_CpuCopy8(&bbs->posts[i + 1], &bbs->posts[i], sizeof(BbsPost));
    }
    bbs->count--;
}
CLEAN_AS(func_020780f0, Bbs_RemovePost)

/* func_02078130 */
void Bbs_SetLastNotice(Bbs *bbs, s16 number)
{
    bbs->last_notice = (u16) number;
}
CLEAN_AS(func_02078130, Bbs_SetLastNotice)

/* func_0207813c */
u16 Bbs_GetLastNotice(Bbs *bbs)
{
    return bbs->last_notice;
}
CLEAN_AS(func_0207813c, Bbs_GetLastNotice)

/* func_02078148: the post after the last, pushing out the oldest when the board is full. */
BbsPost *Bbs_NewPost(Bbs *bbs)
{
    if (bbs->count < BBS_POSTS) {
        bbs->count++;
    } else {
        Bbs_RemovePost(bbs, 0);
        bbs->count = BBS_POSTS;
    }
    return &bbs->posts[bbs->count - 1];
}
CLEAN_AS(func_02078148, Bbs_NewPost)

/* func_02078188 */
u8 Bbs_Count(Bbs *bbs)
{
    return bbs->count;
}
CLEAN_AS(func_02078188, Bbs_Count)

/* func_02078194: empties the board, then posts the first two messages of "bbs_default".
 * QUIRK: those go to the town's board whichever board was emptied (the caller empties that
 * one). */
void Bbs_Init(Bbs *bbs)
{
    Bbs_Clear(bbs);
    Bbs_PostMessage(0, data_020e1858);
    Bbs_PostMessage(1, data_020e1858);
}
CLEAN_AS(func_02078194, Bbs_Init)

/* func_020781bc: no posts, no notice received. */
void Bbs_Clear(Bbs *bbs)
{
    bbs->count = 0;
    bbs->last_notice = 0;
}
CLEAN_AS(func_020781bc, Bbs_Clear)

/* func_020781d0 */
BbsPost *Bbs_GetPost(Bbs *bbs, int index)
{
    return Bbs_PostAt(bbs, index);
}
CLEAN_AS(func_020781d0, Bbs_GetPost)

/* func_020781d8 */
BbsPost *Bbs_PostAt(Bbs *bbs, int index)
{
    return (BbsPost *) ((uintptr_t) bbs + (u32) index * sizeof(BbsPost));
}
CLEAN_AS(func_020781d8, Bbs_PostAt)

/* func_020781e0: the destructor: each post's, through the vector helper. */
Bbs *Bbs_Destruct(Bbs *bbs)
{
    __cxa_vec_cleanup(bbs, BBS_POSTS, sizeof(BbsPost), func_020782d0);
    return bbs;
}
CLEAN_AS(func_020781e0, Bbs_Destruct)

/* func_020781fc: the constructor: each post's, through the vector helper. */
Bbs *Bbs_Construct(Bbs *bbs)
{
    __cxa_vec_ctor(bbs, BBS_POSTS, sizeof(BbsPost), func_020782d4, func_020782d0);
    return bbs;
}
CLEAN_AS(func_020781fc, Bbs_Construct)

/* ---- A post */

/* func_02078224 */
void BbsPost_MarkText(BbsPost *post)
{
    post->flags |= BBS_POST_TEXT;
}
CLEAN_AS(func_02078224, BbsPost_MarkText)

/* func_02078234 */
int BbsPost_IsText(const BbsPost *post)
{
    return (post->flags & BBS_POST_TEXT) != 0;
}
CLEAN_AS(func_02078234, BbsPost_IsText)

/* func_02078248: marks the post read by `player`; nothing for a number outside 0-3. */
void BbsPost_MarkRead(BbsPost *post, int player)
{
    if (player < 0 || player >= BBS_READERS) {
        return;
    }
    post->flags |= (u8) (1 << player);
}
CLEAN_AS(func_02078248, BbsPost_MarkRead)

/* func_02078268: whether `player` has read the post; 1 for a number outside 0-3. */
int BbsPost_IsRead(const BbsPost *post, int player)
{
    if (player < 0 || player >= BBS_READERS) {
        return 1;
    }
    return (post->flags & (1 << player)) != 0;
}
CLEAN_AS(func_02078268, BbsPost_IsRead)

/* func_02078288 */
u8 BbsPost_GetYear(const BbsPost *post)
{
    return post->year;
}
CLEAN_AS(func_02078288, BbsPost_GetYear)

/* func_02078290 */
u8 BbsPost_GetMonth(const BbsPost *post)
{
    return post->month;
}
CLEAN_AS(func_02078290, BbsPost_GetMonth)

/* func_02078298 */
u8 BbsPost_GetDay(const BbsPost *post)
{
    return post->day;
}
CLEAN_AS(func_02078298, BbsPost_GetDay)

/* func_020782a0: a new post of that date: no flags and an empty text. */
void BbsPost_Init(BbsPost *post, const Date *date)
{
    post->day = date->day;
    post->month = date->month;
    post->year = date->year;
    post->flags = 0;
    func_02051bf8(post->text, BBS_POST_LENGTH);
}
CLEAN_AS(func_020782a0, BbsPost_Init)

/* func_020782cc: the text, at the post's start. */
u16 *BbsPost_Text(BbsPost *post)
{
    return post->text;
}
CLEAN_AS(func_020782cc, BbsPost_Text)

/* func_020782d0: the destructor: does nothing. */
void BbsPost_Destruct(BbsPost *post)
{
    (void) post;
}
CLEAN_AS(func_020782d0, BbsPost_Destruct)

/* func_020782d4: the constructor: does nothing. */
void BbsPost_Construct(BbsPost *post)
{
    (void) post;
}
CLEAN_AS(func_020782d4, BbsPost_Construct)
