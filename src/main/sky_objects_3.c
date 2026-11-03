/* sky_objects_3: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020be400 @ 0x020be400, 0x150 bytes, Thumb
 * func_020be388 @ 0x020be388, 0x78 bytes, Thumb
 * func_020be348 @ 0x020be348, 0x40 bytes, Thumb
 * func_020be2d4 @ 0x020be2d4, 0x74 bytes, Thumb
 * func_020be1c4 @ 0x020be1c4, 0x110 bytes, Thumb
 * func_020be160 @ 0x020be160, 0x64 bytes, Thumb
 * func_020be0f8 @ 0x020be0f8, 0x68 bytes, Thumb
 * func_020be0d4 @ 0x020be0d4, 0x22 bytes, Thumb
 * func_020be0a8 @ 0x020be0a8, 0x2c bytes, Thumb
 * func_020be0a0 @ 0x020be0a0, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u8 unk_08;
    u8 unk_09;
} Elem;

typedef struct {
    int unk_00;
    int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char pad_0A[2];
} UnkStruct_020be2d4;

typedef struct {
    char pad_00[0x1b30];
    UnkStruct_020be2d4 arr[5];
    char sub[0x134c];
    char other;
} UnkStruct_020be2d4_2;

typedef struct UnkStruct_020be1c4_3 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_020be1c4_3;

typedef struct UnkStruct_020be1c4 {
    u8 pad_00[0x1b30];
    UnkStruct_020be1c4_3 arr[5];
} UnkStruct_020be1c4;

typedef struct UnkStruct_020be1c4_2 {
    int m;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_020be1c4_2;

typedef struct Record {
    int id;
    unsigned char pad_04[0x70];
} Record;

struct UnkStruct_020be0a8 {
    char pad_00[0x2f24];
    char flag;
};

extern void func_020bef78(void *p);
extern void *func_020bedf4(void *p);
extern void *func_020bebc8(void *p);
extern void *func_020be64c(void *p);
extern void func_020bf1b8(void *p);
extern void *func_020be554(void *);
extern void func_020be550(void *);
extern void *func_020bf9ac(void *);
extern void *func_020bec04(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern int func_020bec70(char *arg0, int arg1);
extern int func_020bf064(char *arg0, int arg1);
extern void func_020bee9c(char *arg0, char *arg1);
extern void func_020bed64(char *arg0, char *arg1, int arg2);
extern UnkStruct_020be1c4_2 data_020d2bb4[];
extern void func_020be000(struct UnkStruct_020be0a8 *obj);
extern void func_020bdb24(struct UnkStruct_020be0a8 *obj);
extern void func_020bd688(struct UnkStruct_020be0a8 *obj);
extern void func_020bd054(struct UnkStruct_020be0a8 *obj);
extern void func_020bdbe0(void *);

void *func_020be400(void *self)
{
    u8 *base = (u8 *) self;
    u8 *p, *end;

    __cxa_vec_ctor((void *) (self), 0x3c, 0x74, (((void (*)(void *)) func_020bf9ac)), (((void (*)(void *)) func_020be554)));

    p = base + 0x1b30;
    end = base + 0x1b6c;
    do {
        func_020bef78(p);
        p += 12;
    } while (p != end);

    func_020bedf4(base + 0x2eb8);

    __cxa_vec_ctor((void *) (base + 0x2f58), 4, 0x14, (((void (*)(void *)) func_020bec04)), (void (*)(void *)) func_020be550);

    func_020bebc8(base + 0x2fa8);
    func_020be64c(base + 0x2fcc);

    *(u32 *) (base + 0x2f00) = 0;
    *(u32 *) (base + 0x2f04) = 0;
    *(u32 *) (base + 0x2f08) = 0;
    *(u32 *) (base + 0x2f0c) = 0;
    *(u32 *) (base + 0x2f10) = 0;
    *(u32 *) (base + 0x2f14) = 0;

    *(u8 *) (base + 0x2f24) = 0;
    *(u8 *) (base + 0x2f25) = 0;
    *(u8 *) (base + 0x2f26) = 0;
    *(u8 *) (base + 0x2f27) = 0;
    *(u8 *) (base + 0x2f28) = 0;
    *(u8 *) (base + 0x2f29) = 0;

    *(u32 *) (base + 0x2f2c) = 0;
    *(u32 *) (base + 0x2f30) = 0;
    *(u32 *) (base + 0x2f34) = 0;
    *(u32 *) (base + 0x2f38) = 0;
    *(u32 *) (base + 0x2f3c) = 0;
    *(u32 *) (base + 0x2f40) = 0;
    *(u32 *) (base + 0x2f44) = 0;
    *(u32 *) (base + 0x2f48) = 0;
    *(u32 *) (base + 0x2f4c) = 0;

    *(u8 *) (base + 0x2f50) = 0;
    *(u8 *) (base + 0x2f51) = 0;

    *(u32 *) (base + 0x2f54) = 0;

    func_020bf1b8(base + 0x1b6c);

    return self;
}

void func_020be388(char *base)
{
    char *p;
    char *end;
    int val, ret;
    unsigned char b;

    end = base + 0x1b6c;
    for (p = base + 0x1b30; p < end; p += 12) {
        val = *(int *) p;
        if (val == 52) {
            continue;
        }
        b = *(unsigned char *) (p + 8);
        ret = func_020bec70(base + 0x2eb8, val);
        if (b == 0) {
            func_020bf064(base + 0x1b6c, val);
            func_020bee9c(p, base + 0x1b6c);
            *(unsigned char *) (p + 8) = 1;
            *(unsigned char *) (p + 9) = 0;
        }
        if (ret == 0) {
            func_020bed64(base + 0x2eb8, base + 0x1b6c, val);
        }
    }
}

void func_020be348(u8 *base)
{
    Elem *end = (Elem *) (base + 0x1b6c);
    Elem *p = (Elem *) (base + 0x1b30);

    while (p < end) {
        u32 f0 = p->unk_00;
        u8 f9 = p->unk_09;

        if (f9 != 0) {
            if (f0 == 0x34) {
                p->unk_09 = 0;
            } else if (p->unk_08 == 0) {
                func_020bf064((char *) end, f0);
            }
        }
        p++;
    }
}

void func_020be2d4(UnkStruct_020be2d4_2 *self, void *arg)
{
    UnkStruct_020be2d4 *end;
    UnkStruct_020be2d4 *e;
    int v;
    int r;
    int flag;

    end = &self->arr[5];
    e = self->arr;
    while (e < end) {
        v = e->unk_00;
        if (e->unk_09 != 0) {
            if (v != 0x34) {
                flag = e->unk_08;
                r = func_020bec70((char *) (&self->other), v);
                if (flag == 0) {
                    func_020bee9c((char *) e, (char *) self->sub);
                    e->unk_08 = 1;
                }
                if (r == 0) {
                    func_020bed64((char *) (&self->other), (char *) self->sub, v);
                }
            }
            e->unk_09 = 0;
        }
        e++;
    }
}

int func_020be1c4(UnkStruct_020be1c4 *p, int i)
{
    int mode;
    int ok;
    int a;
    int b;
    int c;
    int d;
    int e;

    mode = data_020d2bb4[i].m;
    ok = 0;
    if (mode == 6) {
        ok = 1;
    } else if (i == p->arr[mode].unk_00) {
        ok = 1;
    } else {
        a = (p->arr[0].unk_04 > 0);
        b = (p->arr[1].unk_04 > 0);
        c = (p->arr[2].unk_04 > 0);
        d = (p->arr[3].unk_04 > 0);
        e = (p->arr[4].unk_04 > 0);
        if (mode == 0) {
            ok = (!a && !d);
        } else if (mode == 1) {
            ok = (!b && !e);
        } else if (mode == 2) {
            ok = (!c && !d && !e);
        } else if (mode == 3) {
            ok = (!d && !a && !c && !e);
        } else if (mode == 4) {
            ok = (!e && !b && !c && !d);
        }
    }
    if (!ok) {
        return 5;
    }
    return mode;
}

void func_020be160(void *r0, int r1)
{
    if (r1 == 0) {
        *(int *) ((char *) r0 + 0x1b54) = 0x34;
        return;
    }
    if (r1 == 1) {
        *(int *) ((char *) r0 + 0x1b60) = 0x34;
        return;
    }
    if (r1 == 2) {
        *(int *) ((char *) r0 + 0x1b54) = 0x34;
        *(int *) ((char *) r0 + 0x1b60) = 0x34;
        return;
    }
    if (r1 == 3) {
        *(int *) ((char *) r0 + 0x1b30) = 0x34;
        *(int *) ((char *) r0 + 0x1b48) = 0x34;
        *(int *) ((char *) r0 + 0x1b60) = 0x34;
        return;
    }
    if (r1 == 4) {
        *(int *) ((char *) r0 + 0x1b3c) = 0x34;
        *(int *) ((char *) r0 + 0x1b48) = 0x34;
        *(int *) ((char *) r0 + 0x1b54) = 0x34;
    }
}

int func_020be0f8(Record *records, int param1, int param2)
{
    int val;
    int result = 0x3c;
    if (param2 != 0x3c) {
        if (records[param2].id == 0xd) {
            result = param2;
        }
    } else if (param1 == 9) {
        Record *p = (Record *) (((char *) records) + 0x14d8);
        int i;
        i = 0x2e;
        while (i <= 0x3a) {
            if (p->id == 0xd) {
                result = i;
                break;
            }
            i++;
            p = (Record *) (((char *) p) + 0x74);
        }

    } else {
        int j;
        Record *q = records;
        if ((*((int *) (((char *) records) + 0x2f14))) < 0x1e) {
            for (j = 0; j < 0x1e; j++) {
                val = q->id == 0xd;
                if (val) {
                    result = j;
                    break;
                }
                q = (Record *) (((char *) q) + 0x74);
            }
        }
    }
    return result;
}

int func_020be0d4(void *param1, int param2)
{
    int r4;
    int r3;
    int r0;

    r4 = 0x3c;
    r3 = 0;
    r0 = (int) param1;

    while (r3 < 0x3c) {
        if (param2 == *(int *) r0) {
            r4 = r3;
            break;
        }
        r3++;
        r0 += 0x74;
    }

    return r4;
}

void func_020be0a8(struct UnkStruct_020be0a8 *obj)
{
    func_020be000(obj);
    func_020bdb24(obj);
    func_020bd688(obj);
    func_020bd054(obj);
    obj->flag = 0;
}

void func_020be0a0(void *argument0)
{
    func_020bdbe0((void *) argument0);
}
