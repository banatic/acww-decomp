/* villager_residents: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207c330 @ 0x0207c330, 0x80 bytes, Thumb
 * func_0207c190 @ 0x0207c190, 0x1a0 bytes, Thumb
 * func_0207c160 @ 0x0207c160, 0x30 bytes, Thumb
 * func_0207c0f0 @ 0x0207c0f0, 0x6e bytes, Thumb
 * func_0207c0c0 @ 0x0207c0c0, 0x30 bytes, Thumb
 */

extern void func_02080078(int);
extern void func_020800ec(int);
extern int func_020800fc(int);
extern void func_020642d0(int, int);
extern int func_0208150c(int);
extern int func_02003648(int);
extern void func_0207a1c8(char *, int);
extern void func_02079c30(char *, int);
extern void func_0208164c(int, int);
extern void func_02081660(int);
extern void MI_CpuCopy8(int, char *, int);
extern unsigned char data_021dc7aa[];
extern char data_021ee418[];
extern char data_021d1554[];
extern int func_020900d8(int address);
extern int func_02079900(int address);
extern int func_0207cec0(int a, int b);
extern int func_02003704(void *);
extern int func_02064294(const unsigned short *);
extern int func_02080330(int a, int b, int c);
extern int func_0207c4a4(int a, int b);
extern int func_0207cd40(int a);
extern int func_0207cf74(unsigned int);
extern void func_0207c3b0(int a, int b, int c, int d, int e, int f);
extern void func_02080d70(int a);
extern int memcmp(const char *a, const char *b, int c);
extern int func_0207f120(void *);
extern unsigned int func_0207f1c8(unsigned int object);
extern int func_0209b5ec(void *);
extern int func_0209bfec(int);
extern int func_0209e3ac(int, int, int);
extern int func_0209e380(int, int);
extern int func_0207f0c0(void *);

int func_0207c0f0(int a, int b);

void func_0207c330(char *a, int b, int c, int d, int e)
{
    func_02080078(c);
    func_020800ec(c);
    func_020642d0(func_020800fc(c), (unsigned int) data_021dc7aa);
    a[0x4074] = (char) func_02003648(func_0208150c(c));
    func_0207a1c8(&a[0x3f7c], d);
    func_02079c30(&a[0x3f60], d);
    if (b) {
        func_0208164c(b, c);
    }
    func_02081660(c);
    MI_CpuCopy8(e, &a[0x4058], 8);
}

void func_0207c190(int self, int param2)
{
    char *ptr;
    int r4;
    int r7;
    int T;
    char *p;
    ptr = (char *) ((char *) data_021dc7aa);
    r7 = func_02079900(func_020900d8((int) data_021ee418));
    T = func_0207c0f0(self, param2);
    r4 = func_0207cec0(self, T);
    if (func_02003704((void *) (unsigned int) func_0208150c(r7)) == 0) {
        goto cleanup;
    }
    if (func_02064294((const unsigned short *) (char *) func_020800fc(r7)) == 0) {
        goto cleanup;
    }
    p = (char *) func_020800fc(r7);
    if ((*((unsigned short *) p)) == (*((unsigned short *) ((char *) data_021dc7aa)))) {
        if (memcmp(p + 2, ptr + 2, 12) == 0) {
            if (r4 != 0) {
                func_02080d70(r4);
                if (func_02080330(r7, r4, param2) == 0) {
                    func_0207c330((char *) self, r7, r4, T, param2);
                } else {
                    func_0207c330((char *) self, 0, r4, T, param2);
                }
            }
            goto end;
        }
    }
    if (func_0207c4a4(self, func_02003648((int) ((unsigned char *) (unsigned int) func_0208150c(r7)))) != 0) {
        goto L2;
    }
    if ((*((signed char *) (((char *) self) + 0x4074))) == func_02003648((int) ((unsigned char *) (unsigned int) func_0208150c(r7)))) {
        goto L2;
    }
    if (r4 != 0) {
        goto L290;
    }
    r4 = func_0207cd40(self);
    if (func_0207cf74(r4) == 0) {
        goto end;
    }
    func_0207c3b0(self, func_0207cec0(self, r4), r4, r7, 2, param2);
    func_02081660(r7);
    goto end;
L290:
    func_02081660((int) data_021d1554);

    func_0208164c((int) data_021d1554, r7);
    func_02080d70(r4);
    func_0207c330((char *) self, r7, r4, T, param2);
    func_0207c3b0(self, r4, T, (int) data_021d1554, 2, param2);
    goto end;
L2:
    if (r4 != 0) {
        func_02080d70(r4);
        if (func_02080330(r7, r4, param2) == 0) {
            func_0207c330((char *) self, r7, r4, T, param2);
        } else {
            func_0207c330((char *) self, 0, r4, T, param2);
        }
    }

    goto end;
cleanup:
    if (r4 != 0) {
        func_02080d70(r4);
        func_0207c330((char *) self, r7, r4, T, param2);
    }

end:
    return;
}

int func_0207c160(void *arg)
{
    int i;
    void *p = arg;
    for (i = 0; i < 8; i++) {
        if (func_0207f120(p)) {
            return i;
        }
        p = (char *) p + 0x7EC;
    }
    return -1;
}

int func_0207c0f0(int a, int b)
{
    int forwarded_value;

    int res1, t, s, r2;

    res1 = func_0207c160((void *) a);
    if ((forwarded_value = (int) func_0207cec0(a, res1)) == 0) {
        goto ret_minus1;
    }
    s = func_0209b5ec((void *) func_0207f1c8((unsigned int) forwarded_value));
    t = func_0209e3ac(b, func_0209bfec(s), 0x3f);
    r2 = 0;
    if (t == 1) {
        r2 = func_0209e380(func_0209bfec(s), b);
    } else if (t == -1) {
        r2 = func_0209e380(b, func_0209bfec(s));
    }
    if (r2 < 2) {
        goto ret_minus1;
    }
    return res1;

ret_minus1:
    return -1;
}

int func_0207c0c0(void *param)
{
    int i;
    void *p = param;
    int result = 0;

    for (i = 0; i < 8; i++) {
        if (func_0207f0c0(p)) {
            return i;
        }
        p = (char *) p + 0x7ec;
    }
    return -1;
}
