/* func_02071658 @ 0x02071658, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02072824(void);
extern int func_02072830(int, int);
extern void *func_0207282c(void *record);

int func_02071658(int arg)
{
    int ret1 = func_02072824();
    func_02072830(ret1, arg);
    return (int) func_0207282c((void *) ret1);
}
