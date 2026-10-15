/* func_02010424 @ 0x02010424, 0x114 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x500];
    u8 unk_500[0x59c - 0x500];
    u8 unk_59C[0xc8c - 0x59c];
    int unk_C8C;
    u16 unk_C90;
} UnkStruct_02010424;

extern u32 data_020cc7cc;
extern u32 data_020cc7d0;

extern int func_0205e0a4(int);
extern int func_0204bd84(volatile u16 *);
extern int func_0204bfa0(volatile u16 *);
extern int func_0205e098(int);
extern void func_0205de94(void *, int);
extern int func_0205ddd4(void *);
extern void func_020103e4(UnkStruct_02010424 *);
extern void func_0205de70(void *);
extern void func_0205dec8(void *);
extern int func_02055454(void *);
extern int func_0205de10(void *);
extern void func_020554b0(void *, int);
extern int func_0205de24(void *);

static __inline int idxA(u16 v)
{
    return (v >= 0x1431 && v <= 0x1470) ? v - 0x1431 : -1;
}

void func_02010424(UnkStruct_02010424 *p)
{
    volatile u16 h;
    int kind;
    int idx;
    int ok;
    u16 v;

    if (p->unk_C8C != 0) {
        return;
    }
    kind = 0x4b;
    h = p->unk_C90;
    ok = 0;
    v = h;
    if (h >= 0x1431 && v <= 0x1470) {
        ok = 1;
    }
    if (ok) {
        idx = idxA(v);
        if (idx >= 0 && idx < data_020cc7cc) {
            kind = func_0205e0a4(idx);
        }
    } else {
        if (v >= 0x1471 && v <= 0x1491) {
            if (func_0204bd84(&h)) {
                idx = func_0204bfa0(&h);
                if (idx >= 0 && idx < data_020cc7d0) {
                    kind = func_0205e098(idx);
                }
            }
        }
    }
    func_0205de94(p->unk_59C, kind);
    if (func_0205ddd4(p->unk_59C) != 0x4b) {
        func_0205de70(p->unk_59C);
        func_0205dec8(p->unk_59C);
        func_02055454(p->unk_500);
        func_020554b0(p->unk_500, func_0205de10(p->unk_59C));
        func_0205de24(p->unk_59C);
        p->unk_C8C = 1;
    } else {
        p->unk_C8C = 1;
        func_020103e4(p);
    }
}
