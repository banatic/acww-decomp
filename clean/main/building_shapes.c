/* The shapes of the town's buildings (building_shapes.h). */
#include "building_shapes.h"

#include "acre_tile.h"
#include "autoload_2/heap.h"
#include "clean.h"
#include "c_library.h"
#include "rom_file.h"

static_assert(sizeof(BuildingShapeEntry) == 4, "entry");
static_assert(sizeof(BuildingShapeTriangle) == 0x24, "triangle");

/* The archive "/str/bsize.arc" while it is loaded, else NULL, and each building's shape in
 * it (NULL for none). */
extern void *data_021f4b44;
extern void *data_021f4bf4[BUILDING_SHAPES_COUNT];

extern Heap *data_021fbe94;        /* the heap the archive is loaded on */
extern const char data_020e5110[]; /* "/str/bsize.arc" */
extern const char data_020e5120[]; /* "STR", the archive's name once mounted */
extern const char data_020e5124[]; /* "STR:a/%d.bsize" */

/* A mounted archive (NitroSystem's NNSFndArchive). */
typedef struct BuildingShapesArchive {
    u8 bytes[0x6c];
} BuildingShapesArchive;

extern int NNS_FndMountArchive(BuildingShapesArchive *archive, const char *name, void *data);
extern void *NNS_FndGetArchiveFileByName(const char *path);
extern int func_0210285c(BuildingShapesArchive *archive); /* the archive unmounted */

#define BUILDING_SHAPES_NAME_SIZE 0x20
/* Half a tile, in units of position. */
#define BUILDING_SHAPES_HALF_TILE 0x1000
#define BUILDING_SHAPES_TILE 0x2000

static int building_shapes_is_building(u16 code)
{
    return code >= ACRE_TILE_BUILDING_FIRST && code <= ACRE_TILE_BUILDING_LAST;
}

/* Halving as the ARM's arithmetic shift does (rounding down). */
static int building_shapes_half(int value)
{
    return value >= 0 ? value >> 1 : ~(~value >> 1);
}

static int building_shapes_abs(int value)
{
    return value < 0 ? -value : value;
}

/* func_020b3b50: the shape of building `code` (*code), NULL when it is not a building or the
 * archive is not loaded. */
void *BuildingShapes_Of(u16 *code)
{
    if (data_021f4b44 == NULL || !building_shapes_is_building(*code)) {
        return NULL;
    }
    return data_021f4bf4[*code & 0xfff];
}
CLEAN_AS(func_020b3b50, BuildingShapes_Of)

/* func_020b3ba0: no shapes any more, and the archive freed when it was loaded. */
void BuildingShapes_Free(void)
{
    for (unsigned int i = 0; i < BUILDING_SHAPES_COUNT; i++) {
        data_021f4bf4[i] = NULL;
    }
    if (data_021f4b44 != NULL) {
        Heap_FreeCurrent(data_021f4b44);
        data_021f4b44 = NULL;
    }
}
CLEAN_AS(func_020b3ba0, BuildingShapes_Free)

/* func_020b3bd4: the archive loaded and each building's shape found in it. Without the
 * archive every shape is NULL.
 * QUIRK: when the archive loads but cannot be mounted, the shapes are left as they were. */
void BuildingShapes_Load(void)
{
    char name[BUILDING_SHAPES_NAME_SIZE];
    BuildingShapesArchive archive;

    data_021f4b44 = RomFile_Load(data_020e5110, data_021fbe94, 4, NULL);
    if (data_021f4b44 == NULL) {
        for (unsigned int i = 0; i < BUILDING_SHAPES_COUNT; i++) {
            data_021f4bf4[i] = NULL;
        }
        return;
    }
    if (NNS_FndMountArchive(&archive, data_020e5120, data_021f4b44) == 0) {
        return;
    }
    for (unsigned int i = 0; i < BUILDING_SHAPES_COUNT; i++) {
        CLib_SPrintf(name, data_020e5124, i);
        data_021f4bf4[i] = NNS_FndGetArchiveFileByName(name);
    }
    func_0210285c(&archive);
}
CLEAN_AS(func_020b3bd4, BuildingShapes_Load)

