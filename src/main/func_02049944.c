/* func_02049944 @ 0x02049944, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int x, y;
} UnkStruct_02049944;

extern unsigned char data_020ca5d4[];

int func_02049944(void *obj, UnkStruct_02049944 *a, UnkStruct_02049944 *b,
                  int (*cb)(void *, UnkStruct_02049944 *, UnkStruct_02049944 *, UnkStruct_02049944 *))
{
    int i;
    int result = 0;
    unsigned char *tp = data_020ca5d4;

    for (i = 0; i < 8; tp++, i++) {
        unsigned char t = *tp;
        int x = b->x - ((t >> 4) - 8);
        int y = b->y - ((t & 0xf) - 8);

        if (x < 0) {
            continue;
        }
        if (x >= a->x) {
            continue;
        }
        if (y < 0) {
            continue;
        }
        if (y >= a->y) {
            continue;
        }
        if (x == b->x && y == b->y) {
            continue;
        }

        {
            UnkStruct_02049944 p, bb, aa;
            aa.x = a->x;
            aa.y = a->y;
            bb.x = b->x;
            bb.y = b->y;
            p.x = x;
            p.y = y;
            result = cb(obj, &p, &bb, &aa);
            if (result != 0) {
                break;
            }
        }
    }
    return result;
}
