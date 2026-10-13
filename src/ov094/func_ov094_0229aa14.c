/* func_ov094_0229aa14 @ 0x0229aa14, 0x44 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209a088(void *p, int a, int b);

void func_ov094_0229aa14(unsigned int p1, int p2, int p3, int p4)
{
    volatile unsigned short local;
    local = 0xfff1;
    local = p3;
    if (p2 >= 0 && p2 <= 14) {
        func_0209a088((unsigned short *) &local, p4, p2);
    } else if (p2 >= 15 && p2 <= 29) {
        ((unsigned short *) (*(unsigned int *) ((char *) p1 + 0xa34)))[p2 - 15] = p3;
    }
}
