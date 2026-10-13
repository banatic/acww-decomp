/* func_020a8764 @ 0x020a8764, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a87a8(int, int);
extern int func_020a87c8(int, int);

void func_020a8764(int *out, int value)
{
    int a, b, c;
    func_020a87a8(value, 0);
    a = func_020a87c8(value, 2);
    b = func_020a87c8(value, 3);
    c = func_020a87a8(value, 4);
    out[0] = b;
    out[1] = c;
    out[2] = a - 6;
    out[3] = value + 6;
    out[4] = value;
}
