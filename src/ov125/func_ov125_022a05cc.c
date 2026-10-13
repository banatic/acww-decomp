/* func_ov125_022a05cc @ 0x022a05cc, 0x70 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov125_0229faf8(void *p);
extern int __arm func_020ee45c(void *p);
extern int func_0206fca4(int a);
extern int func_ov125_0229f76c(void *p, int b);
extern void func_ov092_02299324(int a, int b, int c);
extern void func_ov002_02207f04(void *p, int a, int b, int c, int d);
extern void func_ov125_022a0564(void *p);
extern void func_ov002_02208090(void *p, int a);

void func_ov125_022a05cc(void *p)
{
    int a, b;

    func_ov125_0229faf8(p);
    a = func_020ee45c(p);
    b = func_0206fca4(a);
    if (func_ov125_0229f76c(p, 0x10) != 0) {
        func_ov092_02299324(a, 0x44, 1);
    } else {
        if (b == 4) {
            func_ov092_02299324(a, 2, 1);
        } else {
            func_ov092_02299324(a, 0x44, 1);
        }
    }
    func_ov002_02207f04(p, 0xa, 0, 0, 0x30);
    func_ov125_022a0564(p);
    func_ov002_02208090(p, 4);
}
