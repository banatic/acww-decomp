/* func_ov129_0229d618 @ 0x0229d618, 0x3c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *a, int b);
extern void func_020027f0(int n);
extern void func_02001b6c(int n);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov129_0229d5a4(void *a);
extern void func_ov129_0229d5ec(void *a);

void func_ov129_0229d618(void *param)
{
    if (func_ov002_02207f3c(param, 0)) {
        func_020027f0(3);
        func_020027f0(6);
        func_02001b6c(2);
        func_ov002_022080a0((void *) (param), 5);
    } else {
        func_ov129_0229d5a4(param);
        func_ov129_0229d5ec(param);
    }
}
