/* func_ov003_02219d8c @ 0x02219d8c, 0x88 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern int func_ov003_02219e14(void *, void *);

typedef struct {
    int x, y, z;
} Vec;
struct S7d4 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};
struct UnkStruct_02219d8c_2 {
    char pad_00[0x2d8];
    int unk_2D8;
    char pad_2DC[0x704 - 0x2dc];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    struct S7d4 unk_7D4;
    char pad_7E4[0x7f0 - 0x7e4];
    int unk_7F0;
};
struct UnkStruct_02219d8c {
    Vec v;
    Vec v2;
};

int func_ov003_02219d8c(void *p0, int slot)
{
    struct UnkStruct_02219d8c t;
    unsigned int h;
    int n;
    struct S7d4 *p;
    struct UnkStruct_02219d8c_2 *o = (struct UnkStruct_02219d8c_2 *) func_02096718(slot);
    if (o != 0) {
        h = (unsigned int) (o->unk_2D8 << 4) >> 16;
        n = 0;
        t.v.x = 0;
        t.v.y = 0;
        t.v.z = 0;
        if (o->unk_7F0 == 0x5e) {
            p = &o->unk_7D4;
            t.v.x = p->unk_04;
            t.v.y = p->unk_08;
            t.v.z = p->unk_0C;
            if (o->unk_704 == 0x4e) {
                n = 0x16 - h;
            } else if (o->unk_704 == 0x4b) {
                n = 9 - h;
            }
        }
        if (n > 0) {
            t.v2.x = t.v.x;
            t.v2.y = t.v.y;
            t.v2.z = t.v.z;
            if (func_ov003_02219e14(p0, &t.v2) != 0) {
                return n;
            }
        }
    }
    return 0;
}
