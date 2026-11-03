/* friend_code_entry: 11 functions, module ov133
 * mwccarm 1.2/base -O4,s
 * func_ov133_0229aed4 @ 0x0229aed4, 0xbc bytes, Thumb
 * func_ov133_0229ae94 @ 0x0229ae94, 0x3e bytes, Thumb
 * func_ov133_0229ae8c @ 0x0229ae8c, 0x8 bytes, Thumb
 * func_ov133_0229ae5c @ 0x0229ae5c, 0x30 bytes, Thumb
 * func_ov133_0229ae1c @ 0x0229ae1c, 0x40 bytes, Thumb
 * func_ov133_0229adc4 @ 0x0229adc4, 0x58 bytes, Thumb
 * func_ov133_0229adb8 @ 0x0229adb8, 0xc bytes, Thumb
 * func_ov133_0229ad9c @ 0x0229ad9c, 0x1c bytes, Thumb
 * func_ov133_0229ad88 @ 0x0229ad88, 0x12 bytes, Thumb
 * func_ov133_0229ad78 @ 0x0229ad78, 0xe bytes, Thumb
 * func_ov133_0229ad68 @ 0x0229ad68, 0xe bytes, Thumb
 */

typedef struct {
    char pad_00[0x9c];
    unsigned char unk_9C;
    unsigned char unk_9D;
    unsigned char unk_9E;
    char unk_9F;
    unsigned char unk_A0;
} UnkStruct_0229ae94;

struct UnkStruct_0229ad88 {
    unsigned char pad_00[0x98];
    unsigned short flags;
};

struct Overlay133_Struct {
    char pad_00[0x98];
    unsigned short flags;
};

struct UnkStruct_0229ad68 {
    char pad_00[0x98];
    unsigned short unk_98;
};

extern void func_ov133_0229afec(void *self);
extern void func_ov133_0229af90(void *self);
extern int func_020b9bbc(void *dst, void *src, int count, int size, int flag);
extern int func_ov133_0229b3f8(UnkStruct_0229ae94 *self, int n);
extern void func_0206fdd4(char *, int, int, int, int, int);
extern char *data_ov133_0229c79c[];
extern int data_ov133_0229c814[];

void func_ov133_0229ae1c(char *obj);
void func_ov133_0229adb8(int a, int b);
void func_ov133_0229ad9c(int a, int b);
int func_ov133_0229ad88(struct UnkStruct_0229ad88 *p, unsigned int mask);
void func_ov133_0229ad78(struct Overlay133_Struct *obj, unsigned short val);
void func_ov133_0229ad68(struct UnkStruct_0229ad68 *p, unsigned short mask);

void func_ov133_0229aed4(void *self)
{
    if (func_ov133_0229ad88((struct UnkStruct_0229ad88 *) self, 8)) {
        func_ov133_0229afec(self);
        func_ov133_0229ad68((struct UnkStruct_0229ad68 *) self, 8);
        func_ov133_0229ad78((struct Overlay133_Struct *) self, 4);
    }
    if (func_ov133_0229ad88((struct UnkStruct_0229ad88 *) self, 16)) {
        func_ov133_0229af90(self);
        func_ov133_0229ad68((struct UnkStruct_0229ad68 *) self, 16);
        func_ov133_0229ad78((struct Overlay133_Struct *) self, 4);
    }
    if (func_ov133_0229ad88((struct UnkStruct_0229ad88 *) self, 2)) {
        if (func_020b9bbc((void *) ((char *) self + 0x34c), (void *) ((char *) self + 0x394), 4, 0x800, 0)) {
            func_ov133_0229ad68((struct UnkStruct_0229ad68 *) self, 2);
        }
    }
    if (func_ov133_0229ad88((struct UnkStruct_0229ad88 *) self, 4)) {
        if (func_020b9bbc((void *) ((char *) self + 0x370), (void *) ((char *) self + 0xb94), 6, 0x800, 0)) {
            func_ov133_0229ad68((struct UnkStruct_0229ad68 *) self, 4);
        }
    }
}

int func_ov133_0229ae94(UnkStruct_0229ae94 *self)
{
    func_ov133_0229ae1c((char *) self);
    self->unk_A0 = self->unk_9C;
    func_ov133_0229adb8((int) self, (unsigned char) self->unk_A0);
    self->unk_9D = 0xd;
    self->unk_9E = 0x5;
    return func_ov133_0229b3f8(self, 1);
}

void func_ov133_0229ae8c(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (157))) + (0)) = 0;
}

int func_ov133_0229ae5c(unsigned char *p)
{
    if (p[0x9D] == 0) {
        goto ret0;
    }
    p[0x9D]--;
    if (p[0x9D] != 0) {
        goto ret0;
    }
    p[0x9D] = 2;
    return 1;
ret0:
    return 0;
}

void func_ov133_0229ae1c(char *obj)
{
    func_0206fdd4(obj + 0x394, 9, 0xc, 0x15, 0x14, 2);
    func_ov133_0229ad9c((int) obj, 0xb);
    func_ov133_0229ad9c((int) obj, 0xa);
    func_ov133_0229ad78((struct Overlay133_Struct *) obj, 2);
}

void func_ov133_0229adc4(char *self, int p1, int p2)
{
    int idx = p1 % 3;
    char *p = data_ov133_0229c79c[idx];
    char *q;
    int v;

    if (idx == 0) {
        q = p + 4;
    } else {
        q = p + 3;
    }

    v = data_ov133_0229c814[p1];
    func_0206fdd4(self + 0x394, (int) p, v, (int) q, v + 1, p2);
    func_ov133_0229ad78((struct Overlay133_Struct *) self, 2);
}

void func_ov133_0229adb8(int a, int b)
{
    func_ov133_0229adc4((char *) a, b, 3);
}

void func_ov133_0229ad9c(int a, int b)
{
    func_ov133_0229adc4((char *) a, b, ((unsigned char) (b + 0xf6) <= 1) ? 1 : 2);
}

int func_ov133_0229ad88(struct UnkStruct_0229ad88 *p, unsigned int mask)
{
    if ((p->flags & mask) == 0) {
        return 0;
    }
    return 1;
}

void func_ov133_0229ad78(struct Overlay133_Struct *obj, unsigned short val)
{
    obj->flags |= val;
}

void func_ov133_0229ad68(struct UnkStruct_0229ad68 *p, unsigned short mask)
{
    unsigned short tmp;

    tmp = p->unk_98;
    p->unk_98 = tmp & ~mask;
}
