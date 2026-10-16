/* A villager's house: its checks of the villager and the talk at its closed door
 * (villager_house.h). */
#include "villager_house.h"

#include <stdint.h>

#include "clean.h"
#include "main/npc_id.h"  /* NpcId, NpcId_Personality, NpcId_FormatName */
#include "main/session.h" /* NetSession, Session_IsSlotTaken */

static_assert(offsetof(VillagerHouse, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(VillagerHouse, message) == 0x10a, "receiver byte 0x1e");
static_assert(offsetof(VillagerHouse, link) == 0x12c, "link");
static_assert(offsetof(VillagerHouse, code) == 0x136, "code");
static_assert(offsetof(VillagerHouse, flags) == 0x236, "flags");
static_assert(offsetof(VillagerHouse, message_set) == 0x237, "message set");

#define VILLAGER_HOUSE_FIRST_CODE 0x5001
#define VILLAGER_HOUSE_LAST_CODE 0x5008
#define VILLAGER_HOUSE_MESSAGE_GONE 6 /* when func_0207f1d4 says there is no villager */
#define VILLAGER_HOUSE_STATUS_AWAY 2  /* the status for which the session's slots are looked at */
#define VILLAGER_HOUSE_SESSION_SLOTS 4

/* The eight villagers (0x7ec bytes each). */
extern u8 data_021e5a2c[];
/* "obj_etc_closed" and "obj_etc_error", the names the receiver gets. */
extern const char data_ov003_02239064[];
extern const char data_ov003_02239074[];
/* The door's message by the villager's personality: the first table and the second. */
extern const u8 data_ov003_0223664c[];
extern const u8 data_ov003_02236644[];
/* The session of the wireless play. */
extern NetSession *data_020ccf94;

/* Villager `index` of the list, NULL when there is none. */
extern void *func_0207cec0(void *villagers, int index);
/* Whether there is a villager (always 1), and its status (0 to 7). */
extern int func_0207f1d4(void *villager);
extern int func_0207f1d8(void *villager);
/* The villager's NpcId, 0x7a0 bytes in. */
extern NpcId *func_0208150c(void *villager);
/* The three bytes of a session slot's link state. */
extern void func_020a6e4c(int slot, u8 *byte0, u8 *byte1, u8 *byte2);
/* The villager index (0 to 7) a link state's first byte names (17 to 24), else -1. */
extern int func_020b66c4(unsigned int value);
/* Whether the hour is outside 6:00 to 18:00. */
extern int func_ov009_02264c40(VillagerHouse *house);
/* Copies at most 25 characters of `name` into the receiver's name. */
extern void func_020a8164(void *receiver, const char *name);
/* A string object (0x24 bytes): built by func_02094fd4, destroyed by func_02094fbc;
 * func_02068404 hands it to the link as line `line`. */
extern void *func_02094fd4(void *text);
extern void *func_02094fbc(void *text);
extern void func_02068404(void *link, int line, void *text);
/* Overlay 3's set of house resources at data_ov003_0223cea0, and its word 9. */
extern int func_ov003_022203c0(void);
extern int func_ov003_0221ffac(int *set);

typedef struct VillagerHouseText {
    u8 bytes[0x24];
} VillagerHouseText;

/* The villager's index from the special character's code, -1 when it is not a villager's. */
static int villager_house_index(const VillagerHouse *house)
{
    unsigned int code = house->code;
    if (code >= VILLAGER_HOUSE_FIRST_CODE && code <= VILLAGER_HOUSE_LAST_CODE) {
        return (int) code - VILLAGER_HOUSE_FIRST_CODE;
    }
    return -1;
}

/* Whether the villager's status is 0 or 3 to 7.
 * QUIRK: the status is asked for again for each value compared. */
static int villager_house_status_refuses(void *villager)
{
    return func_0207f1d8(villager) == 0 || func_0207f1d8(villager) == 3 || func_0207f1d8(villager) == 4 ||
           func_0207f1d8(villager) == 5 || func_0207f1d8(villager) == 6 || func_0207f1d8(villager) == 7;
}

/* func_ov003_0221d2a8 (vtable slot 0x98): always 1. */
int VillagerHouse_Slot98(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221d2a8, VillagerHouse_Slot98)

/* func_ov003_0221d2ac (vtable slot 0x90): always 1. */
int VillagerHouse_Slot90(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221d2ac, VillagerHouse_Slot90)

/* func_ov003_0221d2b0 (vtable slot 0x9c): 0 by day (6:00 to 18:00). At night 1 when there is
 * no such villager; else 0 when func_0207f1d4 says no or the status is 0 or 3 to 7; for status
 * 2 whether one of the four session slots taken names this villager in its link state; else
 * 1. */
int VillagerHouse_Slot9C(VillagerHouse *house)
{
    int index = villager_house_index(house);
    if (func_ov009_02264c40(house) == 0) {
        return 0;
    }
    void *villager = func_0207cec0(data_021e5a2c, index);
    if (villager == NULL) {
        return 1;
    }
    if (func_0207f1d4(villager) == 0) {
        return 0;
    }
    if (villager_house_status_refuses(villager)) {
        return 0;
    }
    if (func_0207f1d8(villager) != VILLAGER_HOUSE_STATUS_AWAY) {
        return 1;
    }
    NetSession *session = data_020ccf94;
    for (int slot = 0; slot < VILLAGER_HOUSE_SESSION_SLOTS; slot++) {
        if (Session_IsSlotTaken(session, slot) != 0) {
            u8 link_state[3];
            func_020a6e4c(slot, &link_state[0], &link_state[1], &link_state[2]);
            if (index == func_020b66c4(link_state[0])) {
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_0221d2b0, VillagerHouse_Slot9C)

/* func_ov003_0221d3a4 (vtable slot 0x8c): whether there is such a villager, func_0207f1d4 says
 * yes and its status is neither 0 nor 3 to 7. */
int VillagerHouse_Slot8C(VillagerHouse *house)
{
    void *villager = func_0207cec0(data_021e5a2c, villager_house_index(house));
    if (villager == NULL) {
        return 0;
    }
    if (func_0207f1d4(villager) == 0) {
        return 0;
    }
    if (villager_house_status_refuses(villager)) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov003_0221d3a4, VillagerHouse_Slot8C)

/* func_ov003_0221d43c (vtable slot 0x78, before a talk): names the receiver "obj_etc_closed"
 * and picks its message: VILLAGER_HOUSE_MESSAGE_GONE when func_0207f1d4 says there is no
 * villager; with VILLAGER_HOUSE_FLAG_ERROR the receiver is renamed "obj_etc_error" with
 * message 0; else, when the villager has an NpcId, the message of its personality from the
 * first table, or the second when message_set is nonzero (otherwise the message stays). The
 * villager's name goes to the link as line 0. */
void VillagerHouse_PrepareTalk(VillagerHouse *house)
{
    void *villager = func_0207cec0(data_021e5a2c, villager_house_index(house));
    func_020a8164(&house->receiver_vtable, data_ov003_02239064);
    if (func_0207f1d4(villager) == 0) {
        house->message = VILLAGER_HOUSE_MESSAGE_GONE;
    } else if (house->flags & VILLAGER_HOUSE_FLAG_ERROR) {
        func_020a8164(&house->receiver_vtable, data_ov003_02239074);
        house->message = 0;
    } else {
        NpcId *npc = func_0208150c(villager);
        if (npc != NULL) {
            if (house->message_set == 0) {
                house->message = data_ov003_0223664c[NpcId_Personality(npc)];
            } else {
                house->message = data_ov003_02236644[NpcId_Personality(npc)];
            }
        }
    }

    VillagerHouseText text;
    func_02094fd4(&text);
    NpcId_FormatName(func_0208150c(villager), (char *) text.bytes);
    func_02068404(house->link, 0, &text);
    func_02094fbc(&text);
}
CLEAN_AS(func_ov003_0221d43c, VillagerHouse_PrepareTalk)

/* func_ov003_0221d530 (vtable slot 0x68): reads word 9 of overlay 3's set of house resources
 * and drops it.
 * QUIRK: declared without a result; in the ROM the word is still in r0 when it returns. */
void VillagerHouse_Slot68(void)
{
    func_ov003_0221ffac((int *) (uintptr_t) (u32) func_ov003_022203c0());
}
CLEAN_AS(func_ov003_0221d530, VillagerHouse_Slot68)
