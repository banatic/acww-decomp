/* text_draw_3: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02051608 @ 0x02051608, 0x1a bytes, Thumb
 * func_020515cc @ 0x020515cc, 0x3c bytes, Thumb
 * func_020515b8 @ 0x020515b8, 0x14 bytes, Thumb
 * func_020515ac @ 0x020515ac, 0xa bytes, Thumb
 * func_0205156c @ 0x0205156c, 0x40 bytes, Thumb
 * func_02051568 @ 0x02051568, 0x2 bytes, Thumb
 * func_020514dc @ 0x020514dc, 0x8c bytes, Thumb
 * func_0205148c @ 0x0205148c, 0x50 bytes, Thumb
 * func_02051480 @ 0x02051480, 0xc bytes, Thumb
 * func_02051478 @ 0x02051478, 0x8 bytes, Thumb
 * func_02051458 @ 0x02051458, 0x20 bytes, Thumb
 * func_02051400 @ 0x02051400, 0x58 bytes, Thumb
 */

struct UnkStruct_020515b8;

typedef unsigned int (*FuncPtr)(struct UnkStruct_020515b8 *);

struct VTable {
    unsigned int pad_00;
    unsigned int pad_04;
    unsigned int pad_08;
    FuncPtr func;
};

struct UnkStruct_020515b8 {
    struct VTable *vtable;
};

struct UnkStruct_0205156c {
    unsigned char pad_00[0x28];
    int unk_28; // 0x28
    unsigned char pad_2C[0x08];
    int unk_34; // 0x34
    unsigned char pad_38[0x2C];
    int unk_64; // 0x64
    int unk_68; // 0x68
};

typedef struct {
    char pad_00[0x54];
    unsigned char flag;
    char pad_55[3];
    int key;
    int state;
} MNode;

extern int func_020516b8(int a, int key);
extern int func_0205171c(int a, int b);
extern int data_020dcf88;
extern int data_020dcf90;
extern int data_020dcf98;
extern int data_020dcfa0;
extern void func_02051794(int, int *, int, int, int);
extern int func_020ea1bc(int, int);
extern void NNS_FndInitList(int, int);
extern unsigned char data_021c8194[];
extern unsigned char data_021fbe94[];
extern unsigned char data_021c81bc[];
extern unsigned char data_021c81d4[];
extern unsigned char data_021c8230[];
extern unsigned char data_021c828c[];
extern unsigned char data_021c82e8[];
extern void func_02050e24(void);
extern void func_020e9fc8(int x);
extern void func_02051758(const void *addr);
extern void MI_CpuFill8(void *p, unsigned char b, unsigned int c);
extern int data_021c8344;
extern void *NNS_FndGetNextListObject(void *a, void *b);
extern void func_02050f0c(void *p);
extern void func_02051368(void *p);

void func_02051400(int param);

void func_02051608(void *r0, unsigned char r1, unsigned char r2, int r3, int r4)
{
    unsigned char *p;
    int *q;

    p = (unsigned char *) r0 + 0x3a;
    *p = r1;
    p = (unsigned char *) r0 + 0x3b;
    *p = r2;
    q = (int *) r0 + 0x10;
    *q = r3;
    q = (int *) r0 + 0x11;
    *q = r4;
}

void func_020515cc(void *obj, unsigned char a, unsigned char b, unsigned int c, unsigned int d, unsigned char e,
                   unsigned char f, unsigned int g, unsigned int h)
{
    ((unsigned char *) obj)[0x3a] = a;
    ((unsigned char *) obj)[0x3b] = b;
    ((unsigned int *) ((unsigned char *) obj + 0x40))[0] = c;
    ((unsigned int *) ((unsigned char *) obj + 0x44))[0] = d;
    ((unsigned char *) obj)[0x3c] = e;
    ((unsigned char *) obj)[0x3d] = f;
    ((unsigned int *) ((unsigned char *) obj + 0x48))[0] = g;
    ((unsigned int *) ((unsigned char *) obj + 0x4c))[0] = h;
}

unsigned int func_020515b8(struct UnkStruct_020515b8 *obj)
{
    return (obj->vtable->func(obj) + 7) >> 3;
}

void func_020515ac(int *p)
{
    p[0x68 / 4] = 0;
    p[0x64 / 4] = -1;
}

void func_0205156c(struct UnkStruct_0205156c *self, int key)
{
    int tmp;

    self->unk_64 = func_020516b8(self->unk_28, key);
    if (self->unk_64 == -1) {
        self->unk_64 = func_020516b8(self->unk_28, 0xff20);
    }

    tmp = func_0205171c(self->unk_28, self->unk_64);
    self->unk_68 = self->unk_68 + tmp;
    self->unk_68 = self->unk_68 + self->unk_34;
}

void func_02051568(void) {}

void func_020514dc(void)
{
    int result;

    func_02051794((unsigned int) data_021c8230, &data_020dcf88, 0, 0, 0);
    func_02051794((unsigned int) data_021c828c, &data_020dcf90, 0, 0, 0);
    func_02051794((unsigned int) data_021c82e8, &data_020dcf98, 0, 0, 0);
    func_02051794((unsigned int) data_021c81d4, &data_020dcfa0, 0, 0, 0);

    result = func_020ea1bc(0x1800, *((int *) data_021fbe94));
    *((int *) data_021c8194) = result;

    if (result) {
        NNS_FndInitList((unsigned int) data_021c81bc, 8);
    }
}

void func_0205148c(void)
{
    if ((*(int *) data_021c8194) != 0) {
        func_02050e24();
        func_020e9fc8((*(int *) data_021c8194));
        (*(int *) data_021c8194) = 0;
    }
    func_02051758((const void *) data_021c8230);
    func_02051758((const void *) data_021c828c);
    func_02051758((const void *) data_021c82e8);
    func_02051758((const void *) data_021c81d4);
}

void func_02051480(void)
{
    func_02051400(1);
}

void func_02051478(void)
{
    func_02050e24();
}

void func_02051458(void *ptr)
{
    unsigned char b = ((unsigned char *) ptr)[0x39];
    MI_CpuFill8(&data_021c8344, (unsigned char) (b | (b << 4)), 0x400);
}

void func_02051400(int param)
{
    MNode *node = 0;
    int local = 0;
    int neg_one = -1;
    int zero = 0;

    while (1) {
        node = NNS_FndGetNextListObject(((int *) data_021c81bc), node);
        if (node == 0) {
            break;
        }
        if (node->key == param) {
            if (node->state != ~local) {
                func_02050f0c(node);
                node->state = neg_one;
            }
            if (node->flag != 0) {
                func_02051368(node);
                node->flag = zero;
            }
        }
    }
}
