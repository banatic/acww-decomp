/* func_ov135_0229cff0 @ 0x0229cff0, 0x20 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229b954(void *);
extern void func_ov002_0220af94(void);

void func_ov135_0229cff0(void *arg0)
{
    func_ov134_0229b954((char *) arg0 + 0x2c8);
    arg0 = (char *) arg0 + 0xfc;
    // clang-format off
    asm {
        mov r0, arg0
    }
    // clang-format on
    func_ov002_0220af94();
}
