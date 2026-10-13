/* func_02035fd8 @ 0x02035fd8, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02035fd8(char *p, int a, int b)
{
    p[0x10] = 1;
    *(int *) (p + 0x14) = a;
    *(int *) (p + 0x18) = b;
}
