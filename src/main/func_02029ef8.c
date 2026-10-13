/* func_02029ef8 @ 0x02029ef8, 0x234 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02029ef8 {
    u8 pad_00[0x40];
    int unk_40;
    u8 pad1[0x164 - 0x44];
    int unk_164;
} UnkStruct_02029ef8;

typedef struct Buf {
    u8 pad_00[0x20];
    u8 a;
    u8 b;
    u8 pad1[2];
} Buf;

typedef struct UnkStruct_02029ef8_2 {
    u16 id;
    u8 name[0xc];
} UnkStruct_02029ef8_2;

typedef struct Pair {
    int unk_00;
    int w1;
} Pair;

extern int data_021c2d04;
extern int data_021c2cd4;
extern int data_021c2d7c;
extern int data_021c2eb4;
extern int data_021c2ecc;
extern int data_021c1e14;
extern int data_021c1d6c;
extern const Pair data_020d9438;
extern void data_020c8928(void);
extern void data_020c8924(void);

extern void func_0201cfb4(UnkStruct_02029ef8 *, Buf *);
extern void func_0201cf90(UnkStruct_02029ef8 *, Buf *, int, int, int, void *);
extern void func_0201cf74(UnkStruct_02029ef8 *, Buf *, int, void *, void *);
extern void func_0201cec8(UnkStruct_02029ef8 *, Buf *);
extern void func_02015de4(UnkStruct_02029ef8 *, UnkStruct_02029ef8_2 *, int, int);
extern void *func_0202d9c4(UnkStruct_02029ef8 *);
extern void func_0202da74(UnkStruct_02029ef8 *, Pair);
extern void func_02068388(int, int);
extern int func_020644cc(int);
extern int memcmp(const void *, const void *, int);
extern UnkStruct_02029ef8_2 *func_0209bba0(void *);
extern UnkStruct_02029ef8_2 *func_0209b908(int);
extern int func_0209b914(int);
extern int func_0209b8c4(int);
extern void *func_020984e8(void);
extern UnkStruct_02029ef8_2 *func_02099870(void *);
extern int func_0209518c(UnkStruct_02029ef8_2 *, UnkStruct_02029ef8_2 *);
extern UnkStruct_02029ef8_2 *func_0209bb70(void *);
extern int func_02099e9c(UnkStruct_02029ef8_2 *);
extern int func_02099f1c(int *, int (*)(int));

int func_02029ef8(UnkStruct_02029ef8 *ctx, int (*fn)(int), int p2, int p3)
{
    int flag;
    UnkStruct_02029ef8_2 *pa;
    UnkStruct_02029ef8_2 *pb;
    int tmp;
    u8 idx;
    int ret;
    Buf buf;

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
            if (func_0209b914(ctx->unk_164) == 2) {
                if (fn(func_0209b8c4(ctx->unk_164)) != 0 && func_02099f1c(&tmp, fn) > 0) {
                    func_0201cf90(ctx, &buf, idx, p2, p2, &data_021c2d04);
                } else {
                    func_0201cf90(ctx, &buf, 0, 0x14, 0x14, &data_021c2cd4);
                }
            } else {
                if (fn((int) func_0209bb70(func_0202d9c4(ctx))) != 0) {
                    if (func_02099e9c(func_0209bb70(func_0202d9c4(ctx))) != -1) {
                        func_0201cf90(ctx, &buf, idx, p3, p3, &data_021c2d7c);
                    } else {
                        func_0201cf90(ctx, &buf, idx, 0x14, 0x14, &data_021c2cd4);
                    }
                } else {
                    func_0201cf90(ctx, &buf, idx, 0x14, 0x14, &data_021c2cd4);
                }
            }
            if (func_0209bb70(func_0202d9c4(ctx))->id != 0xfff1) {
                func_02015de4(ctx, func_0209bb70(func_0202d9c4(ctx)), 0, 7);
            }
            idx++;
            ret = 1;
            break;
        case 1:
            if (func_020644cc(10) & 1) {
                func_0201cf74(ctx, &buf, idx, (void *) data_020c8928, &data_021c2eb4);
                flag = 0;
                idx++;
            }
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
        func_0202da74(ctx, data_020d9438);
        func_02068388(ctx->unk_40, 1);
    }
    return ret;
}
