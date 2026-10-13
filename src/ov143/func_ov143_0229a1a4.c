/* func_ov143_0229a1a4 @ 0x0229a1a4, 0x5c bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Func_ov143_0229a1a4_s {
    u8 pad_00[0x9C];
    u16 unk_9C;
    u8 pad_9E[2];
    void *unk_A0;
} Func_ov143_0229a1a4_t;

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);
extern int func_02073d80(void *);
extern void MI_CpuCopy8(void *, void *, int);

void func_ov143_0229a1a4(Func_ov143_0229a1a4_t *self)
{
    u8 buf[0x11];
    void *obj;

    if (func_02073d90(data_020ccf94) != 0) {
        buf[0] = 0xC;
        MI_CpuCopy8(self->unk_A0, buf + 1, 0x10);
        obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, buf, 0x11);
        func_02073770(obj, 0x16, 4);
        self->unk_9C = (u16) func_02073d80(obj);
    }
}
