/* func_0209ac04 @ 0x0209ac04, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209ad9c(int a, int b);
extern int func_0209b4d4(void *);
extern int func_0209bd44(void *);
extern int func_0209bba8(int x);

int func_0209ac04(int a)
{
    int t;
    t = func_0209b4d4((void *) func_0209ad9c(a, 0));
    if (func_0209bd44((void *) t) != 0) {
        if (func_0209bba8(t) == 1) {
            return 1;
        }
    }
    return 0;
}
