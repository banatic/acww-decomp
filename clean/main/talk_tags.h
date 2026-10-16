/* The tags of a talk's messages (class data_020defe4, constructor func_0206bde0, 0xe4 bytes): a
 * walker of the message texts (MessageWalker, message_cursor.h) that shows a talk's message and
 * acts on the tags it meets. func_0206b840 picks a handler table by the tag's group (0 to 11,
 * and 0xff), each table a handler by the tag's kind; the handlers here are:
 *
 * - group 4 (func_0206b228): texts walked in place of the tag: the talk's parts 0 to 10 (kinds
 *   15 to 25, as in the message reader), its four names (kinds 26 to 29), and texts loaded
 *   from the villager talked to or about (kinds 11 to 14 and 30 to 34): each name between two
 *   colour tags (MessageTag_ColourTag), its last Hangul syllable kept for the particles after
 *   it;
 * - group 5 kind 5: the four choices of the slider window (talk_windows.h);
 * - group 6 (func_0206b04c): branches: the receiver is told the branch and its number of
 *   choices, a value of the game picks one of the message numbers the tag carries, and the talk
 *   goes on with that message (func_0206b964);
 * - group 9 (func_0206aec4): the receiver's scene moves (scene_base.h): who has the focus,
 *   looks and turns, and passing the turn;
 * - group 11 (func_0206ace4), kinds 1 to 7: the walker's own settings;
 * - groups 8 and 10, and group 4 kind 32: nothing.
 *
 * The talk (0x1e9c bytes, talk_process.h) is the walker's word at 0x24; its receiver (a
 * Base_02066994, the scene or object the talk is for) at 0x14a8. */
#ifndef CLEAN_MAIN_TALK_TAGS_H
#define CLEAN_MAIN_TALK_TAGS_H

#include "message_decoder.h"
#include "types.h"

/* The walker (0xe4 bytes). */
typedef struct TalkTagsWalker {
    MessageWalker base; /* 0x00 */
    u8 *talk;           /* 0x24: the talk shown */
    void *window;       /* 0x28: the constructor's second argument */
    s32 lines;          /* 0x2c */
    s32 state;          /* 0x30: TALK_TAGS_STATE_CHOOSING while the slider window is open */
    s32 unk_34;         /* 0x34 */
    MessageTag tag;     /* 0x38: the tag being handled */
    u8 unk_4c[4];       /* 0x4c */
    s32 unk_50;         /* 0x50 */
    s32 unk_54;         /* 0x54 */
    s32 unk_58;         /* 0x58 */
    s32 name_colour;    /* 0x5c: the colour tag put before a name */
    u8 unk_60[0x3c];    /* 0x60 */
    u8 unk_9c[0x3c];    /* 0x9c */
    u8 choices_shown;   /* 0xd8: set while the slider tag waits to open its window */
    u8 convert_next;    /* 0xd9: turn the next character into its other form */
    u8 unk_da[2];       /* 0xda */
    u32 unk_dc;         /* 0xdc */
    s32 unk_e0;         /* 0xe0: 1 or 2 from tags 11/1 and 11/2; 0 when a part is walked */
} TalkTagsWalker;

/* TalkTagsWalker.state while the slider window is open. */
#define TALK_TAGS_STATE_CHOOSING 5

/* Group 11. */
void TalkTags_NotePart2(TalkTagsWalker *walker);
void TalkTags_NotePart1(TalkTagsWalker *walker);
void TalkTags_NotePart0(TalkTagsWalker *walker);
void TalkTags_Nothing11_4(void);
void TalkTags_ConvertNext(TalkTagsWalker *walker);
void TalkTags_SetE0Two(TalkTagsWalker *walker);
void TalkTags_SetE0One(TalkTagsWalker *walker);

/* Groups 8 and 10. */
void TalkTags_Nothing10_0(void *walker);
void TalkTags_Nothing8_2(void *walker);
void TalkTags_Nothing8_1(void *walker);
void TalkTags_Nothing8_0(void *walker);

/* Group 9. */
void TalkTags_PassTurn(TalkTagsWalker *walker);
void TalkTags_FaceSecond(TalkTagsWalker *walker);
void *TalkTags_LookAtSecond(TalkTagsWalker *walker);
void TalkTags_FaceFirst(TalkTagsWalker *walker);
void TalkTags_LookAtFirst(TalkTagsWalker *walker);
void TalkTags_FacePlayer(TalkTagsWalker *walker);
void TalkTags_LookAtPlayer(TalkTagsWalker *walker);
void TalkTags_FocusSecond(TalkTagsWalker *walker);
void TalkTags_FocusFirst(TalkTagsWalker *walker);
void TalkTags_FocusPlayer(TalkTagsWalker *walker);

/* Group 6. */
void TalkTags_BranchBySpecies(TalkTagsWalker *walker);
void TalkTags_BranchByResident(TalkTagsWalker *walker);
void TalkTags_BranchByWeekday(TalkTagsWalker *walker);
void TalkTags_BranchByPlayers(TalkTagsWalker *walker);
void TalkTags_BranchByFalling(TalkTagsWalker *walker);
void TalkTags_BranchByPartOfDay(TalkTagsWalker *walker);
void TalkTags_BranchByVillagers(TalkTagsWalker *walker);
void TalkTags_BranchByFish(TalkTagsWalker *walker);
void TalkTags_BranchByInsects(TalkTagsWalker *walker);
void TalkTags_BranchByHouse(TalkTagsWalker *walker);
void TalkTags_BranchByPlayerKind(TalkTagsWalker *walker);
void TalkTags_BranchByFondness(TalkTagsWalker *walker);
void TalkTags_BranchRandom3(TalkTagsWalker *walker);
void TalkTags_BranchRandom2(TalkTagsWalker *walker);

/* Group 5. */
void TalkTags_SliderChoices(TalkTagsWalker *walker);

/* Group 4. */
void TalkTags_PutBoom(TalkTagsWalker *walker);
void TalkTags_PutPraise(TalkTagsWalker *walker);
void TalkTags_Nothing4_32(void);
void TalkTags_PutNickname(TalkTagsWalker *walker);
void TalkTags_PutImpression(TalkTagsWalker *walker);
void TalkTags_PutName3(TalkTagsWalker *walker);
void TalkTags_PutName2(TalkTagsWalker *walker);
void TalkTags_PutName1(TalkTagsWalker *walker);
void TalkTags_PutName0(TalkTagsWalker *walker);
void TalkTags_PutPart10(TalkTagsWalker *walker);
void TalkTags_PutPart9(TalkTagsWalker *walker);
void TalkTags_PutPart8(TalkTagsWalker *walker);
void TalkTags_PutPart7(TalkTagsWalker *walker);
void TalkTags_PutPart6(TalkTagsWalker *walker);
void TalkTags_PutPart5(TalkTagsWalker *walker);
void TalkTags_PutPart4(TalkTagsWalker *walker);
void TalkTags_PutPart3(TalkTagsWalker *walker);
void TalkTags_PutPart2(TalkTagsWalker *walker);
void TalkTags_PutPart1(TalkTagsWalker *walker);
void TalkTags_PutPart0(TalkTagsWalker *walker);
void TalkTags_PutOtherPlayer(TalkTagsWalker *walker);
void TalkTags_PutRandomNpc(TalkTagsWalker *walker);
void TalkTags_PutDislikedNpc(TalkTagsWalker *walker);
void TalkTags_PutLikedNpc(TalkTagsWalker *walker);

#endif
