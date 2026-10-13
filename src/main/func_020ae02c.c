/* func_020ae02c @ 0x020ae02c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b0074(void *p1, int p2, void *p3);

int func_020ae02c(void *a, void *b)
{
    return func_020b0074(b, 3, (char *) a + 16);
}
