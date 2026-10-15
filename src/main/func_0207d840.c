/* func_0207d840 @ 0x0207d840, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_0207f1c8(int);
extern int func_0209b5ec(void *);
extern int func_0209c330(int);
extern int func_02003704(int);
extern int func_0209c370(int);
extern int func_0209c2c0(int);
extern int func_0207db48(int, int);
extern int func_0209c108(int);
extern void func_0207d9d4(int, int);
extern int func_0209c168(int);
extern int func_0209c38c(int);
extern int func_0209b5e8(int);
extern void func_0209baf4(int);
extern int func_0207f270(int);
extern int func_020794d0(int);
extern void func_0209bd5c(int);
extern int func_0209c310(int);
extern void func_0209bd30(int, int, short *, int);
extern void func_0207f414(int, int, int);

int func_0207d840(int param0, int param1)
{
    int var_b;
    int var_a;
    int r4, r6, r7;
    unsigned short sh;

    var_a = func_0208150c(param0);
    r6 = (func_0209b5ec((void *) func_0207f1c8(param0)));
    r4 = 12;
    r7 = func_0209c330(r6);

    if (func_02003704(var_a) == 0) {
        goto exit;
    }
    if (func_0209c370(r6) == 0) {
        goto exit;
    }

    var_b = func_0209c2c0(r6);

    if (func_0209c330(r6) == 8) {
        if (func_0207db48(param0, param1)) {
            r4 = func_0209c108(r6);
        }
    } else {
        func_0207d9d4(param0, param1);
        r4 = func_0209c168(r6);
    }

    if (r4 == 12) {
        goto exit;
    }
    if (func_0209c38c(r7) && r7 == r4) {
        goto exit;
    }

    func_0209baf4(func_0209b5e8(func_0207f1c8(param0)));
    r6 = func_020794d0(func_0207f270(param0));
    func_0209bd5c(r6);

    if (func_0209c310(r4) == 0) {
        sh = 0xfff1;
        func_0209bd30(r6, r4, (short *) &sh, 0);
    }

    if (func_0209c38c(r4) != 0) {
        func_0207f414(param0, r4, var_b);
    }
exit:
    return r4;
}
