/* savings: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02098400 @ 0x02098400, 0x2 bytes, Thumb
 * func_020983fc @ 0x020983fc, 0x2 bytes, Thumb
 * func_020983f4 @ 0x020983f4, 0x8 bytes, Thumb
 * func_020983f0 @ 0x020983f0, 0x4 bytes, Thumb
 * func_020983ec @ 0x020983ec, 0x4 bytes, Thumb
 * func_020983e0 @ 0x020983e0, 0xc bytes, Thumb
 * func_020983c8 @ 0x020983c8, 0x18 bytes, Thumb
 * func_020983c4 @ 0x020983c4, 0x4 bytes, Thumb
 * func_020983c0 @ 0x020983c0, 0x4 bytes, Thumb
 * func_020982f8 @ 0x020982f8, 0xc8 bytes, Thumb
 */

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_020983f4;

struct UnkStruct_020983e0 {
    char pad_00[0x40];
    unsigned int unk_40;
};

struct Func020983C8Data {
    char pad_00[0x40];
    unsigned int value;
};

extern struct UnkStruct_020983e0 data_021ef8a8;
extern int func_020984e8(void);
extern int func_020992fc(int);
extern int func_0206f798(void);
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

void func_02098400(void *object) {}

void func_020983fc(void *object) {}

void func_020983f4(UnkStruct_020983f4 *p)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
}

int func_020983f0(int *p0)
{
    return p0[0];
}

void func_020983ec(int *p0, int p1)
{
    p0[0] = p1;
}

unsigned int func_020983e0(void)
{
    return data_021ef8a8.unk_40;
}

void func_020983c8(int arg)
{
    if (arg > 0x3b9ac9ff) {
        arg = 0x3b9ac9ff;
    }
    (*(struct Func020983C8Data *) &data_021ef8a8).value = arg;
}

int func_020983c4(unsigned char *p0)
{
    return p0[4];
}

void func_020983c0(unsigned char *p0, int p1)
{
    p0[4] = p1;
}

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
    base = func_020983f0((int *) k);
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
    func_020983ec((int *) k, sum);
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
