/* The field actors' head (FIELD_ACTOR_PART_B, a look byte at 0x428 of the actor): up to two
 * models, whose files are under "/PHead/" ("/PHead/<kind / 32>/<kind>.nsbmd"). Each look names
 * one of four entries of the table at data_021c9f5c (data_020c75e4 gives each player its
 * entry); an entry has one buffer both model files are read into, one after the other, and for
 * each of its two models the VRAM region its texture is placed in, the queued task that takes
 * the texture there, where the file starts in the buffer and its kind (HEAD_LOOK_NO_KIND for
 * none). The second model's texture goes in the first one's region, right after the first's.
 *
 * The first model is the hair (one of 16 kinds), the same hair under a hat (16 more), or what an
 * item 0x13a8 to 0x13c7 worn on the head gives (kinds 32 to 63); the second, when there is one,
 * is what items 0x13c8 to 0x1407 (kinds 64 to 135), the design items 0x1429 to 0x1430 (kind
 * 0x80 or 0x81, wearing the design) and some of items 0x1408 to 0x1428 (kinds 136 to 157) give
 * (HeadLook_ChooseModels). */
#ifndef CLEAN_MAIN_HEAD_LOOK_H
#define CLEAN_MAIN_HEAD_LOOK_H

#include "main/lookups.h"
#include "main/model_loader.h"
#include "main/vram_region.h"
#include "types.h"

/* The number of entries, also a look byte's value for none. */
#define HEAD_LOOK_COUNT 4
/* An entry's models: the first, then the second. */
#define HEAD_LOOK_MODELS 2
/* The kind of a model that is not there. */
#define HEAD_LOOK_NO_KIND 0x9e

typedef struct HeadLookTable {
    u8 *file[HEAD_LOOK_COUNT];                               /* 0x000: the buffers */
    VramRegion region[HEAD_LOOK_COUNT][HEAD_LOOK_MODELS];    /* 0x010 */
    ModelLoaderTask task[HEAD_LOOK_COUNT][HEAD_LOOK_MODELS]; /* 0x0b0: a VramCopyTask each */
    u8 *model[HEAD_LOOK_COUNT][HEAD_LOOK_MODELS];            /* 0x190: each model file in the buffer */
    u8 kind[HEAD_LOOK_COUNT][HEAD_LOOK_MODELS];              /* 0x1b0 */
} HeadLookTable;

void HeadLook_SetKind(unsigned char *look, int model, int kind);
int HeadLook_Kind(const unsigned char *look, int model);
int HeadLook_Task(unsigned char *look, int model);
int HeadLook_Region(unsigned char *look, int model);
void HeadLook_SetModel(unsigned char *look, int model, u8 *file);
int HeadLook_Model(unsigned char *look, unsigned int model);
int HeadLook_File(unsigned char *look);
int HeadLook_PollUpload(unsigned char *look);
void HeadLook_PlaceTextures(unsigned char *look);
int HeadLook_Load(unsigned char *look, int first, int second, ItemCode *item, u8 *record);
void HeadLook_StopUploads(unsigned char *look);
void HeadLook_Unload(unsigned char *look);
void HeadLook_SetLook(unsigned char *look, int entry);
void HeadLook_DestructLook(void *look);
void HeadLook_ConstructLook(unsigned char *look);
void HeadLook_SetEntryKind(HeadLookTable *table, int entry, int model, unsigned char kind);
unsigned char HeadLook_EntryKind(HeadLookTable *table, int entry, int model);
ModelLoaderTask *HeadLook_EntryTask(HeadLookTable *table, int entry, int model);
VramRegion *HeadLook_EntryRegion(HeadLookTable *table, int entry, int model);
void HeadLook_SetEntryModel(HeadLookTable *table, int entry, int model, u8 *file);
int HeadLook_EntryModel(HeadLookTable *table, int entry, int model);
unsigned long HeadLook_EntryFile(HeadLookTable *table, int entry);
void HeadLook_Clear(HeadLookTable *table);
void HeadLook_AllocEntries(HeadLookTable *table);
HeadLookTable *HeadLook_DestructTable(HeadLookTable *table);
HeadLookTable *HeadLook_ConstructTable(HeadLookTable *table);
int HeadLook_PaletteSize(void);
int HeadLook_Texture4x4Size(void);
int HeadLook_TextureSize(void);
int HeadLook_BlockSize(void);
void HeadLook_ChooseModels(int flag, int hair, ItemCode *item, int *first, int *second);
unsigned char HeadLook_ItemCModel(unsigned int index);
unsigned char HeadLook_ItemAModel(unsigned int index);
unsigned char HeadLook_ItemBModel(unsigned int index);
unsigned char HeadLook_CoveredHairModel(unsigned char hair);
unsigned char HeadLook_HairModel(unsigned int hair);
char *HeadLook_Path(unsigned int kind);
void HeadLook_EndScene(void);
void HeadLook_StartScene(Heap *parent);

#endif
