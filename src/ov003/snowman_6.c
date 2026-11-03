/* snowman_6: 12 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221b79c @ 0x0221b79c, 0x1c bytes, Thumb
 * func_ov003_0221b77c @ 0x0221b77c, 0x20 bytes, Thumb
 * func_ov003_0221b75c @ 0x0221b75c, 0x20 bytes, Thumb
 * func_ov003_0221b74c @ 0x0221b74c, 0x10 bytes, Thumb
 * func_ov003_0221b6d4 @ 0x0221b6d4, 0x78 bytes, Thumb
 * func_ov003_0221b668 @ 0x0221b668, 0x6c bytes, Thumb
 * func_ov003_0221b5f8 @ 0x0221b5f8, 0x70 bytes, Thumb
 * func_ov003_0221b5f0 @ 0x0221b5f0, 0x8 bytes, Thumb
 * func_ov003_0221b5e8 @ 0x0221b5e8, 0x8 bytes, Thumb
 * func_ov003_0221b5c0 @ 0x0221b5c0, 0x28 bytes, Thumb
 * func_ov003_0221b5a4 @ 0x0221b5a4, 0x1c bytes, Thumb
 * func_ov003_0221b414 @ 0x0221b414, 0x190 bytes, Thumb
 */

typedef struct {
    void *vtbl;
    char pad_04[0x40];
    unsigned char flag;
} Object;

struct UnkStruct_0221b74c {
    char pad_00[0x44];
    unsigned char flag;
};

struct UnkStruct_0221b5f8 {
    void *unk_00;
    char pad_04[0xEC - 4];
    void *unk_EC;
    char pad_F0[0x134 - 0xF0];
    char unk_134[4];
    char pad_138[0x1d0 - 0x138];
    char unk_1D0[4];
    char pad_1D4[0x274 - 0x1d4];
    char unk_274[4];
    char pad_278[0x2a4 - 0x278];
    char unk_2A4[4];
    char pad_2A8[0x328 - 0x2a8];
    char unk_328[4];
};

typedef struct {
    int x, y, z, w;
} UnkStruct_0221b414;

extern void *func_02089ca4(void *self);
extern char data_ov003_02238280;
extern void *func_02089c58(Object *this);
extern void *func_0203f130(void *);
extern void *func_02066a30(void *);
extern void *func_0205577c(void *);
extern void *func_02032c64(void *);
extern void func_020f5958(void *);
extern void func_020f5948(void *);
extern void *func_02032c50(void *);
extern void *func_02055764(void *);
extern void *func_02066994(void *);
extern void *func_0203f080(void *);
extern unsigned char data_ov003_022382ac[];
extern unsigned char data_ov003_02238314[];
extern int func_020e9948(int, int);
extern void *memset(int, int, int);
extern int data_021c9b24;
extern void func_020e993c(int, int);
extern int data_020d1a10[4];
extern void *data_ov003_022383ac;
extern void *data_ov003_022383c8;
extern int func_0205556c(void *p, unsigned int tag, void *data);
extern int func_ov003_0221a8c4(void *self);
extern UnkStruct_0221b414 *func_020b03f8(void);
extern void func_0203efb0(void *self, unsigned short v);
extern int func_ov003_0221a004(void *self, int a);
extern void func_ov003_0221a7a0(void *self);
extern void func_02031288(void *a, void *b, void *c, int d, int e, void *f, int g);
extern void func_ov003_0221b064(void *self, int a, int b);
extern void func_0200451c(void *p);
extern void func_0203edd0(void *self);
extern int func_ov003_02236254(void *self);

void *func_ov003_0221b6d4(void *obj);
int func_ov003_0221b5c0(int arg0);
void func_ov003_0221b5a4(int arg);

void func_ov003_0221b79c(void)
{
    void *condition_value_2;
    condition_value_2 = (void *) (func_ov003_0221b5c0(0x3a4));
    if (condition_value_2 != 0) {
        func_ov003_0221b6d4(condition_value_2);
    }
}

void *func_ov003_0221b77c(void *this)
{
    func_02089ca4(this);
    *(void **) this = &data_ov003_02238280;
    ((unsigned char *) this)[0x44] = 0;
    return this;
}

Object *func_ov003_0221b75c(Object *this)
{
    this->vtbl = &data_ov003_02238280;
    this->flag = 0;
    func_02089c58(this);
    return this;
}

void func_ov003_0221b74c(struct UnkStruct_0221b74c *self, int a, int b, int flags)
{
    int bit;
    bit = flags & 4;
    if (bit != 0) {
        self->flag = 1;
    }
}

