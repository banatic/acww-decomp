/* func_ov004_0220e674 @ 0x0220e674, 0xc8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
struct UnkStruct_0220e674 {
    u8 data[0x24];
};
struct UnkStruct_0220e674_2 {
    int unk_00;
    int unk_04;
};

extern void *func_02095794(int i);
extern char *func_ov004_0220db94(struct UnkStruct_0220e674 *l);
extern void func_ov004_0220f27c(void *self, struct UnkStruct_0220e674 *l, int a, int b);
extern struct UnkStruct_0220e674_2 *func_ov004_0220db5c(struct UnkStruct_0220e674 *l, unsigned int i);
extern unsigned int func_ov004_0220db68(struct UnkStruct_0220e674 *l);
extern void func_ov004_0220db90(struct UnkStruct_0220e674 *l);
extern void func_0204f794(Vec3 *v, int a, int b);
extern int func_020ea990(void *o, Vec3 *v);
extern int func_0200322c(Vec3 *v, void *o);
extern int func_ov004_0220e73c(Vec3 *v, int a);
extern int data_020ca0ec;

void func_ov004_0220e674(char *self, int flag)
{
    void *o;
    int besti2;
    struct UnkStruct_0220e674_2 *e;
    struct UnkStruct_0220e674 l;
    Vec3 a;
    Vec3 b;
    int bestd;
    int best;
    unsigned int i;
    int d;
    int mind;

    o = func_02095794(4);
    if (o != 0) {
        func_ov004_0220db94(&l);
        func_ov004_0220f27c(self, &l, 0, 0);
        bestd = 0;
        best = ~bestd;
        besti2 = best;
        mind = data_020ca0ec;
        for (i = 0; i < func_ov004_0220db68(&l); i++) {
            e = func_ov004_0220db5c(&l, i);
            func_0204f794(&a, e->unk_00, func_ov004_0220db5c(&l, i)->unk_04);
            d = func_020ea990(o, &a);
            if (d > bestd) {
                best = i;
                bestd = d;
            }
            if (d < mind) {
                besti2 = i;
                mind = d;
            }
        }
        if (flag == 0) {
            best = besti2;
        }
        if (best != -1) {
            e = func_ov004_0220db5c(&l, best);
            func_0204f794(&b, e->unk_00, func_ov004_0220db5c(&l, best)->unk_04);
            func_ov004_0220e73c(&b, func_0200322c(&b, o));
        }
        func_ov004_0220db90(&l);
    }
}
