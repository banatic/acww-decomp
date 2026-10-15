/* func_02030640 @ 0x02030640, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02030708(void *, const void *, unsigned int);

void func_02030640(int r0, int r1, int r2, int r3)
{
    int r5 = r0;
    int r4 = r3;
    func_02030708((void *) r0, (const void *) r1, (unsigned int) r2);
    *(int *) (r5 + 0x10) = r4;
}
