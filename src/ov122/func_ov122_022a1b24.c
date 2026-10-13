/* func_ov122_022a1b24 @ 0x022a1b24, 0x2c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov122_0229efc8(void *p, int n);

typedef struct {
    char pad_00[0x8c];
    char unk_8C;
    char pad_8D[11];
    int unk_98;
} S_022a1b24;

void func_ov122_022a1b24(S_022a1b24 *param)
{
    if (param->unk_98 < 0xA0) {
        param->unk_98 += 0x20;
    } else {
        func_ov122_0229efc8(param, 2);
        param->unk_8C = 0x0A;
    }
}
