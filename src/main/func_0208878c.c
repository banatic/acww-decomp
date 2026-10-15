/* func_0208878c @ 0x0208878c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *p);
extern void func_020887e8(void *p, void *q);

void func_0208878c(unsigned int *ptr, unsigned int bit)
{
    unsigned int word;
    unsigned int shift;
    unsigned int local;

    word = bit >> 5;
    shift = bit & 0x1f;
    if ((int) word < 2) {
        unsigned int *base = (unsigned int *) ((char *) ptr + 4);
        ((volatile unsigned int *) base)[word] = (1 << shift) | ((volatile unsigned int *) base)[word];
    }
    func_0209df64(&local);
    func_020887e8(ptr, &local);
}
