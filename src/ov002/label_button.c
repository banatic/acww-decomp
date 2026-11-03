/* label_button: 7 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220b498 @ 0x0220b498, 0x64 bytes, Thumb
 * func_ov002_0220b47c @ 0x0220b47c, 0x1c bytes, Thumb
 * func_ov002_0220b464 @ 0x0220b464, 0x18 bytes, Thumb
 * func_ov002_0220b444 @ 0x0220b444, 0x20 bytes, Thumb
 * func_ov002_0220b428 @ 0x0220b428, 0x1c bytes, Thumb
 * func_ov002_0220b410 @ 0x0220b410, 0x18 bytes, Thumb
 * func_ov002_0220b3f0 @ 0x0220b3f0, 0x20 bytes, Thumb
 */

#include "types.h"

struct _Obj {
    void *vtbl;
};

extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c60;
extern u8 data_021f6c5c;
extern int func_0208aef0(void *self);
extern int func_0208aeec(void *self);
extern void *func_ov002_0220b698(void *, int, int);
extern void *data_ov002_0220bd74;
extern void *func_ov002_0220b648(void *);
extern void func_020edb3c(void *);
extern void *data_ov002_0220bd58;

int func_ov002_0220b498(void *self)
{
    int ok;
    int t;
    int dy;
    int dx;

    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok) {
        t = data_021f6c60;
        dy = t - func_0208aef0(self);
        t = data_021f6c5c;
        dx = t - func_0208aeec(self);
        if (dy >= 0 && dy <= 0x40 && dx >= 0 && dx <= 0x18) {
            return 1;
        }
    }
    return 0;
}

void *func_ov002_0220b47c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b698(self, 0x0, 0x0);
    *(void **) (self) = &data_ov002_0220bd74;
    return self;
}

void *func_ov002_0220b464(void *arg)
{
    *((void **) arg) = ((int *) &data_ov002_0220bd74);
    func_ov002_0220b648(arg);
    return arg;
}

void *func_ov002_0220b444(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov002_0220bd74);
    func_ov002_0220b648(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_ov002_0220b428(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b698(self, 0x1, 0x0);
    *(void **) (self) = &data_ov002_0220bd58;
    return self;
}

void *func_ov002_0220b410(void *arg)
{
    *((void **) arg) = ((int *) &data_ov002_0220bd58);
    func_ov002_0220b648(arg);
    return arg;
}

void *func_ov002_0220b3f0(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov002_0220bd58);
    func_ov002_0220b648(obj);
    func_020edb3c(obj);
    return obj;
}
