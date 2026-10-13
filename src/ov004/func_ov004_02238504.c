/* func_ov004_02238504 @ 0x02238504, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02239460(int a, int b);
extern int _s32_div_f(int a, int b);

void func_ov004_02238504(void *self)
{
    *(int *) ((char *) self + 0x208) = _s32_div_f(func_ov004_02239460(0xb, 0xf) << 12, 0xa);
    *(int *) ((char *) self + 0x200) = _s32_div_f(func_ov004_02239460(0x14, 0x32) << 12, 0x3e8);
    *(int *) ((char *) self + 0x204) = _s32_div_f(func_ov004_02239460(0xa, 0x1e) << 12, 0x3e8);
    *((char *) self + 0x20c) = (char) func_ov004_02239460(1, 0x96);
    *((char *) self + 0x20d) = (char) func_ov004_02239460(0xa, 0x78);
    *(int *) ((char *) self + 0x158) = 0;
    *(int *) ((char *) self + 0x110) = 0;
    *((char *) self + 0x20e) = 1;
}
