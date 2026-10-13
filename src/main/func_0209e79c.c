/* func_0209e79c @ 0x0209e79c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209dbb4(void *);
extern void func_0206f80c(void *);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern unsigned int func_0209db78(void *, void *);
extern unsigned int func_0209db50(void *, void *);
extern void func_0209dfc0(void);

void func_0209e79c(unsigned char *base)
{
    unsigned int buf0[2];
    unsigned int buf1[2];
    unsigned int buf2[2];
    unsigned int v1;
    unsigned int v2;

    func_0209dbb4(base + 0x173cc);
    buf0[0] = 0;
    buf0[1] = 0;
    func_0206f80c(buf0);
    MI_CpuCopy8(buf0, buf1, 8);
    v1 = func_0209db78(base + 0x173cc, buf1);
    MI_CpuCopy8(buf0, buf2, 8);
    v2 = func_0209db50(base + 0x173cc, buf2);
    *(unsigned int *) (base + 0x173cc) = v1;
    *(unsigned short *) (base + 0x173d0) = (unsigned short) v2;
    func_0209dfc0();
}
