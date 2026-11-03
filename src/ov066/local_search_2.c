/* local_search_2: 16 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02267db4 @ 0x02267db4, 0x4c bytes, ARM
 * func_ov066_02267cb0 @ 0x02267cb0, 0x104 bytes, ARM
 * func_ov066_02267c74 @ 0x02267c74, 0x3c bytes, ARM
 * func_ov066_02267c0c @ 0x02267c0c, 0x68 bytes, ARM
 * func_ov066_02267be0 @ 0x02267be0, 0x2c bytes, ARM
 * func_ov066_02267b58 @ 0x02267b58, 0x88 bytes, ARM
 * func_ov066_02267958 @ 0x02267958, 0x200 bytes, ARM
 * func_ov066_0226794c @ 0x0226794c, 0xc bytes, ARM
 * func_ov066_02267908 @ 0x02267908, 0x44 bytes, ARM
 * func_ov066_0226783c @ 0x0226783c, 0xcc bytes, ARM
 * func_ov066_022677e0 @ 0x022677e0, 0x5c bytes, ARM
 * func_ov066_02267784 @ 0x02267784, 0x5c bytes, ARM
 * func_ov066_02267740 @ 0x02267740, 0x44 bytes, ARM
 * func_ov066_022676a0 @ 0x022676a0, 0xa0 bytes, ARM
 * func_ov066_0226768c @ 0x0226768c, 0x14 bytes, ARM
 * func_ov066_0226763c @ 0x0226763c, 0x50 bytes, ARM
 */

#include "types.h"

struct UnkStruct_02267db4 {
    char pad_00[0x10];
    unsigned char *arr;
};

struct UnkStruct_02267db4_2 {
    char pad_00[0x8e];
    unsigned char unk_8E;
};

typedef struct {
    char pad_00[0xC];
    signed int flag : 1;
} UnkStruct_02267c74;

struct UnkStruct_02267c0c {
    int unk_00;
    int unk_04;
    char pad_08;
    unsigned char unk_09;
};

struct UnkStruct_02267c0c_2 {
    char pad_00[0x95];
    unsigned char unk_95;
};

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
} UnkStruct_02267be0;

struct UnkStruct_02267b58;

struct UnkStruct_02267b58_2;

struct UnkStruct_02267b58_3;

struct UnkStruct_02267b58_4;

struct UnkStruct_02267b58 {
    unsigned char pad_00[0x8e];
    unsigned char unk_8E;
    unsigned char pad_8F[0x95 - 0x8e - 1];
    unsigned char unk_95;
};

struct UnkStruct_02267b58_2 {
    struct UnkStruct_02267b58_4 *first;
    unsigned int second;
};

struct UnkStruct_02267b58_3 {
    unsigned char pad_00[0x22];
    unsigned short unk_22;
};

struct UnkStruct_02267b58_4 {
    unsigned int unk_00;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char unk_0C;
    unsigned char unk_0D;
};

typedef struct Msg {
    u16 id;
    u8 body[6];
} Msg;

typedef struct Link {
    u8 pad_00[0x3c];
    u16 state;
    u8 pad_3E[0x4b - 0x3e];
    u8 flags;
    u8 pad_4C[0x50 - 0x4c];
    u8 data[8];
} Link;

typedef struct UnkStruct_02267958 {
    u8 pad_00[4];
    Link *link;
    void *objs;
    int f0 : 1;
    int pad0c : 31;
    u8 pad_10[0x3c - 0x10];
    int queue;
} UnkStruct_02267958;

typedef struct Flags {
    u8 pad_00[0x3c];
    int pad3c : 3;
    int f3 : 1;
    int f4 : 1;
    int pad3c2 : 27;
} Flags;

typedef struct UnkStruct_02267958_2 {
    u8 pad_00[0x95];
    u8 index;
} UnkStruct_02267958_2;

typedef struct Peer {
    u8 pad_00[0xa];
    u8 name[8];
    u16 tag;
} Peer;

struct UnkStruct_02267908 {
    char pad_00[0xc0];
    unsigned int unk_C0;
};

struct S2b {
    u8 pad_00[0x44];
    int unk_44;
};

struct UnkStruct_0226783c {
    u8 pad_00[0x4];
    struct S2b *unk_04;
    u8 pad1[0x64];
    int (*unk_6C)(void *);
};

struct UnkStruct_0226783c_2 {
    u8 pad_00[0x95];
    unsigned char unk_95;
};

