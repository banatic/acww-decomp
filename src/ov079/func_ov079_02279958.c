/* func_ov079_02279958 @ 0x02279958, 0x100 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0201ae40(void *p);
extern int func_0201aff8(void *p, void *self, int flag);
extern int func_0201afc0(void *p);
extern void func_0201af48(void *p);
extern void func_0201afd4(void *p, void *buf);
extern int func_02019d0c(void *p, int r1, int r2, int r3, int s1, int s2, int s3, int s4, int s5, int s6, int s7);
extern unsigned short data_020c80f8;

extern char data_ov079_0227a200;
extern char data_ov079_0227a1f4;
extern int func_ov079_02279a58(void *self, void *buf, void *tbl);

int func_ov079_02279958(void *self)
{
    void *a = (char *) self + 0x564;
    void *b = (char *) self + 0x350;
    void *c = (char *) self + 0x3a8;
    int kind;
    int result;
    char buf[0xc];

    kind = (int) func_0201ae40(c);
    result = 0;
    if (func_0201aff8(b, self, 1) == 0) {
        if (kind == 1) {
            goto case1;
        }
        if (kind == 2) {
            goto case2;
        }
        if (kind != 3) {
            goto done;
        }
        func_02019d0c(a, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        result = 1;
        goto done;
    case1:
        if (func_ov079_02279a58(self, buf, &data_ov079_0227a200)) {
            func_0201afd4(b, buf);
        } else {
            func_02019d0c(a, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
        result = 1;
        goto done;
    case2:
        if (func_ov079_02279a58(self, buf, &data_ov079_0227a1f4)) {
            func_0201afd4(b, buf);
        } else {
            func_02019d0c(a, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
        result = 1;
        goto done;
    } else {
        if (func_0201afc0(b)) {
            func_0201af48(b);
        }
    }
done:
    return result;
}
