/* The handlers of session messages (session_message.h). */
#include "session_message.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/design.h"
#include "main/packed_bytes.h"
#include "main/player_messages.h"
#include "main/session.h"
#include "main/session_link.h"
#include "main/session_villager.h"
#include "acre_map.h"
#include "acre_tile.h"
#include "activity.h"
#include "fish_disp.h"
#include "item_code.h"
#include "item_info.h"
#include "item_object.h"
#include "link_global.h"
#include "link_parts.h"
#include "link_scene.h"
#include "linked_map_items.h"
#include "object_claim.h"
#include "ov003/town_insect.h"
#include "place_claim.h"
#include "player_actor_ops.h"
#include "player_record.h"
#include "player_records.h"
#include "room_interior.h"
#include "room_object_state.h"
#include "room_sync.h"
#include "scene_claim.h"
#include "scene_query.h"
#include "session_players.h"
#include "shops.h"
#include "tile_changes.h"
#include "tile_request_grant.h"
#include "town_objects.h"
#include "town_villager.h"
#include "villager_items.h"
#include "villager_memories.h"
#include "villager_memory_entry.h"
#include "villager_object.h"
#include "villager_roster.h"
#include "villager_state.h"
#include "villager_status.h"

/* The scene (func_020b65c4) the activity handlers act in. */
#define SCENE_2E 46

#define NO_ITEM 0xfff1 /* an empty item */

/* The item ids SessionMessage_SetVillagerItem7D2 and SessionMessage_SetVillagerObjectItem take. */
#define VILLAGER_ITEM_FIRST 0x11a8
#define VILLAGER_ITEM_LAST 0x12a7
#define OBJECT0_ITEM_FIRST 0x12b0 /* for an object of type 0 */
#define OBJECT0_ITEM_LAST 0x12e7
#define OBJECT1_ITEM_FIRST 0x12e8 /* for an object of type 1 */
#define OBJECT1_ITEM_LAST 0x131f

typedef void SessionMessageHandler(int size, int kind, u8 scene, u32 slot);

extern NetSession *data_020ccf94;                    /* the session */
extern SessionMessageHandler *const data_020cd0dc[]; /* the handlers, by number */
extern u8 data_021e5a2c[];                           /* the villagers (0x7ec bytes each) */
extern const char data_021dc7aa[];

/* func_02076168: hands a message to handler `handler` with its payload as the read cursor.
 * REQUIRES: a handler that the table holds. */
void SessionMessage_Dispatch(int handler, const u8 *payload, int size, int kind, u8 scene, u32 slot)
{
    Session_SetReadCursor(data_020ccf94, payload);
    data_020cd0dc[handler](size, kind, scene, slot);
}
CLEAN_AS(func_02076168, SessionMessage_Dispatch)

/* func_02076540: the sender's link status becomes the payload's byte. */
void SessionMessage_SetSenderStatus(u32 size, u32 kind, u32 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 status;
    Session_ReadMessage(data_020ccf94, &status, 1);
    LinkGlobal_SetStatus((int) slot, status);
}
CLEAN_AS(func_02076540, SessionMessage_SetSenderStatus)

/* func_02076518: this system's link status becomes the payload's byte. */
void SessionMessage_SetOwnStatus(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    u8 status;
    Session_ReadMessage(session, &status, 1);
    LinkGlobal_SetStatus(session->local_slot, status);
}
CLEAN_AS(func_02076518, SessionMessage_SetOwnStatus)

/* func_020764f0 */
void SessionMessage_SetActivityPlayerEB(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    if (SceneQuery_Current() != SCENE_2E) {
        return;
    }
    if (Activity_Current() != NULL) {
        Activity_SetSlotEB(Activity_Current(), (int) slot, 1);
    }
}
CLEAN_AS(func_020764f0, SessionMessage_SetActivityPlayerEB)

/* func_020764cc
 * QUIRK: asks for the activity a second time and does not use the answer; func_020a1210 finds
 * it itself. */
void SessionMessage_SetActivityFlagF3(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    if (SceneQuery_Current() == SCENE_2E && Activity_Current() != NULL) {
        Activity_Current();
        Activity_SetCurrentFlagF3(1);
    }
}
CLEAN_AS(func_020764cc, SessionMessage_SetActivityFlagF3)

/* func_020764a4 */
void SessionMessage_SetActivityPlayerE7(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    if (SceneQuery_Current() == SCENE_2E && Activity_Current() != NULL) {
        Activity_SetSlotE7(Activity_Current(), slot, 1);
    }
}
CLEAN_AS(func_020764a4, SessionMessage_SetActivityPlayerE7)

/* func_02076480: the player in the slot the payload's byte gives leaves. */
void SessionMessage_RemovePlayer(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u8 leaving;
    Session_ReadMessage(data_020ccf94, &leaving, 1);
    Session_RemovePlayer(leaving);
}
CLEAN_AS(func_02076480, SessionMessage_RemovePlayer)

/* func_02076458 */
void SessionMessage_SetActivityPlayerF4(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    if (SceneQuery_Current() == SCENE_2E && Activity_Current() != NULL) {
        Activity_SetSlotAck(Activity_Current(), slot, 1);
    }
}
CLEAN_AS(func_02076458, SessionMessage_SetActivityPlayerF4)

