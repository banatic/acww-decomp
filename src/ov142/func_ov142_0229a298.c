/* func_ov142_0229a298 @ 0x0229a298, 0x128 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov142_0229b10c(void *self);
extern int func_ov142_02299668(void *self, int a);
extern void func_ov142_0229b138(void *self);
extern void func_ov002_0220a574(void *p);
extern void func_ov002_0220a4bc(void);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov142_0229b350(void *self);
extern void func_ov142_0229b2f8(void *self);
extern void func_ov142_02299928(void *self);
extern void func_ov142_02299918(void *self);
extern void RtcSendPxiCommand(int a);
extern void func_ov142_0229ab68(void *self, u8 a);
extern int func_ov142_0229a0f8(void *self, u8 a, s16 b);

int func_ov142_0229a298(char *self, int param)
{
    switch (param) {
        case 0x13:
            func_ov142_0229b10c(self);
            return 1;

        case 0x12:
            if (func_ov142_02299668(self, 0x20) != 0) {
                func_ov142_0229b138(self);
                return 1;
            }
            return 0;

        case 0x14:
            func_ov002_0220a574(self + 0x14c);
            // clang-format off
            asm {
                ldr r0, =0x14c
                add r0, self, r0
            }
            // clang-format on
            func_ov002_0220a4bc();
            func_ov002_02208098((void *) (self), 5);
            return 1;

        case 0x17:
            func_ov142_0229b350(self);
            return 1;

        case 0x18:
            func_ov142_0229b2f8(self);
            return 1;

        case 0x15:
            if (func_ov142_02299668(self, 0x400) != 0) {
                return 0;
            }
            func_ov142_02299928(self);
            func_ov002_02208098((void *) (self), 7);
            return 1;

        case 0x16:
            if (func_ov142_02299668(self, 0x800) != 0) {
                return 0;
            }
            func_ov142_02299918(self);
            func_ov002_02208098((void *) (self), 7);
            return 1;

        default:
            if ((u32) param <= 8) {
                if (*(u8 *) (self + 0xbd) != param) {
                    RtcSendPxiCommand(0xc);
                    func_ov142_0229ab68(self, (u8) param);
                }
                return 0;
            }
            if ((u32) param >= 9 && (u32) param <= 0x11) {
                if (*(u8 *) (self + 0xc2) != 0) {
                    return 0;
                }
                if (func_ov142_0229a0f8(self, *(u8 *) (self + 0xbc), (s16) (*(s16 *) (self + 0xb4) + (param - 9))) != 0) {
                    RtcSendPxiCommand(0x29);
                }
            }
            return 0;
    }
}
