/* outdoor_clock: 8 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221dbb0 @ 0x0221dbb0, 0x1c bytes, Thumb
 * func_ov003_0221db90 @ 0x0221db90, 0x1e bytes, Thumb
 * func_ov003_0221db54 @ 0x0221db54, 0x3c bytes, Thumb
 * func_ov003_0221db30 @ 0x0221db30, 0x24 bytes, Thumb
 * func_ov003_0221db04 @ 0x0221db04, 0x2c bytes, Thumb
 * func_ov003_0221da98 @ 0x0221da98, 0x6c bytes, Thumb
 * func_ov003_0221da68 @ 0x0221da68, 0x30 bytes, Thumb
 * func_ov003_0221da64 @ 0x0221da64, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0221db90 UnkStruct_0221db90;

typedef struct SubA SubA;

typedef struct SubB SubB;

typedef struct Vtbl Vtbl;

typedef struct PType PType;

struct SubA {
    u8 pad_00[1];
    u8 unk_01;
};

struct SubB {
    u8 pad_00[0x2c];
    PType *p;
};

struct UnkStruct_0221db90 {
    SubA *a;
    SubB *b;
};

struct Vtbl {
    u8 pad_00[0x60];
    void (*func)(PType *self, u8 arg1, UnkStruct_0221db90 *ctx);
};

struct PType {
    Vtbl *vt;
};

typedef struct UnkStruct_0221db54 {
    unsigned int unk_00;
    char pad_04[0xEC - 4];
    unsigned int unk_EC;
    char pad_EC[0x2B4 - (0xEC + 4)];
    signed char unk_2B4;
    signed char unk_2B5;
} UnkStruct_0221db54;

typedef struct {
    void *unk_00;
    char pad_04[0xE8];
    void *unk_EC;
} UnkStruct_0221db30;

typedef struct {
    void *unk_00;
    unsigned char pad_04[0xe8];
    void *unk_EC;
} UnkStruct_0221db04;

struct SELF {
    unsigned char pad_00[0x198];
    void *unk_198;
    unsigned char pad_19C[0x2b4 - 0x19c];
    signed char unk_2B4;
    signed char unk_2B5;
};

typedef struct {
    char pad_00[0x2b4];
    signed char unk_2B4;
    signed char unk_2B5;
} UnkStruct_0221da68;

extern int func_020edf70(int);
extern void *func_ov009_0226552c(void *p);
extern unsigned char data_ov003_022390e8[];
extern unsigned char data_ov003_022391ac[];
extern void *func_ov009_0226539c(void *self);
extern void func_020edf54(void *self);
extern int func_0205790c(void *, const char *);
extern void func_02055de0(void *, void (*)(void *), int, int, void *, int);
extern const char data_ov003_02239224[];
extern const char data_ov003_0223922c[];
extern void func_020b3220(int arg);
extern void func_020b3188(int arg);

void *func_ov003_0221db54(void *p);

void func_ov003_0221dbb0(void)
{
    void *condition_value_11;
    condition_value_11 = (void *) (func_020edf70(0x2b8));
    if (condition_value_11 != 0) {
        func_ov003_0221db54(condition_value_11);
    }
}

void func_ov003_0221db90(UnkStruct_0221db90 *obj)
{
    SubB *sb = obj->b;
    PType *p = sb->p;
    if (p) {
        u8 byte = obj->a->unk_01;
        p->vt->func(p, byte, obj);
    }
}

void *func_ov003_0221db54(void *p)
{
    UnkStruct_0221db54 *u = (UnkStruct_0221db54 *) p;
    func_ov009_0226552c(p);
    u->unk_00 = (unsigned int) data_ov003_022390e8;
    u->unk_EC = (unsigned int) data_ov003_022391ac;
    u->unk_2B5 = -1;
    u->unk_2B4 = u->unk_2B5;
    return p;
}

void *func_ov003_0221db30(void *self)
{
    UnkStruct_0221db30 *p = (UnkStruct_0221db30 *) self;
    p->unk_00 = ((int *) data_ov003_022390e8);
    p->unk_EC = ((int *) data_ov003_022391ac);
    func_ov009_0226539c(self);
    return self;
}

UnkStruct_0221db04 *func_ov003_0221db04(UnkStruct_0221db04 *self)
{
    self->unk_00 = ((char *) data_ov003_022390e8);
    self->unk_EC = ((char *) data_ov003_022391ac);
    func_ov009_0226539c(self);
    func_020edf54(self);
    return self;
}

int func_ov003_0221da98(struct SELF *self)
{
    self->unk_2B4 = func_0205790c(self->unk_198, data_ov003_02239224);
    self->unk_2B5 = func_0205790c(self->unk_198, data_ov003_0223922c);
    if (self->unk_2B4 != -1 && self->unk_2B5 != -1) {
        func_02055de0((char *) self + 0x13c, (void (*)(void *)) func_ov003_0221db90, 6, 2, self, 0);
    }
    return 1;
}

void func_ov003_0221da68(UnkStruct_0221da68 *p, int value, int arg)
{
    if (value == p->unk_2B4) {
        func_020b3220(arg);
    } else if (value == p->unk_2B5) {
        func_020b3188(arg);
    }
}

int func_ov003_0221da64(void)
{
    return 1;
}
