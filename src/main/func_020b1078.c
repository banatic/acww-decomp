/* func_020b1078 @ 0x020b1078, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_020b1530(int n);
extern int func_02051bb4(void *a, char *b, int c);

int func_020b1078(void *arg0, int arg1)
{
    int i;
    for (i = 0; i < 16; i++) {
        char *p;
        if (arg1 == i) {
            continue;
        }
        p = func_020b1530(i);
        if (p == 0) {
            continue;
        }
        if (func_02051bb4(arg0, p + 0x1e, 6)) {
            return 1;
        }
    }
    return 0;
}
