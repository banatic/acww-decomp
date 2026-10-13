/* func_020eacf8 @ 0x020eacf8, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

int func_020eacf8(long long v)
{
    volatile unsigned short *ctrl = (volatile unsigned short *) 0x040002b0;
    volatile unsigned long long *numer = (volatile unsigned long long *) 0x040002b8;
    volatile int *res = (volatile int *) 0x040002b4;

    *ctrl = 1;
    *numer = (unsigned long long) v << 2;
    while (*ctrl & 0x8000)
        ;
    return (*res + 1) >> 1;
}
