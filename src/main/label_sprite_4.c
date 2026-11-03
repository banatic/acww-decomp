/* label_sprite_4: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208f604 @ 0x0208f604, 0x4 bytes, Thumb
 * func_0208f600 @ 0x0208f600, 0x4 bytes, Thumb
 * func_0208f58c @ 0x0208f58c, 0x74 bytes, Thumb
 * func_0208f518 @ 0x0208f518, 0x74 bytes, Thumb
 * func_0208f4e0 @ 0x0208f4e0, 0x38 bytes, Thumb
 * func_0208f4a4 @ 0x0208f4a4, 0x3c bytes, Thumb
 * func_0208f46c @ 0x0208f46c, 0x38 bytes, Thumb
 * func_0208f288 @ 0x0208f288, 0x1e4 bytes, Thumb
 * func_0208f268 @ 0x0208f268, 0x20 bytes, Thumb
 * func_0208f260 @ 0x0208f260, 0x8 bytes, Thumb
 * func_0208f258 @ 0x0208f258, 0x8 bytes, Thumb
 * func_0208f250 @ 0x0208f250, 0x8 bytes, Thumb
 */

typedef struct UnkStruct_0208f58c UnkStruct_0208f58c;

struct UnkStruct_0208f58c {
    void *unk_00;
    int pad_04;
    int pad_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    char sub1[20];
    char sub2[20];
    int unk_44;
    int unk_48;
    char sub3[36];
    unsigned short unk_70;
    unsigned char unk_72;
    unsigned char unk_73;
    unsigned char unk_74;
    unsigned char unk_75;
};

typedef struct Struct0208F518 {
    void *unk_00;
    char pad_04[8];
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    char sub_1c[20];
    char sub_30[20];
    int unk_44;
    int unk_48;
    char sub_4c[36];
    unsigned short unk_70;
    unsigned char unk_72;
    unsigned char unk_73;
    unsigned char unk_74;
    unsigned char unk_75;
} Struct0208F518;

struct UnkStruct_0208f4a4 {
    void *vtable;
    char pad_04[0x18];
    char sub1c[0x14];
    char sub30[0x1c];
    char sub4c[1];
};

typedef struct {
    char pad_00[0x0c];
    int unk_0C;
    int unk_10;
    int unk_14;
    char pad_18[0x44 - 0x18];
    int unk_44;
    char pad_48[0x72 - 0x48];
    unsigned char unk_72;
    unsigned char unk_73;
    unsigned char unk_74;
} Func_0208f288_Struct;

extern void func_0208af30(struct UnkStruct_0208f58c *obj);
extern void func_0208a1f8(void *p);
extern void *func_0208f640(void *p);
extern void func_0208f0c4(void *, int);
extern unsigned char data_020e23a0[];
extern void func_0208effc(void *);
extern void *func_0208f628(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);
extern int func_0208a1d0(const void *ptr);
extern int func_0208a1b0(const void *ptr, int a);
extern int func_0208a198(const void *ptr, int a);
extern int func_0208aef0(const void *ptr);
extern int func_0208aeec(const void *ptr);
extern void func_02088df8(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);
extern void func_0208ef7c(const void *ptr);
extern void func_0208a0c8(void *);

int func_0208f604(void)
{
    return 16;
}

int func_0208f600(int p0)
{
    return ((int) (p0) + (18));
}

struct UnkStruct_0208f58c *func_0208f58c(struct UnkStruct_0208f58c *obj, char a, int b)
{
    func_0208af30(obj);
    obj->unk_00 = (void *) data_020e23a0;
    obj->unk_0C = 0;
    obj->unk_10 = 0;
    obj->unk_14 = -1;
    obj->unk_18 = b;
    func_0208a1f8((void *) &obj->sub1);
    func_0208a1f8((void *) &obj->sub2);
    obj->unk_44 = 0;
    obj->unk_48 = 0;
    func_0208f640((void *) &obj->sub3);
    obj->unk_70 = 0x50c0;
    obj->unk_72 = a;
    obj->unk_73 = 0;
    obj->unk_74 = 0;
    obj->unk_75 = 0;
    func_0208f0c4(obj, 0);
    return obj;
}

