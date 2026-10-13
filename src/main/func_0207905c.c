/* func_0207905c @ 0x0207905c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02095794(int i);
extern void func_0204f818(int *x, int *y, void *v);
extern int func_02096190(int i);
int func_0207905c(int a, int b)
{
    int i;
    int r = 0;
    int x = 0;
    int y = 0;
    for (i = 0; i < 4; i++) {
        void *v = func_02095794(i);
        if (v != 0) {
            func_0204f818(&x, &y, v);
            if (x == a && y == b) {
                r = func_02096190(i);
                break;
            }
        }
    }
    return r;
}
