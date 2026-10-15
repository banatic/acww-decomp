/* func_ov134_0229b5ac @ 0x0229b5ac, 0x46 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov134_0229b680(int);
extern int func_02070918(void *, int, int, int, int, int);
extern void func_02070adc(void *, int, int, int, int, int, int);
extern void func_0207099c(void *);

void func_ov134_0229b5ac(int arg0, int arg1, int arg2, int arg3, int arg4, unsigned char arg5, unsigned char arg6)
{
    void *obj;
    int tmp1;
    int tmp2;
    int tmp3;

    obj = func_ov134_0229b680(arg0);
    tmp1 = 0;
    tmp2 = 0;
    func_02070918(obj, arg4, 4, 0, tmp1, tmp2);
    tmp1 = arg5;
    tmp2 = arg6;
    tmp3 = 0;
    func_02070adc(obj, arg1, arg2, arg3, tmp1, tmp2, tmp3);
    func_0207099c(obj);
}
