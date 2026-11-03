/* message_texts: 22 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b5630 @ 0x020b5630, 0x20 bytes, Thumb
 * func_020b5618 @ 0x020b5618, 0x18 bytes, Thumb
 * func_020b55f8 @ 0x020b55f8, 0x20 bytes, Thumb
 * func_020b55f4 @ 0x020b55f4, 0x4 bytes, Thumb
 * func_020b55f0 @ 0x020b55f0, 0x4 bytes, Thumb
 * func_020b55d0 @ 0x020b55d0, 0x20 bytes, Thumb
 * func_020b55b8 @ 0x020b55b8, 0x18 bytes, Thumb
 * func_020b5598 @ 0x020b5598, 0x20 bytes, Thumb
 * func_020b5590 @ 0x020b5590, 0x8 bytes, Thumb
 * func_020b558c @ 0x020b558c, 0x4 bytes, Thumb
 * func_020b5548 @ 0x020b5548, 0x44 bytes, Thumb
 * func_020b5524 @ 0x020b5524, 0x24 bytes, Thumb
 * func_020b550c @ 0x020b550c, 0x18 bytes, Thumb
 * func_020b54ec @ 0x020b54ec, 0x20 bytes, Thumb
 * func_020b54e8 @ 0x020b54e8, 0x4 bytes, Thumb
 * func_020b54e4 @ 0x020b54e4, 0x4 bytes, Thumb
 * func_020b54c8 @ 0x020b54c8, 0x1c bytes, Thumb
 * func_020b54b0 @ 0x020b54b0, 0x18 bytes, Thumb
 * func_020b5490 @ 0x020b5490, 0x20 bytes, Thumb
 * func_020b547c @ 0x020b547c, 0x14 bytes, Thumb
 * func_020b5478 @ 0x020b5478, 0x4 bytes, Thumb
 * func_020b5470 @ 0x020b5470, 0x8 bytes, Thumb
 */

struct obj {
    void *unk_00;
};

struct UnkStruct_020b55b8 {
    void *ptr;
};

struct UnkStruct_020b5598 {
    void *vtable;
};

typedef struct {
    void *vtable;
} Object;

extern void *func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern int data_020e5218;
extern void *func_020a8c38(void *);
extern void func_020edb3c(void *);
extern char data_020e51d0[];
extern unsigned int data_021f4c7c;
extern unsigned char data_021f4c98;
extern unsigned char data_021f4c8c;
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_020e51b8[];
extern void *func_020a9a90(void *p, int arg);
extern char data_020e51e8;
extern void *func_020a9a40(Object *self);
extern void MI_CpuFill8(void *param1, int param2, int param3);

struct obj *func_020b5630(struct obj *self)
{
    func_020a8cac(self);
    self->unk_00 = &data_020e5218;
    func_020a8c1c(self);
    return self;
}

void *func_020b5618(void *param)
{
    *(void **) param = ((char *) &data_020e5218);
    func_020a8c38(param);
    return param;
}

void *func_020b55f8(void *param)
{
    ((unsigned int *) param)[0] = (unsigned int) ((unsigned int *) &data_020e5218);
    func_020a8c38(param);
    func_020edb3c(param);
    return param;
}

int func_020b55f4(void)
{
    return 46;
}

int func_020b55f0(int p0)
{
    return ((int) (p0) + (18));
}

void *func_020b55d0(void *arg)
{
    func_020a8cac(arg);
    *(void **) arg = (void *) data_020e51d0;
    func_020a8c1c(arg);
    return arg;
}

struct UnkStruct_020b55b8 *func_020b55b8(struct UnkStruct_020b55b8 *obj)
{
    obj->ptr = (void *) ((unsigned char *) data_020e51d0);
    func_020a8c38(obj);
    return obj;
}

struct UnkStruct_020b5598 *func_020b5598(struct UnkStruct_020b5598 *self)
{
    self->vtable = ((char *) data_020e51d0);
    func_020a8c38((void *) self);
    func_020edb3c((void *) self);
    return self;
}

int func_020b5590(void)
{
    return 256;
}

int func_020b558c(int p0)
{
    return ((int) (p0) + (18));
}

void *func_020b5548(void)
{
    if ((data_021f4c7c & 1) == 0) {
        func_020b55d0(&data_021f4c98);
        __register_global_object((void *) (&data_021f4c98), (((void *) (void * (*)(void *)) func_020b55b8)), (void *) (&data_021f4c8c));
        data_021f4c7c |= 1;
    }
    return &data_021f4c98;
}

void *func_020b5524(void *obj)
{
    func_020a8cac(obj);
    *(void **) obj = (void *) ((int *) data_020e51b8);
    ((char *) obj)[0x1c] = 0;
    func_020a8c1c(obj);
    return obj;
}

void *func_020b550c(void *self)
{
    *(void **) self = data_020e51b8;
    func_020a8c38(self);
    return self;
}

void *func_020b54ec(void *obj)
{
    *(void **) obj = (void *) data_020e51b8;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}

int func_020b54e8(void)
{
    return 10;
}

int func_020b54e4(int p0)
{
    return ((int) (p0) + (18));
}

void *func_020b54c8(void *param)
{
    func_020a9a90(param, 0);
    *(void **) param = ((int *) &data_020e51e8);
    return param;
}

Object *func_020b54b0(Object *self)
{
    self->vtable = &data_020e51e8;
    func_020a9a40(self);
    return self;
}

void *func_020b5490(void *self)
{
    ((void **) self)[0] = (void *) &data_020e51e8;
    func_020a9a40((Object *) self);
    func_020edb3c(self);
    return self;
}

void func_020b547c(void *param1)
{
    MI_CpuFill8((char *) param1 + 0xa4, 0, 0x00000a00);
}

int func_020b5478(int p0)
{
    return ((int) (p0) + (164));
}

int func_020b5470(void)
{
    return 2560;
}
