/* func_020bde5c @ 0x020bde5c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209def4(void *ptr);
extern unsigned int func_0209dedc(void);

void func_020bde5c(void *base)
{
    unsigned int mode;
    unsigned short val;
    unsigned int *dst;

    func_0209def4((char *) base + 0x2f18);
    mode = func_0209dedc();
    dst = (unsigned int *) ((char *) base + 0x2f1c);
    *dst = mode;
    val = *(unsigned short *) ((char *) base + 0x2f18);
    *(unsigned short *) ((char *) base + 0x2f1a) = val;
    *(unsigned int *) ((char *) base + 0x2f20) = *dst;
}
