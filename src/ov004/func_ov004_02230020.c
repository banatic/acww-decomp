/* func_ov004_02230020 @ 0x02230020, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222c340(void *);
extern void func_ov004_0222c3d4(void *);
extern void func_ov004_0222c598(void *);
extern void *data_ov004_02258558;

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
