/* bank_amount_5: 10 functions, module ov131
 * mwccarm 1.2/base -O4,s
 * func_ov131_0229b624 @ 0x0229b624, 0x4 bytes, Thumb
 * func_ov131_0229b620 @ 0x0229b620, 0x4 bytes, Thumb
 * func_ov131_0229b610 @ 0x0229b610, 0x10 bytes, Thumb
 * func_ov131_0229b5b4 @ 0x0229b5b4, 0x5a bytes, Thumb
 * func_ov131_0229b58c @ 0x0229b58c, 0x28 bytes, Thumb
 * func_ov131_0229b554 @ 0x0229b554, 0x38 bytes, Thumb
 * func_ov131_0229b524 @ 0x0229b524, 0x30 bytes, Thumb
 * func_ov131_0229b504 @ 0x0229b504, 0x20 bytes, Thumb
 * func_ov131_0229b4cc @ 0x0229b4cc, 0x38 bytes, Thumb
 * func_ov131_0229b4b0 @ 0x0229b4b0, 0x1c bytes, Thumb
 */

extern void func_020ee470(void *argument0);
extern int func_ov002_02207f48(void *, int kind);
extern unsigned char *func_ov002_022080a0(void *, unsigned char v);
extern void func_ov131_0229b0d0(int r0);
extern int func_020ee45c(void *p) __attribute__((arm));
extern void func_ov092_02299324(int a, int b, int c);
extern void func_ov002_02207f04(void *p, int a, int b, int c, int d);
extern void func_ov002_02208090(void *p, int a);
extern int func_ov002_02207f3c(int a, int b);
extern void func_020027f0(int a);
extern void func_ov002_02207e80(void *param1, int param2, int param3, int param4);
extern int func_0206fca4(void);
extern void func_ov130_0229a6d8(void *ptr, unsigned char val, int a, int b);
extern void func_ov131_0229ae0c(void *self);
extern void func_ov002_0220af74(void *p);
extern void func_ov130_0229a378(void *p);

void func_ov131_0229b504(void *param1);

int func_ov131_0229b624(void)
{
    return 1;
}

int func_ov131_0229b620(void)
{
    return 1;
}

int func_ov131_0229b610(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov131_0229b5b4(void *r0)
{
    extern void func_ov131_0229b404(void);
    extern void func_ov131_0229b3f4(void *);
    extern void func_ov131_0229b3d4(void *);
    extern void func_02002708(int);
    extern void func_ov131_0229b504(void *);
    extern void func_ov131_0229ad34(void *, int);
    extern int func_ov002_0220ab38(void *, int);
    extern void func_ov002_02208090(void *, int);
    extern void func_ov002_02207f20(void *, int, int, int, int);

    void *r4 = r0;
    func_ov131_0229b404();
    func_ov131_0229b3f4(r4);
    func_ov131_0229b3d4(r4);
    func_ov002_02207f20(r4, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov131_0229b504(r4);
    func_ov131_0229ad34(r4, 1);
    func_ov002_0220ab38((char *) r4 + 0xf8, 0x65);
    func_ov002_02208090(r4, 1);
}

void func_ov131_0229b58c(int arg0)
{
    if (func_ov002_02207f48((void *) arg0, 0) != 0) {
        func_ov002_022080a0((void *) arg0, 2);
        func_ov131_0229b0d0(arg0);
    }
    func_ov131_0229b504((void *) arg0);
}

void func_ov131_0229b554(void *arg)
{
    func_ov092_02299324(func_020ee45c(arg), 0x44, 1);
    func_ov002_02207f04(arg, 10, 0, 0, 0x30);
    func_ov131_0229b504(arg);
    func_ov002_02208090(arg, 3);
}

void func_ov131_0229b524(int arg)
{
    if (func_ov002_02207f3c(arg, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) (arg), 5);
    } else {
        func_ov131_0229b504((void *) arg);
    }
}

void func_ov131_0229b504(void *param1)
{
    func_ov002_02207e80(param1, 6, 0, 0);
    func_ov002_02207e80(param1, 4, 0, 0);
}

void func_ov131_0229b4cc(void *self)
{
    int result;
    unsigned char byte_val;

    result = func_0206fca4();
    byte_val = (unsigned char) (result - 0x34);
    func_ov130_0229a6d8((char *) self + 0x2c4, byte_val, 6, 4);
    func_ov131_0229ae0c(self);
    *((unsigned short *) ((char *) self + 0x1554)) = 0;
}

void func_ov131_0229b4b0(void *p)
{
    func_ov002_0220af74((char *) p + 0xf8);
    func_ov130_0229a378((char *) p + 0x2c4);
}
