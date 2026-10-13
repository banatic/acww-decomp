/* func_02098f0c @ 0x02098f0c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098f70(int);
extern void func_02098ee8(unsigned short *a, int b, int c);

int func_02098f0c(unsigned short *p0, unsigned short *p1, int p2, int p3)
{
    int result = 0;
    if (func_02098f70(p2) == 1) {
        *(unsigned short *) ((char *) p0 + p2 * 2 + 0xA4A) = *p1;
        func_02098ee8(p0, p2, p3);
        result = 1;
    }
    return result;
}
