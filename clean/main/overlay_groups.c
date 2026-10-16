/* Overlay groups: which are in use and loaded, and the one request at a time that loads them.
 *
 * func_02070108 loads a requested group's overlays (func_0204f934 for each), marks it loaded and
 * moves the request on; func_020700cc releases a group's overlays (func_0204f8ec) and clears
 * both marks. Both bit sets are cleared at start, which also sets the request to idle with
 * group 46. */
#include "overlay_groups.h"

#include <assert.h>

#include "autoload_2/links.h"
#include "clean.h"

extern u32 data_021cfcb4[3]; /* the groups in use, one bit each */
extern u32 data_021cfccc[3]; /* the groups loaded */
extern OverlayGroupsRequest data_020df328;
/* The objects the groups are loaded for, each linked in by an OverlayGroupsOwner; the first
 * is the one a group is started under. Empty when the groups are the game's own. */
extern List data_021cfca0;

/* REQUIRES: 0 <= group < 96, the bits the sets have; the game passes 0-45. */
static void clear_bit(u32 *set, int group)
{
    set[group >> 5] &= ~(1u << (group & 31));
}

static void set_bit(u32 *set, int group)
{
    set[group >> 5] |= 1u << (group & 31);
}

static BOOL test_bit(const u32 *set, int group)
{
    return (set[group >> 5] & (1u << (group & 31))) != 0;
}

/* func_0206ff00 */
void OverlayGroups_ClearInUse(int group)
{
    clear_bit(data_021cfcb4, group);
}

/* func_0206ff24 */
void OverlayGroups_SetInUse(int group)
{
    set_bit(data_021cfcb4, group);
}

/* func_0206ff48 */
BOOL OverlayGroups_IsInUse(int group)
{
    return test_bit(data_021cfcb4, group);
}

/* func_0206ff74 */
void OverlayGroups_ClearLoaded(int group)
{
    clear_bit(data_021cfccc, group);
}

/* func_0206ff98 */
void OverlayGroups_SetLoaded(int group)
{
    set_bit(data_021cfccc, group);
}

/* func_0206ffbc */
BOOL OverlayGroups_IsLoaded(int group)
{
    return test_bit(data_021cfccc, group);
}

static void request(int group)
{
    data_020df328.group = (u8) group;
    data_020df328.state = OVERLAY_GROUPS_REQUESTED;
}

/* func_0207000c: ask for a group for the current owner, unless it is loaded already; TRUE when
 * the request was made. */
BOOL OverlayGroups_RequestForOwner(int group)
{
    if (data_020df328.state != OVERLAY_GROUPS_IDLE || data_021cfca0.first == NULL || OverlayGroups_IsLoaded(group)) {
        return FALSE;
    }
    request(group);
    return TRUE;
}

/* func_0207004c: ask for a group when there is no owner; TRUE when the request was made. */
BOOL OverlayGroups_Request(int group)
{
    if (!OverlayGroups_IsIdle()) {
        return FALSE;
    }
    request(group);
    return TRUE;
}

/* func_02070070 */
BOOL OverlayGroups_HasOwner(void)
{
    return data_020df328.state != OVERLAY_GROUPS_OFF && data_021cfca0.first != NULL;
}

/* func_02070094: can a group be requested without an owner? */
BOOL OverlayGroups_IsIdle(void)
{
    return data_020df328.state == OVERLAY_GROUPS_IDLE && data_021cfca0.first == NULL;
}

static_assert(sizeof(OverlayGroupsRequest) == 2, "request layout");

/* Each group's overlays, a list ended by -1. */
extern const int *const data_020df5ec[OVERLAY_GROUP_COUNT];
/* For each group, what func_0202f134 starts once its overlays are loaded. */
extern const u16 data_020df590[OVERLAY_GROUP_COUNT];
/* The object groups are started under when there is no owner (OverlayTask_Init). */
extern void *data_021cfc84;

extern void func_0204f8ec(u8 overlay); /* release an overlay */
extern void func_0204f934(u8 overlay); /* load an overlay */
extern void func_0206f5b0(void);       /* clears state flag 0x80, sets data_021cfc54 to 0x37 */
extern int func_0202f134(int entry, void *parent, int group, int arg);

/* func_020700cc: release a group's overlays and unmark it; always TRUE. */
BOOL OverlayGroups_Release(int group)
{
    const int *overlays = data_020df5ec[group];
    for (int i = 0; overlays[i] != -1; i++) {
        func_0204f8ec((u8) overlays[i]);
    }
    OverlayGroups_ClearLoaded(group);
    OverlayGroups_ClearInUse(group);
    return TRUE;
}
CLEAN_AS(func_020700cc, OverlayGroups_Release)

/* func_02070108: load the requested group's overlays; TRUE when there was one to load. */
BOOL OverlayGroups_LoadRequested(void)
{
    if (data_020df328.state != OVERLAY_GROUPS_REQUESTED) {
        return FALSE;
    }
    const int *overlays = data_020df5ec[data_020df328.group];
    for (int i = 0; overlays[i] != -1; i++) {
        func_0204f934((u8) overlays[i]);
    }
    data_020df328.state = OVERLAY_GROUPS_LOADED;
    OverlayGroups_SetLoaded(data_020df328.group);
    return TRUE;
}
CLEAN_AS(func_02070108, OverlayGroups_LoadRequested)

/* func_02070150: start the loaded group under the first owner (or, without one, under the
 * object at data_021cfc84), and go back to idle; TRUE when it was started. */
BOOL OverlayGroups_StartLoaded(void)
{
    if (data_020df328.state != OVERLAY_GROUPS_LOADED) {
        return FALSE;
    }
    const OverlayGroupsOwner *first = (const OverlayGroupsOwner *) data_021cfca0.first;
    void *parent = first != NULL ? first->owner : data_021cfc84;
    func_0206f5b0();
    u8 group = data_020df328.group;
    if (func_0202f134(data_020df590[group], parent, group, 4) == 0) {
        return FALSE;
    }
    data_020df328.state = OVERLAY_GROUPS_IDLE;
    return TRUE;
}
CLEAN_AS(func_02070150, OverlayGroups_StartLoaded)

/* func_020701a8: release every marked group (OverlayGroups_SetInUse). */
void OverlayGroups_ReleaseMarked(void)
{
    if (data_021cfcb4[0] == 0 && data_021cfcb4[1] == 0 && data_021cfcb4[2] == 0) {
        return;
    }
    for (int group = 0; group < OVERLAY_GROUP_COUNT; group++) {
        if (OverlayGroups_IsInUse(group)) {
            OverlayGroups_Release(group);
        }
    }
}
CLEAN_AS(func_020701a8, OverlayGroups_ReleaseMarked)

/* func_020701e4: unlink an owner, and mark its group to be released. */
void OverlayGroups_RemoveOwner(OverlayGroupsOwner *link)
{
    List_Remove(&data_021cfca0, &link->node);
    OverlayGroups_SetInUse(link->owner[OVERLAY_GROUPS_OWNER_GROUP]);
}
CLEAN_AS(func_020701e4, OverlayGroups_RemoveOwner)

/* func_02070204: link an owner in last. */
void OverlayGroups_AddOwner(OverlayGroupsOwner *link)
{
    List_PushBack(&data_021cfca0, &link->node);
}
CLEAN_AS(func_02070204, OverlayGroups_AddOwner)

static_assert(sizeof(OverlayGroupsOwner) == 12, "owner link layout");
