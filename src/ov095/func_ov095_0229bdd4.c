/* func_ov095_0229bdd4 @ 0x0229bdd4, 0x42 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229be18(int, unsigned short *, unsigned short, int, int, int);

int func_ov095_0229bdd4(int a0, unsigned short *a1, unsigned short a2, int a3, int a4, int a5)
{
    int i;
    if (!func_ov095_0229be18(a0, a1, a2, a3, a4, a5)) {
        return 0;
    }
    i = a4 - 1;
    while (i > a3) {
        a1[i] = a1[i - 1];
        i--;
    }
    a1[a3] = a2;
    return 1;
}
