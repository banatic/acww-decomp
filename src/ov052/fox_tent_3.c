/* fox_tent_3: 19 functions, module ov052
 * mwccarm 1.2/base -O4,s
 * func_ov052_022618ec @ 0x022618ec, 0x1c bytes, Thumb
 * func_ov052_022618d8 @ 0x022618d8, 0x12 bytes, Thumb
 * func_ov052_022618a8 @ 0x022618a8, 0x30 bytes, Thumb
 * func_ov052_02261808 @ 0x02261808, 0xa0 bytes, Thumb
 * func_ov052_022617d4 @ 0x022617d4, 0x34 bytes, Thumb
 * func_ov052_0226170c @ 0x0226170c, 0xc8 bytes, Thumb
 * func_ov052_022616d8 @ 0x022616d8, 0x34 bytes, Thumb
 * func_ov052_022615d8 @ 0x022615d8, 0x100 bytes, Thumb
 * func_ov052_022615a4 @ 0x022615a4, 0x34 bytes, Thumb
 * func_ov052_022614a4 @ 0x022614a4, 0x100 bytes, Thumb
 * func_ov052_0226146c @ 0x0226146c, 0x38 bytes, Thumb
 * func_ov052_02261424 @ 0x02261424, 0x48 bytes, Thumb
 * func_ov052_022613ec @ 0x022613ec, 0x38 bytes, Thumb
 * func_ov052_022613a8 @ 0x022613a8, 0x44 bytes, Thumb
 * func_ov052_022613a4 @ 0x022613a4, 0x4 bytes, Thumb
 * func_ov052_022613a0 @ 0x022613a0, 0x4 bytes, Thumb
 * func_ov052_0226139c @ 0x0226139c, 0x4 bytes, Thumb
 * func_ov052_02261398 @ 0x02261398, 0x4 bytes, Thumb
 * func_ov052_02261358 @ 0x02261358, 0x40 bytes, Thumb
 */

struct UnkStruct_022618a8 {
    char pad_00[0x564];
    char unk_564;
    char pad_565[0x1B7];
    unsigned short unk_71C;
};

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x8e - 0x60];
    short unk_8E;
} UnkStruct_02261808;

typedef struct {
    int unk_00, x1, x2;
} UnkStruct_022615d8;

typedef struct {
    int unk_00, x1, x2;
} UnkStruct_022614a4;

typedef struct {
    int x, y, z;
} UnkStruct_022613a8;

extern void func_ov052_022610cc(int a, int b);
extern int func_0203e0a8(int a, int b);
extern int func_02019c6c(void *p, int a, unsigned short b);
extern unsigned short data_020c80f8;
extern Vec3 *func_02095794(int);
extern int func_0201c2c8(UnkStruct_02261808 *, int);
extern int func_020e8b4c(int, int);
extern void func_0201b458(Vec3 *, UnkStruct_02261808 *, Vec3 *);
extern int func_020eaa2c(Vec3 *, void *);
extern int func_ov052_022604ec(void *arg0);
extern int func_ov052_022604a0(void *self);
extern int func_ov052_02260554(void *self);
extern int func_0201c378(void *self, int kind);
extern void func_ov052_02261908(void *self, int kind);
extern void func_0201aff4(void *self, int arg);
extern int func_02019e00(void *self);
extern int func_02019de8(void *self);
extern int func_02019d0c(unsigned int, int, int, int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
                         unsigned int, unsigned int);
extern void func_0201b044(void *p, UnkStruct_022615d8 *buf);
extern int func_020eaa6c(UnkStruct_022615d8 *buf, void *p);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *p);
extern int func_020ad888(void);
extern int func_0203e020(void *p);
extern int func_020b5e10(void);
extern int func_020b6098(int, int);

int func_ov052_022618ec(int a)
{
    func_ov052_022610cc(a + 0x658, 0);
    return 1;
}

int func_ov052_022618d8(int a)
{
    func_0203e0a8(a, 0);
    return 1;
}

int func_ov052_022618a8(struct UnkStruct_022618a8 *self)
{
    func_02019c6c(&self->unk_564, 1, self->unk_71C);
    self->unk_71C = data_020c80f8;
    return 1;
}

int func_ov052_02261808(UnkStruct_02261808 *self)
{
    Vec3 v1;
    Vec3 v2;
    int a;
    int b;
    int tmp;
    Vec3 *src;

    src = func_02095794(4);
    v1.x = src->x;
    v1.y = src->y;
    v1.z = src->z;
    a = func_0201c378((void *) self, 4);
    tmp = func_0201c2c8(self, 4);
    b = func_020e8b4c(self->unk_8E, tmp);
    func_0201b458(&v2, self, &v1);
    if (a > 0x3000 && func_020eaa2c(&v2, &self->unk_5C) != 0) {
        func_ov052_02261908((void *) self, 3);
    } else if (b > 0x2000) {
        func_ov052_02261908((void *) self, 2);
    }
    if (func_ov052_022604ec((void *) self) != 0) {
        return 1;
    }
    if (func_ov052_022604a0((void *) self) != 0) {
        return 1;
    }
    func_ov052_02260554((void *) self);
    return 1;
}

