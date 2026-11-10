/* Overlay 93's staff roll, made and handed on by overlay 4 (staff_roll_overlay.h). */
#include "staff_roll_overlay.h"

#include "autoload_2/heap.h" /* Heap, Heap_Alloc, Heap_Free */
#include "clean.h"
#include "main/overlay_slots.h"
#include "ov093/staff_roll.h"

/* The object's size. */
#define STAFF_ROLL_OVERLAY_SIZE 0x2520
/* Its flag that the show has ended. */
#define STAFF_ROLL_OVERLAY_ENDED 8
/* The speed a restart takes for one that is not positive. */
#define STAFF_ROLL_OVERLAY_DEFAULT_SPEED 0x125c

/* Bit 0: the object exists. */
extern u8 data_ov004_0225ff50;
/* The object. */
extern StaffRoll *data_ov004_0225ff54;
/* The scenes' heap (scene_heaps.c). */
extern Heap *data_021c9b28;
/* Overlay 93's number, a linker symbol. */
extern char SDK_OVERLAY_ov093_ID;

/* Whether the object exists. */
static int staff_roll_overlay_exists(void)
{
    return (data_ov004_0225ff50 & 1) != 0;
}

/* func_ov004_02246900: whether the show has ended; 0 without the object. */
int StaffRollOverlay_HasEnded(void)
{
    if (staff_roll_overlay_exists()) {
        return StaffRoll_HasEnded(data_ov004_0225ff54);
    }
    return 0;
}
CLEAN_AS(func_ov004_02246900, StaffRollOverlay_HasEnded)

/* func_ov004_0224692c: the roll's switch to its logo (its state 4). */
void StaffRollOverlay_ShowLogo(void)
{
    if (staff_roll_overlay_exists()) {
        StaffRoll_ShowLogo(data_ov004_0225ff54);
    }
}
CLEAN_AS(func_ov004_0224692c, StaffRollOverlay_ShowLogo)

/* func_ov004_02246954: the roll restarted at `speed` (0x125c when it is not positive). */
void StaffRollOverlay_Restart(int speed)
{
    if (staff_roll_overlay_exists()) {
        if (speed <= 0) {
            speed = STAFF_ROLL_OVERLAY_DEFAULT_SPEED;
        }
        StaffRoll_Restart(data_ov004_0225ff54, speed);
    }
}
CLEAN_AS(func_ov004_02246954, StaffRollOverlay_Restart)

/* func_ov004_02246988: the object, when it exists, stopped, destructed and freed, and overlay
 * 93 released; then marked as gone. */
void StaffRollOverlay_Close(void)
{
    if (staff_roll_overlay_exists()) {
        StaffRoll_Close(data_ov004_0225ff54);
        Heap *heap = data_021c9b28;
        StaffRoll_Destruct(data_ov004_0225ff54);
        Heap_Free(heap, data_ov004_0225ff54);
        data_ov004_0225ff54 = NULL;
        OverlaySlots_Release((u8) (uintptr_t) &SDK_OVERLAY_ov093_ID);
    }
    data_ov004_0225ff50 = 0;
}
CLEAN_AS(func_ov004_02246988, StaffRollOverlay_Close)

/* func_ov004_022469dc: the object's two buffers uploaded when due. */
void StaffRollOverlay_Upload(void)
{
    if (staff_roll_overlay_exists()) {
        StaffRoll_Upload(data_ov004_0225ff54);
    }
}
CLEAN_AS(func_ov004_022469dc, StaffRollOverlay_Upload)

/* func_ov004_02246a04: the object's update. */
void StaffRollOverlay_Update(void)
{
    if (staff_roll_overlay_exists()) {
        StaffRoll_Update(data_ov004_0225ff54);
    }
}
CLEAN_AS(func_ov004_02246a04, StaffRollOverlay_Update)

/* func_ov004_02246a2c: overlay 93 loaded, the object made from the scenes' heap and
 * constructed, then started, and marked as existing.
 * BUG: when the heap has no room the object is started at address 0 and marked as existing
 * all the same. BUGFIX: nothing is started or marked then. */
void StaffRollOverlay_Open(void)
{
    OverlaySlots_Load((u8) (uintptr_t) &SDK_OVERLAY_ov093_ID);
    data_ov004_0225ff54 = Heap_Alloc(data_021c9b28, STAFF_ROLL_OVERLAY_SIZE);
    if (data_ov004_0225ff54 != NULL) {
        StaffRoll_Construct(data_ov004_0225ff54);
    }
#ifdef BUGFIX
    if (data_ov004_0225ff54 == NULL) {
        return;
    }
#endif
    StaffRoll_Start(data_ov004_0225ff54);
    data_ov004_0225ff50 = 1;
}
CLEAN_AS(func_ov004_02246a2c, StaffRollOverlay_Open)
