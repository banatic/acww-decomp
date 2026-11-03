/* fox_shop_3: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ae774 @ 0x020ae774, 0x20 bytes, Thumb
 * func_020ae75c @ 0x020ae75c, 0x18 bytes, Thumb
 * func_020ae73c @ 0x020ae73c, 0x20 bytes, Thumb
 * func_020ae738 @ 0x020ae738, 0x4 bytes, Thumb
 * func_020ae734 @ 0x020ae734, 0x4 bytes, Thumb
 * func_020ae724 @ 0x020ae724, 0x10 bytes, Thumb
 * func_020ae720 @ 0x020ae720, 0x2 bytes, Thumb
 * func_020ae6fc @ 0x020ae6fc, 0x24 bytes, Thumb
 */

struct UnkStruct_020ae75c {
    void *unk_00;
};

struct UnkStruct_020ae73c {
    void *unk_00;
};

struct UnkStruct_020ae6fc {
    int a;
    signed char b;
};

extern void *func_020a8cac(void *ptr);
extern void func_020a8c1c(void *ptr);
extern void *func_020a8c38(void *);
extern unsigned char data_020e4170[];
extern void func_020edb3c(void *);
extern void func_020ae564(struct UnkStruct_020ae6fc *);
extern void func_0209f100(void *, int);
extern unsigned char data_021dc7a8[];

void func_020ae6fc(struct UnkStruct_020ae6fc *p);

void *func_020ae774(void *arg)
{
    func_020a8cac(arg);
    *(void **) arg = ((char *) data_020e4170);
    func_020a8c1c(arg);
    return arg;
}

struct UnkStruct_020ae75c *func_020ae75c(struct UnkStruct_020ae75c *self)
{
    self->unk_00 = (void *) ((int *) data_020e4170);
    func_020a8c38(self);
    return self;
}

struct UnkStruct_020ae73c *func_020ae73c(struct UnkStruct_020ae73c *obj)
{
    obj->unk_00 = (void *) data_020e4170;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}

int func_020ae738(int p0)
{
    return ((int) (p0) + (18));
}

int func_020ae734(void)
{
    return 34;
}

int func_020ae724(int arg)
{
    func_020ae6fc((struct UnkStruct_020ae6fc *) arg);
    return arg;
}

void func_020ae720(void *object) {}

void func_020ae6fc(struct UnkStruct_020ae6fc *p)
{
    p->a = 0;
    p->b = -1;
    func_020ae564(p);
    func_0209f100(data_021dc7a8, 8);
}
