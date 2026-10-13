/* func_020850b8 @ 0x020850b8, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_02085148(unsigned short *p);

int func_020850b8(int *out0, int *out1, unsigned short *p2)
{
    unsigned char *ret = func_02085148(p2);
    if (ret != 0 && ret[0] != 0) {
        *out0 = ret[1];
        *out1 = ret[2];
        return 1;
    }
    return 0;
}
