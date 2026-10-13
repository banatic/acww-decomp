/* func_02064f84 @ 0x02064f84, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b3658(void *ptr);

void func_02064f84(void *arg)
{
    int f = func_020b3658((char *) arg + 0x1c);
    int a = ((f << 4) >> 12) + 15;
    int b = ((f << 2) >> 12) + 25;
    int c = ((9 * f) >> 12) + 20;
    *(unsigned short *) ((char *) arg + 0x34) = (unsigned short) ((a << 10) | (b | (c << 5)));
}
