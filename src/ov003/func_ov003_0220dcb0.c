/* func_ov003_0220dcb0 @ 0x0220dcb0, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02010f5c(void *p);
extern int func_02056f28(void *p, int n);
extern int func_020984fc(unsigned int val);
extern void func_0209971c(int a, unsigned short *b);
extern void func_0205eb8c(void *p, unsigned short *q, int r);
extern int func_0200f328(void *p, int n);
extern int func_0203f7d0(void *a, void *b);
extern int func_020912d4(int a, void *b, void *c, int d);
extern unsigned int *func_0200f27c(void *p, int n);

void func_ov003_0220dcb0(char *self)
{
    int res;
    u16 v[2];
    u32 z, y, x;
    struct {
        u32 x;
        u32 y;
        u32 z;
    } tmp;

    func_02010f5c(self);
    if (!func_02056f28(self + 0x2d0, 13)) {
        return;
    }

    res = func_020984fc(*(u32 *) (self + 0x800));

    v[0] = 0xfff1;
    func_0209971c(res, v);

    v[1] = 0xfff1;
    func_0205eb8c(self + 0x5a0, &v[1], 0);

    func_0200f328(self, 0x850);

    z = *(u32 *) (self + 0x694);
    y = *(u32 *) (self + 0x690);
    x = *(u32 *) (self + 0x68c);
    tmp.x = x;
    tmp.y = y;
    tmp.z = z;
    func_0203f7d0(&tmp, &tmp);

    func_020912d4(0x24, &tmp, self + 0x8e, 0);
    func_0200f27c(self, 9);
}
