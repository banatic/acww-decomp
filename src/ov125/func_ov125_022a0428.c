/* func_ov125_022a0428 @ 0x022a0428, 0x4c bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001c08(unsigned char value);
extern void func_020029e8(int layer, int priority);
extern void func_020028bc(unsigned int mode, int a, int b, int c);

void func_ov125_022a0428(void)
{
    func_02001c08(0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
    func_020029e8(3, 1);
    func_020028bc(3, 0, 0, 0);
}
