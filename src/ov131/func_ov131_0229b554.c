/* func_ov131_0229b554 @ 0x0229b554, 0x38 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(void *p) __attribute__((arm));
extern void func_ov092_02299324(int a, int b, int c);
extern void func_ov002_02207f04(void *p, int a, int b, int c, int d);
extern void func_ov131_0229b504(void *p);
extern void func_ov002_02208090(void *p, int a);

void func_ov131_0229b554(void *arg)
{
    func_ov092_02299324(func_020ee45c(arg), 0x44, 1);
    func_ov002_02207f04(arg, 10, 0, 0, 0x30);
    func_ov131_0229b504(arg);
    func_ov002_02208090(arg, 3);
}
