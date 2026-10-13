/* func_020be5d0 @ 0x020be5d0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} Src;
extern void func_020042a0(char *dst, void *c);

void func_020be5d0(char *self, int idx, void *c, Src *src)
{
    if (*(unsigned char *) (self + 0xc0)) {
        int off = idx * 0xc;
        volatile char *base = self;
        func_020042a0((char *) base + off, c);
        {
            int v0 = *(volatile int *) &src->a;
            *(int *) (base + off + 0x60) = v0;
        }
        *(int *) (base + off + 0x64) = src->b;
        *(int *) (base + off + 0x68) = src->c;
    }
}
