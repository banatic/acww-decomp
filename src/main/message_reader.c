/* message_reader: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b4218 @ 0x020b4218, 0x88 bytes, Thumb
 * func_020b419c @ 0x020b419c, 0x7c bytes, Thumb
 * func_020b4178 @ 0x020b4178, 0x24 bytes, Thumb
 * func_020b40dc @ 0x020b40dc, 0x9c bytes, Thumb
 * func_020b4070 @ 0x020b4070, 0x6c bytes, Thumb
 * func_020b4044 @ 0x020b4044, 0x2c bytes, Thumb
 * func_020b402c @ 0x020b402c, 0x18 bytes, Thumb
 * func_020b400c @ 0x020b400c, 0x20 bytes, Thumb
 * func_020b3ffc @ 0x020b3ffc, 0x10 bytes, Thumb
 */

struct Node {
    signed char data;
};

struct UnkStruct_020b4218 {
    char pad_00[0x0afc];
    struct Node start_node;
    char pad_AFD[0x0df7];
    char sub[1];
    char pad_18F5[0x33];
    unsigned char flag;
    char pad_1929[0x2f];
    struct Node *current;
};

struct UnkStruct_020b4044 {
    void *unk_00;
    char pad_04[0x1c];
    int unk_20;
    int unk_24;
    char unk_28;
    char unk_29;
};

struct UnkStruct_020b400c {
    void *vtable;
};

struct UnkStruct_020b3ffc {
    char pad_00[0x20];
    int unk_20;
};

extern void func_020b4c0c(char *p);
extern struct Node *func_020a7bf4(struct Node *n, int a);
extern void func_020b4bf0(char *p, int n);
extern void func_020b4bd4(char *p);
extern void func_020a94a4(void *ptr);
extern void func_020a9354(void *ptr, int x);
extern int func_020a92d8(void *, int);
extern int func_020b4bb4(void *ptr);
extern int func_02050bdc_unk(int, int);
extern void *func_020b5418(void *p, void *q);
extern void *func_020b54c8(void *p);
extern void func_020a9b50(void *p);
extern void *func_020b4ca4(void *p);
extern void *func_020b4ad4(void *p);
extern void *func_020a8210(void *);
extern void *func_020a8228(void *);
extern void *func_020b550c(void *);
extern void *func_020b5524(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void MI_CpuFill8(void *p, int a, int b);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_020b4ab4(void *ptr);
extern void *func_020b4c84(void *ptr);
extern void func_020a9b44(void *ptr);
extern void *func_020b54b0(void *ptr);
extern void *func_020b53f8(void *ptr);
extern void *func_020a81b8(void *param);
extern unsigned char data_020e5200[];
extern void func_020a8188(void *);
extern void func_020edb3c(void *);
extern int data_020d208c[];

int func_020b419c(char *p);
int func_020b4178(int a, int b);

int func_020b4218(struct UnkStruct_020b4218 *self)
{
    int ret;
    struct Node *start;

    ret = 0;
    func_020b4c0c(self->sub);
    start = &self->start_node;

    while (self->flag == 0) {
        struct Node *n = start;
        int val = 0;

        while (n != 0 && n->data != 10) {
            self->current = n;
            val = func_020b419c((char *) self);
            if (val > 0) {
                break;
            }
            n = func_020a7bf4(n, 1);
        }

        func_020b4c0c(self->sub);
        if (val > 0) {
            func_020b4bf0(self->sub, val);
            ret = 1;
        } else {
            func_020b4bd4(self->sub);
        }
    }

    return ret;
}

int func_020b419c(char *p)
{
    int count;
    char *base;
    int val;

    count = 0;
    func_020b4c0c((char *) (p + 0x18f4));
    func_020a94a4(p + 0x1934);
    func_020a9354(p + 0x1934, *(int *) (p + 0x1958));

    base = p + 0x18f4;

    while (1) {
        *(int *) (p + 0x195c) = 1;
        *(int *) (p + 0x1960) = 0;

        func_020a92d8(p + 0x1934, 0);

        val = *(int *) (p + 0x1960);
        if (val == 0xa || val == 0) {
            break;
        }

        if (func_020b4178(func_020b4bb4(base), val) != 0) {
            count++;
        } else {
            count = 0;
            break;
        }
    }

    return count;
}

int func_020b4178(int a, int b)
{
    int ret = 0;
    int res;
    if (a == b) {
        ret = 1;
    } else {
        res = func_02050bdc_unk(a, b);
        if (res == b) {
            ret = 1;
        }
    }
    return ret;
}

void *func_020b40dc(char *self)
{
    func_020b5418(self, self);
    func_020b54c8(self + 0x4c);
    func_020a9b50(self + 0xaf0);
    __cxa_vec_ctor((void *) (self + 0x14fc), 0xb, 0x5c, (((void (*)(void *)) func_020a8228)),
                   (((void (*)(void *)) func_020a8210)));
    *(int *) (self + 0x18f0) = 0;
    func_020b4ca4(self + 0x18f4);
    func_020b4ad4(self + 0x1934);
    __cxa_vec_ctor((void *) (self + 0x1964), 0x10, 0x20, (((void (*)(void *)) func_020b5524)),
                   (((void (*)(void *)) func_020b550c)));
    MI_CpuFill8(self + 0xafc, 0, 0xa00);
    return self;
}

void *func_020b4070(void *s)
{
    __cxa_vec_cleanup((void *) ((char *) s + 0x1964), 0x10, 0x20, (((void (*)(void *)) func_020b550c)));
    func_020b4ab4((char *) s + 0x1934);
    func_020b4c84((char *) s + 0x18f4);
    __cxa_vec_cleanup((void *) ((char *) s + 0x14fc), 0xb, 0x5c, (((void (*)(void *)) func_020a8210)));
    func_020a9b44((char *) s + 0x0af0);
    func_020b54b0((char *) s + 0x4c);
    func_020b53f8(s);
    return s;
}

struct UnkStruct_020b4044 *func_020b4044(struct UnkStruct_020b4044 *self)
{
    func_020a81b8(self);
    self->unk_00 = (void *) data_020e5200;
    self->unk_20 = 0;
    self->unk_24 = 0;
    self->unk_28 = 0;
    self->unk_29 = 0;
    return self;
}

void *func_020b402c(void *self)
{
    *(void **) self = ((int *) data_020e5200);
    func_020a8188(self);
    return self;
}

void *func_020b400c(struct UnkStruct_020b400c *self)
{
    self->vtable = ((char *) data_020e5200);
    func_020a8188(self);
    func_020edb3c(self);
    return self;
}

int func_020b3ffc(struct UnkStruct_020b3ffc *p)
{
    return data_020d208c[p->unk_20];
}
