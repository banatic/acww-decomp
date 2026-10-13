/* func_ov094_02299c40 @ 0x02299c40, 0x1c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_02299c5c(void);
extern void func_ov094_022999a8(void *, int);

void func_ov094_02299c40(void *arg)
{
    int *p = (int *) arg;
    *p = func_ov094_02299c5c();
    ((char *) arg)[0x13] = 0;
    func_ov094_022999a8(arg, 2);
}
