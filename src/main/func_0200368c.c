/* func_0200368c @ 0x0200368c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(int a, int b, int c);
extern int func_02064328(int a, void *b, int c, int d);
extern unsigned char data_020d72bc[];
extern int data_020d72a4[];

int func_0200368c(int param0, int param1, int param2, int param3)
{
    MI_CpuFill8(param0, 0, param1);
    return func_02064328(param0, data_020d72bc, data_020d72a4[param3], param2);
}
