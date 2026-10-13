/* func_02060878 @ 0x02060878, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138d6c(unsigned char *, int, int, void (*)(void), void (*)(void));
extern void func_020ba01c(unsigned char *);
extern void func_02055ce8(void);
extern void func_02055cf4(void);
extern void func_02055764(void);
extern void func_0205577c(void);

unsigned char *func_02060878(unsigned char *self)
{
    unsigned char *p;
    unsigned char *end;
    int i;

    func_02138d6c(self + 0x24, 9, 0x14, func_02055cf4, func_02055ce8);
    p = self + 0xd8;
    end = self + 0x1d4;
    do {
        func_020ba01c(p);
        p += 0x1c;
    } while (p != end);
    func_02138d6c(end, 9, 0x9c, func_0205577c, func_02055764);
    i = 0;
    do {
        int *p2 = (int *) self + i;
        *p2 = 0;
        *(int *) ((char *) p2 + 0x750) = 0;
        i++;
    } while (i < 9);
    return self;
}
