/* func_020ae8e4 @ 0x020ae8e4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b0038(void *a, void *b, void *c, int d, int e);

int func_020ae8e4(void *a, void *b, int c)
{
    return func_020b0038(b, a, (char *) a + 0x10, 6, c);
}
