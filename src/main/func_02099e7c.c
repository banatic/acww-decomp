/* func_02099e7c @ 0x02099e7c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern int func_02099640(void);
extern void func_0209ac50(int, int, int);

void func_02099e7c(int a, int b)
{
    int x;
    func_020984e8();
    x = func_02099640();
    func_0209ac50(x, a, b);
}
