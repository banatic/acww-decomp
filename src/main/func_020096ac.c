/* func_020096ac @ 0x020096ac, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern fx32 FX_Div(fx32 numer, fx32 denom);

typedef struct {
    unsigned char pad_00[0x60];
    int unk_60;
    int unk_64;
} UnkStruct_020096ac;

extern int func_0200f290(UnkStruct_020096ac *self, int a);
extern int func_0201100c(UnkStruct_020096ac *self);
extern void *func_0209d5e8(void);
extern int func_0209d848(void *p);
extern int func_020310c8(int a);
extern void *func_0209d844(void *p);

void func_020096ac(UnkStruct_020096ac *self)
{
    void *p;
    int *f60;
    int target;
    int diff;

    if (func_0200f290(self, 0x18)) {
        func_0201100c(self);
        p = func_0209d5e8();
        if (func_0209d848(p) != 1) {
            return;
        }
        f60 = &self->unk_60;
        target = func_020310c8(0);
        if (*f60 >= target) {
            void *q = func_0209d844(p);
            diff = *(int *) ((char *) q + 8) - self->unk_64;
            if (diff < 0) {
                diff = -diff;
            }
            if (diff < 0x1000) {
                int scaled = FX_Div(0x1000 - diff, 0x1000) * 6;
                *f60 = *f60 + (scaled >> 5);
            } else {
                *f60 = target;
            }
        } else {
            *f60 = target;
        }
    } else {
        func_0201100c(self);
    }
}
