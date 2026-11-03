/* field_actor_states_9: 42 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200a3ac @ 0x0200a3ac, 0x9c bytes, Thumb
 * func_0200a3a8 @ 0x0200a3a8, 0x2 bytes, Thumb
 * func_0200a37c @ 0x0200a37c, 0x2c bytes, Thumb
 * func_0200a354 @ 0x0200a354, 0x28 bytes, Thumb
 * func_0200a338 @ 0x0200a338, 0x1a bytes, Thumb
 * func_0200a300 @ 0x0200a300, 0x36 bytes, Thumb
 * func_0200a2e4 @ 0x0200a2e4, 0x1c bytes, Thumb
 * func_0200a2e0 @ 0x0200a2e0, 0x2 bytes, Thumb
 * func_0200a2a8 @ 0x0200a2a8, 0x38 bytes, Thumb
 * func_0200a28c @ 0x0200a28c, 0x1a bytes, Thumb
 * func_0200a254 @ 0x0200a254, 0x36 bytes, Thumb
 * func_0200a24c @ 0x0200a24c, 0x6 bytes, Thumb
 * func_0200a22c @ 0x0200a22c, 0x20 bytes, Thumb
 * func_0200a220 @ 0x0200a220, 0xc bytes, Thumb
 * func_0200a0c8 @ 0x0200a0c8, 0x158 bytes, Thumb
 * func_0200a088 @ 0x0200a088, 0x40 bytes, Thumb
 * func_0200a02c @ 0x0200a02c, 0x5c bytes, Thumb
 * func_02009fe4 @ 0x02009fe4, 0x48 bytes, Thumb
 * func_02009fac @ 0x02009fac, 0x36 bytes, Thumb
 * func_02009f98 @ 0x02009f98, 0x14 bytes, Thumb
 * func_02009f94 @ 0x02009f94, 0x2 bytes, Thumb
 * func_02009f48 @ 0x02009f48, 0x4c bytes, Thumb
 * func_02009f2c @ 0x02009f2c, 0x1a bytes, Thumb
 * func_02009ef4 @ 0x02009ef4, 0x36 bytes, Thumb
 * func_02009ed8 @ 0x02009ed8, 0x1c bytes, Thumb
 * func_02009ed4 @ 0x02009ed4, 0x2 bytes, Thumb
 * func_02009ea4 @ 0x02009ea4, 0x30 bytes, Thumb
 * func_02009e88 @ 0x02009e88, 0x1a bytes, Thumb
 * func_02009e50 @ 0x02009e50, 0x36 bytes, Thumb
 * func_02009e28 @ 0x02009e28, 0x26 bytes, Thumb
 * func_02009e24 @ 0x02009e24, 0x2 bytes, Thumb
 * func_02009d90 @ 0x02009d90, 0x94 bytes, Thumb
 * func_02009d74 @ 0x02009d74, 0x1a bytes, Thumb
 * func_02009d38 @ 0x02009d38, 0x3c bytes, Thumb
 * func_02009d30 @ 0x02009d30, 0x8 bytes, Thumb
 * func_02009d20 @ 0x02009d20, 0x10 bytes, Thumb
 * func_02009c74 @ 0x02009c74, 0xac bytes, Thumb
 * func_02009c48 @ 0x02009c48, 0x2c bytes, Thumb
 * func_02009c08 @ 0x02009c08, 0x40 bytes, Thumb
 * func_02009ad4 @ 0x02009ad4, 0x134 bytes, Thumb
 * func_02009ab4 @ 0x02009ab4, 0x20 bytes, Thumb
 * func_02009a9c @ 0x02009a9c, 0x16 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x2d0];
    int unk_2D0;
} GameState;

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
} UnkStruct_0200a2a8;

typedef struct {
    unsigned long unk_00;
} UnkStruct_0200a24c;

typedef struct {
    char pad_00[0x7d4];
    char sub;
} UnkStruct_0200a22c;

typedef struct UnkStruct_0200a0c8 {
    u8 pad_00[0x5c];
    int x;
    int y;
    int z;
    u8 pad_68[0x8e - 0x68];
    s16 ang;
    u8 pad_90[0x7d4 - 0x90];
    int p7;
    u8 pad_7D8[0x800 - 0x7d8];
    int unk_800;
} UnkStruct_0200a0c8;

typedef struct Frame {
    s16 ang[4];
    int res;
    int pos[3];
    int target_pos[3];
    int dx;
    int pad_28;
    int dz;
} Frame;

typedef struct {
    char pad_00[0x98];
    int unk_98;
    char pad_9C[0x198];
    char unk_234[0xa0];
    int unk_2D4;
    char pad_2D8[0x8];
    int unk_2E0;
} UnkStruct_0200a088;

typedef struct UnkStruct_0200a02c {
    u8 pad_00[0x98];
    u32 unk_98;
    u8 pad_9C[0x7fc - 0x9c];
    u32 unk_7FC;
    u32 unk_800;
} UnkStruct_0200a02c;

struct UnkStruct_02009fe4 {
    char pad_00[0x800];
    int unk_800;
};

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
} UnkStruct_02009c74;

typedef struct {
    int unk_00;
    unsigned short unk_04;
    unsigned char unk_06;
} UnkStruct_02009c74_2;

typedef struct {
    int a;
    int b;
    int c;
    int d;
} UnkStruct_02009a9c;

typedef struct Triple_02009a9c {
    int a;
    int b;
    int c;
} Triple_02009a9c;

extern int func_02057d58(char *p, unsigned int a, unsigned char b, unsigned int c, char *d, unsigned int e);
extern int func_02056f28(void *a, int b);
extern int func_0200f328(void *a, int b);
extern void func_02010f5c(void *a);
extern int func_02056f94(void *p);
extern unsigned int func_0200e92c(void *ptr);
extern void func_0200e90c(void *ptr, int a, int b, int c);
extern int func_0200e91c(void *ptr);
extern void func_020109fc(int a, int b, int c, int d);
extern int func_02057d0c(int a, int b);
extern int func_02057d34(UnkStruct_0200a2a8 *);
extern int func_02008258(UnkStruct_0200a2a8 *, int);
extern int func_0200e894(int, void *);
extern void *data_020ccf94;
extern void *data_020d730c;
extern s16 FX_SinCosTable_[];
extern int func_02057c44(int *pos);
extern int func_02057c68(void *self);
extern int func_020113b0(int a, int b);
extern int func_020e8ed8(int dx, int dz);
extern int func_020e8b4c(int a, int b);
extern int func_0200e9a8(void *self, s16 *ang, int *tx, int *tz, s16 *out_ang);
extern void func_0201107c(void *self, void *ptr);
extern int func_020113e0(s16 *ang, s16 val);
extern void func_020110a0(void *self, s16 *ang);
extern int FX_MulFunc(int a, s16 b);
extern void func_02054860(void *);
extern void func_0200f95c(void *);
extern int func_02073908(int a, int b);
extern int func_0201100c(void *p);
extern int func_02010ff4(void *p);
extern void func_02010d64(void *p);
extern void func_020109a0(int, int, int, unsigned short);
extern int func_02057c20(int arg);
extern int func_02057bf0(int arg);
extern int func_02057cf4(void);
extern int func_0200c3b0(void *, int, int, int);
extern void func_02057bb8(unsigned short *);
extern void func_02057cb8(void *);
extern void func_020778b0(int destination, int value, ...);
extern int func_02077898(int arg0);
extern unsigned char data_020e54a8;
extern void func_020110c4(UnkStruct_02009c74 *p, void *self);
extern void *func_02011368(void *self);
extern void func_0209971c(void *o, unsigned short *p);
extern int func_020984fc(int);
extern int func_02099728(unsigned int);
extern void func_0200f1a4(int, int, unsigned short);
extern int func_02095694(int a, u32 b);
extern int func_0200c9a8(void *self, int a, int b, int c);
extern int func_0200faf0(void *self, int a);
extern void func_020108cc(void *self, int a, int b);
extern int func_0200f554(int arg);

int func_0200a300(void *arg0, int arg1, int arg2);
int func_02009fac(int a, int b, int c);
int func_02009ef4(int a, int b, int c);
int func_02009e50(int a, int b, int c);

void func_0200a3ac(char *a, char *b, int previous)
{
    char *p = b + 0xc;
    func_02057d58(a + 0x820, *(unsigned int *) (b + 0xc), *(unsigned char *) (p + 4), *(unsigned int *) (p + 8), a,
                  *(unsigned int *) (p + 0xc));
    func_020109a0((int) a, 0x28, 3, 0);
    func_02057d0c(1, (int) a);
    func_0200f328((void *) a, 0x4f);
    {
        unsigned short v = *(unsigned short *) (a + 0x820);
        if (v == 0x1373 || v == 0x1375 || v == 0x1377 || v == 0x1379 || v == 0x136a || v == 0x137b) {
            *(char *) (a + 0x8eb) = -1;
        } else {
            *(char *) (a + 0x8eb) = 0;
        }
    }
}

void func_0200a3a8(void *object, int event) {}

void func_0200a37c(void *self)
{
    if (func_02056f28((char *) self + 0x2d0, 8) != 0) {
        func_0200f328(self, 0x63);
    }
    func_02010f5c(self);
}

void func_0200a354(GameState *p)
{
    if (func_02056f94(&p->unk_2D0)) {
        func_0200a300((void *) p, 6, -1);
    }
}

void func_0200a338(int param)
{
    func_0200a37c((void *) param);
    func_02010d64((void *) param);
    func_0200a354((GameState *) param);
}

int func_0200a300(void *arg0, int arg1, int arg2)
{
    unsigned char local[0x20];
    int result;

    func_0200e92c(local);
    func_0200e90c(local, 0x31, arg1, arg2);
    result = func_0200e894((int) arg0, local);
    func_0200e91c(local);
    return result;
}

void func_0200a2e4(int arg, void *message, int previous)
{
    func_020109fc(arg, 0x29, 3, 0);
    func_02057d0c(2, arg);
}

void func_0200a2e0(void *object, int event) {}

int func_0200a2a8(UnkStruct_0200a2a8 *param)
{
    int ret;

    ret = func_02057d34(param);
    if (ret != 0) {
        return ret;
    }

    param->unk_7FC = func_02008258(param, param->unk_7F0);
    return func_0200c3b0((void *) param, 7, 5, -1);
}

void func_0200a28c(int arg)
{
    func_02010f5c((void *) arg);
    func_02010d64((void *) arg);
    func_0200a2a8((UnkStruct_0200a2a8 *) arg);
}

int func_0200a254(int arg0, int arg1, int arg2)
{
    char buf[0x20];
    int ret;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x32, arg1, arg2);
    ret = func_0200e894(arg0, buf);
    func_0200e91c(buf);
    return ret;
}

void func_0200a24c(UnkStruct_0200a24c *p)
{
    p->unk_00 = 0;
}

void func_0200a22c(UnkStruct_0200a22c *p, void *message, int previous)
{
    func_020109fc((int) p, 1, 3, 0);
    func_0200a24c((UnkStruct_0200a24c *) (&p->sub));
}

void func_0200a220(int a, int b)
{
    func_0200a254(a, 6, b);
}

void func_0200a0c8(UnkStruct_0200a0c8 *self)
{
    int *p7;
    Frame data;
    int *p;
    int angle;
    int res;

    p7 = &self->p7;
    p = (int *) ((char *) self + 0x5c);
    data.pos[0] = p[0];
    data.pos[1] = p[1];
    data.pos[2] = p[2];
    data.ang[2] = *(s16 *) ((char *) self + 0x8e);

    if (func_02073908((int) data_020ccf94, self->unk_800) != 0) {
        if (func_02057c44(data.target_pos) == 0) {
            return;
        }
        data.dx = data.target_pos[0] - self->x;
        data.dz = data.target_pos[2] - self->z;
        if (func_02057c68(self) != 0) {
            *p7 = 0;
        } else {
            *p7 = func_020113b0(*p7, 0x333);
        }
        data.ang[1] = (s16) func_020e8ed8(data.dx, data.dz);
    } else {
        if (func_0200e9a8(self, data.ang, &data.target_pos[0], &data.target_pos[2], &data.ang[1]) == 0) {
            func_0201107c(self, &data_020d730c);
            return;
        }
        if (data.target_pos[0] != self->x || data.target_pos[2] != self->z) {
            data.dx = data.target_pos[0] - self->x;
            data.dz = data.target_pos[2] - self->z;
            *p7 = func_020113b0(*p7, 0x333);
            angle = func_020e8ed8(data.dx, data.dz);
            if (func_020e8b4c(angle, data.ang[2]) >= 0x4000) {
                *p7 = 0;
            } else {
                data.ang[1] = (s16) angle;
            }
        } else {
            *p7 = 0;
        }
    }

    if (*p7 != 0) {
        func_020113e0(&data.ang[2], data.ang[1]);
        func_020110a0(self, &data.ang[2]);
    }

    res = FX_MulFunc(*p7, FX_SinCosTable_[((u16) (s16) (data.ang[2] - data.ang[1]) >> 4) * 2 + 1]);
    if (res < 0) {
        res = -res;
    }
    data.res = res;
    func_0201107c(self, &data.res);
}

void func_0200a088(UnkStruct_0200a088 *self)
{
    int temp;

    temp = FX_MulFunc(self->unk_98, 0x3ae1);
    if (temp <= self->unk_2D4) {
        self->unk_2E0 = temp;
    }
    func_02054860(self->unk_234);
    func_0200f95c(self);
}

void func_0200a02c(UnkStruct_0200a02c *self)
{
    if (func_02073908((int) data_020ccf94, self->unk_800) != 0) {
        if (self->unk_98 == 0) {
            func_02009fac((int) self, 6, -1);
        }
    } else {
        self->unk_7FC = 0;
        if (self->unk_98 == 0) {
            func_0200c3b0((void *) self, 3, 5, -1);
        }
    }
}

void func_02009fe4(struct UnkStruct_02009fe4 *param)
{
    func_0200a0c8((UnkStruct_0200a0c8 *) param);
    func_0200a088((UnkStruct_0200a088 *) param);
    if (func_02073908((*(int *) &data_020ccf94), param->unk_800) != 0) {
        func_0201100c(param);
    } else {
        func_02010ff4(param);
    }
    func_02010d64(param);
    func_0200a02c((UnkStruct_0200a02c *) param);
}

int func_02009fac(int a, int b, int c)
{
    char buf[32];
    int result;
    func_0200e92c(buf);
    func_0200e90c(buf, 0x33, b, c);
    result = func_0200e894(a, buf);
    func_0200e91c(buf);
    return result;
}

void func_02009f98(int arg0, void *message, int previous)
{
    func_020109a0(arg0, 42, 3, 0);
}

void func_02009f94(void *object, int event) {}

void func_02009f48(int param)
{
    if (func_02056f94((void *) (param + 0x2d0)) == 0) {
        return;
    }
    if (func_02057d34((UnkStruct_0200a2a8 *) param) == 0) {
        if (func_02057c20(param) != 1) {
            return;
        }
        func_02057d0c(3, param);
    }
    if (func_02057bf0(3) != 0) {
        return;
    }
    func_02009ef4(param, 6, -1);
}

void func_02009f2c(void *arg)
{
    func_02010f5c(arg);
    func_02010d64(arg);
    func_02009f48((int) arg);
}

int func_02009ef4(int a, int b, int c)
{
    char buf[32];
    int result;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x34, b, c);
    result = func_0200e894(a, buf);
    func_0200e91c(buf);
    return result;
}

void func_02009ed8(int x, void *message, int previous)
{
    func_020109a0(x, 0x2b, 3, 0);
    func_02057d0c(4, x);
}

void func_02009ed4(void *object, int event) {}

void func_02009ea4(char *p)
{
    int result;
    result = func_02056f94((void *) (p + 0x2d0));
    if (result != 0 && func_02057cf4() == 5) {
        func_02009e50((int) p, 6, -1);
    }
}

void func_02009e88(void *arg)
{
    func_02010f5c(arg);
    func_02010d64(arg);
    func_02009ea4((char *) arg);
}

int func_02009e50(int a, int b, int c)
{
    char buf[32];
    int result;
    func_0200e92c((void *) buf);
    func_0200e90c((void *) buf, 0x35, b, c);
    result = func_0200e894(a, (void *) buf);
    func_0200e91c((void *) buf);
    return result;
}

void func_02009e28(void *param, void *message, int previous)
{
    func_02057d0c((int) ((func_020109a0((int) param, 0x2c, 3, 0), (void *) func_02057cf4())), (int) param);
    func_0200f328(param, 0x4f);
}

void func_02009e24(void *object, int event) {}

void func_02009d90(void *p)
{
    if (func_02056f94((char *) p + 0x2d0) != 0) {
        *(int *) ((char *) p + 0x7fc) = func_02008258((UnkStruct_0200a2a8 *) p, *(int *) ((char *) p + 0x7f0));
        func_0200c3b0(p, 3, 5, -1);
        if (*(signed char *) ((char *) p + 0x8eb) >= 0) {
            unsigned short val;
            func_02057bb8(&val);
            switch (val) {
                case 0x1373:
                    *(signed char *) ((char *) p + 0x8eb) = 3;
                    break;
                case 0x1375:
                    *(signed char *) ((char *) p + 0x8eb) = 2;
                    break;
                case 0x1377:
                    *(signed char *) ((char *) p + 0x8eb) = 1;
                    break;
                default:
                    break;
            }
        }
        func_02057cb8(p);
    }
}

void func_02009d74(void *arg)
{
    func_02010f5c(arg);
    func_02010d64(arg);
    func_02009d90(arg);
}

int func_02009d38(int arg0, unsigned short arg1, int arg2, int arg3)
{
    unsigned char buf[0x1C];
    int result;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x3f, arg2, arg3);
    *(unsigned short *) (buf + 0xC) = arg1;
    result = func_0200e894(arg0, buf);
    func_0200e91c(buf);
    return result;
}

void func_02009d30(void *object, unsigned short value)
{
    func_020778b0((int) object, value);
}

void func_02009d20(int arg0, unsigned short *out)
{
    *out = (unsigned short) func_02077898(arg0);
}

void func_02009c74(void *self, char *a1, int a2)
{
    UnkStruct_02009c74 loc;
    void *o;
    unsigned int ok;
    UnkStruct_02009c74_2 *p;
    unsigned short *q;

    q = (unsigned short *) (a1 + 0xc);
    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok != 0) {
        func_020110c4(&loc, self);
        o = func_02011368(self);
        loc.unk_02 = 0xfff1;
        func_0209971c(o, &loc.unk_02);
        func_020109a0((int) self, 0x13, 5, 5);
        func_0209971c(o, &loc.unk_00);
    }
    p = (UnkStruct_02009c74_2 *) ((char *) self + 0x7d4);
    p->unk_00 = 0x1000;
    p->unk_04 = *q;
    if (a2 == 0x10) {
        p->unk_06 = 1;
    } else {
        p->unk_06 = 0;
    }
    if (p->unk_04 != 0xfff1) {
        func_0200f328(self, 0x31);
    } else {
        func_0200f328(self, 0x78);
    }
    func_02009d30((void *) ((char *) self + 0x8f0), *q);
}

void func_02009c48(void *param0, void *param1)
{
    unsigned short local;
    void *ptr;

    func_02009d20((int) ((char *) param0 + 0x8f0), (unsigned short *) (&local));
    func_02009d38((int) param0, local, 6, (int) param1);
}

void func_02009c08(int arg0)
{
    int val;
    int val2;
    unsigned short val3;

    val = (*(int *) &data_020ccf94);
    val2 = *(int *) (arg0 + 0x800);
    if (func_02073908(val, val2) != 0) {
        val = *(int *) (arg0 + 0x800);
        val2 = func_02099728((unsigned int) func_020984fc(val));
        if (val2 != 0) {
            val3 = *(unsigned short *) val2;
            func_0200f1a4(arg0, 3, val3);
        }
    }
}

void func_02009ad4(char *self)
{
    char *r6;
    u16 r4;
    int cond;
    int code;

    r6 = self + 0x7d4;
    r4 = *(u16 *) (r6 + 4);
    cond = ((*(volatile u8 *) &data_020e54a8) == 1) ? 1 : 0;

    if (cond != 0) {
        if (r4 >= 0x1369 && r4 <= 0x13a7) {
            func_02095694(r4 - 0x1368, *(u32 *) (self + 0x800));
        } else {
            func_02095694(0, *(u32 *) (self + 0x800));
        }

        *(int *) (self + 0x7fc) = func_02008258((UnkStruct_0200a2a8 *) self, *(u32 *) (self + 0x7f0));
        if (*(u8 *) (r6 + 6) != 0) {
            func_0200c3b0(self, 3, 5, -1);
        } else {
            func_0200c9a8(self, 3, 5, -1);
        }
    } else {
        func_0200faf0(self, 0x400);
        code = (*(u32 *) (self + 0x2d8) << 4) >> 16;

        switch (code) {
            case 8:
                func_02095694(0, *(u32 *) (self + 0x800));
                break;
            case 11:
                if (r4 >= 0x1369 && r4 <= 0x13a7) {
                    func_02095694(r4 - 0x1368, *(u32 *) (self + 0x800));
                }
                break;
            case 14:
                func_020108cc(self, 0, 6);
                break;
            default:
                break;
        }

        if (func_02056f94(self + 0x2d0) != 0) {
            *(int *) (self + 0x7fc) = func_02008258((UnkStruct_0200a2a8 *) self, *(u32 *) (self + 0x7f0));
            if (*(u8 *) (r6 + 6) != 0) {
                func_0200c3b0(self, 3, 5, -1);
            } else {
                func_0200c9a8(self, 3, 5, -1);
            }
        }
    }
}

void func_02009ab4(int arg)
{
    func_02010f5c((void *) arg);
    func_0200f554(arg);
    func_02010d64((void *) arg);
    func_02009ad4((char *) arg);
}

void func_02009a9c(UnkStruct_02009a9c *out, Triple_02009a9c v, int arg)
{
    out->a = v.a;
    out->b = v.b;
    out->c = v.c;
    out->d = arg;
}
