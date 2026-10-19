/* func_ov121_0229a63c @ 0x0229a63c, 0x78 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229a63c UnkStruct_0229a63c;
struct UnkStruct_0229a63c {
    u8 pad_00[0x98];
    int unk_98;
    u8 pad_9C[4];
    u16 unk_A0;
    u8 pad_A2[12];
    u8 unk_AE;
};

typedef struct UnkStruct_0229a63c_2 {
    u8 p[0x64];
    void *unk_64;
} UnkStruct_0229a63c_2;

extern UnkStruct_0229a63c_2 *data_020ccf94;
extern int func_020984e8(void);
extern int func_0209985c(int);
extern int func_ov121_0229abac(UnkStruct_0229a63c *self, int k);
extern u16 data_ov121_0229c2b8[];
extern int func_020435fc(void *a, int b);
extern void func_ov121_0229af7c(UnkStruct_0229a63c *self, int n, int z);
extern void func_0200467c(int cmd);
extern unsigned char *func_ov002_02208098(UnkStruct_0229a63c *self, unsigned char value);

void func_ov121_0229a63c(UnkStruct_0229a63c *self)
{
    int k;
    k = func_0209985c((int) func_020984e8());
    self->unk_A0 = (u16) (data_ov121_0229c2b8[k] + func_ov121_0229abac(self, self->unk_AE));
    self->unk_98 = func_020435fc(data_020ccf94->unk_64, self->unk_A0);
    if (self->unk_98 == -1) {
        func_ov121_0229af7c(self, 3, 0);
        func_0200467c(0x73);
    } else {
        func_ov002_02208098(self, 0x14);
    }
}
