/* start_menu: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209f6e0 @ 0x0209f6e0, 0x2 bytes, Thumb
 * func_0209f6b8 @ 0x0209f6b8, 0x26 bytes, Thumb
 * func_0209f6b4 @ 0x0209f6b4, 0x2 bytes, Thumb
 * func_0209f668 @ 0x0209f668, 0x4c bytes, Thumb
 * func_0209f658 @ 0x0209f658, 0x10 bytes, Thumb
 * func_0209f5dc @ 0x0209f5dc, 0x7c bytes, Thumb
 * func_0209f5cc @ 0x0209f5cc, 0x10 bytes, Thumb
 * func_0209f550 @ 0x0209f550, 0x7c bytes, Thumb
 * func_0209f538 @ 0x0209f538, 0x18 bytes, Thumb
 * func_0209f520 @ 0x0209f520, 0x18 bytes, Thumb
 * func_0209f500 @ 0x0209f500, 0x20 bytes, Thumb
 * func_0209f4fc @ 0x0209f4fc, 0x4 bytes, Thumb
 * func_0209f47c @ 0x0209f47c, 0x80 bytes, Thumb
 * func_0209f3d0 @ 0x0209f3d0, 0xac bytes, Thumb
 * func_0209f3a0 @ 0x0209f3a0, 0x30 bytes, Thumb
 * func_0209f374 @ 0x0209f374, 0x2c bytes, Thumb
 */

struct UnkStruct_0209f6b8 {
    int unk_00;
    int unk_04;
};

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0209f668;

typedef struct UnkStruct_0209f5dc {
    char pad_00[0x94];
    void *unk_94;
} UnkStruct_0209f5dc;

typedef struct {
    unsigned char pad_00[0xA0];
    unsigned short unk_A0;
} UnkStruct_0209f5cc;

typedef struct UnkStruct_0209f550 {
    char pad_00[0x94];
    void *unk_94;
} UnkStruct_0209f550;

typedef struct {
    void *unk_00;
} UnkStruct_0209f538;

struct Obj0209f520 {
    void *unk_00;
};

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char flag;
    unsigned char pad_1F[0x40 - 0x1f];
    void *data;
} UnkStruct_0209f47c;

typedef struct UnkStruct_0209f3d0 {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    void *unk_40;
    char pad_44[4];
    void *unk_48;
} UnkStruct_0209f3d0;

struct Class {
    void *vtbl;
    unsigned char pad_04[0x50];
    unsigned char sub[1];
};

extern struct UnkStruct_0209f6b8 *func_020682e0(int arg);
extern void func_02068320(struct UnkStruct_0209f6b8 *arg);
extern void func_0203e210(void);
extern void func_0209f820(int arg0, int arg1);
extern int func_020b5e10(void);
extern int func_020b6434(int, int, int, int);
extern int func_02073d90(int);
extern int func_020b5ee4(int, int);
extern void func_020a18ac(void);
extern void func_020a1948(void);
extern int data_020ccf94;
extern int func_0207417c(int);
extern int func_02074150(void);
extern void func_02068358(void *);
extern void func_02068434(void *);
extern void func_020a6f20(int, int);
extern int func_020a6f00(void);
extern void func_020a6ef0(void *);
extern void func_0206844c(void *, unsigned char *, const void *);
extern void func_020a01e0(int);
extern void func_02074120(void);
extern unsigned char data_021f43e8;
extern const int data_020e37d0;
extern void *func_02066a30(void *p);
extern void *func_02066994(void *);
extern void func_020edb3c(void *p);
extern unsigned char data_020e3758[];
extern int func_0206837c(void *);
extern void func_020ab670(int, int, int);
extern void func_020ab628(int, int, unsigned char *, int, unsigned char *, int, int);
extern void func_020ab5f8(int);
extern void func_02068388(void *, int);
extern int func_020ab504(int);
extern void func_02068440(void *);
extern void func_02068364(void *, int);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020e3708[];

void func_0209f6e0(void) {}

void func_0209f6b8(int arg0)
{
    struct UnkStruct_0209f6b8 *p = func_020682e0(0);
    if (p->unk_04 == 0) {
        (((int) (func_02068320(p), p)), func_0203e210());
        func_0209f820(arg0, 0);
    }
}

void func_0209f6b4(void) {}

void func_0209f668(void)
{
    UnkStruct_0209f668 *s = (UnkStruct_0209f668 *) func_020682e0(0);
    if (s->unk_04 != 0) {
        return;
    }

    func_02068320((struct UnkStruct_0209f6b8 *) s);
    func_020b6434(func_020b5e10(), 46, 2, 3);

    if (func_02073d90(data_020ccf94) != 0) {
        func_020b5ee4(func_020b5e10(), 0);
        func_020a18ac();
    } else {
        func_020a1948();
    }
}

