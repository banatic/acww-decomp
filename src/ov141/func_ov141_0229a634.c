/* func_ov141_0229a634 @ 0x0229a634, 0x80 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229a634;
typedef struct UnkStruct_0229a634 UnkStruct_0229a634;

struct UnkStruct_0229a634 {
    u8 pad_00[0xa38];
    u8 obj;
    u8 pad_A39[0x83b];
    u32 unk_1274;
    u8 pad_1278[0x807];
    u8 unk_1A7F[13];
    u8 unk_1A8C;
};

extern int func_0208e484(u8 *p);
extern void func_ov141_0229a524(UnkStruct_0229a634 *self);
extern void func_ov141_0229a4e8(UnkStruct_0229a634 *self);
extern int func_ov141_02299f94(UnkStruct_0229a634 *self, int _x);
extern void RtcSendPxiCommand(u32 cmd);
extern void func_ov141_02299f6c(UnkStruct_0229a634 *self, int val);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov141_0229a358(UnkStruct_0229a634 *self);

void func_ov141_0229a634(UnkStruct_0229a634 *self)
{
    u8 b;

    if (func_0208e484(&self->obj) == 0) {
        return;
    }

    b = self->unk_1A8C;

    if (b == 7) {
        if (self->unk_1274 == 8) {
            func_ov141_0229a524(self);
            return;
        }
    } else if (b == 6) {
        func_ov141_0229a4e8(self);
        return;
    } else {
        if (self->unk_1A7F[b] != 0) {
            func_ov141_02299f94(self, b);
            RtcSendPxiCommand(0x29);
            func_ov141_02299f6c(self, 8);
            func_ov141_02299f6c(self, 0x10);
        }
    }

    func_ov002_02208098((void *) (self), 1);
    func_ov141_0229a358(self);
}