/* func_ov004_022473a8 @ 0x022473a8, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203ad58(void);
extern void func_0203c99c(int a, int b);
extern void func_0203caa4(void *argument0, int argument1, void *argument2);
extern int func_02095794(int argument0);
extern void *data_020ca158;

int func_ov004_022473a8(char *self)
{
    // DECLS
    int v4;
    // ENDDECLS
    func_0203caa4(self, *(int *) ((char *) &data_020ca158 + 0x10), 0x0);
    func_0203c99c((int) (self), (int) (0x0));
    v4 = func_02095794(0x4);
    *(int *) (self + 0x110) = *(int *) ((char *) v4);
    *(int *) (self + 0x114) = *(int *) ((char *) v4 + 0x4);
    *(int *) (self + 0x118) = *(int *) ((char *) v4 + 0x8);
    func_0203ad58();
    return 0x1;
}
