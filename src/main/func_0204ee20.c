/* func_0204ee20 @ 0x0204ee20, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02030e4c(int);
extern int func_02031af0(int, int);

int func_0204ee20(int a, int b, int c)
{
    int e;

    func_02030e4c(*(int *) (a + 0x1c));
    e = func_02031af0(b, c);
    func_02030e4c(0);
    return e;
}
