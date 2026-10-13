/* func_ov129_0229be7c @ 0x0229be7c, 0x68 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_ov127_022996bc(const char *);
extern int func_ov127_022996d8(int);
extern int func_ov127_022996c8(int);
extern int func_ov127_022996e4(void *, int, int);

int func_ov129_0229be7c(unsigned char *p0, const char *p1, int p2)
{
    unsigned char *a;
    int arg1;
    int j;
    unsigned short buf[8];
    int i, k, len;

    a = func_ov127_022996bc(p1);
    i = 0;
    j = 0;
    while (i < 2) {
        unsigned char c;
        c = a[i];
        if (p2 != c) {
            arg1 = func_ov127_022996d8(c);
            len = func_ov127_022996e4(buf, arg1, func_ov127_022996c8(c));
            k = j;
            while (k < len) {
                unsigned char *q = p0 + buf[k];
                if (q[0x2f98] == 1) {
                    return 1;
                }
                k++;
            }
        }
        i++;
    }
    return 0;
}
