/* func_02072d14 @ 0x02072d14, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02072da4(void);
extern void func_02072dbc(void);
extern void func_02072ba0(void *p);
extern void func_02138d6c(void *p, int a, int b, void (*f)(void), void (*g)(void));

void *func_02072d14(void *ptr)
{
    func_02138d6c(ptr, 8, 0x234, func_02072dbc, func_02072da4);
    func_02072ba0((char *) ptr + 0x11a0);
    return ptr;
}
