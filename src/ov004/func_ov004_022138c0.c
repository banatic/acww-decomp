/* func_ov004_022138c0 @ 0x022138c0, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov004_022531c0[];
extern short func_0205790c(int a, char *b);
int func_ov004_022138c0(char *self)
{
    *(short *) (self + 0x844) = func_0205790c(*(int *) (self + 0x594), data_ov004_022531c0);
    return 1;
}
