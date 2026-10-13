/* func_0207af30 @ 0x0207af30, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Buf {
    int a;
    int b;
} Buf;

extern void *data_020cd524[11];
extern void func_0209e474(Buf *);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern int func_0203fc78(void *e, Buf *b, int k);
extern void *func_02041608(void);

int func_0207af30(void)
{
    void **p;
    int i;
    int zero;
    unsigned int ok;
    void *e;
    unsigned int t;
    Buf b1;
    Buf b2;
    p = data_020cd524;
    b1.a = 0;
    b1.b = 0;
    func_0209e474(&b1);
    i = 0;
    zero = 0;
    ok = 0;
    for (; i < 11; p++, i++) {
        e = *p;
        MI_CpuCopy8(&b1, &b2, 8);
        if (func_0203fc78(e, &b2, zero) != 0) {
            t = 1;
        } else {
            t = ok;
        }
        if (t > 0) {
            if (e == func_02041608()) {
                return i;
            }
        }
    }
    return 11;
}
