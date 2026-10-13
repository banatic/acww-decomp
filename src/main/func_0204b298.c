/* func_0204b298 @ 0x0204b298, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0204b298(void *param0);

unsigned short func_0204b298(void *param0)
{
    unsigned short r1;
    unsigned short r2;
    unsigned short r0;

    r2 = 0;
    r1 = *(unsigned short *) param0;
    r0 = 0x1431;
    if (r1 < r0) {
        goto label_0204b2aa;
    }
    r0 = 0x1470;
    if (r1 > r0) {
        goto label_0204b2aa;
    }
    r2 = 1;
label_0204b2aa:
    if (r2 == 0) {
        goto label_0204b2b2;
    }
    return 1;
label_0204b2b2:
    return 0;
}
