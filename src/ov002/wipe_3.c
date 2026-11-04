/* wipe_3: 4 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_02208558 @ 0x02208558, 0x3a bytes, Thumb
 * func_ov002_0220851c @ 0x0220851c, 0x3a bytes, Thumb
 * func_ov002_022084e4 @ 0x022084e4, 0x38 bytes, Thumb
 * func_ov002_02208498 @ 0x02208498, 0x4c bytes, Thumb
 */

extern void func_ov002_02208458(int, int, int, int);
extern void func_02001b7c(int);
extern void func_02001d74(int, int);
extern void func_02001d00(int);
extern void func_ov002_02208348(int, int);
extern void func_ov002_02208418(int, int, int, int);
extern void func_02001bb4(int);
extern void func_02001da0(int);
extern void func_02001d1c(int);
extern int func_02001bd0(void);
extern void func_02001d0c(int);

void func_ov002_02208558(int a, int b, int c, int d, int e)
{
    func_ov002_02208458(a, c, d, e);
    func_02001b7c(1);
    func_02001d74(0x1f, 1);
    func_02001d00(~b & 0x1f);
    func_ov002_02208348(a, 2);
}

void func_ov002_0220851c(int a, int b, int c, int d, int e)
{
    func_ov002_02208418(a, c, d, e);
    func_02001b7c(1);
    func_02001d74(0x1f, 1);
    func_02001d00(~b & 0x1f);
    func_ov002_02208348(a, 2);
}

void func_ov002_022084e4(int a0, int a1, int a2, int a3, int a4)
{
    func_ov002_02208458(a0, a2, a3, a4);
    func_02001bb4(1);
    func_02001da0(0x1f);
    func_02001d1c(~a1 & 0x1f);
    func_ov002_02208348(a0, 0);
}

void func_ov002_02208498(int a, int b, int c, int d, int e)
{
    int x;
    func_ov002_02208418(a, c, d, e);
    func_02001bb4(1);
    func_02001da0(0x1f);
    x = func_02001bd0();
    x &= 2;
    if (x) {
        func_02001d0c(b);
    } else {
        func_02001d1c(~b & 0x1f);
    }
    func_ov002_02208348(a, 0);
}
