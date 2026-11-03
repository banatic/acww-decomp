/* talk_choices: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201cfb4 @ 0x0201cfb4, 0x2e bytes, Thumb
 * func_0201cf90 @ 0x0201cf90, 0x24 bytes, Thumb
 * func_0201cf74 @ 0x0201cf74, 0x1a bytes, Thumb
 * func_0201cf54 @ 0x0201cf54, 0x20 bytes, Thumb
 * func_0201cec8 @ 0x0201cec8, 0x8c bytes, Thumb
 */

typedef struct {
    unsigned char b;
    int w;
} Params;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
} UnkStruct_0201cf74;

void *func_020160b4(void *p0);
void func_020ab670(void *p, unsigned char a, signed char b);
int func_020644cc(int);
void func_020ab628(void *p, int i, char *c, int zero, signed long lit, int zero2, int zero3);
void func_020ab5f8(void *p);
extern unsigned char data_021f43f8[];

void func_0201cfb4(void *unused, char *base)
{
    int i;
    for (i = 0; i < 5; i++) {
        char *p = base + i * 2;
        base[i * 2] = 0;
        p[1] = 0;
        *(int *) (base + i * 4 + 0xc) = 0;
    }
    base[0x20] = 0;
    base[0x21] = (char) 0xff;
}

void func_0201cf90(int unused, unsigned char *p, int i, unsigned char val, unsigned char b, int w)
{
    p[i * 2] = val;
    *(p + i * 2 + 1) = b;
    *(int *) (p + i * 4 + 12) = w;
}

void func_0201cf74(int a0, int a1, int a2, UnkStruct_0201cf74 *a3, unsigned int a4)
{
    func_0201cf90(a0, (unsigned char *) a1, a2, a3->unk_00, a3->unk_01, a4);
}

void func_0201cf54(int *base)
{
    int i = 0;
    int v = i;
    for (; i < 5; i++) {
        *(base + i + 0x50) = v;
    }
}

void func_0201cec8(void *p0, char *p1)
{
    void *result;
    int zero;
    int i;
    char c;
    unsigned char *p;
    int diff;
    int add;
    unsigned char b;

    result = func_020160b4(p0);
    if (result == 0) {
        return;
    }

    func_0201cf54((int *) p0);
    func_020ab670(result, (unsigned char) p1[0x20], (signed char) p1[0x21]);

    zero = 0;
    for (i = 0; i < (unsigned char) p1[0x20]; i++) {
        p = (unsigned char *) p1 + (i << 1);
        diff = p[1] - ((unsigned char *) p1)[i * 2] + 1;
        add = func_020644cc(diff);
        b = ((unsigned char *) p1)[i * 2];
        c = (char) (b + add);
        func_020ab628(result, i, &c, zero, (unsigned int) data_021f43f8, zero, zero);
        *(unsigned int *) ((char *) p0 + i * 4 + 0x140) = *(unsigned int *) ((char *) p1 + i * 4 + 0xc);
    }

    func_020ab5f8(result);
}
