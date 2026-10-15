/* func_ov075_02278bd0 @ 0x02278bd0, 0x174 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02278bd0 {
    char pad_00[0x2a0];
    char unk_2A0[0x334 - 0x2a0];
    char unk_334[0x564 - 0x334];
    char unk_564[0x718 - 0x564];
    unsigned char unk_718;
} UnkStruct_02278bd0;

typedef struct Owner {
    int unk_00;
    int unk_04;
} Owner;

typedef struct UnkStruct_02278bd0_2 {
    char pad_00[0x40];
    Owner *unk_40;
    char pad_44[0xb4 - 0x44];
    unsigned char unk_B4;
    char pad_B5[0xb8 - 0xb5];
    UnkStruct_02278bd0 *unk_B8;
} UnkStruct_02278bd0_2;

extern unsigned short data_020c80f8;
extern int data_ov075_02279aa8;

extern int func_02019c20(void *p, int a, int b, int c, int d, int e);
extern void func_0201b38c(void *p, int a);
extern int func_020164a0(void *p, int a);
extern int func_02019de8(void *p);
extern int func_0201c2c8(UnkStruct_02278bd0 *c, int a);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_02019e00(void *p);
extern void *func_020984e8(void);
extern int func_020155cc(UnkStruct_02278bd0_2 *self);
extern int func_02099020(void *p, int a);
extern void func_02098ff8(void *p, int a);
extern int func_0202ea80(int a, int b);
extern void func_0206844c(Owner *a, unsigned char *p, int *t);
extern int func_020644cc(int a);
extern void func_ov075_02278d44(UnkStruct_02278bd0_2 *self, int a);

void func_ov075_02278bd0(UnkStruct_02278bd0_2 *self)
{
    unsigned char buf[2];
    void *h;
    int r;

    switch (self->unk_B4) {
        case 0:
            if (self->unk_40->unk_04 == 5) {
                func_02019c20(self->unk_B8->unk_564, 2, 0xd5, 1, data_020c80f8, 0);
                func_0201b38c(self->unk_B8->unk_2A0, 0);
                self->unk_B4 = self->unk_B4 + 1;
            }
            break;
        case 1:
            if (func_020164a0(self->unk_B8->unk_334, 0) == 0xd5) {
                if (func_02019de8(self->unk_B8->unk_564) != 0) {
                    r = func_0201c2c8(self->unk_B8, 4);
                    func_02019d0c(self->unk_B8->unk_564, 3, 2, 0, 0, 0, r, 0, 0, data_020c80f8, 0);
                    self->unk_B4 = self->unk_B4 + 1;
                }
            }
            break;
        case 2:
            if (func_02019e00(self->unk_B8->unk_564) == 3) {
                if (func_02019de8(self->unk_B8->unk_564) != 0) {
                    h = func_020984e8();
                    self->unk_B8->unk_718 = 1;
                    func_020155cc(self);
                    if (func_02099020(h, 6) == 0) {
                        func_02098ff8(h, 6);
                        func_0202ea80(0x12, 1);
                        buf[0] = 0x10;
                        func_0206844c(self->unk_40, &buf[0], &data_ov075_02279aa8);
                    } else {
                        func_0202ea80(0x12, 1);
                        buf[1] = (unsigned char) func_020644cc(0xc);
                        func_0206844c(self->unk_40, &buf[1], &data_ov075_02279aa8);
                    }
                    func_ov075_02278d44(self, 0);
                }
            }
            break;
    }
}
