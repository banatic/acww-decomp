/* func_0207c190 @ 0x0207c190, 0x1a0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021ee418[];
extern char data_021dc7aa[];
extern char data_021d1554[];
extern int func_020900d8(int address);
extern int func_02079900(int address);
extern int func_0207c0f0(int a, int b);
extern int func_0207cec0(int a, int b);
extern unsigned int func_0208150c(int a);
extern int func_02003704(void *);
extern char *func_020800fc(int a);
extern int func_02064294(const unsigned short *);
extern int func_02080330(int a, int b, int c);
extern void func_0207c330(int a, int b, int c, int d, int e);
extern int func_02003648(unsigned char *);
extern int func_0207c4a4(int a, int b);
extern int func_0207cd40(int a);
extern int func_0207cf74(unsigned int);
extern void func_0207c3b0(int a, int b, int c, int d, int e, int f);
extern void func_02081660(int a);
extern void func_0208164c(int a, int b);
extern void func_02080d70(int a);
extern int memcmp(const char *a, const char *b, int c);
void func_0207c190(int self, int param2)
{
    char *ptr;
    int r4;
    int r7;
    int T;
    char *p;
    ptr = (char *) data_021dc7aa;
    r7 = func_02079900(func_020900d8((int) data_021ee418));
    T = func_0207c0f0(self, param2);
    r4 = func_0207cec0(self, T);
    if (func_02003704((void *) func_0208150c(r7)) == 0) {
        goto cleanup;
    }
    if (func_02064294((const unsigned short *) func_020800fc(r7)) == 0) {
        goto cleanup;
    }
    p = func_020800fc(r7);
    if ((*((unsigned short *) p)) == (*((unsigned short *) data_021dc7aa))) {
        if (memcmp(p + 2, ptr + 2, 12) == 0) {
            if (r4 != 0) {
                func_02080d70(r4);
                if (func_02080330(r7, r4, param2) == 0) {
                    func_0207c330(self, r7, r4, T, param2);
                } else {
                    func_0207c330(self, 0, r4, T, param2);
                }
            }
            goto end;
        }
    }
    if (func_0207c4a4(self, func_02003648((unsigned char *) func_0208150c(r7))) != 0) {
        goto L2;
    }
    if ((*((signed char *) (((char *) self) + 0x4074))) == func_02003648((unsigned char *) func_0208150c(r7))) {
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
    func_0207c330(self, r7, r4, T, param2);
    func_0207c3b0(self, r4, T, (int) data_021d1554, 2, param2);
    goto end;
L2:
    if (r4 != 0) {
        func_02080d70(r4);
        if (func_02080330(r7, r4, param2) == 0) {
            func_0207c330(self, r7, r4, T, param2);
        } else {
            func_0207c330(self, 0, r4, T, param2);
        }
    }

    goto end;
cleanup:
    if (r4 != 0) {
        func_02080d70(r4);
        func_0207c330(self, r7, r4, T, param2);
    }

end:
    return;
}
