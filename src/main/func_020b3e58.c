/* func_020b3e58 @ 0x020b3e58, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020b3f2c(void *);

int func_020b3e58(void *a, int *b, int *c, unsigned int d)
{
    if (d < func_020b3f2c(a)) {
        char *base = (char *) a + (d << 2);
        *b = *(signed char *) (base + 2);
        *c = *(signed char *) (base + 3);
        return 1;
    } else {
        return 0;
    }
}
