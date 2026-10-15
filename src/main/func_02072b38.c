/* func_02072b38 @ 0x02072b38, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_02072dbc(void *);
extern void *func_02072da4(void *);

void *func_02072b38(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 8, 0x234, (((void (*)(void *)) func_02072dbc)), (((void (*)(void *)) func_02072da4)));
    return arg;
}
