/* func_ov131_0229b3d4 @ 0x0229b3d4, 0x20 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov130_0229a3a0(void *);
extern void func_ov002_0220af94(void);

void func_ov131_0229b3d4(void *arg0)
{
    func_ov130_0229a3a0((char *) arg0 + 0x2c4);
    arg0 = (char *) arg0 + 0xf8;
    // clang-format off
    asm {
        mov r0, arg0
    }
    // clang-format on
    func_ov002_0220af94();
}
