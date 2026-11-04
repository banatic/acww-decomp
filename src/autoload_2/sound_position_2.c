/* sound_position_2: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f5a58 @ 0x020f5a58, 0xac bytes, ARM
 * func_020f5a4c @ 0x020f5a4c, 0xc bytes, ARM
 * func_020f5a3c @ 0x020f5a3c, 0x10 bytes, ARM
 */

struct UnkStruct_020f5a58 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
};

extern int data_021fd248;
extern char data_021fd238;

int func_020f5a58(struct UnkStruct_020f5a58 *p, int t)
{
    int r;

    if (t >= (p->unk_10 >> 12)) {
        r = 0;
    } else if (t <= (p->unk_0C >> 12)) {
        r = p->unk_04 >> 12;
    } else {
        if (t <= (p->unk_00 >> 12)) {
            int shift = t << 12;
            int field = p->unk_14;
            int diff = shift - p->unk_0C;
            r = (p->unk_04 + (int) (((long long) diff * field + 0x800) >> 12)) >> 12;
        } else {
            int shift = t << 12;
            int field = p->unk_18;
            int diff = shift - p->unk_00;
            r = (p->unk_08 + (int) (((long long) diff * field + 0x800) >> 12)) >> 12;
        }
    }

    if (r > 0x7f) {
        return 0x7f;
    }
    if (r < 0) {
        return 0;
    }
    return r;
}

int *func_020f5a4c(void)
{
    return &data_021fd248;
}

void func_020f5a3c(char x)
{
    data_021fd238 = x;
}
