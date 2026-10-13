/* func_0206844c @ 0x0206844c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void strncpy(void *, int, int);
extern void MI_CpuFill8(void *, int, int);

void func_0206844c(unsigned char *base, const unsigned char *src, int flag)
{
    base[0x1e77] = *src;
    if (flag) {
        strncpy(base + 0x1e78, flag, 25);
    } else {
        MI_CpuFill8(base + 0x1e78, 0, 26);
    }
}
