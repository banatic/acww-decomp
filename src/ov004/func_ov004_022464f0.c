/* func_ov004_022464f0 @ 0x022464f0, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020b6744(unsigned int code);
extern int func_020af83c(void *a, void *b);
extern int func_020adf8c(void *a, void *b);
extern int func_020ae8cc(void *a, void *b);

extern unsigned char data_021f395c[];
extern unsigned char data_021f3b30[];
extern unsigned char data_021f3b44[];

int func_ov004_022464f0(unsigned short *p)
{
    int k, f;

    k = func_020b65c4();
    if (func_020b6744((unsigned int) k) != 0) {
        return func_020af83c((void *) data_021f395c, p) == -1 ? 0 : 1;
    }
    if (k == 0xa) {
        k = 1;
        f = 0;
        if (*p >= 0x3e04 && *p <= 0x3e23) {
            f = k;
        }
        if (f == 0) {
            if (func_020ae8cc((void *) data_021f3b44, p) == -1) {
                k = 0;
            }
        }
        return k;
    }
    return func_020adf8c((void *) data_021f3b30, p) == -1 ? 0 : 1;
}
