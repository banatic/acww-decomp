/* func_02092a4c @ 0x02092a4c, 0x180 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} UnkStruct_02092a4c;
typedef struct {
    unsigned char unk_00, unk_01, unk_02, unk_03;
} UnkStruct_02092a4c_2;

typedef struct {
    int unk_00, unk_04, unk_08;
    short unk_0C;
    short unk_0E;
    char pad_10[0x14 - 0x10];
    int unk_14;
    char pad_18[0x1c - 0x18];
} UnkStruct_02092a4c_5;

typedef struct {
    int unk_00, unk_04, unk_08, unk_0C;
} UnkStruct_02092a4c_3;
typedef struct {
    UnkStruct_02092a4c_3 *m;
} UnkStruct_02092a4c_4;

typedef struct {
    char pad_00[0x18];
    UnkStruct_02092a4c_4 *unk_18;
    char pad_1C[4];
    int unk_20, unk_24, unk_28;
    char pad_2C[0x3c - 0x2c];
    short unk_3C, unk_3E, unk_40;
    char pad_42[0x4c - 0x42];
    int unk_4C, unk_50, unk_54;
    char pad_58[0x69 - 0x58];
    unsigned char unk_69;
} UnkStruct_02092a4c_6;

typedef struct {
    char pad_00[4];
    UnkStruct_02092a4c_2 unk_04;
    char pad_08[0xc - 8];
    UnkStruct_02092a4c_6 *unk_0C;
} UnkStruct_02092a4c_7;

extern UnkStruct_02092a4c_5 data_021d52d8[];
extern UnkStruct_02092a4c data_020d1750;
extern void func_020ea6e0(UnkStruct_02092a4c *, int);
extern void func_020914dc(UnkStruct_02092a4c_5 *);

int func_02092a4c(UnkStruct_02092a4c_7 *self)
{
    UnkStruct_02092a4c_2 loc;
    struct {
        UnkStruct_02092a4c p;
        UnkStruct_02092a4c v;
    } w;
    UnkStruct_02092a4c_5 *e;
    UnkStruct_02092a4c *gp;
    UnkStruct_02092a4c_6 *o;
    int n;
    int ret;
    int t, ty, tz;
    unsigned char u;
    short a, b;

    loc = self->unk_04;
    e = &data_021d52d8[loc.unk_00];
    ret = 0;
    if (e->unk_14 != ~ret && e->unk_0E != 0) {
        w.p.x = e->unk_00;
        w.p.y = e->unk_04;
        w.p.z = e->unk_08;
        n = e->unk_0E;
        gp = &data_020d1750;
        w.v.x = gp->x;
        w.v.y = gp->y;
        w.v.z = gp->z;

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
            self->unk_0C->unk_54 = 0;
            self->unk_0C->unk_4C = 0x3d;
            self->unk_0C->unk_50 = 0x466;
        } else {
            u = 0;
            if (n < ~(int) u) {
                e->unk_0E = (short) (e->unk_0E + 1);
                t = e->unk_0E;
                if (t <= -0xa1) {
                    t = t + 0xb4;
                    u = (unsigned char) ((0xc00 * t) >> 12);
                    a = (short) ((short) (3 * t) + 0x3d);
                    b = (short) ((short) (0x38 * t) + 0x466);
                } else if (t <= -0x3d) {
                    u = 0xf;
                    a = 0x7b;
                    b = 0x8cd;
                } else {
                    t = -t;
                    u = (unsigned char) ((t << 10) >> 12);
                    a = (short) ((short) t + 0x3d);
                    b = (short) ((short) (0x13 * t) + 0x466);
                }
                self->unk_0C->unk_69 = u;
                self->unk_0C->unk_4C = a;
                self->unk_0C->unk_50 = b;
            } else {
                self->unk_0C->unk_69 = u;
                self->unk_0C->unk_4C = 0x3d;
                self->unk_0C->unk_50 = 0x466;
            }
        }
        ret = 1;
    }
    if (ret == 0) {
        func_020914dc(e);
    }
    return ret;
}
