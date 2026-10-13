/* func_ov119_0229a5d8 @ 0x0229a5d8, 0x78 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern void *func_02099664(void *);
extern int func_02077bd8(void *);
extern int func_02077bd0(void *);
extern unsigned long long func_02077be0(void *);

void func_ov119_0229a5d8(unsigned char *dst)
{
    void *h;
    int i;
    unsigned long long v;

    h = func_020984e8();
    if ((func_02077bd8(func_02099664(h)) & func_02077bd0(func_02099664(h))) == 0) {
        for (i = 0; i < 0xc; i++) {
            (dst + i)[0xa1] = 0xa;
        }
    } else {
        v = func_02077be0(func_02099664(h));
        for (i = 0xb; i >= 0; i--) {
            (dst + i)[0xa1] = (unsigned char) (v % 10);
            v /= 10;
        }
    }
}
