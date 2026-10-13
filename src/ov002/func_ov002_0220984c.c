/* func_ov002_0220984c @ 0x0220984c, 0x1a bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02209868(void *, int, int);

int func_ov002_0220984c(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    func_ov002_02209868(self, a1, a2);
    *(int *) (self + 0x8) = -a1;
    *(int *) (self + 0xc) = -a2;
    return -a2;
}
