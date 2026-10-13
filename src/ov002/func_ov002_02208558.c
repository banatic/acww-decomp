/* func_ov002_02208558 @ 0x02208558, 0x3a bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208458(int, int, int, int);
extern void func_02001b7c(int);
extern void func_02001d74(int, int);
extern void func_02001d00(int);
extern void func_ov002_02208348(int, int);

void func_ov002_02208558(int a, int b, int c, int d, int e)
{
    func_ov002_02208458(a, c, d, e);
    func_02001b7c(1);
    func_02001d74(0x1f, 1);
    func_02001d00(~b & 0x1f);
    func_ov002_02208348(a, 2);
}
