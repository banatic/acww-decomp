/* Letters a villager sends a player through the post (villager_post.h). */
#include "villager_post.h"

#include "clean.h"
#include "mail.h"
#include "mom_letters.h"
#include "player_records.h"
#include "villager_data.h"
#include "villager_roster.h"

#define VILLAGER_POST_NAME_SIZE 0x28
#define VILLAGER_POST_NO_ITEM 0xfff1
/* The text slot func_020662bc puts the villager's name in. */
#define VILLAGER_POST_FROM_VILLAGER 1
/* The texts each letter is drawn from. */
#define VILLAGER_POST_TEXTS 3
/* The paper of the birthday notice. */
#define VILLAGER_POST_BIRTHDAY_PAPER 0x1a
/* The text slots of the birthday notice: the month and the day. */
#define VILLAGER_POST_SLOT_MONTH 2
#define VILLAGER_POST_SLOT_DAY 3

/* An item list: func_02063ccc constructs it, func_020638d4 draws an item of it, func_02063884
 * draws one with no record to go by, func_02063cc8 destroys it. */
typedef struct VillagerPostItemList {
    int kind;
    int group;
} VillagerPostItemList;

extern const char data_020dd3c4[]; /* "re_q10" */
extern const char data_020dd3cc[]; /* "ev_nbirth" */
extern VillagerTown data_021e5a2c; /* the town's villagers */
extern u8 data_021dc7bc[];         /* the town's four players' records */
/* The buffer a letter's group name is formatted into. */
extern char data_021c9704[VILLAGER_POST_NAME_SIZE];

/* The present lists of kinds 2, 3 and 4, made the first time they are needed (bit 0 of their
 * guard words), each object handed to the C++ runtime with its record. */
extern u32 data_021c95f4, data_021c95f8, data_021c95ec;
extern VillagerPostItemList data_021c96ec[3], data_021c96d4[3], data_021c972c[9];
extern u8 data_021c9650[], data_021c962c[], data_021c9644[];
extern u8 data_021c9620[], data_021c9698[], data_021c96b0[];
extern u8 data_021c9608[], data_021c9668[], data_021c9638[], data_021c965c[], data_021c9680[], data_021c96bc[],
    data_021c95fc[], data_021c9614[], data_021c9674[];
/* The list kinds a present of kind 5 is drawn from (0, 4 and 3). */
extern const int data_020cbfe4[3];

extern u32 func_020644cc(int bound); /* a random number below `bound` */
extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_02063ccc(VillagerPostItemList *list, int kind, int group);
/* The destructor; handed to the C++ runtime, so the game's symbol. */
extern void func_02063cc8(VillagerPostItemList *list);
extern void func_020638d4(u16 *item, VillagerPostItemList *list, int record, int a, u8 b, int c, int *group);
extern void func_02063884(u16 *item, VillagerPostItemList *list);
/* Message arguments of the letters: numbers. */
extern int func_0203d7b0(int index, int value);
extern int func_0203d79c(int index, int value);
extern void func_02066694(MailLetter *letter); /* a letter's constructor */
extern void func_02066688(MailLetter *letter); /* its destructor */
/* The letter written from `npc` to `player`, of message `*text` of the group `name`, on paper
 * `*paper`. */
extern void func_020662bc(MailLetter *letter, const u8 *text, const char *name, const u8 *paper, const NpcId *npc,
                          const DesignCreator *player, int from);
/* The item the letter carries set; the one it had. */
extern u16 func_02065ed0(MailLetter *letter, u16 item, int arg);

/* An item drawn from a copy of `list` (the copy destroyed after). */
static u16 draw_from(const VillagerPostItemList *list)
{
    VillagerPostItemList copy = *list;
    u16 item;
    func_020638d4(&item, &copy, 0, 0, 1, 1, NULL);
    func_02063cc8(&copy);
    return item;
}

/* The `count` lists made once: list i of `kinds[i]` and `groups[i]`, given to the C++ runtime
 * with `records[i]`. */
static void make_lists_once(u32 *guard, VillagerPostItemList *lists, const int *kinds, const int *groups, u8 *const *records,
                            int count)
{
    if ((*guard & 1) != 0) {
        return;
    }
    for (int i = 0; i < count; i++) {
        func_02063ccc(&lists[i], kinds[i], groups[i]);
        __register_global_object(&lists[i], (void *) (uintptr_t) func_02063cc8, records[i]);
    }
    *guard |= 1;
}

/* func_02059e1c: the "re_q10" letter from `npc` to `player`, carrying a present of kind
 * `present` (VILLAGER_POST_PRESENT_FIRST to _LAST; else nothing is sent): 1 drawn from list
 * (0, 0); 2 from one of the lists (0, 1-3); 3 from one of (0, 0), (4, 0), (3, 0); 4 from one
 * of the nine (0, 4 or 3; 1-3); 5 from a list of a drawn kind of data_020cbfe4 for the
 * player's record, or when that gives no item, with the group it gave back. Whether it was
 * sent.
 * QUIRK: two random numbers are drawn and thrown away first. */
