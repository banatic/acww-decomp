/* func_02093f0c @ 0x02093f0c, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

struct Buf {
    u8 b[4];
};

struct UnkStruct_02093f0c {
    u32 unk_00;
    u32 v1;
    u32 v2;
};

struct In {
    u32 unk_00;
    u32 v1;
    u32 v2;
};

struct UnkStruct_02093f0c_3 {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
};

struct Entry {
    char pad_00[0x18];
    struct UnkStruct_02093f0c_3 **unk_18;
    char padx[4];
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    char pad1[0x10];
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
};

struct UnkStruct_02093f0c_4 {
    char pad_00[0x24];
    struct UnkStruct_02093f0c d;
    u32 flag;
    char pad1[0xc];
};

struct UnkStruct_02093f0c_2 {
    char pad_00[4];
    struct Buf unk_04;
    char pad1[4];
    struct Entry *unk_0C;
};

struct GTable {
    char b[0x1c];
};

extern u32 data_021d5658[3];
extern struct GTable data_021d52d8[];
extern void func_02090db0(struct Entry *p);
extern void func_02034270(struct UnkStruct_02093f0c_4 *out, struct In *in, int x, int y);
extern int func_020ea838(struct UnkStruct_02093f0c *d);
extern void MI_CpuCopy8(u32 *vals, struct GTable *t, int len);
extern void func_0203423c(struct UnkStruct_02093f0c_4 *out);

void func_02093f0c(struct UnkStruct_02093f0c_2 *a)
{
    struct Buf buf;
    struct UnkStruct_02093f0c_4 out;
    struct UnkStruct_02093f0c e;
    struct In in;
    struct Entry *p;
    u32 *gv = data_021d5658;

    buf = a->unk_04;
    p = a->unk_0C;
    p->unk_20 = gv[0] + (*p->unk_18)->unk_04;
    p->unk_24 = gv[1] + (*p->unk_18)->unk_08;
    p->unk_28 = gv[2] + (*p->unk_18)->unk_0C;
    func_02090db0(a->unk_0C);
    in.unk_00 = gv[0];
    in.v1 = gv[1];
    in.v2 = gv[2];
    func_02034270(&out, &in, 0, 0);
    if (out.flag != 0) {
        struct UnkStruct_02093f0c *od = &out.d;
        e.unk_00 = od->unk_00;
        e.v1 = od->v1;
        e.v2 = od->v2;
        if (func_020ea838(&e) != 0) {
            u32 v0;
            u32 v1;
            u32 v2;
            v1 = e.v1;
            v2 = e.v2;
            p = a->unk_0C;
            v0 = e.unk_00;
            p->unk_3C = v0;
            p->unk_3E = v1;
            p->unk_40 = v2;
        }
    }
    MI_CpuCopy8(gv, &data_021d52d8[buf.b[0]], 0x1c);
    func_0203423c(&out);
}