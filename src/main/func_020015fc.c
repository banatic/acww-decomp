/* func_020015fc @ 0x020015fc, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int MIi_CpuClearFast(int arg);
int func_020015fc(int arg)
{
    volatile int local = arg;
    return MIi_CpuClearFast(local);
}
