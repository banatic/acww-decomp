/* func_0208fedc @ 0x0208fedc, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208fe1c(void *);
extern int func_0208a1d0(void *);
extern int func_0208aef0(void *);
extern int func_0208a1b0(void *, int);
extern int func_0208aeec(void *);
extern int func_0208a198(void *, int);
extern void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);

void func_0208fedc(unsigned char *self)
{
    int a, b, c, d;

    if (self[0x28] != 0 && func_0208fe1c(self) == 0) {
        a = func_0208a1d0(self + 0x14);
        b = func_0208aef0(self);
        b += func_0208a1b0(self + 0x14, -1);
        c = func_0208aeec(self);
        d = c + func_0208a198(self + 0x14, -1);
        func_02088df8(3, a, b, d, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}
