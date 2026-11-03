/* mail_part_texts: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206daf8 @ 0x0206daf8, 0x20 bytes, Thumb
 * func_0206dae0 @ 0x0206dae0, 0x18 bytes, Thumb
 * func_0206dac0 @ 0x0206dac0, 0x20 bytes, Thumb
 * func_0206dabc @ 0x0206dabc, 0x4 bytes, Thumb
 * func_0206dab8 @ 0x0206dab8, 0x4 bytes, Thumb
 * func_0206da98 @ 0x0206da98, 0x20 bytes, Thumb
 * func_0206da80 @ 0x0206da80, 0x18 bytes, Thumb
 * func_0206da60 @ 0x0206da60, 0x20 bytes, Thumb
 * func_0206da5c @ 0x0206da5c, 0x4 bytes, Thumb
 * func_0206da58 @ 0x0206da58, 0x4 bytes, Thumb
 * func_0206da38 @ 0x0206da38, 0x20 bytes, Thumb
 * func_0206da20 @ 0x0206da20, 0x18 bytes, Thumb
 * func_0206da00 @ 0x0206da00, 0x20 bytes, Thumb
 * func_0206d9fc @ 0x0206d9fc, 0x4 bytes, Thumb
 * func_0206d9f8 @ 0x0206d9f8, 0x4 bytes, Thumb
 */

typedef struct UnkStruct_0206da98 UnkStruct_0206da98;

struct UnkStruct_0206da98 {
    void *unk_00;
};

struct UnkStruct_0206da80 {
    char *unk_00;
};

struct UnkStruct_0206da00 {
    int *unk_00;
};

extern void *func_020a8cac(void *self);
extern void func_020a8c1c(void *self);
extern void *func_020a8c38(void *this);
extern unsigned char data_020df240[];
extern void func_020edb3c(void *self);
extern char data_020df210[];
extern int data_020df228;

void *func_0206daf8(void *self)
{
    func_020a8cac(self);
    *(unsigned int *) self = (unsigned int) ((unsigned int *) data_020df240);
    func_020a8c1c(self);
    return self;
}

void *func_0206dae0(void *this)
{
    *(void **) this = (void *) data_020df240;
    func_020a8c38(this);
    return this;
}

void *func_0206dac0(void *self)
{
    void *vtable = (void *) data_020df240;
    *((void **) self) = vtable;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}

int func_0206dabc(void)
{
    return 22;
}

int func_0206dab8(int p0)
{
    return ((int) (p0) + (18));
}

UnkStruct_0206da98 *func_0206da98(UnkStruct_0206da98 *obj)
{
    func_020a8cac((void *) obj);
    obj->unk_00 = ((char *) data_020df210);
    func_020a8c1c((void *) obj);
    return obj;
}

struct UnkStruct_0206da80 *func_0206da80(struct UnkStruct_0206da80 *obj)
{
    obj->unk_00 = data_020df210;
    func_020a8c38((void *) obj);
    return obj;
}

void *func_0206da60(void *obj)
{
    *(void **) obj = ((int *) data_020df210);
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}

int func_0206da5c(void)
{
    return 130;
}

int func_0206da58(int p0)
{
    return ((int) (p0) + (18));
}

void *func_0206da38(void *arg)
{
    func_020a8cac(arg);
    *(void **) arg = (void *) &data_020df228;
    func_020a8c1c(arg);
    return arg;
}

void *func_0206da20(void *arg)
{
    *((int *) arg) = (int) &data_020df228;
    func_020a8c38(arg);
    return arg;
}

void *func_0206da00(struct UnkStruct_0206da00 *self)
{
    self->unk_00 = &data_020df228;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}

int func_0206d9fc(void)
{
    return 34;
}

int func_0206d9f8(int p0)
{
    return ((int) (p0) + (18));
}
