/* barber_machine_4: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222cc60 @ 0x0222cc60, 0x14 bytes, Thumb
 * func_ov004_0222cc40 @ 0x0222cc40, 0x20 bytes, Thumb
 */

extern void func_0205510c(void *, int);
extern void func_ov004_0222c598(void *);
extern int func_ov004_0222c8f4(void *);
extern void *data_ov004_02258224;

int func_ov004_0222cc60(char *self)
{
    // DECLS
    // ENDDECLS
    func_0205510c(self + 0xec, 0x0);
    return 0x1;
}

int func_ov004_0222cc40(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c8f4(self);
    func_ov004_0222c598(self);
    *(void **) ((char *) &data_ov004_02258224) = 0x0;
    return 0x1;
}
