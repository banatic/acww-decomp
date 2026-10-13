/* func_02077898 @ 0x02077898, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *, void *, unsigned int);

unsigned short func_02077898(const void *param)
{
    unsigned short value;
    MI_CpuCopy8(param, &value, 2);
    return value;
}