void *func_ov003_0221b6d4(void *obj)
{
    func_0203f130(obj);
    func_02066a30((char *) obj + 0xec);
    *(void **) obj = ((char *) data_ov003_022382ac);
    *(void **) ((char *) obj + 0xec) = ((char *) data_ov003_02238314);
    func_0205577c((char *) obj + 0x134);
    func_0205577c((char *) obj + 0x1d0);
    func_02032c64((char *) obj + 0x274);
    func_ov003_0221b77c((char *) obj + 0x2a4);
    func_020f5958((char *) obj + 0x328);
    *(unsigned short *) ((char *) obj + 0x39a) = 0xFFF1;
    return obj;
}

void *func_ov003_0221b668(void *self)
{
    *(void **) self = (void *) data_ov003_022382ac;
    *(void **) ((char *) self + 0xec) = (void *) data_ov003_02238314;
    func_020f5948((char *) self + 0x328);
    func_ov003_0221b75c((Object *) ((char *) self + 0x2a4));
    func_02032c50((char *) self + 0x274);
    func_02055764((char *) self + 0x1d0);
    func_02055764((char *) self + 0x134);
    func_02066994((char *) self + 0xec);
    func_0203f080(self);
    return self;
}

void *func_ov003_0221b5f8(void *arg)
{
    struct UnkStruct_0221b5f8 *obj = (struct UnkStruct_0221b5f8 *) arg;
    obj->unk_00 = ((char *) data_ov003_022382ac);
    obj->unk_EC = ((char *) data_ov003_02238314);
    func_020f5948(obj->unk_328);
    func_ov003_0221b75c((Object *) obj->unk_2A4);
    func_02032c50(obj->unk_274);
    func_02055764(obj->unk_1D0);
    func_02055764(obj->unk_134);
    func_02066994((void *) &obj->unk_EC);
    func_0203f080(obj);
    func_ov003_0221b5a4((int) obj);
    return obj;
}

int func_ov003_0221b5f0(void)
{
    return 2048;
}

int func_ov003_0221b5e8(void)
{
    return 5120;
}

int func_ov003_0221b5c0(int arg0)
{
    int ret = func_020e9948(data_021c9b24, arg0);
    memset(ret, 0, arg0);
    return ret;
}

void func_ov003_0221b5a4(int arg)
{
    if (data_021c9b24 != 0) {
        func_020e993c(data_021c9b24, arg);
    }
}

void func_ov003_0221b414(char *self)
{
    int idx;
    int tmp;
    UnkStruct_0221b414 *arr;
    char *q;

    *(unsigned short *) (self + 0x39a) = 0xfff1;

    *(int *) (self + 0x2f8) = data_020d1a10[0];
    *(int *) (self + 0x2fc) = data_020d1a10[1];
    *(int *) (self + 0x300) = data_020d1a10[2];
    *(int *) (self + 0x304) = data_020d1a10[3];

    func_0205556c(self + 0x134, 0x534e5730, &data_ov003_022383ac);
    func_0205556c(self + 0x1d0, 0x534e5731, &data_ov003_022383c8);

    if (func_ov003_0221a8c4(self)) {
        idx = *(int *) (self + 8) & 1;
        arr = func_020b03f8();
        *(int *) (self + 0x26c) = arr[idx & 1].w;

        idx = *(int *) (self + 8) & 1;
        arr = func_020b03f8();
        arr[idx & 1].x = *(int *) (self + 0x5c);
        arr[idx & 1].y = *(int *) (self + 0x60);
        arr[idx & 1].z = *(int *) (self + 0x64);

        tmp = *(int *) (self + 0x26c);
        idx = *(int *) (self + 8) & 1;
        arr = func_020b03f8();
        arr[idx & 1].w = tmp;
    }

    func_0203efb0(self, (unsigned short) *(int *) (self + 8));
    func_ov003_0221a004(self, 0);
    func_ov003_0221a7a0(self);

    *(int *) (self + 0x68) = *(int *) (self + 0x5c);
    *(int *) (self + 0x6c) = *(int *) (self + 0x60);
    *(int *) (self + 0x70) = *(int *) (self + 0x64);
    q = self + 0x68;
    *(int *) (self + 0x31c) = *(int *) (self + 0x68);
    *(int *) (self + 0x320) = *(int *) (q + 4);
    *(int *) (self + 0x324) = *(int *) (q + 8);

    func_02031288(self + 0x274, self + 0x5c, q, 0, *(int *) (self + 0x270), self, 0xb);

    *(int *) (self + 0x68) = *(int *) (self + 0x5c);
    *(int *) (self + 0x6c) = *(int *) (self + 0x60);
    *(int *) (self + 0x70) = *(int *) (self + 0x64);
    q = self + 0x68;
    *(int *) (self + 0x31c) = *(int *) (self + 0x68);
    *(int *) (self + 0x320) = *(int *) (q + 4);
    *(int *) (self + 0x324) = *(int *) (q + 8);

    *(unsigned char *) (self + 0x369) = *(unsigned char *) (self + 0x284);

    func_ov003_0221b064(self, 0, 0);
    func_0200451c(self + 0x328);
    func_0203edd0(self);
    func_ov003_02236254(self);
}
