/* rmo_object_slots_3: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222c6e0 @ 0x0222c6e0, 0x24 bytes, Thumb
 * func_ov004_0222c6d0 @ 0x0222c6d0, 0xe bytes, Thumb
 * func_ov004_0222c6cc @ 0x0222c6cc, 0x4 bytes, Thumb
 */

extern int func_0203efdc(char *self);
extern void func_ov004_0222c2f0(char *p);

int func_ov004_0222c6e0(char *self)
{
    int r;
    if (func_0203efdc(self) == 0) {
        r = 0;
    } else {
        func_ov004_0222c2f0(self + 0x250);
        r = 1;
    }
    return r;
}

void func_ov004_0222c6d0(char *self, char *a1)
{
    // DECLS
    // ENDDECLS
    *(int *) (a1) = *(int *) (self + 0x5c);
    *(int *) (a1 + 0x4) = *(int *) (self + 0x60);
    *(int *) (a1 + 0x8) = *(int *) (self + 0x64);
}

int func_ov004_0222c6cc(void *object, unsigned int mode)
{
    return 1;
}