Struct0208F518 *func_0208f518(Struct0208F518 *self, int param1, int param2)
{
    func_0208af30((struct UnkStruct_0208f58c *) self);
    self->unk_00 = (void *) data_020e23a0;
    self->unk_0C = 0;
    self->unk_10 = 0;
    self->unk_14 = -1;
    self->unk_18 = param2;
    func_0208a1f8((void *) self->sub_1c);
    func_0208a1f8((void *) self->sub_30);
    self->unk_44 = 0;
    self->unk_48 = 0;
    func_0208f640((void *) self->sub_4c);
    self->unk_70 = 0x50c0;
    self->unk_72 = (unsigned char) param1;
    self->unk_73 = 0;
    self->unk_74 = 0;
    self->unk_75 = 0;
    func_0208f0c4(self, 0);
    return self;
}

void *func_0208f4e0(void *p)
{
    ((unsigned int *) p)[0] = (unsigned int) ((char *) data_020e23a0);
    func_0208effc(p);
    func_0208f628((char *) p + 0x4C);
    func_0208a1f4((char *) p + 0x30);
    func_0208a1f4((char *) p + 0x1C);
    func_0208af00(p);
    return p;
}

struct UnkStruct_0208f4a4 *func_0208f4a4(struct UnkStruct_0208f4a4 *self)
{
    self->vtable = (void *) data_020e23a0;
    func_0208effc(self);
    func_0208f628(&self->sub4c);
    func_0208a1f4(&self->sub30);
    func_0208a1f4(&self->sub1c);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}

void *func_0208f46c(void *self)
{
    *(void **) self = (void *) data_020e23a0;
    func_0208effc(self);
    func_0208f628((char *) self + 0x4c);
    func_0208a1f4((char *) self + 0x30);
    func_0208a1f4((char *) self + 0x1c);
    func_0208af00(self);
    return self;
}

void func_0208f288(Func_0208f288_Struct *self)
{
    int a, b, c, d, e, f, x, y, x2, y2, x3, y3;
    int flag74;

    if (self->unk_44 == 0) {
        goto exit;
    }

    e = func_0208a1d0((char *) self + 0x1c);
    f = func_0208a1d0((char *) self + 0x30);
    a = func_0208a1b0((char *) self + 0x1c, -1);
    b = func_0208a198((char *) self + 0x1c, -1);
    c = func_0208a1b0((char *) self + 0x30, -1);
    d = func_0208a198((char *) self + 0x30, -1);
    x = func_0208aef0(self) + self->unk_0C;
    y = func_0208aeec(self) + self->unk_10;
    x2 = x + a;
    y2 = y + b;
    x3 = x + c;
    y3 = y + d;

    flag74 = (self->unk_74 == 0);

    if (self->unk_72) {
        func_02088df8(0, e, x2, y2, self->unk_14, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        if (flag74) {
            func_02088df8(0, f, x3, y3, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (self->unk_73) {
            func_02088df8(0, e, x2, y2, -1, -1, 0x1000, 0x1000, 0, 2, 0, 0);
            if (flag74) {
                func_02088df8(0, f, x3, y3, -1, -1, 0x1000, 0x1000, 0, 2, 0, 0);
            }
        }
    } else {
        func_02088df8(1, e, x2, y2, self->unk_14, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        if (flag74) {
            func_02088df8(1, f, x3, y3, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (self->unk_73) {
            func_02088df8(1, e, x2, y2, -1, -1, 0x1000, 0x1000, 0, 2, 0, 0);
            if (flag74) {
                func_02088df8(1, f, x3, y3, -1, -1, 0x1000, 0x1000, 0, 2, 0, 0);
            }
        }
    }

exit:
    func_0208ef7c(self);
}

void func_0208f268(void *param)
{
    if (*(unsigned int *) ((char *) param + 0x44) != 0) {
        func_0208a0c8((char *) param + 0x1c);
        func_0208a0c8((char *) param + 0x30);
    }
}

void func_0208f260(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (115))) + (0)) = 1;
}

void func_0208f258(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (116))) + (0)) = 1;
}

void func_0208f250(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (116))) + (0)) = 0;
}
