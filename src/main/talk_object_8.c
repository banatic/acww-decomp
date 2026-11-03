/* talk_object_8: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020679a0 @ 0x020679a0, 0x10 bytes, Thumb
 * func_02067964 @ 0x02067964, 0x3c bytes, Thumb
 * func_02067948 @ 0x02067948, 0x1c bytes, Thumb
 * func_020678f8 @ 0x020678f8, 0x50 bytes, Thumb
 * func_020678d4 @ 0x020678d4, 0x24 bytes, Thumb
 * func_0206786c @ 0x0206786c, 0x68 bytes, Thumb
 * func_0206785c @ 0x0206785c, 0x10 bytes, Thumb
 */

typedef struct UnkStruct_02067964 UnkStruct_02067964;

typedef struct ObjVtbl ObjVtbl;

struct ObjVtbl {
    unsigned char pad_00[0x68];
    int (*method)(UnkStruct_02067964 *);
};

struct UnkStruct_02067964 {
    ObjVtbl *vtbl;
};

typedef struct UnkStruct_02067964_2 {
    unsigned char pad_00[0x14A8];
    UnkStruct_02067964 *obj;
    unsigned char pad_14AC[0x1CEC - 0x14AC];
    char unk_1CEC;
} UnkStruct_02067964_2;

struct UnkStruct_020678f8;

struct VT {
    unsigned char pad_00[0x68];
    void *(*unk_68)(struct UnkStruct_020678f8 *o);
};

struct UnkStruct_020678f8 {
    struct VT *vt;
};

typedef struct VT_0206786c {
    unsigned char pad_00[0x68];
    int (*unk_68)(void *);
} VT_0206786c;

typedef struct UnkStruct_0206786c {
    VT_0206786c *vt;
} UnkStruct_0206786c;

typedef struct UnkStruct_0206786c_2 {
    unsigned char pad_00[0x14a8];
    UnkStruct_0206786c *unk_14A8;
    unsigned char pad_14AC[0x1d2c - 0x14a8 - 4];
    unsigned char unk_1D2C[0x1e75 - 0x1d2c];
    unsigned char unk_1E75;
    unsigned char unk_1E76;
} UnkStruct_0206786c_2;

extern void func_020a8c1c(void *);
extern void func_0207eec4(int, void *);
extern void func_0207ee78(void *r, unsigned char *p);
extern int func_020984e8(void);
extern int func_02099348(int, void *);

void func_020679a0(unsigned int r0)
{
    func_020a8c1c((void *) (r0 + 0x1cec));
}

int func_02067964(UnkStruct_02067964_2 *self)
{
    UnkStruct_02067964 *obj = self->obj;
    int res = obj->vtbl->method(obj);
    int ret = 0;
    func_020a8c1c(&self->unk_1CEC);
    if (res != 0) {
        func_0207eec4(res, &self->unk_1CEC);
        ret = 1;
    }
    return ret;
}

void func_02067948(unsigned char *base)
{
    base[0x1e74] = 0;
    func_020a8c1c(base + 0x1d0c);
}

int func_020678f8(unsigned char *p)
{
    int ok = 1;
    if (p[0x1e74] == 0) {
        struct UnkStruct_020678f8 *o = *(struct UnkStruct_020678f8 **) (p + 0x14a8);
        void *r = o->vt->unk_68(o);
        func_020a8c1c((void *) (p + 0x1d0c));
        if (r != 0) {
            func_0207ee78(r, p + 0x1d0c);
        } else {
            ok = 0;
        }
        p[0x1e74] = 1;
    }
    return ok;
}

void func_020678d4(void *param)
{
    unsigned char *base = (unsigned char *) param;
    base[0x1e75] = 0;
    base[0x1e76] = 0;
    func_020a8c1c((void *) ((unsigned char *) param + 0x1d2c));
}

int func_0206786c(UnkStruct_0206786c_2 *self)
{
    int ret;
    int x;
    UnkStruct_0206786c *o;
    int r;
    ret = 1;
    if (self->unk_1E75 == 0) {
        x = func_020984e8();
        func_020a8c1c(self->unk_1D2C);
        if (func_02099348(x, self->unk_1D2C) == 0) {
            o = self->unk_14A8;
            r = o->vt->unk_68(o);
            if (r != 0) {
                func_0207ee78((void *) r, (unsigned char *) self->unk_1D2C);
                self->unk_1E76 = (unsigned char) ret;
            } else {
                ret = 0;
            }
        }
        self->unk_1E75 = 1;
    }
    return ret;
}

void func_0206785c(int arg)
{
    func_020a8c1c((void *) (arg + 0x1d4c));
}
