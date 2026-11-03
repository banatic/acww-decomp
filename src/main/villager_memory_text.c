/* villager_memory_text: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082048 @ 0x02082048, 0x18 bytes, Thumb
 * func_02082030 @ 0x02082030, 0x18 bytes, Thumb
 * func_02082010 @ 0x02082010, 0x20 bytes, Thumb
 * func_0208200c @ 0x0208200c, 0x4 bytes, Thumb
 * func_02082008 @ 0x02082008, 0x4 bytes, Thumb
 * func_02081ff0 @ 0x02081ff0, 0x18 bytes, Thumb
 * func_02081fd8 @ 0x02081fd8, 0x18 bytes, Thumb
 * func_02081fb8 @ 0x02081fb8, 0x20 bytes, Thumb
 * func_02081fb4 @ 0x02081fb4, 0x4 bytes, Thumb
 * func_02081fb0 @ 0x02081fb0, 0x4 bytes, Thumb
 */

struct UnkStruct_02081fb8 {
    void *vtable;
};

extern void *func_020a8cac(void *self);
extern void *func_020a8c38(void *);
extern char data_020e191c[];
extern void func_020edb3c(void *obj);
extern void *func_020a88ec(void *self);
extern char data_020e18ec;
extern void *func_020a887c(void *ptr);

void *func_02082048(void *self)
{
    func_020a8cac(self);
    *(char **) self = ((char *) data_020e191c);
    return self;
}

void *func_02082030(void *arg)
{
    *(void **) arg = (void *) ((char *) data_020e191c);
    func_020a8c38(arg);
    return arg;
}

void *func_02082010(void *obj)
{
    *(void **) obj = (void *) data_020e191c;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}

int func_0208200c(void)
{
    return 22;
}

int func_02082008(int p0)
{
    return ((int) (p0) + (18));
}

void *func_02081ff0(void *self)
{
    func_020a88ec(self);
    *(void **) self = &data_020e18ec;
    return self;
}

void *func_02081fd8(void *arg0)
{
    *(char **) arg0 = &data_020e18ec;
    func_020a887c(arg0);
    return arg0;
}

struct UnkStruct_02081fb8 *func_02081fb8(struct UnkStruct_02081fb8 *self)
{
    self->vtable = &data_020e18ec;
    func_020a887c((void *) self);
    func_020edb3c((void *) self);
    return self;
}

int func_02081fb4(void)
{
    return 10;
}

int func_02081fb0(int p0)
{
    return ((int) (p0) + (14));
}
