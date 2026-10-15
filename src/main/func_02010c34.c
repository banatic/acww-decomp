/* func_02010c34 @ 0x02010c34, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205dc80(char *);
extern int func_0205db38(char *);
extern int func_0205685c(char *, int, int, int, int);

void func_02010c34(char *base)
{
    int v0;
    int v1;

    v0 = *((int *) (base + 0x3e8));
    v1 = func_0205dc80(base + 0x70d);
    func_0205685c(base + 0x710, v0, v1, 1, func_0205db38(base + 0x70f));

    v0 = *((int *) (base + 0x3e8));
    v1 = func_0205dc80(base + 0x70d);
    func_0205685c(base + 0x73c, v0, v1, 1, func_0205db38(base + 0x70f));
}
