/* func_020bb214 @ 0x020bb214, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209e380(unsigned long long *p, int a);

int func_020bb214(void)
{
    unsigned long long local = 0;
    int uninit;

    local = 0x0000000101000000ULL;
    return (unsigned short) ((func_0209e380(&local, uninit) % 64) * 8);
}