/* func_02076434 */
void SessionMessage_SetActivityFlagE6(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    if (SceneQuery_Current() == SCENE_2E && Activity_Current() != NULL) {
        Activity_SetFlagE6(Activity_Current(), 1);
    }
}
CLEAN_AS(func_02076434, SessionMessage_SetActivityFlagE6)

/* func_020763f4: the sender's slot and the payload's byte go into the link state's first free
 * pair. */
void SessionMessage_AddLinkPair(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 value[2];
    LinkPart_MakeByte(value);
    Session_ReadMessage(data_020ccf94, value, 1);
    LinkPart_CopyByte(&value[0], &value[1]);
    LinkGlobal_QueueMove(slot, value[1]);
    LinkPart_EndByte(value);
}
CLEAN_AS(func_020763f4, SessionMessage_AddLinkPair)

/* func_0207639c: a link state entry (2 bytes) with the slot it is for. */
void SessionMessage_SetLinkEntry(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u8 entry[2];
    int entry_slot;
    u8 byte0;
    u8 byte1;
    u8 byte2;
    int fields;
    LinkPart_MakeEntry(entry);
    Session_ReadMessage(data_020ccf94, entry, 2);
    LinkPart_ReadEntry(entry, (s32 *) &entry_slot, &byte0, &byte1, &byte2, (s32 *) &fields);
    LinkGlobal_SetPlace(entry_slot, byte0, byte1, byte2, fields);
    LinkPart_EndEntry(entry);
}
CLEAN_AS(func_0207639c, SessionMessage_SetLinkEntry)

/* func_02076374: the sender's word 0x2c of the link state becomes the payload's byte. */
void SessionMessage_SetLinkWord2C(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 value;
    Session_ReadMessage(data_020ccf94, &value, 1);
    LinkGlobal_SetArrived(slot, value);
}
CLEAN_AS(func_02076374, SessionMessage_SetLinkWord2C)

/* func_0207631c: the sender's entry from 0x3c of the link state, from 2 bytes. */
void SessionMessage_SetLinkEntry3C(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 entry[2];
    u8 byte0;
    u8 byte1;
    u8 byte2;
    u32 fields;
    LinkPart_MakeEntryB(entry);
    Session_ReadMessage(data_020ccf94, entry, 2);
    LinkPart_ReadEntryChange(entry, &byte0, &byte1, &byte2, (s32 *) &fields);
    LinkGlobal_AddPlaceChange(slot, byte0, byte1, byte2, (int) fields);
    LinkPart_EndEntryB(entry);
}
CLEAN_AS(func_0207631c, SessionMessage_SetLinkEntry3C)

/* func_020762b8: a byte whose bits 0-2 go to the link state's word for the sender's slot (for
 * this system's slot when the sender is slot 0), bits 5-7 to func_020a6f10 and bits 3-4 to
 * func_020a6f34, each of those two only when below 4. */
void SessionMessage_SetLinkStatusBits(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 byte;
    int low;
    int high;
    int middle;
    LinkPart_MakeStatusByte(&byte);
    NetSession *session = data_020ccf94;
    Session_ReadMessage(session, &byte, 1);
    LinkPart_UnpackStatusByte(&byte, (u32 *) &low, (u32 *) &high, (u32 *) &middle);
    if (slot == 0) {
        LinkGlobal_SetAnswer(session->local_slot, low);
    } else {
        LinkGlobal_SetAnswer(slot, low);
    }
    if (high < 4) {
        LinkGlobal_SetKind(high);
    }
    if (middle < 4) {
        LinkGlobal_SetChosen(middle);
    }
    LinkPart_EndStatusByte(&byte);
}
CLEAN_AS(func_020762b8, SessionMessage_SetLinkStatusBits)

/* func_020762ac */
void SessionMessage_SetLinkSlotFlag68(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    LinkScene_GlobalSetAcked((int) slot, 1);
}
CLEAN_AS(func_020762ac, SessionMessage_SetLinkSlotFlag68)

/* func_020762a0: the link state's word 0x74 becomes the sender's slot. */
void SessionMessage_SetLinkWord74(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    LinkScene_GlobalSetStateAsker((int) slot);
}
CLEAN_AS(func_020762a0, SessionMessage_SetLinkWord74)

/* func_0207626c: the category 15 bundle, read whole into its buffer, then taken in. */
void SessionMessage_ReceiveBundle15(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    Session_ReadMessage(session, Session_GetBundle15Buffer(session), size);
    Session_SetBundle15Length(session, size);
    LinkScene_TakeLeftState();
}
CLEAN_AS(func_0207626c, SessionMessage_ReceiveBundle15)

/* func_0207623c: the category 16 bundle, read whole into its buffer. */
void SessionMessage_ReceiveBundle16(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    Session_ReadMessage(session, Session_GetBundle16Buffer(session), size);
    Session_SetBundle16Length(session, size);
}
CLEAN_AS(func_0207623c, SessionMessage_ReceiveBundle16)

/* func_02076230 */
void SessionMessage_SetLinkFlag7C(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    LinkScene_GlobalSetReleased(1);
}
CLEAN_AS(func_02076230, SessionMessage_SetLinkFlag7C)

