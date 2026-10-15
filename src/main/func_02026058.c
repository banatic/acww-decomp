/* func_02026058 @ 0x02026058, 0x158 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02026058 {
    char pad_00[0x124];
    u16 unk_124;
    char pad_126[0x3e];
    int unk_164;
};

struct Loc {
    u8 unk_00;
    u8 unk_01;
    u16 h1;
    u16 h2;
};

extern int data_020d9f94;
struct Pair {
    int a;
    int b;
};
extern struct Pair data_020d9388;
extern void func_0202db48(struct UnkStruct_02026058 *a, struct Pair p);

extern int func_0209b91c(int a);
extern int func_0209bd44(int a);
extern int func_0209b914(int a);
extern void func_0209e474(void *p);
extern void *func_0202d9c4(struct UnkStruct_02026058 *a);
extern int func_0209bc40(void *a);
extern void func_02015de4(struct UnkStruct_02026058 *a, void *b, int c, int d);
extern void func_020261b0(u16 *out, struct UnkStruct_02026058 *a, int v);
extern void func_020263b0(u16 *out, struct UnkStruct_02026058 *a, int v);
extern int func_0209b8bc(int a);
extern int func_020535f0(u16 *p);
extern int func_0209b850(int);
extern int func_02015dd4(struct UnkStruct_02026058 *a, int b, void *c, void *d, void *e);

void func_02026058(struct UnkStruct_02026058 *self)
{
    struct Loc loc;
    int buf[2];
    int v;
    int n;
    int f;
    int x;

    v = 0;
    buf[0] = v;
    buf[1] = v;
    if (func_0209bd44(func_0209b91c(self->unk_164)) != 0) {
        v = func_0209b914(self->unk_164);
    }
    func_0209e474(buf);
    switch (func_0209bc40(func_0202d9c4(self))) {
        case 0:
            if (self->unk_124 != 0xfff1) {
                func_02015de4(self, &self->unk_124, 0, 7);
            }
            break;
        case 1:
            if (self->unk_124 != 0xfff1) {
                func_02015de4(self, &self->unk_124, 0, 7);
            }
            break;
        case 2:
            if (self->unk_124 == 0xfff1) {
                func_020261b0(&loc.h1, self, v);
                self->unk_124 = loc.h1;
            }
            if (v < 2) {
                break;
            }
            n = func_0209b8bc(self->unk_164);
            if (n >= 0x18) {
                f = 0;
                if (self->unk_124 >= 0x450c && self->unk_124 <= 0x45db) {
                    f = 1;
                }
                if (f != 0) {
                    n = func_020535f0(&self->unk_124);
                }
            }
            if (n < 0x18) {
                x = func_0209b850(n);
                if (x != -1) {
                    loc.unk_00 = x;
                    loc.unk_01 = 0;
                    func_02015dd4(self, 0, &loc, &data_020d9f94, &loc.unk_01);
                }
            }
            break;
        case 3:
            if (self->unk_124 == 0xfff1) {
                func_020263b0(&loc.h2, self, v);
                self->unk_124 = loc.h2;
            }
            if (self->unk_124 != 0xfff1) {
                func_02015de4(self, &self->unk_124, 0, 7);
            }
            break;
        case 4:
            break;
    }
    func_0202db48(self, data_020d9388);
}
