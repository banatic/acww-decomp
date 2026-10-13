/* func_020411fc @ 0x020411fc, 0x96 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 b[16];        // 0x00-0x0f
    u8 unk_10;       // 0x10
    u8 unk_11;       // 0x11
    u8 pad_12[0x22]; // 0x12-0x33
    u32 unk_34;      // 0x34
    u32 unk_38;      // 0x38
} UnkStruct_020411fc;

typedef struct {
    u8 v[4];
} Blk;

extern void func_0209df64(u8 *dst);
extern int func_020644cc(int arg);
extern void func_0204101c(UnkStruct_020411fc *p);
extern void func_02040c90(UnkStruct_020411fc *p, int arg);

void func_020411fc(UnkStruct_020411fc *out)
{
    u8 buf[16];

    func_0209df64(buf);

    *(Blk *) (buf + 4) = *(Blk *) buf;

    out->b[0] = buf[4];
    out->b[1] = buf[5];
    out->b[2] = buf[6];
    out->b[3] = buf[7];

    *(Blk *) (buf + 8) = *(Blk *) buf;

    out->b[4] = buf[8];
    out->b[5] = buf[9];
    out->b[6] = buf[10];
    out->b[7] = buf[11];

    out->b[8] = 1;
    out->b[9] = 1;
    out->b[10] = 0;
    out->b[11] = 0;
    out->b[12] = 1;
    out->b[13] = 1;
    out->b[14] = 0;
    out->b[15] = 0;

    out->unk_10 = (u8) (func_020644cc(5) + 1);
    out->unk_11 = 0x63;

    out->unk_34 = 0;
    out->unk_38 = 0;

    func_0204101c(out);
    func_02040c90(out, 1);
}
