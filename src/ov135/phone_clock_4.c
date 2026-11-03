/* phone_clock_4: 11 functions, module ov135
 * mwccarm 1.2/base -O4,s
 * func_ov135_0229d24c @ 0x0229d24c, 0x1c bytes, Thumb
 * func_ov135_0229d248 @ 0x0229d248, 0x4 bytes, Thumb
 * func_ov135_0229d244 @ 0x0229d244, 0x4 bytes, Thumb
 * func_ov135_0229d234 @ 0x0229d234, 0x10 bytes, Thumb
 * func_ov135_0229d1d8 @ 0x0229d1d8, 0x5a bytes, Thumb
 * func_ov135_0229d1b0 @ 0x0229d1b0, 0x28 bytes, Thumb
 * func_ov135_0229d178 @ 0x0229d178, 0x38 bytes, Thumb
 * func_ov135_0229d148 @ 0x0229d148, 0x30 bytes, Thumb
 * func_ov135_0229d128 @ 0x0229d128, 0x20 bytes, Thumb
 * func_ov135_0229d0e8 @ 0x0229d0e8, 0x40 bytes, Thumb
 * func_ov135_0229d0c8 @ 0x0229d0c8, 0x20 bytes, Thumb
 */

extern void func_ov135_0229d0b0(int);
extern void func_ov135_0229d268(int);
extern void func_ov135_0229d0a8(int);
extern void func_020ee470(void *argument0);
extern void func_ov135_0229d030(void);
extern void func_ov135_0229d010(void *);
extern void func_ov135_0229cff0(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov135_0229c564(void *, int);
extern int func_ov002_0220ab38(char *, int);
extern void func_ov002_02208090(void *, int);
extern int func_ov002_02207f48(int a, int b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov135_0229ca1c(int a);
extern int func_020ee45c(int);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(int, int, int, int, int);
extern int func_ov002_02207f3c(int, int);
extern void func_020027f0(int);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov134_0229bd38(void *param, int a, int b, int c, int d);
extern int func_0206fca4(void);
extern void func_ov134_0229bd2c(void *param);
extern void func_ov134_0229bcf0(void *);
extern void func_ov002_0220af74(void *);

void func_ov135_0229d128(void *p);

int func_ov135_0229d24c(int arg)
{
    func_ov135_0229d0b0(arg);
    func_ov135_0229d268(arg);
    func_ov135_0229d0a8(arg);
    return 1;
}

int func_ov135_0229d248(void)
{
    return 1;
}

int func_ov135_0229d244(void)
{
    return 1;
}

int func_ov135_0229d234(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov135_0229d1d8(void *p)
{
    func_ov135_0229d030();
    func_ov135_0229d010(p);
    func_ov135_0229cff0(p);
    func_ov002_02207f20(p, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov135_0229d128(p);
    func_ov135_0229c564(p, 1);
    func_ov002_0220ab38((char *) p + 0xfc, 0x65);
    func_ov002_02208090(p, 1);
}

void func_ov135_0229d1b0(int a)
{
    if (func_ov002_02207f48(a, 0)) {
        func_ov002_022080a0((void *) (a), 2);
        func_ov135_0229ca1c(a);
    }
    func_ov135_0229d128((void *) a);
}

void func_ov135_0229d178(int param)
{
    int zero = 0;
    func_ov092_02299324(func_020ee45c(param), 0x44, 1);
    func_ov002_02207f04(param, 0xa, zero, zero, 0x30);
    func_ov135_0229d128((void *) param);
    func_ov002_02208090((void *) param, 3);
}

void func_ov135_0229d148(int param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) (param), 5);
    } else {
        func_ov135_0229d128((void *) param);
    }
}

void func_ov135_0229d128(void *p)
{
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov002_02207e80(p, 4, 0, 0);
}

void func_ov135_0229d0e8(unsigned char *p)
{
    func_ov134_0229bd38(p + 0x2c8, 0, 6, 4, 3);
    if (func_0206fca4() == 0x33) {
        func_ov134_0229bd2c(p + 0x2c8);
    }
    *(p + 0x95) = 0;
    *(unsigned short *) (p + 0x92) = 0;
}

void func_ov135_0229d0c8(void *self)
{
    func_ov134_0229bcf0((char *) self + 0x2c8);
    func_ov002_0220af74((char *) self + 0xfc);
}
