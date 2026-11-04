/* sound_scene: 49 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f2e3c @ 0x020f2e3c, 0x2c bytes, ARM
 * func_020f2e18 @ 0x020f2e18, 0x24 bytes, ARM
 * func_020f2dec @ 0x020f2dec, 0x2c bytes, ARM
 * func_020f2da4 @ 0x020f2da4, 0x48 bytes, ARM
 * func_020f2d78 @ 0x020f2d78, 0x2c bytes, ARM
 * func_020f2d54 @ 0x020f2d54, 0x24 bytes, ARM
 * func_020f2d28 @ 0x020f2d28, 0x2c bytes, ARM
 * func_020f2ce0 @ 0x020f2ce0, 0x48 bytes, ARM
 * func_020f2cb4 @ 0x020f2cb4, 0x2c bytes, ARM
 * func_020f2c90 @ 0x020f2c90, 0x24 bytes, ARM
 * func_020f2c64 @ 0x020f2c64, 0x2c bytes, ARM
 * func_020f2c1c @ 0x020f2c1c, 0x48 bytes, ARM
 * func_020f2bf0 @ 0x020f2bf0, 0x2c bytes, ARM
 * func_020f2bcc @ 0x020f2bcc, 0x24 bytes, ARM
 * func_020f2ba0 @ 0x020f2ba0, 0x2c bytes, ARM
 * func_020f2b58 @ 0x020f2b58, 0x48 bytes, ARM
 * func_020f2b2c @ 0x020f2b2c, 0x2c bytes, ARM
 * func_020f2b08 @ 0x020f2b08, 0x24 bytes, ARM
 * func_020f2adc @ 0x020f2adc, 0x2c bytes, ARM
 * func_020f2a94 @ 0x020f2a94, 0x48 bytes, ARM
 * func_020f2a68 @ 0x020f2a68, 0x2c bytes, ARM
 * func_020f2a44 @ 0x020f2a44, 0x24 bytes, ARM
 * func_020f2a18 @ 0x020f2a18, 0x2c bytes, ARM
 * func_020f29d0 @ 0x020f29d0, 0x48 bytes, ARM
 * func_020f29a4 @ 0x020f29a4, 0x2c bytes, ARM
 * func_020f2980 @ 0x020f2980, 0x24 bytes, ARM
 * func_020f2954 @ 0x020f2954, 0x2c bytes, ARM
 * func_020f290c @ 0x020f290c, 0x48 bytes, ARM
 * func_020f28d8 @ 0x020f28d8, 0x34 bytes, ARM
 * func_020f28b4 @ 0x020f28b4, 0x24 bytes, ARM
 * func_020f2888 @ 0x020f2888, 0x2c bytes, ARM
 * func_020f2840 @ 0x020f2840, 0x48 bytes, ARM
 * func_020f2814 @ 0x020f2814, 0x2c bytes, ARM
 * func_020f27f0 @ 0x020f27f0, 0x24 bytes, ARM
 * func_020f27c4 @ 0x020f27c4, 0x2c bytes, ARM
 * func_020f2784 @ 0x020f2784, 0x40 bytes, ARM
 * func_020f274c @ 0x020f274c, 0x38 bytes, ARM
 * func_020f2720 @ 0x020f2720, 0x2c bytes, ARM
 * func_020f26fc @ 0x020f26fc, 0x24 bytes, ARM
 * func_020f26d0 @ 0x020f26d0, 0x2c bytes, ARM
 * func_020f2690 @ 0x020f2690, 0x40 bytes, ARM
 * func_020f2664 @ 0x020f2664, 0x2c bytes, ARM
 * func_020f2640 @ 0x020f2640, 0x24 bytes, ARM
 * func_020f2614 @ 0x020f2614, 0x2c bytes, ARM
 * func_020f25bc @ 0x020f25bc, 0x58 bytes, ARM
 * func_020f2590 @ 0x020f2590, 0x2c bytes, ARM
 * func_020f256c @ 0x020f256c, 0x24 bytes, ARM
 * func_020f2540 @ 0x020f2540, 0x2c bytes, ARM
 * func_020f2500 @ 0x020f2500, 0x40 bytes, ARM
 */

