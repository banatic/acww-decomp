/* room_object_glowing: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02212124 @ 0x02212124, 0x38 bytes, Thumb
 * func_ov004_022120e8 @ 0x022120e8, 0x3c bytes, Thumb
 * func_ov004_022120b0 @ 0x022120b0, 0x38 bytes, Thumb
 * func_ov004_0221206c @ 0x0221206c, 0x44 bytes, Thumb
 */

extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_022101e4(void *, int, int, int, int);
extern int func_ov004_02210744(void *);
extern int func_0205265c(unsigned int argument0, int argument1, int argument2, int argument3);
extern int func_ov004_0220d058(char *argument0, int argument1, int argument2, int argument3);
extern int func_ov004_0220d2a8(char *argument0);
extern int func_ov004_0220ffbc(char *argument0);
extern int func_ov004_0221078c(void *);
extern int func_ov004_022107d4(char *argument0);

int func_ov004_02212124(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02210744(self);
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_022101e4(self, 0x0, 0x1, 0x1000, 0x0);
    return 0x1;
}

int func_ov004_022120e8(char *self)
{
    // DECLS
    int v3;
    // ENDDECLS
    func_ov004_0220ffbc(self);
    func_ov004_0220d058(self + 0x844, 0x0, 0x1, 0x0);
    v3 = func_ov004_0220d2a8(self + 0x740);
    if (v3 != 0x0) {
        return func_0205265c((unsigned int) (self), (int) (0x1), (int) (0xff), (int) (0x1));
    }
    return v3;
}

int func_ov004_022120b0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0221078c(self);
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_022101e4(self, 0x1, 0x0, 0x1000, 0x0);
    return 0x1;
}

int func_ov004_0221206c(char *self)
{
    // DECLS
    int v4;
    // ENDDECLS
    func_ov004_0220ffbc(self);
    func_ov004_0220d058(self + 0x844, 0x1, 0x1, 0x0);
    func_ov004_022107d4(self);
    v4 = func_ov004_0220d2a8(self + 0x740);
    if (v4 != 0x0) {
        return func_0205265c((unsigned int) (self), (int) (0x0), (int) (0xff), (int) (0x1));
    }
    return v4;
}
