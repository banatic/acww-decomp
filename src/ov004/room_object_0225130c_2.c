/* room_object_0225130c_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02212d44 @ 0x02212d44, 0x34 bytes, Thumb
 * func_ov004_02212d1c @ 0x02212d1c, 0x28 bytes, Thumb
 * func_ov004_02212ce4 @ 0x02212ce4, 0x38 bytes, Thumb
 */

extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_022101e4(void *, int, int, int, int);
extern int func_ov004_0220d2a8(void *p);
extern int func_0205265c(void *p, int a, int b, int c);
extern int func_ov004_0221078c(void *);

int func_ov004_02212d44(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_022101e4(self, 0x0, 0x3, 0x1000, 0x0);
    return 0x1;
}

void func_ov004_02212d1c(char *self)
{
    if (func_ov004_0220d2a8(self + 0x740)) {
        func_0205265c(self, 1, 0xff, 1);
    }
}

int func_ov004_02212ce4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_022101e4(self, 0x0, 0x1, 0x1000, 0x0);
    func_ov004_0221078c(self);
    return 0x1;
}
