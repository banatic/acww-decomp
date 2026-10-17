/* Overlay 93's object, made and handed on by overlay 4 (music_show_overlay.h). */
#include "music_show_overlay.h"

#include "autoload_2/heap.h" /* Heap, Heap_Alloc, Heap_Free */
#include "clean.h"
#include "main/overlay_slots.h"

/* The object's size. */
#define MUSIC_SHOW_OVERLAY_SIZE 0x2520
/* Its flag that the show has ended. */
#define MUSIC_SHOW_OVERLAY_ENDED 8
/* What a restart takes for a value that is not positive. */
#define MUSIC_SHOW_OVERLAY_DEFAULT_VALUE 0x125c

/* Bit 0: the object exists. */
extern u8 data_ov004_0225ff50;
/* The object. */
extern void *data_ov004_0225ff54;
/* The scenes' heap (scene_heaps.c). */
extern Heap *data_021c9b28;
/* Overlay 93's number, a linker symbol. */
extern char SDK_OVERLAY_ov093_ID;

/* Overlay 93's functions on the object. */
extern int func_ov093_02299418(void *object);             /* whether bit 8 of its flags is set */
extern void func_ov093_02299424(void *object);            /* display registers set, its state 4 */
extern void func_ov093_022994ac(void *object, int value); /* restarted with `value`, state 1 */
extern void func_ov093_0229959c(void *object);            /* stopped */
extern void func_ov093_022995b0(void *object);            /* its two buffers uploaded when due */
extern void func_ov093_02299630(void *object);            /* its update */
extern void func_ov093_0229976c(void *object);            /* started */
extern void *func_ov093_022997b4(void *object);           /* the destructor */
extern void *func_ov093_022997f8(void *object);           /* the constructor */

/* Whether the object exists. */
static int MusicShowOverlay_exists(void)
{
    return (data_ov004_0225ff50 & 1) != 0;
}

/* func_ov004_02246900: whether the show has ended; 0 without the object. */
int MusicShowOverlay_HasEnded(void)
{
    if (MusicShowOverlay_exists()) {
        return func_ov093_02299418(data_ov004_0225ff54);
    }
    return 0;
}
CLEAN_AS(func_ov004_02246900, MusicShowOverlay_HasEnded)

/* func_ov004_0224692c: the object's change of the display registers (its state 4). */
void MusicShowOverlay_SetDisplay(void)
{
    if (MusicShowOverlay_exists()) {
        func_ov093_02299424(data_ov004_0225ff54);
    }
}
CLEAN_AS(func_ov004_0224692c, MusicShowOverlay_SetDisplay)

/* func_ov004_02246954: the object restarted with `value` (0x125c when it is not positive). */
void MusicShowOverlay_Restart(int value)
{
    if (MusicShowOverlay_exists()) {
        if (value <= 0) {
            value = MUSIC_SHOW_OVERLAY_DEFAULT_VALUE;
        }
        func_ov093_022994ac(data_ov004_0225ff54, value);
    }
}
CLEAN_AS(func_ov004_02246954, MusicShowOverlay_Restart)

/* func_ov004_02246988: the object, when it exists, stopped, destructed and freed, and overlay
 * 93 released; then marked as gone. */
void MusicShowOverlay_Close(void)
{
    if (MusicShowOverlay_exists()) {
        func_ov093_0229959c(data_ov004_0225ff54);
        Heap *heap = data_021c9b28;
        func_ov093_022997b4(data_ov004_0225ff54);
        Heap_Free(heap, data_ov004_0225ff54);
        data_ov004_0225ff54 = NULL;
        OverlaySlots_Release((u8) (uintptr_t) &SDK_OVERLAY_ov093_ID);
    }
    data_ov004_0225ff50 = 0;
}
CLEAN_AS(func_ov004_02246988, MusicShowOverlay_Close)

/* func_ov004_022469dc: the object's two buffers uploaded when due. */
void MusicShowOverlay_Upload(void)
{
    if (MusicShowOverlay_exists()) {
        func_ov093_022995b0(data_ov004_0225ff54);
    }
}
CLEAN_AS(func_ov004_022469dc, MusicShowOverlay_Upload)

/* func_ov004_02246a04: the object's update. */
void MusicShowOverlay_Update(void)
{
    if (MusicShowOverlay_exists()) {
        func_ov093_02299630(data_ov004_0225ff54);
    }
}
CLEAN_AS(func_ov004_02246a04, MusicShowOverlay_Update)

/* func_ov004_02246a2c: overlay 93 loaded, the object made from the scenes' heap and
 * constructed, then started, and marked as existing.
 * BUG: when the heap has no room the object is started at address 0 and marked as existing
 * all the same. BUGFIX: nothing is started or marked then. */
void MusicShowOverlay_Open(void)
{
    OverlaySlots_Load((u8) (uintptr_t) &SDK_OVERLAY_ov093_ID);
    data_ov004_0225ff54 = Heap_Alloc(data_021c9b28, MUSIC_SHOW_OVERLAY_SIZE);
    if (data_ov004_0225ff54 != NULL) {
        func_ov093_022997f8(data_ov004_0225ff54);
    }
#ifdef BUGFIX
    if (data_ov004_0225ff54 == NULL) {
        return;
    }
#endif
    func_ov093_0229976c(data_ov004_0225ff54);
    data_ov004_0225ff50 = 1;
}
CLEAN_AS(func_ov004_02246a2c, MusicShowOverlay_Open)
