/* func_ov003_0222228c @ 0x0222228c, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct Vec {
    int x, y, z;
};
struct UnkStruct_0222228c {
    char pad_00[8];
    unsigned short unk_08;
    char pad_0A[0x18 - 0xa];
    int unk_18, unk_1C, unk_20;
    char pad_24[0x30 - 0x24];
    int unk_30, unk_34, unk_38, unk_3C, unk_40, unk_44;
    short unk_48;
    char pad_4A[0x60 - 0x4a];
    char unk_60[0xa0 - 0x60];
    unsigned char unk_A0;
};

extern "C" void func_020044c0(void *, int, int, int);

extern "C" void func_ov003_0222228c(struct UnkStruct_0222228c *o, int unused, struct Vec *v, int flag)
{
    o->unk_30 = 0;
    o->unk_34 = 0x800;
    o->unk_38 = 0x300;
    o->unk_18 = v->x;
    o->unk_1C = v->y;
    o->unk_20 = v->z;
    o->unk_3C = 0x1000;
    o->unk_40 = 0x1000;
    o->unk_44 = 0x1000;
    if (o->unk_48 != 0) {
        o->unk_A0 = 0;
    }
    if (flag) {
        return;
    }
    volatile unsigned short t = 0xfff1;
    t = o->unk_08;
    int ok = 0;
    unsigned short lo = t;
    unsigned short hi = t;
    if (hi >= 0x1492 && lo <= 0x14fd) {
        ok = 1;
    }
    int id;
    if (ok) {
        id = 0x74;
    } else {
        id = 0x7d6;
    }
    func_020044c0(o->unk_60, id, 0x7f, 0);
}