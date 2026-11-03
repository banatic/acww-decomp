/* letter_reader: 19 functions, module ov091
 * mwccarm 1.2/base -O4,s
 * func_ov091_022992f4 @ 0x022992f4, 0x4 bytes, Thumb
 * func_ov091_022992f0 @ 0x022992f0, 0x4 bytes, Thumb
 * func_ov091_022992e0 @ 0x022992e0, 0x10 bytes, Thumb
 * func_ov091_02299244 @ 0x02299244, 0x9c bytes, Thumb
 * func_ov091_022991e8 @ 0x022991e8, 0x5c bytes, Thumb
 * func_ov091_022991b0 @ 0x022991b0, 0x38 bytes, Thumb
 * func_ov091_0229914c @ 0x0229914c, 0x64 bytes, Thumb
 * func_ov091_022990f4 @ 0x022990f4, 0x58 bytes, Thumb
 * func_ov091_022990b0 @ 0x022990b0, 0x42 bytes, Thumb
 * func_ov091_02299064 @ 0x02299064, 0x4c bytes, Thumb
 * func_ov091_02299058 @ 0x02299058, 0xc bytes, Thumb
 * func_ov091_02299054 @ 0x02299054, 0x2 bytes, Thumb
 * func_ov091_02299050 @ 0x02299050, 0x2 bytes, Thumb
 * func_ov091_02299004 @ 0x02299004, 0x4c bytes, Thumb
 * func_ov091_02298fb4 @ 0x02298fb4, 0x50 bytes, Thumb
 * func_ov091_02298fa8 @ 0x02298fa8, 0xc bytes, Thumb
 * func_ov091_02298f9c @ 0x02298f9c, 0xc bytes, Thumb
 * func_ov091_02298f5c @ 0x02298f5c, 0x40 bytes, Thumb
 * func_ov091_02298f20 @ 0x02298f20, 0x3c bytes, Thumb
 */

typedef struct {
    char pad_before[0x8c];
    unsigned char unk_8C;
    char pad_after[0x3bc - 0x8d];
} UnkStruct_02299004;

typedef struct UnkStruct_02298fb4 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0x434 - 0x8c - 1];
    char sub[1];
} UnkStruct_02298fb4;

typedef struct Global {
    unsigned char pad_00[2];
    unsigned short flags;
} Global;

