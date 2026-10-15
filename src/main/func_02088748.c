/* func_02088748 @ 0x02088748, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void func_02088748(const void *a, void *b)
{
    MI_CpuCopy8(a, b, 1);
}