/* func_020b3c58: the rectangle around the shape's 'S' tiles, as its centre and its size in
 * units of position (each tile reaching half a tile either side of its centre). Without 'S'
 * tiles it is the building's own tile.
 * QUIRK: with 'S' tiles the smallest offset starts at 1 and the largest at -1 rather than at
 * the first tile's, so on each axis the smallest is never above 1 and the largest never below
 * -1, whatever the tiles. */
void BuildingShapes_Bounds(BuildingShapeEntry *shape, int *centre_x, int *centre_z, int *width, int *depth)
{
    int min_x = 0;
    int max_x = 0;
    int min_z = 0;
    int max_z = 0;

    unsigned int count = (unsigned int) BuildingShapes_SCount(shape);
    if (count != 0) {
        min_x = 1;
        max_x = -1;
        min_z = 1;
        max_z = -1;
        for (unsigned int i = 0; i < count; i++) {
            int value;
            int x;
            int z;
            if (BuildingShapes_STile(shape, &value, &x, &z, i) == 0) {
                continue;
            }
            if (x < min_x) {
                min_x = x;
            }
            if (z < min_z) {
                min_z = z;
            }
            if (x > max_x) {
                max_x = x;
            }
            if (z > max_z) {
                max_z = z;
            }
        }
    }

    int right = max_x * BUILDING_SHAPES_TILE + BUILDING_SHAPES_HALF_TILE;
    int left = min_x * BUILDING_SHAPES_TILE - BUILDING_SHAPES_HALF_TILE;
    int far = max_z * BUILDING_SHAPES_TILE + BUILDING_SHAPES_HALF_TILE;
    int near = min_z * BUILDING_SHAPES_TILE - BUILDING_SHAPES_HALF_TILE;
    *centre_x = building_shapes_half(right + left);
    *centre_z = building_shapes_half(far + near);
    *width = building_shapes_abs(right - left);
    *depth = building_shapes_abs(far - near);
}
CLEAN_AS(func_020b3c58, BuildingShapes_Bounds)

/* func_020b3d04: the corners of triangle `index`; whether there is one. Without it the
 * corners are all 0. */
int BuildingShapes_Triangle(BuildingShapeEntry *shape, Vec3 *a, Vec3 *b, Vec3 *c, u32 index)
{
    u32 count = (u32) BuildingShapes_TriangleCount(shape);

    *a = (Vec3){0, 0, 0};
    *b = (Vec3){0, 0, 0};
    *c = (Vec3){0, 0, 0};
    if (index >= count) {
        return 0;
    }
    /* The triangles follow the entries, the word that ends them and the count. */
    int f = BuildingShapes_FCount(shape);
    int around = BuildingShapes_AroundCount(shape);
    int s = BuildingShapes_SCount(shape);
    const BuildingShapeTriangle *triangles = (const BuildingShapeTriangle *) (shape + (f + around + s + 2));
    const BuildingShapeTriangle *triangle = &triangles[index];
    *a = triangle->corners[0];
    *b = triangle->corners[1];
    *c = triangle->corners[2];
    return 1;
}
CLEAN_AS(func_020b3d04, BuildingShapes_Triangle)

/* func_020b3d90: the number of triangles, the word after the one that ends the entries. */
int BuildingShapes_TriangleCount(BuildingShapeEntry *shape)
{
    int f = BuildingShapes_FCount(shape);
    int around = BuildingShapes_AroundCount(shape);
    int s = BuildingShapes_SCount(shape);
    return *(const s32 *) &shape[f + around + s + 1];
}
CLEAN_AS(func_020b3d90, BuildingShapes_TriangleCount)

/* func_020b3db8: the value and offsets of 'S' tile `index`; whether there is one. */
int BuildingShapes_STile(BuildingShapeEntry *shape, int *value, int *x, int *z, unsigned int index)
{
    BuildingShapeEntry *covered = shape + BuildingShapes_AroundCount(shape);

    if (index >= (unsigned int) BuildingShapes_SCount(shape)) {
        return 0;
    }
    const BuildingShapeEntry *entry = &covered[(unsigned int) BuildingShapes_FCount(shape) + index];
    *value = entry->value;
    *x = entry->x;
    *z = entry->z;
    return 1;
}
CLEAN_AS(func_020b3db8, BuildingShapes_STile)

