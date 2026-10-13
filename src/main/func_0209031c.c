/* func_0209031c @ 0x0209031c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209035c(void *);

void func_0209031c(unsigned char *p)
{
    int i;

    for (i = 0; i < 10; i++) {
        func_0209035c(p);
        p += 8;
    }
}
