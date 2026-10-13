/* func_ov068_02271e4c @ 0x02271e4c, 0x2c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

void func_ov068_02271e4c(void *r0)
{
    int r1;
    int r2;
    short *r0_short;

    r2 = *(int *) ((char *) r0 + 0x5c);
    r1 = r2 - 0x1c00;
    *(int *) ((char *) r0 + 0x5c) = r1;

    r2 = *(int *) ((char *) r0 + 0x64);
    r1 = r2 + 0x2c00;
    *(int *) ((char *) r0 + 0x64) = r1;

    r1 = 0x8e;
    r2 = *(short *) ((char *) r0 + r1);
    r1 = r2 + 0x8000;
    r0_short = (short *) ((char *) r0 + 0x8e);
    *r0_short = (short) r1;
}
