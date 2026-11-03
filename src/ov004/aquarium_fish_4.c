/* aquarium_fish_4: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02236578 @ 0x02236578, 0x1a bytes, Thumb
 * func_ov004_0223655c @ 0x0223655c, 0x1a bytes, Thumb
 * func_ov004_0223653c @ 0x0223653c, 0x20 bytes, Thumb
 * func_ov004_02236464 @ 0x02236464, 0xd8 bytes, Thumb
 * func_ov004_02236418 @ 0x02236418, 0x4c bytes, Thumb
 * func_ov004_0223635c @ 0x0223635c, 0xbc bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02236464 {
    char unk_00[0x1ac];
    int unk_1AC;
} UnkStruct_02236464;

struct UnkStruct_02236418;

struct UnkStruct_02236418_2 {
    int a, b, c;
};

struct UnkStruct_02236418 {
    u8 pad_00[0x1ee];
    u8 unk_1EE;
    u8 pad_1EF[0x253 - 0x1ef];
    u8 unk_253;
};

struct UnkStruct_0223635c {
    u8 pad_00[0x158];
    int unk_158;
    u8 pad_15C[0x164 - 0x15c];
    u8 unk_164;
    u8 pad_165[0x1a8 - 0x165];
    int unk_1A8;
    u8 pad_1AC[0x1c0 - 0x1ac];
    s16 unk_1C0;
    u8 pad_1C2[0x1c4 - 0x1c2];
    s16 unk_1C4;
    u8 pad_1C6[0x1ee - 0x1c6];
    u8 unk_1EE;
    u8 pad_1EF[0x1fd - 0x1ef];
    u8 unk_1FD;
    u8 pad_1FE[0x24c - 0x1fe];
    s16 unk_24C;
    u8 pad_24E[0x253 - 0x24e];
    u8 unk_253;
    u8 unk_254;
};

extern void func_02054d60(void *, void *);
extern void func_02054cf4(void *, void *);
extern unsigned char data_021f6c38;
extern unsigned char data_021f6c34;
extern int func_020b6590(void);
extern int func_020b755c(int h, Vec3 *v, int *id, unsigned char *kind);
extern long long func_020ea940(char *p, Vec3 *v);
extern int func_0200322c(void *a, void *b);
extern int func_ov004_02239460(int a, int b);
extern int func_ov004_022397ec(struct UnkStruct_0223635c *self);

void func_ov004_0223635c(struct UnkStruct_0223635c *self, void *p);

void func_ov004_02236578(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) *(int *) (self + 0x4) + 0x2c) != 0x0) {
        func_02054d60((char *) *(int *) ((char *) *(int *) (self + 0x4) + 0x2c) + 0x64, self);
    }
}

void func_ov004_0223655c(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) *(int *) (self + 0x4) + 0x2c) != 0x0) {
        func_02054cf4((char *) *(int *) ((char *) *(int *) (self + 0x4) + 0x2c) + 0x64, self);
    }
}

void func_ov004_0223653c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x24) = (void *) func_ov004_02236578;
    *(u8 *) (self + 0x92) = 0x1;
    *(void **) (self + 0x24) = (void *) func_ov004_0223655c;
    *(u8 *) (self + 0x92) = 0x2;
}

int func_ov004_02236464(UnkStruct_02236464 *self, Vec3 *out)
{
    unsigned char kind;
    int id;
    Vec3 v;
    int ok;
    int t, d;

    ok = 0;
    if (func_020b755c(func_020b6590(), &v, &id, &kind) != 0) {
        t = (data_021f6c38 != 0 && data_021f6c34 != 0) ? 1 : 0;
        if (t == 0 && id == 0x13) {
            if (kind == 0) {
                if (func_020ea940((char *) self + 0x1a8, &v) <= 0x9000) {
                    d = self->unk_1AC - v.y;
                    if (d < 0) {
                        d = -d;
                    }
                    if (d <= 0x3000) {
                        out->x = v.x;
                        out->y = v.y;
                        out->z = v.z;
                        ok = 1;
                    }
                }
            } else if (kind == 1) {
                if (func_020ea940((char *) self + 0x1a8, &v) <= 0x9000) {
                    d = self->unk_1AC - v.y;
                    if (d < 0) {
                        d = -d;
                    }
                    if (d <= 0x3000) {
                        out->x = v.x;
                        out->y = v.y;
                        out->z = v.z;
                        ok = 1;
                    }
                }
            }
        }
    }
    return ok;
}

int func_ov004_02236418(struct UnkStruct_02236418 *self)
{
    int ok;
    struct UnkStruct_02236418_2 f;

    ok = 0;
    if (self->unk_253 != 0) {
        if (self->unk_1EE != 1) {
            self->unk_253 = 0;
        }
        return 0;
    }
    if (func_ov004_02236464((UnkStruct_02236464 *) self, (Vec3 *) (&f)) != 0) {
        func_ov004_0223635c((struct UnkStruct_0223635c *) self, (void *) (&f));
        ok = 1;
        self->unk_253 = 1;
    }
    return ok;
}

void func_ov004_0223635c(struct UnkStruct_0223635c *self, void *p)
{
    if (self->unk_253 != 0) {
        return;
    }
    self->unk_1C4 = 0;
    self->unk_1EE = 1;
    self->unk_158 = 0;
    if ((u8) (self->unk_164 + 0xfc) <= 1) {
        if (self->unk_254 >= 0x7d) {
            self->unk_24C = func_0200322c(p, &self->unk_1A8);
        } else if (self->unk_1C0 >= 0) {
            self->unk_24C = func_ov004_02239460(0x38e4, 0x471c);
        } else {
            self->unk_24C = -func_ov004_02239460(0x38e4, 0x471c);
        }
    } else {
        self->unk_24C = func_0200322c(p, &self->unk_1A8);
    }
    if (self->unk_1FD == 1) {
        func_ov004_022397ec(self);
    }
}
