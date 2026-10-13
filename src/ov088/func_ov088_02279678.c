/* func_ov088_02279678 @ 0x02279678, 0x58 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int pad_04;
    int y;
} UnkStruct_02279678;

int func_ov088_02279678(int arg0, UnkStruct_02279678 *a, UnkStruct_02279678 *b)
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
