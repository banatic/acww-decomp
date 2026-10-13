/* func_ov004_0220dad0 @ 0x0220dad0, 0x1e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220daf0(void *, int, int);
extern void func_ov004_0220db48(void *, int, int);

void *func_ov004_0220dad0(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220db48(self, a1, a2);
    func_ov004_0220daf0(self, a1, a2);
    return self;
}
