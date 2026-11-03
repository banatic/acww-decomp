/* daily_bits: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208880c @ 0x0208880c, 0x2 bytes, Thumb
 * func_02088808 @ 0x02088808, 0x2 bytes, Thumb
 * func_020887f8 @ 0x020887f8, 0x10 bytes, Thumb
 * func_020887e8 @ 0x020887e8, 0xe bytes, Thumb
 * func_020887c0 @ 0x020887c0, 0x28 bytes, Thumb
 * func_0208878c @ 0x0208878c, 0x34 bytes, Thumb
 * func_02088768 @ 0x02088768, 0x22 bytes, Thumb
 */

extern void MI_CpuFill8(void *p, int value, int size);
extern void func_0209df64(void *p);

void func_0208880c(void *object) {}

void func_02088808(void *object) {}

void func_020887f8(void *p)
{
    MI_CpuFill8((char *) p + 4, 0, 8);
}

void func_020887e8(unsigned char *r0, unsigned char *r1)
{
    r0[2] = r1[2];
    r0[1] = r1[1];
    r0[0] = r1[0];
}

int func_020887c0(unsigned int *ptr, unsigned int bit)
{
    unsigned int word;
    unsigned int shift;
    int result;

    word = bit >> 5;
    shift = bit & 0x1f;

    if ((int) word >= 2) {
        goto fail;
    }
    result = 1;
    if ((*(unsigned int *) ((char *) ptr + word * 4 + 4) & (1 << shift)) != 0) {
        goto done;
    }
fail:
    result = 0;
done:
    return result;
}

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
    func_020887e8((unsigned char *) ptr, (unsigned char *) (&local));
}

void func_02088768(unsigned int *ptr, unsigned int bit)
{
    unsigned int word;
    unsigned int shift;
    word = bit >> 5;
    shift = bit & 0x1f;
    if ((int) word < 2) {
        unsigned int *base = (unsigned int *) ((char *) ptr + 4);
        base[word] = ~(1 << shift) & ((volatile unsigned int *) base)[word];
    }
}