int func_ov052_022617d4(char *ptr)
{
    func_02019d0c((unsigned int) (ptr + 0x564), 3, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov052_0226170c(void *self)
{
    int r6, r4;
    int tmp[3];
    int local[3];

    if (func_ov052_022604ec((void *) self)) {
        return 1;
    }
    if (func_ov052_022604a0(self)) {
        return 1;
    }
    if (func_ov052_02260554(self)) {
        return 1;
    }

    {
        void *p = (void *) func_02095794(4);
        tmp[0] = *(int *) p;
        tmp[1] = *(int *) ((char *) p + 4);
        tmp[2] = *(int *) ((char *) p + 8);
    }

    r6 = func_0201c378(self, 4);
    r4 = func_0201c2c8((UnkStruct_02261808 *) self, 4);

    func_020e8b4c(*(short *) ((char *) self + 0x8e), r4);

    func_0201b458((Vec3 *) (&local[0]), (UnkStruct_02261808 *) self, (Vec3 *) (&tmp[0]));

    if (r6 > 0x3000) {
        if (func_020eaa2c((Vec3 *) (&local[0]), (char *) self + 0x5c)) {
            func_ov052_02261908(self, 3);
            return 1;
        }
    }

    (func_0201aff4((char *) self + 0x350, r4), (int) ((char *) self + 0x350));
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564)) {
            func_ov052_02261908(self, 1);
        }
    }
    return 1;
}

int func_ov052_022616d8(unsigned int p)
{
    func_02019d0c(p + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, (unsigned int) data_020c80f8, 0);
    return 1;
}

int func_ov052_022615d8(void *self)
{
    UnkStruct_022615d8 src, buf;
    int t;

    if (func_ov052_022604ec(self)) {
        return 1;
    }
    if (func_ov052_022604a0(self)) {
        return 1;
    }
    if (func_ov052_02260554(self)) {
        return 1;
    }

    {
        UnkStruct_022615d8 *p = (UnkStruct_022615d8 *) func_02095794(4);
        src.unk_00 = p->unk_00;
        src.x1 = p->x1;
        src.x2 = p->x2;
    }
    t = func_0201c378(self, 4);
    func_0201b458((Vec3 *) (&buf), (UnkStruct_02261808 *) self, (Vec3 *) (&src));

    if (t > 0x4000) {
        if (func_02019e00((char *) self + 0x564) == 1) {
            func_02019d0c((unsigned int) ((char *) self + 0x564), 2, 1, 0, 0, 0x800, 0, 0, 0, data_020c80f8, 0);
        }
    } else {
        if (func_02019e00((char *) self + 0x564) == 2) {
            func_02019d0c((unsigned int) ((char *) self + 0x564), 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }

    func_0201b044((char *) self + 0x350, &buf);

    if (t <= 0x3000 || func_020eaa6c(&buf, (char *) self + 0x5c) != 0) {
        func_ov052_02261908(self, 1);
    }

    return 1;
}

int func_ov052_022615a4(unsigned int p)
{
    func_02019d0c(p + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, (unsigned int) data_020c80f8, 0);
    return 1;
}

int func_ov052_022614a4(void *self)
{
    UnkStruct_022614a4 src, buf;
    int t;

    if (func_ov052_022604ec(self)) {
        return 1;
    }
    if (func_ov052_022604a0(self)) {
        return 1;
    }
    if (func_ov052_02260554(self)) {
        return 1;
    }

    {
        UnkStruct_022614a4 *p = (UnkStruct_022614a4 *) func_02095794(4);
        src.unk_00 = p->unk_00;
        src.x1 = p->x1;
        src.x2 = p->x2;
    }
    t = func_0201c378(self, 4);
    func_0201b458((Vec3 *) (&buf), (UnkStruct_02261808 *) self, (Vec3 *) (&src));

    if (t > 0x4000) {
        if (func_02019e00((char *) self + 0x564) == 1) {
            func_02019d0c((unsigned int) ((char *) self + 0x564), 2, 1, 0, 0, 0x800, 0, 0, 0, data_020c80f8, 0);
        }
    } else {
        if (func_02019e00((char *) self + 0x564) == 2) {
            func_02019d0c((unsigned int) ((char *) self + 0x564), 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }

    func_0201b044((char *) self + 0x350, (UnkStruct_022615d8 *) (&buf));

    if (t <= 0x3000 || func_020eaa6c((UnkStruct_022615d8 *) (&buf), (char *) self + 0x5c) != 0) {
        func_ov052_02261908(self, 1);
    }

    return 1;
}

int func_ov052_0226146c(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov052_02261424(void *obj)
{
    if (func_02014868((char *) obj + 0x618) != 0) {
        return 1;
    }
    if (*(unsigned char *) ((char *) obj + 0x730) != 0) {
        if (func_020ad888() == 0) {
            return 1;
        }
    }
    func_0203e020(obj);
    func_ov052_02261908(obj, 7);
    return 1;
}

int func_ov052_022613ec(void *self)
{
    int size = func_02016104((char *) self + 0x658);
    int ret = 0;
    if (size != 0) {
        ret = func_0201c314(self, size);
    }
    func_020147fc((char *) self + 0x618, 0, ret, 1);
    return 1;
}

int func_ov052_022613a8(char *self)
{
    volatile int a, b, c;
    UnkStruct_022613a8 *p = (UnkStruct_022613a8 *) func_02095794(4);
    a = p->x;
    b = p->y;
    c = p->z;
    if (func_02014868(self + 0x618) == 0) {
        func_020b6098(func_020b5e10(), 0);
        func_ov052_02261908(self, 7);
    }
    return 1;
}

int func_ov052_022613a4(void)
{
    return 1;
}

int func_ov052_022613a0(void)
{
    return 1;
}

int func_ov052_0226139c(void)
{
    return 1;
}

int func_ov052_02261398(void)
{
    return 1;
}

int func_ov052_02261358(unsigned char *self)
{
    self[0x731] = 50;
    func_02019d0c((unsigned int) (self + 0x564), 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
