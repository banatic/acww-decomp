/* func_ov095_0229bc00 @ 0x0229bc00, 0xec bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_021fbe94;

extern void *func_020e9958(void *p, int size);
extern void func_020e993c(void *p, void *handle);
extern void func_02051c08(void *a, void *b, u32 c);
extern int func_ov095_0229bcec(u32 a0, void *handle, u32 a2, u8 *bytep, u32 a4, u32 a5, u32 a7, u32 a8);
extern int func_0206de88(void *handle, void *out1, void *out2, u32 a4, u32 a5, u32 a7, u32 a6);
extern int func_ov095_022999b0(u32 a0, int param);
extern void func_ov095_022999a8(u32 a0, int param);
extern void func_ov095_022999c0(u32 a0, u16 param);

int func_ov095_0229bc00(u32 a0, u16 *a1, u32 a2, u8 *a3, u32 a4, u32 a5, u32 a6, u32 a7, u32 a8, u32 a9)
{
    u32 a2_save = a2;
    u8 *a3_save = a3;
    void *p = data_021fbe94;
    void *handle;
    u8 byte;
    u32 buf2[1]; // 4 bytes
    u32 buf1[8]; // 32 bytes

    handle = func_020e9958(p, 0xC0);
    if (handle == 0) {
        return 0;
    }

    func_02051c08(a1, handle, a4);

    byte = *a3_save;

    if (!func_ov095_0229bcec(a0, handle, a2_save, &byte, a4, 0x2710, a8, 0)) {
        func_020e993c(p, handle);
        return 0;
    }

    if (!func_0206de88(handle, buf1, buf2, a4, a5, a7, a6)) {
        func_020e993c(p, handle);
        if (func_ov095_022999b0(a0, 0x100) == 0) {
            func_ov095_022999a8(a0, 0x80);
        }
        return 0;
    }

    if (a8 == 0) {
        func_02051c08(handle, a1, a4);
        *a3_save = byte;
        if (a9 == 1 && byte != 0) {
            func_ov095_022999c0(a0, a1[byte - 1]);
        }
    }

    func_020e993c(p, handle);
    return 1;
}
