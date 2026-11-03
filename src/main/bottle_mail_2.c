/* bottle_mail_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02096e38 @ 0x02096e38, 0x84 bytes, Thumb
 * func_02096df4 @ 0x02096df4, 0x44 bytes, Thumb
 * func_02096de0 @ 0x02096de0, 0x12 bytes, Thumb
 */

extern void *func_0209a1d0(void);
extern void *func_02097f14(void *);
extern unsigned char func_02065ec0(unsigned char *param);
extern void func_02066650(void *);
extern void *func_020984e8(void);
extern void *func_020996ac(void *);
extern int func_0203cd2c(void *, void *, int, int);
extern int func_02066830(void *, void *);
extern int func_02073d90(void *);
extern void func_0207055c(int, int);
extern void *data_020ccf94;
extern unsigned char data_021f36ec[];
extern void func_02065f88(int a, int b, void *c);
extern char data_020e3070;
extern int func_0204677c(void);
extern int func_02046ebc(int);

int func_02096de0(void);

int func_02096e38(void)
{
    void *a, *b, *c;
    unsigned short key;

    a = func_0209a1d0();
    if (a == 0) {
        return 0;
    }
    b = func_02097f14((void *) data_021f36ec);
    if (func_02065ec0(b) == 0) {
        func_02066650(b);
        return 1;
    }
    c = func_020984e8();
    key = 0x1033;
    func_0203cd2c(func_020996ac(c), &key, 0, 1);
    func_02066830(a, b);
    func_02066650(b);
    c = data_020ccf94;
    if (func_02073d90(c) != 0 && *(int *) ((char *) c + 0x64) != 0) {
        func_0207055c(7, 0);
    }
    return 1;
}

int func_02096df4(int param)
{
    int temp = (int) func_02097f14(((char *) data_021f36ec));
    if ((int) func_02065ec0((unsigned char *) temp) != 0) {
        return 0;
    }
    if (func_02096de0() == 0) {
        return 0;
    }
    func_02065f88(temp, param, &data_020e3070);
    return 1;
}

int func_02096de0(void)
{
    return func_02046ebc((int) func_0204677c());
}
