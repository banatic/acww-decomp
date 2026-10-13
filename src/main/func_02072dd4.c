/* func_02072dd4 @ 0x02072dd4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02072fcc(void *p, void *q);

int func_02072dd4(char *a, char *b)
{
    unsigned int i;
    if (func_02072fcc(a + 0x200, b + 0x200) != 0) {
        for (i = 0; i < 0x80; i++) {
            if (*(int *) a != *(int *) b) {
                return 0;
            }
            a += 4;
            b += 4;
        }
        return 1;
    }
    return 0;
}
