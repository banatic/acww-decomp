/* The small parts of the link state (link_state.h): a status byte, a slot's arrived word, a
 * move asked of the host, a slot's place and a pending change of it. Each has a constructor
 * and a destructor the link state's arrays use (LinkState_Construct, LinkState_Destruct).
 *
 * A status byte (the session message of handler 0xc, link_state.h) holds an answer in bits
 * 0-2, the slot served in bits 3-4 and the kind in bits 5-7. */
#ifndef CLEAN_MAIN_LINK_PARTS_H
#define CLEAN_MAIN_LINK_PARTS_H

#include "link_state.h"
#include "types.h"

void LinkPart_UnpackStatusByte(const u8 *byte, u32 *answer, u32 *kind, u32 *slot);
void LinkPart_PackStatusByte(u8 *byte, int answer, int kind, int slot);
void LinkPart_EndStatusByte(u8 *byte);
void LinkPart_MakeStatusByte(u8 *byte);

void LinkPart_ClearArrived(u32 *arrived);
void LinkPart_GetArrived(const u32 *arrived, u32 *value);
void LinkPart_SetArrived(u32 *arrived, int value);
void LinkPart_EndArrived(u32 *arrived);
u32 *LinkPart_MakeArrived(u32 *arrived);

void LinkPart_ResetMove(LinkStateMove *move);
void LinkPart_GetMove(const LinkStateMove *move, s32 *slot, u8 *scene);
void LinkPart_SetMove(LinkStateMove *move, int slot, int scene);
void LinkPart_EndMove(LinkStateMove *move);
LinkStateMove *LinkPart_MakeMove(LinkStateMove *move);

void LinkPart_ResetPlace(LinkStatePlace *place);
void LinkPart_GetPlace(const LinkStatePlace *place, u8 *scene, u8 *holder, u8 *moving);
void LinkPart_SetPlace(LinkStatePlace *place, int scene, int holder, int moving);
void LinkPart_EndPlace(LinkStatePlace *place);
LinkStatePlace *LinkPart_MakePlace(LinkStatePlace *place);

void LinkPart_ResetChange(LinkStatePlaceChange *change);

#endif
