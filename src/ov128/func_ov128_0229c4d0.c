/* func_ov128_0229c4d0 @ 0x0229c4d0, 0x3c bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *x, int y);
extern void func_020027f0(int x);
extern void func_02001b6c(int x);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov128_0229c464(void *x);
extern void func_ov128_0229c4ac(void *x);

void func_ov128_0229c4d0(void *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(3);
        func_020027f0(6);
        func_02001b6c(2);
        func_ov002_022080a0((void *) (param), 5);
    } else {
        func_ov128_0229c464(param);
        func_ov128_0229c4ac(param);
    }
}
