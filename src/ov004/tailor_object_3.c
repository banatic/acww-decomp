/* tailor_object_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02230054 @ 0x02230054, 0x24 bytes, Thumb
 * func_ov004_02230020 @ 0x02230020, 0x34 bytes, Thumb
 */

extern void func_0205510c(void *, int);
extern void func_ov004_0222c340(void *);
extern void func_ov004_0222c3d4(void *);
extern void func_ov004_0222c598(void *);
extern void *data_ov004_02258558;

int func_ov004_02230054(char *self)
{
    // DECLS
    // ENDDECLS
    func_0205510c(self + 0xec, 0x0);
    func_0205510c(self + 0x290, 0x0);
    return 0x1;
}

int func_ov004_02230020(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c598(self);
    func_ov004_0222c3d4(self + 0x348);
    func_ov004_0222c340(self + 0x3ec);
    *(void **) ((char *) &data_ov004_02258558) = 0x0;
    return 0x1;
}
