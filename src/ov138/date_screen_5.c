/* date_screen_5: 10 functions, module ov138
 * mwccarm 1.2/base -O4,s
 * func_ov138_0229d14c @ 0x0229d14c, 0x4 bytes, Thumb
 * func_ov138_0229d148 @ 0x0229d148, 0x4 bytes, Thumb
 * func_ov138_0229d138 @ 0x0229d138, 0x10 bytes, Thumb
 * func_ov138_0229d0dc @ 0x0229d0dc, 0x5a bytes, Thumb
 * func_ov138_0229d0b4 @ 0x0229d0b4, 0x28 bytes, Thumb
 * func_ov138_0229d07c @ 0x0229d07c, 0x38 bytes, Thumb
 * func_ov138_0229d04c @ 0x0229d04c, 0x30 bytes, Thumb
 * func_ov138_0229d02c @ 0x0229d02c, 0x20 bytes, Thumb
 * func_ov138_0229cff4 @ 0x0229cff4, 0x38 bytes, Thumb
 * func_ov138_0229cfd4 @ 0x0229cfd4, 0x20 bytes, Thumb
 */

extern void func_020ee470(void *argument0);
extern void func_ov138_0229cf3c(void);
extern void func_ov138_0229cf1c(void *self);
extern void func_ov138_0229cefc(void *self);
extern void func_02002708(int arg);
extern void func_ov138_0229c564(void *self, int arg);
extern void func_ov002_02207f20(void *self, int a, int b, int c, int d);
extern int func_ov002_0220ab38(void *self, int arg);
extern void func_ov002_02208090(void *self, int arg);
extern int func_ov002_02207f48(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov138_0229c9c0(void *p);
extern int func_020ee45c(void *p);
extern void func_ov092_02299324(int a, int b, int c);
extern void func_ov002_02207f04(void *p, int a, int b, int c, int d);
extern int func_ov002_02207f3c(void *a, int b);
extern void func_020027f0(int a);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov134_0229bd38(unsigned char *p, int, int, int, int);
extern void func_ov134_0229bd2c(unsigned char *p);
extern void func_ov134_0229bcf0(void *);
extern void func_ov002_0220af74(void *);

void func_ov138_0229d02c(void *p);

int func_ov138_0229d14c(void)
{
    return 1;
}

int func_ov138_0229d148(void)
{
    return 1;
}

int func_ov138_0229d138(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov138_0229d0dc(void *self)
{
    func_ov138_0229cf3c();
    func_ov138_0229cf1c(self);
    func_ov138_0229cefc(self);
    func_ov002_02207f20(self, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov138_0229d02c(self);
    func_ov138_0229c564(self, 1);
    func_ov002_0220ab38((char *) self + 0xfc, 0x65);
    func_ov002_02208090(self, 1);
}

void func_ov138_0229d0b4(void *param)
{
    if (func_ov002_02207f48(param, 0)) {
        func_ov002_022080a0((void *) (param), 2);
        func_ov138_0229c9c0(param);
    }
    func_ov138_0229d02c(param);
}

void func_ov138_0229d07c(void *p)
{
    func_ov092_02299324(func_020ee45c(p), 0x44, 1);
    func_ov002_02207f04(p, 0xa, 0, 0, 0x30);
    func_ov138_0229d02c(p);
    func_ov002_02208090(p, 3);
}

void func_ov138_0229d04c(void *arg)
{
    if (func_ov002_02207f3c(arg, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) (arg), 5);
    } else {
        func_ov138_0229d02c(arg);
    }
}

void func_ov138_0229d02c(void *p)
{
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov002_02207e80(p, 4, 0, 0);
}

void func_ov138_0229cff4(unsigned char *self)
{
    func_ov134_0229bd38(self + 0x2c8, 3, 6, 4, 3);
    func_ov134_0229bd2c(self + 0x2c8);
    self[0x95] = 0;
    *(unsigned short *) (self + 0x92) = 0;
}

void func_ov138_0229cfd4(void *arg0)
{
    func_ov134_0229bcf0((char *) arg0 + 0x2c8);
    func_ov002_0220af74((char *) arg0 + 0xfc);
}
