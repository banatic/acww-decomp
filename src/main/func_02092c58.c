/* func_02092c58 @ 0x02092c58, 0x1bc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
typedef struct {
    int x, y, z;
} UnkStruct_02092c58;
typedef struct {
    unsigned char unk_00, unk_01, unk_02, unk_03;
} UnkStruct_02092c58_2;

typedef struct {
    int unk_00, unk_04, unk_08;
    short unk_0C;
    short unk_0E;
    char pad_10[0x14 - 0x10];
    int unk_14;
    char pad_18[0x1c - 0x18];
} UnkStruct_02092c58_5;

typedef struct {
    int unk_00, unk_04, unk_08, unk_0C;
} UnkStruct_02092c58_3;
typedef struct {
    UnkStruct_02092c58_3 *m;
} UnkStruct_02092c58_4;

typedef struct {
    char pad_00[0x18];
    UnkStruct_02092c58_4 *unk_18;
    char pad_1C[4];
    int unk_20, unk_24, unk_28;
    char pad_2C[0x3c - 0x2c];
    short unk_3C, unk_3E, unk_40;
    char pad_42[0x4c - 0x42];
    int unk_4C, unk_50, unk_54;
    char pad_58[0x68 - 0x58];
    unsigned char unk_68;
} UnkStruct_02092c58_6;

typedef struct {
    char pad_00[4];
    UnkStruct_02092c58_2 unk_04;
    char pad_08[0xc - 8];
    UnkStruct_02092c58_6 *unk_0C;
} UnkStruct_02092c58_7;

extern UnkStruct_02092c58_5 data_021d52d8[];
extern UnkStruct_02092c58 data_020d1750;
extern void func_020ea6e0(UnkStruct_02092c58 *, int);
extern void func_020914dc(UnkStruct_02092c58_5 *);

int func_02092c58(UnkStruct_02092c58_7 *self, int p1, int p2, int p3, int b0, short s0, short s1, short s2, int b1, short t0,
                  short t1, short t2)
{
    UnkStruct_02092c58_2 loc;
    struct {
        UnkStruct_02092c58 v;
        UnkStruct_02092c58 p;
    } w;
    UnkStruct_02092c58_5 *e;
    UnkStruct_02092c58 *gp;
    UnkStruct_02092c58_6 *o;
    int ret;
    int n;
    int t, ty, tz;
    int q;
    unsigned char z;
    unsigned short u;
    short a, b;

    loc = self->unk_04;
    e = &data_021d52d8[loc.unk_00];
    w.v.x = data_020d1750.x;
    w.v.y = data_020d1750.y;
    w.v.z = data_020d1750.z;
    ret = 0;
    if (e->unk_14 != ~ret && e->unk_0E != 0) {
        w.p.x = e->unk_00;
        w.p.y = e->unk_04;
        w.p.z = e->unk_08;
        n = e->unk_0E;

        o = self->unk_0C;
        o->unk_20 = w.p.x + o->unk_18->m->unk_04;
        o->unk_24 = w.p.y + o->unk_18->m->unk_08;
        o->unk_28 = w.p.z + o->unk_18->m->unk_0C;

        func_020ea6e0(&w.v, e->unk_0C);
        ty = w.v.y;
        tz = w.v.z;
        o = self->unk_0C;
        o->unk_3C = (short) w.v.x;
        o->unk_3E = (short) ty;
        o->unk_40 = (short) tz;

        if (n > 0) {
            e->unk_0E = (short) (e->unk_0E - 1);
            self->unk_0C->unk_68 = 5;
            self->unk_0C->unk_4C = b0;
            self->unk_0C->unk_50 = b1;
        } else {
            z = 0;
            if (n < ~(int) z) {
                e->unk_0E = (short) (e->unk_0E + 1);
                t = e->unk_0E;
                if (t <= -0xa1) {
                    // B1
                    q = p1 + 1;
                    p2 = (-0xa1 - t) * p2;
                    u = (unsigned short) (q + (p2 >> 12));
                    // B1END
                    t = t + 0xb4;
                    a = (short) (b0 + (short) (s1 * t));
                    b = (short) (b1 + (short) (t1 * t));
                } else if (t <= -0x3d) {
                    u = (unsigned short) p1;
                    a = s0;
                    b = t0;
                } else {
                    // B3
                    q = p1 + 1;
                    p3 = (t + 0x3c) * p3;
                    u = (unsigned short) (q + (p3 >> 12));
                    // B3END
                    t = -t;
                    a = (short) (b0 + (short) (s2 * t));
                    b = (short) (b1 + (short) (t2 * t));
                }
                self->unk_0C->unk_68 = (unsigned char) u;
                self->unk_0C->unk_4C = a;
                self->unk_0C->unk_50 = b;
            } else {
                self->unk_0C->unk_68 = 5;
                self->unk_0C->unk_4C = b0;
                self->unk_0C->unk_50 = b1;
            }
        }
        ret = 1;
    }
    if (ret == 0) {
        func_020914dc(e);
    }
    return ret;
}
