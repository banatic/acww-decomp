/* func_ov145_0229a928 @ 0x0229a928, 0x30 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int n);
extern void func_020027f0(int n);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov145_0229a8e8(void *p);

void func_ov145_0229a928(void *arg)
{
    if (func_ov002_02207f3c(arg, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) (arg), 5);
    } else {
        func_ov145_0229a8e8(arg);
    }
}
