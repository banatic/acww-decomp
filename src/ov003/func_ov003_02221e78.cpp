/* func_ov003_02221e78 @ 0x02221e78, 0x9c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

struct Vec {
    int x, y, z;
};
struct Pair {
    int x, y;
};
struct UnkStruct_02221e78 {
    char pad_00[0x18];
    int unk_18, unk_1C, unk_20;
    char pad_24[0x30 - 0x24];
    int unk_30, unk_34, unk_38, unk_3C, unk_40, unk_44;
    char pad_48[0x60 - 0x48];
    char unk_60[0xa0 - 0x60];
    unsigned char unk_A0;
};

extern "C" void func_0204f794(struct Vec *, int, int);
extern "C" int _s32_div_f(int, int);
extern "C" void func_020044c0(void *, int, int, int);

extern "C" void func_ov003_02221e78(struct UnkStruct_02221e78 *o, struct Pair *a, struct Vec *b, unsigned short d)
{
    struct Vec v;
    func_0204f794(&v, a->x, a->y);
    int dz = _s32_div_f(v.z - b->z, 8);
    int dx = _s32_div_f(v.x - b->x, 8);
    o->unk_30 = dx;
    o->unk_34 = 0x1000;
    o->unk_38 = dz;
    o->unk_18 = b->x;
    o->unk_1C = b->y;
    o->unk_20 = b->z;
    int ok = 0;
    o->unk_3C = 0;
    o->unk_40 = 0x1000;
    o->unk_44 = 0;
    o->unk_A0 = 0;
    volatile unsigned short t = 0xfff1;
    t = d;
    unsigned short lo = t;
    unsigned short hi = t;
    if (hi >= 0x1492 && lo <= 0x14fd) {
        ok = 1;
    }
    int id;
    if (ok) {
        id = 0x74;
    } else {
        id = 0x75;
    }
    func_020044c0(o->unk_60, id, 0x7f, 0);
}