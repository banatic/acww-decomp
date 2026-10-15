/* func_02005490 @ 0x02005490, 0x27c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    u8 pad_00[0x24];
    Vec p;
} UnkStruct_02005490;

extern void func_02055d38(UnkStruct_02005490 *d, u8 k);
extern void func_02054848(UnkStruct_02005490 *d, int n);
extern int func_02055d0c(UnkStruct_02005490 *d, UnkStruct_02005490 *s, int n);
extern int func_0203f7d0(Vec *d, Vec *s);
extern void func_02055e7c(UnkStruct_02005490 *d, int n);
extern int func_0205e138(UnkStruct_02005490 *d, int n);
extern int func_0205ddd4(UnkStruct_02005490 *d);
extern void func_020acbc8(Vec *d, int n);
extern int func_0200f290(u8 *self, int n);
extern void func_0205e954(UnkStruct_02005490 *d, UnkStruct_02005490 *s);
extern int func_0200fbe0(u8 *self);
extern void func_0205e8f8(UnkStruct_02005490 *d, UnkStruct_02005490 *s, int n);
extern UnkStruct_02005490 data_021cfe68;

void func_02005490(u8 *self)
{
    UnkStruct_02005490 buf;
    Vec v;
    Vec w;
    Vec slot;
    UnkStruct_02005490 m1;
    UnkStruct_02005490 m2;
    int mode;

    data_021cfe68 = *(UnkStruct_02005490 *) (self + 0x298);
    func_02055d38((UnkStruct_02005490 *) (self + 0x234), self[0x8e9]);
    func_02054848((UnkStruct_02005490 *) (self + 0x234), 0);
    func_02055d0c((UnkStruct_02005490 *) (self + 0x234), (UnkStruct_02005490 *) (self + 0x42c), 0xf);
    func_02055d0c((UnkStruct_02005490 *) (self + 0x234), (UnkStruct_02005490 *) (self + 0x668), 0xe);
    func_02055d0c((UnkStruct_02005490 *) (self + 0x234), (UnkStruct_02005490 *) (self + 0x698), 0xb);
    func_02055d0c((UnkStruct_02005490 *) (self + 0x234), &buf, 7);
    v.x = buf.p.x;
    v.y = buf.p.y;
    v.z = buf.p.z;
    func_0203f7d0((Vec *) (self + 0x6c8), &v);
    func_02055d0c((UnkStruct_02005490 *) (self + 0x234), &buf, 4);
    v.x = buf.p.x;
    v.y = buf.p.y;
    v.z = buf.p.z;
    func_0203f7d0((Vec *) (self + 0x6d4), &v);
    func_02055d0c((UnkStruct_02005490 *) (self + 0x234), &buf, 0x10);
    v.x = buf.p.x;
    v.y = buf.p.y;
    v.z = buf.p.z;
    func_0203f7d0((Vec *) (self + 0x6e0), &v);
    *(UnkStruct_02005490 *) (self + 0x3f0) = *(UnkStruct_02005490 *) (self + 0x42c);
    func_02055d38((UnkStruct_02005490 *) (self + 0x38c), self[0x8e9]);
    func_02055e7c((UnkStruct_02005490 *) (self + 0x38c), 0);
    if (func_0205e138((UnkStruct_02005490 *) (self + 0x428), 1) < 0x9e) {
        *(UnkStruct_02005490 *) (self + 0x4c8) = *(UnkStruct_02005490 *) (self + 0x42c);
        func_02055d38((UnkStruct_02005490 *) (self + 0x464), self[0x8e9]);
        func_02055e7c((UnkStruct_02005490 *) (self + 0x464), 0);
    }
    if (func_0205ddd4((UnkStruct_02005490 *) (self + 0x59c)) != 0x4b) {
        *(UnkStruct_02005490 *) (self + 0x564) = *(UnkStruct_02005490 *) (self + 0x42c);
        func_02055d38((UnkStruct_02005490 *) (self + 0x500), self[0x8e9]);
        func_02055e7c((UnkStruct_02005490 *) (self + 0x500), 0);
    }
    if (*(int *) (self + 0x6f0) > 0) {
        func_02055d0c((UnkStruct_02005490 *) (self + 0x234), &buf, 1);
        w.x = buf.p.x;
        w.y = buf.p.y;
        w.z = buf.p.z;
        func_0203f7d0(&slot, &w);
        func_020acbc8(&slot, *(int *) (self + 0x6f0));
    }
    if (func_0200f290(self, 0) != 0) {
        func_0205e954((UnkStruct_02005490 *) (self + 0x5a0), (UnkStruct_02005490 *) (self + 0x668));
        switch (func_0200fbe0(self)) {
            case 4:
            case 10:
                mode = 2;
                break;
            case 1:
            case 5:
            case 9:
                mode = 1;
                break;
            default:
                mode = 0;
                break;
        }
        func_0205e8f8(&m1, (UnkStruct_02005490 *) (self + 0x5a0), mode);
        *(UnkStruct_02005490 *) (self + 0x608) = m1;
        if (func_0200fbe0(self) == 4) {
            func_0205e8f8(&m2, (UnkStruct_02005490 *) (self + 0x5a0), 3);
            *(UnkStruct_02005490 *) (self + 0x638) = m2;
        }
    }
}
