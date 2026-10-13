/* func_0201c390 @ 0x0201c390, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ea9e4(char *a, char *b);

int func_0201c390(char *p1, char *p2)
{
    int result = 0;
    if (p2) {
        result = func_020ea9e4(p2 + 0x5c, p1 + 0x5c);
    }
    return result;
}
