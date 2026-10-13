/* func_01ffd3e8 @ 0x01ffd3e8, 0x28 bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

int func_01ffd3e8(unsigned char *p)
{
    if (p[0x0f] != 0) {
        goto L0;
    }
    if ((p[0x13] & 8) == 0) {
        goto L1;
    }
L0:
    return 0;
L1:
    return 1;
}