struct UnkStruct_0226783c_3 {
    u8 pad_00[0x28];
    int unk_28;
    u8 pad1[0x10];
    signed int : 5;
    signed int b5 : 1;
    signed int b6 : 1;
    signed int b7 : 1;
};

struct Param {
    u8 pad_00[4];
    unsigned char unk_04;
    u8 pad1;
    unsigned char unk_06;
};

typedef struct {
    unsigned char pad_00[8];
    char *base;
} UnkStruct_022677e0;

typedef struct {
    unsigned char pad_00[9];
    unsigned char count;
} UnkStruct_022677e0_2;

struct ListStruct {
    int unk_00;
    int unk_04;
    char *entries;
};

struct UnkStruct_022676a0_3 {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[4];
    u16 unk_08;
};

struct UnkStruct_022676a0 {
    u8 pad_00[8];
    u32 base;
    unsigned int : 1;
    signed int flag : 1;
};

struct UnkStruct_022676a0_2 {
    u8 pad_00[0x95];
    u8 unk_95;
};

typedef struct {
    unsigned char pad_00[2];
    unsigned short field;
} Arg;

typedef struct {
    unsigned int pad_00;
    unsigned int field;
} Target;

extern int func_ov066_0226a1b0(int);
extern struct UnkStruct_02267db4 *data_ov066_0226bdec;
extern struct UnkStruct_02267db4_2 *data_ov066_0226bdf4;
extern struct UnkStruct_02267cb0_3 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} *data_ov066_0226bdf0;
extern void func_ov066_0226a3b0(int);
extern void func_ov066_0226a2e8(int, int);
extern void func_ov066_02267e00(int);
extern void OS_CancelAlarm(void *);
extern void OS_SetAlarm(void *, long long, void (*)(void), int);
extern void DC_InvalidateRange(void *p, int n);
extern void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern void DC_StoreRange(void *p, int n);
extern int func_ov066_0226a494(void *obj, int a, void *name, int tag, int id, void *link);
extern struct UnkStruct_02267908;
extern void *func_ov066_0226a434(void *);
extern int func_ov066_0226a418(void *ptr, int arg);
extern int WM_StartScan(void (*func)(void *), int data);
extern void func_ov066_0226686c(int status);
extern int func_ov066_02266e08(void);
extern void func_ov066_0226a404(u32 arg);
extern int WM_EndScan(void (*func)(void *));
extern void func_ov066_02266bf4(void);

void func_ov066_02267c74(void);
void func_ov066_02267c0c(void);
void func_ov066_02267be0(void);
void func_ov066_02267b58(void);
void func_ov066_0226794c(void *argument);
void func_ov066_02267908(void);
int func_ov066_0226783c(void *arg0, struct Param *p);
void func_ov066_02267740(void);
void func_ov066_022676a0(struct UnkStruct_022676a0_3 *self);
void func_ov066_0226768c(void);
void func_ov066_0226763c(Arg *arg);

int func_ov066_02267db4(int index)
{
    if (data_ov066_0226bdec->arr) {
        return data_ov066_0226bdec->arr[index];
    }
    return func_ov066_0226a1b0(data_ov066_0226bdf4->unk_8E);
}

void func_ov066_02267cb0(int arg0)
{
    if ((*(struct UnkStruct_02267cb0 { unsigned char pad_00[0x3c]; struct { unsigned int : 3; signed int flag : 1; unsigned int : 28; } bits; } * *) &data_ov066_0226bdec)->bits.flag != 0) {
        func_ov066_0226a3b0(data_ov066_0226bdf0->unk_08 + ((int) (*(struct UnkStruct_02267cb0_2 { unsigned char pad_00[0x95]; unsigned char unk_95; } * *) &data_ov066_0226bdf4)->unk_95 << 4));
    } else {
        func_ov066_0226a2e8(data_ov066_0226bdf0->unk_08 + ((int) (*(struct UnkStruct_02267cb0_2 { unsigned char pad_00[0x95]; unsigned char unk_95; } * *) &data_ov066_0226bdf4)->unk_95 << 4), 500);
        func_ov066_02267e00(0);
    }

    data_ov066_0226bdf0->unk_0C |= 2;
    data_ov066_0226bdf0->unk_0C &= ~1;

    if (arg0 != 0) {
        int q;

        OS_CancelAlarm((char *) data_ov066_0226bdf0 + 0x10);
        q = (arg0 * 33514) / 64;
        OS_SetAlarm((char *) data_ov066_0226bdf0 + 0x10, (long long) q, func_ov066_02267c74, 0);
    }

    func_ov066_02267c0c();
}

