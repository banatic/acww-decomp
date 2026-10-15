/* func_ov004_0223ef98 @ 0x0223ef98, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d138(void *);
extern void func_ov004_0223ebf0(void *, int);

int func_ov004_0223ef98(char *self)
{
    // DECLS
    int i;
    // ENDDECLS
    for (i = 0; i < 0x20; i++) {
        func_ov004_0223ebf0(self, i);
    }
    func_0209d138(self + 0x180);
    return 0x1;
}