/* func_020761fc: item records (5 bytes each) put on the town map. */
void SessionMessage_PlaceTownItems(u32 size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    for (u32 done = 0; done < size; done += 5) {
        u8 record[5];
        Session_ReadMessage(session, record, 5);
        LinkedMapItems_Place(record);
    }
}
CLEAN_AS(func_020761fc, SessionMessage_PlaceTownItems)

/* func_02076198: item records (5 bytes each), each put on the town map here or sent on
 * (func_0205f9d4). */
void SessionMessage_RelayTownItems(u32 size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    for (u32 done = 0; done < size; done += 5) {
        u8 record[5];
        u8 item_scene;
        u8 flag;
        Session_ReadMessage(session, record, 5);
        u16 item = PackedBytes_ReadItem(record);
        PackedBytes_SplitScene(&record[2], &item_scene, &flag);
        LinkedMapItems_Set((s8) record[3], (s8) record[4], item_scene, item, flag != 0 ? 1 : 0);
    }
}
CLEAN_AS(func_02076198, SessionMessage_RelayTownItems)

/* func_02076aa0: the answer (a byte) to message 53. */
void SessionMessage_ReceiveAnswer(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u8 answer;
    Session_ReadMessage(data_020ccf94, &answer, 1);
    SceneClaim_ReceiveAnswer(&answer);
}
CLEAN_AS(func_02076aa0, SessionMessage_ReceiveAnswer)

/* func_02076a78: the request (a byte) of message 53, with the sender's slot. */
void SessionMessage_ReceiveRequest(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 request;
    Session_ReadMessage(data_020ccf94, &request, 1);
    SceneClaim_ReceiveRelease(&request, (int) slot);
}
CLEAN_AS(func_02076a78, SessionMessage_ReceiveRequest)

/* The entry of a villager that a payload byte names, or NULL. */
static u8 *session_message_villager_entry(const u8 *byte)
{
    int villager;
    int entry;
    SessionVillager_UnpackEntry(&villager, &entry, byte);
    u8 *record = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, villager);
    if (record == NULL) {
        return NULL;
    }
    return (u8 *) VillagerMemory_At(record, entry);
}

/* func_02076a18: the entry the payload names gets the sender's name (func_02081e94).
 * REQUIRES: size <= 4 (the payload is one byte, SessionVillager_SendEntrySenderByIndex); the original
 * reads it into a 4-byte variable. */
void SessionMessage_SetVillagerEntrySender(int size, int kind, int scene, int slot)
{
    (void) kind;
    (void) scene;
    u8 bytes[4];
    Session_ReadMessage(data_020ccf94, bytes, size);
    u8 *entry = session_message_villager_entry(bytes);
    if (entry != NULL) {
        u8 *name = (u8 *) PlayerRecord_Player(PlayerRecords_OfPlayer(slot));
        VillagerMemoryEntry_Take((VillagerMemory *) (void *) entry, (const DesignCreator *) (void *) name,
                                 (const NpcIdHead *) (void *) data_021dc7aa, NULL);
    }
}
CLEAN_AS(func_02076a18, SessionMessage_SetVillagerEntrySender)

/* func_020769b8: the entry the payload names is filled with the sender's name
 * (func_02081e14).
 * REQUIRES: size <= 4 (the payload is one byte, SessionVillager_SendEntryFillByIndex); the original
 * reads it into a 4-byte variable. */
void SessionMessage_FillVillagerEntry(int size, int kind, int scene, int slot)
{
    (void) kind;
    (void) scene;
    u8 bytes[4];
    Session_ReadMessage(data_020ccf94, bytes, size);
    u8 *entry = session_message_villager_entry(bytes);
    if (entry != NULL) {
        u8 *name = (u8 *) PlayerRecord_Player(PlayerRecords_OfPlayer(slot));
        VillagerMemoryEntry_Update((VillagerMemory *) (void *) entry, (const DesignCreator *) (void *) name,
                                   (const NpcIdHead *) (void *) data_021dc7aa, NULL);
    }
}
CLEAN_AS(func_020769b8, SessionMessage_FillVillagerEntry)

/* func_0207695c: the entry the first byte names gets the second byte as its byte 0x6d; the
 * second byte is read only when the entry exists. */
void SessionMessage_SetVillagerEntryByte6D(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    u8 bytes[2];
    Session_ReadMessage(session, &bytes[0], 1);
    u8 *entry = session_message_villager_entry(&bytes[0]);
    if (entry != NULL) {
        Session_ReadMessage(session, &bytes[1], 1);
        VillagerMemoryEntry_SetImpression((VillagerMemory *) (void *) entry, bytes[1]);
    }
}
CLEAN_AS(func_0207695c, SessionMessage_SetVillagerEntryByte6D)

/* func_02076900: as SessionMessage_SetVillagerEntryByte6D, for the byte 0x6c.
 * QUIRK: the value is passed as a signed byte. */
void SessionMessage_SetVillagerEntryByte6C(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    NetSession *session = data_020ccf94;
    u8 bytes[2];
    Session_ReadMessage(session, &bytes[0], 1);
    u8 *entry = session_message_villager_entry(&bytes[0]);
    if (entry != NULL) {
        Session_ReadMessage(session, &bytes[1], 1);
        VillagerMemoryEntry_SetFondness((VillagerMemory *) (void *) entry, (s8) bytes[1]);
    }
}
CLEAN_AS(func_02076900, SessionMessage_SetVillagerEntryByte6C)

