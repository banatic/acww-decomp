/* func_ov082_02278ab8 @ 0x02278ab8, 0xac bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02278ab8 {
    u8 pad_00[0x1e];
    u8 unk_1E;
    u8 pad_1F[0x21];
    void *unk_40;
    u8 pad_44[0x84];
    int unk_C8;
} UnkStruct_02278ab8;

typedef struct LocalData {
    u8 code;
    u8 subcode;
    u16 value;
} LocalData;

extern int func_020160b4(void *);
extern int func_020ab504(int);
extern void func_0209a050(int);
extern void func_02015330(UnkStruct_02278ab8 *, u16 *, int, int, int);
extern void func_0206844c(void *, void *, void *);
extern int func_ov082_02278dec(UnkStruct_02278ab8 *);
extern u8 data_ov082_022798c8[];
extern u8 data_ov082_022798d8[];

void func_ov082_02278ab8(UnkStruct_02278ab8 *self)
{
    int res;
    u8 *param;
    u8 code;
    int state;
    LocalData data;

    res = func_020ab504(func_020160b4(self));
    param = data_ov082_022798c8;
    code = 0xff;
    state = self->unk_C8;

    if (state >= 0) {
        param = data_ov082_022798d8;
        if (self->unk_1E == 0 && res == 0) {
            if (state >= 0) {
                func_0209a050(state);
                data.value = 0x37e0;
                func_02015330(self, &data.value, 0, 5, 0);
            }
            code = 2;
        }
        if (code != 0xff) {
            data.code = code;
            func_0206844c(self->unk_40, &data, param);
        }
    } else {
        if (self->unk_1E == 8) {
            if (res != 0) {
                int r;
                r = func_ov082_02278dec(self);
                if (r == 0) {
                    code = 9;
                } else if (r > 0) {
                    code = 0xa;
                } else {
                    code = 0x1e;
                }
            } else {
                code = 0xb;
            }
        }
        if (code != 0xff) {
            data.subcode = code;
            func_0206844c(self->unk_40, &data.subcode, param);
        }
    }
}
