/* bank_amount_3: 12 functions, module ov131
 * mwccarm 1.2/base -O4,s
 * func_ov131_0229b1f0 @ 0x0229b1f0, 0x5c bytes, Thumb
 * func_ov131_0229b1c8 @ 0x0229b1c8, 0x28 bytes, Thumb
 * func_ov131_0229b188 @ 0x0229b188, 0x40 bytes, Thumb
 * func_ov131_0229b124 @ 0x0229b124, 0x62 bytes, Thumb
 * func_ov131_0229b10c @ 0x0229b10c, 0x16 bytes, Thumb
 * func_ov131_0229b0f0 @ 0x0229b0f0, 0x1c bytes, Thumb
 * func_ov131_0229b0d0 @ 0x0229b0d0, 0x20 bytes, Thumb
 * func_ov131_0229b07c @ 0x0229b07c, 0x54 bytes, Thumb
 * func_ov131_0229b04c @ 0x0229b04c, 0x30 bytes, Thumb
 * func_ov131_0229aff8 @ 0x0229aff8, 0x54 bytes, Thumb
 * func_ov131_0229afe8 @ 0x0229afe8, 0x10 bytes, Thumb
 * func_ov131_0229afd8 @ 0x0229afd8, 0x10 bytes, Thumb
 */

extern int func_0208e484(void *self);
extern int func_ov130_0229a080(void *self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov130_0229a070(void *self);
extern void func_ov131_0229aee4(void *self);
extern void func_ov131_0229af24(void *);
extern unsigned short data_021fbe40;
extern void func_ov130_0229a24c(void *p);
extern int func_ov130_0229a224(void *p);
extern int func_ov002_0220a700(char *p);
extern int func_0208e4bc(char *p);
extern int func_ov002_0220a6e0(char *p);
extern int func_ov002_0220a768(char *p, int x);
extern int func_ov002_0220a72c(char *p, int x);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov131_0229afbc(void *p);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov002_02207fc0(void *param);
extern int func_0206fe60(void);
extern int func_ov002_0220a620(char *p, int n);
extern int func_ov002_0220a720(char *p, int n);
extern void func_ov002_02208090(char *p, int n);
extern void func_0206fc4c(int n);
extern int func_ov130_02299ddc(char *p);
extern void func_0206f830(int argument0);
extern void func_ov131_0229ad5c(char *p);
extern void func_0200467c(int);
extern int func_ov130_0229a124(void *p);
extern void func_ov002_0220a374(void *p, int n);
extern unsigned int func_ov130_0229a148(unsigned int arg);
extern int func_ov130_0229a138(int);

int func_ov131_0229b07c(char *ptr);
void func_ov131_0229b04c(void *r0);
void func_ov131_0229aff8(void *p);
unsigned int func_ov131_0229afe8(unsigned int arg);
int func_ov131_0229afd8(int arg);

void func_ov131_0229b1f0(void *self)
{
    if (func_0208e484((char *) self + 0x94) != 0) {
        if (func_ov130_0229a080((char *) self + 0x2c4) != 0) {
            func_ov002_02208098((void *) (self), 6);
        } else {
            if (func_ov130_0229a070((char *) self + 0x2c4) != 0) {
                if (func_ov131_0229b07c((char *) self) != 0) {
                    return;
                }
                func_ov002_02208098((void *) (self), 2);
                func_ov131_0229aee4(self);
            } else {
                func_ov131_0229b04c(self);
            }
        }
    }
}

void func_ov131_0229b1c8(unsigned char *self)
{
    if (func_0208e484(self + 0x94)) {
        func_ov131_0229af24(self);
        func_ov002_02208098((void *) (self), self[0x1556]);
    }
}

void func_ov131_0229b188(void *p)
{
    if ((data_021fbe40 & 1) == 0) {
        func_ov130_0229a24c((char *) p + 0x2c4);
        func_ov002_02208098((void *) (p), 2);
        func_ov131_0229aee4(p);
    } else {
        func_ov130_0229a224((char *) p + 0x2c4);
    }
}

void func_ov131_0229b124(void *arg)
{
    if (func_ov002_0220a700((char *) arg + 0xf8) != 0) {
        if (func_0208e4bc((char *) arg + 0x94) != 0) {
            int r4, r6, r2;

            r4 = func_ov002_0220a6e0((char *) arg + 0xf8);
            r6 = func_ov002_0220a768((char *) arg + 0xf8, -1);
            r2 = func_ov002_0220a72c((char *) arg + 0xf8, -1);
            func_ov002_0220a0b4((char *) arg + 0x94, r4 + r6, r4 + r2);
        }
    } else {
        func_ov131_0229afbc(arg);
        func_ov002_022080a0((void *) (arg), 1);
    }
}

void func_ov131_0229b10c(int param)
{
    func_ov131_0229afbc((void *) param);
    func_ov002_02208098((void *) (param), 0);
}

void func_ov131_0229b0f0(void *param)
{
    func_ov131_0229aff8(param);
    func_ov002_02207fc0(param);
    func_ov002_02208098((void *) (param), 2);
}

void func_ov131_0229b0d0(int r0)
{
    if (func_0206fe60() != 0) {
        func_ov131_0229b10c(r0);
    } else {
        func_ov131_0229b0f0((void *) r0);
    }
}

int func_ov131_0229b07c(char *ptr)
{
    if (func_ov002_0220a620(ptr + 0xf8, 6) != 0) {
        return 0;
    }

    func_ov002_0220a720(ptr + 0xf8, 6);
    func_ov002_02208090(ptr, 2);
    func_ov002_02208098((void *) (ptr), 7);
    func_0206fc4c(1);

    func_0206f830(func_ov130_02299ddc(ptr + 0x2c4));
    func_ov131_0229ad5c(ptr);

    return 1;
}

void func_ov131_0229b04c(void *r0)
{
    func_0200467c(0x2a);
    func_0206fc4c(0);
    func_ov002_0220a720((char *) ((char *) r0 + 0xf8), 7);
    func_ov002_02208090((char *) r0, 2);
    func_ov002_02208098((void *) (r0), 7);
}

void func_ov131_0229aff8(void *p)
{
    int a;
    int b;

    a = (int) func_ov131_0229afe8((unsigned int) p);
    b = func_ov131_0229afd8((int) p);
    func_ov002_0220a0b4((char *) ((char *) p + 0x94), a, b);
    if (func_ov130_0229a124((char *) p + 0x2c4) != 0) {
        func_ov002_0220a374((char *) p + 0x94, 7);
    } else {
        func_ov002_0220a374((char *) p + 0x94, 1);
    }
    func_ov131_0229af24(p);
}

unsigned int func_ov131_0229afe8(unsigned int arg)
{
    return func_ov130_0229a148(arg + 0x2c4);
}

int func_ov131_0229afd8(int arg)
{
    return func_ov130_0229a138(arg + 0x2c4);
}
