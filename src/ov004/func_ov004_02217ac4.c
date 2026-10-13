/* func_ov004_02217ac4 @ 0x02217ac4, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220ce50(void *);
extern void func_ov004_0220e758(void *, void *, void *, int, int);

int func_ov004_02217ac4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220e758(self, self + 0x850, self + 0x854, 0x0, 0x0);
    func_ov004_0220ce50(self);
    return 0x1;
}
