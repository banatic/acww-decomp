/* func_020836e0 @ 0x020836e0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02083708(void);
extern void func_020837bc(void *, int);

void func_020836e0(void *self, unsigned int index)
{
    if (index < *(unsigned int *) ((char *) self + 4)) {
        unsigned int n4 = 5;
        void *base;
        n4 += index;
        base = func_02083708();
        func_020837bc((char *) base + 8 + index * 2, n4);
    }
}
