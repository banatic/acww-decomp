/* func_ov095_0229b704 @ 0x0229b704, 0x80 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229b454(void *ctx, unsigned short *src, unsigned short *dst);
extern int func_ov095_0229b8d8(void *self, int x);
extern int func_ov095_0229b810(void *ctx, int c);
extern unsigned short data_ov095_0229d0f8[];

int func_ov095_0229b704(void *self, void *ptr)
{
    unsigned short buf[6];
    int v;
    int k;

    v = 0;
    do {
        buf[v] = 0;
        v++;
    } while (v < 4);

    if (func_ov095_0229b454(self, ptr, buf) == 0) {
        return 0;
    }

    v = func_ov095_0229b8d8(self, buf[0]);
    v = (unsigned short) (v + func_ov095_0229b8d8(self, buf[1]));
    if (buf[2] != 0) {
        v = (unsigned short) (v + func_ov095_0229b810(self, buf[2]));
    }

    for (k = 0; k < 0x933; k++) {
        if (v == data_ov095_0229d0f8[k]) {
            return v;
        }
    }
    return 0;
}
