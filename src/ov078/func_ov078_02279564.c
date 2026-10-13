/* func_ov078_02279564 @ 0x02279564, 0x58 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02279564 {
    int x;
    int pad_04;
    int y;
};

int func_ov078_02279564(int unused, struct UnkStruct_02279564 *a, struct UnkStruct_02279564 *b)
{
    int result = 0;
    int flag2 = 0;
    int flag1 = 0;

    if (b->x > a->x - 0x10000 && b->x < a->x + 0x10000) {
        flag1 = 1;
    }
    if (flag1 != 0) {
        if (b->y > a->y - 0x1a000) {
            flag2 = 1;
        }
    }
    if (flag2 != 0) {
        if (b->y < a->y + 0xa000) {
            result = 1;
        }
    }
    return result;
}
