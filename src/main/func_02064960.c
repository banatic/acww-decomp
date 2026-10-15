/* func_02064960 @ 0x02064960, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02064980(int a, int b, int c, int d, int *e);

void *func_02064960(int a, int b, int c, ...)
{
    int *p = (int *) (((unsigned int) &c & ~3U) + 4);
    return func_02064980(a, b, 0, c, p);
}
