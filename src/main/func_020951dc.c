/* func_020951dc @ 0x020951dc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *src, void *dst, int size);
extern void func_020642a8(void *src, void *dst);

void func_020951dc(void *src, void *dst)
{
    MI_CpuCopy8((char *) src + 0x10, (char *) dst + 0x10, 0xc);
    *(unsigned short *) ((char *) dst + 0xe) = *(unsigned short *) ((char *) src + 0xe);
    *(char *) ((char *) dst + 0x1c) = *(signed char *) ((char *) src + 0x1c);
    func_020642a8(src, dst);
}