/* func_020765cc: an item (2 bytes) and a villager (byte 2): the villager's item 0x7d2 becomes
 * it when it is one of 0x11a8-0x12a7 (SessionVillager_SendItem7D2ByIndex sends only those). */
void SessionMessage_SetVillagerItem7D2(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u16 item = NO_ITEM;
    u8 bytes[3];
    u32 index;
    Session_ReadMessage(data_020ccf94, bytes, 3);
    SessionVillager_UnpackItem(&index, &item, bytes);
    u8 *villager = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, (int) index);
    if (villager != NULL && item >= VILLAGER_ITEM_FIRST && item <= VILLAGER_ITEM_LAST) {
        TownVillager_SetClothes(villager, &item);
    }
}
CLEAN_AS(func_020765cc, SessionMessage_SetVillagerItem7D2)

/* func_02076568: four items (2 bytes each) and a villager (byte 8): the villager's items from
 * 0x7b0. */
void SessionMessage_SetVillagerItems7B0(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u16 items[4] = {NO_ITEM, NO_ITEM, NO_ITEM, NO_ITEM};
    u8 bytes[9];
    u32 index;
    Session_ReadMessage(data_020ccf94, bytes, 9);
    SessionVillager_UnpackItems(&index, items, bytes);
    u8 *villager = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, (int) index);
    if (villager == NULL) {
        return;
    }
    for (u32 i = 0; i < 4; i++) {
        u16 *slot_item = VillagerItems_At(villager, i);
        if (slot_item != NULL) {
            *slot_item = items[i];
        }
    }
}
CLEAN_AS(func_02076568, SessionMessage_SetVillagerItems7B0)

/* func_020767ac: a villager (high nibble of byte 0), an operation on its object (low nibble)
 * and a value (byte 1): 0 func_0209bb90, 1 func_0209ba7c, 2 func_0209b920, 3 func_0209b8a4,
 * 4 func_0209b890 and then as 5, 5 the object's byte 0x2e; all but 1 only while the object
 * is in use.
 * QUIRK: operation 4 goes on into operation 5. */
void SessionMessage_ChangeVillagerObject(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u8 operation = 6;
    u8 value = 0;
    u8 bytes[2];
    u32 index;
    Session_ReadMessage(data_020ccf94, bytes, 2);
    SessionVillager_UnpackObjectChange(&index, &operation, &value, bytes);
    u8 *villager = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, (int) index);
    if (villager == NULL) {
        return;
    }
    u8 *object = (u8 *) VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager));
    switch (operation) {
        case 0:
            if (ItemObject_IsInUse((ItemObject *) (void *) VillagerObject_Base((VillagerObject *) (void *) object)) != 0) {
                ItemObject_SetLow5((ItemObject *) (void *) VillagerObject_Base((VillagerObject *) (void *) object), value);
            }
            break;
        case 1:
            VillagerObject_ClearItem((VillagerObject *) (void *) object);
            break;
        case 2:
            if (ItemObject_IsInUse((ItemObject *) (void *) VillagerObject_Base((VillagerObject *) (void *) object)) != 0) {
                VillagerObject_NextStep((VillagerObject *) (void *) object);
            }
            break;
        case 3:
            if (ItemObject_IsInUse((ItemObject *) (void *) VillagerObject_Base((VillagerObject *) (void *) object)) != 0) {
                VillagerObject_SetKind((VillagerObject *) (void *) object, value);
            }
            break;
        case 4:
            if (ItemObject_IsInUse((ItemObject *) (void *) VillagerObject_Base((VillagerObject *) (void *) object)) != 0) {
                VillagerObject_SetFlag((VillagerObject *) (void *) object, value);
            }
            /* fall through */
        case 5:
            if (ItemObject_IsInUse((ItemObject *) (void *) VillagerObject_Base((VillagerObject *) (void *) object)) != 0) {
                object[0x2e] = value;
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020767ac, SessionMessage_ChangeVillagerObject)

/* func_020766f8: an item (bytes 0-1), a villager (high nibble of byte 2), a slot (bits 0-2) and
 * a flag (bit 3), and a kind (byte 3): the object the villager's func_0207f270 gives is
 * emptied, then the villager's object takes the item and kind (func_0209b9cc) with the name of
 * the player in that slot, when the slot is below 4 and has one. */
void SessionMessage_SetVillagerObject(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u8 object_kind = 0x16;
    u16 item = NO_ITEM;
    int player_slot = 4;
    u8 flag = 0;
    u8 bytes[4];
    int index;
    Session_ReadMessage(data_020ccf94, bytes, 4);
    SessionVillager_UnpackObject(&index, &object_kind, &item, &player_slot, &flag, bytes);
    u8 *villager = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, index);
    if (villager == NULL) {
        return;
    }
    u8 *object = (u8 *) VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager));
    int flagged = flag != 0;
    ItemObject_Clear((ItemObject *) (void *) VillagerState_Object(VillagerStatus_StateEntry(villager)));
    u8 *name = NULL;
    if (player_slot < 4) {
        u8 *record = PlayerRecords_OfPlayer(player_slot);
        if (record != NULL) {
            name = (u8 *) PlayerRecord_Player(record);
        }
    }
    VillagerObject_Set((VillagerObject *) (void *) object, object_kind, &item, (const DesignCreator *) (void *) name, flagged);
}
CLEAN_AS(func_020766f8, SessionMessage_SetVillagerObject)

