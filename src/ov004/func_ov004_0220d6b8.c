/* func_ov004_0220d6b8 @ 0x0220d6b8, 0xd0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0220d6b8 {
    int data[9];
};
struct UnkStruct_0220d6b8_2 {
    int unk_00;
    int unk_04;
};

extern char *func_ov004_0220db94(struct UnkStruct_0220d6b8 *l);
extern void func_ov004_0220f27c(void *self, struct UnkStruct_0220d6b8 *l, int a, int b);
extern struct UnkStruct_0220d6b8_2 *func_ov004_0220db5c(struct UnkStruct_0220d6b8 *l, unsigned int i);
extern unsigned int func_ov004_0220db68(struct UnkStruct_0220d6b8 *l);
extern void func_ov004_0220db90(struct UnkStruct_0220d6b8 *l);
extern u16 *func_0204f5e0(void *g, int a, int b, int c, int d, int e);
extern int func_0204bc90(u16 *p);
extern int func_0204bd08(u16 *p);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern void *data_021c80bc;

int func_ov004_0220d6b8(void *unused, char *self)
{
    int u;
    int v;
    u16 tmp;
    struct UnkStruct_0220d6b8 l;
    void *g;
    unsigned int i;
    int sentinel;
    int a, b, ai, bi, ok;
    u16 *p;

    func_ov004_0220db94(&l);
    func_ov004_0220f27c(self, &l, 0, 0);
    g = data_021c80bc;
    u = 0;
    sentinel = 0xfff1;
    v = 0;
    for (i = 0; i < func_ov004_0220db68(&l); i++) {
        b = func_ov004_0220db5c(&l, i)->unk_04;
        a = func_ov004_0220db5c(&l, i)->unk_00;
        ai = a >> 4;
        bi = b >> 4;
        p = func_0204f5e0(g, ai, bi, a - (ai << 4), b - (bi << 4), 1);
        if (p != 0 && func_0204bc90(p) == 0 && func_0204bd08(p) == 0) {
            if (func_0204bcdc(p) != 0) {
                tmp = (u16) sentinel;
                ok = (func_0204bc64(p) == func_0204bc64(&tmp)) ? 1 : u;
            } else {
                ok = (*p == (u16) sentinel) ? 1 : v;
            }
            if (ok == 0) {
                func_ov004_0220db90(&l);
                return 0;
            }
        }
    }
    func_ov004_0220db90(&l);
    return 1;
}
