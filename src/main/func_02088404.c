/* func_02088404 @ 0x02088404, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020882dc(int arg);
extern void func_020882cc(char *addr, unsigned char val);
extern void func_020882f0(char *addr);
extern void func_02088318(void);
extern char data_021dc7a8[];
extern char data_021f3b8a;

void func_02088404(int arg)
{
    char *base;
    int diff;

    if (arg < 1) {
        return;
    }
    base = data_021dc7a8;
    diff = func_020882dc((int) &data_021f3b8a) - arg;
    if (diff < 0) {
        diff = 0;
    }
    if (diff <= 0) {
        func_020882f0(base + 0x173e2);
    } else {
        func_020882cc(base + 0x173e2, (unsigned char) diff);
    }
    func_02088318();
}
