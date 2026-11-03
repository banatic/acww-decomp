/* label_button_3: 7 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220b698 @ 0x0220b698, 0x18 bytes, Thumb
 * func_ov002_0220b680 @ 0x0220b680, 0x18 bytes, Thumb
 * func_ov002_0220b660 @ 0x0220b660, 0x20 bytes, Thumb
 * func_ov002_0220b648 @ 0x0220b648, 0x18 bytes, Thumb
 * func_ov002_0220b63c @ 0x0220b63c, 0xc bytes, Thumb
 * func_ov002_0220b5ec @ 0x0220b5ec, 0x50 bytes, Thumb
 * func_ov002_0220b59c @ 0x0220b59c, 0x50 bytes, Thumb
 */

struct _Obj {
    void *vtbl;
};

extern void *func_0208f58c(void *arg, char parameter1, int parameter2);
extern int data_ov002_0220bd90;
extern void *func_0208f46c(void *);
extern void func_020edb3c(void *);
extern void func_0208aef4(void *p, int x, int y);
extern int func_0208aef0(void *self);
extern int func_0208f0c0(void *self);
extern void func_0208f184(void *self, int *a, int *b);
extern int func_0208aeec(void *self);

void *func_ov002_0220b698(void *arg, char arg1, int arg2)
{
    func_0208f58c(arg, arg1, arg2);
    *(void **) arg = &data_ov002_0220bd90;
    return arg;
}

void *func_ov002_0220b680(void *arg)
{
    *((void **) arg) = &data_ov002_0220bd90;
    func_0208f46c(arg);
    return arg;
}

void *func_ov002_0220b660(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov002_0220bd90);
    func_0208f46c(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov002_0220b648(void *arg)
{
    *((void **) arg) = &data_ov002_0220bd90;
    func_0208f46c(arg);
    return arg;
}

void func_ov002_0220b63c(void *p, int x, int y)
{
    func_0208aef4(p, x - 0x80, y - 0x60);
}

int func_ov002_0220b5ec(void *self, int k)
{
    int v = func_0208aef0(self);

    if (func_0208f0c0(self) == 2) {
        int a;
        int b;

        func_0208f184(self, &a, &b);
        v += a;
    }
    switch (k) {
        case 0:
        case 2:
            v += 0x10;
            break;
        case 1:
        case 3:
            v += 0x20;
            break;
    }
    return v;
}

int func_ov002_0220b59c(void *self, int k)
{
    int v = func_0208aeec(self);

    if (func_0208f0c0(self) == 2) {
        int a;
        int b;

        func_0208f184(self, &a, &b);
        v += b;
    }
    switch (k) {
        case 0:
        case 1:
            v += 8;
            break;
        case 2:
            break;
        case 3:
            v += 8;
            break;
    }
    return v;
}
