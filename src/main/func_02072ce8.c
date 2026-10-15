/* func_02072ce8 @ 0x02072ce8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02072b9c(void *p);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

extern void *func_02072da4(void *);

void *func_02072ce8(void *p)
{
    func_02072b9c((char *) p + 0x11a0);
    __cxa_vec_cleanup((void *) (p), 8, 0x234, (((void (*)(void *)) func_02072da4)));
    return p;
}
