/* rmo_telephone_7: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02231690 @ 0x02231690, 0x14 bytes, Thumb
 * func_ov004_02231674 @ 0x02231674, 0x1c bytes, Thumb
 */

extern void func_0205510c(void *, int);
extern void func_ov004_0222c598(char *arg0);
extern void *data_ov004_022588c8;

int func_ov004_02231690(char *self)
{
    // DECLS
    // ENDDECLS
    func_0205510c(self + 0xec, 0x0);
    return 0x1;
}

int func_ov004_02231674(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c598((char *) self);
    *(void **) ((char *) &data_ov004_022588c8) = 0x0;
    return 0x1;
}
