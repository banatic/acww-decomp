/* func_0207aeac @ 0x0207aeac, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(unsigned char *s);
extern void func_0209e29c(unsigned char *s, int v);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern int func_0203fea0(unsigned char *p, unsigned char *buf);
extern unsigned int data_020cd524[];

int func_0207aeac(unsigned int count, void *src)
{
    int out;
    int i;
    int j;
    int n;
    int k;
    unsigned char s[0x68];
    unsigned int *tbl;
    unsigned char *p;

    *(unsigned int *) &s[0] = 0;
    *(unsigned int *) &s[4] = 0;
    if (src == 0) {
        func_0209e474(s);
    } else {
        MI_CpuCopy8(src, s, 8);
    }

    out = 0;
    j = 0;
    while (out <= count) {
        p = &s[0x10];
        MI_CpuCopy8(s, &s[8], 8);
        n = func_0203fea0(p, &s[8]);
        i = 0;
        while (i < n) {
            tbl = data_020cd524;
            k = j;
            while (k < 0xb) {
                if (*(unsigned short *) p == *tbl) {
                    return k;
                }
                tbl++;
                k++;
            }
            p += 0xc;
            i++;
        }
        func_0209e29c(s, 1);
        out++;
    }
    return 0xb;
}
