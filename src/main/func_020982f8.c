/* func_020982f8 @ 0x020982f8, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_020992fc(int);
extern int func_0206f798(void);
extern int func_020983f0(int);
extern void func_020983ec(int, int);
extern void func_02066694(char *);
extern void *func_020b5630(char *);
extern int func_020b45d0(char *, int, int, int, int, int);
extern int func_0203d7c4(int, char *);
extern int func_02099870(int);
extern void func_02066024(char *, char *, const char *, const char *, const char *, int);
extern int func_02097a54(char *);
extern void *func_020b5618(char *);
extern void func_02066688(char *);
extern char data_020e310c;
extern char data_020e3118;
extern char data_020e3110;
void func_020982f8(int p)
{
    int h;
    int k;
    int v;
    int sum;
    char empty[4];
    int base;
    char temp[64];
    char big[256];
    h = func_020984e8();
    k = func_020992fc(h);
    if (func_0206f798() != 0) {
        return;
    }
    if (p <= 0) {
        return;
    }
    base = func_020983f0(k);
    v = base / 2000;
    v = p * v;
    v = v * 10;
    if (v > 99999) {
        v = 99999;
    }
    if (v == 0) {
        return;
    }
    if ((base ^ 0) == 999999999) {
        return;
    }
    sum = base + v;
    if (sum > 999999999) {
        sum = 999999999;
    }
    func_020983ec(k, sum);
    func_02066694(big);
    empty[0] = 0;
    func_020b5630(temp);
    func_020b45d0(temp, v, 10, 0, 0, 0);
    func_0203d7c4(1, temp);
    func_02066024(big, empty, &data_020e3118, &data_020e3110, &data_020e310c, func_02099870(h));
    func_02097a54(big);
    func_020b5618(temp);
    func_02066688(big);
}
