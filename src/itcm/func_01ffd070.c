/* func_01ffd070 @ 0x01ffd070, 0x44 bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

extern void func_01ffd070(int *out, const int *a, const int *b);

void func_01ffd070(int *out, const int *a, const int *b)
{
    int x0, x1, x2;
    int y0, y1, y2;

    x0 = a[0];
    y0 = b[0];
    x2 = a[2];
    y2 = b[2];
    x1 = a[1];
    y1 = b[1];

    out[0] = x0 + y0;
    out[1] = x1 + y1;
    out[2] = x2 + y2;
}
