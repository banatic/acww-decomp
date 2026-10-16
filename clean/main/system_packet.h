/* The handlers of system packets (session_link.h): data_020ccff0 holds one per kind 0-23 and
 * Session_OnReceived calls it with the packet's payload (after its first byte), the payload's
 * length and the sender's AID.
 *
 * Several handlers act on the current activity object (func_020a132c, data_021f3c3c), only in
 * the scenes it belongs to, setting one of its flags; others write data into this system's
 * records or the session's shared records at an offset the payload starts with. */
#ifndef CLEAN_MAIN_SYSTEM_PACKET_H
#define CLEAN_MAIN_SYSTEM_PACKET_H

#include "types.h"

typedef void SystemPacketHandler(u8 *payload, u32 length, int sender);

void SystemPacket_Dispatch(u8 *payload, u32 length, int sender, int kind);

void SystemPacket_SetActivityFlag101(u8 *payload, u32 length, int sender);   /* kind 23 */
void SystemPacket_WriteRecordBlock(u8 *payload, u32 length, int sender);     /* kind 22 */
void SystemPacket_WriteOwnRecord(u8 *payload, u32 length, int sender);       /* kind 21 */
void SystemPacket_SetActivityPlayer100(u8 *payload, u32 length, int sender); /* kind 20 */
void SystemPacket_SetActivityPlayerF4(u8 *payload, u32 length, int sender);  /* kind 19 */
void SystemPacket_SetActivityFlagE5(u8 *payload, u32 length, int sender);    /* kind 18 */
void SystemPacket_SetActivityPlayerFC(u8 *payload, u32 length, int sender);  /* kind 17 */
void SystemPacket_SetActivityPlayerF8(u8 *payload, u32 length, int sender);  /* kind 16 */
void SystemPacket_SetLinkEntries(u8 *payload, u32 length, int sender);       /* kind 15 */
void SystemPacket_SetActivityPlayerEF(u8 *payload, u32 length, int sender);  /* kind 14 */
void SystemPacket_RunCommands(u8 *payload, u32 length, int sender);          /* kind 13 */
void SystemPacket_WriteSharedRecords(u8 *payload, u32 length, int sender);   /* kind 12 */
void SystemPacket_SetActivityFlagE4(u8 *payload, u32 length, int sender);    /* kind 11 */
void SystemPacket_SetActivityDataDC(u8 *payload, u32 length, int sender);    /* kind 10 */
void SystemPacket_SetActivityFlagD9(u8 *payload, u32 length, int sender);    /* kind 9 */
void SystemPacket_RequestMode(u8 *payload, u32 length, int sender);          /* kind 8 */
void SystemPacket_SetLinkFlagC4(u8 *payload, u32 length, int sender);        /* kind 7 */
void SystemPacket_SetOwnStatus(u8 *payload, u32 length, int sender);         /* kind 6 */
void SystemPacket_SetSenderStatus(u8 *payload, u32 length, int sender);      /* kind 5 */
void SystemPacket_WriteSenderBlock(u8 *payload, u32 length, int sender);     /* kind 4 */

#endif
