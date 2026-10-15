/* func_020642bc @ 0x020642bc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dest, unsigned int size);
void func_020642bc(void *dest, const void *src)
{
    *(unsigned short *) dest = *(const unsigned short *) src;
    MI_CpuCopy8((const char *) src + 2, (char *) dest + 2, 12);
}