void func_ov066_02267c74(void)
{
    if ((*(UnkStruct_02267c74 * *) &data_ov066_0226bdf0)->flag) {
        return;
    }
    func_ov066_02267be0();
}

void func_ov066_02267c0c(void)
{
    (*(struct UnkStruct_02267c0c * *) &data_ov066_0226bdec)->unk_04 = 7;
    func_ov066_02267b58();
    func_ov066_02267740();
    (*(struct UnkStruct_02267c0c_2 * *) &data_ov066_0226bdf4)->unk_95 = (*(struct UnkStruct_02267c0c_2 * *) &data_ov066_0226bdf4)->unk_95 + 1;
    if ((*(struct UnkStruct_02267c0c_2 * *) &data_ov066_0226bdf4)->unk_95 >= (*(struct UnkStruct_02267c0c * *) &data_ov066_0226bdec)->unk_09) {
        (*(struct UnkStruct_02267c0c_2 * *) &data_ov066_0226bdf4)->unk_95 = 0;
    }
}

void func_ov066_02267be0(void)
{
    (*(UnkStruct_02267be0 * *) &data_ov066_0226bdf0)->unk_0C &= ~2;
    OS_CancelAlarm(&(*(UnkStruct_02267be0 * *) &data_ov066_0226bdf0)->unk_10);
}

void func_ov066_02267b58(void)
{
    struct UnkStruct_02267b58_4 *out = (*(struct UnkStruct_02267b58_2 * *) &data_ov066_0226bdf0)->first;
    (*(struct UnkStruct_02267b58 * *) &data_ov066_0226bdf4)->unk_8E = (unsigned char) func_ov066_02267db4((unsigned char) ((*(struct UnkStruct_02267b58 * *) &data_ov066_0226bdf4)->unk_95));
    out->unk_00 = (*(struct UnkStruct_02267b58_2 * *) &data_ov066_0226bdf0)->second;
    out->unk_04 = (*(struct UnkStruct_02267b58 * *) &data_ov066_0226bdf4)->unk_8E;
    out->unk_06 = (*(struct UnkStruct_02267b58_3 * *) &data_ov066_0226bdec)->unk_22;
    out->unk_08 = 0xff;
    out->unk_09 = 0xff;
    out->unk_0A = 0xff;
    out->unk_0B = 0xff;
    out->unk_0C = 0xff;
    out->unk_0D = 0xff;
}

void func_ov066_02267958(Peer *peer)
{
    Msg msg;

    DC_InvalidateRange((*(UnkStruct_02267958 * *) &data_ov066_0226bdf0)->link, 0xc0);

    if ((*(UnkStruct_02267958 * *) &data_ov066_0226bdf0)->link->state == 0) {
        if ((*(Flags * *) &data_ov066_0226bdec)->f4) {
            return;
        }
        func_ov066_0226a494((char *) (*(UnkStruct_02267958 * *) &data_ov066_0226bdf0)->objs + (*(UnkStruct_02267958_2 * *) &data_ov066_0226bdf4)->index * 16, 0xfa0, peer->name, 0xacce,
                            peer->tag, (*(UnkStruct_02267958 * *) &data_ov066_0226bdf0)->link);
        return;
    }

    if (((*(UnkStruct_02267958 * *) &data_ov066_0226bdf0)->link->flags & 1) == 0) {
        return;
    }

    MI_CpuCopy8((*(UnkStruct_02267958 * *) &data_ov066_0226bdf0)->link->data, &msg, 8);
    DC_StoreRange(&msg, 8);

    if (!func_ov066_0226783c((void *) peer, (struct Param *) (&msg))) {
        return;
    }

    func_ov066_0226a494((char *) (*(UnkStruct_02267958 * *) &data_ov066_0226bdf0)->objs + (*(UnkStruct_02267958_2 * *) &data_ov066_0226bdf4)->index * 16, 0xfa0, peer->name, msg.id,
                        peer->tag, (*(UnkStruct_02267958 * *) &data_ov066_0226bdf0)->link);

    if (!(*(Flags * *) &data_ov066_0226bdec)->f3) {
        return;
    }
    // msg.id is read again from the stack for each compare.
    if (*(volatile u16 *) &msg == 0xbd8a) {
        func_ov066_02267908();
        return;
    }
    if (*(volatile u16 *) &msg != 0x2348) {
        return;
    }
    if ((*(UnkStruct_02267958 * *) &data_ov066_0226bdf0)->f0) {
        return;
    }
    OS_CancelAlarm(&(*(UnkStruct_02267958 * *) &data_ov066_0226bdf0)->queue);
    OS_SetAlarm(&(*(UnkStruct_02267958 * *) &data_ov066_0226bdf0)->queue, (unsigned long long) 0x3d5dULL, (void (*)(void)) func_ov066_0226794c, 0);
    (*(UnkStruct_02267958 * *) &data_ov066_0226bdf0)->f0 = 1;
}

