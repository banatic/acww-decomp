/* villager_talk_offers_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02029a98 @ 0x02029a98, 0x20c bytes, Thumb
 * func_02029a18 @ 0x02029a18, 0x80 bytes, Thumb
 * func_02029910 @ 0x02029910, 0x108 bytes, Thumb
 * func_020296f8 @ 0x020296f8, 0x218 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02029a98 {
    u8 pad_00[0x40];
    int unk_40;
    u8 pad1[0x164 - 0x44];
    int unk_164;
} UnkStruct_02029a98;

typedef struct Buf {
    u8 pad_00[0x20];
    u8 a;
    u8 b;
    u8 pad1[2];
} Buf;

typedef struct UnkStruct_02029a98_2 {
    u16 id;
    u8 name[0xc];
} UnkStruct_02029a98_2;

typedef struct Pair {
    int unk_00;
    int w1;
} Pair;

typedef struct UnkStruct_020296f8 {
    u8 pad_00[0x40];
    int unk_40;
    u8 pad1[0x164 - 0x44];
    int unk_164;
} UnkStruct_020296f8;

typedef struct UnkStruct_020296f8_2 {
    u16 id;
    u8 name[0xc];
} UnkStruct_020296f8_2;

extern int data_021c2df4;
extern int data_021c2cd4;
extern int data_021c2ecc;
extern int data_021c1e14;
extern int data_021c1d6c;
extern const Pair data_020d8e10;
extern void data_020c8928(void);
extern void data_020c8924(void);
extern int func_02029e78(unsigned short *);
extern void func_0201cfb4(UnkStruct_02029a98 *, Buf *);
extern void func_0201cf90(UnkStruct_02029a98 *, Buf *, int, int, int, void *);
extern void func_0201cf74(UnkStruct_02029a98 *, Buf *, int, void *, void *);
extern void func_0201cec8(UnkStruct_02029a98 *, Buf *);
extern void func_02015de4(UnkStruct_02029a98 *, UnkStruct_02029a98_2 *, int, int);
extern void *func_0202d9c4(UnkStruct_02029a98 *);
extern void func_0202da74(UnkStruct_02029a98 *, Pair);
extern void func_02068388(int, int);
extern int memcmp(const void *, const void *, int);
extern UnkStruct_02029a98_2 *func_0209bba0(void *);
extern UnkStruct_02029a98_2 *func_0209b908(int);
extern unsigned int func_0209b914(int);
extern void *func_020984e8(void);
extern UnkStruct_02029a98_2 *func_02099870(void *);
extern UnkStruct_02029a98_2 *func_0209bb70(void *);
extern int func_02099e9c(UnkStruct_02029a98_2 *);
extern int func_0209518c(UnkStruct_02029a98_2 *, UnkStruct_02029a98_2 *);
extern int func_02099f1c(int *, void *);
extern int func_02099734(int a);
extern u16 *func_02098f48(int h, int a);
extern int func_02098e8c(int h, int i);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_0209b878(void *p, unsigned char a);
extern int func_0209b8bc(void *p);
extern void func_0209b750(void *p, int a, unsigned char b);
extern int data_021c2eb4;
extern const int data_020d9f94;
extern const Pair data_020d8e20;
extern int func_02029e34(unsigned short *);
extern int func_02015dd4(UnkStruct_020296f8 *, int, u8 *, const void *, u8 *);
extern int func_020644cc(int);
extern int func_0209b850(int);

int func_02029a98(UnkStruct_02029a98 *ctx)
{
    int flag;
    UnkStruct_02029a98_2 *pb;
    int tmp;
    Buf buf;
    UnkStruct_02029a98_2 *pa;
    u8 idx;
    int ret;
    int t;
    UnkStruct_02029a98_2 *e;

    flag = 1;
    idx = 0;
    ret = 0;
    func_0201cfb4(ctx, &buf);
    switch ((int) func_0209bba0(func_0202d9c4(ctx))) {
        case 0:
            pa = func_0209b908(ctx->unk_164);
            pb = func_02099870(func_020984e8());
            if (pb->id != pa->id) {
                break;
            }
            if (memcmp(pb->name, pa->name, 0xc) != 0) {
                break;
            }
            if (func_0209518c(pb, pa) == 0) {
                break;
            }
            if (func_0209b914(ctx->unk_164) <= 1) {
                if (func_02099f1c(&tmp, (void *) func_02029e78) > 0) {
                    func_0201cf90(ctx, &buf, idx, 0x1b, 0x1b, &data_021c2df4);
                } else {
                    func_0201cf90(ctx, &buf, idx, 0x14, 0x14, &data_021c2cd4);
                }
            } else {
                e = func_0209bb70(func_0202d9c4(ctx));
                t = 0;
                if (e->id >= 0x11a8 && e->id <= 0x12a7) {
                    t = 1;
                }
                if (t != 0) {
                    if (func_02099e9c(func_0209bb70(func_0202d9c4(ctx))) != -1) {
                        func_0201cf90(ctx, &buf, idx, 0x1b, 0x1b, &data_021c2df4);
                    } else {
                        func_0201cf90(ctx, &buf, idx, 0x14, 0x14, &data_021c2cd4);
                    }
                } else {
                    func_0201cf90(ctx, &buf, 0, 0x14, 0x14, &data_021c2cd4);
                }
            }
            e = func_0209bb70(func_0202d9c4(ctx));
            t = 0;
            if (e->id >= 0x11a8 && e->id <= 0x12a7) {
                t = 1;
            }
            if (t != 0) {
                func_02015de4(ctx, func_0209bb70(func_0202d9c4(ctx)), 0, 7);
            }
            idx++;
            ret = 1;
            break;
        case 1:
            ret = 1;
            break;
        case 2:
            func_0201cf74(ctx, &buf, idx, (void *) data_020c8928, &data_021c2ecc);
            idx++;
            flag = 0;
            ret = 1;
            break;
    }
    if (ret == 1) {
        if (flag != 0) {
            func_0201cf74(ctx, &buf, idx, (void *) data_020c8928, &data_021c1e14);
            idx++;
        }
        func_0201cf74(ctx, &buf, idx, (void *) data_020c8924, &data_021c1d6c);
        idx++;
        buf.a = idx;
        buf.b = idx - 1;
        func_0201cec8(ctx, &buf);
        func_0202da74(ctx, data_020d8e10);
        func_02068388(ctx->unk_40, 1);
    }
    return ret;
}

u16 func_02029a18(u16 *key)
{
    int h;
    u16 *p;
    int i;
    u16 mask;
    unsigned int ok;
    int r;

    h = func_02099734((int) func_020984e8());
    p = func_02098f48(h, 0);
    mask = 0;
    for (i = 0; i < 15; i++) {
        if (func_02098e8c(h, i) == 0) {
            if (func_0204bcdc(p) != 0) {
                r = func_0204bc64(p);
                ok = (r == func_0204bc64(key)) ? 1 : 0;
            } else {
                ok = (*p == *key) ? 1 : 0;
            }
            if (ok != 0) {
                mask = mask | (1 << i);
            }
        }
        p++;
    }
    return mask;
}

static __inline int sameId(unsigned short *p, unsigned short *q)
{
    int v;
    v = func_0204bc64((u16 *) p);
    if (v == func_0204bc64((u16 *) q)) {
        return 1;
    }
    return 0;
}

static __inline int sameRaw(unsigned short *p, unsigned short *q)
{
    if (*p == *q) {
        return 1;
    }
    return 0;
}

unsigned short func_02029910(void *param)
{
    void *data;
    unsigned short *ptr;
    unsigned short arr[4];
    int flag1;
    unsigned short *ptr2;
    int flag2;
    unsigned short result;
    int i;
    int j;

    data = (void *) func_02099734((int) (func_020984e8()));
    ptr = (unsigned short *) func_02098f48((int) data, 0);
    arr[1] = 0xfff1;
    arr[2] = 0xfff1;
    arr[3] = 0xfff1;
    ptr2 = &arr[1];
    result = 0;

    for (i = 0; i < 3; i++) {
        if (func_0209b878(param, (unsigned char) i) == 0) {
            func_0209b750(arr, func_0209b8bc(param), (unsigned char) i);
            *(ptr2 + i) = arr[0];
        } else {
            *(ptr2 + i) = 0xfff1;
        }
    }

    flag1 = 0;
    flag2 = 0;

    for (i = 0; i < 15; ptr++, i++) {
        int ok;
        int found;
        if (func_02098e8c((int) data, i) != 0) {
            continue;
        }
        ok = flag1;
        if (((*ptr) >= 0x450c) && ((*ptr) <= 0x45db)) {
            ok = 1;
        }
        if (ok == 0) {
            continue;
        }
        for (j = flag2; j < 3; j++) {
            if (func_0204bcdc((u16 *) ptr) != 0) {
                found = sameId(ptr, ptr2 + j);
            } else {
                found = sameRaw(ptr, ptr2 + j);
            }
            if (found) {
                result = (unsigned short) (result | (1 << i));
                break;
            }
        }
    }

    return result;
}

int func_020296f8(UnkStruct_020296f8 *ctx)
{
    UnkStruct_020296f8_2 *pa;
    UnkStruct_020296f8_2 *pb;
    u8 arr[8];
    Buf buf;
    int flag;
    u8 idx;
    int ret;
    int v;

    flag = 1;
    idx = 0;
    ret = 0;
    func_0201cfb4((UnkStruct_02029a98 *) ctx, &buf);
    switch ((int) (UnkStruct_020296f8_2 *) func_0209bba0(func_0202d9c4((UnkStruct_02029a98 *) ctx))) {
        case 0:
            pa = (UnkStruct_020296f8_2 *) func_0209b908(ctx->unk_164);
            pb = (UnkStruct_020296f8_2 *) func_02099870(func_020984e8());
            if (pb->id != pa->id) {
                break;
            }
            if (memcmp(pb->name, pa->name, 0xc) != 0) {
                break;
            }
            if (func_0209518c((UnkStruct_02029a98_2 *) pb, (UnkStruct_02029a98_2 *) pa) == 0) {
                break;
            }
            if (func_0209b914(ctx->unk_164) <= 1) {
                if (func_02099f1c((int *) (&arr[2]), (void *) func_02029e34) > 0) {
                    func_0201cf90((UnkStruct_02029a98 *) ctx, &buf, idx, 0x1a, 0x1a, &data_021c2df4);
                } else {
                    func_0201cf90((UnkStruct_02029a98 *) ctx, &buf, idx, 0x14, 0x14, &data_021c2cd4);
                }
            } else if (func_0209b914(ctx->unk_164) >= 2) {
                if ((int) func_02029910((void *) ctx->unk_164) != 0) {
                    func_0201cf90((UnkStruct_02029a98 *) ctx, &buf, idx, 0x1a, 0x1a, &data_021c2df4);
                } else {
                    func_0201cf90((UnkStruct_02029a98 *) ctx, &buf, idx, 0x14, 0x14, &data_021c2cd4);
                }
            } else {
                func_0201cf90((UnkStruct_02029a98 *) ctx, &buf, idx, 0x14, 0x14, &data_021c2cd4);
            }
            if (func_0209b914(ctx->unk_164) >= 2) {
                v = func_0209b850(func_0209b8bc((void *) ctx->unk_164));
                if (v != -1) {
                    arr[0] = (u8) v;
                    arr[1] = 0;
                    func_02015dd4(ctx, 0, arr, &data_020d9f94, &arr[1]);
                }
            }
            idx++;
            ret = 1;
            break;
        case 1:
            if (func_020644cc(10) & 1) {
                func_0201cf74((UnkStruct_02029a98 *) ctx, &buf, idx, (void *) data_020c8928, &data_021c2eb4);
                flag = 0;
                idx++;
            }
            ret = 1;
            break;
        case 2:
            func_0201cf74((UnkStruct_02029a98 *) ctx, &buf, idx, (void *) data_020c8928, &data_021c2ecc);
            idx++;
            flag = 0;
            ret = 1;
            break;
    }
    if (ret == 1) {
        if (flag != 0) {
            func_0201cf74((UnkStruct_02029a98 *) ctx, &buf, idx, (void *) data_020c8928, &data_021c1e14);
            idx++;
        }
        func_0201cf74((UnkStruct_02029a98 *) ctx, &buf, idx, (void *) data_020c8924, &data_021c1d6c);
        idx++;
        buf.a = idx;
        buf.b = idx - 1;
        func_0201cec8((UnkStruct_02029a98 *) ctx, &buf);
        func_0202da74((UnkStruct_02029a98 *) ctx, data_020d8e20);
        func_02068388(ctx->unk_40, 1);
    }
    return ret;
}
