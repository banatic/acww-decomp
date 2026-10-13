/* func_02073bcc @ 0x02073bcc, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int);

unsigned int func_02073bcc(char *a1, int a2, int a3)
{
    char *base;
    base = a1 + func_02077b58(a2) * 12;
    return *(unsigned int *) (base + a3 * 4 + 0x28);
}
