/* func_ov146_0229ae28 @ 0x0229ae28, 0x38 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ee45c(void *obj);
extern void func_ov092_02299324(void *a, int b, int c);
extern void func_ov002_02207f04(void *obj, int a, int b, int c, int d);
extern void func_ov146_0229adb8(void *obj);
extern void func_ov002_02208090(void *obj, int a);

void func_ov146_0229ae28(void *obj)
{
    int zero = 0;

    func_ov092_02299324(func_020ee45c(obj), 0x44, 1);
    func_ov002_02207f04(obj, 10, zero, zero, 0x28);
    func_ov146_0229adb8(obj);
    func_ov002_02208090(obj, 3);
}
