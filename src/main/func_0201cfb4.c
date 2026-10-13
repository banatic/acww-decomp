/* func_0201cfb4 @ 0x0201cfb4, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0201cfb4(void *unused, char *base)
{
    int i;
    for (i = 0; i < 5; i++) {
        char *p = base + i * 2;
        base[i * 2] = 0;
        p[1] = 0;
        *(int *) (base + i * 4 + 0xc) = 0;
    }
    base[0x20] = 0;
    base[0x21] = (char) 0xff;
}