void func_ov066_0226794c(void *argument)
{
    func_ov066_02267908();
}

void func_ov066_02267908(void)
{
    (*(struct UnkStruct_02267908 * *) &data_ov066_0226bdf4)->unk_C0 |= 0x100;
    OS_CancelAlarm((char *) (*(char * *) &data_ov066_0226bdf0) + 0x3c);
    func_ov066_02267be0();
}

int func_ov066_0226783c(void *arg0, struct Param *p)
{
    struct UnkStruct_0226783c_3 *s = (*(struct UnkStruct_0226783c_3 * *) &data_ov066_0226bdec);

    if (s->b5) {
        if ((*(struct UnkStruct_0226783c * *) &data_ov066_0226bdf0)->unk_04->unk_44 != s->unk_28) {
            goto fail;
        }
    }
    if (s->b6) {
        if (p->unk_04 != (*(struct UnkStruct_0226783c_2 * *) &data_ov066_0226bdf4)->unk_95) {
            goto fail;
        }
    }
    if (s->b7) {
        if (p->unk_06 != 5) {
            goto fail;
        }
    }
    if ((*(struct UnkStruct_0226783c * *) &data_ov066_0226bdf0)->unk_6C != 0) {
        goto call_func;
    }
    return 1;
call_func:
    return (*(struct UnkStruct_0226783c * *) &data_ov066_0226bdf0)->unk_6C(arg0);
fail:
    return 0;
}

void *func_ov066_022677e0(unsigned int arg)
{
    if ((*(UnkStruct_022677e0 * *) &data_ov066_0226bdf0) == 0) {
        goto fail;
    }
    if (arg >= (*(UnkStruct_022677e0_2 * *) &data_ov066_0226bdec)->count) {
        goto fail;
    }
    return func_ov066_0226a434((*(UnkStruct_022677e0 * *) &data_ov066_0226bdf0)->base + (arg << 4));
fail:
    return 0;
}

int func_ov066_02267784(unsigned int idx, int arg)
{
    if ((*(struct ListStruct * *) &data_ov066_0226bdf0) != 0 && idx < (*(unsigned char * *) &data_ov066_0226bdec)[9]) {
        return func_ov066_0226a418((char *) (*(struct ListStruct * *) &data_ov066_0226bdf0)->entries + (idx << 4), arg);
    }
    return 0;
}

void func_ov066_02267740(void)
{
    int status = WM_StartScan((void (*)(void *)) func_ov066_022676a0, *(*(int * *) &data_ov066_0226bdf0));
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}

void func_ov066_022676a0(struct UnkStruct_022676a0_3 *self)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }
    if (self->unk_02 == 0) {
        u16 v = self->unk_08;
        if (v == 4) {
        } else if (v == 5) {
            func_ov066_02267958((Peer *) self);
        } else {
            return;
        }
        if ((*(struct UnkStruct_022676a0 * *) &data_ov066_0226bdf0)->flag) {
            func_ov066_02267c0c();
            return;
        }
        func_ov066_0226a404((*(struct UnkStruct_022676a0_2 * *) &data_ov066_0226bdf4)->unk_95 * 16 + (*(struct UnkStruct_022676a0 * *) &data_ov066_0226bdf0)->base);
        func_ov066_0226768c();
    } else {
        func_ov066_0226686c(self->unk_02);
    }
}

void func_ov066_0226768c(void)
{
    WM_EndScan((void (*)(void *)) (void (*)(void *)) func_ov066_0226763c);
}

void func_ov066_0226763c(Arg *arg)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }
    if (arg->field == 0) {
        (*(Target * *) &data_ov066_0226bdec)->field = 4;
        func_ov066_02266bf4();
        return;
    } else {
        func_ov066_0226686c(arg->field);
        return;
    }
}
