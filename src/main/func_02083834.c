/* func_02083834 @ 0x02083834, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208385c(void);
extern void func_020838fc(void *, int);

void func_02083834(void *self, unsigned int index)
{
    if (index < *(unsigned int *) ((char *) self + 4)) {
        unsigned int n4 = 0;
        void *base;
        n4 += index;
        base = func_0208385c();
        func_020838fc((char *) base + 8 + index * 8, n4);
    }
}
