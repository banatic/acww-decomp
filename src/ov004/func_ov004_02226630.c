/* func_ov004_02226630 @ 0x02226630, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022266c4(void *self);
extern void func_ov004_02226920(void *self);
extern void func_02010ff4(void *self);
extern void func_02010d64(void *self);
extern char *data_020ccf94;
extern int func_02073908(char *g, int a);
extern void func_0200f328(void *self, int a);
extern int func_020b5e10(void);
extern void func_020b6098(int a, int b);

void func_ov004_02226630(char *self)
{
    unsigned char *q;
    unsigned char *p;
    unsigned int m;
    char *g;

    func_ov004_022266c4(self);
    func_ov004_02226920(self);
    func_02010ff4(self);
    func_02010d64(self);
    q = (unsigned char *) (self + 0x7d4);
    p = q + 0x14;
    m = q[0x15];
    g = data_020ccf94;
    if (func_02073908(g, *(int *) (self + 0x800)) == 0 && *p == 0xf && m == 1) {
        func_0200f328(self, 0x4d3);
    }
    if (func_02073908(g, *(int *) (self + 0x800)) != 0 && m - 1 <= 1 && *p == 0xa) {
        func_020b6098(func_020b5e10(), *(int *) (self + 0x804));
    }
    *p = *p + 1;
}
