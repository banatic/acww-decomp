/* func_ov066_02268024 @ 0x02268024, 0x58 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

#pragma arm

int func_ov066_02268024(unsigned char *p)
{
    if (p[0] || p[1] || p[2] || p[3] || p[4]) {
        goto ret1;
    }
    if (p[5] == 0) {
        goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}
