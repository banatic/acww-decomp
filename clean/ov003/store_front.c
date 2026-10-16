/* Nook's store seen from outside: whether the player may go in, and the closed sign
 * (store_front.h). */
#include "store_front.h"

#include "autoload_2/heap.h" /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "main/calendar.h"  /* Time, DateTime */
#include "main/date_time.h" /* DateTime_Now */
#include "main/map_code.h"
#include "main/message_receiver.h"
#include "main/nook_store.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/start_kind.h"

static_assert(offsetof(SceneActor, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(SceneActor, message) == 0x10a, "receiver byte 0x1e");
static_assert(offsetof(SceneActor, code) == 0x136, "code");
static_assert(offsetof(SceneActor, flags) == 0x236, "flags");
static_assert(offsetof(StoreFront, level) == 0x2b4, "level");
static_assert(sizeof(StoreFront) == 0x2b8, "the size StoreFront_New allocates");

#define STORE_FRONT_RECEIVER_OFFSET 0xec
/* The hours the store is open: from 8:00 until 23:00. */
#define STORE_FRONT_OPENS 8
#define STORE_FRONT_CLOSES 23
/* The day before its upgrade, the store is closed after this hour. */
#define STORE_FRONT_LAST_HOUR_BEFORE 12
/* Flags of the player's record: never let in, always let in. */
#define STORE_FRONT_PLAYER_KEPT_OUT 0x23
#define STORE_FRONT_PLAYER_LET_IN 1
/* The messages. */
#define STORE_FRONT_MESSAGE_ERROR 0     /* of "obj_etc_error" */
#define STORE_FRONT_MESSAGE_NO_LEVEL 4  /* of "obj_etc_closed" */
#define STORE_FRONT_MESSAGE_CLOSED 7    /* of "obj_etc_closed" */
#define STORE_FRONT_MESSAGE_SEQUENCE 21 /* of "sp_etc_sequence4" */
#define STORE_FRONT_LEVEL_MASK 3

/* "obj_etc_closed", "obj_etc_error" and "sp_etc_sequence4" */
extern const char data_ov003_02239890[];
extern const char data_ov003_022398a0[];
extern const char data_ov003_022398b0[];
/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_02239754[];
extern const u8 data_ov003_02239818[];
/* The town's Nook's store. */
extern NookStore data_021f395c;

/* Overlay 9's scene actor: the paths of its archive, texture and light texture (vtable slots
 * 0xa4, 0xa8 and 0xac; the last gives none for some codes), its destructor and its
 * constructor. */
extern int *func_ov009_02264c10(StoreFront *store);
extern char *func_ov009_02264be0(StoreFront *store);
extern void *func_ov009_02264b64(StoreFront *store);
extern void *func_ov009_0226539c(StoreFront *store);
extern void *func_ov009_0226552c(StoreFront *store);

static MessageReceiver *store_front_receiver(StoreFront *store)
{
    return (MessageReceiver *) (void *) &store->actor.receiver_vtable;
}

static int store_front_is_open_at(int hour)
{
    return hour >= STORE_FRONT_OPENS && hour < STORE_FRONT_CLOSES;
}

/* func_ov003_0221eb44 (vtable slot 0x98): always 1. */
int StoreFront_Slot98(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221eb44, StoreFront_Slot98)

/* func_ov003_0221eb48: whether today is the day the store is closed for its upgrade (never
 * with no level). */
int StoreFront_IsClosedForUpgrade(StoreFront *store)
{
    if (store->level != STORE_FRONT_NO_LEVEL) {
        DateTime now = {0};
        DateTime_Now(&now);
        if (NookStore_IsClosedOn(&data_021f395c, &now)) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_0221eb48, StoreFront_IsClosedForUpgrade)

/* func_ov003_0221eb84 (vtable slot 0x8c): whether the player may go in (store_front.h). The
 * player's record may be missing: its flags are then not asked. */
int StoreFront_LetsIn(StoreFront *store)
{
    Time now;
    Calendar_Now(&now);
    if (store->level == STORE_FRONT_NO_LEVEL) {
        return store_front_is_open_at(now.hour);
    }
    u8 *player = PlayerRecords_Current();
    if (StartKind_IsSet() || (player != NULL && PlayerRecord_TestFlag(player, STORE_FRONT_PLAYER_KEPT_OUT))) {
        return 0;
    }
    if (player != NULL && PlayerRecord_TestFlag(player, STORE_FRONT_PLAYER_LET_IN)) {
        return 1;
    }
    if (StoreFront_IsClosedForUpgrade(store)) {
        return 0;
    }
    if (!store_front_is_open_at(now.hour)) {
        return 0;
    }
    if (NookStore_IsUpgradeDue(&data_021f395c)) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov003_0221eb84, StoreFront_LetsIn)

/* func_ov003_0221ec24 (vtable slot 0x78, before a talk): names the receiver and picks its
 * message, the first that applies:
 *
 *   - with no level: "obj_etc_error" message 0 when the visit record said 2, else
 *     "obj_etc_closed" message 4;
 *   - while a start kind is set or the player has flag 0x23: "sp_etc_sequence4" message 0x15;
 *   - on the day of the upgrade: "obj_etc_closed" message 7;
 *   - when the visit record said 2: "obj_etc_error" message 0;
 *   - with an upgrade planned, after 12:59 on the day before it, on its day or once it is due:
 *     "obj_etc_closed" message 7;
 *   - else "obj_etc_closed" with the store's level as its message.
 *
 * REQUIRES: this console's player has a record (the flag is asked without a check, unlike in
 * StoreFront_LetsIn). */
void StoreFront_PrepareTalk(StoreFront *store)
{
    MessageReceiver *receiver = store_front_receiver(store);
    MessageReceiver_SetName(receiver, data_ov003_02239890);

    if (store->level == STORE_FRONT_NO_LEVEL) {
        if (store->actor.flags & SCENE_ACTOR_FLAG_VISIT_2) {
            MessageReceiver_SetName(receiver, data_ov003_022398a0);
            store->actor.message = STORE_FRONT_MESSAGE_ERROR;
        } else {
            store->actor.message = STORE_FRONT_MESSAGE_NO_LEVEL;
        }
        return;
    }

    u8 *player = PlayerRecords_Current();
    if (StartKind_IsSet() || PlayerRecord_TestFlag(player, STORE_FRONT_PLAYER_KEPT_OUT)) {
        MessageReceiver_SetName(receiver, data_ov003_022398b0);
        store->actor.message = STORE_FRONT_MESSAGE_SEQUENCE;
        return;
    }
    if (StoreFront_IsClosedForUpgrade(store)) {
        store->actor.message = STORE_FRONT_MESSAGE_CLOSED;
        return;
    }
    if (store->actor.flags & SCENE_ACTOR_FLAG_VISIT_2) {
        MessageReceiver_SetName(receiver, data_ov003_022398a0);
        store->actor.message = STORE_FRONT_MESSAGE_ERROR;
        return;
    }

    int closed = 0;
    if (NookStore_Upgrade(&data_021f395c)->pending) {
        DateTime now = {0};
        DateTime_Now(&now);
        if (NookStore_IsClosedTomorrow(&data_021f395c)) {
            closed = now.hour > STORE_FRONT_LAST_HOUR_BEFORE;
        } else if (NookStore_IsClosedToday(&data_021f395c) || NookStore_IsUpgradeDue(&data_021f395c)) {
            closed = 1;
        }
    }
    if (closed) {
        store->actor.message = STORE_FRONT_MESSAGE_CLOSED;
    } else {
        store->actor.message = (u8) (store->level & STORE_FRONT_LEVEL_MASK);
    }
}
CLEAN_AS(func_ov003_0221ec24, StoreFront_PrepareTalk)

/* func_ov003_0221ed48 (vtable slot 0xac): overlay 9's path of the light texture.
 * QUIRK: the original goes on to overlay 9's function and so hands back what it returns, the
 * path; its callers read it although this is declared void. */
void StoreFront_LightTexturePath(StoreFront *store)
{
    func_ov009_02264b64(store);
}
CLEAN_AS(func_ov003_0221ed48, StoreFront_LightTexturePath)

/* func_ov003_0221ed50 (vtable slot 0xa8): overlay 9's path of the texture.
 * QUIRK: hands back what overlay 9's function returns, as StoreFront_LightTexturePath. */
void StoreFront_TexturePath(StoreFront *store)
{
    func_ov009_02264be0(store);
}
CLEAN_AS(func_ov003_0221ed50, StoreFront_TexturePath)

/* func_ov003_0221ed58 (vtable slot 0xa4): overlay 9's path of the archive.
 * QUIRK: hands back what overlay 9's function returns, as StoreFront_LightTexturePath. */
void StoreFront_ArchivePath(StoreFront *store)
{
    func_ov009_02264c10(store);
}
CLEAN_AS(func_ov003_0221ed58, StoreFront_ArchivePath)

/* func_ov003_0221ed60 (vtable slot 0x70, setting it up): keeps the store's level its code
 * names (-1 for another code); always 1. */
int StoreFront_SetUp(StoreFront *store)
{
    store->level = MapCode_StoreLevel(&store->actor.code);
    return 1;
}
CLEAN_AS(func_ov003_0221ed60, StoreFront_SetUp)

/* The vtables set back, then overlay 9's destructor. */
static void store_front_destroy_parts(StoreFront *store)
{
    store->actor.vtable = data_ov003_02239754;
    store->actor.receiver_vtable = data_ov003_02239818;
    func_ov009_0226539c(store);
}

/* func_ov003_0221ed80 (vtable slot 0x44, the deleting destructor): the destructor's work, then
 * the memory freed. */
StoreFront *StoreFront_DestroyAndFree(StoreFront *store)
{
    store_front_destroy_parts(store);
    Heap_FreeAux(store);
    return store;
}
CLEAN_AS(func_ov003_0221ed80, StoreFront_DestroyAndFree)

/* func_ov003_0221edac (vtable slot 0x40): the destructor, without freeing. */
StoreFront *StoreFront_Destroy(StoreFront *store)
{
    store_front_destroy_parts(store);
    return store;
}
CLEAN_AS(func_ov003_0221edac, StoreFront_Destroy)

/* func_ov003_0221edd0: the constructor: overlay 9's, then the vtables. */
StoreFront *StoreFront_Construct(StoreFront *store)
{
    func_ov009_0226552c(store);
    store->actor.vtable = data_ov003_02239754;
    store->actor.receiver_vtable = data_ov003_02239818;
    return store;
}
CLEAN_AS(func_ov003_0221edd0, StoreFront_Construct)

/* func_ov003_0221edf4 (the class's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void StoreFront_New(void)
{
    StoreFront *store = Heap_AllocAuxZeroed(sizeof(StoreFront));
    if (store != NULL) {
        StoreFront_Construct(store);
    }
}
CLEAN_AS(func_ov003_0221edf4, StoreFront_New)

/* The store around its receiver part, as the receiver vtable's thunks find it. */
static StoreFront *store_front_from_receiver(void *receiver)
{
    return (StoreFront *) (void *) ((u8 *) receiver - STORE_FRONT_RECEIVER_OFFSET);
}

/* _ZThn236_N18Obj_ov003_02239754D0Ev (receiver slot 0x04): StoreFront_DestroyAndFree. */
StoreFront *StoreFront_ReceiverDestroyAndFree(void *receiver)
{
    return StoreFront_DestroyAndFree(store_front_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02239754D0Ev, StoreFront_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_02239754D1Ev (receiver slot 0x00): StoreFront_Destroy. */
StoreFront *StoreFront_ReceiverDestroy(void *receiver)
{
    return StoreFront_Destroy(store_front_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02239754D1Ev, StoreFront_ReceiverDestroy)
