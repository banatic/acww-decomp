/* session_players: 36 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209646c @ 0x0209646c, 0x18 bytes, Thumb
 * func_0209645c @ 0x0209645c, 0x10 bytes, Thumb
 * func_02096440 @ 0x02096440, 0x1a bytes, Thumb
 * func_02096438 @ 0x02096438, 0x6 bytes, Thumb
 * func_0209642c @ 0x0209642c, 0xc bytes, Thumb
 * func_0209641c @ 0x0209641c, 0xe bytes, Thumb
 * func_02096414 @ 0x02096414, 0x6 bytes, Thumb
 * func_02096408 @ 0x02096408, 0xc bytes, Thumb
 * func_020963f8 @ 0x020963f8, 0xe bytes, Thumb
 * func_020963f0 @ 0x020963f0, 0x6 bytes, Thumb
 * func_020963e4 @ 0x020963e4, 0xc bytes, Thumb
 * func_020963d4 @ 0x020963d4, 0xe bytes, Thumb
 * func_02096398 @ 0x02096398, 0x3a bytes, Thumb
 * func_020962f8 @ 0x020962f8, 0xa0 bytes, Thumb
 * func_020962dc @ 0x020962dc, 0x1c bytes, Thumb
 * func_020962c8 @ 0x020962c8, 0x14 bytes, Thumb
 * func_020962b8 @ 0x020962b8, 0x10 bytes, Thumb
 * func_020962a4 @ 0x020962a4, 0x14 bytes, Thumb
 * func_02096294 @ 0x02096294, 0x10 bytes, Thumb
 * func_02096284 @ 0x02096284, 0x10 bytes, Thumb
 * func_0209627c @ 0x0209627c, 0x8 bytes, Thumb
 * func_02096274 @ 0x02096274, 0x8 bytes, Thumb
 * func_0209626c @ 0x0209626c, 0x8 bytes, Thumb
 * func_02096260 @ 0x02096260, 0xc bytes, Thumb
 * func_02096254 @ 0x02096254, 0xc bytes, Thumb
 * func_02096244 @ 0x02096244, 0x10 bytes, Thumb
 * func_02096238 @ 0x02096238, 0xc bytes, Thumb
 * func_02096204 @ 0x02096204, 0x34 bytes, Thumb
 * func_020961f0 @ 0x020961f0, 0x14 bytes, Thumb
 * func_020961e0 @ 0x020961e0, 0x10 bytes, Thumb
 * func_020961d0 @ 0x020961d0, 0x10 bytes, Thumb
 * func_020961c0 @ 0x020961c0, 0x10 bytes, Thumb
 * func_020961bc @ 0x020961bc, 0x2 bytes, Thumb
 * func_020961a8 @ 0x020961a8, 0x12 bytes, Thumb
 * func_020961a4 @ 0x020961a4, 0x2 bytes, Thumb
 * func_02096190 @ 0x02096190, 0x12 bytes, Thumb
 */

typedef struct {
    unsigned int v[3];
} Vec3;

typedef struct {
    unsigned char pad_00[0x18];
    struct {
        unsigned short a : 7;
        unsigned short b : 4;
        unsigned short c : 5;
    } flags;
    unsigned short unk_1A;
    unsigned char unk_1C;
    unsigned char pad_1D[3];
    unsigned int arr20[4];
    unsigned char arr30[4];
    Vec3 vecs[4];
    unsigned short arr64[4];
} UnkStruct_020962f8;

extern int func_02077898(const void *);
extern void func_020012dc(void *);
extern void func_020012e8(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern unsigned char data_021d5684[];
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern int data_021d569c;
extern int data_021d569e;
extern int data_021d56a0;
extern char data_021d56a4[];
extern char data_021d56b4[];
extern char data_021d56b8[]; // 0x021d56b8
extern unsigned short data_021d56e8[];
extern int func_02096718(int a);

void func_0209646c(int r0, unsigned short *r4, int *r6)
{
    int r5 = r0;
    int r2 = *r6;
    unsigned char r0_2;

    r0 = func_02077898((const void *) r0);
    *r4 = (unsigned short) r0;
    r0_2 = *(unsigned char *) (r5 + 2);
    *r6 = r0_2;
}

void func_0209645c(unsigned char *out, unsigned int a, unsigned int b)
{
    *out = (unsigned char) (((b << 4) & 0x70) | (a & 0x0f));
}

void func_02096440(unsigned char *src, unsigned char *low, unsigned char *high)
{
    *low = *src & 0xF;
    *high = (*src >> 4) & 0x7;
}

void func_02096438(int *p, int i, int v)
{
    p[i] = v;
}

void func_0209642c(int a, int b)
{
    func_02096438((int *) a, b, 0);
}

int func_0209641c(int *r0, int r1)
{
    if (r1 < 4) {
        return r0[r1];
    }
    return 0;
}

void func_02096414(unsigned char *p, int i, int v)
{
    unsigned char *q = p + i;
    q[0x10] = (unsigned char) v;
}

void func_02096408(int a, int b)
{
    func_02096414((unsigned char *) a, b, 7);
}

unsigned char func_020963f8(unsigned char *ptr, int idx)
{
    if (idx < 4) {
        return *(unsigned char *) (ptr + idx + 16);
    }
    return 7;
}

void func_020963f0(unsigned char *p, int i, int v)
{
    unsigned char *q = p + i;
    q[0x14] = (unsigned char) v;
}

void func_020963e4(int a, int b)
{
    func_020963f0((unsigned char *) a, b, 4);
}

int func_020963d4(unsigned char *p, int i)
{
    if (i < 4) {
        return *(p + i + 0x14);
    }
    return 4;
}

int func_02096398(void *arg)
{
    unsigned int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == func_020963d4((unsigned char *) arg, j)) {
                break;
            }
        }
        if (j < 4) {
            continue;
        }
        return i;
    }
    return 4;
}

