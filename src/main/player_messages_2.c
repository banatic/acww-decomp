/* player_messages_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02070778 @ 0x02070778, 0xc bytes, Thumb
 * func_02070760 @ 0x02070760, 0x18 bytes, Thumb
 * func_0207072c @ 0x0207072c, 0x34 bytes, Thumb
 * func_020706cc @ 0x020706cc, 0x60 bytes, Thumb
 * func_02070658 @ 0x02070658, 0x74 bytes, Thumb
 * func_02070614 @ 0x02070614, 0x44 bytes, Thumb
 */

typedef void (*Func)(void *, int);

typedef struct UnkStruct_020706cc {
    unsigned char pad_00[0x8e];
    short unk_8E;
} UnkStruct_020706cc;

typedef struct {
    int a;
    int b;
} Pair;

extern unsigned char data_020df6a4;
extern Func data_020df6bc[];
extern void func_02077ed4(void *);
extern void *func_020e9958(void *, int);
extern void MI_CpuCopy8(void *, void *, int);
extern void func_020e993c(void *, void *);
extern unsigned char data_021fbe94[];
extern unsigned char data_020e54a8;
extern UnkStruct_020706cc *func_020961a8(int);
extern int func_ov003_0222ea84(int);
extern void func_ov003_0222e898(int, int);
extern void func_ov003_0222eabc(int, int);
extern int data_020c904c;
extern void func_02077978(unsigned char *src, int *out1, int *out2);
extern int func_ov003_0222780c(unsigned char k, unsigned short idx, Pair *pr);
extern void func_ov003_0222c3a8(Pair *pr, unsigned char k);
extern unsigned char data_021f3a68[];
extern unsigned char data_021f3a86[];

void func_02070778(void)
{
    data_020df6a4 = 0x18;
}

void func_02070760(void *p, int arg)
{
    data_020df6bc[*(unsigned char *) p](p, arg);
}

void func_0207072c(void *arg0, int player)
{
    void *r6;
    void *r4;
    void *r0;

    r6 = *(void **) data_021fbe94;
    r4 = func_020e9958(r6, 0xc0);
    MI_CpuCopy8((char *) arg0 + 1, r4, 0xc0);
    func_02077ed4(r4);
    func_020e993c(r6, r4);
}

void func_020706cc(unsigned char *p, int a1)
{
    unsigned int ok;
    int v;
    short acc;
    unsigned char *q;
    UnkStruct_020706cc *o;

    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok > 0) {
        q = p + 1;
        v = (unsigned char) a1;
        acc = (short) ((p[2] - 0x1e) * 0xb6);
        o = func_020961a8(v);
        if (o != 0) {
            acc = (short) (acc + o->unk_8E);
            if (func_ov003_0222ea84(v) == 0) {
                func_ov003_0222e898(*q, v);
                func_ov003_0222eabc(v, acc);
            }
        }
    }
}

void func_02070658(unsigned char *p, int arg)
{
    unsigned char buf[5];
    Pair pr;
    int extra;
    unsigned int flag;
    unsigned char k;
    unsigned short idx;

    if (data_020e54a8 == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag == 0) {
        return;
    }
    k = (unsigned char) arg;
    MI_CpuCopy8((void *) (p + 2), buf, 5);
    func_02077978(buf, &pr.a, &extra);
    pr.b = data_020c904c;
    if (p[0] == 2) {
        if (p[1] < 0x38) {
            idx = (unsigned short) (p[1] + 0x12e8);
        } else {
            idx = 0x12e8;
        }
        func_ov003_0222780c(k, idx, &pr);
    } else {
        func_ov003_0222c3a8(&pr, k);
    }
}

void func_02070614(unsigned char *p, int player)
{
    char buf[30];
    MI_CpuCopy8(p + 1, (void *) buf, 30);
    switch (*p) {
        case 3:
            MI_CpuCopy8(buf, (void *) ((const void *) data_021f3a68), 30);
            break;
        case 4:
            MI_CpuCopy8(buf, (void *) ((const void *) data_021f3a86), 30);
            break;
    }
}
