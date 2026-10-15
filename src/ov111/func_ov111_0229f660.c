/* func_ov111_0229f660 @ 0x0229f660, 0x48 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051c8c_unk(const void *, int);
extern void func_ov111_0229f854(void);
extern int func_02095804(void);
extern void RtcSendPxiCommand(int);
extern void func_ov111_0229fc9c(void);

int func_ov111_0229f660(unsigned char *self)
{
    if (self[0x9b]) {
        return 0;
    }
    if (func_02051c8c_unk(self + 0x3d16, 0x10) == 0) {
        // clang-format off
        asm {
            mov r0, self
        }
        // clang-format on
        func_ov111_0229f854();
    } else {
        func_02095804();
        RtcSendPxiCommand(0x32);
        // clang-format off
        asm {
            mov r0, self
        }
        // clang-format on
        func_ov111_0229fc9c();
        return 1;
    }
    return 0;
}
