/* func_02081ef0 @ 0x02081ef0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02095238(void *param1);
extern void MI_CpuFill8(void *param1, int param2, int param3);

void func_02081ef0(void *param1)
{
    MI_CpuFill8(param1, 0, 0x80);
    func_02095238(param1);
    *(int *) ((char *) param1 + 0x54) = 0;
    *(int *) ((char *) param1 + 0x58) = 0;
    *(unsigned short *) ((char *) param1 + 0x6a) = 0xfff1;
}
