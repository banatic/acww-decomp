/* Letters a villager writes to a player (villager_letter.h). */
#include "villager_letter.h"

#include "clean.h"
#include "mail.h"
#include "mom_letters.h"

/* The text slot (func_0203d7c4) func_020662bc and func_02066228 put the villager's name in;
 * 11 would leave it out. */
#define VILLAGER_LETTER_FROM_VILLAGER 1

/* The buffers the group names of the two kinds of letter are formatted into. */
extern char data_021d1380[VILLAGER_LETTER_NAME_SIZE];
extern char data_021d1358[VILLAGER_LETTER_NAME_SIZE];

extern int func_020951bc(const void *player);  /* whether the player id is set */
extern void func_02066694(MailLetter *letter); /* a letter's constructor */
extern void func_02066688(MailLetter *letter); /* its destructor */
/* The letter written from `npc` to `player`, of message `*text` of the group `name`, on paper
 * `*paper`. */
extern void func_020662bc(MailLetter *letter, const u8 *text, const char *name, const u8 *paper, const NpcId *npc,
                          const void *player, int from);
/* The same, of the four parts `*part1` to `*part4` of the group `name`. */
extern void func_02066228(MailLetter *letter, const u8 *part1, const u8 *part2, const u8 *part3, const u8 *part4,
                          const char *name, const u8 *paper, const NpcId *npc, const void *player, int from);
/* The item the letter carries (its halfword 0xfc) set; the one it had. */
extern u16 func_02065ed0(MailLetter *letter, u16 item, int arg);
extern unsigned int func_020644cc(int bound); /* a random number below `bound` */

/* The item put on the letter, when there is one, and the letter held at the post office; it is
 * destroyed after. Whether it was held. */
static int send(MailLetter *letter, const u16 *item)
{
    if (item != NULL && *item != VILLAGER_LETTER_NO_ITEM) {
        func_02065ed0(letter, *item, 1);
    }
    int held = Mail_HoldAtPostOffice(letter, 0) != 0;
    func_02066688(letter);
    return held;
}

/* func_0207d33c: a letter from the villager `npc` to `player` (a player id), message `text` of
 * the group `name` of its personality, carrying `item` when it is not NULL nor no item; whether
 * the post office took it (0 too when the player id is not set or `npc` is not valid). */
int VillagerLetter_Post(const char *name, int text, const void *player, const NpcId *npc, const u16 *item)
{
    if (func_020951bc(player) == 0 || !NpcId_IsValid(npc)) {
        return 0;
    }
    MailLetter letter;
    func_02066694(&letter);
    u8 paper = MomLetters_PaperFromSet(NpcId_Personality(npc));
    NpcId_FormatResourceName(npc, data_021d1380, VILLAGER_LETTER_NAME_SIZE, name);
    u8 message = (u8) text;
    func_020662bc(&letter, &message, data_021d1380, &paper, npc, player, VILLAGER_LETTER_FROM_VILLAGER);
    return send(&letter, item);
}
CLEAN_AS(func_0207d33c, VillagerLetter_Post)

/* func_0207d3dc: the same, of four parts each drawn from `first` to `first + choices - 1`. */
int VillagerLetter_PostDrawn(const char *name, int first, int choices, const void *player, const NpcId *npc, const u16 *item)
{
    if (func_020951bc(player) == 0 || !NpcId_IsValid(npc)) {
        return 0;
    }
    MailLetter letter;
    func_02066694(&letter);
    u8 paper = MomLetters_PaperFromSet(NpcId_Personality(npc));
    u8 parts[VILLAGER_LETTER_PARTS];
    for (int i = 0; i < VILLAGER_LETTER_PARTS; i++) {
        parts[i] = (u8) (first + (int) func_020644cc(choices));
    }
    NpcId_FormatResourceName(npc, data_021d1358, VILLAGER_LETTER_NAME_SIZE, name);
    func_02066228(&letter, &parts[0], &parts[1], &parts[2], &parts[3], data_021d1358, &paper, npc, player,
                  VILLAGER_LETTER_FROM_VILLAGER);
    return send(&letter, item);
}
CLEAN_AS(func_0207d3dc, VillagerLetter_PostDrawn)
