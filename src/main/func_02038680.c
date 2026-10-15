/* func_02038680 @ 0x02038680, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a7c(void *arg);
extern int func_020b9f80(void *arg1, void *arg2, int arg3, int arg4, int arg5);

void func_02038680(void *s, int n)
{
    char *p = *(char **) ((char *) s + 0x60);
    char *q = p + *(int *) (p + 8);
    char *r = q + *(unsigned short *) (q + 0xa);
    char *t = q + *(int *) (r + 8);
    int a = func_02057a7c(t);
    func_020b9f80((char *) s + 0xa0, (char *) s + 0x2e4, a + (n << 11), 0x800, 2);
}
