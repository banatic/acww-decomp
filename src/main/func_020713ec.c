/* func_020713ec @ 0x020713ec, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02071318(int, int, int *);

void func_020713ec(int param0, int param1)
{
    int local;
    unsigned char *p;
    p = func_02071318(param0, param1, &local);
    if (p) {
        int bitpos = (local & 1) << 2;
        int offset = local >> 1;
        p[offset] &= ~(0xF << bitpos);
        p[offset] |= (5 << bitpos);
    }
}
