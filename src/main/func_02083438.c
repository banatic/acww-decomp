/* func_02083438 @ 0x02083438, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02083460(void);
extern void func_02083500(void *, int);

void func_02083438(void *self, unsigned int index)
{
    if (index < *(unsigned int *) ((char *) self + 4)) {
        unsigned int n4 = 4;
        void *base;
        n4 += index;
        base = func_02083460();
        func_02083500((char *) base + 8 + index * 2, n4);
    }
}
