/* func_ov142_0229ace4 @ 0x0229ace4, 0x90 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov142_0229ae8c(void *p);
extern int func_ov142_0229a6d8(void *p);
extern int func_ov142_0229a6e8(void *p);
extern int func_02070918(void *a, int b, int c, int d, int e, int f);
extern void func_02070a98(void *a, int b, int c, int d, int e, int f, int g);
extern void func_0207099c(void *a);
extern void func_02070a04(void *a, int b, int c);

void func_ov142_0229ace4(void *param)
{
    void *obj;
    int val;

    obj = func_ov142_0229ae8c(param);
    val = func_ov142_0229a6d8(param);
    func_02070918(obj, val, 3, 0, 0, 0);
    func_02070a98(obj, 6, 0x156, 3, 0xe, 4, 0);
    func_0207099c(obj);

    obj = func_ov142_0229ae8c(param);
    val = func_ov142_0229a6e8(param);
    func_02070918(obj, val, 3, 0, 0, 0);
    func_02070a98(obj, 6, 0x15a, 3, 0xe, 4, 0);
    func_02070a04(obj, 0, 0);
}
