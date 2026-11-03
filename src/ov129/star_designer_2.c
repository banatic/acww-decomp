/* star_designer_2: 5 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229d244 @ 0x0229d244, 0x8 bytes, Thumb
 * func_ov129_0229d218 @ 0x0229d218, 0x2c bytes, Thumb
 * func_ov129_0229d1b8 @ 0x0229d1b8, 0x60 bytes, Thumb
 * func_ov129_0229d180 @ 0x0229d180, 0x38 bytes, Thumb
 * func_ov129_0229d110 @ 0x0229d110, 0x70 bytes, Thumb
 */

extern void func_020b1800(void *);
extern void func_ov002_0220af74(void *);
extern void func_ov129_0229b7cc(void *, int);
extern void func_ov127_02299e64(void *addr);
extern int func_ov129_0229b7ec(void *self, int n);
extern void func_ov129_0229b7dc(void *self, int n);
extern void func_02004658(int v);
extern void func_02004644(int v, int n);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_020b177c(void *ptr, int a);
extern void func_ov127_0229a04c(void *ptr, int a);
extern void func_ov127_02299fd4(unsigned char *self, unsigned char val, int mode);
extern void func_ov127_02299f90(void *receiver);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_0220abbc(void *ptr);
extern void func_ov002_0220a63c(void *ptr, int a);
extern void func_ov002_0220a658(void *ptr, int a);

void func_ov129_0229d1b8(void *self);

void func_ov129_0229d244(void *argument0)
{
    func_ov129_0229d1b8(argument0);
}

void func_ov129_0229d218(void *self)
{
    func_020b1800((char *) self + 0x404);
    func_ov002_0220af74((char *) self + 0x1d4);
    func_ov129_0229b7cc(self, 0x40);
}

void func_ov129_0229d1b8(void *self)
{
    func_ov127_02299e64((char *) self + 0x734);
    if (func_ov129_0229b7ec(self, 0x40) != 0) {
        if (func_ov129_0229b7ec(self, 0x20) == 0) {
            func_ov129_0229b7dc(self, 0x20);
            func_02004658(0x883);
        }
    } else {
        if (func_ov129_0229b7ec(self, 0x20) != 0) {
            func_ov129_0229b7cc(self, 0x20);
            func_02004644(0x883, 1);
        }
    }
}

void func_ov129_0229d180(void)
{
    func_02001c08(0);
    func_020029e8(3, 2);
    func_020028bc(3, 1, 0, 0);
    func_020029e8(6, 1);
    func_020028bc(6, 0, 0, 0);
}

void func_ov129_0229d110(void *self)
{
    func_ov127_0229a04c((char *) self + 0x734, 3);
    func_ov127_02299fd4((unsigned char *) self + 0x734, 6, 1);
    func_020b177c((char *) self + 0x404, 3);
    func_ov127_02299f90((void *) ((char *) self + 0x734));
    func_ov002_0220af94((void *) ((char *) self + 0x1d4));
    func_ov002_0220abbc((char *) self + 0x1d4);
    if (*(unsigned char *) ((char *) self + 0xb1) == 2) {
        func_ov002_0220a63c((char *) self + 0x1d4, 6);
    } else {
        func_ov002_0220a658((char *) self + 0x1d4, 6);
    }
}