/* func_0207689c: an item (bytes 0-1) and a villager and entry (byte 2): the entry's item 0x6a,
 * when func_02081edc allows. */
void SessionMessage_SetVillagerEntryItem(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u16 item = NO_ITEM;
    u8 bytes[3];
    u32 index;
    u32 entry_index;
    Session_ReadMessage(data_020ccf94, bytes, 3);
    SessionVillager_UnpackEntryItem(&index, &entry_index, &item, bytes);
    u8 *villager = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, (int) index);
    if (villager == NULL) {
        return;
    }
    u8 *entry = (u8 *) VillagerMemory_At(villager, (int) entry_index);
    if (entry != NULL && VillagerMemoryEntry_InUse((VillagerMemory *) (void *) entry) != 0) {
        VillagerMemoryEntry_SetItem((VillagerMemory *) (void *) entry, &item);
    }
}
CLEAN_AS(func_0207689c, SessionMessage_SetVillagerEntryItem)

/* func_02076638: an item (bytes 0-1) and a villager (byte 2; byte 3 is read and not used):
 * the item of the villager's object in use (0x2c) becomes it when it fits the object's type:
 * 0x12b0-0x12e7 for type 0, 0x12e8-0x131f for type 1. */
void SessionMessage_SetVillagerObjectItem(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    u16 item = NO_ITEM;
    u8 bytes[4];
    u32 index;
    Session_ReadMessage(data_020ccf94, bytes, 4);
    SessionVillager_UnpackItem(&index, &item, bytes);
    u8 *villager = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, (int) index);
    if (villager == NULL) {
        return;
    }
    u8 *object = (u8 *) VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager));
    u8 *in_use = VillagerObject_Base((VillagerObject *) (void *) object);
    if (ItemObject_IsInUse((ItemObject *) (void *) in_use) == 0) {
        return;
    }
    int fits = ItemObject_Type((ItemObject *) (void *) in_use) == 0 && item >= OBJECT0_ITEM_FIRST && item <= OBJECT0_ITEM_LAST;
    if (!fits) {
        if (ItemObject_Type((ItemObject *) (void *) in_use) != 1) {
            return;
        }
        if (item < OBJECT1_ITEM_FIRST || item > OBJECT1_ITEM_LAST) {
            return;
        }
    }
    *VillagerObject_Item((VillagerObject *) (void *) object) = item;
}
CLEAN_AS(func_02076638, SessionMessage_SetVillagerObjectItem)

/* ---- Handlers 20-51: each reads its payload and hands it on to the code it is for; some of
 * that code answers with a message of its own. */

extern u8 data_020e54a8;       /* while 0, handlers 40, 41, 47 and 48 act on overlay 3's objects */
extern u8 data_ov003_0226053c; /* set by handler 41 */
extern Heap *data_021fbe94;    /* the current heap */

/* func_0207716c: 4 bytes for func_020348fc.
 * REQUIRES: size <= 4. */
void SessionMessage_Handle20(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    u16 payload[2];
    Session_ReadMessage(data_020ccf94, payload, size);
    RoomInterior_ReceiveChange((const RoomInteriorChange *) payload);
}
CLEAN_AS(func_0207716c, SessionMessage_Handle20)

/* func_0207714c: a design copied or swapped between the systems (Design_Receive).
 * REQUIRES: size <= 4. */
void SessionMessage_ReceiveDesign(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    DesignMessage message;
    Session_ReadMessage(data_020ccf94, &message, size);
    Design_Receive(&message);
}
CLEAN_AS(func_0207714c, SessionMessage_ReceiveDesign)

/* func_02077108: a message between the players' consoles, read into a block of the current
 * heap for PlayerMessages_Dispatch.
 * QUIRK: the block is not checked for NULL. */
void SessionMessage_ReceivePlayerMessage(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    Heap *heap = data_021fbe94;
    u8 *message = Heap_AllocBack(heap, size);
    Session_ReadMessage(data_020ccf94, message, size);
    PlayerMessages_Dispatch(message, (int) slot);
    Heap_Free(heap, message);
}
CLEAN_AS(func_02077108, SessionMessage_ReceivePlayerMessage)

/* func_020770e0: up to 8 bytes for func_0203f4ec with the sender's slot.
 * REQUIRES: size <= 8. */
void SessionMessage_Handle23(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    u8 payload[8];
    Session_ReadMessage(data_020ccf94, payload, size);
    ObjectClaim_Dispatch(payload, (int) slot);
}
CLEAN_AS(func_020770e0, SessionMessage_Handle23)

/* func_020770c0: 4 bytes for func_02052b90.
 * REQUIRES: size <= 4. */
void SessionMessage_Handle24(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    u32 payload;
    Session_ReadMessage(data_020ccf94, &payload, size);
    RoomSync_ReceiveState(&payload);
}
CLEAN_AS(func_020770c0, SessionMessage_Handle24)

/* func_020770a0: a byte for func_02052b20.
 * REQUIRES: size <= 4. */
void SessionMessage_Handle25(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    u8 payload[4];
    Session_ReadMessage(data_020ccf94, payload, size);
    RoomSync_ReceiveLit(payload);
}
CLEAN_AS(func_020770a0, SessionMessage_Handle25)

