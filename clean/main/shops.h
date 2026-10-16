/* The town's shops as the players share them: Nook's store (data_021f395c, whose first word is
 * what has been spent there, capped by its level), the list of six items at data_021f3b44 that
 * Design reads (design.c) and the list at data_021f3b30 that the fox's
 * scene reads (ov003/fox.c).
 *
 * func_020adb70 changes a place of one of the three (`mode` 0 Nook's store, 1 data_021f3b44,
 * 2 data_021f3b30); while linked to other systems it also sends them the change as message 38,
 * a word: the place in bits 0-5 (63 for none: only an amount spent at Nook's), the amount in
 * bits 6-24, a flag in bit 25 and the shop's kind in bits 26-31. A system that gets message 38
 * applies it (Shops_ApplyMessage) and answers with message 39; the sender counts the answers in
 * data_021f49ec (Shops_CountAnswer) and waits for all (Shops_AllAnsweredA, Shops_AllAnsweredB).
 *
 * What some of these do is only known from where they are called; the names say what the code
 * does. */
#ifndef CLEAN_MAIN_SHOPS_H
#define CLEAN_MAIN_SHOPS_H

#include "types.h"

/* The place of a message 38 that is no place. */
#define SHOPS_NO_PLACE 0x3f

/* Shop kinds in message 38 that are not Nook's store. */
#define SHOPS_KIND_LIST_A 10 /* data_021f3b44 */
#define SHOPS_KIND_LIST_B 15 /* data_021f3b30 */

void Shops_ApplyPending(void);
void Shops_SetPendingState(int state);
int Shops_PendingState(void);
int Shops_IsHour8To22(void);
void Shops_PickRandomItem(u16 *out);
int Shops_CountAnswer(int slot);
void Shops_ApplyMessage(const u32 *payload, int slot);
int Shops_AllAnsweredA(void);
void Shops_TakeFromListB(int a, int b, int kind);
void Shops_SetListBPlace(int place, int kind, int send, int g);
int Shops_AllAnsweredB(void);
void Shops_TakeFromListA(int a, int b, int kind);
int Shops_MailNookItem(const u16 *item);
int Shops_CanMail(void);
int Shops_AllAnsweredC(void);
void Shops_TakeFromStore(void *a, void *b, int amount, int kind);
void Shops_SpendAtStore(int spent);
void Shops_ChangePlace(int place, int amount, int kind, int flag, int mode, u8 send, int g);

#endif
