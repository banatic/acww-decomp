/* How a tile request (tile_requests.h) is granted or refused. TileRequestGrant_Submit checks a
 * new request against the scene's map and the changes under way (tile_changes.h). Not linked,
 * it carries the request out at once through func_02046024 (and the drops of
 * TileRequestGrant_Drops); linked, the system holding the scene answers it
 * (TileRequestGrant_Answer) and any other sends it there as session message 49
 * (TileRequestMessage).
 *
 * The holder's answer, session message 50 (TileRequestAnswer), goes to every system: the asker
 * notes it in its request slot and carries it out, the others carry it out too, or only put
 * its items on the map of the scene it was asked in when it is not theirs.
 *
 * The drops: a growth line code that is grown (kinds 1 and 6) drops up to three items on the
 * tiles around it (two for 0xcc); 0x66-0x6c one, a bag of bells for 0x68 and 0x6c, else an item
 * func_020638d4 draws. Their tiles go back in the answer. */
#ifndef CLEAN_MAIN_TILE_REQUEST_GRANT_H
#define CLEAN_MAIN_TILE_REQUEST_GRANT_H

#include "acre_map.h"
#include "tile_requests.h"
#include "types.h"

/* A request sent to the system holding the scene (8 bytes). */
typedef struct TileRequestMessage {
    u8 who;   /* bits 0-1: the asker's TileRequest.player; 2-3: its request slot; 4-5: unk_1d; 6-7 not set */
    u8 what;  /* bits 0-4: the kind; 5-6: TileRequest.unk_20; 7: the layer */
    u16 tile; /* 0x02: x in the high byte, z in the low */
    u16 code; /* 0x04: the tile's code */
    u16 item; /* 0x06 */
} TileRequestMessage;

#define TILE_REQUEST_MESSAGE_KIND_MASK 0x1f

/* The holder's answer (14 bytes); TileRequestsActionMessage is its first 12. */
typedef struct TileRequestAnswer {
    u8 who;             /* bit 0: the extra tiles are set; 1-2: the asker's slot; 3-7: the kind */
    u8 what;            /* bits 0-1: the request slot; 2: granted; 3-4: unk_1d; 5-6: unk_20; 7: the layer */
    u16 tile;           /* 0x02 */
    u16 item;           /* 0x04 */
    u16 extra_tiles[3]; /* 0x06: where the drops went, 0xffff for none */
    u16 extra_item;     /* 0x0c: the item dropped */
} TileRequestAnswer;

#define TILE_REQUEST_ANSWER_EXTRAS 0x01
#define TILE_REQUEST_ANSWER_GRANTED 0x04
#define TILE_REQUEST_ANSWER_SIZE 14
#define TILE_REQUEST_ANSWER_SHORT 6 /* without the extra tiles */

void TileRequestGrant_ReceiveAnswer(const TileRequestAnswer *answer, int scene);
void TileRequestGrant_PutOnScene(const TileRequestAnswer *answer, int scene);
void TileRequestGrant_LetGo(const TileRequestAnswer *answer);
void TileRequestGrant_Apply(const TileRequestAnswer *answer);
void TileRequestGrant_Answer(const TileRequestMessage *request, int granted, int slot);
int TileRequestGrant_Drops(TileRequestAnswer *answer, const TileRequestMessage *request, int slot);
void TileRequestGrant_DropOne(TileRequestAnswer *answer, const TileRequestMessage *request, int slot);
void TileRequestGrant_DropMany(TileRequestAnswer *answer, int slot, int code);
u16 TileRequestGrant_DropItemOf(int unused, int code);
int TileRequestGrant_FindDropTile(void *unused, TileRequestTile *tile, int index, AcreMap *town);
void TileRequestGrant_Submit(u8 index, int unk_20);
int TileRequestGrant_Prepare(TileRequestMessage *message, const TileRequest *request);
int TileRequestGrant_TileFree(int index, const TileRequestTile *tile);
int TileRequestGrant_NoOtherNear(const TileRequestTile *tile);
int TileRequestGrant_NoOtherNearFor(const TileRequestTile *tile, int slot);
int TileRequestGrant_NoOneNear(const TileRequestTile *tile, int skip);

#endif
