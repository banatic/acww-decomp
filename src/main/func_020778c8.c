/* func_020778c8 @ 0x020778c8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(int p1, short *p2, int p3);

int func_020778c8(int p1)
{
    short local;
    MI_CpuCopy8(p1, &local, 2);
    return local;
}
