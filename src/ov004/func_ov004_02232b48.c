/* func_ov004_02232b48 @ 0x02232b48, 0x100 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02232b48 {
    char pad_00[0x20];
    int unk_20;
};
struct UnkStruct_02232b48_2 {
    char pad_00[0x20];
    struct UnkStruct_02232b48 *unk_20;
};
struct UnkStruct_02232b48_3 {
    struct UnkStruct_02232b48_2 *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

extern struct UnkStruct_02232b48_3 *data_021c80bc;

extern void func_ov004_02232980(void *a, int b, int c);
extern void func_ov004_022326f4(void *a, int b, int c);
extern void func_ov004_02232c48(void *self, volatile u16 *a, int *b, volatile u16 *c, int *d);
extern void func_ov004_02232968(void *a, int b, int c, int d);
extern void func_ov004_022326dc(void *a, int b, int c, int d);
extern void func_ov004_022327a0(void *a, volatile u16 *b, int c, int d);
extern void func_ov004_02232514(void *a, volatile u16 *b, int c, int d);

static __inline int atleast(unsigned int x, unsigned int n)
{
    return x > n;
}

static __inline struct UnkStruct_02232b48_2 *get(void)
{
    struct UnkStruct_02232b48_3 *g = data_021c80bc;

    if (!atleast(g->unk_04, 0) || !atleast(g->unk_08, 0) || g->unk_00 == 0) {
        return 0;
    }
    return g->unk_00;
}

void func_ov004_02232b48(char *self)
{
    // DECLS
    int ok;
    unsigned int lo;
    unsigned int hi;
    struct UnkStruct_02232b48 *r;
    // ENDDECLS
    volatile u16 buf[2];
    int v8;
    int v12;

    r = get()->unk_20;
    func_ov004_02232980(self + 0x128, *(int *) (self + 0xac), r->unk_20);
    func_ov004_022326f4(self + 0x1228, *(int *) (self + 0xac), r->unk_20);
    buf[0] = 0xfff1;
    buf[1] = 0xfff1;
    func_ov004_02232c48(self, &buf[0], &v8, &buf[1], &v12);

    ok = 0;
    lo = buf[0];
    hi = buf[0];
    if (hi >= 0x1188 && lo <= 0x11a7) {
        ok = 1;
    }
    if (ok != 0) {
        func_ov004_02232968(self + 0x128, 0x1124, *(int *) (self + 0xac), v8);
    }
    ok = 0;
    lo = buf[1];
    hi = buf[1];
    if (hi >= 0x1188 && lo <= 0x11a7) {
        ok = 1;
    }
    if (ok != 0) {
        func_ov004_022326dc(self + 0x1228, 0x1182, *(int *) (self + 0xac), v12);
    }
    func_ov004_022327a0(self + 0x128, &buf[0], *(int *) (self + 0xac), v8);
    func_ov004_02232514(self + 0x1228, &buf[1], *(int *) (self + 0xac), v12);
}
