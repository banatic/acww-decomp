/* func_020ae458 @ 0x020ae458, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020ae458(unsigned int *param1, unsigned int param2);

unsigned int func_020ae458(unsigned int *param1, unsigned int param2)
{
    unsigned int r3;
    unsigned int r2;
    unsigned int r1;
    unsigned int r0;

    r3 = *param1;
    r0 = 1;
    r2 = 0x1f;
    r1 = param2 & r2;
    r2 = r0 << r1;
    r3 = r3 & r2;
    if (r3 != 0) {
        r0 = 1;
    } else {
        r0 = 0;
    }
    return r0;
}
