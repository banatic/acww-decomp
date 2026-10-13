/* func_ov113_0229a590 @ 0x0229a590, 0x30 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *ptr, int i);
extern void func_0200277c(int i);
extern void func_ov002_02208090(void *ptr, int i);
extern void func_ov002_02207e80(void *ptr, int i, int j, int k);

void func_ov113_0229a590(void *arg)
{
    int zero = 0;
    if (func_ov002_02207f3c(arg, 1)) {
        func_0200277c(2);
        func_ov002_02208090(arg, 7);
    } else {
        func_ov002_02207e80(arg, 2, zero, zero);
    }
}
