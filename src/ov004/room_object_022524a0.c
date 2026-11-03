/* room_object_022524a0: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022141c0 @ 0x022141c0, 0x30 bytes, Thumb
 * func_ov004_02214198 @ 0x02214198, 0x28 bytes, Thumb
 * func_ov004_02214160 @ 0x02214160, 0x38 bytes, Thumb
 * func_ov004_0221412c @ 0x0221412c, 0x34 bytes, Thumb
 */

extern void func_ov004_0220cfec(void *, int);
extern void func_ov004_022101e4(void *, int, int, int, int);
extern int func_ov004_0220d2a8(void *p);
extern int func_02052738(void *p, int a, int b, int c);
extern int func_ov004_0221078c(void *);
extern void func_02054cdc(void *argument0);
extern int func_02056f94(void *argument0);

int func_ov004_022141c0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220cfec(self + 0x764, 0x0);
    func_ov004_022101e4(self, 0x0, 0x1, 0x1000, 0x0);
    return 0x1;
}

void func_ov004_02214198(char *self)
{
    if (func_ov004_0220d2a8(self + 0x740)) {
        func_02052738(self, 1, 0xff, 1);
    }
}

int func_ov004_02214160(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220cfec(self + 0x764, 0x1);
    func_ov004_022101e4(self, 0x0, 0x1, 0x1000, 0x0);
    func_ov004_0221078c(self);
    return 0x1;
}

int func_ov004_0221412c(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    func_02054cdc(self + 0x538);
    v2 = func_02056f94(self + 0x5d4);
    if (v2 != 0x0) {
        return func_02052738((void *) ((unsigned int) (self)), (int) (0x0), (int) (0xff), (int) (0x1));
    }
    return v2;
}
