/* func_ov096_0229da6c @ 0x0229da6c, 0x80 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229da6c {
    u8 pad_00[0xc4];
    int unk_C4;
} UnkStruct_0229da6c;

typedef struct UnkStruct_0229da6c_2 {
    u8 pad_00[0x64];
    int unk_64;
} UnkStruct_0229da6c_2;

extern u8 data_020e54a8;
extern UnkStruct_0229da6c_2 *data_020ccf94;
extern int func_020435fc(int a, int b);
extern void func_ov096_0229fb9c(UnkStruct_0229da6c *self);
extern void func_ov096_0229f874(UnkStruct_0229da6c *self, int a, int b, int c);
extern void func_0200467c(int a);
extern int func_020b67d4(void);
extern int func_ov097_022a27fc(UnkStruct_0229da6c *self, int p);

int func_ov096_0229da6c(UnkStruct_0229da6c *self, int p)
{
    unsigned int ok;

    ok = (data_020e54a8 == 0) ? 1 : 0;
    if (ok > 0) {
        self->unk_C4 = func_020435fc(data_020ccf94->unk_64, p);
        if (self->unk_C4 == -1) {
            func_ov096_0229fb9c(self);
            func_ov096_0229f874(self, 3, 0xff, 0);
            func_0200467c(0x73);
            return 0;
        }
        return 2;
    }
    if (func_020b67d4() != 0) {
        return func_ov097_022a27fc(self, p);
    }
    return 0;
}
