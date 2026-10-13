/* func_02054a34 @ 0x02054a34, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02054a34(unsigned int *p, unsigned int n)
{
    if (n >= 32) {
        *(unsigned int *) ((char *) p + 0x150) &= ~(1 << (n - 32));
    } else {
        *(unsigned int *) ((char *) p + 0x14c) &= ~(1 << n);
    }
}