extern void func_020ee470(void *parameter0);
extern void func_0200467c(int);
extern unsigned int data_021c526c;
extern void func_02036470(unsigned int, int);
extern void func_02001c30(int);
extern int func_0206fcbc(void);
extern void func_0206e230(unsigned char *, int, int, int, int);
extern void func_ov002_02207ee8(char *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(unsigned char *, int, int, int);
extern void func_020028bc(int, int, int, int);
extern int func_ov002_02207f48(unsigned char *, int);
extern unsigned char *func_ov002_022080a0(unsigned char *, unsigned char value);
extern void func_ov002_0220a374(unsigned char *, int);
extern int func_0206fe60(void);
extern int func_0208e484(void *ptr);
extern void func_0208f0c4(void *ptr, int value);
extern void func_ov002_02208090(void *ptr, int value);
extern int func_ov002_0220b57c(void *);
extern int func_0208e4bc(void *);
extern int func_ov002_0220b5ec(void *, int);
extern int func_ov002_0220b59c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_02036468(char *);
extern void func_ov002_02207ecc(void *, int, int, int, int);
extern int func_ov002_02207f3c(int a, int b);
extern void func_020027f0(int a);
extern void func_0206e2ec(void *p0, int p1);
extern void func_ov002_0220b53c(void *p0, int p1);
extern void func_0206e2e4(char *object);
extern int func_ov002_02208054(UnkStruct_02299004 *self, int a);
extern int func_ov002_0220b498(void *);
extern int func_ov002_02208014(void *receiver);
extern void func_ov002_0220a1dc(void *p);
extern Global data_021fbe40;
extern unsigned char *func_ov002_02208098(int, unsigned char value);
extern void *data_ov091_02299530;
extern void *func_ov002_02209c60(void *ptr);
extern void *func_ov002_0220b410(void *ptr);
extern void *func_0206e35c(void *ptr);
extern void *func_ov002_0220826c(void *ptr);
extern void func_ov002_02207f6c(void *ptr);

void func_ov091_02298fa8(int a);
void func_ov091_02298f9c(int p0);

int func_ov091_022992f4(void)
{
    return 1;
}

int func_ov091_022992f0(void)
{
    return 1;
}

int func_ov091_022992e0(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov091_02299244(unsigned char *param)
{
    int t;

    func_0200467c(1);
    func_02036470(data_021c526c + 0x1c4, 0);
    func_02001c30(0);
    t = func_0206fcbc();
    func_0206e230(param + 0x94, t, 0, 2, 1);
    func_ov002_02207ee8((char *) (param), 10, 0, 0, 0x30);
    func_02002708(0);
    func_ov002_02207e80(param, 0, 0, 0);
    func_020028bc(0, 0, 0, 0);
    func_02002708(2);
    func_ov002_02207e80(param, 2, 0, 0);
    func_020028bc(2, 0, 0, 0);
    func_ov002_02208090((void *) param, 1);
}

void func_ov091_022991e8(unsigned char *self)
{
    if (func_ov002_02207f48(self, 1) != 0) {
        func_ov002_022080a0(self, 2);
        func_ov002_0220a374(self + 0x434, 1);
        if (func_0206fe60() != 0) {
            func_ov002_02208098((int) self, 0);
        } else {
            func_ov002_02208098((int) self, 1);
        }
    }
    func_ov002_02207e80(self, 0, 0, 0);
    func_ov002_02207e80(self, 2, 0, 0);
}

void func_ov091_022991b0(void *obj)
{
    if (func_0208e484((char *) obj + 0x434)) {
        func_0208f0c4((char *) obj + 0x3bc, 2);
        func_ov002_02208090(obj, 3);
        func_0200467c(0x27);
    }
}

void func_ov091_0229914c(void *p)
{
    if (func_ov002_0220b57c((char *) p + 0x3bc)) {
        if (func_0208e4bc((char *) p + 0x434)) {
            int a, b;
            a = func_ov002_0220b5ec((char *) p + 0x3bc, 1);
            b = func_ov002_0220b59c((char *) p + 0x3bc, 1);
            func_ov002_0220a0b4((char *) p + 0x434, a, b);
        }
    } else {
        func_ov002_0220a374((unsigned char *) ((char *) p + 0x434), 0);
        func_ov002_02208090(p, 4);
    }
}

void func_ov091_022990f4(void *self)
{
    int zero = 0;
    func_0200467c(2);
    func_02036468((*(char * *) &data_021c526c) + 0x1c4);
    func_ov002_02207ecc(self, 10, zero, zero, 0x30);
    func_ov002_02207e80((unsigned char *) self, zero, zero, zero);
    func_ov002_02207e80((unsigned char *) self, 2, zero, zero);
    func_ov002_02208090(self, 5);
}

void func_ov091_022990b0(int param)
{
    if (func_ov002_02207f3c(param, 1) != 0) {
        func_020027f0(0);
        func_020027f0(2);
        func_ov002_022080a0((unsigned char *) param, 5);
    } else {
        func_ov002_02207e80((unsigned char *) param, 0, 0, 0);
        func_ov002_02207e80((unsigned char *) param, 2, 0, 0);
    }
}

void func_ov091_02299064(void *self)
{
    int r4;
    int r2;
    void *p;

    func_0206e2ec((char *) self + 0x94, 0);
    func_ov002_0220b53c((char *) self + 0x3bc, 0x65);
    r4 = func_ov002_0220b5ec((char *) self + 0x3bc, 1);
    r2 = func_ov002_0220b59c((char *) self + 0x3bc, 1);
    p = (char *) self + 0x434;
    func_ov002_0220a0b4(p, r4, r2);
}

void func_ov091_02299058(char *object)
{
    func_0206e2e4(object + 0x94);
}

void func_ov091_02299054(void) {}

void func_ov091_02299050(void) {}

void func_ov091_02299004(UnkStruct_02299004 *self)
{
    if (func_ov002_02208054(self, 1)) {
        func_ov091_02298f9c((int) self);
        return;
    }
    if (func_ov002_0220b498((void *) ((char *) self + 0x3bc))) {
        func_0208f0c4((void *) ((char *) self + 0x3bc), 2);
        self->unk_8C = 3;
        func_ov002_022080a0((unsigned char *) self, 1);
        func_0200467c(0x27);
    }
}

void func_ov091_02298fb4(UnkStruct_02298fb4 *p)
{
    if (func_ov002_02208014(p)) {
        func_ov091_02298fa8((int) p);
        return;
    }
    {
        unsigned short f = data_021fbe40.flags;
        if ((f & 1) || (f & 2)) {
            func_ov002_0220a1dc(&p->sub);
            p->unk_8C = 2;
            func_ov002_022080a0((unsigned char *) p, 1);
        }
    }
}

void func_ov091_02298fa8(int a)
{
    func_ov002_02208098(a, 0);
}

void func_ov091_02298f9c(int p0)
{
    func_ov002_02208098(p0, 1);
}

void *func_ov091_02298f5c(void *self)
{
    ((int *) self)[0] = (int) &data_ov091_02299530;
    func_ov002_02209c60((char *) self + 0x434);
    func_ov002_0220b410((char *) self + 0x3bc);
    func_0206e35c((char *) self + 0x94);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov091_02298f20(void *self)
{
    *(int *) self = (int) ((int *) &data_ov091_02299530);
    func_ov002_02209c60((char *) self + 0x434);
    func_ov002_0220b410((char *) self + 0x3bc);
    func_0206e35c((char *) self + 0x94);
    func_ov002_0220826c(self);
    return self;
}
