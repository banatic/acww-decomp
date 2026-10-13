/* func_ov004_0220ee90 @ 0x0220ee90, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0220ee90 {
    u8 data[0x24];
};
struct Iter {
    u8 data[0x14];
};

extern void func_ov004_0220db94(struct UnkStruct_0220ee90 *l);
extern void func_ov004_0220f27c(void *self, struct UnkStruct_0220ee90 *l, int a, int b);
extern void func_ov004_0220dad0(struct Iter *it, struct UnkStruct_0220ee90 *l, int k);
extern void func_ov004_0220f100(void *self, int a, int b);
extern void func_ov004_0220ef14(void *obj, int a, int b, int c, int d);
extern void *func_ov004_0220dab0(struct Iter *it, unsigned int i);
extern unsigned int func_ov004_0220dabc(struct Iter *it);
extern void func_ov004_0220dac0(struct Iter *it);
extern void func_ov004_0220db90(struct UnkStruct_0220ee90 *l);

void func_ov004_0220ee90(char *self, int a, int b)
{
    struct UnkStruct_0220ee90 local;
    struct Iter it;
    unsigned int i;
    void *p;

    func_ov004_0220db94(&local);
    func_ov004_0220f27c(self, &local, 0, 0);
    func_ov004_0220dad0(&it, &local, *(u8 *) (self + 0x288));
    func_ov004_0220f100(self, 1, 1);
    func_ov004_0220ef14(self, 1, a, b, 1);
    for (i = 0; i < func_ov004_0220dabc(&it); i++) {
        p = func_ov004_0220dab0(&it, i);
        if (p != 0) {
            func_ov004_0220ef14(p, 1, a, b, 1);
        }
    }
    func_ov004_0220dac0(&it);
    func_ov004_0220db90(&local);
}
