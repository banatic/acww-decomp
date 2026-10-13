/* func_020139bc @ 0x020139bc, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dst, int val, int size);

void func_020139bc(void *param)
{
    MI_CpuFill8(param, 0, 0x9c);
    *(int *) ((char *) param + 0) = 2;
    *(int *) ((char *) param + 8) = 7;
    *(short *) ((char *) param + 0x24) = -1;
    *(short *) ((char *) param + 0x26) = -1;
    *(int *) ((char *) param + 0x8c) = 2;
    *(int *) ((char *) param + 0x90) = 4;
}
