/* func_020266d8 @ 0x020266d8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
} UnkStruct_020266d8;

extern void func_0209e474(UnkStruct_020266d8 *);
extern void (*data_020c8efc[5])(u16 *, UnkStruct_020266d8 *);

void func_020266d8(u16 *dst, int unused, u32 index)
{
    if (index < 5) {
        void (*func)(u16 *, UnkStruct_020266d8 *) = data_020c8efc[index];
        if (func != 0) {
            UnkStruct_020266d8 local;
            local.unk_00 = 0;
            local.unk_04 = 0;
            func_0209e474(&local);
            func(dst, &local);
            return;
        }
    }
    *dst = 0xfff1;
}
