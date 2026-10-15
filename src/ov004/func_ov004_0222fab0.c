/* func_ov004_0222fab0 @ 0x0222fab0, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222c598(void *);
extern int func_ov004_0222f474(void *);
extern void *data_ov004_02258490;

int func_ov004_0222fab0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222f474(self);
    func_ov004_0222c598(self);
    *(void **) ((char *) &data_ov004_02258490) = 0x0;
    return 0x1;
}
