/* The field actors' accessory (FIELD_ACTOR_ACCESSORY, a look byte at 0x59c of the actor), whose
 * model files are under "/PGls/" ("/PGls/<kind / 32>/<kind>.nsbmd"): each look names one of
 * four entries of the table at data_021c9e68, which holds the file's buffer
 * (AccessoryLook_EntryFile), the VRAM region its texture is placed in (AccessoryLook_EntryRegion),
 * the queued task that takes the texture to VRAM (AccessoryLook_EntryTask) and the kind the
 * entry holds (ACCESSORY_LOOK_NO_KIND for none), as the body looks (body_look.h) do.
 *
 * A worn item gives the kind: items 0x1431 to 0x1470 kinds 0 to 63 (AccessoryLook_FirstKind),
 * items 0x1471 to 0x1491 kinds 64 to 74 (AccessoryLook_SecondKind). */
#ifndef CLEAN_MAIN_GLASSES_LOOK_H
#define CLEAN_MAIN_GLASSES_LOOK_H

#include "main/model_loader.h"
#include "main/vram_region.h"
#include "types.h"

/* The number of entries, also a look byte's value for none. */
#define ACCESSORY_LOOK_COUNT 4
/* The number of kinds, also the kind of an entry that holds none. */
#define ACCESSORY_LOOK_NO_KIND 0x4b

/* The table at data_021c9e68 (a global C++ object): for each entry the buffer the model file
 * is read into, taken from the scene's heap at data_021c9adc for the session's players only,
 * its texture's VRAM region, the task that takes the texture there (a VramCopyTask,
 * vram_copy_task.h) and the kind the entry holds. */
typedef struct AccessoryLookTable {
    u8 *file[ACCESSORY_LOOK_COUNT];             /* 0x00 */
    VramRegion region[ACCESSORY_LOOK_COUNT];    /* 0x10 */
    ModelLoaderTask task[ACCESSORY_LOOK_COUNT]; /* 0x60 */
    u8 kind[ACCESSORY_LOOK_COUNT];              /* 0xd0 */
} AccessoryLookTable;

void AccessoryLook_SetKind(unsigned char *look, int kind);
int AccessoryLook_Kind(unsigned char *look);
ModelLoaderTask *AccessoryLook_Task(unsigned char *look);
VramRegion *AccessoryLook_Region(unsigned char *look);
unsigned long AccessoryLook_File(unsigned char *look);
int AccessoryLook_PollUpload(void *look);
void AccessoryLook_PlaceTexture(unsigned char *look);
void AccessoryLook_Load(unsigned char *look, int kind);
void AccessoryLook_StopUpload(void *look);
void AccessoryLook_Unload(unsigned char *look);
void AccessoryLook_SetLook(unsigned char *look, int entry);
void AccessoryLook_DestructLook(void *look);
void AccessoryLook_ConstructLook(unsigned char *look);
void AccessoryLook_SetEntryKind(AccessoryLookTable *table, int entry, int kind);
int AccessoryLook_EntryKind(AccessoryLookTable *table, int entry);
ModelLoaderTask *AccessoryLook_EntryTask(AccessoryLookTable *table, int entry);
VramRegion *AccessoryLook_EntryRegion(AccessoryLookTable *table, int entry);
unsigned long AccessoryLook_EntryFile(AccessoryLookTable *table, int entry);
void AccessoryLook_Clear(AccessoryLookTable *table);
void AccessoryLook_AllocEntries(AccessoryLookTable *table);
AccessoryLookTable *AccessoryLook_DestructTable(AccessoryLookTable *table);
AccessoryLookTable *AccessoryLook_ConstructTable(AccessoryLookTable *table);
int AccessoryLook_PaletteSize(void);
int AccessoryLook_Texture4x4Size(void);
int AccessoryLook_TextureSize(void);
unsigned char AccessoryLook_SecondKind(unsigned int index);
unsigned char AccessoryLook_FirstKind(unsigned int index);
int AccessoryLook_FileSize(void);
char *AccessoryLook_Path(unsigned int kind);
void AccessoryLook_EndScene(void);
void AccessoryLook_StartScene(Heap *parent);

#endif
