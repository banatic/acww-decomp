/* func_02031a08 @ 0x02031a08, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
    unsigned char *data;
} TileMap;

extern TileMap *func_01ffcb5c(int, int);

int func_02031a08(int x, int y)
{
    TileMap *map;
    int index;
    unsigned char byte;

    map = func_01ffcb5c(x >> 4, y >> 4);
    if (map) {
        x &= 0xF;
        y &= 0xF;
        index = x + (y << 4);
        byte = map->data[index >> 1];

        if (index & 1) {
            return (byte >> 4) & 0xF;
        } else {
            return byte & 0xF;
        }
    }
    return 0;
}
