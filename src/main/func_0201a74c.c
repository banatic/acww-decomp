/* func_0201a74c @ 0x0201a74c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201a720(void *p, void *q, int n);
extern void MI_CpuFill8(void *p, int a, int b);

void func_0201a74c(void *p)
{
    MI_CpuFill8(p, 0xff, 0x10);
    func_0201a720(p, (char *) p + 0x10, 2);
    *(unsigned int *) ((char *) p + 0x1c) = 0x137;
    *(unsigned char *) ((char *) p + 0x24) = 2;
    *(unsigned char *) ((char *) p + 0x25) = 0x3c;
    *(unsigned char *) ((char *) p + 0x27) = 0;
    *(unsigned char *) ((char *) p + 0x26) = 0;
}
