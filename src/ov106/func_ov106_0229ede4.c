/* func_ov106_0229ede4 @ 0x0229ede4, 0x60 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f48(void *a, int b);
extern void func_ov002_02207f20(void *a, int b, int c, int d, int e);
extern void func_ov002_02207e90(void *a, int b);
extern void func_02002708(int a);
extern void func_ov002_02208090(void *a, int b);
extern void func_ov106_0229eafc(void *a);
extern void func_ov106_0229e88c(void *a);
extern void func_ov106_0229c354(void *a, int b);
extern void func_ov106_0229eadc(void *a);

void func_ov106_0229ede4(void *param)
{
    void *res;
    res = func_ov002_02207f48(param, 0);
    func_ov106_0229eafc(param);
    if (res != 0) {
        func_ov106_0229e88c(param);
        func_ov002_02207f20(param, 2, 0, 2, 0x30);
        func_ov002_02207e90(param, 0xC0);
        func_02002708(4);
        func_ov106_0229c354(param, 0x200);
        func_ov106_0229eadc(param);
        func_ov002_02208090(param, 3);
    }
}
