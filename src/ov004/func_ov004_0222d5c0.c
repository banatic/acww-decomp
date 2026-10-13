/* func_ov004_0222d5c0 @ 0x0222d5c0, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0222c3c4(void *, int);
extern int func_02055140(void *, void *);
extern void func_02055060(void *, int, int, int, int, int);
extern void func_02055050(void *);
extern void *data_021c9b24;

int func_ov004_0222d5c0(char *self)
{
    if (func_ov004_0222c3c4(self + 0x1a4, 0) != 0) {
        if (func_02055140(self + 0xec, data_021c9b24) != 0) {
            func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0), 0, 0x1000, 0, 0);
            func_02055050(self + 0xec);
            return 1;
        }
    }
    return 0;
}
