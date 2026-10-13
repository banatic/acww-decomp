/* func_020a0244 @ 0x020a0244, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a1954(int a, void *b, int c);
extern int func_020984e8(void);
extern void func_02098fd0(int a, int b);
extern int func_020a01ec(void);
extern int func_0208b500(void);
extern void func_0208d0bc(int a, int b, int c);
extern void func_02098ff8(int a, int b);
extern char data_020e3c40[];

void func_020a0244(int arg0)
{
    func_020a1954(arg0, data_020e3c40, 7);
    func_02098fd0(func_020984e8(), 2);
    if (func_020a01ec()) {
        func_0208d0bc(func_0208b500(), 0, 1);
        func_02098ff8(func_020984e8(), 2);
    }
}
