/* func_ov142_0229bc34 @ 0x0229bc34, 0x30 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(int a, int b);
extern void func_020027f0(int c);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov142_0229bb08(int f);

void func_ov142_0229bc34(int param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) (param), 5);
    } else {
        func_ov142_0229bb08(param);
    }
}
