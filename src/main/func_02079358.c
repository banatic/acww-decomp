/* func_02079358 @ 0x02079358, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0207956c(void *p);

void func_02079358(void *p)
{
    int i;
    char *base = (char *) p;

    for (i = 0; i < 8; i++) {
        func_0207956c(base + i * 0x2c);
    }

    base[0x160] = -1;
    base[0x161] = 0;
    base[0x162] = -1;
    base[0x163] = -1;
    base[0x164] = -1;
    *(int *) (base + 0x168) = 0;
    base[0x16c] = -1;
}
