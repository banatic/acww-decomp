/* func_ov004_0222d0f4 @ 0x0222d0f4, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055060(void *argument0, int argument1, int argument2, int argument3, unsigned short argument4,
                          unsigned short argument5);
extern int func_02055e00(int argument0);
extern void func_02056440(int argument0, int argument1, int argument2, int argument3, int argument4, unsigned short argument5);
extern int func_ov004_0222c3b4(char *argument0, int argument1);
extern int func_ov004_0222c3c4(char *argument0, int argument1);

int func_ov004_0222d0f4(char *self)
{
    // DECLS
    int v3;
    // ENDDECLS
    func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0x0), 0x0, 0x1000, 0x0, 0x0);
    v3 = func_02055e00((int) (self + 0xec));
    func_02056440((int) (self + 0x290), (int) (v3), (int) (func_ov004_0222c3b4(self + 0x1a4, 0x0)), (int) (0x0),
                  (int) (0x1000), (unsigned short) (0x0));
    return 0x1;
}
