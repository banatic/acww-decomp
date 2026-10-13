/* func_020991d4 @ 0x020991d4, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct LocalInfo {
    u8 pad_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03;
};

extern char data_021dc7a8[];

void *func_020984e8(void);
void func_0209df64(void *);
struct LocalInfo *func_02099308(void *);
int func_0209dcdc(struct LocalInfo *, struct LocalInfo *);
void func_020982f8(int);
void func_020981f4(int);
void func_020980f0(int);
void func_02099670(void *);
void func_02088810(void);
void func_020889a8(void);
void func_0209948c(void *);
int func_020992ac(void *);
void func_020992b8(void *, int);
void func_0209967c(void *);
void func_020887f8(void);
void func_02099768(void *, int);
void func_02088ac8(void);
void func_0209f100(void *, int);
void *func_02099688(void *);
void func_020882f0(void *);

void func_020991d4(void)
{
    struct LocalInfo local;
    char *base;
    void *self;
    struct LocalInfo *p6;
    int r4;

    base = (char *) &data_021dc7a8;
    self = func_020984e8();
    if (self == 0) {
        return;
    }

    func_0209df64(&local);
    p6 = func_02099308(self);
    r4 = func_0209dcdc(&local, p6);

    func_020982f8((local.unk_01 - p6->unk_01) + 12 * (local.unk_02 - p6->unk_02));

    func_020981f4(r4);
    func_020980f0(r4);
    func_02099670(self);
    func_02088810();
    func_02099670(self);
    func_020889a8();

    if (r4 != 0) {
        func_0209948c(self);
    }

    if (local.unk_02 != func_020992ac(self)) {
        func_020992b8(self, 0xff);
    }

    if (r4 != 0) {
        func_0209967c(self);
        func_020887f8();
        func_02099768(self, 0);
        func_02099670(self);
        func_02088ac8();
        func_0209f100(&data_021dc7a8, 0x10);
    }

    if (r4 < 0) {
        func_020882f0(func_02099688(self));
        func_020882f0(base + 0x173e2);
    }

    func_0209df64(func_02099308(self));
}
