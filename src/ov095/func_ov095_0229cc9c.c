/* func_ov095_0229cc9c @ 0x0229cc9c, 0x42 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229cc9c {
    char pad_00[0x1b];
    unsigned char unk_1B;
} UnkStruct_0229cc9c;

extern void func_ov095_022999a0(UnkStruct_0229cc9c *param, int n);
extern int func_ov095_022999b0(UnkStruct_0229cc9c *param, int n);
extern void func_ov095_0229cb5c(UnkStruct_0229cc9c *param, int a, int b);

void func_ov095_0229cc9c(UnkStruct_0229cc9c *param)
{
    if (param->unk_1B != 3) {
        func_ov095_022999a0(param, 0x20);
    }
    if (param->unk_1B == 2) {
    } else if (param->unk_1B == 3) {
        if (func_ov095_022999b0(param, 0x20)) {
            func_ov095_0229cb5c(param, 0x5d, 0xd);
        } else {
            func_ov095_0229cb5c(param, 0x52, 0xd);
        }
    }
}
