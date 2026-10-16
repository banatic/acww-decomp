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

/* A pending change carried in a session message as 2 bytes: byte 0 the scene in bits 0-5,
 * holder in bit 6 and moving in bit 7 (PackedBytes_JoinScene); byte 1 the fields marked in
 * bits 0-5 and the slot it is for in bits 6-7. */
void LinkPart_GetChange(const LinkStatePlaceChange *change, u8 *scene, u8 *holder, u8 *moving, u32 *mask);
void LinkPart_AddChange(LinkStatePlaceChange *change, u8 scene, u8 holder, u8 moving, u32 mask);
void LinkPart_EndChange(LinkStatePlaceChange *change);
LinkStatePlaceChange *LinkPart_MakeChange(LinkStatePlaceChange *change);

void LinkPart_ReadEntry(const u8 *entry, s32 *slot, u8 *scene, u8 *holder, u8 *moving, s32 *mask);
void LinkPart_WriteEntry(u8 *entry, int slot, int scene, int holder, u8 moving, int mask);
u8 *LinkPart_EndEntry(u8 *entry);
u8 *LinkPart_MakeEntry(u8 *entry);
void LinkPart_ReadEntryChange(const u8 *entry, u8 *scene, u8 *holder, u8 *moving, s32 *mask);
void LinkPart_WriteEntryChange(u8 *entry, int scene, int holder, int moving, int mask);
u8 *LinkPart_EndEntryB(u8 *entry);
u8 *LinkPart_MakeEntryB(u8 *entry);
void LinkPart_UnpackEntry(const u8 *entry, s32 *slot, u8 *scene, u8 *holder, u8 *moving, s32 *mask);
void LinkPart_PackEntry(u8 *entry, int slot, int scene, int holder, u8 moving, int mask);
void LinkPart_EndEntryBytes(void);
void LinkPart_MakeEntryBytes(void);

/* A one-byte value of a session message (the byte a link pair takes). */
void LinkPart_CopyByte(const u8 *src, u8 *dst);
void LinkPart_SetByte(u8 *value, int byte);
void LinkPart_EndByte(u8 *value);
void LinkPart_MakeByte(u8 *value);

#endif
