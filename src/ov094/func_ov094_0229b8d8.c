/* func_ov094_0229b8d8 @ 0x0229b8d8, 0x60 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229b8d8 {
    int pad_00;
    unsigned char *unk_04;
} UnkStruct_0229b8d8;

extern int func_020984e8(void *a, int b);
extern int func_02099734(int x);
extern unsigned char *func_02098e44(int x, int b);

unsigned char *func_ov094_0229b8d8(void *a, int b)
{
    int t;
    t = func_02099734(func_020984e8(a, b));
    if (b >= 0 && b <= 9) {
        return func_02098e44(t, b);
    } else if (b >= 0xa && b <= 0x22) {
        return ((UnkStruct_0229b8d8 *) a)->unk_04 + ((b - 0xa) << 8);
    } else if (b >= 0x23 && b <= 0x2c) {
        return ((UnkStruct_0229b8d8 *) a)->unk_04 + ((b - 0x23) << 8);
    } else if (b >= 0x2d && b <= 0x36) {
        return ((UnkStruct_0229b8d8 *) a)->unk_04 + ((b - 0x2d) << 8);
    } else {
        return 0;
    }
}
