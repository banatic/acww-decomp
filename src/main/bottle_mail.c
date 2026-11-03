/* bottle_mail: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02096d10 @ 0x02096d10, 0x68 bytes, Thumb
 * func_02096c88 @ 0x02096c88, 0x88 bytes, Thumb
 */

extern int func_02096d78(void);
extern void *func_02097f14(void *buffer);
extern int func_02065ec0(int);
extern int func_02096de0(void);
extern int func_020644cc(int);
extern int func_02097e38(void *);
extern int func_02096df4(const char *);
extern void func_02097edc(void *, int);
extern unsigned char data_021f36ec;
extern unsigned char data_021f43ec;
extern int func_02090158(int *);
extern int func_020900f0(int *);
extern int func_02090130(int *);
extern int func_020900f4(int *);
extern void func_02090100(int *);
extern void func_020664e0(int);
extern int func_02066830(int, int);
extern void func_02066650(int);
extern int data_021ee418;
extern unsigned char data_020d18c8[];

void func_02096d10(int param0)
{
    if (param0 <= 0) {
        return;
    }
    if (func_02096d78() != 0) {
        return;
    }
    {
        int n;
        void *p = &data_021f36ec;
        char tmp;
        if (func_02065ec0((int) func_02097f14(p)) != 0) {
            func_02096de0();
            return;
        }
        if (func_020644cc(0xa) != 7) {
            return;
        }
        tmp = (char) data_021f43ec;
        n = func_02097e38(p);
        tmp = (char) n;
        if (func_02096df4(&tmp)) {
            func_02097edc(p, n);
        }
    }
}

void func_02096c88(void)
{
    int *base = &data_021ee418;
    int r4_val, v, w, tmp;

    if (func_02090158(base) == 0) {
        return;
    }
    r4_val = func_020900f0(base);
    if (func_02065ec0(r4_val) == 0) {
        return;
    }
    v = func_02090130(base);

    switch (v) {
        case 0:
            w = func_020900f4(base);
            if (w == 0) {
                return;
            }
            if (w >= 5) {
                break;
            }
            if (func_020644cc(data_020d18c8[w]) != 1) {
                return;
            }
            // fall through
        case 1:
        default:
            break;
    }

    func_02090100(base);
    func_020664e0(r4_val);
    tmp = (int) func_02097f14(((int *) &data_021f36ec));
    func_02066830(tmp, r4_val);
    func_02066650(r4_val);
    if (func_02096d78() != 0) {
        return;
    }
    func_02096de0();
}
