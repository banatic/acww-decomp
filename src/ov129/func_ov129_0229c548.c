/* func_ov129_0229c548 @ 0x0229c548, 0x2c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov129_0229b7ec(void *arg, int n);

struct func_ov129_0229c548_ctx {
    unsigned char pad_00[0xae];
    unsigned char unk_AE;
};

int func_ov129_0229c548(struct func_ov129_0229c548_ctx *arg)
{
    if (func_ov129_0229b7ec(arg, 2) != 0) {
        return 1;
    }
    if ((unsigned char) (arg->unk_AE + 0xfd) <= 1) {
        return 0;
    }
    return 1;
}
