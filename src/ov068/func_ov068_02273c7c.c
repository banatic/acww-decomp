/* func_ov068_02273c7c @ 0x02273c7c, 0x234 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    signed char unk_00;
    signed char unk_01;
    signed char unk_02;
    signed char unk_03;
    signed char unk_04;
    unsigned char pad_05[3];
    int unk_08;
} Other;
typedef struct {
    unsigned char pad_00[0xb4];
    void *unk_B4;
    unsigned char pad_B8[4];
    signed char unk_BC;
    signed char unk_BD;
    signed char unk_BE;
    signed char unk_BF;
    signed char unk_C0;
    unsigned char pad_C1[0xf];
    unsigned char unk_D0;
} UnkStruct_02273c7c;
extern Other *func_0200420c(void);
extern void func_ov004_02246a04(void);
extern void func_ov004_02246e88(void);
extern void func_ov004_0224692c(void);
extern void func_ov004_02246e98(void);
extern void func_0201a038(void *dst, void *src);
extern int func_0201acbc(void *ptr, int a, int b, int c, int d, int e);
extern void func_020542e0(void *ptr);
extern void func_02019c20(void *ptr, int a, int b, int c, int d, int e);
extern void func_02019c6c(void *ptr, int a, int b);
extern void func_0201a028(void *ptr);
extern int func_ov004_02246900(void);
extern void func_ov068_022740f8(void *self, int a);
extern void MI_CpuCopy8(void *dst, void *src, int size);
extern void func_ov004_02246954(int a);
extern void func_ov004_022469dc(void);
extern void *data_ov068_02277b94[];
extern void *data_ov068_022779a8;
extern volatile unsigned short data_020c80f8;
void func_ov068_02273c7c(UnkStruct_02273c7c *self)
{
    int val;
    Other *other = func_0200420c();
    func_ov004_02246a04();
    if (other != 0) {
        if (!((other->unk_03 == 1) && (self->unk_BF == 1))) {
            if (other->unk_04 == self->unk_C0) {
            } else if (other->unk_04 == 2) {
                func_ov004_02246e88();
                func_ov004_0224692c();
            } else if (((unsigned char) other->unk_04) <= 1) {
                func_ov004_02246e98();
            }
            if (other->unk_01 == self->unk_BD) {
            } else if (other->unk_01 == (-1)) {
                func_0201a038(((char *) self->unk_B4) + 0x2ac, &data_ov068_022779a8);
            } else {
                func_0201a038(((char *) self->unk_B4) + 0x2ac, data_ov068_02277b94[other->unk_01]);
            }
            if ((other->unk_02 == self->unk_BE) && (other->unk_00 == self->unk_BC)) {
            } else {
                if (other->unk_02 == 1) {
                    func_0201acbc(((char *) self->unk_B4) + 0x3b0, 0, 0, 0, 0x100, 0x200);
                } else {
                    func_0201acbc(((char *) self->unk_B4) + 0x3b0, 0, (int) 0xfffff3e8, 0, 0x100, 0x200);
                }
                val = data_020c80f8;
                if (self->unk_D0 == 0) {
                    val = 0x28;
                    self->unk_D0 = 1;
                }
                if (other->unk_00 == 3) {
                    func_02019c20(((char *) self->unk_B4) + 0x564, 2, 0x103, 0, val, 0);
                } else if (other->unk_00 == 4) {
                    func_02019c20(((char *) self->unk_B4) + 0x564, 2, 0x104, 0, val, 0);
                }
            }
            if (((unsigned char) ((signed char) (other->unk_00 - 3))) <= 1) {
                *((int *) (((char *) self->unk_B4) + 0x190)) = 0;
                *((int *) (((char *) self->unk_B4) + 0x198)) = other->unk_08;
                func_020542e0(((char *) self->unk_B4) + 0xec);
                *((int *) (((char *) self->unk_B4) + 0x198)) = 0;
            }
            if (other->unk_03 != self->unk_BF) {
                if (other->unk_03 == 0) {
                    func_ov004_02246a04();
                    func_ov004_02246954(0);
                    func_ov004_022469dc();
                }
                if (other->unk_03 == 1) {
                    func_0201a038(((char *) self->unk_B4) + 0x2ac, &data_ov068_022779a8);
                    func_0201a028(((char *) self->unk_B4) + 0x2ac);
                    func_02019c6c(((char *) self->unk_B4) + 0x564, 2, 0x28);
                }
            }
        }
    }
    func_ov004_022469dc();
    MI_CpuCopy8(other, &self->unk_BC, 0x14);
    if (func_ov004_02246900() != 0) {
        *((short *) (((char *) self->unk_B4) + 0x748)) = 0x14;
        func_ov068_022740f8(self, 4);
    }
}
