/* Letters a villager sends a player through the post (Mail_Post, or the post office when that
 * does not take it), with a paper that can be chosen, and two letters made with it: the
 * "re_q10" letter that carries a present drawn from one of five kinds of item list, and the
 * "ev_nbirth" letter that names the villager's birthday. */
#ifndef CLEAN_MAIN_VILLAGER_POST_H
#define CLEAN_MAIN_VILLAGER_POST_H

#include "design.h"
#include "npc_id.h"
#include "types.h"

/* VillagerPost_Send: the paper of the villager's personality. */
#define VILLAGER_POST_PERSONALITY_PAPER (-1)

/* The kinds of present of VillagerPost_SendQ10Reply. */
#define VILLAGER_POST_PRESENT_FIRST 1
#define VILLAGER_POST_PRESENT_LAST 5

int VillagerPost_SendQ10Reply(unsigned int present, const DesignCreator *player, const NpcId *npc);
int VillagerPost_SendBirthdayNotice(const DesignCreator *player, const NpcId *npc);
int VillagerPost_Send(const char *name, int text, const DesignCreator *player, const NpcId *npc, const u16 *item, int paper);

#endif
