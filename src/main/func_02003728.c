/* func_02003728 @ 0x02003728, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *dst, const void *src, int size);

void func_02003728(void *a, void *b)
{
    MI_CpuCopy8(b, a, 0x10);
}
