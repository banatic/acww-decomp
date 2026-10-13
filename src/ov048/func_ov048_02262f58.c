/* func_ov048_02262f58 @ 0x02262f58, 0x12c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0200338c(int, int);
extern int func_02016884(void *, int, void *);
extern int func_02019de8(void *);
extern void func_02019c20(void *, int, int, int, int, int);
extern void func_0201addc(void *);
extern int func_02041d14(int, int);
extern void func_0200468c(void);
extern int func_020e8858(void *);
extern int func_020e8840(void *);
extern unsigned short data_020c80f8;

int func_ov048_02262f58(void *arg)
{
    char *base;
    char *p334;
    char *p564;
    char *p2a0;
    char *p3b0;
    int result;

    base = (char *) func_0200338c(0x73, 0);
    p334 = base + 0x334;
    p564 = base + 0x564;
    p2a0 = base + 0x2a0;
    p3b0 = base + 0x3b0;

    if (func_020e8858((char *) arg + 0xe70) == 0 && func_02016884(p334, 0x81, p2a0) == 0 &&
        func_02016884(p334, 0x82, p2a0) == 0) {
        func_02019c20(p564, 1, 0x81, 1, data_020c80f8, 0);
    }

    if (func_02016884((char *) arg + 0x334, 0x81, (char *) arg + 0x2a0) != 0 && func_02019de8((char *) arg + 0x564) != 0) {
        func_02019c20((char *) arg + 0x564, 1, 0x82, 0, data_020c80f8, 0);
    }

    if (func_02016884(p334, 0x81, p2a0) != 0 && func_02019de8(p564) != 0) {
        func_02019c20(p564, 1, 0x82, 0, data_020c80f8, 0);
    }

    if (*(unsigned short *) ((char *) arg + 0xe6e) == 2) {
        func_0201addc((char *) arg + 0x3b0);
        func_0201addc(p3b0);
    }

    if (func_020e8840((char *) arg + 0xe6e) != 0) {
        goto ret0;
    }
    if (*(unsigned int *) ((char *) arg + 0x654) == 8) {
        if (func_02041d14(2, 0xf) != 0) {
            func_0200468c();
            result = 1;
        } else {
            goto ret0;
        }
    } else {
        result = 1;
    }
    goto done;
ret0:
    result = 0;
done:
    return result;
}
