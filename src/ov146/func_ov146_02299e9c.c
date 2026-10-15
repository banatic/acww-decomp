/* func_ov146_02299e9c @ 0x02299e9c, 0x4c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov146_0229a174(void);
extern int func_ov146_02299ee8(int a, int b);

int func_ov146_02299e9c(int a, int b)
{
    int v;
    int idx;

    if (b >= 0x20) {
        return 0;
    }

    v = func_ov146_0229a174();
    idx = 35 * b;
    if (func_ov146_02299ee8(a, v + 0x180 + idx)) {
        unsigned char c = *(unsigned char *) (v + idx + 0x1a2);
        if (c < 4) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
