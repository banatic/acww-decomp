/* func_02042418 @ 0x02042418, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *src, void *dst, int size);

void func_02042418(unsigned char *p0, void *p1, void *p2, int p3, unsigned char p4)
{
    MI_CpuCopy8(p1, p0 + 0xc8, 8);
    MI_CpuCopy8(p2, p0 + 0xd0, 8);
    *(int *) (p0 + 0xd8) = p3;
    *(unsigned char *) (p0 + 0xdc) = p4;
    *(unsigned char *) (p0 + 0x10e8) = 1;
}
