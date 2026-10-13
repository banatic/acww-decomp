/* func_ov054_02262494 @ 0x02262494, 0x94 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int *func_02095794(int);
extern void func_0204f818(int *lo, int *hi, const void *in);

struct MainObj {
    char pad_00[0x80C];
    int unk_80C;
};

struct TableEntry {
    int a, b, c;
};

extern struct TableEntry data_ov054_022629c8[2];

int func_ov054_02262494(struct MainObj *self)
{
    int out1_lo, out1_hi;
    int out2_lo, out2_hi;
    int input[3];
    struct TableEntry tempEntry;
    int *data;
    int original;
    int i;

    data = func_02095794(4);
    input[0] = data[0];
    input[1] = data[1];
    input[2] = data[2];

    out1_lo = 0;
    out1_hi = 0;
    func_0204f818(&out1_lo, &out1_hi, input);

    original = self->unk_80C;

    i = 0;
    while (i < 2) {
        out2_lo = 0;
        out2_hi = 0;
        tempEntry.a = data_ov054_022629c8[i].a;
        tempEntry.b = data_ov054_022629c8[i].b;
        tempEntry.c = data_ov054_022629c8[i].c;
        func_0204f818(&out2_lo, &out2_hi, &tempEntry);
        if (out1_lo == out2_lo && out1_hi == out2_hi) {
            self->unk_80C = i;
            break;
        }
        i++;
    }

    if (original != self->unk_80C) {
        return 1;
    } else {
        return 0;
    }
}
