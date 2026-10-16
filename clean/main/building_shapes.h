/* The shapes of the town's buildings (the item codes 0x5000-0x5021): file "a/<n>.bsize" of
 * the archive "/str/bsize.arc" for building n (the code's low bits), all loaded at once
 * (BuildingShapes_Load) and kept until BuildingShapes_Free.
 *
 * A shape is a list of four-byte entries, each starting with its kind, in this order:
 *
 * - 'R' and 'M' entries, the tiles around the building (acre_tile.c), the 'M' ones first: an
 *   x and z offset from the building's tile in bytes 2 and 3;
 * - 'F' and then 'S' entries, the tiles the building covers, the same way (an entry at offset
 *   (0, 0) stands for no tile); an 'S' entry also has a value in byte 1;
 * - a word of another kind that ends the list, then the number of triangles and the
 *   triangles, three corners (Vec3) each.
 *
 * Offsets and values are signed bytes; a tile is 0x2000 units of position wide. */
#ifndef CLEAN_MAIN_BUILDING_SHAPES_H
#define CLEAN_MAIN_BUILDING_SHAPES_H

#include "autoload_2/vector.h"
#include "types.h"

#define BUILDING_SHAPES_COUNT 0x22

/* An entry of a shape. */
typedef struct BuildingShapeEntry {
    char kind; /* 'R', 'M', 'F', 'S' */
    s8 value;  /* an 'S' entry's */
    s8 x;
    s8 z;
} BuildingShapeEntry;

/* A triangle after the entries. */
typedef struct BuildingShapeTriangle {
    Vec3 corners[3];
} BuildingShapeTriangle;

void *BuildingShapes_Of(u16 *code);
void BuildingShapes_Free(void);
void BuildingShapes_Load(void);
void BuildingShapes_Bounds(BuildingShapeEntry *shape, int *centre_x, int *centre_z, int *width, int *depth);
int BuildingShapes_Triangle(BuildingShapeEntry *shape, Vec3 *a, Vec3 *b, Vec3 *c, u32 index);
int BuildingShapes_TriangleCount(BuildingShapeEntry *shape);
int BuildingShapes_STile(BuildingShapeEntry *shape, int *value, int *x, int *z, unsigned int index);
int BuildingShapes_CoveredTile(BuildingShapeEntry *shape, int *x, int *z, unsigned int index);
int BuildingShapes_AroundTile(BuildingShapeEntry *shape, int *x, int *z, unsigned int index);
int BuildingShapes_MTile(unsigned int shape, unsigned int x, unsigned int z, unsigned int index);
int BuildingShapes_CoveredCount(BuildingShapeEntry *shape);
int BuildingShapes_SCount(BuildingShapeEntry *shape);
int BuildingShapes_FCount(BuildingShapeEntry *shape);
int BuildingShapes_AroundCount(BuildingShapeEntry *shape);
int BuildingShapes_MCount(BuildingShapeEntry *shape);

#endif
