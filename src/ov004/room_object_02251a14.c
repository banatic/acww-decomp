/* room_object_02251a14: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02219bcc @ 0x02219bcc, 0x34 bytes, Thumb
 * func_ov004_02219ba4 @ 0x02219ba4, 0x28 bytes, Thumb
 * func_ov004_02219b70 @ 0x02219b70, 0x34 bytes, Thumb
 * func_ov004_02219b38 @ 0x02219b38, 0x38 bytes, Thumb
 */

extern int func_ov004_0220d058(void *, int, int, int);
extern void func_ov004_0220d280(void *, int, int);
extern int func_ov004_02210744(void *);
extern int func_ov004_0220d2a8(void *p);
extern int func_0205265c(void *p, int a, int b, int c);
extern int func_ov004_0221078c(void *);
extern int func_ov004_0220ffbc(char *argument0);
extern int func_ov004_022107d4(char *argument0);
extern int func_ov004_0221081c(char *argument0);

int func_ov004_02219bcc(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_02210744(self);
    func_ov004_0220d058(self + 0x848, 0x0, 0x1, 0x0);
    return 0x1;
}

void func_ov004_02219ba4(char *self)
{
    if (func_ov004_0220d2a8(self + 0x740)) {
        func_0205265c(self, 1, 0xff, 1);
    }
}

int func_ov004_02219b70(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_0221078c(self);
    func_ov004_0220d058(self + 0x848, 0x1, 0x1, 0x0);
    return 0x1;
}

int func_ov004_02219b38(char *self)
{
    // DECLS
    int v4;
    // ENDDECLS
    func_ov004_0220ffbc(self);
    func_ov004_0221081c(self);
    func_ov004_022107d4(self);
    v4 = func_ov004_0220d2a8((void *) (self + 0x740));
    if (v4 != 0x0) {
        return func_0205265c((void *) ((unsigned int) (self)), (int) (0x0), (int) (0xff), (int) (0x1));
    }
    return v4;
}
