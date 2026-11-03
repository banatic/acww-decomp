/* town_ground_4: 8 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221fe10 @ 0x0221fe10, 0x1c bytes, Thumb
 * func_ov003_0221fdc8 @ 0x0221fdc8, 0x48 bytes, Thumb
 * func_ov003_0221fdb8 @ 0x0221fdb8, 0x10 bytes, Thumb
 * func_ov003_0221fd60 @ 0x0221fd60, 0x58 bytes, Thumb
 * func_ov003_0221fd04 @ 0x0221fd04, 0x5c bytes, Thumb
 * func_ov003_0221fca4 @ 0x0221fca4, 0x60 bytes, Thumb
 * func_ov003_0221faac @ 0x0221faac, 0x1f8 bytes, Thumb
 * func_ov003_0221fa28 @ 0x0221fa28, 0x84 bytes, Thumb
 */

typedef struct {
    char pad[1];
    unsigned char unk_01;
} UnkStruct_0221fdc8;

typedef struct {
    char pad[0xe8];
    signed char unk_E8;
} UnkStruct_0221fdc8_2;

typedef struct {
    char pad[0x2c];
    UnkStruct_0221fdc8_2 *unk_2C;
} UnkStruct_0221fdc8_3;

typedef struct {
    char pad[0x28];
    int unk_28;
} Bb;

typedef struct {
    UnkStruct_0221fdc8 *unk_00;
    UnkStruct_0221fdc8_3 *unk_04;
    char pad[0xa8];
    Bb *unk_B0;
} UnkStruct_0221fdc8_4;

typedef struct {
    char pad_00[0x1c];
    void (*callback)(void *);
    char pad_20[0x70];
    unsigned char unk_90;
} UnkStruct_0221fdb8;

struct UnkStruct_0221fd04 {
    void *head;
};

struct UnkStruct_0221fca4 {
    void *unk_00;
};

