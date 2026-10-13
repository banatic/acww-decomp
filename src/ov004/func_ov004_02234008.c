/* func_ov004_02234008 @ 0x02234008, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f5958(void *);

void *func_ov004_02234008(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x10) = 0x0;
    *(void **) (self + 0x14) = 0x0;
    func_020f5958(self + 0x4c);
    return self;
}
