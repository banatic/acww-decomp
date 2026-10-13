/* func_02066650 @ 0x02066650, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *param1, int param2, int param3);

void func_02066650(void *param1)
{
    MI_CpuFill8(param1, 0, 0x100);
    *(unsigned short *) ((char *) param1 + 0xfc) = 0xfff1;
}
