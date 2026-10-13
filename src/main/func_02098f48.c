/* func_02098f48 @ 0x02098f48, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098f70(int);

unsigned short *func_02098f48(void *base, int n)
{
    unsigned short *res = 0;

    if (func_02098f70(n) == 1) {
        res = (unsigned short *) ((char *) base + 0xa4a) + n;
    }

    return res;
}
