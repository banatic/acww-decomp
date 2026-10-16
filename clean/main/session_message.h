/* The handlers of session messages (session.h): data_020cd0dc holds one per handler number
 * (a message header's byte 2), SessionMessage_Dispatch calls it with the payload's size, the
 * header's kind, and the sender's scene and slot, after setting the read cursor to the
 * payload; a handler reads the payload with Session_ReadMessage.
 *
 * Handlers 0-19 act on the link state (data_021f4320, next to the session), on the current
 * activity object (func_020a132c), or on items on the town map; handlers 52-63 change one of
 * the villagers (data_021e5a2c, eight entries of 0x7ec bytes, func_0207cec0) or an entry of
 * one (func_020807c0), their payload naming the villager in its high nibble.
 *
 * Handlers 20-51 read their payload and hand it on: to Design_Receive (21), to
 * PlayerMessages_Dispatch (22), to the sender's player record (func_020984fc; 43, 44, 46), to
 * overlay 3's objects (40, 41, 47, 48), and to other code of the game, some of which answers
 * with a message of its own: 30 with 31 or 32, 38 with 39, 40 with 41, 49 with 50 and 51 with
 * 52. */
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
void SessionMessage_Handle20(int size, int kind, u8 scene, u32 slot);                /* 20 */
void SessionMessage_ReceiveDesign(int size, int kind, u8 scene, u32 slot);           /* 21 */
void SessionMessage_ReceivePlayerMessage(int size, int kind, u8 scene, u32 slot);    /* 22 */
void SessionMessage_Handle23(int size, int kind, u8 scene, u32 slot);                /* 23 */
void SessionMessage_Handle24(int size, int kind, u8 scene, u32 slot);                /* 24 */
void SessionMessage_Handle25(int size, int kind, u8 scene, u32 slot);                /* 25 */
void SessionMessage_Handle26(int size, int kind, int scene, u32 slot);               /* 26 */
void SessionMessage_Handle27(int size, int kind, int scene, u32 slot);               /* 27 */
void SessionMessage_Handle28(int size, int kind, int scene, u32 slot);               /* 28 */
void SessionMessage_Handle29(u32 size, int kind, u8 scene, u32 slot);                /* 29 */
void SessionMessage_Handle30(int size, int kind, int scene, int slot);               /* 30 */
void SessionMessage_Handle31(int size, int kind, u8 scene, u32 slot);                /* 31 */
void SessionMessage_Handle32(int size, int kind, u8 scene, u32 slot);                /* 32 */
void SessionMessage_Handle33(int size, int kind, int scene, int slot);               /* 33 */
void SessionMessage_Handle34(int size, int kind, u8 scene, u32 slot);                /* 34 */
void SessionMessage_Handle35(u32 size, u32 kind, u32 scene, u32 slot);               /* 35 */
void SessionMessage_Handle36(int size, int kind, int scene, int slot);               /* 36 */
void SessionMessage_Handle37(int size, int kind, u8 scene, u32 slot);                /* 37 */
void SessionMessage_Handle38(int size, int kind, u8 scene, u32 slot);                /* 38 */
int SessionMessage_Handle39(int size, int kind, int scene, int slot);                /* 39 */
void SessionMessage_Handle40(int size, int kind, int scene, int slot);               /* 40 */
void SessionMessage_Handle41(int size, int kind, u8 scene, u32 slot);                /* 41 */
void SessionMessage_Handle42(int size, int kind, int scene, int slot);               /* 42 */
void SessionMessage_Handle43(int size, int kind, int scene, int slot);               /* 43 */
void SessionMessage_Handle44(int size, int kind, int scene, int slot);               /* 44 */
void SessionMessage_Handle45(int size, int kind, u8 scene, u32 slot);                /* 45 */
void SessionMessage_Handle46(int size, int kind, int scene, int slot);               /* 46 */
void SessionMessage_Handle47(int size, int kind, u8 scene, u32 slot);                /* 47 */
void SessionMessage_Handle48(int size, int kind, u8 scene, u32 slot);                /* 48 */
void SessionMessage_Handle49(int size, int kind, int scene, int slot);               /* 49 */
void SessionMessage_Handle50(int size, int kind, int scene, u32 slot);               /* 50 */
void SessionMessage_Handle51(int size, int kind, int scene, int slot);               /* 51 */
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
