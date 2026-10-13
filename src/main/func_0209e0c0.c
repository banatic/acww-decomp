/* func_0209e0c0 @ 0x0209e0c0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0209e0c0 {
    unsigned char pad_00;
    unsigned char b;
};

extern void func_0209e100(struct UnkStruct_0209e0c0 *, int);

void func_0209e0c0(struct UnkStruct_0209e0c0 *p, int v)
{
    int d = p->b - v;
    if (d < 0) {
        int c;
        int r;
        if (d < 0) {
            d = -d;
        }
        c = d / 60 + 1;
        r = d % 60;
        d = 60 - r;
        if (d == 60) {
            d = 0;
            c--;
        }
        func_0209e100(p, c);
    }
    p->b = d;
}
