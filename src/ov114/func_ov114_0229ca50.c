/* func_ov114_0229ca50 @ 0x0229ca50, 0x8c bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ca50;

extern int func_ov114_0229c1b8(struct UnkStruct_0229ca50 *a, int b);
extern void func_ov114_0229c6f8(struct UnkStruct_0229ca50 *a, unsigned char b);
extern void RtcSendPxiCommand(int cmd);
extern int _s32_div_f(int numerator, int denominator);

struct UnkStruct_0229ca50 {
    char pad_00[0x127c];
    int unk_127C;
    char pad_1280[0x14];
    int unk_1294;
    char pad_1298[0x21];
    unsigned char unk_12B9;
};

int func_ov114_0229ca50(struct UnkStruct_0229ca50 *a, int b, int c)
{
    int v;
    int limit;
    int x;
    int r4;

    if (c < 0x90 || c >= 0xb0) {
        return 0;
    }
    if (b < 0x10 || b >= 0xf0) {
        return 0;
    }
    if (b < 0x18) {
        b = 0x18;
    }
    if (b > 0xe8) {
        b = 0xe8;
    }

    v = a->unk_127C;
    x = b - (0x15 - v);
    if (x < 0) {
        x = 0;
    }

    r4 = _s32_div_f(x, 0x1b);

    limit = a->unk_1294;
    if (r4 >= limit) {
        r4 = limit - 1;
    }

    if (func_ov114_0229c1b8(a, r4) != 0) {
        if (a->unk_12B9 != r4) {
            RtcSendPxiCommand(0x29);
        }
        func_ov114_0229c6f8(a, (unsigned char) r4);
        return 1;
    }
    return 0;
}
