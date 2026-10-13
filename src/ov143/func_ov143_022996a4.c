/* func_ov143_022996a4 @ 0x022996a4, 0x46 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa0];
    unsigned char *ptr;
} UnkStruct_022996a4;

extern int func_ov143_022997d8(UnkStruct_022996a4 *a, unsigned char b);

void func_ov143_022996a4(UnkStruct_022996a4 *a, int *dst, int idx)
{
    int d;
    int x = 26;
    int y = 63;

    d = func_ov143_022997d8(a, a->ptr[idx]);
    if (idx < 8) {
        x += 24 * idx;
        y -= 2 * d;
    } else {
        x += 24 * (idx - 8) + 16;
        y += 56 - 2 * d;
    }
    dst[0] = x;
    dst[1] = y;
}