struct obj_020f2d78 {
    unsigned int unk_00;
    char unk_04;
};

struct UnkStruct_020f2cb4 {
    void *unk_00;
    unsigned char unk_04;
};

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_020f2bf0;

struct UnkStruct_020f2bcc {
    void *v;
};

struct UnkStruct_020f2b2c {
    void *unk_00;
    unsigned char unk_04;
};

struct UnkStruct_020f2adc {
    void *vtbl;
};

struct UnkStruct_020f29a4 {
    unsigned char *data;
    unsigned char flag;
};

typedef struct {
    void *unk_00;
    unsigned char unk_04;
} UnkStruct_020f28d8;

struct UnkStruct_020f2814 {
    void *unk_00;
    unsigned char unk_04;
};

struct UnkStruct_020f27c4 {
    void *unk_00;
};

struct UnkStruct_020f274c {
    char pad_00[0x30];
    int unk_30;
    char pad_34[0x19];
    char unk_4D;
};

struct UnkStruct_020f2720 {
    void *vtable;
    char flag;
};

struct UnkStruct_020f2664 {
    void *unk_00;
    unsigned char unk_04;
};

struct UnkStruct_020f2590 {
    int *unk_00;
    char unk_04;
};

struct obj_020f2540 {
    void *unk_00;
};

extern void *func_020f45c4(void *this);
extern unsigned int data_0213ed10;
extern void *func_020f4514(void *);
extern void func_020edb3c(void *);
extern void func_020f4220(void *receiver, int resource, int count);
extern int func_020f4038(void *receiver);
extern void *func_020eef70(void);
extern int NNS_SndHeapSaveState(void *heap);
extern unsigned char data_021fd1bc[];
extern void func_020f41f4(void *receiver);
extern unsigned int data_0213ed44;
extern unsigned char data_0213ed78[];
extern char data_0213edac;
extern char data_0213ede0;
extern int data_0213ee14;
extern char data_0213ee48;
extern void func_020f5a3c(int);
extern char data_0213ee7c[];
extern void func_020f41a4(void *receiver, int count);
extern void func_020f4080(void *receiver);
extern int func_020f1d84(void *receiver, int sound);
extern void func_020f1004(void *receiver);
extern void func_020f4318(unsigned char *receiver);
extern char data_0213eeb0;
extern void func_020f6700(int);
extern void func_020f43f8(int, int);
extern char data_0213eee4[];
extern void *func_020f3fe0(void *);
extern char data_0213ef18;
extern void *func_020f3f14(void *);
extern int data_0213ef4c;

void *func_020f2e3c(void *this)
{
    func_020f45c4(this);
    *(unsigned int *) this = (unsigned int) &data_0213ed10;
    *((unsigned char *) this + 4) = 42;
    return this;
}

void *func_020f2e18(void *arg)
{
    *(int **) arg = ((int *) &data_0213ed10);
    func_020f4514(arg);
    return arg;
}

void *func_020f2dec(void *self)
{
    *(void **) self = ((char *) &data_0213ed10);
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}

void func_020f2da4(void *receiver)
{
    func_020f4220(receiver, 0x245c0, 20);
    func_020f41f4(receiver);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}

struct obj_020f2d78 *func_020f2d78(struct obj_020f2d78 *obj)
{
    func_020f45c4(obj);
    obj->unk_00 = (unsigned int) &data_0213ed44;
    obj->unk_04 = 0x2b;
    return obj;
}

void *func_020f2d54(void *p)
{
    *(void **) p = ((int *) &data_0213ed44);
    func_020f4514(p);
    return p;
}

void *func_020f2d28(void *obj)
{
    *(void **) obj = ((char *) &data_0213ed44);
    func_020f4514(obj);
    func_020edb3c(obj);
    return obj;
}

