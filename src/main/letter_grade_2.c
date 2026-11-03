/* letter_grade_2: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206d9d8 @ 0x0206d9d8, 0x20 bytes, Thumb
 * func_0206d9c0 @ 0x0206d9c0, 0x18 bytes, Thumb
 * func_0206d9a0 @ 0x0206d9a0, 0x20 bytes, Thumb
 * func_0206d998 @ 0x0206d998, 0x8 bytes, Thumb
 * func_0206d994 @ 0x0206d994, 0x4 bytes, Thumb
 * func_0206d97c @ 0x0206d97c, 0x18 bytes, Thumb
 * func_0206d964 @ 0x0206d964, 0x18 bytes, Thumb
 * func_0206d94c @ 0x0206d94c, 0x18 bytes, Thumb
 * func_0206d92c @ 0x0206d92c, 0x20 bytes, Thumb
 * func_0206d924 @ 0x0206d924, 0x8 bytes, Thumb
 * func_0206d920 @ 0x0206d920, 0x4 bytes, Thumb
 */

struct UnkStruct_0206d9d8 {
    void *unk_00;
};

struct UnkStruct_0206d9c0 {
    unsigned char *unk_00;
};

typedef struct OpaqueType OpaqueType;

typedef struct {
    OpaqueType *vtable;
} UnkStruct_0206d964;

extern void *func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern unsigned char data_020df1d0[];
extern void *func_020a8c38(void *);
extern void func_020edb3c(void *);
extern int func_020b4a20(int a, char *b, int c);
extern void *func_020a88ec(UnkStruct_0206d964 *obj);
extern void *func_020a887c(void *p);
extern unsigned char data_020df1e8[];

struct UnkStruct_0206d9d8 *func_0206d9d8(struct UnkStruct_0206d9d8 *this)
{
    func_020a8cac(this);
    this->unk_00 = (void *) data_020df1d0;
    func_020a8c1c(this);
    return this;
}

struct UnkStruct_0206d9c0 *func_0206d9c0(struct UnkStruct_0206d9c0 *obj)
{
    obj->unk_00 = ((unsigned char *) data_020df1d0);
    func_020a8c38(obj);
    return obj;
}

void *func_0206d9a0(void *obj)
{
    *(void **) obj = ((unsigned char *) data_020df1d0);
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}

int func_0206d998(void)
{
    return 2562;
}

int func_0206d994(int p0)
{
    return ((int) (p0) + (18));
}

int func_0206d97c(int a, int b, char c)
{
    char local = c;
    return func_020b4a20(a, &local, b);
}

UnkStruct_0206d964 *func_0206d964(UnkStruct_0206d964 *obj)
{
    func_020a88ec(obj);
    obj->vtable = ((OpaqueType *) data_020df1e8);
    return obj;
}

void *func_0206d94c(void *p)
{
    *((void **) p) = (void *) data_020df1e8;
    func_020a887c(p);
    return p;
}

void *func_0206d92c(void *self)
{
    *((void **) self) = (void *) data_020df1e8;
    func_020a887c(self);
    func_020edb3c(self);
    return self;
}

int func_0206d924(void)
{
    return 1280;
}

int func_0206d920(int p0)
{
    return ((int) (p0) + (14));
}
