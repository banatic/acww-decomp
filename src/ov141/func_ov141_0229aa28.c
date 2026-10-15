/* func_ov141_0229aa28 @ 0x0229aa28, 0x2a bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(int a, int b);
extern void func_020027f0(int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov141_0229aa04(int a);

void func_ov141_0229aa28(int param)
{
    if (func_ov002_02207f3c(param, 0)) {
        func_020027f0(6);
        func_ov002_022080a0((void *) (param), 5);
    } else {
        func_ov141_0229aa04(param);
    }
}
