/* func_ov093_0229939c @ 0x0229939c, 0x24 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void MIi_CpuClear16(unsigned short, void *, int);

void func_ov093_0229939c(void *arg0, void *arg1, int arg2)
{
    volatile unsigned short local;
    local = *(unsigned short *) ((char *) arg0 + 0x1028);
    MIi_CpuClear16(local, (char *) arg1 + (arg2 << 6), 0x40);
}
