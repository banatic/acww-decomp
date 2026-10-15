/* func_02093e3c @ 0x02093e3c, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char b[4];
} UnkStruct_02093e3c;
typedef struct {
    int x, y, z;
} UnkStruct_02093e3c_2;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char pad_0C[2];
    short unk_0E;
    unsigned char pad_10[4];
    int unk_14;
    unsigned char pad_18[4];
} UnkStruct_02093e3c_4;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_02093e3c_5;

typedef struct {
    unsigned char pad_00[0x18];
    UnkStruct_02093e3c_5 **unk_18;
    int pad_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    unsigned char pad_2C[0x3c - 0x2c];
    short unk_3C;
    short unk_3E;
    short unk_40;
} UnkStruct_02093e3c_6;

typedef struct {
    unsigned char pad_00[4];
    UnkStruct_02093e3c key;
    unsigned char pad_08[4];
    UnkStruct_02093e3c_6 *unk_0C;
} UnkStruct_02093e3c_3;

typedef struct {
    unsigned char pad_00[0x24];
    UnkStruct_02093e3c_2 unk_24;
    int unk_30;
    unsigned char pad_34[0x40 - 0x34];
} Big;

extern UnkStruct_02093e3c_4 data_021d52d8[];
extern void func_020914dc(UnkStruct_02093e3c_4 *e);
extern int func_02034270(Big *b, UnkStruct_02093e3c_2 *v, int c, int d);
extern void func_0203423c(Big *b);
extern int func_020ea838(UnkStruct_02093e3c_2 *v);

int func_02093e3c(UnkStruct_02093e3c_3 *p)
{
    UnkStruct_02093e3c key;
    Big big;
    UnkStruct_02093e3c_2 a;
    UnkStruct_02093e3c_2 b;
    int v;
    int ret;
    UnkStruct_02093e3c_4 *e;
    UnkStruct_02093e3c_6 *o;

    key = p->key;
    e = &data_021d52d8[key.b[0]];
    ret = 0;
    if (e->unk_14 != -1 && e->unk_0E != 0) {
        o = p->unk_0C;
        o->unk_20 = e->unk_00 + (*o->unk_18)->unk_04;
        o->unk_24 = e->unk_04 + (*o->unk_18)->unk_08;
        o->unk_28 = e->unk_08 + (*o->unk_18)->unk_0C;
        b.x = e->unk_00;
        b.y = e->unk_04;
        b.z = e->unk_08;
        func_02034270(&big, &b, 0, 0);
        if (big.unk_30 != 0) {
            UnkStruct_02093e3c_2 *q = &big.unk_24;
            a.x = q->x;
            a.y = q->y;
            a.z = q->z;
            if (func_020ea838(&a) != 0) {
                int vy = a.y;
                int vz = a.z;
                UnkStruct_02093e3c_6 *o2 = p->unk_0C;
                o2->unk_3C = (short) a.x;
                o2->unk_3E = (short) vy;
                o2->unk_40 = (short) vz;
            }
        }
        v = e->unk_0E;
        if (v > 0) {
            e->unk_0E = v - 1;
        }
        ret = 1;
        func_0203423c(&big);
    }
    if (ret == 0) {
        func_020914dc(e);
    }
    return ret;
}
