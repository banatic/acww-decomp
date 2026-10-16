/* Items put on the maps while linked (linked_map_items.h). */
#include "linked_map_items.h"

#include "acre_map.h"
#include "acre_tile.h"
#include "clean.h"
#include "link_global.h"
#include "packed_bytes.h"
#include "scene_query.h"
#include "session.h"

/* The session messages: a record put down by the holder, and one asked of it. */
#define LINKED_MAP_ITEMS_MESSAGE_PLACED 18
#define LINKED_MAP_ITEMS_KIND_PLACED 4
#define LINKED_MAP_ITEMS_MESSAGE_ASK 19
#define LINKED_MAP_ITEMS_KIND_ASK 6
/* The layer of the tiles' codes an item goes in. */
#define LINKED_MAP_ITEMS_LAYER 0

extern NetSession *data_020ccf94; /* the session */

/* func_0205f9d4: item `item` put on tile (x, z) of the map of `scene` (`flag` not 0: the
 * tile's bit set, on the town's map), here when this machine holds the scene, else asked of
 * the holder (message 19). */
void LinkedMapItems_Set(unsigned char x, unsigned char z, int scene, int item, int flag)
{
    u8 record[LINKED_MAP_ITEMS_RECORD_SIZE];

    PackedBytes_WriteItem(record, item);
    PackedBytes_JoinScene(&record[2], (u8) scene, flag != 0 ? 1 : 0);
    record[3] = x;
    record[4] = z;
    if (LinkGlobal_HoldsScene()) {
        LinkedMapItems_PlaceAndShare(record);
    } else {
        NetSession *session = data_020ccf94;
        Session_BeginMessage(session);
        Session_AppendMessage(session, record, LINKED_MAP_ITEMS_RECORD_SIZE);
        Session_EndMessage(session, LINKED_MAP_ITEMS_MESSAGE_ASK, LINKED_MAP_ITEMS_KIND_ASK);
    }
}
CLEAN_AS(func_0205f9d4, LinkedMapItems_Set)

/* func_0205fa40: the record put down here, then, when it was and the session is linked, sent
 * on to the others (message 18). */
void LinkedMapItems_PlaceAndShare(u8 *record)
{
    if (LinkedMapItems_Place(record) && Session_IsLinked(data_020ccf94)) {
        NetSession *session = data_020ccf94;
        Session_BeginMessage(session);
        Session_AppendMessage(session, record, LINKED_MAP_ITEMS_RECORD_SIZE);
        Session_EndMessage(session, LINKED_MAP_ITEMS_MESSAGE_PLACED, LINKED_MAP_ITEMS_KIND_PLACED);
    }
}
CLEAN_AS(func_0205fa40, LinkedMapItems_PlaceAndShare)

/* func_0205fa84: the record's item put on its tile: on the town's map for scene 0, the tile's
 * bit then set or cleared by the flag; else on the map of the room numbered by the scene. 1
 * when done, 0 when there is no such map. */
int LinkedMapItems_Place(unsigned char *record)
{
    u16 item = PackedBytes_ReadItem(record);
    u8 scene;
    u8 number;
    PackedBytes_SplitScene(&record[2], &scene, &number);
    int flag = number != 0;
    int x = (s8) record[3];
    int z = (s8) record[4];

    if (SceneQuery_Is0(scene)) {
        AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
        if (town == NULL) {
            return 0;
        }
        AcreTile_SetItem(town, &item, x, z, LINKED_MAP_ITEMS_LAYER);
        if (flag) {
            AcreTile_Mark(town, x, z);
        } else {
            AcreTile_Unmark(town, x, z);
        }
        return 1;
    }
    AcreMap *room = (AcreMap *) (uintptr_t) AcreMap_RoomByNumber(scene);
    if (room == NULL) {
        return 0;
    }
    AcreTile_SetItem(room, &item, x, z, LINKED_MAP_ITEMS_LAYER);
    return 1;
}
CLEAN_AS(func_0205fa84, LinkedMapItems_Place)
