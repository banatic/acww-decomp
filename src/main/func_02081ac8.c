/* func_02081ac8 @ 0x02081ac8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dst, int val, int size);
extern void MI_CpuCopy8(const void *src, void *dst, int size);

void func_02081ac8(void *param0, void *param1, int param2)
{
    int capped;
    unsigned short *flags;

    capped = param2;
    MI_CpuFill8((char *) param0 + 0x3e, 0, 0x14);
    if (capped > 0xa) {
        capped = 0xa;
    }
    MI_CpuCopy8(param1, (char *) param0 + 0x3e, capped << 1);
    flags = (unsigned short *) ((char *) param0 + 0x7c);
    *flags = (unsigned short) (*flags | 8);
}
