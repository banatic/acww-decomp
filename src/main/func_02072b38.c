/* func_02072b38 @ 0x02072b38, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138d6c(void *a, int b, int c, void (*d)(void), void (*e)(void));
extern void func_02072dbc(void);
extern void func_02072da4(void);

void *func_02072b38(void *arg)
{
    func_02138d6c(arg, 8, 0x234, func_02072dbc, func_02072da4);
    return arg;
}
