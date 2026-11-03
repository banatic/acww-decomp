/* message_window_2: 4 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220b10c @ 0x0220b10c, 0x20 bytes, Thumb
 * func_ov002_0220b0f4 @ 0x0220b0f4, 0x18 bytes, Thumb
 * func_ov002_0220b0d4 @ 0x0220b0d4, 0x20 bytes, Thumb
 * func_ov002_0220b0c8 @ 0x0220b0c8, 0xc bytes, Thumb
 */

struct _Obj {
    void *vtbl;
};

extern void func_0208aa88(void *);
extern void *func_0208ade8(void *, int);
extern void *data_ov002_0220bdac;
extern void *func_0208ad24(void *);
extern void func_020edb3c(void *);
extern void func_0208aef4(void *p, int x, int y);

void *func_ov002_0220b10c(char *self)
{
    // DECLS
    // ENDDECLS
    func_0208ade8(self, 0x0);
    *(void **) (self) = &data_ov002_0220bdac;
    func_0208aa88(self);
    return self;
}

void *func_ov002_0220b0f4(void *arg)
{
    *((void **) arg) = ((int *) &data_ov002_0220bdac);
    func_0208ad24(arg);
    return arg;
}

void *func_ov002_0220b0d4(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov002_0220bdac);
    func_0208ad24(obj);
    func_020edb3c(obj);
    return obj;
}

void func_ov002_0220b0c8(void *p, int x, int y)
{
    func_0208aef4(p, x - 0x80, y - 0x60);
}
