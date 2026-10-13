/* func_ov003_022223bc @ 0x022223bc, 0x150 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    char pad_04[6];
    unsigned short unk_0A;
    char pad_0C[0x10 - 0xc];
    int unk_10, unk_14;
    char pad_18[0x3c - 0x18];
    int unk_3C;
    int unk_40;
    int unk_44;
    char pad_48[0xa0 - 0x48];
    unsigned char a0;
} UnkStruct_022223bc;

extern int func_ov003_02221118(int a, unsigned short b, int *pair);
extern void func_ov003_02222860(UnkStruct_022223bc *self);

void func_ov003_022223bc(UnkStruct_022223bc *self)
{
    unsigned int h, g, f, e, d, c, b, a;
    unsigned short lo, hi;
    int pair[2];

    self->unk_3C = self->unk_3C - 0x154;
    if (self->unk_3C < 0) {
        volatile unsigned short t = 0xfff1;
        a = 0;
        self->unk_3C = 0;
        t = self->unk_0A;
        h = 1;
        g = 1;
        f = 1;
        e = 1;
        d = 1;
        c = 1;
        b = 1;
        lo = t;
        hi = t;
        if (hi <= 5) {
            a = 1;
        }
        if (a == 0) {
            if (!(lo >= 6 && lo <= 0xb)) {
                b = 0;
            }
        }
        if (b == 0) {
            if (!(lo >= 0xc && lo <= 0x11)) {
                c = 0;
            }
        }
        if (c == 0) {
            if (!((lo >= 0x12 && lo <= 0x19) || lo == 0x1c)) {
                d = 0;
            }
        }
        if (d == 0) {
            if (!((lo >= 0x8a && lo <= 0x8f) || (lo >= 0x90 && lo <= 0x95) || (lo >= 0x96 && lo <= 0x9b) ||
                  (lo >= 0x9c && lo <= 0xa3) || lo == 0xa5)) {
                e = 0;
            }
        }
        if (e == 0) {
            if (lo != 0x1a) {
                f = 0;
            }
        }
        if (f == 0) {
            if (lo != 0xa4) {
                g = 0;
            }
        }
        if (g == 0) {
            if (lo != 0x1d) {
                h = 0;
            }
        }
        if (h != 0 || (lo >= 0x26 && lo <= 0x2a) || (lo >= 0x5d && lo <= 0x61) || (lo >= 0x2f && lo <= 0x56) ||
            (lo >= 0x57 && lo <= 0x5b) || (lo >= 0x66 && lo <= 0x68) || lo == 0x69 || (lo >= 0x6a && lo <= 0x6c) ||
            lo == 0x6d || (lo >= 0xc8 && lo <= 0xcf) || (lo >= 0xd4 && lo <= 0xda)) {
            pair[0] = self->unk_10;
            pair[1] = self->unk_14;
            if (func_ov003_02221118(self->unk_00, self->unk_0A, pair) != 0) {
                self->a0 = 0;
                func_ov003_02222860(self);
            }
        } else {
            func_ov003_02222860(self);
        }
    }
    self->unk_44 = self->unk_3C;
}
