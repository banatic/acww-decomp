/* func_02009918 @ 0x02009918, 0x10c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;

struct UnkStruct_02009918 {
    int a;
    int b;
    int c;
};

struct UnkStruct_02009918_2 {
    int unk_00;
    int w1;
};

struct Packed {
    u16 low : 7;
    u16 mid : 4;
    u16 high : 5;
};

extern void func_020109fc(void *p, int a, int b, int c);
extern void func_02009a24(void *dst, struct UnkStruct_02009918 s, int p4, int p5);
extern unsigned int *func_0200f27c(void *p, int a);
extern int func_0200ee0c(void *p);
extern int func_02073908(void *a, int b);
extern int func_020b65c4(void);
extern void func_0209e474(void *p);
extern u8 *func_0209626c(void);
extern void func_0209e140(void *p, int a);
extern void *func_02011368(void *p);
extern void func_02099794(void *p, struct Packed s);

void func_02009918(void *param0, void *param1, int param2)
{
    int p2_copy = param2;
    struct Packed packed;
    struct UnkStruct_02009918_2 local;
    int d;
    struct UnkStruct_02009918 *p = (struct UnkStruct_02009918 *) ((char *) param1 + 0xc);

    func_020109fc(param0, 1, 3, 0);
    d = *(int *) ((char *) p + 0xc);
    func_02009a24((char *) param0 + 0x7d4, *p, d, p2_copy);
    func_0200f27c(param0, 5);
    *(int *) ((char *) param0 + 0x808) = 0;

    if (func_0200ee0c(param0) != 0 && func_02073908(data_020ccf94, *(int *) ((char *) param0 + 0x800)) != 0 &&
        func_020b65c4() == 0xc && d == 0x666) {
        local.unk_00 = 0;
        local.w1 = 0;
        func_0209e474(&local);
        *func_0209626c() &= 0xf9;
        if (!(*func_0209626c() & 1)) {
            func_0209e140(&local, 1);
        }
        packed.low = ((u8 *) &local)[5];
        packed.mid = ((u8 *) &local)[4];
        packed.high = ((u8 *) &local)[3];
        func_02099794(func_02011368(param0), packed);
    }
}
