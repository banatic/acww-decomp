/* func_0207e55c @ 0x0207e55c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099734(void);
extern int func_02098cf8(int, int);

int func_0207e55c(void)
{
    int v;
    v = func_02098cf8(func_02099734(), 1);
    if (v >= 10000 && v < 20000) {
        return 1;
    }
    return 0;
}
