/* The field actors' part C (FIELD_ACTOR_PART_C, a look byte at 0x59c of the actor), whose
 * model files are under "/PGls/" ("/PGls/<kind / 32>/<kind>.nsbmd"): each look names one of
 * four entries of the table at data_021c9e68, which holds the file's buffer
 * (GlassesLook_EntryFile), the VRAM region its texture is placed in (GlassesLook_EntryRegion),
 * the queued task that takes the texture to VRAM (GlassesLook_EntryTask) and the kind the
 * entry holds (GLASSES_LOOK_NO_KIND for none), as the body looks (body_look.h) do.
 *
 * A worn item gives the kind: items 0x1431 to 0x1470 kinds 0 to 63 (GlassesLook_FirstKind),
 * items 0x1471 to 0x1491 kinds 64 to 74 (GlassesLook_SecondKind). */
#ifndef CLEAN_MAIN_GLASSES_LOOK_H
#define CLEAN_MAIN_GLASSES_LOOK_H

#include "main/model_loader.h"
#include "main/vram_region.h"
#include "types.h"

/* The number of entries, also a look byte's value for none. */
#define GLASSES_LOOK_COUNT 4
/* The number of kinds, also the kind of an entry that holds none. */
#define GLASSES_LOOK_NO_KIND 0x4b

/* The table at data_021c9e68 (a global C++ object): for each entry the buffer the model file
 * is read into, taken from the scene's heap at data_021c9adc for the session's players only,
 * its texture's VRAM region, the task that takes the texture there (a VramCopyTask,
 * vram_copy_task.h) and the kind the entry holds. */
typedef struct GlassesLookTable {
    u8 *file[GLASSES_LOOK_COUNT];             /* 0x00 */
    VramRegion region[GLASSES_LOOK_COUNT];    /* 0x10 */
    ModelLoaderTask task[GLASSES_LOOK_COUNT]; /* 0x60 */
    u8 kind[GLASSES_LOOK_COUNT];              /* 0xd0 */
} GlassesLookTable;

void GlassesLook_SetKind(unsigned char *look, int kind);
int GlassesLook_Kind(unsigned char *look);
ModelLoaderTask *GlassesLook_Task(unsigned char *look);
VramRegion *GlassesLook_Region(unsigned char *look);
unsigned long GlassesLook_File(unsigned char *look);
int GlassesLook_PollUpload(void *look);
void GlassesLook_PlaceTexture(unsigned char *look);
void GlassesLook_Load(unsigned char *look, int kind);
void GlassesLook_StopUpload(void *look);
void GlassesLook_Unload(unsigned char *look);
void GlassesLook_SetLook(unsigned char *look, int entry);
void GlassesLook_DestructLook(void *look);
void GlassesLook_ConstructLook(unsigned char *look);
void GlassesLook_SetEntryKind(GlassesLookTable *table, int entry, int kind);
int GlassesLook_EntryKind(GlassesLookTable *table, int entry);
ModelLoaderTask *GlassesLook_EntryTask(GlassesLookTable *table, int entry);
VramRegion *GlassesLook_EntryRegion(GlassesLookTable *table, int entry);
unsigned long GlassesLook_EntryFile(GlassesLookTable *table, int entry);
void GlassesLook_Clear(GlassesLookTable *table);
void GlassesLook_AllocEntries(GlassesLookTable *table);
GlassesLookTable *GlassesLook_DestructTable(GlassesLookTable *table);
GlassesLookTable *GlassesLook_ConstructTable(GlassesLookTable *table);
int GlassesLook_PaletteSize(void);
int GlassesLook_Texture4x4Size(void);
int GlassesLook_TextureSize(void);
unsigned char GlassesLook_SecondKind(unsigned int index);
unsigned char GlassesLook_FirstKind(unsigned int index);
int GlassesLook_FileSize(void);

#endif
