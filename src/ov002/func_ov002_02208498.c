/* func_ov002_02208498 @ 0x02208498, 0x4c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208418(int, int, int, int);
extern void func_02001bb4(int);
extern void func_02001da0(int);
extern int func_02001bd0(void);
extern void func_02001d0c(int);
extern void func_02001d1c(int);
extern void func_ov002_02208348(int, int);

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