void func_0209f658(int p0)
{
    *(unsigned short *) ((char *) (((int) (p0) + (160))) + (0)) = 200;
    func_0207417c(2);
}

void func_0209f5dc(UnkStruct_0209f5dc *this)
{
    void *o = this->unk_94;
    int r = func_02074150();

    if ((unsigned int) (r - 5) <= 1) {
        func_02068358(o);
        func_02068434(o);
        if (r == 5) {
            func_020a6f20(0, 6);
            func_020a6ef0((void *) func_020a6f00());
            func_0206844c(o, &data_021f43e8, (const void *) 0);
            func_020a01e0(0);
            func_0209f820((int) this, 3);
        } else {
            unsigned char code = 5;
            func_0206844c(o, &code, (const void *) &data_020e37d0);
            func_0209f820((int) this, 2);
        }
        func_02074120();
    }
}

void func_0209f5cc(UnkStruct_0209f5cc *s)
{
    s->unk_A0 = 0xC8;
    func_0207417c(3);
}

void func_0209f550(UnkStruct_0209f550 *this)
{
    void *o = this->unk_94;
    int r = func_02074150();

    if ((unsigned int) (r - 5) <= 1) {
        func_02068358(o);
        func_02068434(o);
        if (r == 5) {
            func_020a6f20(0, 6);
            func_020a6ef0((void *) func_020a6f00());
            func_0206844c(o, &data_021f43e8, (const void *) 0);
            func_020a01e0(1);
            func_0209f820((int) this, 3);
        } else {
            unsigned char code = 5;
            func_0206844c(o, &code, (const void *) &data_020e37d0);
            func_0209f820((int) this, 2);
        }
        func_02074120();
    }
}

void *func_0209f538(void *p)
{
    func_02066a30(p);
    ((UnkStruct_0209f538 *) p)->unk_00 = (void *) ((char *) data_020e3758);
    return p;
}

struct Obj0209f520 *func_0209f520(struct Obj0209f520 *self)
{
    self->unk_00 = ((unsigned char *) data_020e3758);
    func_02066994(self);
    return self;
}

void *func_0209f500(void *arg)
{
    *(void **) arg = (void *) data_020e3758;
    func_02066994(arg);
    func_020edb3c(arg);
    return arg;
}

void func_0209f4fc(int *p0, int p1)
{
    p0[18] = p1;
}

void func_0209f47c(UnkStruct_0209f47c *obj)
{
    unsigned char local[4];
    void *ptr;
    int result;

    if (obj->flag != 0) {
        return;
    }

    ptr = obj->data;
    result = func_0206837c(ptr);
    func_020ab670(result, 2, 1);

    local[0] = 0xc;
    local[1] = data_021f43e8;
    func_020ab628(result, 0, local, 1, &local[1], 0, 2);

    local[2] = 0xd;
    local[3] = data_021f43e8;
    func_020ab628(result, 1, &local[2], 1, &local[3], 0, 0);

    func_020ab5f8(result);
    func_02068388(ptr, 1);
}

void func_0209f3d0(UnkStruct_0209f3d0 *this)
{
    void *o = this->unk_40;
    int ok = func_020ab504(func_0206837c(o));
    unsigned char code;

    switch (this->unk_1E) {
        case 4:
            switch (ok) {
                case 0:
                    func_02068440(o);
                    func_02068364(o, 1);
                    func_0209f820((int) this->unk_48, 4);
                    break;
                case 1:
                    code = 8;
                    func_0206844c(o, &code, (const void *) &data_020e37d0);
                    break;
            }
            break;
        case 8:
            switch (ok) {
                case 0:
                    func_02068440(o);
                    func_02068364(o, 1);
                    func_0209f820((int) this->unk_48, 5);
                    break;
                case 1:
                    func_0206844c(o, &data_021f43e8, (const void *) 0);
                    break;
            }
            break;
        case 0:
            if (ok == 0) {
                func_0206844c(o, &data_021f43e8, (const void *) 0);
                func_0209f820((int) this->unk_48, 3);
            }
            break;
    }
}

struct Class *func_0209f3a0(struct Class *this)
{
    this->vtbl = (void *) data_020e3708;
    func_0209f520((struct Obj0209f520 *) this->sub);
    this->vtbl = (void *) data_020da13c;
    func_020ee62c(this);
    func_020edf54(this);
    return this;
}

void *func_0209f374(void *this)
{
    *(int **) this = ((int *) data_020e3708);
    func_0209f520((struct Obj0209f520 *) ((void *) ((unsigned int) this + 0x54)));
    *(int **) this = ((int *) data_020da13c);
    func_020ee62c((void *) this);
    return this;
}
