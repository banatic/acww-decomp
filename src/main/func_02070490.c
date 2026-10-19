/* func_02070490 @ 0x02070490, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200467c(int cmd);
extern int func_0208b500(void);
extern void func_0208d0bc(int a, int b, int c);
extern int data_020df6a8[];

void func_02070490(int param)
{
    if (param == 0) {
        func_0200467c(0x67);
    } else {
        func_0200467c(0x66);
    }
    func_0208d0bc(func_0208b500(), data_020df6a8[param], 0);
}
