/* func_ov134_0229a8e8 @ 0x0229a8e8, 0x2e bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229a96c(void *, int, int);

void func_ov134_0229a8e8(void *p)
{
    int i;
    for (i = 0; i <= 5; i++) {
        func_ov134_0229a96c(p, i, 3);
    }
    for (i = 0; i <= 5; i++) {
        ((char *) p + i)[0x98] = 0;
    }
}
