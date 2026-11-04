/* sound_scene_4: 14 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f4178 @ 0x020f4178, 0x2c bytes, ARM
 * func_020f4130 @ 0x020f4130, 0x48 bytes, ARM
 * func_020f40e8 @ 0x020f40e8, 0x48 bytes, ARM
 * func_020f40ac @ 0x020f40ac, 0x3c bytes, ARM
 * func_020f4080 @ 0x020f4080, 0x2c bytes, ARM
 * func_020f4038 @ 0x020f4038, 0x48 bytes, ARM
 * func_020f3fe0 @ 0x020f3fe0, 0x58 bytes, ARM
 * func_020f3f88 @ 0x020f3f88, 0x58 bytes, ARM
 * func_020f3f64 @ 0x020f3f64, 0x24 bytes, ARM
 * func_020f3f38 @ 0x020f3f38, 0x2c bytes, ARM
 * func_020f3f14 @ 0x020f3f14, 0x24 bytes, ARM
 * func_020f3eb4 @ 0x020f3eb4, 0x60 bytes, ARM
 * func_020f3e84 @ 0x020f3e84, 0x30 bytes, ARM
 * func_020f3e5c @ 0x020f3e5c, 0x28 bytes, ARM
 */

struct UnkStruct_020f3fe0 {
    void *data;
    char flag;
};

struct Global {
    char pad_00[0x30];
    int unk_30;
    char pad_34[0x3f];
    unsigned char unk_73;
};

struct UnkStruct_020f3f88 {
    void *vtable;
    unsigned char flag;
};

extern int func_020eef70(void);
extern int NNS_SndPlayerCreateHeap(int, int, int);
extern void *func_020f45c4(struct UnkStruct_020f3fe0 *self);
extern void func_020f65bc(int code, int line);
extern void func_020f5a3c(char value);
extern char data_021fd1bc[];
extern void *func_020f4514(void *this);
extern void func_020edb3c(void *obj);
extern unsigned char data_0213ef80[];
extern void func_020f4220(void *receiver, int resource, int count);
extern void func_020f41a4(void *receiver, int count);
extern int NNS_SndHeapSaveState(void *heap);
extern int func_020f1d84(void *receiver, int sound);
extern void func_020f1004(void *receiver);
extern void func_020f4318(unsigned char *receiver);
extern int func_020eec48(void);
extern void func_020eec60(int argument0);
extern int func_020f4338(int a, int b);

void func_020f4178(void *receiver)
{
    int r0;
    r0 = func_020eef70();
    NNS_SndPlayerCreateHeap(5, r0, 0x31ac);
}

void func_020f4130(void *receiver)
{
    int x = func_020eef70();
    int i;
    for (i = 0; i < 2; i++) {
        NNS_SndPlayerCreateHeap(6, x, 0x7a4c);
    }
}

void func_020f40e8(void *receiver)
{
    int result = func_020eef70();
    int i;
    for (i = 0; i < 4; i++) {
        NNS_SndPlayerCreateHeap(0x11, result, 0x356c);
    }
}

void func_020f40ac(void *receiver)
{
    int x = func_020eef70();
    NNS_SndPlayerCreateHeap(18, x, 0x5ecc);
    NNS_SndPlayerCreateHeap(19, x, 0x46bc);
}

void func_020f4080(void *receiver)
{
    int x;
    x = func_020eef70();
    NNS_SndPlayerCreateHeap(0xd, x, 0x1f4c);
}

int func_020f4038(void *receiver)
{
    int x;
    int i;
    int result;
    x = func_020eef70();
    for (i = 0; i < 2; i++) {
        result = NNS_SndPlayerCreateHeap(0xc, x, 0x8cc);
    }
    return result;
}

struct UnkStruct_020f3fe0 *func_020f3fe0(struct UnkStruct_020f3fe0 *self)
{
    int x;

    func_020f45c4(self);
    self->data = ((char *) data_0213ef80);
    x = *(int *) (data_021fd1bc + 0x30);
    if (x != 0) {
        func_020f65bc(x, 0xD1);
    }
    self->flag = 1;
    func_020f5a3c(1);
    data_021fd1bc[0x73] = 0;
    return self;
}

struct UnkStruct_020f3f88 *func_020f3f88(struct UnkStruct_020f3f88 *obj)
{
    func_020f45c4((struct UnkStruct_020f3fe0 *) obj);
    obj->vtable = ((int *) data_0213ef80);
    if ((*(struct Global *) data_021fd1bc).unk_30 != 0) {
        func_020f65bc((*(struct Global *) data_021fd1bc).unk_30, 0xd1);
    }
    obj->flag = 1;
    func_020f5a3c(1);
    (*(struct Global *) data_021fd1bc).unk_73 = 0;
    return obj;
}

void *func_020f3f64(void *this)
{
    *(void **) this = (void *) ((char *) data_0213ef80);
    func_020f4514(this);
    return this;
}

void *func_020f3f38(void *obj)
{
    *(void **) obj = (void *) ((int *) data_0213ef80);
    func_020f4514(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_020f3f14(void *p)
{
    *((unsigned int *) p) = (unsigned int) data_0213ef80;
    func_020f4514(p);
    return p;
}

void func_020f3eb4(void *receiver)
{
    func_020f4220(receiver, 0x21ef8, 1);
    func_020f41a4(receiver, 3);
    func_020f4080(receiver);
    func_020f4038(receiver);
    NNS_SndHeapSaveState((void *) func_020eef70());
    func_020f1d84(((unsigned char *) data_021fd1bc), 0x8f);
    ((unsigned char *) data_021fd1bc)[0x62] = 0;
}

int func_020f3e84(int a, int b)
{
    int tmp;
    tmp = a;

    func_020eec60(func_020eec48());
    return func_020f4338(tmp, b);
}

void func_020f3e5c(void *argument0)
{
    unsigned int *p;

    func_020f4318((unsigned char *) argument0);
    p = (unsigned int *) ((unsigned char *) data_021fd1bc);
    func_020f1d84((void *) ((unsigned int) p), 0x8f);
}
