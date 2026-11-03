/* head_look: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205e274 @ 0x0205e274, 0xd2 bytes, Thumb
 * func_0205e1bc @ 0x0205e1bc, 0xb6 bytes, Thumb
 * func_0205e1a8 @ 0x0205e1a8, 0x14 bytes, Thumb
 * func_0205e194 @ 0x0205e194, 0x14 bytes, Thumb
 * func_0205e174 @ 0x0205e174, 0x20 bytes, Thumb
 * func_0205e160 @ 0x0205e160, 0x14 bytes, Thumb
 * func_0205e14c @ 0x0205e14c, 0x14 bytes, Thumb
 * func_0205e138 @ 0x0205e138, 0x14 bytes, Thumb
 * func_0205e118 @ 0x0205e118, 0x20 bytes, Thumb
 */

typedef struct UnkStruct_0205e1bc UnkStruct_0205e1bc;

struct UnkStruct_0205e1bc {
    unsigned char pad_00[0xd];
    unsigned char state;
};

extern void *func_021077e8(void *p);
extern int NNS_G3dTexGetRequiredSize(void *p);
extern int NNS_G3dTex4x4GetRequiredSize(void *p);
extern int NNS_G3dPlttGetRequiredSize(void *p);
extern void func_02055b50(void *a, void *b);
extern int func_02055c74(void *a, int b);
extern int func_02055c2c(void *a, int b, int c);
extern int func_02055c68(void *a, int b);
extern int func_02055c18(void *a, int b, int c);
extern int func_02055c40(void *a, int b);
extern int func_02055bac(void *a, int b, int c);
extern void func_02055b34(void *a, int b, int c, int d);
extern int func_020b9eec(UnkStruct_0205e1bc *p, int val, int flag);
extern int func_0205e560(void *, unsigned char);
extern unsigned char data_021c9f5c[];
extern int func_0205e54c(unsigned int, unsigned char, unsigned int);
extern void func_0205e538(void *p, unsigned char ch, int x, int y);
extern int func_0205e528(void *ptr, unsigned char val, int param);
extern int func_0205e518(void *, unsigned char, int);
extern int func_0205e508(unsigned char *data, unsigned char byte, int flag);
extern void func_0205e4f8(void *, unsigned char, int, int);

int func_0205e194(unsigned char *arg0, unsigned int arg1);
int func_0205e160(unsigned char *arg0, int arg1);
int func_0205e14c(unsigned char *p1, int p2);
int func_0205e138(const unsigned char *src, int flag);

void func_0205e274(void *p)
{
    void *q;
    void *a;
    void *tmp;
    void *b;
    int v1, v2, v3, w1, w2, w3;
    int t1, t2, t3, t4, t5, t6;

    a = func_021077e8((void *) func_0205e194((unsigned char *) p, 0));
    q = (void *) func_0205e160((unsigned char *) p, 0);
    func_02055b50(q, a);

    if (func_0205e138((const unsigned char *) p, 1) >= 0x9e) {
        return;
    }

    tmp = (void *) func_0205e194((unsigned char *) p, 1);
    if (tmp == 0) {
        return;
    }

    v1 = NNS_G3dTexGetRequiredSize(a);
    v2 = NNS_G3dTex4x4GetRequiredSize(a);
    v3 = NNS_G3dPlttGetRequiredSize(a);

    b = func_021077e8(tmp);

    w1 = NNS_G3dTexGetRequiredSize(b);
    w2 = NNS_G3dTex4x4GetRequiredSize(b);
    w3 = NNS_G3dPlttGetRequiredSize(b);

    p = (void *) func_0205e160((unsigned char *) p, 1);

    t1 = func_02055c74(q, v1);
    t2 = func_02055c2c(q, t1, w1);
    t3 = func_02055c68(q, v2);
    t4 = func_02055c18(q, t3, w2);
    t5 = func_02055c40(q, v3);
    t6 = func_02055bac(q, t5, w3);

    func_02055b34(p, t2, t4, t6);
    func_02055b50(p, b);
}

int func_0205e1bc(UnkStruct_0205e1bc *p)
{
    volatile int unused;
    int r6 = 0;
    int r4 = r6;
    UnkStruct_0205e1bc *a = (UnkStruct_0205e1bc *) func_0205e14c((unsigned char *) p, r6);
    unsigned int flag1 = (a->state == 2) ? 1 : 0;
    if (flag1 != 0) {
        r6 = 1;
    } else {
        unsigned int flag2 = (a->state == 1) ? 1 : 0;
        if (flag2 == 0) {
            UnkStruct_0205e1bc *b0 = (UnkStruct_0205e1bc *) func_0205e194((unsigned char *) p, 0);
            int e = (int) func_021077e8((void *) b0);
            func_020b9eec(a, e, 1);
        }
    }
    if (func_0205e138((const unsigned char *) p, 1) < 0x9e) {
        UnkStruct_0205e1bc *b1 = (UnkStruct_0205e1bc *) func_0205e194((unsigned char *) p, 1);
        UnkStruct_0205e1bc *a2 = (UnkStruct_0205e1bc *) func_0205e14c((unsigned char *) p, 1);
        unsigned int flag3 = (a2->state == 2) ? 1 : 0;
        if (flag3 != 0) {
            r4 = 1;
        } else {
            unsigned int flag4 = (a2->state == 1) ? 1 : 0;
            if (flag4 == 0) {
                int e2 = (int) func_021077e8((void *) b1);
                func_020b9eec(a2, e2, 1);
            }
        }
    } else {
        r4 = 1;
    }
    if (r6 != 0 && r4 != 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_0205e1a8(void *ptr)
{
    return func_0205e560((void *) data_021c9f5c, *(unsigned char *) ptr);
}

int func_0205e194(unsigned char *arg0, unsigned int arg1)
{
    return func_0205e54c((unsigned int) data_021c9f5c, *arg0, arg1);
}

void func_0205e174(unsigned char *a, int b, int c)
{
    func_0205e538(((int *) data_021c9f5c), *a, b, c);
}

int func_0205e160(unsigned char *arg0, int arg1)
{
    return func_0205e528((void *) data_021c9f5c, *arg0, arg1);
}

int func_0205e14c(unsigned char *p1, int p2)
{
    return func_0205e518(((char *) data_021c9f5c), *p1, p2);
}

int func_0205e138(const unsigned char *src, int flag)
{
    return func_0205e508(data_021c9f5c, *src, flag);
}

void func_0205e118(unsigned char *ptr, int a, int b)
{
    func_0205e4f8(((int *) data_021c9f5c), *ptr, a, b);
}
