/* wfc_host_list_rows_4: 2 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_0229a42c @ 0x0229a42c, 0x38 bytes, Thumb
 * func_ov146_0229a400 @ 0x0229a400, 0x2c bytes, Thumb
 */

extern void func_02070b84(void *);

char *func_ov146_0229a42c(char *p)
{
    if (*(unsigned char *) (p + 0xb4) >= 0x14) {
        return p + 0x1e34;
    } else {
        (*(unsigned char *) (p + 0xb4))++;
        return p + 0x1630 + (*(unsigned char *) (p + 0xb4) - 1) * 108;
    }
}

void func_ov146_0229a400(void *arg0)
{
    int i;
    char *p;
    char *base;

    p = (char *) arg0 + 0xb4;
    *p = 0;
    base = (char *) arg0 + 0x1630;
    for (i = 0; i < 20; i++) {
        func_02070b84(base + i * 0x6c);
    }
}
