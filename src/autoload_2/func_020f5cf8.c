/* func_020f5cf8 @ 0x020f5cf8, 0x11c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fd23c;
extern int data_021fd244;
extern int data_021fd240;

void func_020f5cf8(int x, int *out1, int *out2)
{
    int a, b;

    if (x <= 0) {
        a = 0;
    } else if (x <= 0x99a) {
        a = (int) (((long long) data_021fd23c * x + 0x800) >> 12);
        a = a >> 12;
    } else if (x > 0x1000) {
        a = 0;
    } else {
        int t = (int) (((long long) data_021fd244 * (x - 0x99a) + 0x800) >> 12);
        a = (0x7f000 - t) >> 12;
    }

    if (x <= 0x99a) {
        b = 0;
    } else if (x >= 0xccd) {
        b = 0x7f;
    } else {
        b = (int) (((long long) data_021fd240 * (x - 0x99a) + 0x800) >> 12);
        b = b >> 12;
    }

    if (a > 0x7f) {
        a = 0x7f;
    } else if (a < 0) {
        a = 0;
    }
    *out1 = a;

    if (b > 0x7f) {
        b = 0x7f;
    } else if (b < 0) {
        b = 0;
    }
    *out2 = b;
}
