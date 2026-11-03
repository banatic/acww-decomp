/* rmo_telephone_4: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223119c @ 0x0223119c, 0x20 bytes, Thumb
 * func_ov004_02231178 @ 0x02231178, 0x24 bytes, Thumb
 */

extern int func_ov004_0222befc(void);
extern int func_ov004_0222c2dc(void *, int);
extern int func_02056f94(void *argument0);
extern void func_ov004_0223121c(void *self, int i);

int func_ov004_0223119c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222befc();
    return func_ov004_0222c2dc(self + 0x250, 0x4d4);
}

void func_ov004_02231178(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02056f94(self + 0x188);
    if (v1 != 0x0) {
        func_ov004_0223121c(self, 0x2);
        return;
    }
    return;
}
