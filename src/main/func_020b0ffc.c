/* func_020b0ffc @ 0x020b0ffc, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_020b1768(int a);
extern int func_020b1050(int a, int b);

void func_020b0ffc(unsigned short *out, int a, int flags)
{
    unsigned char *p = func_020b1768(a);
    int i;
    int idx;
    int high;
    int first;
    int second;
    int slot;

    idx = 0;
    i = idx;
    flags &= 0xf;
    high = flags << 12;
    for (; i < 4; i++) {
        first = p[idx];
        if (first == 0xff) {
            break;
        }
        second = p[idx + 1];
        idx += 2;
        slot = func_020b1050(first, second);
        out[slot] = (out[slot] & 0xfff) | high;
    }
}
