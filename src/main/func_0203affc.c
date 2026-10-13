/* func_0203affc @ 0x0203affc, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eaca0(int *out, int *a, int *b);
extern void func_01ffd070(int *out, int *a, int *b);
extern void func_020eaad0(int *out, int *in, int scale);

int func_0203affc(int *a, int *b, int *c, int *out, int *extra)
{
    int min[3];
    int max[3];
    int out1[3];
    int tmp[3];
    int result[3];
    int max2;
    int m;

    min[0] = a[0];
    min[1] = a[1];
    min[2] = a[2];
    max[0] = a[0];
    max[1] = a[1];
    max[2] = a[2];

    if (min[0] > b[0]) {
        min[0] = b[0];
    } else {
        max[0] = b[0];
    }
    if (min[2] > b[2]) {
        min[2] = b[2];
    } else {
        max[2] = b[2];
    }

    if (min[0] > c[0]) {
        min[0] = c[0];
    }
    if (min[2] > c[2]) {
        min[2] = c[2];
    }
    if (max[0] < c[0]) {
        max[0] = c[0];
    }
    if (max[2] < c[2]) {
        max[2] = c[2];
    }

    func_020eaca0(out1, max, min);

    max2 = out1[2];
    m = out1[0];
    if (m <= max2) {
        m = max2;
    }

    if (out != 0) {
        func_01ffd070(tmp, min, max);
        func_020eaad0(result, tmp, 1);
        out[0] = result[0];
        out[1] = result[1];
        out[2] = result[2];
        out[1] = (a[1] + b[1]) >> 1;
        if (extra != 0) {
            *extra = out1[2] >> 1;
        }
    }

    return m;
}
