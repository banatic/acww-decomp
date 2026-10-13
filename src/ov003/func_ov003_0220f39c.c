/* func_ov003_0220f39c @ 0x0220f39c, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *p, int a, int b, int c);

void func_ov003_0220f39c(void *p)
{
    unsigned int val;
    if (*(unsigned int *) ((char *) p + 0x704) != 0x7a) {
        func_020109a0(p, 0x38, 3, 0);
    }
    val = *(unsigned int *) ((char *) p + 0x2d4);
    val = (val << 4) >> 16;
    val = ((val - 1) << 16) >> 4;
    *(unsigned int *) ((char *) p + 0x2d8) = val;
}
