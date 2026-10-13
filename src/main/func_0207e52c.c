/* func_0207e52c @ 0x0207e52c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099734(void);
extern int func_02098cf8(int, int);

int func_0207e52c(void)
{
    int y;
    y = func_02098cf8(func_02099734(), 1);
    if (y >= 20000 && y < 40000) {
        return 1;
    } else {
        return 0;
    }
}
