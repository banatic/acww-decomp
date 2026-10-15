/* func_ov091_022990b0 @ 0x022990b0, 0x42 bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(int a, int b);
extern void func_020027f0(int a);
extern unsigned char *func_ov002_022080a0(int a, unsigned char value);
extern void func_ov002_02207e80(int a, int b, int c, int d);

void func_ov091_022990b0(int param)
{
    if (func_ov002_02207f3c(param, 1) != 0) {
        func_020027f0(0);
        func_020027f0(2);
        func_ov002_022080a0(param, 5);
    } else {
        func_ov002_02207e80(param, 0, 0, 0);
        func_ov002_02207e80(param, 2, 0, 0);
    }
}
