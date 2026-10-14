/* Overlay groups: which are in use and loaded, and the one request at a time that loads them.
 *
 * func_02070108 loads a requested group's overlays (func_0204f934 for each), marks it loaded and
 * moves the request on; func_020700cc releases a group's overlays (func_0204f8ec) and clears
 * both marks. Both bit sets are cleared at start, which also sets the request to idle with
 * group 46. */
#include "overlay_groups.h"

#include <assert.h>

extern u32 data_021cfcb4[3]; /* the groups in use, one bit each */
extern u32 data_021cfccc[3]; /* the groups loaded */
extern OverlayGroupsRequest data_020df328;
/* The object the group is loaded for, which also gives the heap to load it into; null when
 * the overlays go to the game's own heap. */
extern void *data_021cfca0;

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
    if (data_020df328.state != OVERLAY_GROUPS_IDLE || data_021cfca0 == NULL || OverlayGroups_IsLoaded(group)) {
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
    return data_020df328.state != OVERLAY_GROUPS_OFF && data_021cfca0 != NULL;
}

/* func_02070094: can a group be requested without an owner? */
BOOL OverlayGroups_IsIdle(void)
{
    return data_020df328.state == OVERLAY_GROUPS_IDLE && data_021cfca0 == NULL;
}

static_assert(sizeof(OverlayGroupsRequest) == 2, "request layout");
