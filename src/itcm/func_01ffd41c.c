/* func_01ffd41c @ 0x01ffd41c, 0x28 bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

int func_01ffd41c(unsigned char *p)
{
    if (p[0x0f] != 0) {
        goto L0;
    }
    if ((p[0x13] & 2) == 0) {
        goto L1;
    }
L0:
    return 0;
L1:
    return 1;
}
