/* design_assets_2: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020723a0 @ 0x020723a0, 0x8 bytes, Thumb
 * func_02072380 @ 0x02072380, 0x20 bytes, Thumb
 * func_02072370 @ 0x02072370, 0x10 bytes, Thumb
 * func_02072360 @ 0x02072360, 0x10 bytes, Thumb
 * func_02072350 @ 0x02072350, 0x10 bytes, Thumb
 * func_02072338 @ 0x02072338, 0x18 bytes, Thumb
 * func_02072330 @ 0x02072330, 0x8 bytes, Thumb
 * func_02072268 @ 0x02072268, 0xc6 bytes, Thumb
 * func_02072260 @ 0x02072260, 0x8 bytes, Thumb
 * func_0207225c @ 0x0207225c, 0x2 bytes, Thumb
 * func_02072244 @ 0x02072244, 0x18 bytes, Thumb
 * func_02072220 @ 0x02072220, 0x22 bytes, Thumb
 * func_0207221c @ 0x0207221c, 0x2 bytes, Thumb
 * func_02072204 @ 0x02072204, 0x18 bytes, Thumb
 * func_020721e0 @ 0x020721e0, 0x22 bytes, Thumb
 * func_020721dc @ 0x020721dc, 0x2 bytes, Thumb
 * func_020721c4 @ 0x020721c4, 0x18 bytes, Thumb
 * func_020721b0 @ 0x020721b0, 0x14 bytes, Thumb
 * func_020721ac @ 0x020721ac, 0x2 bytes, Thumb
 * func_02072180 @ 0x02072180, 0x2c bytes, Thumb
 * func_0207216c @ 0x0207216c, 0x14 bytes, Thumb
 */

extern void func_0207252c(void *receiver);
extern char data_021d054c[];
extern int data_021d04e4[];
extern void func_0206e8c4(int param);
extern int func_0206e8b4(int arg);
extern int func_0206e890(int a, void *p, int b, int c);
extern char data_020e1828[];
extern void func_0206e808(void *);
extern int func_0206e7bc(int a0, int a2);
extern void *func_02062fbc(void *);
extern int func_020a8be4(void *, void *);
extern void func_02072e64(void *, void *);
extern void func_02072f54(void *, int);
extern void func_02072e18(void *, int);
extern void *func_020641c8(void *);
extern void *func_02094fd4(void *);
extern void func_020642fc(void *);
extern void func_020641e0(void *, void *);
extern void *func_0209529c(void *);
extern void func_02095044(void *, void *);
extern void func_02095038(void *, void *);
extern void func_02072eec(void *, void *);
extern int func_0209526c(void *);
extern void func_020642f8(void *);
extern void *func_02094fbc(void *);
extern void *func_020641b0(void *);
extern void *func_02062f4c(void *);
extern int data_021d04c8;
extern int func_02064af4(void *, const void *, unsigned int);
extern unsigned char data_020e180c[];
extern void func_02002628(int, int, int, int, int);
extern unsigned char data_020e17f0[];
extern unsigned char data_020e17d8[];
extern void func_020024f0(int a, int b, int c, int d);
extern int func_02064328(void *dest, const void *src, int n);
extern const char data_020e17c0[];

void func_020723a0(void *receiver)
{
    func_0207252c(receiver);
}

int func_02072380(int unused, int row, int col)
{
    int row_off = (row & 3) * 32;
    int col_off = (col & 7) * 4;
    return *(int *) (data_021d054c + row_off + col_off);
}

int func_02072370(int unused, unsigned int index)
{
    return data_021d04e4[index & 7];
}

int func_02072360(int arg)
{
    func_0206e8c4(arg);
    return arg;
}

int func_02072350(int arg)
{
    func_0206e8b4(arg);
    return arg;
}

void func_02072338(int a)
{
    func_0206e890(a, data_020e1828, 0x34, 0x32);
}

void func_02072330(void *argument0)
{
    func_0206e808((void *) argument0);
}

int func_02072268(int a0, void *a1, int a2)
{
    unsigned char buf0[0x28];
    unsigned char buf1[0x20];
    unsigned char buf2[0x20];
    unsigned char buf3[0x2c];
    unsigned char *p4;
    unsigned char b1, b2;

    if (a2 < 0x32) {
        p4 = (unsigned char *) func_0206e7bc(a0, a2);
        if (p4 != 0) {
            func_02062fbc(buf0);
            func_020a8be4(buf0, p4);
            func_02072e64(a1, buf0);
            b1 = *(p4 + 0x32);
            func_02072f54(a1, b1);
            b2 = *(p4 + 0x33);
            func_02072e18(a1, b2);
            func_020641c8(buf1);
            func_020a8be4(buf1, p4 + 0x24);
            func_02094fd4(buf2);
            func_020a8be4(buf2, p4 + 0x16);
            func_020642fc(buf3);
            func_020641e0(buf3, buf1);
            func_0209529c(buf3 + 0xe);
            func_02095044(buf3 + 0xe, buf2);
            func_02095038(buf3 + 0xe, buf3);
            func_02072eec(a1, buf3 + 0xe);
            func_0209526c(buf3 + 0xe);
            func_020642f8(buf3);
            func_02094fbc(buf2);
            func_020641b0(buf1);
            func_02062f4c(buf0);
            return 1;
        }
    }
    return 0;
}

int func_02072260(void)
{
    return (int) &data_021d04c8;
}

void func_0207225c(void) {}

void func_02072244(const void *src)
{
    func_02064af4(data_020e180c, src, 0x1000);
}

int func_02072220(int a, int b, int c)
{
    if (c < 0 || c >= 8) {
        return 0;
    }
    func_02002628(a, b, c * 4, 4, 4);
    return 1;
}

void func_0207221c(void) {}

void func_02072204(unsigned char *src)
{
    func_02064af4(data_020e17f0, src, 0x1000);
}

int func_020721e0(int a, int b, int c)
{
    if (c < 0 || c >= 8) {
        return 0;
    }
    func_02002628(a, b, c << 2, 4, 4);
    return 1;
}

void func_020721dc(void) {}

void func_020721c4(const void *src)
{
    func_02064af4(data_020e17d8, src, 0x200);
}

int func_020721b0(int a, int b)
{
    func_020024f0(a, b, 4, 4);
    return 1;
}

void func_020721ac(void) {}

int func_02072180(const void *arg0, int arg1)
{
    char buf[0x28];

    func_02064328(buf, data_020e17c0, arg1 + 2);
    return func_02064af4(buf, arg0, 0x200);
}

int func_0207216c(int a, int b)
{
    func_020024f0(a, b, 4, 4);
    return 1;
}
