/* telephone_3: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022119f8 @ 0x022119f8, 0x1c bytes, Thumb
 * func_ov004_022119f4 @ 0x022119f4, 0x2 bytes, Thumb
 * func_ov004_022119d0 @ 0x022119d0, 0x24 bytes, Thumb
 * func_ov004_022119bc @ 0x022119bc, 0x14 bytes, Thumb
 * func_ov004_022119a0 @ 0x022119a0, 0x1c bytes, Thumb
 * func_ov004_0221199c @ 0x0221199c, 0x2 bytes, Thumb
 * func_ov004_02211978 @ 0x02211978, 0x24 bytes, Thumb
 * func_ov004_02211964 @ 0x02211964, 0x14 bytes, Thumb
 */

typedef void (*Fn)(void *self, int a, int b);

extern void func_ov004_0220d280(void *, int, int);
extern int func_ov004_0221078c(void *);

int func_ov004_022119f8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    return 0x1;
}

void func_ov004_022119f4(void *callbackObject) {}

int func_ov004_022119d0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_0221078c(self);
    return 0x1;
}

void func_ov004_022119bc(void *self)
{
    (*(Fn **) self)[28](self, 2, 0xff);
}

int func_ov004_022119a0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    return 0x1;
}

void func_ov004_0221199c(void *callbackObject) {}

int func_ov004_02211978(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_0221078c(self);
    return 0x1;
}

void func_ov004_02211964(void *self)
{
    (*(Fn **) self)[28](self, 0, 0xff);
}