typedef struct UnkStruct_0221faac {
    char *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_0221faac;

extern int func_020edf70(int);
extern int FX_Div(int, int);
extern void func_02030b80(int);
extern int data_ov003_0223cad4;
extern void *func_020ee660(void *obj);
extern void *func_ov003_0221f618(void *obj);
extern int func_ov003_0221f204(void *obj);
extern void *func_020576cc(void *obj);
extern void func_ov003_0221ef7c(void *obj);
extern unsigned char data_020da13c[];
extern unsigned char data_ov003_02239a58[];
extern void func_ov003_0221ef78(void *);
extern void *func_02057694(void *);
extern int func_ov003_0221f1f4(void *);
extern void *func_ov003_0221f5f4(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern UnkStruct_0221faac *data_021c80bc;
extern void *data_021c9b24;
extern char data_ov003_02239aac[];
extern char data_ov003_02239ab8[];
extern char data_ov003_02239ac4[];
extern char data_ov003_02239acc[];
extern void func_ov003_0221f1ec(void *p);
extern int func_ov003_0221f1ac(void *p);
extern void *func_0203750c(void);
extern int func_02037594(void *h);
extern int func_02037564(void *h);
extern int func_02037570(void *h);
extern int func_0203754c(void *h);
extern int func_02037558(void *h);
extern int func_020575e4(void *p, int a, void *b, void *c, int d, int e, int f);
extern void *func_020e9948(void *heap, int size);
extern char *func_ov003_0221f3b0(char *p);
extern void func_0204f800(int *a, int *b, int x, int z, int i, int j);
extern int func_02031478(int a, int b);
extern void func_0204f7ac(int *v, int x, int z, int i, int j);
extern int func_ov003_0221f47c(void *p, int *v, int idx);
extern int func_ov003_0221f270(char *p, char *e, int x, int y);
extern void func_ov003_0221ef70(void *p);
extern int func_ov003_0221f144(void *);
extern int func_ov003_0221f444(void *);
extern int func_ov003_0221f244(void *);
extern int func_02057538(void *);
extern void func_ov003_0221f6dc(void *);
extern int data_021d3124;

void *func_ov003_0221fd60(void *self);

void func_ov003_0221fe10(void)
{
    void *condition_value_17;
    condition_value_17 = (void *) (func_020edf70(0x31c));
    if (condition_value_17 != 0) {
        func_ov003_0221fd60(condition_value_17);
    }
}

void func_ov003_0221fdc8(UnkStruct_0221fdc8_4 *s)
{
    UnkStruct_0221fdc8_2 *t;
    unsigned char c;
    if (data_ov003_0223cad4 == 0) {
        t = s->unk_04->unk_2C;
        c = s->unk_00->unk_01;
        if (t != 0 && t->unk_E8 == c) {
            func_02030b80(FX_Div(s->unk_B0->unk_28 + 0xda2, 0xda2));
            data_ov003_0223cad4 = 1;
        }
    }
}

void func_ov003_0221fdb8(UnkStruct_0221fdb8 *obj)
{
    obj->callback = (void (*)(void *)) func_ov003_0221fdc8;
    obj->unk_90 = 2;
}

void *func_ov003_0221fd60(void *self)
{
    func_020ee660(self);
    *(int *) self = (unsigned int) data_020da13c;
    *(int *) self = (unsigned int) data_ov003_02239a58;
    func_ov003_0221f618((char *) self + 0x54);
    func_ov003_0221f204((char *) self + 0x150);
    func_020576cc((char *) self + 0x1f0);
    func_020576cc((char *) self + 0x280);
    func_ov003_0221ef7c((char *) self + 0x310);
    return self;
}

struct UnkStruct_0221fd04 *func_ov003_0221fd04(struct UnkStruct_0221fd04 *self)
{
    self->head = ((char *) data_ov003_02239a58);
    func_ov003_0221ef78((char *) self + 0x310);
    func_02057694((char *) self + 0x280);
    func_02057694((char *) self + 0x1f0);
    func_ov003_0221f1f4((char *) self + 0x150);
    func_ov003_0221f5f4((char *) self + 0x54);
    self->head = ((char *) data_020da13c);
    func_020ee62c(self);
    return self;
}

void *func_ov003_0221fca4(struct UnkStruct_0221fca4 *this)
{
    this->unk_00 = (void *) ((int *) data_ov003_02239a58);
    func_ov003_0221ef78((char *) this + 0x310);
    func_02057694((char *) this + 0x280);
    func_02057694((char *) this + 0x1f0);
    func_ov003_0221f1f4((char *) this + 0x150);
    func_ov003_0221f5f4((char *) this + 0x54);
    this->unk_00 = (void *) ((int *) data_020da13c);
    func_020ee62c(this);
    func_020edf54(this);
    return this;
}

int func_ov003_0221faac(char *self)
{
    unsigned int z;
    unsigned int i;
    unsigned int n;
    int idx;
    int aa, bb;
    int v3[3];
    UnkStruct_0221faac *g;
    int t;
    int u;
    char *p;
    unsigned int x, j, y;
    char *e;

    func_ov003_0221f1ec(self + 0x150);
    func_ov003_0221f1ac(self + 0x150);
    t = func_02037594(func_0203750c());
    u = func_02037564(func_0203750c());
    func_020575e4(self + 0x1f0, t, data_ov003_02239aac, data_ov003_02239ab8, u, func_02037570(func_0203750c()), 0);
    t = func_02037594(func_0203750c());
    u = func_0203754c(func_0203750c());
    func_020575e4(self + 0x280, t, data_ov003_02239ac4, data_ov003_02239acc, u, func_02037558(func_0203750c()), 1);
    g = data_021c80bc;
    *(unsigned int *) (self + 0x148) = g->unk_04;
    *(unsigned int *) (self + 0x14c) = g->unk_08;
    *(int *) (self + 0x50) =
        (int) func_020e9948(data_021c9b24, 0xec * *(unsigned int *) (self + 0x148) * *(unsigned int *) (self + 0x14c));
    p = (char *) *(int *) (self + 0x50);
    while (p <
           (char *) *(int *) (self + 0x50) + (*(unsigned int *) (self + 0x148) * *(unsigned int *) (self + 0x14c) * 0xec)) {
        if (p != 0) {
            p = func_ov003_0221f3b0(p);
        }
        p = p + 0xec;
    }
    for (z = 0; z < *(unsigned int *) (self + 0x14c); z++) {
        for (x = 0; x < *(unsigned int *) (self + 0x148); x++) {
            for (j = 0; j < 0x10; j++) {
                for (i = 0; i < 0x10; i++) {
                    func_0204f800(&aa, &bb, x, z, i, j);
                    idx = func_02031478(aa, bb);
                    if (idx != -1) {
                        v3[0] = 0;
                        v3[1] = 0;
                        v3[2] = 0;
                        func_0204f7ac(v3, x, z, i, j);
                        func_ov003_0221f47c(self + 0x54, v3, idx);
                    }
                }
            }
        }
    }
    n = 0;
    for (y = 0; y < *(unsigned int *) (self + 0x14c); y++) {
        for (x = 0; x < *(unsigned int *) (self + 0x148); x++) {
            if (x < g->unk_04 && y < g->unk_08 && g->unk_00 != 0) {
                e = g->unk_00 + 0x28 * (x + y * g->unk_04);
            } else {
                e = 0;
            }
            func_ov003_0221f270((char *) *(int *) (self + 0x50) + 0xec * n++, e, x, y);
        }
    }
    func_ov003_0221ef70(self + 0x310);
    return 1;
}

int func_ov003_0221fa28(void *arg0)
{
    int i, j;
    char *ptr;
    func_ov003_0221f144((char *) arg0 + 0x150);
    func_ov003_0221f444((char *) arg0 + 0x54);
    ptr = *(char **) ((char *) arg0 + 0x50);
    for (i = 0; i < *(int *) ((char *) arg0 + 0x14c); i++) {
        for (j = 0; j < *(int *) ((char *) arg0 + 0x148); j++) {
            func_ov003_0221f244(ptr);
            ptr += 0xEC;
        }
    }
    func_02057538((char *) arg0 + 0x1f0);
    func_02057538((char *) arg0 + 0x280);
    func_ov003_0221f6dc(arg0);
    data_021d3124 = 0;
    return 1;
}
