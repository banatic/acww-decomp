/* func_ov004_0222f3a0 @ 0x0222f3a0, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055050(void *);
extern void func_02055060(void *, int, int, int, int, int);
extern int func_02055140(void *, int);
extern int func_ov004_0222c3c4(void *, int);
extern int func_ov004_0222c5c8(void *, void *);
extern void *data_021c9b24;
extern void *data_ov004_022552f8;

int func_ov004_0222f3a0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c5c8(self, &data_ov004_022552f8);
    if (func_ov004_0222c3c4(self + 0x1a4, 0x0) != 0x0 &&
        func_02055140(self + 0xec, *(int *) ((char *) &data_021c9b24)) != 0x0) {
        func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0x0), 0x0, 0x1000, 0x0, 0x0);
        func_02055050(self + 0xec);
    }
    return 0x1;
}
