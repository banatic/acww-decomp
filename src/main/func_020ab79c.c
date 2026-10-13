/* func_020ab79c @ 0x020ab79c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43ec;
extern void func_020a8c1c(void *);
extern void func_020a82b0(void *);
extern void MI_CpuFill8(void *, int, int);

void func_020ab79c(void *arg)
{
    unsigned char *p = arg;
    *p = data_021f43ec;
    *(int *) (p + 4) = 0;
    func_020a8c1c(p + 8);
    func_020a82b0(p + 0x64);
    *(p + 0x70) = data_021f43ec;
    MI_CpuFill8(p + 0x71, 0, 0x1a);
    *(p + 0x8b) = 0;
    *(int *) (p + 0x8c) = 0;
}
