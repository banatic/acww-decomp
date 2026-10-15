/* func_02099e7c @ 0x02099e7c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099640(int);
extern int func_0209ac50(int, int, int);

void func_02099e7c(int a, int b)
{
    int x;
    x = func_02099640((int) func_020984e8());
    func_0209ac50(x, a, b);
}
