/* func_ov068_0226c63c @ 0x0226c63c, 0x70 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201aff8(void *, void *, int);
extern int func_0201c194(void *, int *);
extern void func_02019c6c(void *, int, unsigned short);
extern void func_0201afd4(void *, int *);
extern int func_0201afc0(void *);
extern void func_0201af48(void *);
extern unsigned short data_020c80f8;

int func_ov068_0226c63c(void *unused, void *p)
{
    void *a = (char *) p + 0x564;
    int r;
    void *b = (char *) p + 0x350;
    int loc[3];
    r = 0;
    if (func_0201aff8(b, p, 1) == 0) {
        switch (func_0201c194(p, loc)) {
            case 1:
                func_02019c6c(a, 1, data_020c80f8);
                r = 1;
                break;
            case 2:
                func_0201afd4(b, loc);
                break;
        }
    } else {
        if (func_0201afc0(b) != 0) {
            func_0201af48(b);
        }
    }
    return r;
}
