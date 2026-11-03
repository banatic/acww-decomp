/* villager_talk_part_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02026ab4 @ 0x02026ab4, 0xb0 bytes, Thumb
 * func_02026a1c @ 0x02026a1c, 0x98 bytes, Thumb
 */

#include "types.h"

struct Global {
    u32 unk_00;
    u8 unk_04;
};

struct UnkStruct_02026ab4 {
    u8 pad_00[0x100];
    u8 *ptr830;
    u8 unk_104[0x1e];
    u8 unk_122;
    u8 pad_123;
    u16 hword124;
    u8 pad_126[0x1a0 - 0x126];
    u32 unk_1A0;
};

struct UnkStruct_02026ab4_2 {
    char *ptr;
    u8 byte;
};

extern struct Global data_020c8d90;
extern void func_02015f38(struct UnkStruct_02026ab4 *self, int word, int a2, int a3, int a4, int a5, int a6);
extern void func_02015de4(struct UnkStruct_02026ab4 *self, void *ptr, int a2, int a3);
extern int func_0208150c(int arg);
extern int func_020036e8(int arg);
extern int func_0202da38(void *self, void *p1, void *p2, int len, int a5, int a6, int a7, int a8, int a9);
extern void *func_020984e8(void);
extern void *func_02099734(void *);
extern void func_02098a24(void *, int, int);
extern int func_02098eb8(void *);
extern int func_02098f0c(void *, void *, int, int);
extern void *func_020996ac(void *);
extern int func_0203cd2c(void *, void *, int, int);
extern int func_020154b4(void *, void *, int, int, int);

void func_02026ab4(struct UnkStruct_02026ab4 *self, struct UnkStruct_02026ab4_2 *out)
{
    int flag = 0;
    int r;
    u16 val;

    val = self->hword124;
    if (val >= 0x1492u && val <= 0x14fdu) {
        flag = 1;
    }

    if (flag) {
        func_02015f38(self, self->unk_1A0, 1, 4, 1, 0, 0);
    } else {
        func_02015de4(self, (char *) &self->hword124, 1, 7);
    }

    r = func_020036e8(func_0208150c(*(u32 *) (self->ptr830 + 0x830)));

    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 0x1e, r, data_020c8d90.unk_00, data_020c8d90.unk_04, 0,
                  0);

    out->ptr = (char *) self + 0x104;
    out->byte = self->unk_122;
}

void func_02026a1c(void *obj)
{
    void *h, *ctx;
    unsigned int ok;
    unsigned short v;
    int rc;

    h = func_020984e8();
    ctx = func_02099734(h);
    ok = 0;
    v = *(unsigned short *) ((char *) obj + 0x124);
    if (v >= 0x1492 && v <= 0x14fd) {
        ok = 1;
    }
    if (ok > 0) {
        func_02098a24(ctx, *(int *) ((char *) obj + 0x1a0), 1);
    } else if (v != 0xfff1) {
        rc = func_02098eb8(ctx);
        if (rc != -1) {
            func_02098f0c(ctx, (char *) obj + 0x124, rc, 0);
            func_0203cd2c(func_020996ac(h), (char *) obj + 0x124, 0, 1);
        }
    }
    func_020154b4(obj, (char *) obj + 0x124, 0, 5, 0);
}
