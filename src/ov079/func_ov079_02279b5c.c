/* func_ov079_02279b5c @ 0x02279b5c, 0x58 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

int func_ov079_02279b5c(int unused, int *p1, int *p2)
{
    int result = 0;
    int flag2 = 0;
    int flag1 = 0;

    if (*p2 > *p1 - 0x10000 && *p2 < *p1 + 0x10000) {
        flag1 = 1;
    }

    if (flag1) {
        if (p2[2] > p1[2] - 0x1a000) {
            flag2 = 1;
        }
    }

    if (flag2) {
        if (p2[2] < p1[2] + 0xa000) {
            result = 1;
        }
    }

    return result;
}
