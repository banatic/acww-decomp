/* Letters a villager writes to a player (villager_letter.h). */
#include "villager_letter.h"

#include "clean.h"
#include "mail.h"
#include "mom_letters.h"
#include "letter.h"
#include "main_random.h"
#include "player_id.h"

/* The text slot (func_0203d7c4) func_020662bc and func_02066228 put the villager's name in;
 * 11 would leave it out. */
#define VILLAGER_LETTER_FROM_VILLAGER 1

/* The buffers the group names of the two kinds of letter are formatted into. */
extern char data_021d1380[VILLAGER_LETTER_NAME_SIZE];
extern char data_021d1358[VILLAGER_LETTER_NAME_SIZE];

/* The item put on the letter, when there is one, and the letter held at the post office; it is
 * destroyed after. Whether it was held. */
static int post_letter(Letter *letter, const u16 *item)
{
    if (item != NULL && *item != VILLAGER_LETTER_NO_ITEM) {
        Letter_SetItem(letter, *item, 1);
    }
    int held = Mail_HoldAtPostOffice(letter, 0) != 0;
    Letter_Destruct(letter);
    return held;
}

/* func_0207d33c: a letter from the villager `npc` to `player` (a player id), message `text` of
 * the group `name` of its personality, carrying `item` when it is not NULL nor no item; whether
 * the post office took it (0 too when the player id is not set or `npc` is not valid). */
int VillagerLetter_Post(const char *name, int text, const void *player, const NpcId *npc, const u16 *item)
{
    if (PlayerId_IsSet((DesignCreator *) player) == 0 || !NpcId_IsValid(npc)) {
        return 0;
    }
    Letter letter;
    Letter_Construct(&letter);
    u8 paper = MomLetters_PaperFromSet(NpcId_Personality(npc));
    NpcId_FormatResourceName(npc, data_021d1380, VILLAGER_LETTER_NAME_SIZE, name);
    u8 message = (u8) text;
    Letter_WriteVillagerToPlayer(&letter, &message, data_021d1380, &paper, npc, player, VILLAGER_LETTER_FROM_VILLAGER);
    return post_letter(&letter, item);
}
CLEAN_AS(func_0207d33c, VillagerLetter_Post)

/* func_0207d3dc: the same, of four parts each drawn from `first` to `first + choices - 1`. */
int VillagerLetter_PostDrawn(const char *name, int first, int choices, const void *player, const NpcId *npc, const u16 *item)
{
    if (PlayerId_IsSet((DesignCreator *) player) == 0 || !NpcId_IsValid(npc)) {
        return 0;
    }
    Letter letter;
    Letter_Construct(&letter);
    u8 paper = MomLetters_PaperFromSet(NpcId_Personality(npc));
    u8 parts[VILLAGER_LETTER_PARTS];
    for (int i = 0; i < VILLAGER_LETTER_PARTS; i++) {
        parts[i] = (u8) (first + (int) MainRandom_Below(choices));
    }
    NpcId_FormatResourceName(npc, data_021d1358, VILLAGER_LETTER_NAME_SIZE, name);
    Letter_WriteVillagerToPlayerZ(&letter, &parts[0], &parts[1], &parts[2], &parts[3], data_021d1358, &paper, npc, player,
                                  VILLAGER_LETTER_FROM_VILLAGER);
    return post_letter(&letter, item);
}
CLEAN_AS(func_0207d3dc, VillagerLetter_PostDrawn)
