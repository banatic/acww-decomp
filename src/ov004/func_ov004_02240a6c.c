/* func_ov004_02240a6c @ 0x02240a6c, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02240bac(void *, int, int);

int func_ov004_02240a6c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02240bac(self, 0xc8, 0x50);
    *(void **) (self + 0x15c) = 0x0;
    return 0x15c;
}
