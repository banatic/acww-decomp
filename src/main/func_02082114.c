/* func_02082114 @ 0x02082114, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *r0, int r1, int r2);

void func_02082114(void *r0, int r1, int r2)
{
    if (r2 < 4) {
    } else {
        r2 = 4;
    }
    r0 = (char *) r0 + 0xe;
    r2 = r2 << 1;
    MI_CpuCopy8(r0, r1, r2);
}
