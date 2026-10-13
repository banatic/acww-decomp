/* func_02065cc8 @ 0x02065cc8, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02065d0c(void *, void *, void *, int);
extern void MI_CpuFill8(void *, int, int);

void func_02065cc8(void *p)
{
    char buf[2];
    MI_CpuFill8(p, 0, 0x4a);
    buf[0] = 0x23;
    func_02065d0c(buf, p, (char *) p + 0x48, 0);
    buf[1] = 0x26;
    func_02065d0c(buf + 1, (char *) p + 0x14, (char *) p + 0x49, 0);
}
