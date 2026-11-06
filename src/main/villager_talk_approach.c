/* villager_talk_approach: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202b8dc @ 0x0202b8dc, 0x70 bytes, Thumb
 * func_0202b800 @ 0x0202b800, 0xdc bytes, Thumb
 * func_0202b770 @ 0x0202b770, 0x90 bytes, Thumb
 * func_0202b6c8 @ 0x0202b6c8, 0xa8 bytes, Thumb
 * func_0202b61c @ 0x0202b61c, 0xac bytes, Thumb
 * func_0202b598 @ 0x0202b598, 0x84 bytes, Thumb
 * func_0202b52c @ 0x0202b52c, 0x6c bytes, Thumb
 * func_0202b510 @ 0x0202b510, 0x1c bytes, Thumb
 * func_0202b420 @ 0x0202b420, 0xf0 bytes, Thumb
 * func_0202b354 @ 0x0202b354, 0xcc bytes, Thumb
 * func_0202b220 @ 0x0202b220, 0x134 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0202b8dc UnkStruct_0202b8dc;

struct UnkStruct_0202b8dc {
    unsigned char pad_00[0x824];
    unsigned char unk_824;
    unsigned char pad_825[0x830 - 0x824 - 1];
    int unk_830;
};

typedef struct UnkStruct_0202b8dc_2 UnkStruct_0202b8dc_2;

struct UnkStruct_0202b8dc_2 {
    char pad_00[0x100];
    UnkStruct_0202b8dc *sub;
};

typedef struct GlobalData {
    int unk_00;
    unsigned char unk_04;
} GlobalData;

typedef struct UnkStruct_0202b800 {
    unsigned char pad_00[0x830];
    int unk_830;
} UnkStruct_0202b800;

typedef struct UnkStruct_0202b800_2 {
    unsigned char pad_00[0x100];
    UnkStruct_0202b800 *unk_100;
    char unk_104[0x1e];
    u8 unk_122;
    unsigned char pad_123[0x12c - 0x123];
    int unk_12C;
    unsigned char pad_130[0x19c - 0x130];
    u16 unk_19C;
} UnkStruct_0202b800_2;

typedef struct Global {
    int unk_00;
    u8 unk_04;
} Global;

typedef struct {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0202b770_3;

typedef struct {
    char pad_00[0x100];
    UnkStruct_0202b770_3 *unk_100;
    char unk_104[0x1e];
    char unk_122[0x0a];
    int unk_12C;
} UnkStruct_0202b770;

typedef struct {
    int word;
    unsigned char byte;
} UnkStruct_0202b770_2;

struct UnkStruct_0202b61c {
    u8 pad_00[0x100];
    void *unk_100;
    u8 unk_104[0x1e];
    u8 unk_122[0x7a];
    u16 unk_19C;
    u8 unk_19E;
};

struct UnkStruct_0202b61c_2 {
    u8 pad_00[0x830];
    void *unk_830;
};

typedef struct UnkStruct_0202b598 UnkStruct_0202b598;

struct UnkStruct_0202b598 {
    u8 pad_00[0x100];
    void *unk_100;
    u8 pad_104[0x19c - 0x104];
    u16 unk_19C;
    u8 unk_19E;
};

typedef struct UnkStruct_0202b354_2 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0202b354_2;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_0202b354_3 {
    char pad_00[0x100];
    UnkStruct_0202b354_2 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
    char pad_123[1];
    unsigned short unk_124;
    char pad_126[0x19c - 0x126];
    unsigned short unk_19C;
    unsigned char unk_19E;
} UnkStruct_0202b354_3;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
    unsigned short unk_06;
} UnkStruct_0202b354;

typedef struct {
    unsigned char pad_00[0x100];
    void *unk_100;
    char unk_104[0x122 - 0x104];
    char unk_122[0x19c - 0x122];
    unsigned short unk_19C;
    unsigned char unk_19E;
    unsigned char pad_19F;
    int unk_1A0;
} UnkStruct_0202b220;

typedef struct {
    unsigned short a;
    unsigned short b;
} UnkStruct_0202b220_2;

extern GlobalData data_020c8b18;
extern unsigned int func_0208150c(int arg);
extern int func_020036e8(unsigned char *);
extern void func_0202da88(UnkStruct_0202b8dc_2 *this, char *p);
extern char data_021c2704[];
extern Global data_020c8b38;
extern int func_020819f0(int);
extern int func_02081d20(int);
extern void func_02081a04(int);
extern int func_02099fe8(void);
extern int func_02003704(int);
extern int func_02003648(int);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern void func_0209df64(void *p);
extern int func_0207a650(void *a, void *b);
extern UnkStruct_0202b770_2 data_020c8b20;
extern char data_021e5a2c;
extern char data_021c2794;
extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_02080404(unsigned int, unsigned int *, int, int);
extern int func_02021d60(int a, int b);
extern int func_02021ea8(void *self, int *arr, int count, void *predicate);
extern struct {
    unsigned int w;
    unsigned char b;
} data_020c89c8;
extern void func_0207de14(void *dst, void *src);
extern struct {
    u32 w;
    u8 b;
} data_020c89e8;
extern struct {
    u32 a;
    u8 b;
} data_020c8ca8;
extern int func_0209c310(unsigned int);
extern int func_02099f7c(void *, void *);
extern int func_020644cc(unsigned char);
extern unsigned short func_0209a034(int);
extern void *data_020c8f38[];
extern unsigned int func_0207f1c8(void *);
extern void *func_0209b5ec(void *);
extern unsigned int func_0209c330(unsigned char *);
extern int func_020644b4(int);
extern int func_0204c878(unsigned char *);
extern int func_0205be38(void);
extern int func_02099734(int);
extern int func_02098cf8(int, int);
extern struct {
    unsigned int field0;
    unsigned char field4;
} data_020c89a0;
extern void func_02015fb0(unsigned char *, int, int, int, int, int);
extern Cfg data_020c8a30;
extern void func_0202d694(unsigned short *p);
extern unsigned char data_020c8be8[];

int func_0202b8dc(UnkStruct_0202b8dc_2 *this)
{
    UnkStruct_0202b8dc *sub;
    int ret0;
    int local1;
    int local2;
    int local3;
    int local4;
    GlobalData *g;

    sub = this->sub;
    ret0 = func_020036e8((unsigned char *) func_0208150c(sub->unk_830));
    g = &data_020c8b18;
    local1 = g->unk_00;
    local2 = 9;
    local3 = sub->unk_824 & 1;
    local4 = g->unk_04;

    func_0202da38((void *) this, (void *) ((char *) this + 0x104), (void *) ((char *) this + 0x122), 0x1e, ret0, local1,
                  local2, local3, local4);
    func_0202da88(this, data_021c2704);
    return 1;
}

int func_0202b800(UnkStruct_0202b800_2 *self)
{
    int status;
    unsigned int v;

    status = 0;
    if (self->unk_12C == 0) {
        goto out;
    }

    v = 0;
    if (func_020819f0(self->unk_12C) == 0) {
        if (func_02081d20(self->unk_12C) >= 0x50) {
            if (func_02099fe8() != -1) {
                func_02081a04(self->unk_12C);
                status = 1;
            } else {
                status = 2;
            }
        } else {
            status = 3;
        }
    }

    func_0202da38(self, self->unk_104, &self->unk_122, 0x1e,
                  func_020036e8((unsigned char *) ((int) func_0208150c(self->unk_100->unk_830))), data_020c8b38.unk_00,
                  data_020c8b38.unk_04, status, 0);

    if (func_02003704((int) func_0208150c(self->unk_100->unk_830)) != 0) {
        v = func_02003648((int) func_0208150c(self->unk_100->unk_830));
    }

    self->unk_19C = (u16) (v < 0x9c ? 0x47d8 + v * 4 : 0x47d8);
    return 1;
out:
    return status;
}

int func_0202b770(UnkStruct_0202b770 *p)
{
    int local;
    signed char *object;
    func_0209df64(&local);
    if ((object = (signed char *) p->unk_12C) == 0) {
        goto fail;
    }
    if (func_02081d20((int) object) < 0) {
        goto fail;
    }
    if (func_0207a650(&data_021e5a2c, &local) == 0) {
        goto fail;
    }
    func_0202da38(p, p->unk_104, p->unk_122, 30, func_020036e8((unsigned char *) func_0208150c(p->unk_100->unk_830)),
                  data_020c8b20.word, data_020c8b20.byte, 0, 0);
    func_0202da88((UnkStruct_0202b8dc_2 *) p, (char *) (&data_021c2794));
    return 1;
fail:
    return 0;
}

int func_0202b6c8(void *self)
{
    unsigned int val;
    unsigned int arr[8];
    int flag;
    int i;
    int res;
    int t;

    val = *(unsigned int *) ((char *) *(void **) ((char *) self + 0x100) + 0x830);
    flag = 0;
    for (i = flag; i < 8; i++) {
        arr[i] = 0;
    }

    res = func_02080404(val, arr, func_02099870((int) func_020984e8()), 2);
    if (res > 0) {
        *(unsigned int *) ((char *) self + 0x138) =
            func_02021ea8((void *) (val), (int *) (arr), (int) (res), (((void *) func_02021d60)));
    }

    if (*(unsigned int *) ((char *) self + 0x138) == 0) {
        flag = 1;
    }

    t = func_020036e8(
        (unsigned char *) func_0208150c(*(unsigned int *) ((char *) *(void **) ((char *) self + 0x100) + 0x830)));
    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 30, t, data_020c89c8.w, data_020c89c8.b, flag, 0);

    return 1;
}

int func_0202b61c(struct UnkStruct_0202b61c *self)
{
    u16 temp[2];
    void *field;

    if (func_02099fe8() != -1) {
        field = ((struct UnkStruct_0202b61c_2 *) self->unk_100)->unk_830;

        func_0207de14(temp, field);
        self->unk_19C = temp[0];

        if (self->unk_19C != 0xfff1) {
            self->unk_19E = 1;
        } else {
            func_0202d694((unsigned short *) (&temp[1]));
            self->unk_19C = temp[1];
            self->unk_19E = 0;
        }

        func_0202da38(self, self->unk_104, self->unk_122, 0x1e,
                      (u32) func_020036e8((unsigned char *) func_0208150c((int) field)), data_020c89e8.w, data_020c89e8.b, 0,
                      0);
        return 1;
    }
    return 0;
}

int func_0202b598(UnkStruct_0202b598 *self)
{
    u16 local;
    u16 val;

    if (func_02099fe8() == -1) {
        goto fail;
    }

    func_0202d694((unsigned short *) (&local));
    val = local;
    self->unk_19C = val;
    self->unk_19E = 0;

    func_0202da38((void *) self, (void *) ((char *) self + 0x104), (void *) ((char *) self + 0x122), 0x1e,
                  (u32) func_020036e8((unsigned char *) func_0208150c(*(u32 *) ((char *) self->unk_100 + 0x830))),
                  data_020c8ca8.a, data_020c8ca8.b, 0, 0);

    return 1;

fail:
    return 0;
}

void func_0202b52c(unsigned short *out, unsigned int p1)
{
    struct {
        unsigned short mask;
        unsigned char flag;
    } local;
    int count;
    unsigned short mask;
    int i;

    *out = 0xFFF1;
    if (func_0209c310(p1) != 0) {
        return;
    }
    if (p1 >= 5) {
        return;
    }
    if (func_02099f7c(&local, data_020c8f38[p1]) > 0) {
        count = func_020644cc(local.flag);
        mask = local.mask;
        for (i = 0; i < 15; i++) {
            if ((mask >> i) & 1) {
                if (count == 0) {
                    *out = func_0209a034(i);
                    return;
                } else {
                    count--;
                }
            }
        }
    }
}

int func_0202b510(int n)
{
    int result = ((n + 5) / 10) * 10;
    if (result < 10) {
        result = 10;
    }
    return result;
}

int func_0202b420(unsigned char *param0)
{
    void *structPtr;
    void *r6;
    unsigned short local;
    int r4;
    int r0;
    int r1;

    structPtr = *(void **) (param0 + 0x100);
    r6 = *(void **) ((unsigned char *) structPtr + 0x830);

    func_0202b52c(&local, func_0209c330((unsigned char *) func_0209b5ec((void *) func_0207f1c8(r6))));

    *(unsigned short *) (param0 + 0x124) = local;
    if (*(unsigned short *) (param0 + 0x124) == 0xfff1) {
        goto FAIL;
    }

    r4 = func_020644b4(0xccd) + 0xccd;
    r0 = func_0204c878(param0 + 0x124);
    r4 = r0 * r4;
    r0 = func_0205be38();
    r1 = (r4 >> 14) + 3 * r0;
    *(int *) (param0 + 0x1a0) = r1;
    r0 = *(int *) (param0 + 0x1a0);
    r0 = func_0202b510(r0);
    *(int *) (param0 + 0x1a0) = r0;

    r0 = func_02098cf8(func_02099734((int) func_020984e8()), 1);
    if (*(int *) (param0 + 0x1a0) > r0) {
        goto FAIL;
    }

    r0 = (unsigned int) func_020036e8((unsigned char *) (int) func_0208150c((int) r6));

    func_0202da38((void *) param0, (void *) (param0 + 0x104), (void *) (param0 + 0x122), 0x1e, r0, data_020c89a0.field0,
                  data_020c89a0.field4, 0, 0);

    func_02015fb0(param0, *(int *) (param0 + 0x1a0), 1, 0xa, 0, 0);

    return 1;

FAIL:
    return 0;
}

int func_0202b354(UnkStruct_0202b354_3 *self)
{
    // DECLS
    UnkStruct_0202b354 tmp;
    int inner;
    // ENDDECLS

    inner = self->unk_100->unk_830;
    func_0202b52c(
        (unsigned short *) (&tmp),
        (int) func_0209c330((unsigned char *) (((int) func_0209b5ec((void *) (int) func_0207f1c8((void *) inner))))));
    self->unk_124 = tmp.unk_00;
    if (self->unk_124 == 0xfff1) {
        goto fail;
    }
    func_0207de14((void *) (&tmp.unk_02), (void *) inner);
    self->unk_19C = tmp.unk_02;
    if (self->unk_19C != 0xfff1) {
        self->unk_19E = 1;
    } else {
        func_0202d694(&tmp.unk_04);
        self->unk_19C = tmp.unk_04;
        self->unk_19E = 0;
    }
    func_0202da38((void *) self, (void *) self->unk_104, (void *) (&self->unk_122), 0x1e,
                  func_020036e8((unsigned char *) ((int) func_0208150c(inner))), data_020c8a30.unk_00, data_020c8a30.unk_04, 0,
                  0);
    return 1;
fail:
    return 0;
}

int func_0202b220(UnkStruct_0202b220 *p)
{
    UnkStruct_0202b220_2 local;
    int r5, limit, v, arg5, arg6, arg8;
    unsigned char arg7;
    void *r6;

    r6 = *(void **) ((char *) p->unk_100 + 0x830);
    func_0209c330((unsigned char *) func_0209b5ec((void *) func_0207f1c8(r6)));
    if (func_02099fe8() == -1) {
        goto fail;
    }

    func_0207de14(&local, r6);
    p->unk_19C = local.a;
    if (p->unk_19C != 0xfff1) {
        p->unk_19E = 1;
    } else {
        func_0202d694(&local.b);
        p->unk_19C = local.b;
        p->unk_19E = 0;
    }

    if (p->unk_19C == 0xfff1) {
        goto fail;
    }

    r5 = func_020644b4(0xccd) + 0xccd;
    r5 = (r5 * func_0204c878((unsigned char *) (&p->unk_19C))) >> 12;
    limit = 3 * func_0205be38();
    v = r5 - (r5 > limit ? limit : 0);
    p->unk_1A0 = func_0202b510(v);

    if (p->unk_1A0 > 0xbb8) {
        p->unk_1A0 = 0xbb8;
    }

    if (p->unk_1A0 > func_02098cf8(func_02099734((int) func_020984e8()), 1)) {
        goto fail;
    }

    arg5 = func_020036e8((unsigned char *) func_0208150c((int) r6));
    arg6 = *(int *) data_020c8be8;
    arg7 = data_020c8be8[4];
    func_0202da38(p, p->unk_104, p->unk_122, 30, arg5, arg6, arg7, 0, 0);
    func_02015fb0((unsigned char *) p, p->unk_1A0, 2, 0xa, 0, 0);
    return 1;

fail:
    return 0;
}
