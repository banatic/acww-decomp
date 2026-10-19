/* func_ov112_022a0068 @ 0x022a0068, 0x44 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200467c(int cmd);
extern void func_ov112_0229fe50(int a, int b);
extern void func_ov112_0229f45c(void *object, unsigned char flags, int mode);
extern void func_ov112_0229fe60(int a, int b);
extern void func_ov112_0229f1f4(int a);
extern void func_ov112_0229f8e4(int a);
extern void func_ov112_0229fd20(int a);

void func_ov112_022a0068(int param)
{
    func_0200467c(0x29);
    func_ov112_0229fe50(param, 0x2000);
    func_ov112_0229f45c((void *) param, 2, 9);
    func_ov112_0229fe60(param, 0x400);
    func_ov112_0229f1f4(param);
    func_ov112_0229f8e4(param);
    func_ov112_0229fd20(param);
}
