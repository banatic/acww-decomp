/* func_020832f8 @ 0x020832f8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02083320(void);
extern void func_020833c0(void *, int);

void func_020832f8(void *self, unsigned int index)
{
    if (index < *(unsigned int *) ((char *) self + 4)) {
        unsigned int n4 = 4;
        void *base;
        n4 += index;
        base = func_02083320();
        func_020833c0((char *) base + 8 + index * 2, n4);
    }
}