/* func_02077078: 4 bytes for func_02052a3c with the sender's scene. */
void SessionMessage_Handle26(int size, int kind, int scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) slot;
    u32 payload;
    Session_ReadMessage(data_020ccf94, &payload, 4);
    RoomSync_ReceivePutItem(scene, &payload);
}
CLEAN_AS(func_02077078, SessionMessage_Handle26)

/* func_02077050: 4 bytes for func_02052ac8 with the sender's scene. */
void SessionMessage_Handle27(int size, int kind, int scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) slot;
    u32 payload;
    Session_ReadMessage(data_020ccf94, &payload, 4);
    RoomSync_ReceiveTakeFurniture(scene, &payload);
}
CLEAN_AS(func_02077050, SessionMessage_Handle27)

/* func_02077028: 4 bytes for func_02052a64 with the sender's scene. */
void SessionMessage_Handle28(int size, int kind, int scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) slot;
    u32 payload;
    Session_ReadMessage(data_020ccf94, &payload, 4);
    RoomSync_ReceivePutFurniture(scene, &payload);
}
CLEAN_AS(func_02077028, SessionMessage_Handle28)

/* func_02077008: 2 bytes for func_02052960.
 * REQUIRES: size <= 4. */
void SessionMessage_Handle29(u32 size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    u16 payload[2];
    Session_ReadMessage(data_020ccf94, payload, (int) size);
    RoomSync_ReceiveToggle(payload);
}
CLEAN_AS(func_02077008, SessionMessage_Handle29)

/* func_02076fe0: 3 bytes for func_020528fc with the sender's slot; it answers with message 31
 * or 32. */
void SessionMessage_Handle30(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 payload[8];
    Session_ReadMessage(data_020ccf94, payload, 3);
    PlaceClaim_ReceiveRequest((const PlaceClaimRequest *) (void *) payload, slot);
}
CLEAN_AS(func_02076fe0, SessionMessage_Handle30)

/* func_02076fd4: the answer 31 to message 30. */
void SessionMessage_Handle31(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    PlaceClaim_ReceiveAnswer(1);
}
CLEAN_AS(func_02076fd4, SessionMessage_Handle31)

/* func_02076fc8: the answer 32 to message 30. */
void SessionMessage_Handle32(int size, int kind, u8 scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    (void) slot;
    PlaceClaim_ReceiveAnswer(0);
}
CLEAN_AS(func_02076fc8, SessionMessage_Handle32)

/* func_02076fbc: func_020528d4 with the sender's slot; no payload is read. */
void SessionMessage_Handle33(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    PlaceClaim_ReceiveRelease(slot);
}
CLEAN_AS(func_02076fbc, SessionMessage_Handle33)

/* func_02076f9c: 2 bytes for func_020b2734.
 * REQUIRES: size <= 4. */
void SessionMessage_Handle34(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    u16 payload[2];
    Session_ReadMessage(data_020ccf94, payload, size);
    TownObjects_OnModeMessage(payload);
}
CLEAN_AS(func_02076f9c, SessionMessage_Handle34)

/* func_02076f74: up to 8 bytes for func_020b260c with the sender's slot.
 * REQUIRES: size <= 8. */
void SessionMessage_Handle35(u32 size, u32 kind, u32 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    u8 payload[8];
    Session_ReadMessage(data_020ccf94, payload, (int) size);
    TownObjects_OnVisitMessage(payload, (int) slot);
}
CLEAN_AS(func_02076f74, SessionMessage_Handle35)

/* func_02076f4c: an index for func_020b25e0, which clears the bit the sender's slot numbers in
 * that entry of data_021f4bac.
 * REQUIRES: size <= 8. */
void SessionMessage_Handle36(int size, int kind, int scene, int slot)
{
    (void) kind;
    (void) scene;
    u8 payload[8];
    Session_ReadMessage(data_020ccf94, payload, size);
    TownObjects_OnLeftMessage(payload, (u32) slot);
}
CLEAN_AS(func_02076f4c, SessionMessage_Handle36)

/* func_02076f2c: a byte of two nibbles for func_0209d3a8.
 * REQUIRES: size <= 4. */
void SessionMessage_Handle37(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    u8 payload[4];
    Session_ReadMessage(data_020ccf94, payload, size);
    RoomObjectState_Receive((RoomObjectStateMessage *) (void *) payload);
}
CLEAN_AS(func_02076f2c, SessionMessage_Handle37)

/* func_02076f04: 4 bytes for func_020ad7f4 with the sender's slot; it answers with message
 * 39.
 * REQUIRES: size <= 4. */
void SessionMessage_Handle38(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    u32 payload;
    Session_ReadMessage(data_020ccf94, &payload, size);
    Shops_ApplyMessage(&payload, (int) slot);
}
CLEAN_AS(func_02076f04, SessionMessage_Handle38)

/* func_02076ef8: the answer 39 to message 38; no payload is read.
 * QUIRK: returns func_020ad7e4's result, which the dispatch drops. */
int SessionMessage_Handle39(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    return Shops_CountAnswer(slot);
}
CLEAN_AS(func_02076ef8, SessionMessage_Handle39)

