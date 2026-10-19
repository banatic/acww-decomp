/* func_0204c048 @ 0x0204c048, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c064(int a, int b);
extern void func_0204b3cc(int a, int b);

void func_0204c048(int a, int b, int c)
{
    int temp;

    temp = func_0204c064(b, c);
    func_0204b3cc(a, temp);
}
