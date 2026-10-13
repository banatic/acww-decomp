/* func_ov002_022084e4 @ 0x022084e4, 0x38 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208458(int, int, int, int);
extern void func_02001bb4(int);
extern void func_02001da0(int);
extern void func_02001d1c(int);
extern void func_ov002_02208348(int, int);

void func_ov002_022084e4(int a0, int a1, int a2, int a3, int a4)
{
    func_ov002_02208458(a0, a2, a3, a4);
    func_02001bb4(1);
    func_02001da0(0x1f);
    func_02001d1c(~a1 & 0x1f);
    func_ov002_02208348(a0, 0);
}
