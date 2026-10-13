/* func_ov093_02299338 @ 0x02299338, 0x44 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b4a20(void *dst, void *src, void *data);
extern void func_020a7bf4(void *dst, int value);
extern int _s32_div_f(int value, int count);

extern unsigned char data_ov093_0229990c[];

void func_ov093_02299338(void *self, int param)
{
    int result;
    unsigned char byte;
    void *ptr;

    result = _s32_div_f(param, 6);
    byte = (unsigned char) result;
    ptr = &byte;
    func_020b4a20((char *) self + 0x1828, ptr, (void *) data_ov093_0229990c);
    func_020a7bf4((char *) self + 0x183a, param - result * 6);
}
