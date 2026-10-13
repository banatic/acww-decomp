/* func_020bd054 @ 0x020bd054, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xe80];
    unsigned int unk_E80;
    unsigned char pad_E84[0x2094];
    unsigned char unk_2F18;
    unsigned char unk_2F19;
    unsigned char pad_2F1A[0x37];
    unsigned char unk_2F51;
} UnkStruct_020bd054;

extern unsigned char data_021f3b28[4];
extern unsigned char data_020d22b5[];

extern void func_020bc548(UnkStruct_020bd054 *self);
extern int func_020bdc50(UnkStruct_020bd054 *self, int a, int b, int c, int d);
extern void func_020bdc14(UnkStruct_020bd054 *self, int a);

void func_020bd054(UnkStruct_020bd054 *self)
{
    unsigned char v;
    unsigned char t, t2, t3;
    int r1;
    int f4;

    self->unk_2F51 = 0;
    v = data_021f3b28[2];
    if (v >= 0x13 && v <= 0x17) {
        t = data_020d22b5[v];
        t2 = self->unk_2F19;
        if (t == t2) {
            t3 = self->unk_2F18;
            if ((int) t3 < 0x2d) {
                if ((int) t3 <= 0xf) {
                    r1 = t3 * 0xccc;
                } else {
                    r1 = (t3 - 0xf) * (int) 0xfffff99a;
                    r1 = r1 + 0xc000;
                }
                if (r1 < 0) {
                    r1 = 0;
                } else if (r1 > 0xc000) {
                    r1 = 0xc000;
                }
                r1 = (r1 + 0x800) >> 12;
                self->unk_2F51 = (unsigned char) r1;
            }
        }
    }

    f4 = (self->unk_E80 == 10) ? 1 : 0;
    if (self->unk_2F51 != 0) {
        func_020bc548(self);
        if (f4 == 0) {
            if (func_020bdc50(self, 10, 0x20, 0, 0) == 0) {
                self->unk_2F51 = 0;
            }
        }
    } else {
        if (f4 != 0) {
            func_020bdc14(self, 10);
        }
    }
}
