/* The town's bulletin board (data_021eed68, at 0x125c0 of the block at data_021dc7a8): up to
 * 15 posts, the oldest first. A post is 96 16-bit characters (six lines of up to 16, each
 * shorter one ended by a newline), the date it was posted and five flags:
 *
 *   bits 0-3  read by the player of that number (overlay 113 shows unread posts in another
 *             color and marks them read when shown);
 *   bit 4     a post whose text came as such (Bbs_PostText: written in overlay 112, received
 *             from another player as a log entry, or a notice received over Wi-Fi), rather
 *             than one of the game's messages (Bbs_PostMessage: archives "bbs_default",
 *             "bbs_raccoon", "bbs_shopinfo").
 *
 * A new post past the fifteenth pushes the oldest out. The board also keeps the number of the
 * last notice received over Wi-Fi (func_0203f5a4 posts one only when its number differs).
 *
 * Two text classes serve the board, both on the game's text base (text_label.h): a wide text
 * of 96 characters (vtable data_020e1870) and a label of 194 8-bit characters (vtable
 * data_020e1888) that a message of the archives is loaded into. */
#ifndef CLEAN_MAIN_BBS_H
#define CLEAN_MAIN_BBS_H

#include "main/calendar.h"
#include "main/text_label.h"
#include "types.h"

#define BBS_POSTS 15
#define BBS_POST_LENGTH 96 /* 16-bit characters */
#define BBS_POST_LINES 6
#define BBS_LINE_LENGTH 16
#define BBS_READERS 4 /* the players whose reading is kept */

#define BBS_POST_TEXT 0x10 /* flag bit 4 */

typedef struct BbsPost {
    u16 text[BBS_POST_LENGTH]; /* 0x00 */
    u8 day;                    /* 0xc0 */
    u8 month;                  /* 0xc1 */
    u8 year;                   /* 0xc2: from 2000 */
    u8 flags;                  /* 0xc3 */
} BbsPost;

typedef struct Bbs {
    BbsPost posts[BBS_POSTS]; /* 0x000 */
    u16 last_notice;          /* 0xb7c */
    u8 count;                 /* 0xb7e */
} Bbs;

#define BBS_WIDE_TEXT_CAPACITY 96
#define BBS_LABEL_CAPACITY 194

typedef struct BbsWideText {
    const TextVtable *vtable; /* data_020e1870 */
    u8 base_04[0xa];          /* the text base's */
    u16 text[BBS_WIDE_TEXT_CAPACITY];
} BbsWideText;

typedef struct BbsLabel {
    const TextVtable *vtable; /* data_020e1888 */
    u8 base_04[0xe];          /* the text base's */
    char text[BBS_LABEL_CAPACITY];
} BbsLabel;

u8 Bbs_CountTownPosts(void);
void Bbs_PostText(const u16 *text);
void *Bbs_PostMessage(int number, const char *archive);
void *Bbs_PostMessageDated(int number, const char *archive, u8 year, u8 month, u8 day);
int BbsPost_SetTextFromLabel(BbsPost *post, BbsLabel *label);

int BbsWideText_Buffer(int text);
int BbsWideText_Capacity(void);
BbsWideText *BbsWideText_DestructDelete(BbsWideText *text);
BbsWideText *BbsWideText_Destruct(BbsWideText *text);
BbsWideText *BbsWideText_Construct(BbsWideText *text);
void BbsLabel_LoadMessage(BbsLabel *label, int number, const char *archive);
int BbsLabel_Buffer(int label);
int BbsLabel_Capacity(void);
BbsLabel *BbsLabel_DestructDelete(BbsLabel *label);
BbsLabel *BbsLabel_Destruct(BbsLabel *label);
BbsLabel *BbsLabel_Construct(BbsLabel *label);

void Bbs_RemovePost(Bbs *bbs, int index);
void Bbs_SetLastNotice(Bbs *bbs, s16 number);
u16 Bbs_GetLastNotice(Bbs *bbs);
BbsPost *Bbs_NewPost(Bbs *bbs);
u8 Bbs_Count(Bbs *bbs);
void Bbs_Init(Bbs *bbs);
void Bbs_Clear(Bbs *bbs);
BbsPost *Bbs_GetPost(Bbs *bbs, int index);
BbsPost *Bbs_PostAt(Bbs *bbs, int index);
Bbs *Bbs_Destruct(Bbs *bbs);
Bbs *Bbs_Construct(Bbs *bbs);

void BbsPost_MarkText(BbsPost *post);
int BbsPost_IsText(const BbsPost *post);
void BbsPost_MarkRead(BbsPost *post, int player);
int BbsPost_IsRead(const BbsPost *post, int player);
u8 BbsPost_GetYear(const BbsPost *post);
u8 BbsPost_GetMonth(const BbsPost *post);
u8 BbsPost_GetDay(const BbsPost *post);
void BbsPost_Init(BbsPost *post, const Date *date);
u16 *BbsPost_Text(BbsPost *post);
void BbsPost_Destruct(BbsPost *post);
void BbsPost_Construct(BbsPost *post);

#endif
