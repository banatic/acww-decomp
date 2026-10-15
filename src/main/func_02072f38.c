/* func_02072f38 @ 0x02072f38, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099870(int);
extern void func_02072eec(int a, int b);

void func_02072f38(int a)
{
    int b;
    b = func_02099870((int) func_020984e8());
    func_02072eec(a, b);
}
