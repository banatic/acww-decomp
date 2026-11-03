/* bank_menu_5: 10 functions, module ov132
 * mwccarm 1.2/base -O4,s
 * func_ov132_0229b6a0 @ 0x0229b6a0, 0x4 bytes, Thumb
 * func_ov132_0229b69c @ 0x0229b69c, 0x4 bytes, Thumb
 * func_ov132_0229b68c @ 0x0229b68c, 0x10 bytes, Thumb
 * func_ov132_0229b630 @ 0x0229b630, 0x5a bytes, Thumb
 * func_ov132_0229b608 @ 0x0229b608, 0x28 bytes, Thumb
 * func_ov132_0229b5c8 @ 0x0229b5c8, 0x40 bytes, Thumb
 * func_ov132_0229b598 @ 0x0229b598, 0x30 bytes, Thumb
 * func_ov132_0229b578 @ 0x0229b578, 0x20 bytes, Thumb
 * func_ov132_0229b564 @ 0x0229b564, 0x14 bytes, Thumb
 * func_ov132_0229b534 @ 0x0229b534, 0x30 bytes, Thumb
 */

extern void func_020ee470(void *parameter0);
extern void func_ov132_0229b4c0(void);
extern void func_ov132_0229b3d8(void *self);
extern void func_ov132_0229b3cc(void *receiver);
extern void func_ov002_02207f20(void *self, int a, int b, int c, int d);
extern void func_02002708(int a);
extern void func_ov132_0229ad60(void *self, int a);
extern int func_ov002_0220ab84(void *self, int a);
extern void func_ov002_02208090(void *self, int a);
extern int func_ov002_02207f48(void *arg, int val);
extern unsigned char *func_ov002_022080a0(void *arg, unsigned char value);
extern void func_ov132_0229b104(void *arg);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, unsigned char, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern int func_ov002_02207f3c(int a, int b);
extern void func_020027f0(int a);
extern void func_ov002_02207e80(int, int, int, int);
extern void func_020b9ccc(void *);
extern void func_ov002_0220af74(void *);
extern void func_ov132_0229adb8(void *);

void func_ov132_0229b578(int a);

int func_ov132_0229b6a0(void)
{
    return 1;
}

int func_ov132_0229b69c(void)
{
    return 1;
}

int func_ov132_0229b68c(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov132_0229b630(void *self)
{
    func_ov132_0229b4c0();
    func_ov132_0229b3d8(self);
    func_ov132_0229b3cc(self);
    func_ov002_02207f20(self, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov132_0229b578((int) self);
    func_ov132_0229ad60(self, 1);
    func_ov002_0220ab84((char *) self + 0xf8, 0x65);
    func_ov002_02208090(self, 1);
}

void func_ov132_0229b608(void *arg)
{
    if (func_ov002_02207f48(arg, 0)) {
        func_ov002_022080a0(arg, 2);
        func_ov132_0229b104(arg);
    }
    func_ov132_0229b578((int) arg);
}

void func_ov132_0229b5c8(void *obj)
{
    int ret = func_020ee45c(obj);
    func_ov092_02299324(ret, ((unsigned char *) obj)[0x1505], 1);
    func_ov002_02207f04(obj, 10, 0, 0, 0x30);
    func_ov132_0229b578((int) obj);
    func_ov002_02208090(obj, 3);
}

void func_ov132_0229b598(int arg0)
{
    if (func_ov002_02207f3c(arg0, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) arg0, 5);
    } else {
        func_ov132_0229b578(arg0);
    }
}

void func_ov132_0229b578(int a)
{
    int zero = 0;
    func_ov002_02207e80(a, 6, zero, zero);
    func_ov002_02207e80(a, 4, zero, zero);
}

void func_ov132_0229b564(unsigned char *r0)
{
    r0[0x1502] = 0;
    *(unsigned short *) (r0 + 0x1500) = 0;
}

void func_ov132_0229b534(void *self)
{
    func_ov002_0220af74((char *) self + 0xf8);
    func_ov132_0229adb8(self);
    func_020b9ccc((char *) self + 0x39c);
    func_020b9ccc((char *) self + 0x3c0);
}