/* func_02076e58: an object of overlay 3, which, while data_020e54a8 is clear,
 * func_ov003_0222d7d0 is asked to take to state 0x10. The answer is message 41: when it did,
 * the byte with the sender's slot plus 1 in its high nibble, as kind 7; else the byte 1, as
 * kind `slot`.
 * REQUIRES: size <= 2 (a second payload byte would take the place of the answer 1). */
void SessionMessage_Handle40(int size, int kind, int scene, int slot)
{
    (void) kind;
    (void) scene;
    u8 bytes[2];
    bytes[1] = 1;
    NetSession *session = data_020ccf94;
    Session_ReadMessage(session, bytes, size);
    if (data_020e54a8 == 0) {
        bytes[1] = (u8) TownInsect_Hide(bytes[0]);
    }
    Session_BeginMessage(session);
    if (bytes[1] == 0) {
        bytes[0] = (u8) (((bytes[0] & 0xfu) | ((u32) slot << 4)) + 0x10);
        session = data_020ccf94;
        Session_AppendMessage(session, &bytes[0], 1);
        Session_EndMessage(session, 41, 7);
    } else {
        session = data_020ccf94;
        Session_AppendMessage(session, &bytes[1], 1);
        Session_EndMessage(session, 41, (u32) slot);
    }
}
CLEAN_AS(func_02076e58, SessionMessage_Handle40)

/* func_02076de4: the answer 41 to message 40, while data_020e54a8 is clear. When the byte's
 * high nibble is this system's slot plus 1, data_ov003_0226053c is cleared and the object of
 * set 1 at the byte's low nibble goes to state 0x10 (func_ov003_0222e750); else
 * data_ov003_0226053c is set.
 * QUIRK: the original also tests the rewritten byte (always 0x10-0x1f) for 1, which would set
 * data_ov003_0226053c; that never happens.
 * QUIRK: a high nibble of 0 matches a slot of -1 (the comparison is unsigned).
 * REQUIRES: size <= 1. */
void SessionMessage_Handle41(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    if (data_020e54a8 != 0) {
        return;
    }
    NetSession *session = data_020ccf94;
    u8 byte;
    Session_ReadMessage(session, &byte, size);
    u32 answer_slot = (u32) byte >> 4;
    u8 object = (u8) ((byte & 0xfu) | 0x10);
    if (answer_slot - 1 == (u32) session->local_slot) {
        data_ov003_0226053c = 0;
        TownInsect_HideById(object);
    } else {
        data_ov003_0226053c = 1;
    }
}
CLEAN_AS(func_02076de4, SessionMessage_Handle41)

/* func_02076d40: up to 8 bytes for func_02050884 with the sender's slot.
 * REQUIRES: size <= 8. */
void SessionMessage_Handle42(int size, int kind, int scene, int slot)
{
    (void) kind;
    (void) scene;
    u8 payload[8];
    Session_ReadMessage(data_020ccf94, payload, size);
    FishDisp_HandleMessage(payload, slot);
}
CLEAN_AS(func_02076d40, SessionMessage_Handle42)

/* func_02076c84: an item (bytes 0-1) and an operation (byte 2) on the sender's player record:
 * 0-2 go to func_020955e0; 3 sets the record's item at 0x2406 when the item differs from it,
 * then calls func_02095694 with 1 more than func_02062148 gives for the item.
 * REQUIRES: size <= 4. */
