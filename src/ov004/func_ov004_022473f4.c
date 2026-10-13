/* func_ov004_022473f4 @ 0x022473f4, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203ad68(void);
extern void func_0203c99c(void *, int);
extern void func_0203caa4(void *, int, int);
extern void *data_021fbee8;

int func_ov004_022473f4(char *self)
{
    // DECLS
    // ENDDECLS
    func_0203caa4(self, 0x11, 0x0);
    func_0203c99c(self, 0x0);
    *(int *) (self + 0x110) = *(int *) ((char *) &data_021fbee8);
    *(int *) (self + 0x114) = *(int *) ((char *) &data_021fbee8 + 0x4);
    *(int *) (self + 0x118) = *(int *) ((char *) &data_021fbee8 + 0x8);
    func_0203ad68();
    return 0x1;
}
