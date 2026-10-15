/* func_02060878 @ 0x02060878, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_020ba01c(unsigned char *);
extern void func_02055ce8(void *);
extern void *func_02055cf4(void *);
extern void *func_02055764(void *);
extern void *func_0205577c(void *);

unsigned char *func_02060878(unsigned char *self)
{
    unsigned char *p;
    unsigned char *end;
    int i;

    __cxa_vec_ctor((void *) (self + 0x24), 9, 0x14, (((void (*)(void *)) func_02055cf4)), (void (*)(void *)) func_02055ce8);
    p = self + 0xd8;
    end = self + 0x1d4;
    do {
        func_020ba01c(p);
        p += 0x1c;
    } while (p != end);
    __cxa_vec_ctor((void *) (end), 9, 0x9c, (((void (*)(void *)) func_0205577c)), (((void (*)(void *)) func_02055764)));
    i = 0;
    do {
        int *p2 = (int *) self + i;
        *p2 = 0;
        *(int *) ((char *) p2 + 0x750) = 0;
        i++;
    } while (i < 9);
    return self;
}
