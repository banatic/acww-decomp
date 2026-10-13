/* func_02094f34 @ 0x02094f34, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *r0, int r1, int r2);

void func_02094f34(void *r0, int r1, int r2)
{
    MI_CpuCopy8((char *) r0 + 0xe, r1, r2 << 1);
}
