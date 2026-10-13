/* func_02068ad0 @ 0x02068ad0, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02068ad0(void *r0, short r1);

void func_02068ad0(void *r0, short r1)
{
    int r3;
    int r2;

    r3 = *(int *) ((char *) r0 + 0x10);
    if (r3 < 2) {
        r2 = r3 + 1;
        *(int *) ((char *) r0 + 0x10) = r2;
        r2 = r3 << 1;
        r0 = (char *) r0 + r2;
        *(short *) ((char *) r0 + 8) = r1;
    }
}
