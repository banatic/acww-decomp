/* An acre of a map of acres (acre_record.h). */
#include "acre_record.h"

#include "acre_kind.h"
#include "clean.h"

static_assert(offsetof(AcreRecord, x) == 0x04, "acre x");
static_assert(offsetof(AcreRecord, position) == 0x0c, "acre position");
static_assert(offsetof(AcreRecord, layers) == 0x18, "acre layers");
static_assert(offsetof(AcreRecord, bg_model) == 0x20, "acre background model");
static_assert(offsetof(AcreRecord, bits) == 0x24, "acre bits");
static_assert(sizeof(AcreRecord) == 0x28, "acre size");
static_assert(offsetof(BgModel, data) == 0x0c, "background model data");

/* Whether a model number is one of the six of the table at data_020d1ac0 (0x18, 0x19, 0x1c,
 * 0x1f, 0x22 and 0x25). */
extern int func_0209d048(int model);
/* Registers acre data with the map in entry `slot` of the table at data_021c31ec, for the acre
 * at (x, z). */
extern int func_02030c84(int x, int z, int data, int slot);

/* func_02037d14: the tile (x, z) of an index into a layer: x in its low 4 bits, z in the next
 * four. */
void AcreRecord_TileOfIndex(int *x, int *z, int index)
{
    *x = index & 0xf;
    *z = (int) (((unsigned int) index >> 4) & 0xf);
}
CLEAN_AS(func_02037d14, AcreRecord_TileOfIndex)

/* func_02037d2c: the bit of tile (x, z) cleared, when the acre has bits; whether it was. */
int AcreRecord_ClearTileBit(AcreRecord *acre, int x, int z)
{
    if (acre->bits != NULL) {
        return AcreBits_Clear(acre->bits, (unsigned int) x, (unsigned int) z);
    }
    return 0;
}
CLEAN_AS(func_02037d2c, AcreRecord_ClearTileBit)

/* func_02037d48: the bit of tile (x, z) set, when the acre has bits; whether it was. */
int AcreRecord_SetTileBit(AcreRecord *acre, int x, int z)
{
    if (acre->bits != NULL) {
        return AcreBits_Set(acre->bits, (unsigned int) x, (unsigned int) z);
    }
    return 0;
}
CLEAN_AS(func_02037d48, AcreRecord_SetTileBit)

/* func_02037d64: whether the acre has any of `flags`. */
int AcreRecord_HasAnyFlag(AcreRecord *acre, int flags)
{
    return (flags & AcreRecord_Flags(acre)) != 0;
}
CLEAN_AS(func_02037d64, AcreRecord_HasAnyFlag)

/* func_02037d80: whether the acre has all of `flags`. */
int AcreRecord_HasAllFlags(AcreRecord *acre, unsigned int flags)
{
    unsigned int own = (unsigned int) AcreRecord_Flags(acre);
    return (flags & own) == flags;
}
CLEAN_AS(func_02037d80, AcreRecord_HasAllFlags)

/* func_02037d9c: the flags of the acre's model's kind. */
int AcreRecord_Flags(AcreRecord *acre)
{
    return AcreKind_ModelFlags((unsigned int) acre->model);
}
CLEAN_AS(func_02037d9c, AcreRecord_Flags)

/* func_02037da8: looks through a layer, in order, for the first code from *first to *last; its
 * tile goes to (*x, *z). Whether one was found (never without the layer). */
