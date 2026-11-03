/* my_designs_11: 10 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_0229bd90 @ 0x0229bd90, 0x4 bytes, Thumb
 * func_ov121_0229bd8c @ 0x0229bd8c, 0x4 bytes, Thumb
 * func_ov121_0229bd7c @ 0x0229bd7c, 0x10 bytes, Thumb
 * func_ov121_0229bcc8 @ 0x0229bcc8, 0xb4 bytes, Thumb
 * func_ov121_0229bc70 @ 0x0229bc70, 0x58 bytes, Thumb
 * func_ov121_0229bc08 @ 0x0229bc08, 0x68 bytes, Thumb
 * func_ov121_0229bbd0 @ 0x0229bbd0, 0x38 bytes, Thumb
 * func_ov121_0229bb90 @ 0x0229bb90, 0x40 bytes, Thumb
 * func_ov121_0229bb54 @ 0x0229bb54, 0x3a bytes, Thumb
 * func_ov121_0229ba60 @ 0x0229ba60, 0xf4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad[0x8d];
    unsigned char byte;
} UnkStruct_0229bcc8;

struct UnkStruct_0229bc70 {
    u8 pad_00[0x8c];
    u8 unk_8C;
    u8 pad_8D[0x2d8 - 0x8c - 1];
    u8 unk_2D8;
};

struct UnkStruct_0229bbd0 {
    char pad_00[0x94];
    int unk_94;
};

typedef struct UnkStruct_0229bb90 {
    char pad_00[0x94];
    int unk_94;
} UnkStruct_0229bb90;

typedef struct {
    u8 pad_00[0x64];
    u32 unk_64;
} PtrStruct;

typedef struct {
    u8 pad_00[0x9c];
    u32 unk_9C;
    u8 pad_A0[0xa2 - 0xa0];
    u16 unk_A2;
    u8 pad_A4[0xac - 0xa4];
    u8 unk_AC;
    u8 pad_AD[0xb0 - 0xad];
    u8 unk_B0;
    u8 unk_B1;
    u8 pad_B2[0x528 - 0xb2];
    u8 unk_528;
    u8 pad_529[0x118c - 0x529];
    u8 arr[8];
} UnkStruct_0229ba60;

extern void func_020ee470(void *parameter0);
extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_0206fe60(void);
extern int func_ov090_022990e0(void);
extern struct {
    unsigned char pad[2];
    unsigned short flags;
} data_021fbe40;
extern void *func_020ee45c(struct UnkStruct_0229bc70 *self);
extern void func_ov090_022993cc(void *ptr, unsigned char b);
extern unsigned char *func_ov002_022080a0(struct UnkStruct_0229bc70 *self, unsigned char value);
extern int func_ov002_02207d24(void *p, int x);
extern int func_ov121_0229a50c(void *receiver);
extern void func_ov121_0229b948(void);
extern void func_ov121_0229b8c0(void *p);
extern void func_ov121_0229b7d4(void *self);
extern void func_ov002_022097b8(void *p);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int x);
extern void func_ov002_02208090(void *p, int a);
extern void func_ov121_02299a4c(void *p, int a);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f48(struct UnkStruct_0229bbd0 *s, int x);
extern unsigned char *func_ov121_0229afb8(struct UnkStruct_0229bbd0 *s);
extern void func_ov121_0229a358(void *);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern int func_ov002_02207f60(void *);
extern int func_ov002_02207f3c(void *p, int n);
extern void func_020027f0(int n);
extern u8 data_020e54a8;
extern PtrStruct *data_020ccf94;
extern void func_ov121_0229adc0(UnkStruct_0229ba60 *self, int val);
extern int func_ov121_0229ba2c(void *receiver);
extern int func_02073d90(PtrStruct *p);
extern void func_ov002_02209984(void *addr, int a, int b, int c);

int func_ov121_0229bc70(struct UnkStruct_0229bc70 *self, int mode);

int func_ov121_0229bd90(void)
{
    return 1;
}

int func_ov121_0229bd8c(void)
{
    return 1;
}

int func_ov121_0229bd7c(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

int func_ov121_0229bcc8(UnkStruct_0229bcc8 *self)
{
    int r5;

    func_0206f58c();
    if (func_0206f56c()) {
        switch (self->byte) {
            case 0:
            case 1:
            case 4:
            case 7:
            case 8:
                return func_ov121_0229bc70((struct UnkStruct_0229bc70 *) self, 7);
            default:
                break;
        }
    }

    if (self->byte != 0 && self->byte != 4) {
        return 0;
    }

    r5 = -1;
    if (func_0206fe60()) {
        r5 = func_ov090_022990e0();
    } else {
        unsigned short w = data_021fbe40.flags;
        if (w & 0x800) {
            r5 = 0;
        } else if (w & 0x400) {
            r5 = 5;
        } else if (w & 0x4) {
            r5 = 4;
        }
    }

    return func_ov121_0229bc70((struct UnkStruct_0229bc70 *) self, r5);
}

int func_ov121_0229bc70(struct UnkStruct_0229bc70 *self, int mode)
{
    void *r = func_020ee45c(self);
    if (mode != -1 && mode != 1) {
        func_ov090_022993cc(r, (unsigned char) mode);
        self->unk_8C = 2;
        func_ov002_022080a0(self, 1);
        func_ov002_02207d24(&self->unk_2D8, 1);
        if (mode != 7) {
            func_ov121_0229a50c(self);
        }
        return 1;
    }
    return 0;
}

void func_ov121_0229bc08(void *p)
{
    func_ov121_0229b948();
    func_ov121_0229b8c0(p);
    func_ov121_0229b7d4(p);
    func_ov002_022097b8((char *) p + 0x528);
    func_ov002_02207f20(p, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02208090(p, 1);
    func_ov121_02299a4c(p, 1);
    func_ov002_02207e80(p, 6, 0, 0);
    *(void **) ((char *) p + 0x94) = (void *) func_ov002_02207f60(p);
}

void func_ov121_0229bbd0(struct UnkStruct_0229bbd0 *s)
{
    if (func_ov002_02207f48(s, 0) != 0) {
        func_ov002_022080a0((struct UnkStruct_0229bc70 *) s, 2);
        func_ov121_0229afb8(s);
    }
    func_ov002_02207e80((void *) s, 6, 0, 0);
    s->unk_94 = func_ov002_02207f60((void *) s);
}

void func_ov121_0229bb90(UnkStruct_0229bb90 *p)
{
    func_ov121_0229a358(p);
    func_ov002_02207f04(p, 8, 0, 0, 0x30);
    func_ov002_02208090(p, 3);
    func_ov002_02207e80(p, 6, 0, 0);
    p->unk_94 = func_ov002_02207f60(p);
}

void func_ov121_0229bb54(void *arg)
{
    if (func_ov002_02207f3c(arg, 0)) {
        func_020027f0(6);
        func_ov002_022080a0((struct UnkStruct_0229bc70 *) arg, 5);
    } else {
        func_ov002_02207e80(arg, 6, 0, 0);
        *(int *) ((char *) arg + 0x94) = func_ov002_02207f60(arg);
    }
}

void func_ov121_0229ba60(UnkStruct_0229ba60 *self)
{
    u8 i;
    unsigned int flag;
    PtrStruct *p;

    for (i = 0; i < 8; i++) {
        self->arr[i] = i;
    }
    self->unk_A2 = 0;
    self->unk_9C = 0;

    flag = data_020e54a8 ? 0 : 1;
    if (flag != 0) {
        self->unk_AC = 0;
        func_ov121_0229adc0(self, 9);
        func_ov121_0229adc0(self, 10);
        func_ov121_0229adc0(self, 11);

        p = data_020ccf94;
        if (func_02073d90(p) != 0 && p->unk_64 != 0) {
            func_ov121_0229adc0(self, 15);
        }
    } else {
        if (func_ov121_0229ba2c(self) != 0) {
            self->unk_AC = 1;
            func_ov121_0229adc0(self, 15);
        } else {
            self->unk_AC = 2;
            func_ov121_0229adc0(self, 9);
            func_ov121_0229adc0(self, 10);
            func_ov121_0229adc0(self, 11);
            func_ov121_0229adc0(self, 14);
            func_ov121_0229adc0(self, 15);
        }
    }

    func_ov002_02209984(&self->unk_528, 3, 1, 0);
    self->unk_B0 = 0x18;
    self->unk_B1 = 0;
}
