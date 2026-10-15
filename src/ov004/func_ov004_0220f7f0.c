/* func_ov004_0220f7f0 @ 0x0220f7f0, 0xd0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

struct UnkStruct_0220f7f0 {
    int data[9];
};
struct UnkStruct_0220f7f0_2 {
    int unk_00;
    int unk_04;
};

extern char *func_ov004_0220db94(struct UnkStruct_0220f7f0 *l);
extern void func_ov004_0220f27c(void *self, struct UnkStruct_0220f7f0 *l, int a, int b);
extern struct UnkStruct_0220f7f0_2 *func_ov004_0220db5c(struct UnkStruct_0220f7f0 *l, unsigned int i);
extern unsigned int func_ov004_0220db68(struct UnkStruct_0220f7f0 *l);
extern void func_ov004_0220db90(struct UnkStruct_0220f7f0 *l);
extern u16 *func_0204f5e0(void *g, int a, int b, int c, int d, int e);
extern int func_0204bd08(u16 *p);
extern void func_0204f794(Vec3 *v, int a, int b);
extern int func_ov004_0223c5b8(int a, int b);
extern int func_020b6590(void);
extern void *func_020b7d3c(int h, void *o, Vec3 *v, int a, int b, int c, int d);
extern void *data_021c80bc;

void func_ov004_0220f7f0(char *self)
{
    void *g;
    struct UnkStruct_0220f7f0 l;
    Vec3 v;
    unsigned int i;
    int a, b, ai, bi;
    u16 *p;

    if (*(u8 *) (self + 0x288) == 0 && *(int *) (self + 0x788) == 1) {
        func_ov004_0220db94(&l);
        func_ov004_0220f27c(self, &l, 0, 0);
        g = data_021c80bc;
        for (i = 0; i < func_ov004_0220db68(&l); i++) {
            a = func_ov004_0220db5c(&l, i)->unk_00;
            b = func_ov004_0220db5c(&l, i)->unk_04;
            ai = a >> 4;
            bi = b >> 4;
            p = func_0204f5e0(g, ai, bi, a - (ai << 4), b - (bi << 4), 1);
            if (p != 0 && func_0204bd08(p) != 0) {
                func_0204f794(&v, a, b);
                v.y = func_ov004_0223c5b8(a, b);
                func_020b7d3c(func_020b6590(), self + 0x1d0 + i * 32, &v, 0xccd, 0x100, 0xa, 0xff);
            }
        }
        func_ov004_0220db90(&l);
    }
}
