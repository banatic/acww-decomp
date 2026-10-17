/* The indoor room's own object (room_manager.h). */
#include "room_manager.h"

#include "clean.h"

static_assert(offsetof(RoomManager, tv) == 0x064, "TV broadcast");
static_assert(offsetof(RoomManager, mover) == 0x1c4, "furniture mover");
static_assert(offsetof(RoomManager, broadcast_changed) == 0x2b0, "broadcast changed");

/* The room, NULL while none is set up. */
extern RoomManager *data_ov004_022595c0;

/* func_ov004_0223b22c: the room's furniture mover, NULL without a room. */
FurnitureMover *RoomManager_Mover(void)
{
    RoomManager *room = data_ov004_022595c0;
    if (room != NULL) {
        return (FurnitureMover *) (void *) room->mover;
    }
    return NULL;
}
CLEAN_AS(func_ov004_0223b22c, RoomManager_Mover)

/* func_ov004_0223b258: 0 without a room. */
int RoomManager_BroadcastChanged(void)
{
    if (data_ov004_022595c0 != NULL) {
        return data_ov004_022595c0->broadcast_changed;
    }
    return 0;
}
CLEAN_AS(func_ov004_0223b258, RoomManager_BroadcastChanged)

/* func_ov004_0223b274 */
void RoomManager_SetBroadcastChanged(void)
{
    if (data_ov004_022595c0 != NULL) {
        data_ov004_022595c0->broadcast_changed = 1;
    }
}
CLEAN_AS(func_ov004_0223b274, RoomManager_SetBroadcastChanged)
