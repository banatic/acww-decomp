/* func_02019a2c @ 0x02019a2c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);

void func_02019a2c(void *param0, void *param1, unsigned short *param2, unsigned char *param3)
{
    unsigned char temp;

    MI_CpuCopy8(param3, param0, 2);
    MI_CpuCopy8(param3 + 2, param1, 2);
    temp = param3[4];
    *param2 = temp;
}
