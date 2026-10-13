/* func_0209faac @ 0x0209faac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *);
extern void MI_CpuCopy8(const void *, void *, unsigned int);

int func_0209faac(void *obj, const void *src)
{
    unsigned char local[4];
    if (src == 0) {
        func_0209df64(local);
        src = local;
    }
    MI_CpuCopy8(src, obj, 4);
    ((unsigned char *) obj)[3] = 1;
    return 1;
}
