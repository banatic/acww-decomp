/* func_01ffcbd8 @ 0x01ffcbd8, 0x38 bytes, Thumb, module itcm
 * mwccarm 1.2/base -O4,s
 */

struct Tile {
    char pad_00[0x24];
    unsigned short *cells;
};

struct Map {
    struct Tile *tiles;
    int width;
};

int func_01ffcbd8(struct Map *map, int x, int y)
{
    int tx = x >> 4;
    int ty = y >> 4;
    unsigned short *cells = map->tiles[ty * map->width + tx].cells;
    unsigned short v = cells[y - (ty << 4)];
    if ((v & (1 << (x - (tx << 4)))) != 0) {
        return 1;
    } else {
        return 0;
    }
}
