/* catch_panel_7: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208e024 @ 0x0208e024, 0x20 bytes, Thumb
 * func_0208e00c @ 0x0208e00c, 0x18 bytes, Thumb
 * func_0208dfec @ 0x0208dfec, 0x20 bytes, Thumb
 * func_0208dfe8 @ 0x0208dfe8, 0x4 bytes, Thumb
 * func_0208dfe4 @ 0x0208dfe4, 0x4 bytes, Thumb
 */

typedef struct {
    void *vtable;
} UnkStruct_0208e024;

struct UnkStruct_0208e00c {
    void *vtable;
};

extern void *func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern void *func_020a8c38(void *self);
extern int data_020e21e4;
extern void func_020edb3c(void *);

void *func_0208e024(UnkStruct_0208e024 *obj)
{
    func_020a8cac(obj);
    obj->vtable = ((char *) &data_020e21e4);
    func_020a8c1c(obj);
    return obj;
}

void *func_0208e00c(struct UnkStruct_0208e00c *self)
{
    self->vtable = &data_020e21e4;
    func_020a8c38(self);
    return self;
}

void *func_0208dfec(void *arg)
{
    *(void **) arg = &data_020e21e4;
    func_020a8c38(arg);
    func_020edb3c(arg);
    return arg;
}

int func_0208dfe8(void *object)
{
    (void) object;
    return 10;
}

int func_0208dfe4(int p0)
{
    return ((int) (p0) + (18));
}
