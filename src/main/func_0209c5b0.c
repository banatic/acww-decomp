/* func_0209c5b0 @ 0x0209c5b0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int n);
extern unsigned char *func_0206e7bc(void *p, int n);
extern int func_0209cc30(void *p, unsigned int a, unsigned int b);
extern int func_0209d01c(int v, int n);
extern int data_021dc580;

void func_0209c5b0(void *self, int n)
{
    unsigned char *p;
    unsigned int y, x;
    unsigned int one = 1;
    int v;

    if (n < 0) {
        v = func_020644cc(524);
    } else {
        v = (unsigned int) n % 524;
    }
    data_021dc580 = v;
    p = func_0206e7bc((char *) self + 0x120, v);
    if (p != 0) {
        y = 1;
        do {
            x = one;
            do {
                func_0209d01c(func_0209cc30(self, x, y), *p++);
                x++;
            } while (x < 5);
            y++;
        } while (y < 5);
    }
}
