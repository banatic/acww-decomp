/* func_ov003_02233720 @ 0x02233720, 0xb8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02233720;
extern UnkStruct_02233720 *data_020ccf94;

extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern int func_ov003_02234d70(void *self);
extern void func_ov003_0222d518(void *self, int a);
extern void func_ov003_02234e28(void *self, short *t, int a, int b, int c, int d);
extern int func_020644cc(int n);
extern int FX_Div(int a, int b);
extern void func_ov003_02234dac(void *self, int a, int b, int c);

void func_ov003_02233720(char *self)
{
    short t;
    short *p;

    t = *(short *) (self + 0x23a);
    p = (short *) (self + 0x242);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0 || func_020a7278() != 0) {
        if (func_ov003_02234d70(self) == 2) {
            func_ov003_0222d518(self, 0x1000);
            *(char *) (self + 0x24a) = 0;
        }
    }
    func_ov003_02234e28(self, &t, 0x38e, 0x28, 0x50, *(u8 *) (self + 0x257) << 12);
    *p = *p + (short) FX_Div(0x2000, (func_020644cc(4) + 5) << 12);
    func_ov003_02234dac(self, *p, 0x1000, (func_020644cc(4) + 0xa) << 12);
}
