/* check_in_gate_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222d0f4 @ 0x0222d0f4, 0x60 bytes, Thumb
 * func_ov004_0222d0bc @ 0x0222d0bc, 0x38 bytes, Thumb
 * func_ov004_0222d04c @ 0x0222d04c, 0x70 bytes, Thumb
 */

extern void func_02055060(void *argument0, int argument1, int argument2, int argument3, unsigned short argument4,
                          unsigned short argument5);
extern int func_02055e00(int argument0);
extern void func_02056440(int argument0, int argument1, int argument2, int argument3, int argument4, unsigned short argument5);
extern int func_ov004_0222c3b4(char *argument0, int argument1);
extern int func_ov004_0222c3c4(char *argument0, int argument1);
extern void func_02055124(void *object);
extern void func_02056ffc(void *object);
extern void func_ov004_0222d30c(char *object, int value);
extern void func_0200467c(int command);

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

void func_ov004_0222d0bc(char *self)
{
    func_02055124(self + 0xec);
    func_02056ffc(self + 0x290);
    *(int *) *(int *) (self + 0x2a8) = *(int *) (self + 0x298);
    func_ov004_0222d30c(self, 0);
}

int func_ov004_0222d04c(char *self)
{
    // DECLS
    int v3;
    // ENDDECLS
    func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0x1), 0x1, 0x1000, 0x0, 0x0);
    v3 = func_02055e00((int) (self + 0xec));
    func_02056440((int) (self + 0x290), (int) (v3), (int) (func_ov004_0222c3b4(self + 0x1a4, 0x1)), (int) (0x1),
                  (int) (0x1000), (unsigned short) (0x0));
    func_0200467c(0x4eb);
    return 0x1;
}