/* func_020b3e08: the offsets of covered tile `index` ('F' and 'S' entries); whether it is a
 * tile, which one at offset (0, 0) is not. Past the covered tiles nothing is written. */
int BuildingShapes_CoveredTile(BuildingShapeEntry *shape, int *x, int *z, unsigned int index)
{
    BuildingShapeEntry *covered = shape + BuildingShapes_AroundCount(shape);
    unsigned int count = (unsigned int) BuildingShapes_CoveredCount(shape);

    if (index >= count) {
        return 0;
    }
    *x = covered[index].x;
    *z = covered[index].z;
    return *x != 0 || *z != 0;
}
CLEAN_AS(func_020b3e08, BuildingShapes_CoveredTile)

/* func_020b3e58: the offsets of tile `index` around the building ('R' and 'M' entries);
 * whether there is one. */
int BuildingShapes_AroundTile(BuildingShapeEntry *shape, int *x, int *z, unsigned int index)
{
    if (index >= (unsigned int) BuildingShapes_AroundCount(shape)) {
        return 0;
    }
    *x = shape[index].x;
    *z = shape[index].z;
    return 1;
}
CLEAN_AS(func_020b3e58, BuildingShapes_AroundTile)

/* func_020b3e8c: as BuildingShapes_AroundTile for the 'M' tiles only (the first ones). */
int BuildingShapes_MTile(unsigned int shape, unsigned int x, unsigned int z, unsigned int index)
{
    BuildingShapeEntry *entries = (BuildingShapeEntry *) (uintptr_t) shape;

    if (index >= (unsigned int) BuildingShapes_MCount(entries)) {
        return 0;
    }
    return BuildingShapes_AroundTile(entries, (int *) (uintptr_t) x, (int *) (uintptr_t) z, index);
}
CLEAN_AS(func_020b3e8c, BuildingShapes_MTile)

/* func_020b3eb8: the number of tiles the building covers ('F' and 'S' entries). */
int BuildingShapes_CoveredCount(BuildingShapeEntry *shape)
{
    int f = BuildingShapes_FCount(shape);
    return f + BuildingShapes_SCount(shape);
}
CLEAN_AS(func_020b3eb8, BuildingShapes_CoveredCount)

/* func_020b3ed4: the number of 'S' entries, the ones after the 'F' entries. */
int BuildingShapes_SCount(BuildingShapeEntry *shape)
{
    int around = BuildingShapes_AroundCount(shape);
    int f = BuildingShapes_FCount(shape);
    const BuildingShapeEntry *entry = shape + around + f;
    int count = 0;

    while (entry[count].kind == 'S') {
        count++;
    }
    return count;
}
CLEAN_AS(func_020b3ed4, BuildingShapes_SCount)

/* func_020b3f08: the number of 'F' entries, the ones after the 'R' and 'M' entries. */
int BuildingShapes_FCount(BuildingShapeEntry *shape)
{
    const BuildingShapeEntry *entry = shape + BuildingShapes_AroundCount(shape);
    int count = 0;

    while (entry[count].kind == 'F') {
        count++;
    }
    return count;
}
CLEAN_AS(func_020b3f08, BuildingShapes_FCount)

/* func_020b3f2c: the number of 'R' and 'M' entries at the start. */
int BuildingShapes_AroundCount(BuildingShapeEntry *shape)
{
    int count = 0;

    while (shape[count].kind == 'R' || shape[count].kind == 'M') {
        count++;
    }
    return count;
}
CLEAN_AS(func_020b3f2c, BuildingShapes_AroundCount)

/* func_020b3f44: the number of 'M' entries at the start. */
int BuildingShapes_MCount(BuildingShapeEntry *shape)
{
    int count = 0;

    while (shape[count].kind == 'M') {
        count++;
    }
    return count;
}
CLEAN_AS(func_020b3f44, BuildingShapes_MCount)