void SessionMessage_Handle43(int size, int kind, int scene, int slot)
{
    (void) kind;
    (void) scene;
    u8 payload[4];
    u16 item;
    int operation;
    Session_ReadMessage(data_020ccf94, payload, size);
    SessionPlayers_ReadItemOperation(payload, &item, &operation);
    switch (operation) {
        case 0:
        case 1:
        case 2:
            PlayerActorOps_SetWorn(&item, operation, slot);
            break;
        case 3: {
            u8 *record = PlayerRecords_OfPlayer(slot);
            u16 *current = PlayerRecord_HeldItem(record);
            int same;
            if (ItemCode_HasVariant(&item) != 0) {
                int code = ItemCode_VariantItem(&item);
                same = code == ItemCode_VariantItem(current);
            } else {
                same = item == *current;
            }
            if (!same) {
                u32 count = ItemInfo_HeldModelNumber(&item);
                PlayerRecord_SetHeldItem(record, &item);
                PlayerActorOps_SetHeldModel(count + 1, slot);
            }
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_02076c84, SessionMessage_Handle43)

/* func_02076c3c: a byte whose bits 0-3 go to bits 4-7 of the sender's player record's byte
 * 0x243c and whose bits 4-6 go to bits 0-2 of its byte 0x243d.
 * REQUIRES: size <= 3. */
void SessionMessage_Handle44(int size, int kind, int scene, int slot)
{
    (void) kind;
    (void) scene;
    u8 bytes[3];
    Session_ReadMessage(data_020ccf94, bytes, size);
    SessionPlayers_SplitLowHigh(&bytes[0], &bytes[1], &bytes[2]);
    u8 *record = PlayerRecords_OfPlayer(slot);
    PlayerRecord_SetHeadKind(record, bytes[1]);
    PlayerRecord_SetHairColor(record, bytes[2]);
}
CLEAN_AS(func_02076c3c, SessionMessage_Handle44)

/* func_02076c14: a byte for func_02095578 with the sender's slot.
 * REQUIRES: size <= 8. */
void SessionMessage_Handle45(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    u8 payload[8];
    Session_ReadMessage(data_020ccf94, payload, size);
    PlayerActorOps_SetFlag0(payload[0], (int) slot);
}
CLEAN_AS(func_02076c14, SessionMessage_Handle45)

/* func_02076bec: a byte for func_02095558 (bits 3-5 of the sender's player record's byte
 * 0x243d).
 * REQUIRES: size <= 8. */
void SessionMessage_Handle46(int size, int kind, int scene, int slot)
{
    (void) kind;
    (void) scene;
    u8 payload[8];
    Session_ReadMessage(data_020ccf94, payload, size);
    PlayerActorOps_SetSunLevel(payload[0], slot);
}
CLEAN_AS(func_02076bec, SessionMessage_Handle46)

/* func_02076dac: an object of overlay 3 for func_ov003_0222e4c0, while data_020e54a8 is
 * clear; the payload is read either way.
 * REQUIRES: size <= 4. */
void SessionMessage_Handle47(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    u8 payload[4];
    Session_ReadMessage(data_020ccf94, payload, size);
    if (data_020e54a8 == 0) {
        TownInsect_Show(payload[0]);
    }
}
CLEAN_AS(func_02076dac, SessionMessage_Handle47)

/* func_02076d68: an object of overlay 3, while data_020e54a8 is clear: below 4 for
 * func_ov003_0222e6c4 (told not to send message 48 on), else for func_ov003_0222e7f8; the
 * payload is read either way.
 * REQUIRES: size <= 1. */
void SessionMessage_Handle48(int size, int kind, u8 scene, u32 slot)
{
    (void) kind;
    (void) scene;
    (void) slot;
    u8 object;
    Session_ReadMessage(data_020ccf94, &object, size);
    if (data_020e54a8 == 0) {
        if (object < 4) {
            TownInsect_EndHeld(object, 0);
        } else {
            TownInsect_Startle(object);
        }
    }
}
CLEAN_AS(func_02076d68, SessionMessage_Handle48)

/* func_02076b10: an 8-byte request about an item on the town's grid. Bytes 2-3 give the tile
 * (x in the high byte, z in the low one; blocks of 16 by 16 tiles), byte 1's bit 7 the layer,
 * bytes 4-5 the item expected there. It is found when the tile holds that item and either
 * func_02045d80 finds no entry for the tile and func_02045aa4 allows it for the sender, or the
 * entry it finds (func_02045bac) has the request's byte 0 bits 0-1 in its bits 0-2, its byte 1
 * bit 7 set and its byte 2 bit 0 clear. func_0204510c answers with message 50. Nothing is read
 * while there is no grid. */
void SessionMessage_Handle49(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u16 *grid = (u16 *) (uintptr_t) AcreMap_Town();
    if (grid == NULL) {
        return;
    }
    u8 request[8];
    Session_ReadMessage(data_020ccf94, request, 8);
    u32 tile = (u32) request[2] | ((u32) request[3] << 8);
    u16 expected = (u16) (request[4] | (request[5] << 8));
    u8 layer = request[1] >> 7;
    u32 x = tile >> 8;
    u32 z = tile & 0xffu;
    u32 block_x = x >> 4;
    u32 block_z = z >> 4;

    int found = 0;
    u16 *item = AcreTile_ItemInAcre((AcreMap *) grid, block_x, block_z, (int) (x & 0xfu), (int) (z & 0xfu), layer);
    if (item != NULL && *item == expected) {
        int position[2] = {(int) x, (int) z};
        int index = TileChanges_IndexAt((const TileChangesTile *) position, layer);
        if (index < 0) {
            int position2[2] = {(int) x, (int) z};
            found = TileRequestGrant_NoOtherNearFor((const TileRequestTile *) position2, slot) != 0;
        } else {
            const u8 *entry = (const u8 *) (uintptr_t) TileChanges_At(index);
            found = (entry[0] & 7) == (request[0] & 3) && (entry[1] & 0x80) != 0 && (entry[2] & 1) == 0;
        }
    }
    TileRequestGrant_Answer((const TileRequestMessage *) (void *) request, found, slot);
}
CLEAN_AS(func_02076b10, SessionMessage_Handle49)

/* func_02076ae8: the answer 50 to message 49: 14 bytes for func_02044e28 with the sender's
 * scene. */
void SessionMessage_Handle50(int size, int kind, int scene, u32 slot)
{
    (void) size;
    (void) kind;
    (void) slot;
    u8 payload[16];
    Session_ReadMessage(data_020ccf94, payload, 14);
    TileRequestGrant_ReceiveAnswer((const TileRequestAnswer *) (void *) payload, scene);
}
CLEAN_AS(func_02076ae8, SessionMessage_Handle50)

/* func_02076ac0: a request (a byte) for func_0209d4c0 with the sender's slot; it answers with
 * message 52. */
void SessionMessage_Handle51(int size, int kind, int scene, int slot)
{
    (void) size;
    (void) kind;
    (void) scene;
    u8 request[4];
    Session_ReadMessage(data_020ccf94, request, 1);
    SceneClaim_ReceiveRequest(request, slot);
}
CLEAN_AS(func_02076ac0, SessionMessage_Handle51)
