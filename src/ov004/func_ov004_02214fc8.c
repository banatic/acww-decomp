/* func_ov004_02214fc8 @ 0x02214fc8, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051f4c(int a, int b, int c);
extern void func_02054cdc(void *argument0);
extern int func_020b65c4(void);
extern void func_ov004_0220d280(unsigned char *argument0, unsigned char argument1, int argument2);
extern int func_ov004_0220d2a8(char *argument0);
extern int func_ov004_0220fd8c(char *argument0);
extern int func_ov004_02215298(char *argument0, int *argument1);

void func_ov004_02214fc8(char *self)
{
    // DECLS
    int v3;
    int v5;
    // ENDDECLS
    func_ov004_02215298((char *) (self), (int *) (self + 0x5c));
    func_02054cdc(self + 0x538);
    v3 = func_ov004_0220d2a8(self + 0x740);
    if (v3 != 0x0) {
        func_ov004_0220d280((unsigned char *) (self + 0x740), 0, 0);
        v5 = func_020b65c4();
        func_02051f4c((int) (v5), (int) (self + 0x5c), (int) (func_ov004_0220fd8c(self)));
    }
}
