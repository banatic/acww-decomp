/* path_walker_10: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020139f0 @ 0x020139f0, 0x1c bytes, Thumb
 * func_020139ec @ 0x020139ec, 0x2 bytes, Thumb
 * func_020139bc @ 0x020139bc, 0x2e bytes, Thumb
 */

extern void MI_CpuFill8(void *dst, int val, int size);

int func_020139f0(int *p0)
{
    p0[3] = 0;
    p0[4] = 0;
    p0[5] = 0;
    p0[6] = 0;
    p0[7] = 0;
    p0[8] = 0;
    *(int *) ((char *) (((int) ((int) p0) + (148))) + (0)) = 0;
    *(int *) ((char *) (((int) ((int) p0) + (152))) + (0)) = 0;
    return (int) p0;
}

void func_020139ec(void *p) {}

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
