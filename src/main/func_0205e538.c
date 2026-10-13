/* func_0205e538 @ 0x0205e538, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0205e538(char *base, int i, int j, int val)
{
    char *p;
    p = base + (i << 3);
    p += (j << 2);
    *((int *) (p + 0x190)) = val;
}
