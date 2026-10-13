/* func_02029a98 @ 0x02029a98, 0x20c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

extern int data_021c2df4;
extern int data_021c2cd4;
extern int data_021c2ecc;
extern int data_021c1e14;
extern int data_021c1d6c;
extern const Pair data_020d8e10;
extern void data_020c8928(void);
extern void data_020c8924(void);
extern void func_02029e78(void);

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
