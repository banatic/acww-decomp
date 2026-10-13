/* func_020be5a0 @ 0x020be5a0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} Src;
extern void func_02004290(void *entry, int param3);

void func_020be5a0(char *self, int idx, int param3, Src *src)
{
    if (*(unsigned char *) (self + 0xc0)) {
        int off = idx * 0xc;
        volatile char *base = self;
        func_02004290((char *) base + off, param3);
        {
            int v0 = *(volatile int *) &src->a;
            *(int *) (base + off + 0x60) = v0;
        }
        *(int *) (base + off + 0x64) = src->b;
        *(int *) (base + off + 0x68) = src->c;
    }
}
