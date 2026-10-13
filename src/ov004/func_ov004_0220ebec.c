/* func_ov004_0220ebec @ 0x0220ebec, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0220ebec {
    u8 data[0x24];
};
struct UnkStruct_0220ebec_2 {
    int unk_00;
    int unk_04;
};

extern void func_ov004_0220db94(struct UnkStruct_0220ebec *l);
extern void func_ov004_0220f27c(void *self, struct UnkStruct_0220ebec *l, int a, int b);
extern struct UnkStruct_0220ebec_2 *func_ov004_0220db5c(struct UnkStruct_0220ebec *l, unsigned int i);
extern unsigned int func_ov004_0220db68(struct UnkStruct_0220ebec *l);
extern void func_ov004_0220db90(struct UnkStruct_0220ebec *l);
extern u16 *func_0204f5e0(void *g, int a, int b, int c, int d, int e);
extern void *data_021c80bc;

int func_ov004_0220ebec(char *self)
{
    struct UnkStruct_0220ebec l;
    void *g;
    unsigned int i;
    int a;
    int b;
    int ai;
    int bi;
    u16 *p;

    func_ov004_0220db94(&l);
    func_ov004_0220f27c(self, &l, 0, 0);
    g = data_021c80bc;
    if (*(u8 *) (self + 0x288) == 0 && *(int *) (self + 0x788) == 1) {
        for (i = 0; i < func_ov004_0220db68(&l); i++) {
            b = func_ov004_0220db5c(&l, i)->unk_04;
            a = func_ov004_0220db5c(&l, i)->unk_00;
            ai = a >> 4;
            bi = b >> 4;
            p = func_0204f5e0(g, ai, bi, a - (ai << 4), b - (bi << 4), 1);
            if (p != 0 && *p != 0xfff1) {
                func_ov004_0220db90(&l);
                return 1;
            }
        }
    }
    func_ov004_0220db90(&l);
    return 0;
}
