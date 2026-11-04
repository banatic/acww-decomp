/* The town's mystery cat record: Blanca's (the faceless cat's, ov074/mystery_cat.h) face, a
 * design, and the impression she took, sent to and fetched from Nintendo's gamestats server
 * over the Nintendo Wi-Fi Connection (0x238 bytes; the state block's copy is data_021f3278,
 * the one fetched data_021f40a4, wfc_session.h): its last bytes hold a checksum that makes its
 * halfwords sum to 0, a status and the impression. */
#ifndef CLEAN_MAIN_MYSTERY_CAT_RECORD_H
#define CLEAN_MAIN_MYSTERY_CAT_RECORD_H

#include "types.h"

#define MYSTERY_CAT_RECORD_SIZE 0x238

/* The status (byte 0x236). */
enum MysteryCatRecordStatus {
    MYSTERY_CAT_RECORD_NONE = 0,     /* to be fetched */
    MYSTERY_CAT_RECORD_RECEIVED = 1, /* fetched and checked (WfcSession_ApplyCatRecord) */
    MYSTERY_CAT_RECORD_IN_USE = 2,   /* received, and the date has moved on since (func_0204714c) */
    MYSTERY_CAT_RECORD_TO_SEND = 3,  /* to be sent */
};

typedef struct MysteryCatRecord {
    u8 data[0x234]; /* 0x000 */
    u16 checksum;   /* 0x234 */
    u8 status;      /* 0x236: enum MysteryCatRecordStatus */
    u8 impression;  /* 0x237: the impression Blanca took (overlay 74) */
} MysteryCatRecord;

u16 MysteryCatRecord_Checksum(const MysteryCatRecord *record);
void MysteryCatRecord_SetChecksum(MysteryCatRecord *record, u16 checksum);
int MysteryCatRecord_IsInUse(const MysteryCatRecord *record);
u8 MysteryCatRecord_Impression(const MysteryCatRecord *record);

/* The record's first bytes are a design (design.h): a blank one is all colour 15 with
 * palette 0. */
struct Design;

void MysteryCatRecord_SetImpression(MysteryCatRecord *record, u8 value);
u8 MysteryCatRecord_Status(const MysteryCatRecord *record);
void MysteryCatRecord_SetStatus(MysteryCatRecord *record, u8 status);
struct Design *MysteryCatRecord_Design(MysteryCatRecord *record);
void MysteryCatRecord_ClearDesign(MysteryCatRecord *record);
void MysteryCatRecord_Init(MysteryCatRecord *record);
void MysteryCatRecord_Reset(MysteryCatRecord *record);
MysteryCatRecord *MysteryCatRecord_Destruct(MysteryCatRecord *record);
MysteryCatRecord *MysteryCatRecord_Construct(MysteryCatRecord *record);

#endif
