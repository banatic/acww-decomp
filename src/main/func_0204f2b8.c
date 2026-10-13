/* func_0204f2b8 @ 0x0204f2b8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct CollisionMap {
    unsigned char *data;
    unsigned int width;
    unsigned int height;
} CollisionMap;

int func_0204f2b8(CollisionMap *map, unsigned int qx, unsigned int qy, unsigned int rx, unsigned int ry)
{
    unsigned char *tile;
    unsigned short *table;
    int result;
    unsigned short bits;
    int mask;

    if (qx < map->width && qy < map->height && map->data != 0) {
        tile = map->data + (qx + qy * map->width) * 0x28;
    } else {
        tile = 0;
    }

    result = 0;
    if (tile == 0) {
        return result;
    }
    table = (unsigned short *) *(unsigned int *) (tile + 0x24);
    if (table == 0) {
        return result;
    }

    if (rx < 0x10 && ry < 0x10) {
        result = 1;
    }
    if (result != 0) {
        if (rx < 0x10) {
            bits = table[ry];
            mask = 1 << rx;
            if ((bits & mask) != 0) {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}
