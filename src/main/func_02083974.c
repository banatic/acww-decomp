/* func_02083974 @ 0x02083974, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208399c(unsigned int, int);
extern void func_02083a3c(void *, int);

void func_02083974(void *self, unsigned int index)
{
    if (index < *(unsigned int *) ((char *) self + 4)) {
        unsigned int n4 = 0;
        void *base;
        n4 += index;
        base = func_0208399c(0, index);
        func_02083a3c((char *) base + 8 + index * 8, n4);
    }
}
