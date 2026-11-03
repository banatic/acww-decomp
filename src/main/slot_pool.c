/* slot_pool: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020832e4 @ 0x020832e4, 0x12 bytes, Thumb
 * func_020832c4 @ 0x020832c4, 0x20 bytes, Thumb
 * func_020832ac @ 0x020832ac, 0x16 bytes, Thumb
 * func_02083294 @ 0x02083294, 0x18 bytes, Thumb
 * func_02083274 @ 0x02083274, 0x20 bytes, Thumb
 * func_02083260 @ 0x02083260, 0x14 bytes, Thumb
 * func_02083228 @ 0x02083228, 0x38 bytes, Thumb
 * func_020831fc @ 0x020831fc, 0x2c bytes, Thumb
 * func_020831c8 @ 0x020831c8, 0x34 bytes, Thumb
 * func_020831c0 @ 0x020831c0, 0x8 bytes, Thumb
 * func_020831a4 @ 0x020831a4, 0x1c bytes, Thumb
 * func_02083178 @ 0x02083178, 0x2a bytes, Thumb
 * func_02083148 @ 0x02083148, 0x30 bytes, Thumb
 * func_02083134 @ 0x02083134, 0x14 bytes, Thumb
 * func_02083110 @ 0x02083110, 0x22 bytes, Thumb
 */

struct UnkStruct_020832e4 {
    int unk_00;
    unsigned int size;
    unsigned short data[1];
};

typedef struct {
    int unk_00;
    unsigned int count;
} UnkStruct_020832c4;

typedef struct {
    int *unk_00;
    int unk_04;
    int unk_08;
} SelfType;

typedef struct {
    void *unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_020831fc;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_02083178;

typedef struct {
    unsigned char pad_00[4];
    unsigned int unk_04;
} UnkStruct_02083148;

typedef struct {
    unsigned int unk_00;
    unsigned int count;
} self_t;

extern unsigned char *func_02083320(void);
extern void func_02083cb8(void *);
extern void *func_0205efac(void *);
extern void *func_0205ef90(void *arg);
extern void func_02083cb4(void *receiver);
extern void func_0205ec50(void *a, int b, int c, int d, int e, int f);
extern void func_0205ebb4(void *);
extern void func_02083ca8(void *, int);
extern void __arm __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __arm __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02083c78(void *);
extern unsigned char data_020e1b00[];
extern void func_020edb3c(void *);
extern int data_021d1f04;
extern void func_02083c30(void *p, unsigned int n);

int func_02083148(UnkStruct_02083148 *p, unsigned int i, int c);

unsigned short *func_020832e4(struct UnkStruct_020832e4 *self, unsigned int index)
{
    unsigned short *result = 0;
    if (index < self->size) {
        result = &self->data[index];
    }
    return result;
}

unsigned char *func_020832c4(UnkStruct_020832c4 *param0, unsigned int param1)
{
    unsigned char *ret = 0;
    if (param1 < param0->count) {
        unsigned char *base = func_02083320();
        unsigned int offset = param1 * 2;
        base += 8;
        base += offset;
        ret = base + 1;
    }
    return ret;
}

void *func_020832ac(void *arg)
{
    func_02083cb8(arg);
    func_0205efac((char *) arg + 4);
    return arg;
}

void *func_02083294(void *arg)
{
    func_0205ef90((char *) arg + 4);
    func_02083cb4(arg);
    return arg;
}

void func_02083274(char *p, int b, int c)
{
    func_0205ec50(p + 4, b, 0, c, 0, 0);
    *p = 1;
}

void func_02083260(void *arg)
{
    unsigned char *p = (unsigned char *) arg;
    func_0205ebb4(p + 4);
    *p = 0;
}

SelfType *func_02083228(SelfType *self)
{
    func_02083ca8(self, 5);
    self->unk_00 = ((int *) data_020e1b00);
    __cxa_vec_ctor((void *) (&self->unk_08), 5, 0x6c, (((void (*)(void *)) func_020832ac)),
                   (((void (*)(void *)) func_02083294)));
    return self;
}

UnkStruct_020831fc *func_020831fc(UnkStruct_020831fc *p)
{
    p->unk_00 = (void *) data_020e1b00;
    __cxa_vec_cleanup((void *) (&p->unk_08), 5, 0x6c, (((void (*)(void *)) func_02083294)));
    func_02083c78(p);
    return p;
}

void *func_020831c8(void *param)
{
    *(void **) param = ((int *) data_020e1b00);
    __cxa_vec_cleanup((void *) ((char *) param + 8), 5, 0x6c, (((void (*)(void *)) func_02083294)));
    func_02083c78(param);
    func_020edb3c(param);
    return param;
}

int func_020831c0(void)
{
    return (int) &data_021d1f04;
}

int func_020831a4(int a, int b)
{
    unsigned short tmp = 0xfff1;
    return func_02083148((UnkStruct_02083148 *) a, b, (int) (&tmp));
}

void func_02083178(UnkStruct_02083178 *p, unsigned int n)
{
    func_02083c30(p, n);
    if (n < p->unk_04) {
        func_02083260((void *) ((unsigned char *) func_020831c0() + 8 + n * 0x6c));
    }
}

int func_02083148(UnkStruct_02083148 *p, unsigned int i, int c)
{
    int r = 0;
    if (i < p->unk_04) {
        unsigned int n4 = 4;
        n4 += i;
        func_02083274((char *) ((unsigned char *) func_020831c0() + 8 + i * 0x6c), n4, c);
        r = 1;
    }
    return r;
}

void *func_02083134(char *p, unsigned int i)
{
    void *result = 0;
    if (i < *(unsigned int *) (p + 4)) {
        result = p + 8 + 108 * i;
    }
    return result;
}

char *func_02083110(self_t *self, unsigned int index)
{
    if (index < self->count) {
        char *p = (char *) func_020831c0() + 8;
        return p + index * 0x6C + 4;
    } else {
        return 0;
    }
}
