/* func_ov143_02299ed8 @ 0x02299ed8, 0x6e bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} TempStruct;

extern void func_ov143_022996a4(void *obj, TempStruct *out, int idx);

int func_ov143_02299ed8(void *obj, int b, int c)
{
    int i;
    TempStruct tmp;
    for (i = 0; i < 16; i++) {
        func_ov143_022996a4(obj, &tmp, i);
        if (tmp.x > b || tmp.x + 0x14 <= b || tmp.y > c || tmp.y + 0x12 <= c) {
            continue;
        }
        return (unsigned char) i;
    }
    if (b >= 0 && b < 0x38 && c >= 0x90 && c < 0xac) {
        return 0x10;
    }
    if (b >= 0x60 && b < 0xb0 && c >= 0x90 && c < 0xb8) {
        return 0x11;
    }
    return 0x16;
}
