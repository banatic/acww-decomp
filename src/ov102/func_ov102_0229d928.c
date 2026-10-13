/* func_ov102_0229d928 @ 0x0229d928, 0x58 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02209f9c(void *ptr);
extern void func_ov102_0229d320(void *self);
extern void func_ov102_0229cdf4(void *self);
extern void func_ov002_02208098(void *self, int a);
extern void func_ov094_022999d8(void);
extern void func_ov102_0229d54c(void *self, u8 a, int b);
extern void func_ov102_0229cd38(void *self);

typedef struct {
    u8 pad_00[0x25a5];
    u8 unk_25A5;
    u8 unk_25A6;
} UnkStruct_0229d928;

void func_ov102_0229d928(UnkStruct_0229d928 *self)
{
    if (func_ov002_02209f9c((char *) self + 0x2274) == 0) {
        if (self->unk_25A5 == self->unk_25A6) {
            func_ov102_0229d320(self);
            func_ov102_0229cdf4(self);
            func_ov002_02208098(self, 3);
            func_ov094_022999d8();
        } else {
            func_ov102_0229d54c(self, self->unk_25A6, 4);
        }
    } else {
        func_ov102_0229cd38(self);
    }
}
