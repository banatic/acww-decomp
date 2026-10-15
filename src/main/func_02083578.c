/* func_02083578 @ 0x02083578, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020835a0(void);
extern void func_02083640(void *, int);

void func_02083578(void *self, unsigned int index)
{
    if (index < *(unsigned int *) ((char *) self + 4)) {
        unsigned int n4 = 0;
        void *base;
        n4 += index;
        base = func_020835a0();
        func_02083640((char *) base + 8 + index * 8, n4);
    }
}