void func_020f2ce0(void *receiver)
{
    func_020f4220(receiver, 0x245c0, 21);
    func_020f41f4(receiver);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}

struct UnkStruct_020f2cb4 *func_020f2cb4(struct UnkStruct_020f2cb4 *self)
{
    func_020f45c4(self);
    self->unk_00 = ((int *) data_0213ed78);
    self->unk_04 = 0x2c;
    return self;
}

void *func_020f2c90(void *self)
{
    *(void **) self = (void *) data_0213ed78;
    func_020f4514(self);
    return self;
}

void *func_020f2c64(void *self)
{
    *(unsigned int *) self = (unsigned int) ((unsigned int *) data_0213ed78);
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}

void func_020f2c1c(void *receiver)
{
    func_020f4220(receiver, 0x245c0, 22);
    func_020f41f4(receiver);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}

UnkStruct_020f2bf0 *func_020f2bf0(UnkStruct_020f2bf0 *p)
{
    func_020f45c4(p);
    p->ptr = ((int *) &data_0213edac);
    p->byte = 0x2d;
    return p;
}

void *func_020f2bcc(void *p)
{
    ((struct UnkStruct_020f2bcc *) p)->v = &data_0213edac;
    func_020f4514(p);
    return p;
}

void *func_020f2ba0(void *this)
{
    *(void **) this = (void *) &data_0213edac;
    func_020f4514(this);
    func_020edb3c(this);
    return this;
}

void func_020f2b58(void *receiver)
{
    func_020f4220(receiver, 0x245c0, 23);
    func_020f41f4(receiver);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}

void *func_020f2b2c(struct UnkStruct_020f2b2c *obj)
{
    func_020f45c4(obj);
    obj->unk_00 = &data_0213ede0;
    obj->unk_04 = 0x2e;
    return obj;
}

void *func_020f2b08(void *p)
{
    *(void **) p = &data_0213ede0;
    func_020f4514(p);
    return p;
}

struct UnkStruct_020f2adc *func_020f2adc(struct UnkStruct_020f2adc *self)
{
    self->vtbl = &data_0213ede0;
    func_020f4514((void *) self);
    func_020edb3c((void *) self);
    return self;
}

void func_020f2a94(void *receiver)
{
    func_020f4220(receiver, 0x245c0, 24);
    func_020f41f4(receiver);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}

void *func_020f2a68(void *p)
{
    func_020f45c4(p);
    *(unsigned int *) p = (unsigned int) ((unsigned char *) &data_0213ee14);
    *((unsigned char *) p + 4) = 0x2f;
    return p;
}

void *func_020f2a44(void *p)
{
    *(void **) p = (void *) &data_0213ee14;
    func_020f4514(p);
    return p;
}

void *func_020f2a18(void *obj)
{
    *(void **) obj = &data_0213ee14;
    func_020f4514(obj);
    func_020edb3c(obj);
    return obj;
}

void func_020f29d0(void *receiver)
{
    func_020f4220(receiver, 0x245c0, 25);
    func_020f41f4(receiver);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}

struct UnkStruct_020f29a4 *func_020f29a4(struct UnkStruct_020f29a4 *self)
{
    func_020f45c4(self);
    self->data = ((unsigned char *) &data_0213ee48);
    self->flag = 0x30;
    return self;
}

void *func_020f2980(void *obj)
{
    void *self = obj;
    void *vt = (void *) &data_0213ee48;

    *(void **) self = vt;
    func_020f4514(self);
    return self;
}

void *func_020f2954(void *self)
{
    *(char **) self = &data_0213ee48;
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}

void func_020f290c(void *receiver)
{
    func_020f4220(receiver, 0x245c0, 26);
    func_020f41f4(receiver);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}

