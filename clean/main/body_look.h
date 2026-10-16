/* The field actors' body looks (FIELD_ACTOR_BODY_LOOK, a slot byte at 0x389 of the actor):
 * each names one of four entries of the table at data_021c9c2c, which holds a body texture
 * file (func_0205d0e0), the VRAM region it is placed in (func_0205d0d4) and the queued task
 * that takes it to VRAM (func_0205d0c8, model_loader.h). */
#ifndef CLEAN_MAIN_BODY_LOOK_H
#define CLEAN_MAIN_BODY_LOOK_H

#include "main/model_loader.h"
#include "main/vram_region.h"
#include "types.h"

ModelLoaderTask *BodyLook_Task(unsigned char *look);
VramRegion *BodyLook_Region(unsigned char *look);
int BodyLook_File(unsigned char *look);
int BodyLook_PollUpload(void *look);
void BodyLook_PlaceTexture(void *look);

/* The number of entries, also a look byte's value for none. */
#define BODY_LOOK_COUNT 4

/* The table at data_021c9c2c (a global C++ object, 0xd0 bytes): for each entry the buffer its
 * body model file ("/PBody/boy.nsbmd" or "/PBody/grl.nsbmd") is read into, taken from the
 * scene's heap at data_021c9ae8 for the session's players only, the VRAM region of the file's
 * texture and the task that takes the texture there (a VramCopyTask, vram_copy_task.h). */
typedef struct BodyLookTable {
    u8 *file[BODY_LOOK_COUNT];             /* 0x00 */
    VramRegion region[BODY_LOOK_COUNT];    /* 0x10 */
    ModelLoaderTask task[BODY_LOOK_COUNT]; /* 0x60 */
} BodyLookTable;

void BodyLook_LoadModel(unsigned char *look, int girl);
void BodyLook_StopUpload(unsigned char *look);
void BodyLook_SetLook(unsigned char *look, int entry);
void BodyLook_DestructLook(void *look);
void BodyLook_ConstructLook(unsigned char *look);
ModelLoaderTask *BodyLook_EntryTask(BodyLookTable *table, int entry);
VramRegion *BodyLook_EntryRegion(BodyLookTable *table, int entry);
unsigned long BodyLook_EntryFile(BodyLookTable *table, int entry);
void BodyLook_Clear(BodyLookTable *table);
void BodyLook_AllocEntries(BodyLookTable *table);
BodyLookTable *BodyLook_DestructTable(BodyLookTable *table);
BodyLookTable *BodyLook_ConstructTable(BodyLookTable *table);
int BodyLook_PaletteSize(void);
int BodyLook_Texture4x4Size(void);
int BodyLook_TextureSize(void);
int BodyLook_FileSize(void);
unsigned int BodyLook_ModelPath(unsigned int girl);
void BodyLook_EndScene(void);
void BodyLook_StartScene(Heap *parent);

#endif
