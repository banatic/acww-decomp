/* func_02031c14 @ 0x02031c14, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c9090[];

int func_02031c14(int r0, int r1)
{
    int r2;

    if (r0 < 0x7c) {
        r2 = data_020c9090[30 * r0];
    } else {
        r2 = 0;
    }
    if (r2 == 0) {
        goto L48;
    }
    if (r1 == 1) {
        goto L34;
    }
    if (r1 != 2) {
        goto L44;
    }
    goto L3c;

L34:
    if (r0 != 0x16) {
        goto L44;
    }
    return 0;

L3c:
    if (r0 != 0x16) {
        goto L44;
    }
    return 0;

L44:
    return 1;

L48:
    return 0;
}
