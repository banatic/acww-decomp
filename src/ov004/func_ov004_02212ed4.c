/* func_ov004_02212ed4 @ 0x02212ed4, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220cdf8(void *);
extern int func_ov004_0220e5c8(void *);
extern void func_ov004_0223cf40(void *, int, void *);

int func_ov004_02212ed4(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_ov004_0220e5c8(self) == 0x0 && func_ov004_0220cdf8(self) == 0x0) {
        func_ov004_0223cf40(self + 0x798, 0x42a, self + 0x7b8);
    }
    return 0x1;
}
