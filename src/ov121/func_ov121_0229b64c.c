/* func_ov121_0229b64c @ 0x0229b64c, 0xa4 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229b64c {
    u8 pad_00[0xAF];
    u8 unk_AF;
};

extern u8 data_021fbdd8;

extern void func_ov121_02299a3c(struct UnkStruct_0229b64c *self, unsigned short mask);
extern int func_0206f56c(void);
extern void func_ov121_0229aec4(struct UnkStruct_0229b64c *self, int val);
extern int func_ov121_0229ac00(struct UnkStruct_0229b64c *self);
extern int func_ov121_0229add4(struct UnkStruct_0229b64c *self);
extern void func_ov121_02299a4c(struct UnkStruct_0229b64c *self, int val);
extern unsigned char *func_ov002_02208098(struct UnkStruct_0229b64c *self, unsigned char value);

void func_ov121_0229b64c(struct UnkStruct_0229b64c *self)
{
    func_ov121_02299a3c(self, 8);
    if (func_0206f56c() != 0) {
        func_ov121_02299a3c(self, 4);
        func_ov121_0229aec4(self, 0x18);
        func_ov002_02208098(self, 0);
    } else {
        if (data_021fbdd8 == 0) {
            func_ov121_02299a3c(self, 4);
            func_ov121_0229aec4(self, 0x18);
            if (func_ov121_0229ac00(self) == 0) {
                func_ov002_02208098(self, 0);
            }
        } else {
            self->unk_AF = (unsigned char) func_ov121_0229add4(self);
            if (self->unk_AF >= 9 && self->unk_AF <= 15) {
                func_ov121_0229aec4(self, self->unk_AF);
                func_ov121_02299a4c(self, 8);
            } else {
                if (self->unk_AF <= 7 || self->unk_AF == 8) {
                    func_ov121_02299a4c(self, 8);
                }
                func_ov121_0229aec4(self, 0x18);
            }
        }
    }
}
