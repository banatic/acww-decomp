/* func_ov004_0223cea8 @ 0x0223cea8, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9fc8(int);
extern void func_ov004_0223cef4(void *);

void func_ov004_0223cea8(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self) != 0x0) {
        func_020e9fc8(*(int *) (self));
    }
    func_ov004_0223cef4(self);
}
