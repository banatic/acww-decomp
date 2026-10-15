/* func_ov054_02261d54 @ 0x02261d54, 0x38 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int func_020154b4(unsigned char *p, unsigned short *addr, int a, int b, int c);

void func_ov054_02261d54(unsigned char *p)
{
    int stackArg;
    unsigned short localHalf;
    if (p[0xbc] == 0) {
        localHalf = 0x1565;
        stackArg = 1;
        func_020154b4(p, &localHalf, 0, 5, stackArg);
        p[0xbc] = 1;
    }
}
