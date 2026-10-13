/* func_ov106_0229ece8 @ 0x0229ece8, 0x50 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *param, int flag);
extern void func_020027f0(int size);
extern void func_ov106_0229c344(void *param, int value);
extern void func_ov002_02207f04(void *param, int a, int b, int c, int d);
extern void func_ov002_02208090(void *param, int val);
extern void func_ov106_0229ec8c(void *param);
extern void func_ov106_0229eadc(void *param);

void func_ov106_0229ece8(void *arg)
{
    if (func_ov002_02207f3c(arg, 0)) {
        func_020027f0(4);
        func_ov106_0229c344(arg, 0x200);
        func_ov002_02207f04(arg, 8, 0, 0, 0x30);
        func_ov002_02208090(arg, 6);
        func_ov106_0229ec8c(arg);
    } else {
        func_ov106_0229eadc(arg);
    }
}
