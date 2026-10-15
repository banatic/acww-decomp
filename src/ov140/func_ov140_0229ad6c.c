/* func_ov140_0229ad6c @ 0x0229ad6c, 0x2a bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(int a, int b);
extern void func_020027f0(int x);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov140_0229ad4c(int a);

int func_ov140_0229ad6c(int arg)
{
    if (func_ov002_02207f3c(arg, 0) != 0) {
        func_020027f0(6);
        return (int) func_ov002_022080a0((void *) (arg), 5);
    } else {
        return func_ov140_0229ad4c(arg);
    }
}
