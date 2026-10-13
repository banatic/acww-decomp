/* func_02077ea4 @ 0x02077ea4, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *a, void *b, int c);

void *func_02077ea4(void *a, void *b)
{
    MI_CpuCopy8(b, a, 12);
    return a;
}
