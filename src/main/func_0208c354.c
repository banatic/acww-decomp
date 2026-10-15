/* func_0208c354 @ 0x0208c354, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f0(void *dst, void *src);
extern void func_0208a1ec(void *dst, void *src);
extern void *func_0208a144(void *dst);
extern char data_020d5b3c[];

void func_0208c354(void *self)
{
    int i;
    char *base;
    char *p;

    base = (char *) self;
    *(int *) (base + 0xc0) = 1;
    for (i = 0; i < 9; i++) {
        p = base + 0xc + i * 0x14;
        func_0208a1f0(p, data_020d5b3c + (i + 0xe) * 8);
        func_0208a1ec(p, (char *) 1);
        func_0208a144(p);
    }
}
