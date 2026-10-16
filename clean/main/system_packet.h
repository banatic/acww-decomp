/* The handlers of system packets (session_link.h): data_020ccff0 holds one per kind 0-23 and
 * Session_OnReceived calls it with the packet's payload (after its first byte), the payload's
 * length and the sender's AID.
 *
 * Several handlers act on the current activity object (func_020a132c, data_021f3c3c), only in
 * the scenes it belongs to, setting one of its flags; others write data into this system's
 * records or the session's shared records at an offset the payload starts with.
 *
 * Each kind has a sender that builds the packet in the share block (Session_GetSendBlock(s, 4))
 * and sends it to the AIDs of a mask (bit n for AID n; 1 is the host) once every peer in the
 * mask has a credit. Data longer than a packet goes in chunks of SYSTEM_PACKET_CHUNK bytes
 * (SystemPacket_SendInChunks): each chunk is its offset (4 bytes) and its bytes, and the caller
 * keeps the count of chunks sent and calls again until it returns 1. */
#ifndef CLEAN_MAIN_SYSTEM_PACKET_H
#define CLEAN_MAIN_SYSTEM_PACKET_H

#include "types.h"

typedef void SystemPacketHandler(u8 *payload, u32 length, int sender);

#define SYSTEM_PACKET_CHUNK 0xffb /* the data bytes of a chunk: a block less the kind and the offset */

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
void SystemPacket_SetOwnBlock(u8 *payload, u32 length, int sender);          /* kind 3 */
void SystemPacket_WriteSlotBlock(u8 *payload, u32 length, int sender);       /* kind 2 */
void SystemPacket_WriteActivityBuffer(u8 *payload, u32 length, int sender);  /* kind 1 */
void SystemPacket_SetActivityMembers(u8 *payload, u32 length, int sender);   /* kind 0 */

int SystemPacket_SendActivityFlag101(void);                                                                    /* kind 23 */
int SystemPacket_SendRecordBlock(u8 *chunks_sent);                                                             /* kind 22 */
int SystemPacket_SendOwnRecord(u8 *chunks_sent);                                                               /* kind 21 */
int SystemPacket_SendActivityPlayer100(void);                                                                  /* kind 20 */
int SystemPacket_SendActivityPlayerF4(void);                                                                   /* kind 19 */
int SystemPacket_SendActivityFlagE5(int to);                                                                   /* kind 18 */
int SystemPacket_SendActivityPlayerFC(void);                                                                   /* kind 17 */
int SystemPacket_SendActivityPlayerF8(void);                                                                   /* kind 16 */
int SystemPacket_SendLinkEntries(int slot);                                                                    /* kind 15 */
int SystemPacket_SendActivityPlayerEF(int value, int to);                                                      /* kind 14 */
int SystemPacket_SendSharedRecords(u8 *chunks_sent, int to);                                                   /* kind 12 */
int SystemPacket_SendActivityFlagE4(int to);                                                                   /* kind 11 */
int SystemPacket_SendDateTime(int to);                                                                         /* kind 10 */
int SystemPacket_SendActivityFlagD9(void);                                                                     /* kind 9 */
int SystemPacket_SendModeRequest(void);                                                                        /* kind 8 */
int SystemPacket_SendLinkFlagC4(void);                                                                         /* kind 7 */
int SystemPacket_SendSenderBlock(u8 *chunks_sent, u32 to);                                                     /* kind 4 */
int SystemPacket_SendSlotBlocks(int content1, int block1, int content2, int block2, int content3, int block3); /* kind 3 */
int SystemPacket_SendOwnBlock(u8 *chunks_sent);                                                                /* kind 2 */
int SystemPacket_SendActivityBuffer(u8 *chunks_sent, int to);                                                  /* kind 1 */
int SystemPacket_SendActivityMembers(int to);                                                                  /* kind 0 */
int SystemPacket_SendShareData(int to);
int SystemPacket_SendInChunks(u8 *chunks_sent, const u8 *data, u32 size, int kind, u16 to);

#endif
