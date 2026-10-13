/* func_02046680 @ 0x02046680, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020466d8(void);

void func_02046680(void)
{
    int *p;
    int i;

    p = func_020466d8();
    for (i = 0; i < 24; i++) {
        p[0] = -1;
        p[1] = -1;
        p += 2;
    }
}
