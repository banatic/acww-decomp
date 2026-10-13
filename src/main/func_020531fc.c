/* func_020531fc @ 0x020531fc, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char lo : 4;
    unsigned char hi : 4;
} Nib;

int func_020531fc(unsigned char *p, int a, int b)
{
    unsigned int i;
    Nib *n;
    unsigned char *used;
    unsigned char *nib;

    for (i = 0; i < 4; i++) {
        if (((*(p + (i >> 3) + 4) >> (i & 7)) & 1) != 0) {
            n = (Nib *) (p + i);
            if (a == n->lo) {
                if (b == n->hi) {
                    n->lo = 0;
                    n->hi = 0;
                    used = p + 4;
                    used[i >> 3] &= ~(1 << (i & 7));
                    nib = p + 5;
                    nib[i >> 1] &= ~(0xf << ((i & 1) << 2));
                    return 1;
                }
            }
        }
    }
    return 0;
}
