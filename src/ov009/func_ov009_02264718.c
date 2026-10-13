/* func_ov009_02264718 @ 0x02264718, 0x16c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_021c526c;
extern int func_02095de0(void);
extern int func_ov009_02264c90(void *self);
extern void func_ov003_022203a0(int);
extern void func_02035c10(void *ptr, int);
extern int func_ov003_02219a40(void);
extern int func_0204bcdc(void *ptr);
extern int func_0204bc64(void *ptr);

struct UnkStruct_02264718 {
    u8 pad_00[0x136];
    u16 unk_136;
    u8 pad_138[0xfc];
    u8 unk_234;
};

void func_ov009_02264718(struct UnkStruct_02264718 *self)
{
    u16 temp[2];

    if (self->unk_234 < 1) {
        return;
    }
    if (self->unk_234 != 3) {
        goto inc;
    }
    if (func_02095de0() == 0) {
        goto inc;
    }

    switch (func_ov009_02264c90(self)) {
        case 2:
            func_ov003_022203a0(1);
            func_02035c10((char *) data_021c526c + 0x2d0, 1);
            if (func_ov003_02219a40() == 0) {
                goto inc;
            }
            self->unk_234 = 0;
            return;
        case 3:
            func_ov003_022203a0(0);
            func_02035c10((char *) data_021c526c + 0x2d0, 2);
            if (func_ov003_02219a40() == 0) {
                goto inc;
            }
            self->unk_234 = 0;
            return;
        case 1:
            func_ov003_022203a0(0);
            {
                int flag;
                if (func_0204bcdc(&self->unk_136) != 0) {
                    temp[0] = 0x5012;
                    flag = (func_0204bc64(&self->unk_136) == func_0204bc64(&temp[0]));
                } else {
                    flag = (self->unk_136 == 0x5012);
                }
                if (flag) {
                    goto do_4;
                }

                if (func_0204bcdc(&self->unk_136) != 0) {
                    temp[1] = 0x5013;
                    flag = (func_0204bc64(&self->unk_136) == func_0204bc64(&temp[1]));
                } else {
                    flag = (self->unk_136 == 0x5013);
                }
                if (flag) {
                do_4:
                    func_02035c10((char *) data_021c526c + 0x2d0, 4);
                } else {
                    func_02035c10((char *) data_021c526c + 0x2d0, 3);
                }
            }
            if (func_ov003_02219a40() == 0) {
                goto inc;
            }
            self->unk_234 = 0;
            return;
        default:
            self->unk_234 = 0;
            return;
    }

inc:
    if (self->unk_234 < 3) {
        self->unk_234++;
    }
}
