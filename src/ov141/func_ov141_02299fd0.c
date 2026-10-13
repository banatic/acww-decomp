/* func_ov141_02299fd0 @ 0x02299fd0, 0x34 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(int a, void *b, int c);

void func_ov141_02299fd0(char *self, int idx, int param)
{
    MI_CpuCopy8(param, self + 0xc8c + 0xe0 * idx, 0xe0);
    ((char *) self + idx)[0x1a7f] = 1;
}
