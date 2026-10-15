/* func_02057a20 @ 0x02057a20, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a40(void *ptr, const char *);
extern void *func_020579f0(void *obj, int k);

void *func_02057a20(void *p0, int p1)
{
    int r = func_02057a40(p0, (const char *) p1);
    if (r == -1) {
        return 0;
    }
    return func_020579f0(p0, r);
}
