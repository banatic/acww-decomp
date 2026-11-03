/* push_button: 14 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220a5fc @ 0x0220a5fc, 0x24 bytes, Thumb
 * func_ov002_0220a5e4 @ 0x0220a5e4, 0x18 bytes, Thumb
 * func_ov002_0220a5c4 @ 0x0220a5c4, 0x20 bytes, Thumb
 * func_ov002_0220a58c @ 0x0220a58c, 0x36 bytes, Thumb
 * func_ov002_0220a580 @ 0x0220a580, 0xc bytes, Thumb
 * func_ov002_0220a574 @ 0x0220a574, 0xc bytes, Thumb
 * func_ov002_0220a568 @ 0x0220a568, 0xc bytes, Thumb
 * func_ov002_0220a544 @ 0x0220a544, 0x22 bytes, Thumb
 * func_ov002_0220a530 @ 0x0220a530, 0x12 bytes, Thumb
 * func_ov002_0220a51c @ 0x0220a51c, 0x12 bytes, Thumb
 * func_ov002_0220a4f8 @ 0x0220a4f8, 0x22 bytes, Thumb
 * func_ov002_0220a4d4 @ 0x0220a4d4, 0x22 bytes, Thumb
 * func_ov002_0220a4c8 @ 0x0220a4c8, 0xc bytes, Thumb
 * func_ov002_0220a4bc @ 0x0220a4bc, 0xc bytes, Thumb
 */

struct _Obj {
    void *vtbl;
};

struct UnkStruct_0220a530 {
    char pad_00[0xc];
    int unk_0C;
};

struct UnkStruct_0220a51c {
    char pad_00[0x10];
    int unk_10;
};

extern void *func_0208e95c(void *, int);
extern void *func_0208ec88(void *, int);
extern void *data_ov002_0220bcec;
extern void *func_0208ebb8(void *);
extern void func_020edb3c(void *);
extern int func_0208e958(void *);
extern int func_0208e930(void *);
extern int func_0208aef0(void *p);
extern int func_0208aeec(void *p);
extern void func_0208e9e0(char *self, int *a, int *b);
extern void func_0200467c(int);

int func_ov002_0220a530(struct UnkStruct_0220a530 *p);
int func_ov002_0220a51c(struct UnkStruct_0220a51c *p);

void *func_ov002_0220a5fc(char *self)
{
    // DECLS
    // ENDDECLS
    func_0208ec88(self, 0x0);
    *(void **) (self) = &data_ov002_0220bcec;
    func_0208e95c(self, 0x0);
    return self;
}

void *func_ov002_0220a5e4(void *arg)
{
    *((void **) arg) = ((int *) &data_ov002_0220bcec);
    func_0208ebb8(arg);
    return arg;
}

void *func_ov002_0220a5c4(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov002_0220bcec);
    func_0208ebb8(obj);
    func_020edb3c(obj);
    return obj;
}

int func_ov002_0220a58c(void *self, int x, int y)
{
    int dx;
    int dy;

    dx = x - func_ov002_0220a530((struct UnkStruct_0220a530 *) self);
    dy = y - func_ov002_0220a51c((struct UnkStruct_0220a51c *) self);
    if (dx < 0 || dx > 0x10) {
        return 0;
    }
    if (dy < 0 || dy > 0x10) {
        return 0;
    }
    return 1;
}

void func_ov002_0220a580(int arg)
{
    func_0208e95c((void *) arg, 1);
}

void func_ov002_0220a574(int a)
{
    func_0208e95c((void *) a, 2);
}

int func_ov002_0220a568(int a)
{
    return (int) func_0208e95c((void *) a, 3);
}

void func_ov002_0220a544(void *self)
{
    if (func_0208e958(self) == 3 && func_0208e930(self) != 0) {
        func_ov002_0220a580((int) self);
    }
}

int func_ov002_0220a530(struct UnkStruct_0220a530 *p)
{
    int r = func_0208aef0(p);
    return p->unk_0C + r;
}

int func_ov002_0220a51c(struct UnkStruct_0220a51c *p)
{
    int r = func_0208aeec(p);
    return p->unk_10 + r;
}

int func_ov002_0220a4f8(char *self)
{
    int a;
    int b;

    func_0208e9e0(self, &a, &b);
    return a + func_ov002_0220a530((struct UnkStruct_0220a530 *) self) + 7;
}

int func_ov002_0220a4d4(char *self)
{
    int a;
    int b;

    func_0208e9e0(self, &a, &b);
    return b + func_ov002_0220a51c((struct UnkStruct_0220a51c *) self) + 7;
}

void func_ov002_0220a4c8(void *receiver)
{
    // DECLS
    // ENDDECLS
    func_0200467c(0x19);
}

void func_ov002_0220a4bc(void *receiver)
{
    // DECLS
    // ENDDECLS
    func_0200467c(0x33);
}
