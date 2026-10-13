/* func_02073c90 @ 0x02073c90, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int);

int func_02073c90(int *a, int b)
{
    int c;
    c = func_02077b58(b);
    return *(int *) ((char *) a + (c << 2) + 0x18);
}