UnkStruct_020962f8 *func_020962f8(UnkStruct_020962f8 *p)
{
    unsigned int i;
    __cxa_vec_ctor((void *) ((char *) p + 0x34), 4, 0xc, (void (*)(void *)) func_020012e8, (void (*)(void *)) func_020012dc);
    for (i = 0; i < 4; i++) {
        func_02096408((int) ((void *) data_021d5684), i);
        func_020963e4((int) ((void *) data_021d5684), i);
        p->arr20[i] = 0x93;
        p->arr30[i] = 0x33;
        p->vecs[i].v[0] = 0;
        p->vecs[i].v[1] = 0;
        p->vecs[i].v[2] = 0;
        p->arr64[i] = 0;
    }
    p->flags.a = 0;
    p->flags.b = 1;
    p->flags.c = 1;
    p->unk_1A = 0;
    p->unk_1C = 0;
    return p;
}

void *func_020962dc(void *p)
{
    __cxa_vec_cleanup((void *) ((char *) p + 0x34), 4, 12, (void (*)(void *)) func_020012dc);
    return p;
}

void func_020962c8(int a, int b)
{
    func_02096438((int *) ((unsigned int) data_021d5684), a, b);
}

void func_020962b8(void *param1)
{
    func_0209642c((int) ((void *) data_021d5684), (int) param1);
}

void func_020962a4(int a, int b)
{
    func_02096414((unsigned char *) (((int *) data_021d5684)), a, b);
}

void func_02096294(void *param0)
{
    func_02096408((int) ((void *) data_021d5684), (int) param0);
}

unsigned char func_02096284(void *arg)
{
    return func_020963f8(data_021d5684, (int) arg);
}

int func_0209627c(void)
{
    return (int) &data_021d569c;
}

int func_02096274(void)
{
    return (int) &data_021d569e;
}

int func_0209626c(void)
{
    return (int) &data_021d56a0;
}

char *func_02096260(int param)
{
    return &data_021d56a4[param * 4];
}

char *func_02096254(int index)
{
    return &data_021d56b4[index];
}

int func_02096244(int a)
{
    return (int) &data_021d56b8[a * 12];
}

unsigned short *func_02096238(int idx)
{
    return &data_021d56e8[idx];
}

void func_02096204(void *param)
{
    int *a;
    char *b;
    int *c;
    short *d;

    a = (int *) func_02096260((int) param);
    *a = 0x93;

    b = func_02096254((int) param);
    *b = 0x33;

    c = (int *) func_02096244((int) param);
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;

    d = (short *) func_02096238((int) param);
    *d = 0;
}

void func_020961f0(int a, int b)
{
    func_020963f0((unsigned char *) (((int *) data_021d5684)), a, b);
}

void func_020961e0(void *param1)
{
    void *r1;
    void *r0;
    void *r3;

    r1 = param1;
    r0 = (void *) data_021d5684;
    r3 = (void *) (void (*)(void *, void *)) func_020963e4;
    func_020963e4((int) r0, (int) r1);
}

int func_020961d0(void *arg)
{
    return func_020963d4((unsigned char *) ((void *) data_021d5684), (int) arg);
}

int func_020961c0(void)
{
    return func_02096398((void *) data_021d5684);
}

void *func_020961bc(void *object)
{
    return object;
}

int func_020961a8(int a)
{
    return (int) func_020961bc((void *) func_02096718(a));
}

int func_020961a4(int object)
{
    return object;
}

int func_02096190(int argument0)
{
    return func_020961a4(func_02096718((int) argument0));
}
