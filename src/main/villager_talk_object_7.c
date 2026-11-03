/* villager_talk_object_7: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02025c48 @ 0x02025c48, 0x90 bytes, Thumb
 * func_02025bf8 @ 0x02025bf8, 0x50 bytes, Thumb
 */

#include "types.h"

#define Predicate_0202a17c ((int (*)(unsigned short *, int)) func_0202a17c)
#define Predicate_0202a12c ((int (*)(unsigned short *, int)) func_0202a12c)

struct Pair {
    u32 lo;
    u32 hi;
};

struct UnkStruct_02025c48 {
    u8 pad_00[0x830];
    u32 unk_830;
};

struct UnkStruct_02025c48_2 {
    u8 pad_00[0x100];
    struct UnkStruct_02025c48 *ptr; // 0x100
    u8 unk_104[0x1E];               // 0x104
    u8 unk_122;                     // 0x122
    u8 pad_123[0x41];               // 0x123
    u32 unk_164;                    // 0x164
};

struct UnkStruct_02025c48_3 {
    u8 *ptr;
    u8 byte;
};

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

extern struct Pair data_020d92f8;
extern u32 data_020d9dd4[];
extern int func_0209b914(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(struct UnkStruct_02025c48_2 *, u8 *, u8 *, int, int, int offset, int scale, int, int);
extern int func_0202d9c4(int arg);
extern int func_0209bc40(int value);
extern void func_020157d4(void *, int (*)(unsigned short *, int), unsigned char, unsigned char);
extern int func_02015828(int arg, int a);
extern Pair data_020d92f0;
extern void func_0202dbf0(int arg, Pair value);
extern unsigned short func_0202a17c(unsigned short *, int);
extern unsigned short func_0202a12c(unsigned short *, int);

void func_02025c48(struct UnkStruct_02025c48_2 *a, struct UnkStruct_02025c48_3 *out)
{
    struct Pair d = data_020d92f8;
    int idx = func_0209b914(a->unk_164);
    if (idx < 7) {
        d.lo = data_020d9dd4[idx];
    }
    if (d.lo != 0) {
        int x = func_020036e8(func_0208150c(a->ptr->unk_830));
        func_0202da38(a, a->unk_104, &a->unk_122, 0x1e, x, d.lo, ((u8 *) &d)[4], 0, 0);
    }
    out->ptr = a->unk_104;
    out->byte = a->unk_122;
}

void func_02025bf8(int arg)
{
    if (func_0209bc40(func_0202d9c4(arg)) == 0) {
        func_020157d4((void *) arg, Predicate_0202a17c, 13, 1);
    } else {
        func_020157d4((void *) arg, Predicate_0202a12c, 13, 1);
    }
    func_02015828(arg, 0);
    func_0202dbf0(arg, data_020d92f0);
}
