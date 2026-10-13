/* func_02080ff8 @ 0x02080ff8, 0x14c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02080ff8 {
    u16 unk_00;
    u16 unk_02;
    int unk_04;
    int unk_08;
};
struct UnkStruct_02080ff8_2 {
    int unk_00;
    int unk_04;
};

extern int func_0208150c(void *a);
extern void *func_020984e8(void);
extern int func_02003704(int a);
extern void *func_02099870(void *a);
extern int func_020951bc(void *a);
extern int func_02094ffc(void *a);
extern int func_02099020(void *a, int b);
extern u8 *func_020992e4(void *a);
extern void func_0209e474(void *a);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern void *func_020807a8(void *a, void *b);
extern int func_02081d20(void *a);
extern int func_02081910(void *a);
extern int func_020644cc(int a);
extern void func_02063ccc(struct UnkStruct_02080ff8_2 *b, void *p, int c);
extern void func_020638d4(u16 *a, struct UnkStruct_02080ff8_2 *b, int c, int d, int e, int f, int g);
extern void func_02063cc8(struct UnkStruct_02080ff8_2 *b);
extern int func_0205a240(void *a, int b, void *c, int d, void *e, int f);
extern void func_02081938(void *a);

extern void *data_020cd448[];
extern int data_020e1988;

void func_02080ff8(void *a0, void *a1, void *a2)
{
    int v10;
    struct UnkStruct_02080ff8 s;
    struct UnkStruct_02080ff8_2 b[2];
    u8 *p;
    int flag;
    void *r7;
    void *r5;
    void *ptr;

    v10 = func_0208150c(a0);
    if (a1 == 0) {
        a1 = func_020984e8();
    }
    if (func_02003704(v10) == 0) {
        return;
    }
    if (a1 == 0) {
        return;
    }
    r7 = func_02099870(a1);
    if (func_020951bc(r7) == 0) {
        return;
    }
    if (func_02094ffc(r7) != 0) {
        return;
    }
    if (func_02099020(a1, 1) != 0) {
        return;
    }

    s.unk_04 = 0;
    s.unk_08 = 0;
    p = func_020992e4(a1);
    flag = 0;
    if (a2 == 0) {
        func_0209e474(&s.unk_04);
    } else {
        MI_CpuCopy8(a2, &s.unk_04, 8);
    }

    if (p[1] == ((u8 *) &s)[8] && p[0] == ((u8 *) &s)[7] && ((u8 *) &s)[6] >= 6) {
        flag = 1;
    }
    if (flag == 0) {
        return;
    }

    r5 = func_020807a8(a0, r7);
    if (r5 == 0) {
        return;
    }
    if (func_02081d20(r5) < 0x40) {
        return;
    }
    if (func_02081910(r5) != 0) {
        return;
    }

    s.unk_00 = 0xfff1;
    ptr = 0;
    func_02063ccc(&b[0], data_020cd448[func_020644cc(3)], 0);
    b[1].unk_00 = b[0].unk_00;
    b[1].unk_04 = b[0].unk_04;
    func_020638d4(&s.unk_02, &b[1], 0, 0, 1, 1, 0);
    s.unk_00 = s.unk_02;
    func_02063cc8(&b[1]);
    if (s.unk_00 != 0xfff1) {
        ptr = &s;
    }
    if (func_0205a240(&data_020e1988, (u8) func_020644cc(3), r7, v10, ptr, -1) != 0) {
        func_02081938(r5);
    }
    func_02063cc8(&b[0]);
}
