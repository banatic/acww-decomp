/* func_0203fb80 @ 0x0203fb80, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203fda0(int, int);

extern unsigned char data_021c74d4[];

void func_0203fb80(int *r5, int *r4, int r2)
{
    void *r0;
    int r1;

    r0 = func_0203fda0(r2, (unsigned int) data_021c74d4);
    if (r0 != 0) {
        r1 = *(int *) ((char *) r0 + 4);
        *r5 = r1;
        r1 = *(int *) ((char *) r0 + 8);
        *r4 = r1;
    } else {
        *r5 = 1;
        *r4 = 1;
    }
}
