/* The background models of the field (data_021c52c0, 0x64c bytes): up to 31 acre models loaded
 * from "/bg/a<model / 16>/<model>.arc" into the background heap (data_021c9b24), the 0x180 bytes
 * of acre data of up to 9 models (the archive's "bcl0"), and the ground's and the water's
 * textures and animations shared by every acre.
 *
 * Each archive holds the model ("bmd0"), the acre data ("bcl0"), "bsd0", optional joint,
 * material colour and texture coordinate animations ("bca0", "bma0", "bta0") and a list of marks
 * ("mgt0": a count, then entries of a kind and a position in the acre). Models 0x1000-0x1fff
 * also have a texture of their own, "/bg/t<model / 16>/<model>.nsbtx". */
#ifndef CLEAN_MAIN_BG_MODELS_H
#define CLEAN_MAIN_BG_MODELS_H

#include "autoload_2/heap.h"
#include "types.h"

#define BG_MODELS_SLOTS 31
#define BG_MODELS_DATA_SLOTS 9
#define BG_MODEL_NONE 0xffff
#define BG_MODEL_DATA_SIZE 0x180

/* An acre model, free while `archive` is NULL. */
typedef struct BgModel {
    u32 key;          /* 0x00: the model number; BG_MODEL_NONE when cleared */
    u8 *archive;      /* 0x04: the loaded archive */
    u8 *model;        /* 0x08: the first model of "bmd0" */
    u8 *data;         /* 0x0c: "bcl0", BG_MODEL_DATA_SIZE bytes of acre data */
    u8 *bsd;          /* 0x10: "bsd0" */
    u8 *joint_anim;   /* 0x14: the first animation of "bca0", when there is one */
    u8 *colour_anim;  /* 0x18: the same of "bma0" */
    u8 *texture_anim; /* 0x1c: the same of "bta0" */
    void *texture;    /* 0x20: the model's own texture (models 0x1000-0x1fff) */
    u32 archive_size; /* 0x24 */
    u8 *marks;        /* 0x28: the entries of "mgt0" */
    s32 mark_count;   /* 0x2c */
} BgModel;

/* The acre data of a model, free while `data` is NULL. */
typedef struct BgModelData {
    u32 key;  /* the model number; BG_MODEL_NONE when cleared */
    u8 *data; /* BG_MODEL_DATA_SIZE bytes */
} BgModelData;

typedef struct BgModels {
    BgModel models[BG_MODELS_SLOTS];        /* 0x000 */
    BgModelData data[BG_MODELS_DATA_SLOTS]; /* 0x5d0 */
    u8 full;                                /* 0x618: the ground's animations are loaded */
    u8 unk_619[3];
    u32 heap_size;           /* 0x61c: the background heap's size in bytes */
    u32 unk_620[4];          /* only cleared */
    void *ground_texture;    /* 0x630: "/bg/ct<n>/grd_set<n><season>.nsbtx" */
    u8 *ground_colour_anim;  /* 0x634: of "grd_set.nsbma" */
    u8 *ground_texture_anim; /* 0x638: of "grd_set.nsbta" */
    u8 *river_pattern_anim;  /* 0x63c: of "riv.nsbtp" */
    void *river_texture;     /* 0x640: "riv_itp.nsbtx" */
    u8 *beb_pattern_anim;    /* 0x644: of "beB.nsbtp" */
    void *beb_texture;       /* 0x648: "beB_itp.nsbtx" */
} BgModels;

/* A mark of "mgt0": its kind, and its position in the acre (fx32). */
typedef struct BgMark {
    s32 kind;
    fx32 x;
    fx32 z;
} BgMark;

int BgModels_Get(void);
void BgModels_MarkAt(BgMark *out, const u8 *marks, int index);
int BgModels_MarkCount(const s16 *marks);
u32 BgModels_BebTexture(const BgModels *self);
u32 BgModels_BebPatternAnim(const BgModels *self);
u32 BgModels_RiverTexture(const BgModels *self);
int BgModels_RiverPatternAnim(const BgModels *self);
u32 BgModels_GroundTextureAnim(const BgModels *self);
u32 BgModels_GroundColourAnim(const BgModels *self);
u32 BgModels_GroundTexture(const BgModels *self);
int BgModels_Release(BgModels *self);
BgModel *BgModels_Load(BgModels *self, int key);
int BgModels_Data(BgModels *self, int key);
void *BgModels_LoadData(int key, Heap *heap);
void BgModels_LoadGroundAnims(BgModels *self);
void BgModels_LoadGroundTexture(BgModels *self);
u32 BgModels_TownSetting(BgModels *self);
int BgModels_SetUp(BgModels *self, int full);
void BgModels_Clear(BgModels *self);
void BgModels_Destruct(BgModels *self);
int BgModels_Construct(BgModels *self);
void *BgModels_LoadFile(const char *path, u32 *size);

#endif
