/* func_ov074_022796a0 @ 0x022796a0, 0x58 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int pad_04;
    int y;
} UnkStruct_022796a0;

int func_ov074_022796a0(int arg0, UnkStruct_022796a0 *a, UnkStruct_022796a0 *b)
{
    int result = 0;
    int ok2 = 0;
    int ok1 = 0;

    if ((b->x > a->x - 0x10000) && (b->x < a->x + 0x10000)) {
        ok1 = 1;
    }
    if (ok1 && (b->y > a->y - 0x1a000)) {
        ok2 = 1;
    }
    if (ok2 && (b->y < a->y + 0xa000)) {
        result = 1;
    }

    return result;
}
