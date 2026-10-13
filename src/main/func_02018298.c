/* func_02018298 @ 0x02018298, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057bf0(int);
extern int func_02057d0c(int, void *);
extern void func_02016764(void *, void *, int, unsigned short, int, int, int, int);
extern void func_02012444(unsigned int, unsigned short, int);
extern volatile unsigned short data_020c80f8;

void func_02018298(void *self, void *other)
{
    unsigned short h;
    unsigned int v;

    if (func_02057bf0(3) != 0) {
        return;
    }
    if (func_02057d0c(4, other) == 0) {
        return;
    }

    h = data_020c80f8;
    func_02016764((char *) other + 0x334, other, 0x26, data_020c80f8, 1, 0x1000, 0, 0);

    v = *(unsigned int *) ((char *) other + 0x628);
    if (v != 0) {
        func_02012444(v, h, 0);
    }
    *(unsigned char *) ((char *) self + 0x98) = 4;
}
