/* talk_object_12: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206812c @ 0x0206812c, 0x18 bytes, Thumb
 * func_02068114 @ 0x02068114, 0x18 bytes, Thumb
 * func_02068104 @ 0x02068104, 0x10 bytes, Thumb
 * func_020680ec @ 0x020680ec, 0x18 bytes, Thumb
 * func_020680d0 @ 0x020680d0, 0x1c bytes, Thumb
 * func_0206807c @ 0x0206807c, 0x54 bytes, Thumb
 * func_02068058 @ 0x02068058, 0x24 bytes, Thumb
 * func_02068034 @ 0x02068034, 0x24 bytes, Thumb
 * func_02068010 @ 0x02068010, 0x24 bytes, Thumb
 * func_02067fd4 @ 0x02067fd4, 0x3c bytes, Thumb
 * func_02067fa4 @ 0x02067fa4, 0x30 bytes, Thumb
 * func_02067f74 @ 0x02067f74, 0x30 bytes, Thumb
 * func_02067f28 @ 0x02067f28, 0x4a bytes, Thumb
 */

typedef struct {
    char data[0x60];
} SomeObject;

typedef struct {
    char pad_00[0x1a64];
    int unk_1A64;
    char pad_1A68[0x10];
    char unk_1A78;
} Some;

struct UnkStruct_02068058 {
    char pad_00[0x1a69];
    unsigned char byte;
    char pad_1A6A[0x4e];
    void *unk_1AB8;
};

typedef struct UnkStruct_02067fd4 {
    unsigned char pad_00[0x1a6b];
    unsigned char byte;
    unsigned char pad_1A6C[0x1bb0 - 0x1a6b - 1];
    unsigned char data[1];
} UnkStruct_02067fd4;

struct func_02067fa4_s {
    char pad_00[0x1a6a];
    unsigned char b;
    char pad_1A6B[0x185];
    char arr[1];
};

extern void func_020690d8(void *ptr);
extern void func_020a9ce0(void *ptr);
extern int func_0203d4a8(void);
extern void func_02068ad0(int a, int b);
extern void func_02068ae4(void *ptr, int arg);
extern void *func_020a8228(void *);
extern int func_020b45d0(void *, int, int, int, int, unsigned char);
extern int func_020a8be4(void *, void *);
extern int func_020a89dc(void *, void *);
extern void *func_020a8210(void *);
extern char data_020cce80[];
extern int func_020b44bc(void **, unsigned char);
extern int func_020b44a4(unsigned char *dest, unsigned char value);
extern void func_020b44d4(void *p, int x, int y);

void func_0206812c(void *arg)
{
    void *ptr = arg;
    func_020690d8((char *) ptr + 0x1c);
    func_020a9ce0((char *) ptr + 0xb4);
}

int func_02068114(void)
{
    int result;
    if (func_0203d4a8() == 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void func_02068104(int a, int b)
{
    func_02068ad0(a + 0x1a2c, b);
}

void func_020680ec(unsigned char *base, int flag)
{
    if (flag) {
        base[0x1e97] = 1;
    } else {
        base[0x1e97] = 0;
    }
}

void func_020680d0(char *base)
{
    base[0x1e97] = 0;
    func_02068ae4(base + 0x1a2c, 1);
}

char *func_0206807c(Some *self)
{
    SomeObject local;
    func_020a8228(&local);
    func_020b45d0(&local, self->unk_1A64, 2, 6, 0, 0);
    func_020a8be4(&self->unk_1A78, data_020cce80);
    func_020a89dc(&self->unk_1A78, &local);
    func_020a8210(&local);
    return &self->unk_1A78;
}

void *func_02068058(struct UnkStruct_02068058 *p)
{
    func_020b44bc(&p->unk_1AB8, p->byte);
    return (void *) &p->unk_1AB8;
}

unsigned char *func_02068034(unsigned char *arg)
{
    func_020b44a4(arg + 0x1b14, arg[0x1a68]);
    return arg + 0x1b14;
}

void *func_02068010(char *p)
{
    func_020b44d4(p + 0x1b54, *(int *) (p + 0x1a6c), 0);
    return p + 0x1b54;
}

unsigned char *func_02067fd4(UnkStruct_02067fd4 *self)
{
    unsigned int b = self->byte;
    if (b >= 12) {
        b -= 12;
    }
    if (b == 0) {
        b = 12;
    }
    func_020b45d0(self->data, b, 2, 0, 0, 0);
    return self->data;
}

char *func_02067fa4(struct func_02067fa4_s *self)
{
    func_020b45d0((void *) self->arr, (unsigned char) self->b, 2, 0, 9, 0);
    return self->arr;
}

void *func_02067f74(char *self)
{
    func_020b45d0(self + 0x1c30, *(unsigned int *) (self + 0x1a70), 2, 0, 0, 0);
    return self + 0x1c30;
}

void func_02067f28(void *r0, int r1, int r2, int r3, int r4)
{
    unsigned short *p0 = (unsigned short *) ((char *) r0 + 0xa0);
    *p0 = 0;
    *(int *) ((char *) r0 + 0xa4) = r1;
    *(int *) ((char *) r0 + 0xa8) = r2;
    *(int *) ((char *) r0 + 0xac) = r3;
    *(int *) ((char *) r0 + 0xb0) = r4;
    *(int *) ((char *) r0 + 0xa8) = *(int *) ((char *) r0 + 0xa8) * 3;
    *(int *) ((char *) r0 + 0xa8) = *(int *) ((char *) r0 + 0xa8) >> 1;
}
