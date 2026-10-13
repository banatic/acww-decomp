/* func_020a2468 @ 0x020a2468, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021ee418;
extern void MI_CpuCopy8(int, int, int);

void func_020a2468(int p0)
{
    MI_CpuCopy8(*(int *) ((char *) (((int) (p0) + (192))) + (0)), (int) &data_021ee418, 2384);
}
