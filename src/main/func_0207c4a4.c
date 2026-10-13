/* func_0207c4a4 @ 0x0207c4a4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208150c(void *);
extern int func_02003704(void *);
extern int func_02003648(void *);

void *func_0207c4a4(void *base, int param)
{
    int i;
    for (i = 0; i < 8; i++) {
        void *node = func_0208150c(base);
        if (func_02003704(node) != 0 && param == func_02003648(node)) {
            return base;
        }
        base = (char *) base + 0x7ec;
    }
    return 0;
}
