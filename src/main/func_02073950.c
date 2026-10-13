/* func_02073950 @ 0x02073950, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int b);

int func_02073950(char *a, int b)
{
    char *p = a + (func_02077b58(b) << 2);
    if (*(unsigned int *) (p + 0x58) == 0) {
        return 3;
    } else {
        return *(unsigned int *) (p + 0x4c);
    }
}
