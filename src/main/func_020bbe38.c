/* func_020bbe38 @ 0x020bbe38, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    char pad0[0x24];
    unsigned int f24;
    char pad1[0x0c];
    unsigned int f34;
} data_021f8ab0;

void func_020bbe38(unsigned int *out)
{
    unsigned int x;
    unsigned int y;
    int a;
    int b;
    int c;

    x = data_021f8ab0.f24;
    a = (x == 3);
    b = (x == 4);
    y = data_021f8ab0.f34;
    c = (y == 1);

    out[3] = 0;

    if (c) {
        if (a) {
            out[3] = 0x00099a00;
        } else if (b) {
            out[3] = 0x00100000;
        }
    }
}
