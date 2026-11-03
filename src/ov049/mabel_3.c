/* mabel_3: 6 functions, module ov049
 * mwccarm 1.2/base -O4,s
 * func_ov049_022621d8 @ 0x022621d8, 0xc bytes, Thumb
 * func_ov049_02262198 @ 0x02262198, 0x40 bytes, Thumb
 * func_ov049_02262190 @ 0x02262190, 0x8 bytes, Thumb
 * func_ov049_0226218c @ 0x0226218c, 0x4 bytes, Thumb
 * func_ov049_02262158 @ 0x02262158, 0x34 bytes, Thumb
 * func_ov049_02262100 @ 0x02262100, 0x58 bytes, Thumb
 */

extern void func_ov049_02262a94(int, int);
extern int data_020c814c;
extern void func_0201ad18(void *p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7);
extern unsigned char data_021fbee8[];
extern int func_ov049_022629e4(void *argument0);
extern unsigned short data_020c80f8;
extern int func_02019d0c(char *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern int func_02019c6c(void *p, int a, unsigned short b);
extern void *func_0201c2c8(void *p, int a);
extern void func_0201aff4(void *p, void *q);
extern int func_0203e0a8(void *p, int a);

void func_ov049_022621d8(int a)
{
    func_ov049_02262a94(a, 14);
}

void func_ov049_02262198(void *param)
{
    func_0201ad18((char *) param + 0x3b0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    func_ov049_02262a94((int) param, 1);
}

void func_ov049_02262190(void *argument0)
{
    func_ov049_022629e4(argument0);
}

int func_ov049_0226218c(void)
{
    return 1;
}

int func_ov049_02262158(char *ptr)
{
    func_02019d0c(ptr + 0x564, 3, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov049_02262100(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564) != 0) {
            func_02019c6c((char *) self + 0x564, 1, *(unsigned short *) ((char *) self + 0x972));
        }
    }
    func_0201aff4((char *) self + 0x350, func_0201c2c8(self, 4));
    func_0203e0a8(self, 0);
    return 1;
}
