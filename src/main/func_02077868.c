/* func_02077868 @ 0x02077868, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(int, unsigned short *, int);

unsigned short func_02077868(int arg0)
{
    unsigned short result;
    MI_CpuCopy8(arg0, &result, 2);
    return result;
}
