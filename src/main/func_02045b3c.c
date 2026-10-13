/* func_02045b3c @ 0x02045b3c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02046224(char *);

void func_02045b3c(char *arg)
{
    char *p;
    int i;

    p = arg + 4;
    for (i = 0; i < 20; i++) {
        func_02046224(p);
        p += 16;
    }
}
