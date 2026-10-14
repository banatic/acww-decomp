#include "../../../clean/main/overlay_groups.h"
#include "diffcheck.h"

#define IN_USE 0x021cfcb4u
#define LOADED 0x021cfcccu
#define REQUEST 0x020df328u
#define OWNER 0x021cfca0u

static u32 *words_at(uint32_t address)
{
    return (u32 *) (uintptr_t) address;
}

/* Some of the 46 groups in use and loaded (a loaded group is usually in use too), a request in
 * any state for any group or none, and an owner or not. */
static void set_state(DiffRng *rng)
{
    u32 *in_use = words_at(IN_USE);
    u32 *loaded = words_at(LOADED);
    for (int i = 0; i < 3; i++) {
        in_use[i] = 0;
        loaded[i] = 0;
    }
    int marked = diff_range(rng, 0, 4);
    for (int i = 0; i < marked; i++) {
        int group = diff_range(rng, 0, OVERLAY_GROUP_COUNT - 1);
        in_use[group >> 5] |= 1u << (group & 31);
        if (diff_range(rng, 0, 3) != 0) {
            loaded[group >> 5] |= 1u << (group & 31);
        }
    }
    OverlayGroupsRequest *req = (OverlayGroupsRequest *) (uintptr_t) REQUEST;
    req->state = (u8) diff_range(rng, 0, 3);
    req->group = (u8) diff_range(rng, 0, OVERLAY_GROUP_COUNT);
    *words_at(OWNER) = diff_range(rng, 0, 1) ? 0 : 0x02180000u + (u32) diff_range(rng, 0, 0xff) * 0x40;
}

/* A group, often one that is marked. */
static void a_group(DiffRng *rng, uint32_t args[4])
{
    set_state(rng);
    int group = diff_range(rng, 0, OVERLAY_GROUP_COUNT - 1);
    if (diff_range(rng, 0, 1) == 0) {
        for (int tries = 0; tries < 8; tries++) {
            int g = diff_range(rng, 0, OVERLAY_GROUP_COUNT - 1);
            if (words_at(IN_USE)[g >> 5] & (1u << (g & 31))) {
                group = g;
                break;
            }
        }
    }
    args[0] = (uint32_t) group;
}

#define GROUP_CALL(name, call)                                                                                                \
    static uint32_t name(const uint32_t args[4])                                                                              \
    {                                                                                                                         \
        return (uint32_t) call((int) args[0]);                                                                                \
    }

#define GROUP_CALL_VOID(name, call)                                                                                           \
    static uint32_t name(const uint32_t args[4])                                                                              \
    {                                                                                                                         \
        call((int) args[0]);                                                                                                  \
        return 0;                                                                                                             \
    }

GROUP_CALL_VOID(clear_in_use, OverlayGroups_ClearInUse)
GROUP_CALL_VOID(set_in_use, OverlayGroups_SetInUse)
GROUP_CALL(is_in_use, OverlayGroups_IsInUse)
GROUP_CALL_VOID(clear_loaded, OverlayGroups_ClearLoaded)
GROUP_CALL_VOID(set_loaded, OverlayGroups_SetLoaded)
GROUP_CALL(is_loaded, OverlayGroups_IsLoaded)
GROUP_CALL(request_for_owner, OverlayGroups_RequestForOwner)
GROUP_CALL(request, OverlayGroups_Request)

static uint32_t has_owner(const uint32_t args[4])
{
    (void) args;
    return (uint32_t) OverlayGroups_HasOwner();
}

static uint32_t is_idle(const uint32_t args[4])
{
    (void) args;
    return (uint32_t) OverlayGroups_IsIdle();
}

DIFF_CHECK(func_0206ff00, "main", 0x0206ff00 | 1, 0, 0, a_group, clear_in_use)
DIFF_CHECK(func_0206ff24, "main", 0x0206ff24 | 1, 0, 0, a_group, set_in_use)
DIFF_CHECK(func_0206ff48, "main", 0x0206ff48 | 1, 32, 0, a_group, is_in_use)
DIFF_CHECK(func_0206ff74, "main", 0x0206ff74 | 1, 0, 0, a_group, clear_loaded)
DIFF_CHECK(func_0206ff98, "main", 0x0206ff98 | 1, 0, 0, a_group, set_loaded)
DIFF_CHECK(func_0206ffbc, "main", 0x0206ffbc | 1, 32, 0, a_group, is_loaded)
DIFF_CHECK(func_0207000c, "main", 0x0207000c | 1, 32, 1, a_group, request_for_owner)
DIFF_CHECK(func_0207004c, "main", 0x0207004c | 1, 32, 1, a_group, request)
DIFF_CHECK(func_02070070, "main", 0x02070070 | 1, 32, 0, a_group, has_owner)
DIFF_CHECK(func_02070094, "main", 0x02070094 | 1, 32, 0, a_group, is_idle)
