/* func_0207aa8c @ 0x0207aa8c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02080928(void *p);
extern int func_02079924(void *p, int n, int i);
extern int func_0207cc54(unsigned char mask, int count, int size);
int func_0207aa8c(char *base, int n)
{
    char *p = base;
    int i;
    int best = 0xfffe7960;
    unsigned char mask = 0;
    int count = 0;
    for (i = 0; i < 8; p += 0x7ec, i++) {
        if (i == n) {
            continue;
        }
        if (!func_02080928(p)) {
            continue;
        }
        {
            int val = func_02079924(base + 0x3f60, n, i);
            if (val > best) {
                best = val;
                mask = (unsigned char) (1 << i);
                count = 1;
            } else if (val == best) {
                mask = (unsigned char) (mask | (1 << i));
                count++;
            }
        }
    }

    return func_0207cc54(mask, count, 8);
}