int AcreRecord_FindCode(AcreRecord *acre, int *x, int *z, const u16 *first, const u16 *last, u8 layer)
{
    const u16 *codes = AcreRecord_Tile(acre, 0, 0, layer);
    if (codes == NULL) {
        return 0;
    }
    for (int index = 0; index < ACRE_RECORD_TILES; index++) {
        if (codes[index] >= *first && codes[index] <= *last) {
            AcreRecord_TileOfIndex(x, z, index);
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02037da8, AcreRecord_FindCode)

/* func_02037e0c: the code of tile (x, z) of a layer, or NULL when the layer, x or z is out of
 * range or the acre has no such layer. */
u16 *AcreRecord_Tile(AcreRecord *acre, unsigned int x, unsigned int z, unsigned int layer)
{
    if (layer < ACRE_RECORD_LAYERS && x < ACRE_RECORD_SIDE && z < ACRE_RECORD_SIDE) {
        u16 *codes = acre->layers[layer];
        if (codes != NULL) {
            return &codes[x + z * ACRE_RECORD_SIDE];
        }
    }
    return NULL;
}
CLEAN_AS(func_02037e0c, AcreRecord_Tile)

/* func_02037e44: the code of tile (x, z) of a layer set to *code; whether the tile exists. */
int AcreRecord_SetTile(AcreRecord *acre, const u16 *code, int x, int z, unsigned char layer)
{
    u16 *tile = AcreRecord_Tile(acre, (unsigned int) x, (unsigned int) z, layer);
    if (tile != NULL) {
        *tile = *code;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02037e44, AcreRecord_SetTile)

/* func_02037e70: whether the acre's model is one of the six func_0209d048 knows. */
int AcreRecord_ModelIsListed(AcreRecord *acre)
{
    return func_0209d048(AcreRecord_Model(acre));
}
CLEAN_AS(func_02037e70, AcreRecord_ModelIsListed)

/* func_02037e84 */
int AcreRecord_Model(const AcreRecord *acre)
{
    return acre->model;
}
CLEAN_AS(func_02037e84, AcreRecord_Model)

/* func_02037e88 */
void AcreRecord_SetModel(AcreRecord *acre, int model)
{
    acre->model = model;
}
CLEAN_AS(func_02037e88, AcreRecord_SetModel)

/* func_02037e8c: the address of the acre's coordinates (x, then z). */
int AcreRecord_Coordinates(AcreRecord *acre)
{
    return (int) ((uintptr_t) acre + offsetof(AcreRecord, x));
}
CLEAN_AS(func_02037e8c, AcreRecord_Coordinates)

/* func_02037e90: `count` acres from `heap`, aligned to `align`, each cleared by
 * AcreRecord_Init; NULL when the heap has no room. */
AcreRecord *AcreRecord_NewArray(int count, Heap *heap, int align)
{
    AcreRecord *acres = Heap_AllocAligned(heap, count * (int) sizeof(AcreRecord), align);
    if (acres != NULL) {
        for (int i = 0; i < count; i++) {
            AcreRecord_Init(&acres[i]);
        }
    }
    return acres;
}
CLEAN_AS(func_02037e90, AcreRecord_NewArray)

/* func_02037ecc: the acre's background model set; the acre data registered with the map of
 * `slot` is the model's own when there is a model, else `data`, and nothing is registered when
 * that is 0. */
void AcreRecord_SetBgModel(AcreRecord *acre, BgModel *bg_model, int data, int slot)
{
    acre->bg_model = bg_model;
    if (bg_model != NULL) {
        data = (int) (uintptr_t) bg_model->data;
    }
    if (data != 0) {
        func_02030c84(acre->x, acre->z, data, slot);
    }
}
CLEAN_AS(func_02037ecc, AcreRecord_SetBgModel)

/* func_02037eec: AcreRecord_SetUp with the coordinates given as a pair (x, z). */
void AcreRecord_SetUpAt(AcreRecord *acre, int model, const Vec3 *position, u16 *items, u16 *layer1, AcreBits *bits,
                        BgModel *bg_model, int data, const int *coordinates, int slot)
{
    Vec3 copy = *position;
    AcreRecord_SetUp(acre, model, &copy, items, layer1, bits, bg_model, data, coordinates[0], coordinates[1], slot);
}
CLEAN_AS(func_02037eec, AcreRecord_SetUpAt)

/* func_02037f28: the acre's model, position, layers, bits and coordinates set, then its
 * background model and data (AcreRecord_SetBgModel). */
void AcreRecord_SetUp(AcreRecord *acre, int model, const Vec3 *position, u16 *items, u16 *layer1, AcreBits *bits,
                      BgModel *bg_model, int data, int x, int z, int slot)
{
    acre->model = model;
    acre->position = *position;
    acre->layers[0] = items;
    acre->layers[1] = layer1;
    acre->bits = bits;
    acre->x = x;
    acre->z = z;
    AcreRecord_SetBgModel(acre, bg_model, data, slot);
}
CLEAN_AS(func_02037f28, AcreRecord_SetUp)

/* func_02037f5c: the coordinates and both layers cleared; the rest is left as it was. */
void AcreRecord_Init(AcreRecord *acre)
{
    acre->x = 0;
    acre->z = 0;
    for (int i = 0; i < ACRE_RECORD_LAYERS; i++) {
        acre->layers[i] = NULL;
    }
}
CLEAN_AS(func_02037f5c, AcreRecord_Init)
