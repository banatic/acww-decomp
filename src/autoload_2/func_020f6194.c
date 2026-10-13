/* func_020f6194 @ 0x020f6194, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndPlayerReadVariable(void *p, int mode, short *value);

void func_020f6194(char *p)
{
    short a, b;
    b = -1;
    a = -1;
    NNS_SndPlayerReadVariable(p, 4, &a);
    NNS_SndPlayerReadVariable(p, 3, &b);
    p[8] = (char) a;
    p[9] = (char) b;
}
