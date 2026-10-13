/* func_ov004_02239460 @ 0x02239460, 0x12 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int n);
char *func_ov004_02239460(char *a, char *b)
{
    return a + func_020644cc(b - a);
}
