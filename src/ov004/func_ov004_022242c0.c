/* func_ov004_022242c0 @ 0x022242c0, 0xdc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022242c0 {
    char unk_00[0x14];
    int unk_14;
} UnkStruct_022242c0;

typedef struct UnkStruct_022242c0_2 {
    char unk_00[0x1e];
    unsigned char unk_1E;
    char unk_1F[0x40 - 0x1f];
    UnkStruct_022242c0 *unk_40;
    char unk_44[0xb4 - 0x44];
    int unk_B4;
} UnkStruct_022242c0_2;

extern int data_ov004_02254594;

extern int func_020984e8(void);
extern int func_02099670(int a);
extern int func_020160b4(UnkStruct_022242c0_2 *self);
extern int func_020ab504(void *);
extern int func_02088bd4(int h);
extern void func_ov004_0222421c(UnkStruct_022242c0_2 *self, int k);
extern int func_0201b43c(int a, int b);
extern void func_0201b420(int a, int b);
extern int func_020644cc(int n);
extern void func_0206844c(UnkStruct_022242c0 *s, unsigned char *p, int v);

void func_ov004_022242c0(UnkStruct_022242c0_2 *self)
{
    int h;
    int fl;
    int v;
    unsigned char k;
    unsigned char b;

    h = func_02099670(func_020984e8());
    fl = func_020ab504((void *) func_020160b4(self));
    v = data_ov004_02254594;
    k = 0xff;
    if ((int) self->unk_1E >= 0x24 && (int) self->unk_1E <= 0x2b) {
        if (fl != 0) {
            k = (unsigned char) ((func_02088bd4(h) >> 2) + 0x28);
        } else {
            self->unk_40->unk_14 = 0;
            func_ov004_0222421c(self, 2);
        }
    }
    switch (self->unk_1E) {
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
            if (fl == 0) {
                if (func_0201b43c(self->unk_B4, 0xc8) == 0) {
                    k = 0x2f;
                } else {
                    func_0201b420(self->unk_B4, 0xc8);
                    k = (unsigned char) (func_020644cc(2) + ((func_02088bd4(h) >> 2) * 2 + 0x1c));
                }
            } else {
                k = (unsigned char) ((func_02088bd4(h) >> 2) + 0x18);
            }
            break;
    }
    if (k != 0xff) {
        b = k;
        func_0206844c(self->unk_40, &b, v);
    }
}
