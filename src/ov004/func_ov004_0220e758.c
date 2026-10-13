/* func_ov004_0220e758 @ 0x0220e758, 0xb0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0220e758 {
    u8 data[0x24];
};
struct UnkStruct_0220e758_2 {
    int unk_00;
    int unk_04;
};

extern void func_ov004_0220db94(struct UnkStruct_0220e758 *l);
extern void func_ov004_0220f27c(void *self, struct UnkStruct_0220e758 *l, int a, int b);
extern struct UnkStruct_0220e758_2 *func_ov004_0220db5c(struct UnkStruct_0220e758 *l, unsigned int i);
extern unsigned int func_ov004_0220db68(struct UnkStruct_0220e758 *l);
extern void func_ov004_0220db90(struct UnkStruct_0220e758 *l);
extern u16 *func_0204f5e0(void *g, int a, int b, int c, int d, int e);
extern int func_0204bcdc(u16 *p);
extern void *data_021c80bc;

int func_ov004_0220e758(char *self, int *outa, int *outb, int p3, short p4)
{
    void *g;
    struct UnkStruct_0220e758 l;
    unsigned int i;
    int a;
    int b;
    int ai;
    int bi;
    int k;
    u16 *p;

    func_ov004_0220db94(&l);
    func_ov004_0220f27c(self, &l, p3, p4);
    g = data_021c80bc;
    for (i = 0; i < func_ov004_0220db68(&l); i++) {
        k = *(u8 *) (self + 0x288);
        b = func_ov004_0220db5c(&l, i)->unk_04;
        a = func_ov004_0220db5c(&l, i)->unk_00;
        ai = a >> 4;
        bi = b >> 4;
        p = func_0204f5e0(g, ai, bi, a - (ai << 4), b - (bi << 4), k);
        if (p != 0 && func_0204bcdc(p) != 0) {
            *outa = func_ov004_0220db5c(&l, i)->unk_00;
            *outb = func_ov004_0220db5c(&l, i)->unk_04;
            func_ov004_0220db90(&l);
            return 1;
        }
    }
    func_ov004_0220db90(&l);
    return 0;
}
