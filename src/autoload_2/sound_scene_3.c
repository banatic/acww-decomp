/* sound_scene_3: 12 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f3dc4 @ 0x020f3dc4, 0x48 bytes, ARM
 * func_020f3da0 @ 0x020f3da0, 0x24 bytes, ARM
 * func_020f3d74 @ 0x020f3d74, 0x2c bytes, ARM
 * func_020f3d1c @ 0x020f3d1c, 0x58 bytes, ARM
 * func_020f3cd4 @ 0x020f3cd4, 0x48 bytes, ARM
 * func_020f3cb0 @ 0x020f3cb0, 0x24 bytes, ARM
 * func_020f3c84 @ 0x020f3c84, 0x2c bytes, ARM
 * func_020f3c24 @ 0x020f3c24, 0x60 bytes, ARM
 * func_020f3be8 @ 0x020f3be8, 0x3c bytes, ARM
 * func_020f3bb8 @ 0x020f3bb8, 0x30 bytes, ARM
 * func_020f3b80 @ 0x020f3b80, 0x38 bytes, ARM
 * func_020f3ab4 @ 0x020f3ab4, 0xcc bytes, ARM
 */

typedef struct UnkStruct_020f3dc4 {
    unsigned char pad_00[0x30];
    unsigned int unk_30;
} UnkStruct_020f3dc4;

typedef struct UnkStruct_020f3dc4_2 {
    void *vtable;
    unsigned char unk_04;
} UnkStruct_020f3dc4_2;

typedef struct {
    void *unk_00;
} Unk_020f3da0;

struct UnkStruct_020f3cd4 {
    const char *vtbl;
    unsigned char flag;
};

struct UnkStruct_020f3cd4_2 {
    char pad_00[0x30];
    int flag;
};

struct UnkStruct_020f3c84 {
    int *data;
};

typedef struct UnkStruct_020f3be8 {
    void *unk_00;
    unsigned char unk_04;
    unsigned char pad_05[3];
    char unk_08[20];
    unsigned char unk_1C;
} UnkStruct_020f3be8;

typedef struct UnkStruct_020f3bb8 {
    void *vtbl;
    int unk_04;
    char subobj;
} UnkStruct_020f3bb8;

typedef struct {
    unsigned char pad_00[8];
    unsigned char sub[0x14];
    unsigned char flag;
    unsigned char level;
} SObj;

extern void *func_020f3fe0(void *self);
extern void func_020f65bc(int cond, int code);
extern char data_0213e99c;
extern void *func_020f3f14(void *self);
extern void func_020edb3c(void *);
extern void func_020f4220(void *receiver, int resource, int count);
extern void func_020f41a4(void *receiver, int count);
extern void func_020f4080(void *receiver);
extern int func_020f4038(void *receiver);
extern void *func_020eef70(void);
extern int NNS_SndHeapSaveState(void *heap);
extern int func_020f1d84(void *receiver, int sound);
extern void func_020f1004(void *receiver);
extern void func_020f4318(unsigned char *receiver);
extern unsigned char data_021fd1bc[];
extern const char data_0213ec40[];
extern void *func_020f45c4(void *self);
extern void *func_020f9888(void *ptr);
extern unsigned int *func_020f9868(char *);
extern void *func_020f4514(void *);
extern int data_0213ea04;
extern void func_020f41f4(void *self);
extern void func_020f4178(void *self);
extern void func_020f4130(void *self);
extern void func_020f40e8(void *self);
extern void func_020f40ac(void *self);
extern int func_0210e160(int a, void *b);
extern int NNS_SndHeapGetCurrentLevel(void *heap);
extern void func_020f97dc(void *p, int q);
extern void NNS_SndPlayerSetPlayerVolume(int player, int volume);

void *func_020f3dc4(void *self)
{
    UnkStruct_020f3dc4_2 *s = (UnkStruct_020f3dc4_2 *) self;
    func_020f3fe0(self);
    s->vtable = &data_0213e99c;
    if ((*(UnkStruct_020f3dc4 *) data_021fd1bc).unk_30 != 0) {
        func_020f65bc((*(UnkStruct_020f3dc4 *) data_021fd1bc).unk_30, 0xd1);
    }
    s->unk_04 = 2;
    return self;
}

void *func_020f3da0(Unk_020f3da0 *self)
{
    self->unk_00 = &data_0213e99c;
    func_020f3f14(self);
    return self;
}

void *func_020f3d74(void *obj)
{
    *(void **) obj = (void *) ((int *) &data_0213e99c);
    func_020f3f14(obj);
    func_020edb3c(obj);
    return obj;
}

void func_020f3d1c(void *receiver)
{
    func_020f4220(receiver, 0x1f340, 2);
    func_020f41a4(receiver, 2);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    func_020f1d84(data_021fd1bc, 0x8f);
    data_021fd1bc[0x62] = 0;
}

struct UnkStruct_020f3cd4 *func_020f3cd4(struct UnkStruct_020f3cd4 *this)
{
    int flag;

    func_020f3fe0(this);
    this->vtbl = data_0213ec40;
    flag = (*(const struct UnkStruct_020f3cd4_2 *) data_021fd1bc).flag;
    if (flag != 0) {
        func_020f65bc(flag, 0xd1);
    }
    this->flag = 3;
    return this;
}

void *func_020f3cb0(void *arg)
{
    *(void **) arg = ((char *) data_0213ec40);
    func_020f3f14(arg);
    return arg;
}

struct UnkStruct_020f3c84 *func_020f3c84(struct UnkStruct_020f3c84 *obj)
{
    obj->data = ((int *) data_0213ec40);
    func_020f3f14(obj);
    func_020edb3c(obj);
    return obj;
}

void func_020f3c24(void *receiver)
{
    func_020f4220(receiver, 0x21ef8, 3);
    func_020f41a4(receiver, 2);
    func_020f4080(receiver);
    func_020f4038(receiver);
    NNS_SndHeapSaveState(func_020eef70());
    func_020f1d84(data_021fd1bc, 0x8f);
    data_021fd1bc[0x62] = 0;
}

UnkStruct_020f3be8 *func_020f3be8(UnkStruct_020f3be8 *self)
{
    func_020f45c4(self);
    self->unk_00 = ((char *) &data_0213ea04);
    func_020f9888(self->unk_08);
    self->unk_04 = 10;
    self->unk_1C = 0;
    return self;
}

void *func_020f3bb8(UnkStruct_020f3bb8 *self)
{
    self->vtbl = (void *) &data_0213ea04;
    func_020f9868(&self->subobj);
    func_020f4514(self);
    return self;
}

void *func_020f3b80(void *self)
{
    *(void **) self = (void *) &data_0213ea04;
    func_020f9868((char *) ((char *) self + 8));
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}

void func_020f3ab4(SObj *self)
{
    void *heap;

    func_020f4220(self, 0x10ea0, 5);
    func_020f41f4(self);
    func_020f4178(self);
    func_020f4130(self);
    func_020f40e8(self);
    func_020f40ac(self);

    heap = func_020eef70();

    func_0210e160(9, heap);
    NNS_SndHeapSaveState(heap);
    self->level = NNS_SndHeapGetCurrentLevel(heap);

    func_020f1d84(data_021fd1bc, 0x90);
    func_020f4038(self);
    NNS_SndHeapSaveState(heap);
    self->flag = 1;

    data_021fd1bc[0x62] = 0;
    func_020f97dc(self->sub, 1);

    NNS_SndPlayerSetPlayerVolume(0x12, 0x3f);
    NNS_SndPlayerSetPlayerVolume(0x13, 0x3f);
}
