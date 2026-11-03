/* player_house: 14 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221de04 @ 0x0221de04, 0x1c bytes, Thumb
 * func_ov003_0221dde0 @ 0x0221dde0, 0x24 bytes, Thumb
 * func_ov003_0221ddbc @ 0x0221ddbc, 0x24 bytes, Thumb
 * func_ov003_0221dd90 @ 0x0221dd90, 0x2c bytes, Thumb
 * func_ov003_0221dd3c @ 0x0221dd3c, 0x54 bytes, Thumb
 * func_ov003_0221dd1c @ 0x0221dd1c, 0x20 bytes, Thumb
 * func_ov003_0221dd0c @ 0x0221dd0c, 0x10 bytes, Thumb
 * func_ov003_0221dcd8 @ 0x0221dcd8, 0x34 bytes, Thumb
 * func_ov003_0221dc7c @ 0x0221dc7c, 0x5c bytes, Thumb
 * func_ov003_0221dc38 @ 0x0221dc38, 0x44 bytes, Thumb
 * func_ov003_0221dc1c @ 0x0221dc1c, 0x1c bytes, Thumb
 * func_ov003_0221dc0c @ 0x0221dc0c, 0x10 bytes, Thumb
 * func_ov003_0221dc08 @ 0x0221dc08, 0x4 bytes, Thumb
 * func_ov003_0221dc04 @ 0x0221dc04, 0x4 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0221ddbc {
    void *unk_00;
};

struct UnkStruct_0221ddbc_2 {
    void *unk_00;
    char pad_04[0xE8];
    struct UnkStruct_0221ddbc sub;
};

typedef struct UnkStruct_0221dd90 {
    void *unk_00;
    unsigned char pad_04[0xe8];
    void *unk_EC;
} UnkStruct_0221dd90;

typedef struct UnkStruct_0221dc7c {
    u8 pad_00[0x2b4];
    volatile int unk_2B4;
} UnkStruct_0221dc7c;

typedef struct {
    char pad_00[0x198];
    void *unk_198;
    char pad_19C[0x118];
    void *unk_2B4;
    void *unk_2B8;
} UnkStruct_0221dc38;

extern int func_020edf70(int);
extern void *func_ov009_0226552c(void *this);
extern char data_ov003_02239254[];
extern char data_ov003_02239318[];
extern void *func_ov009_0226539c(void *obj);
extern void func_020edf54(UnkStruct_0221dd90 *self);
extern int func_ov009_0226321c(int, int *, int *);
extern int func_02003348(int, int, int *, int, int);
extern int func_ov003_02220174(int);
extern void func_ov009_022632c8(void *object);
extern int func_02060e10(void *p);
extern unsigned char data_021ebcd4[];
extern int func_ov003_022203dc(void);
extern int func_02064328(char *a, char *b, signed char c, int d);
extern char data_ov003_0223c998[];
extern char data_ov003_02239390[];
extern signed char data_ov003_02236654[];
extern void *data_021fbe94;
extern int data_021c9b1c;
extern void *func_02064b2c(int id, void *heap, int alignment, unsigned int *size);
extern int func_021077e8(void *);
extern int func_020560e0(int, int);
extern int func_020561cc(int, int);
extern void func_020e9898(void *);
extern int NNS_G3dBindMdlTex(void *, void *);
extern int NNS_G3dBindMdlPltt(void *, void *);
extern int func_020984d4(void);
extern int func_020988d8(unsigned int argument0);
extern int func_02060be0(void *addr);

void *func_ov003_0221dde0(void *this);
void func_ov003_0221dc7c(UnkStruct_0221dc7c *self);
void func_ov003_0221dc38(UnkStruct_0221dc38 *p);

void func_ov003_0221de04(void)
{
    void *condition_value_13;
    condition_value_13 = (void *) (func_020edf70(0x2bc));
    if (condition_value_13 != 0) {
        func_ov003_0221dde0(condition_value_13);
    }
}

void *func_ov003_0221dde0(void *this)
{
    func_ov009_0226552c(this);
    *(void **) this = (void *) ((int *) data_ov003_02239254);
    *(void **) ((char *) this + 0xec) = (void *) ((int *) data_ov003_02239318);
    return this;
}

void *func_ov003_0221ddbc(struct UnkStruct_0221ddbc_2 *obj)
{
    struct UnkStruct_0221ddbc *p = &obj->sub;
    obj->unk_00 = data_ov003_02239254;
    p->unk_00 = data_ov003_02239318;
    func_ov009_0226539c(obj);
    return obj;
}

UnkStruct_0221dd90 *func_ov003_0221dd90(UnkStruct_0221dd90 *self)
{
    self->unk_00 = ((char *) data_ov003_02239254);
    self->unk_EC = ((char *) data_ov003_02239318);
    func_ov009_0226539c((void *) self);
    func_020edf54(self);
    return self;
}

int func_ov003_0221dd3c(int arg)
{
    int arr[4];

    func_ov003_0221dc7c((UnkStruct_0221dc7c *) arg);
    func_ov003_0221dc38((UnkStruct_0221dc38 *) arg);

    if (func_ov009_0226321c(arg, &arr[1], &arr[0])) {
        arr[1] -= 0x2000;
        arr[3] += 0x1000;
        func_02003348(0x24, 0x501d, &arr[1], 0, 0);
    }

    return 1;
}

int func_ov003_0221dd1c(void)
{
    void *condition_value_12;
    condition_value_12 = (void *) (func_ov003_02220174(0x501d));
    if (condition_value_12 != 0) {
        func_ov009_022632c8(condition_value_12);
    }
    return 1;
}

int func_ov003_0221dd0c(void)
{
    return func_02060e10((void *) data_021ebcd4);
}

void *func_ov003_0221dcd8(void)
{
    int x = func_ov003_0221dd0c();
    int y = func_ov003_022203dc();
    func_02064328(data_ov003_0223c998, data_ov003_02239390, data_ov003_02236654[x & 0xF], y);
    return data_ov003_0223c998;
}

void func_ov003_0221dc7c(UnkStruct_0221dc7c *self)
{
    void *p;

    p = func_02064b2c((int) func_ov003_0221dcd8(), data_021fbe94, -4, 0);
    self->unk_2B4 = func_021077e8(p);
    if (func_020560e0(self->unk_2B4, 0) != 0) {
        self->unk_2B4 = func_020561cc(self->unk_2B4, data_021c9b1c);
    }
    func_020e9898(p);
}

void func_ov003_0221dc38(UnkStruct_0221dc38 *p)
{
    if (p->unk_2B4 != 0) {
        NNS_G3dBindMdlTex(p->unk_198, p->unk_2B4);
    }
    if (p->unk_2B8 != 0) {
        NNS_G3dBindMdlTex(p->unk_198, p->unk_2B8);
        NNS_G3dBindMdlPltt(p->unk_198, p->unk_2B8);
    }
}

int func_ov003_0221dc1c(void)
{
    int result;

    result = func_020988d8((unsigned int) func_020984d4());

    if (result != 0) {
        return 0;
    } else {
        return 1;
    }
}

void func_ov003_0221dc0c(void)
{
    func_02060be0(((char *) data_021ebcd4));
}

int func_ov003_0221dc08(void)
{
    return 1;
}

int func_ov003_0221dc04(void)
{
    return 1;
}
