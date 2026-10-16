/* The handlers of session messages (session.h): data_020cd0dc holds one per handler number
 * (a message header's byte 2), SessionMessage_Dispatch calls it with the payload's size, the
 * header's kind, and the sender's scene and slot, after setting the read cursor to the
 * payload; a handler reads the payload with Session_ReadMessage.
 *
 * Handlers 0-19 act on the link state (data_021f4320, next to the session), on the current
 * activity object (func_020a132c), or on items on the town map; handlers 52-63 change one of
 * the villagers (data_021e5a2c, eight entries of 0x7ec bytes, func_0207cec0) or an entry of
 * one (func_020807c0), their payload naming the villager in its high nibble. */
#ifndef CLEAN_MAIN_SESSION_MESSAGE_H
#define CLEAN_MAIN_SESSION_MESSAGE_H

#include "types.h"

void SessionMessage_Dispatch(int handler, const u8 *payload, int size, int kind, u8 scene, u32 slot);

void SessionMessage_SetSenderStatus(u32 size, u32 kind, u32 scene, u32 slot);        /* 0 */
void SessionMessage_SetOwnStatus(int size, int kind, u8 scene, u32 slot);            /* 1 */
void SessionMessage_SetActivityPlayerEB(int size, int kind, u8 scene, u32 slot);     /* 2 */
void SessionMessage_SetActivityFlagF3(int size, int kind, u8 scene, u32 slot);       /* 3 */
void SessionMessage_SetActivityPlayerE7(int size, int kind, int scene, int slot);    /* 4 */
void SessionMessage_RemovePlayer(int size, int kind, u8 scene, u32 slot);            /* 5 */
void SessionMessage_SetActivityPlayerF4(int size, int kind, int scene, int slot);    /* 6 */
void SessionMessage_SetActivityFlagE6(int size, int kind, u8 scene, u32 slot);       /* 7 */
void SessionMessage_AddLinkPair(int size, int kind, int scene, int slot);            /* 8 */
void SessionMessage_SetLinkEntry(int size, int kind, u8 scene, u32 slot);            /* 9 */
void SessionMessage_SetLinkWord2C(int size, int kind, int scene, int slot);          /* 10 */
void SessionMessage_SetLinkEntry3C(int size, int kind, int scene, int slot);         /* 11 */
void SessionMessage_SetLinkStatusBits(int size, int kind, int scene, int slot);      /* 12 */
void SessionMessage_SetLinkSlotFlag68(int size, int kind, u8 scene, u32 slot);       /* 13 */
void SessionMessage_SetLinkWord74(int size, int kind, u8 scene, u32 slot);           /* 14 */
void SessionMessage_ReceiveBundle15(int size, int kind, u8 scene, u32 slot);         /* 15 */
void SessionMessage_ReceiveBundle16(int size, int kind, u8 scene, u32 slot);         /* 16 */
void SessionMessage_SetLinkFlag7C(int size, int kind, u8 scene, u32 slot);           /* 17 */
void SessionMessage_PlaceTownItems(u32 size, int kind, u8 scene, u32 slot);          /* 18 */
void SessionMessage_RelayTownItems(u32 size, int kind, u8 scene, u32 slot);          /* 19 */
void SessionMessage_ReceiveAnswer(int size, int kind, u8 scene, u32 slot);           /* 52 */
void SessionMessage_ReceiveRequest(int size, int kind, u8 scene, u32 slot);          /* 53 */
void SessionMessage_SetVillagerEntrySender(int size, int kind, int scene, int slot); /* 54 */
void SessionMessage_FillVillagerEntry(int size, int kind, int scene, int slot);      /* 55 */
void SessionMessage_SetVillagerEntryByte6D(int size, int kind, u8 scene, u32 slot);  /* 56 */
void SessionMessage_SetVillagerEntryByte6C(int size, int kind, u8 scene, u32 slot);  /* 57 */
void SessionMessage_SetVillagerItem7D2(int size, int kind, u8 scene, u32 slot);      /* 58 */
void SessionMessage_SetVillagerItems7B0(int size, int kind, u8 scene, u32 slot);     /* 59 */
void SessionMessage_ChangeVillagerObject(int size, int kind, u8 scene, u32 slot);    /* 60 */
void SessionMessage_SetVillagerObject(int size, int kind, u8 scene, u32 slot);       /* 61 */
void SessionMessage_SetVillagerEntryItem(int size, int kind, u8 scene, u32 slot);    /* 62 */
void SessionMessage_SetVillagerObjectItem(int size, int kind, u8 scene, u32 slot);   /* 63 */

#endif
