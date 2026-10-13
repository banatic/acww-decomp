/* func_02067f28 @ 0x02067f28, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02067f28(void *r0, int r1, int r2, int r3, int r4);

void func_02067f28(void *r0, int r1, int r2, int r3, int r4)
{
    unsigned short *p0 = (unsigned short *) ((char *) r0 + 0xa0);
    *p0 = 0;
    *(int *) ((char *) r0 + 0xa4) = r1;
    *(int *) ((char *) r0 + 0xa8) = r2;
    *(int *) ((char *) r0 + 0xac) = r3;
    *(int *) ((char *) r0 + 0xb0) = r4;
    *(int *) ((char *) r0 + 0xa8) = *(int *) ((char *) r0 + 0xa8) * 3;
    *(int *) ((char *) r0 + 0xa8) = *(int *) ((char *) r0 + 0xa8) >> 1;
}
