/* func_ov117_02299a94 @ 0x02299a94, 0x10 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void func_ov117_02299a94(int a, int b)
{
    MI_CpuCopy8((const void *) a, (void *) b, 0x2000);
}
