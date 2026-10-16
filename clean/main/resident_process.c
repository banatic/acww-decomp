/* The resident process and the processes spawned at boot (resident_process.h). */
#include "resident_process.h"

#include "acre_kind.h"       /* AcreKind_Load, AcreKind_Free */
#include "acre_map.h"        /* AcreMap_Create..., AcreMap_Free... */
#include "autoload_2/heap.h" /* Heap_FreeAux */
#include "building_shapes.h" /* BuildingShapes_Load, BuildingShapes_Free */
#include "clean.h"
#include "design_assets.h"  /* DesignArchive_Get, DesignArchive_Open, DesignArchive_Close */
#include "furniture_info.h" /* FurnitureInfo_Open, FurnitureInfo_Close */
#include "session_link.h"   /* Session_CreateHeap, Session_FreeHeap */

/* Vtables: the resident process's, and its base class's. */
extern const u32 data_020e360c[];
extern const u32 data_020da13c[];

extern Heap *data_021fbe94;                                /* the current heap */
extern Process *data_021dc740;                             /* the resident process */
extern const u16 data_020d1adc[RESIDENT_PROCESS_CHILDREN]; /* the classes of the root's children */

/* Opening and closing the resources at data_021cb5e0; two empty functions; clearing the state
 * at data_021d2128. */
extern void func_02062b04(void);
extern void func_02062af4(void);
extern void func_020a6c94(void);
extern void func_020a6c90(void);
extern void func_02085e94(void);
/* Starts the scene asked for, once (data_020e3c80, 0xd8 once started). */
extern int func_020a536c(void);
/* Asks for scene 1. */
extern void func_020a53c4(void);
/* Process_SpawnRoot and Process_SpawnChild, through main's wrappers. */
extern int func_0202f12c(int class_id, int param, int unk_12);
extern int func_0202f134(int class_id, int parent, int param, int unk_12);

#define ROOT_CLASS 0

/* func_0209d9d4: the destructor. */
Process *ResidentProcess_Destruct(Process *self)
{
    self->vtable = data_020e360c;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    return self;
}
CLEAN_AS(func_0209d9d4, ResidentProcess_Destruct)

/* func_0209d9f4: the destructor, then the object freed. */
Process *ResidentProcess_DestructFree(Process *self)
{
    self->vtable = data_020e360c;
    self->vtable = data_020da13c;
    Process_Destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_0209d9f4, ResidentProcess_DestructFree)

/* func_0209da1c (vtable slot 9): nothing to draw; done. */
int ResidentProcess_Draw(void)
{
    return 1;
}
CLEAN_AS(func_0209da1c, ResidentProcess_Draw)

/* func_0209da20 (vtable slot 6): the scene asked for started; done.
 * QUIRK: the answer of func_020a536c is dropped. */
int ResidentProcess_Execute(void)
{
    func_020a536c();
    return 1;
}
CLEAN_AS(func_0209da20, ResidentProcess_Execute)

/* func_0209da30 (vtable slot 3): what Create loaded freed, in the same order; done at once. */
int ResidentProcess_Delete(void)
{
    BuildingShapes_Free();
    AcreKind_Free();
    FurnitureInfo_Close();
    func_02062af4();
    DesignArchive_Close((RecordFile *) (uintptr_t) DesignArchive_Get());
    AcreMap_FreeTemplateSet((int) (uintptr_t) data_021fbe94);
    AcreMap_FreeTown(data_021fbe94);
    AcreMap_FreeRooms((int) (uintptr_t) data_021fbe94);
    Session_FreeHeap();
    func_020a6c90();
    return 1;
}
CLEAN_AS(func_0209da30, ResidentProcess_Delete)

/* func_0209da78 (vtable slot 0): the process noted in data_021dc740 and the resources loaded,
 * the template set, town, rooms and session heap from the current heap; done at once. */
int ResidentProcess_Create(Process *self)
{
    data_021dc740 = self;
    BuildingShapes_Load();
    AcreKind_Load();
    FurnitureInfo_Open();
    func_02062b04();
    DesignArchive_Open((RecordFile *) (uintptr_t) DesignArchive_Get());
    AcreMap_CreateTemplateSet((int) (uintptr_t) data_021fbe94);
    AcreMap_CreateTown(data_021fbe94);
    AcreMap_CreateRooms(data_021fbe94);
    Session_CreateHeap(data_021fbe94);
    func_020a6c94();
    func_02085e94();
    return 1;
}
CLEAN_AS(func_0209da78, ResidentProcess_Create)

/* func_0209dae8 (at boot): scene 1 asked for, the root process spawned, and under it the seven
 * classes of data_020d1adc (0xd7, 0xce, 0xcf, 0xcb, 8, 0xa, 0xcc). */
void ResidentProcess_SpawnAll(void)
{
    func_020a53c4();
    int root = func_0202f12c(ROOT_CLASS, 0, 1);
    for (int i = 0; i < RESIDENT_PROCESS_CHILDREN; i++) {
        func_0202f134(data_020d1adc[i], root, 0, 0);
    }
}
CLEAN_AS(func_0209dae8, ResidentProcess_SpawnAll)
