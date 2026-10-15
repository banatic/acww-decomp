/* func_ov138_0229cefc @ 0x0229cefc, 0x20 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229b954(void *);
extern void func_ov002_0220af94(void);

void func_ov138_0229cefc(void *self)
{
    func_ov134_0229b954((char *) self + 0x2c8);
    self = (char *) self + 0xfc;
    // clang-format off
    asm {
        mov r0, self
    }
    // clang-format on
    func_ov002_0220af94();
}
