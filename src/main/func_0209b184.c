/* func_0209b184 @ 0x0209b184, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ad7a4(int a, int b);
extern int func_020af950(void *p);
extern int func_0209b218(int a, int b);
extern int func_020644cc(int x);
extern int data_021f395c;

int func_0209b184(int a, int b)
{
    int i;
    int r;

    if (func_020ad7a4(a, b) == 0) {
        b = (unsigned char) (b & ~3);
    } else {
        if (func_020af950(&data_021f395c) != 0) {
            b = (unsigned char) (b & ~1);
        }
    }

    r = func_0209b218(a, b);
    if (r > 0) {
        r = func_020644cc(r);
        for (i = 0; i < 5; i++) {
            if ((b >> i) & 1) {
                if (r == 0) {
                    return i;
                }
                r--;
            }
        }
    }
    return -1;
}