int VillagerPost_SendQ10Reply(unsigned int present, const DesignCreator *player, const NpcId *npc)
{
    static const int kinds_2[3] = {0, 0, 0}, groups_2[3] = {1, 2, 3};
    static const int kinds_3[3] = {0, 4, 3}, groups_3[3] = {0, 0, 0};
    static const int kinds_4[9] = {0, 0, 0, 4, 4, 4, 3, 3, 3}, groups_4[9] = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    static u8 *const records_2[3] = {data_021c9650, data_021c962c, data_021c9644};
    static u8 *const records_3[3] = {data_021c9620, data_021c9698, data_021c96b0};
    static u8 *const records_4[9] = {data_021c9608, data_021c9668, data_021c9638, data_021c965c, data_021c9680,
                                     data_021c96bc, data_021c95fc, data_021c9614, data_021c9674};

    if (present < VILLAGER_POST_PRESENT_FIRST || present > VILLAGER_POST_PRESENT_LAST) {
        return 0;
    }
    u16 item = VILLAGER_POST_NO_ITEM;
    func_020644cc(3);
    func_020644cc(3);

    switch (present) {
        case 1: {
            VillagerPostItemList list;
            func_02063ccc(&list, 0, 0);
            func_020638d4(&item, &list, 0, 0, 1, 1, NULL);
            func_02063cc8(&list);
            break;
        }
        case 2:
            make_lists_once(&data_021c95f4, data_021c96ec, kinds_2, groups_2, records_2, 3);
            item = draw_from(&data_021c96ec[func_020644cc(3)]);
            break;
        case 3:
            make_lists_once(&data_021c95f8, data_021c96d4, kinds_3, groups_3, records_3, 3);
            item = draw_from(&data_021c96d4[func_020644cc(3)]);
            break;
        case 4:
            make_lists_once(&data_021c95ec, data_021c972c, kinds_4, groups_4, records_4, 9);
            item = draw_from(&data_021c972c[func_020644cc(9)]);
            break;
        default: {
            u8 *record = PlayerRecords_Find(data_021dc7bc, (const PlayerRecordsId *) (const void *) player);
            int kind = data_020cbfe4[func_020644cc(3)];
            VillagerPostItemList list;
            func_02063ccc(&list, kind, 0);
            VillagerPostItemList copy = list;
            int group;
            func_020638d4(&item, &copy, (int) (uintptr_t) record, 0, 1, 1, &group);
            func_02063cc8(&copy);
            if (item == VILLAGER_POST_NO_ITEM) {
                VillagerPostItemList other;
                func_02063ccc(&other, kind, group);
                func_02063884(&item, &other);
                func_02063cc8(&other);
            }
            func_02063cc8(&list);
            break;
        }
    }
    return VillagerPost_Send(data_020dd3c4, (u8) func_020644cc(VILLAGER_POST_TEXTS), player, npc, &item,
                             VILLAGER_POST_PERSONALITY_PAPER);
}
CLEAN_AS(func_02059e1c, VillagerPost_SendQ10Reply)

/* func_0205a1dc: the "ev_nbirth" letter from `npc` to `player`, with the villager's birthday
 * (month, day) as its numbers, on paper VILLAGER_POST_BIRTHDAY_PAPER; 0 when `npc` is not one
 * of the town's villagers. Whether it was sent. */
int VillagerPost_SendBirthdayNotice(const DesignCreator *player, const NpcId *npc)
{
    u8 *villager = VillagerRoster_Find(&data_021e5a2c, npc);
    if (villager == NULL) {
        return 0;
    }
    func_0203d7b0(VILLAGER_POST_SLOT_MONTH, VillagerData_Birthday(villager)->month);
    func_0203d79c(VILLAGER_POST_SLOT_DAY, VillagerData_Birthday(villager)->day);
    return VillagerPost_Send(data_020dd3cc, (u8) func_020644cc(VILLAGER_POST_TEXTS), player, npc, NULL,
                             VILLAGER_POST_BIRTHDAY_PAPER);
}
CLEAN_AS(func_0205a1dc, VillagerPost_SendBirthdayNotice)

/* func_0205a240: a letter from `npc` to `player`, message `text` of the group `name` of the
 * villager's personality, on paper `paper` (VILLAGER_POST_PERSONALITY_PAPER: its
 * personality's), carrying `*item` when `item` is not NULL; posted, or else held at the post
 * office. Whether either took it (0 when `npc` is not one of the town's villagers).
 * QUIRK: the item is put on the letter even when it is no item (0xfff1). */
int VillagerPost_Send(const char *name, int text, const DesignCreator *player, const NpcId *npc, const u16 *item, int paper)
{
    if (VillagerRoster_Find(&data_021e5a2c, npc) == NULL) {
        return 0;
    }
    NpcId_FormatResourceName(npc, data_021c9704, VILLAGER_POST_NAME_SIZE, name);
    u8 message = (u8) text;
    u8 letter_paper = MomLetters_PaperFromSet(NpcId_Personality(npc));
    if (paper != VILLAGER_POST_PERSONALITY_PAPER) {
        letter_paper = (u8) paper;
    }
    MailLetter letter;
    func_02066694(&letter);
    func_020662bc(&letter, &message, data_021c9704, &letter_paper, npc, player, VILLAGER_POST_FROM_VILLAGER);
    if (item != NULL) {
        func_02065ed0(&letter, *item, 1);
    }
    int sent = Mail_Post(&letter) != 0 || Mail_HoldAtPostOffice(&letter, 0) != 0;
    func_02066688(&letter);
    return sent;
}
CLEAN_AS(func_0205a240, VillagerPost_Send)