UnkStruct_020f28d8 *func_020f28d8(UnkStruct_020f28d8 *p)
{
    func_020f45c4(p);
    p->unk_00 = ((char *) data_0213ee7c);
    p->unk_04 = 0x32;
    func_020f5a3c(1);
    return p;
}

void *func_020f28b4(void *obj)
{
    *(void **) obj = data_0213ee7c;
    func_020f4514(obj);
    return obj;
}

void *func_020f2888(void *p)
{
    *(unsigned int *) p = (unsigned int) ((unsigned char *) data_0213ee7c);
    func_020f4514(p);
    func_020edb3c(p);
    return p;
}

void func_020f2840(void *receiver)
{
    func_020f4220(receiver, 0, 27);
    func_020f41a4(receiver, 3);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}

void *func_020f2814(struct UnkStruct_020f2814 *p)
{
    func_020f45c4(p);
    p->unk_00 = &data_0213eeb0;
    p->unk_04 = 0x33;
    return p;
}

void *func_020f27f0(void *p)
{
    *(int **) p = ((int *) &data_0213eeb0);
    func_020f4514(p);
    return p;
}

void *func_020f27c4(struct UnkStruct_020f27c4 *self)
{
    self->unk_00 = &data_0213eeb0;
    func_020f4514((void *) self);
    func_020edb3c((void *) self);
    return self;
}

void func_020f2784(void *receiver)
{
    func_020f4220(receiver, 0, 28);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
    func_020f1004(data_021fd1bc);
}

void func_020f274c(int arg)
{
    func_020f6700((*(struct UnkStruct_020f274c *) data_021fd1bc).unk_30);
    (*(struct UnkStruct_020f274c *) data_021fd1bc).unk_4D = 1;
    func_020f43f8(arg, 0x11);
}

struct UnkStruct_020f2720 *func_020f2720(struct UnkStruct_020f2720 *this)
{
    func_020f45c4(this);
    this->vtable = data_0213eee4;
    this->flag = 0x34;
    return this;
}

void *func_020f26fc(void *obj)
{
    *(void **) obj = ((int *) data_0213eee4);
    func_020f4514(obj);
    return obj;
}

void *func_020f26d0(void *arg)
{
    *((int *) arg) = (unsigned int) ((unsigned char *) data_0213eee4);
    func_020f4514(arg);
    func_020edb3c(arg);
    return arg;
}

void func_020f2690(void *receiver)
{
    func_020f4220(receiver, 0x2a824, 29);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}

void *func_020f2664(struct UnkStruct_020f2664 *self)
{
    func_020f3fe0(self);
    self->unk_00 = ((int *) &data_0213ef18);
    self->unk_04 = 0x3c;
    return self;
}

void *func_020f2640(void *self)
{
    *(void **) self = &data_0213ef18;
    func_020f3f14(self);
    return self;
}

void *func_020f2614(void *self)
{
    *(void **) self = &data_0213ef18;
    func_020f3f14(self);
    func_020edb3c(self);
    return self;
}

void func_020f25bc(void *receiver)
{
    func_020f4220(receiver, 0x21ef8, 4);
    func_020f41a4(receiver, 2);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    func_020f1d84(data_021fd1bc, 0x8f);
    data_021fd1bc[0x62] = 0;
}

struct UnkStruct_020f2590 *func_020f2590(struct UnkStruct_020f2590 *this)
{
    func_020f45c4(this);
    this->unk_00 = &data_0213ef4c;
    this->unk_04 = 0x63;
    return this;
}

void *func_020f256c(void *p)
{
    *(void **) p = ((char *) &data_0213ef4c);
    func_020f4514(p);
    return p;
}

struct obj_020f2540 *func_020f2540(struct obj_020f2540 *self)
{
    self->unk_00 = &data_0213ef4c;
    func_020f4514((void *) self);
    func_020edb3c((void *) self);
    return self;
}

void func_020f2500(void *receiver)
{
    func_020f4220(receiver, 0x2a824, 29);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    data_021fd1bc[0x62] = 0;
}
