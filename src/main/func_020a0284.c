/* func_020a0284 @ 0x020a0284, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a1954(int, char *, int);
extern int func_020984e8(void);
extern void func_02098fd0(int, int);
extern int func_0208b500(void);
extern void func_0208d0bc(int, int, int);
extern char data_020e3c2c[];

void func_020a0284(int a, int b)
{
    if (b == 0) {
        func_020a1954(a, data_020e3c2c, 105);
    }
    func_0208d0bc((func_02098fd0(func_020984e8(), 2), func_0208b500()), 0, 1);
}
