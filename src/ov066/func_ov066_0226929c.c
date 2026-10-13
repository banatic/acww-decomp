/* func_ov066_0226929c @ 0x0226929c, 0x24 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern char *data_ov066_0226bdf4;
extern void MI_CpuFill8(void *, int, unsigned int);

void func_ov066_0226929c(void)
{
    MI_CpuFill8(data_ov066_0226bdf4 + 0x28, 0, 0x60);
}
