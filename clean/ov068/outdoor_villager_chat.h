/* Behaviour 9 of a villager out walking in the town (its behaviour member at 0x8b8,
 * outdoor_villager.h): paired with another villager (OutdoorVillager_Pair, the partner at its
 * word 0x644), the two chat, and the chat may end with one of seven exchanges.
 *
 * Its start turns the villager to its partner with the watch on the partner (kind 2). Its
 * update's steps (a table of member pointers filled once, as outdoor_villager_acts.h says):
 * - 0: once the turn is done it stands and the chat lasts by the pair's tier (the wait from
 *   data_ov068_022767b8: 240, 160, 100, 60, 60 frames; 100 past the table); while turning,
 *   the byte at 0xa05 parts the pair and starts behaviour 19.
 * - 1, the chat: both play acts of the table data_ov068_0227679c now and then while the wait
 *   runs; the byte at 0xa05 parts the pair (behaviour 19). It ends early (step 3) when this
 *   console's player comes within 0x6000 of the pair and is unknown to one of them (a stranger
 *   breaks it up), when the pair gets on badly (tier 4) with the player that near (both
 *   moods then asked for 2), or when they are no longer within 0x3c00 of each other. At the
 *   end of the wait, once both are ready, with a current player record an exchange is chosen;
 *   without one, one time in two both moods are asked for from data_ov068_02276740, and it
 *   ends.
 * - 2: once the speaker's motion of kind 20 (it shows a held item, SceneMotion_RequestKind20)
 *   is done, both moods applied.
 * - 3: the partner told the pairing ends (its vtable slot 0xbc, OutdoorVillager_Unpair); when
 *   it agrees, this one is unpaired too, resumes its saved behaviour (else 0) and its
 *   pairing's cooldown starts.
 *
 * The exchanges are tried in random order by weight (data_ov068_02276794: 15, 10, 15, 20, 10,
 * 15, 15 of 100) until one happens; each first sorts the pair into a first and a second
 * (func_ov068_0226aca8: the first is the one fonder of the current player, either at random
 * when they are as fond, the villager itself without a player) and the second learns from
 * the first (VillagerMode_LearnFrom, VillagerMemory_ShareNickname). The two of them outside these files talk about how the pair
 * gets on, or only learn; the five here: the first's catchphrase passed on (to the second, or
 * when the second already says it, to another villager of the town who does not), the first's
 * design passed on (the same way: the second shows it), the first's clothes and its item of
 * 0x1380 to 0x139f back to its own defaults, the second's catchphrase back to its own default,
 * and the first given a new design of data_021ed278's eight (it shows it). */
#ifndef CLEAN_OV068_OUTDOOR_VILLAGER_CHAT_H
#define CLEAN_OV068_OUTDOOR_VILLAGER_CHAT_H

#include "outdoor_villager.h"
#include "types.h"

int OutdoorVillagerChat_Update9(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerChat_End9(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerChat_Show9(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerChat_Exchange(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerChat_Talk9(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerChat_BadPairNear(OutdoorVillagerBehaviour *self, u8 *villager, int distance);
int OutdoorVillagerChat_StrangerNear(OutdoorVillagerBehaviour *self, u8 *villager, int distance);
int OutdoorVillagerChat_PlayerDistance(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerChat_PartnerClose(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerChat_Turn9(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerChat_Start9(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerChat_NewDesign(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerChat_DefaultCatchphrase(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerChat_DefaultClothes(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerChat_PassDesign(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerChat_PassCatchphrase(OutdoorVillagerBehaviour *self, u8 *villager);

#endif
