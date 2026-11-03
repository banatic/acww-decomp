/* room_object_022525cc: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221984c @ 0x0221984c, 0x38 bytes, Thumb
 * func_ov004_02219824 @ 0x02219824, 0x28 bytes, Thumb
 * func_ov004_022197e0 @ 0x022197e0, 0x44 bytes, Thumb
 * func_ov004_022197b0 @ 0x022197b0, 0x30 bytes, Thumb
 * func_ov004_0221977c @ 0x0221977c, 0x34 bytes, Thumb
 */

extern void func_ov004_0220d280(void *p, int a, int b);
extern int func_ov004_0220d058(void *p, int a, int b, int c);
extern int func_ov004_0220d2a8(void *p);
extern int func_0205265c(void *p, int a, int b, int c);
extern int func_ov004_0221078c(char *argument0);
extern int func_ov004_022107d4(char *argument0);
extern int func_ov004_0221081c(char *argument0);
extern int func_ov004_02210744(void *);

int func_ov004_0221984c(unsigned char *self)
{
    *(int *) (self + 0x848) = 0;
    func_ov004_0220d280(self + 0x740, 0, 0);
    func_ov004_0220d058(self + 0x84c, 0, 1, 0);
    return 1;
}

void func_ov004_02219824(char *self)
{
    if (func_ov004_0220d2a8(self + 0x740)) {
        func_0205265c(self, 1, 0xff, 1);
    }
}

int func_ov004_022197e0(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) (self + 0x848) = 0x1000;
    func_ov004_0220d280((void *) ((unsigned char *) (self + 0x740)), (unsigned char) ((unsigned char) (0x1)), (int) (0x0));
    func_ov004_0221078c(self);
    func_ov004_0220d058((void *) (self + 0x84c), 0x1, 0x1, 0x0);
    return 0x1;
}

int func_ov004_022197b0(char *self)
{
    // DECLS
    int v3;
    // ENDDECLS
    func_ov004_0221081c(self);
    func_ov004_022107d4(self);
    v3 = func_ov004_0220d2a8((void *) (self + 0x740));
    if (v3 != 0x0) {
        return func_0205265c((void *) ((unsigned int) (self)), (int) (0x2), (int) (0xff), (int) (0x1));
    }
    return v3;
}

int func_ov004_0221977c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_02210744(self);
    func_ov004_0220d058(self + 0x84c, 0x1, 0x1, 0x0);
    return 0x1;
}
