/* func_ov004_022308a8 @ 0x022308a8, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222c598(void *);
extern void func_ov004_02230404(void *, int);
extern void *data_ov004_02258870;

int func_ov004_022308a8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c598(self);
    func_ov004_02230404(self, 0x0);
    func_ov004_02230404(self, 0x1);
    func_ov004_02230404(self, 0x2);
    *(void **) ((char *) &data_ov004_02258870) = 0x0;
    return 0x1;
}
