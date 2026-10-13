/* func_020bf2b8 @ 0x020bf2b8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);
extern int FX_Div(int, int);

void func_020bf2b8(int *out, int a, int b, int size)
{
    int x = FX_MulFunc(0x400, size);
    int y = FX_MulFunc(0x1000, size);
    int z = FX_Div(0x1000 - x, y - x);
    if (z < 0) {
        z = 0;
    } else if (z > 0x1000) {
        z = 0x1000;
    }
    out[0] = a;
    out[1] = b;
    out[2] = z;
}
