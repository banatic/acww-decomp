/* bbs_write_scene_2: 20 functions, module ov112
 * mwccarm 1.2/base -O4,s
 * func_ov112_022a1978 @ 0x022a1978, 0x74 bytes, Thumb
 * func_ov112_022a1974 @ 0x022a1974, 0x4 bytes, Thumb
 * func_ov112_022a1970 @ 0x022a1970, 0x4 bytes, Thumb
 * func_ov112_022a1960 @ 0x022a1960, 0x10 bytes, Thumb
 * func_ov112_022a189c @ 0x022a189c, 0xc4 bytes, Thumb
 * func_ov112_022a1808 @ 0x022a1808, 0x94 bytes, Thumb
 * func_ov112_022a17a8 @ 0x022a17a8, 0x60 bytes, Thumb
 * func_ov112_022a1758 @ 0x022a1758, 0x4e bytes, Thumb
 * func_ov112_022a1700 @ 0x022a1700, 0x58 bytes, Thumb
 * func_ov112_022a16c0 @ 0x022a16c0, 0x3e bytes, Thumb
 * func_ov112_022a168c @ 0x022a168c, 0x34 bytes, Thumb
 * func_ov112_022a1664 @ 0x022a1664, 0x26 bytes, Thumb
 * func_ov112_022a1600 @ 0x022a1600, 0x64 bytes, Thumb
 * func_ov112_022a15a0 @ 0x022a15a0, 0x5e bytes, Thumb
 * func_ov112_022a1520 @ 0x022a1520, 0x80 bytes, Thumb
 * func_ov112_022a14d8 @ 0x022a14d8, 0x48 bytes, Thumb
 * func_ov112_022a145c @ 0x022a145c, 0x7c bytes, Thumb
 * func_ov112_022a13f4 @ 0x022a13f4, 0x68 bytes, Thumb
 * func_ov112_022a1310 @ 0x022a1310, 0xe4 bytes, Thumb
 * func_ov112_022a12dc @ 0x022a12dc, 0x34 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_022a1978 {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
} UnkStruct_022a1978;

struct UnkStruct_022a1808 {
    char pad_to_A0[0xA0];
    unsigned int unk_A0;
    unsigned int unk_A4;
    unsigned int unk_A8;
};

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    char pad_A4[4];
    int unk_A8;
} UnkStruct_022a17a8;

struct UnkStruct_022a168c {
    char pad_00[0xA8];
    int unk_A8;
};

typedef struct {
    char pad_00[0xA8];
    int unk_A8;
} UnkStruct_022a1664;

struct UnkStruct_022a1600 {
    char pad_00[0xA0];
    int unk_A0;
    char pad_A4[4];
    int unk_A8;
};

typedef struct {
    unsigned char pad_00[0xa0];
    u32 unk_A0;
    u32 pad_A4;
    u32 unk_A8;
} UnkStruct_022a15a0;

struct UnkStruct_022a1520 {
    char pad_00[0xA4];
    int unk_A4;
    int unk_A8;
};

struct UnkStruct_022a14d8 {
    char pad_00[0xA4];
    int unk_A4;
    int unk_A8;
};

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
} UnkStruct_022a145c;

typedef struct {
    char pad_00[0xA0];
    int unk_A0;
    int unk_A4;
    int unk_A8;
} UnkStruct_022a13f4;

extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern void func_ov112_0229ff5c(UnkStruct_022a1978 *p);
extern void func_ov112_022a12a4(UnkStruct_022a1978 *p);
extern void func_ov112_022a19ec(UnkStruct_022a1978 *p);
extern void func_020ee470(void *parameter0);
extern void func_ov112_022a11f4(void);
extern void func_ov112_022a1104(void *self);
extern void func_ov112_0229fbc0(void *self);
extern void func_ov112_0229fe60(void *self, int arg);
extern void func_ov095_0229c420(void *ptr, int a);
extern void func_ov095_0229bf7c(void *ptr, int a);
extern void func_ov002_02207f20(void *self, int a, int b, int c, int d);
extern void func_02002708(int a);
extern void func_ov002_02207e80(void *self, int a, int b, int c);
extern void func_ov002_02208090(void *self, int a);
extern int func_ov002_02207f60(void *self);
extern int func_ov002_0220acc4(void *ptr);
extern void func_ov112_0229fd20(void *self);
extern void func_ov112_022a122c(void *self);
extern int func_ov112_0229fe70(struct UnkStruct_022a1808 *param, unsigned int arg);
extern void func_ov112_0229f11c(struct UnkStruct_022a1808 *param);
extern void func_ov112_0229f0ec(struct UnkStruct_022a1808 *param);
extern void func_ov112_0229f6e4(struct UnkStruct_022a1808 *param);
extern int func_ov112_0229fefc(struct UnkStruct_022a1808 *param);
extern void func_ov112_0229fb7c(UnkStruct_022a17a8 *param, int arg);
extern int func_ov002_02207f3c(void *a, int b);
extern void func_020027f0(int a);
extern void func_ov112_0229fe50(void *a, int b);
extern int func_ov002_02207f48(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern int func_0206fe60(void);
extern int func_ov112_0229fee4(void *p);
extern void func_ov112_0229fe84(void *p);
extern int func_ov112_0229efbc(void *);
extern void func_ov112_0229f058(void *);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
int func_ov112_0229fb70(void *self);
extern void func_ov095_0229c084(void *, int);
extern void func_02051bf8(void *, int);
extern void *func_02070c08(void *);
extern int func_020984e8(void);
extern void *func_02094fd4(void *);
extern int func_02099870(int);
extern void *func_02095074(int, void *);
extern void *func_020b496c(int, void *);
extern int func_0207094c(void *, int);
extern void *func_020707d0(void *);
extern int func_020a87e0(void *, void *);
extern int func_02051c8c_unk(void *, int);
extern void func_02051c08(void *, void *, int);
extern void func_ov002_0220a580(void *);
extern void MI_CpuFill8(void *, int, int);
extern void *func_020707b8(void *);
extern void *func_02094fbc(void *);
extern int **func_02070be8(void *);
extern void func_ov112_0229fbf4(void *arg0);
extern void func_ov095_0229c05c(void *);
extern void func_020b9ccc(void *);
extern void func_ov002_0220af74(void *);

int func_ov112_022a1978(UnkStruct_022a1978 *p)
{
    func_0206f58c();
    if (func_0206f56c() != 0) {
        switch (p->unk_8D) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 9:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 17:
            case 19:
                func_ov112_0229ff5c(p);
                return 1;
            case 7:
            case 8:
            case 10:
            case 16:
            case 18:
                break;
        }
    }
    func_ov112_022a12a4(p);
    func_ov112_022a19ec(p);
    func_ov112_022a122c((void *) p);
    return 1;
}

int func_ov112_022a1974(void)
{
    return 1;
}

int func_ov112_022a1970(void)
{
    return 1;
}

int func_ov112_022a1960(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov112_022a189c(void *self)
{
    func_ov112_022a11f4();
    func_ov112_022a1104(self);
    func_ov112_0229fbc0(self);
    func_ov112_0229fe60(self, 0x4000);
    func_ov095_0229c420((char *) self + 0x384, 6);
    func_ov095_0229bf7c((char *) self + 0x384, 6);
    func_ov002_02207f20(self, 10, 7, 0, 0x30);
    func_02002708(4);
    func_02002708(6);
    func_ov002_02207e80(self, 4, 0, ~7);
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02208090(self, 1);
    *(unsigned int *) ((char *) self + 0xa0) = func_ov002_02207f60(self);
    *(unsigned int *) ((char *) self + 0xa4) = *(unsigned int *) ((char *) self + 0xa0);
    *(unsigned int *) ((char *) self + 0xa8) = *(unsigned int *) ((char *) self + 0xa4);
    func_ov112_0229fe60(self, 0x81);
    func_ov002_0220acc4((char *) self + 0x427c);
    func_ov112_0229fd20(self);
    func_ov112_022a122c(self);
}

void func_ov112_022a1808(struct UnkStruct_022a1808 *param)
{
    if (func_ov112_0229fe70(param, 0x4000) != 0) {
        func_ov112_0229f11c(param);
        func_ov112_0229f0ec(param);
        func_ov112_0229fe50((void *) param, 0x4000);
    }
    if (func_ov002_02207f48((void *) param, 0) != 0) {
        func_ov112_0229f6e4(param);
        func_ov002_022080a0((void *) param, 2);
        func_ov112_0229fefc(param);
        func_ov112_0229fd20((void *) param);
        func_ov112_022a122c((void *) param);
    }
    func_ov002_02207e80((void *) param, 4, 0, -8);
    func_ov002_02207e80((void *) param, 6, 0, 0);
    param->unk_A0 = (unsigned int) func_ov002_02207f60((void *) param);
    param->unk_A4 = param->unk_A0;
    param->unk_A8 = param->unk_A4;
}

void func_ov112_022a17a8(UnkStruct_022a17a8 *param)
{
    func_ov112_0229fe50((void *) param, 0x40);
    func_ov002_02207f04((void *) param, 8, 0, 0, 0x30);
    func_ov002_02207e80((void *) param, 6, 0, 0);
    func_ov002_02208090((void *) param, 3);
    param->unk_A0 = func_ov002_02207f60((void *) param);
    param->unk_A8 = param->unk_A0;
    func_ov112_0229fb7c(param, 0);
    func_ov112_0229fe50((void *) param, 0x80);
}

void func_ov112_022a1758(void *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_ov112_0229fe50(p, 1);
        func_ov002_02208090(p, 4);
    } else {
        func_ov002_02207e80(p, 6, 0, 0);
    }
    *((int *) ((char *) p + 0xa0)) = func_ov002_02207f60(p);
    *((int *) ((char *) p + 0xa8)) = *((int *) ((char *) p + 0xa0));
}

void func_ov112_022a1700(unsigned char *self)
{
    extern void func_ov112_0229f078(unsigned char *);
    extern int func_ov002_0220aa60(unsigned char *, int);
    extern void func_ov002_02207eb4(unsigned char *, int, int);

    func_ov112_0229f078(self);
    if (func_ov112_0229fe70((struct UnkStruct_022a1808 *) self, 0x2000)) {
        func_ov002_0220aa60(self + 0x427c, 0x87);
    } else {
        func_ov002_0220aa60(self + 0x427c, 0x22);
    }
    func_ov002_02207eb4(self, 5, 0);
    *(int *) (self + 0xa8) = func_ov002_02207f60((void *) self);
    func_ov002_02208090((void *) self, 5);
}

void func_ov112_022a16c0(void *p)
{
    if (func_ov002_02207f48(p, -1) != 0) {
        (void) func_ov002_022080a0(p, 2);
        if (func_0206fe60() != 0) {
            func_ov112_0229fee4(p);
        } else {
            func_ov112_0229fe84(p);
        }
    }
    *(int *) ((char *) p + 0xa8) = func_ov002_02207f60(p);
}

void func_ov112_022a168c(struct UnkStruct_022a168c *obj)
{
    func_ov112_0229f058((void *) obj);
    func_ov002_02207f04((void *) obj, 0, 0, 0, 0x30);
    func_ov002_02208090((void *) obj, 7);
    obj->unk_A8 = func_ov002_02207f60((void *) obj);
}

void func_ov112_022a1664(UnkStruct_022a1664 *param)
{
    if (func_ov002_02207f3c((void *) param, 0) != 0) {
        func_ov002_02208090((void *) param, 8);
    }
    param->unk_A8 = func_ov002_02207f60((void *) param);
}

void func_ov112_022a1600(struct UnkStruct_022a1600 *param)
{
    func_ov002_02207f20((void *) param, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80((void *) param, 6, 0, 0);
    func_ov002_02208090((void *) param, 9);
    param->unk_A0 = func_ov002_02207f60((void *) param);
    param->unk_A8 = param->unk_A0;
    func_ov112_0229fe60((void *) param, 1);
    func_ov002_0220acc4((char *) param + 0x427C);
}

void func_ov112_022a15a0(UnkStruct_022a15a0 *p)
{
    int zero = 0;

    if (func_ov002_02207f48(p, 0) != 0) {
        func_ov112_0229f6e4((struct UnkStruct_022a1808 *) p);
        func_ov002_022080a0(p, 2);
        func_ov112_0229fefc((struct UnkStruct_022a1808 *) p);
        func_ov112_0229fd20(p);
        func_ov112_022a122c(p);
        func_ov112_0229fe60(p, 0x80);
    }

    func_ov002_02207e80(p, 6, zero, zero);
    p->unk_A0 = func_ov002_02207f60(p);
    p->unk_A8 = p->unk_A0;
}

void func_ov112_022a1520(struct UnkStruct_022a1520 *obj)
{
    if (func_ov112_0229fe70((struct UnkStruct_022a1808 *) obj, 0x2000) != 0 || func_ov112_0229efbc(obj) != 0) {
        func_ov112_0229fe50(obj, 0x40);
        func_ov112_0229f058(obj);
        func_ov092_02299324(func_020ee45c(obj), 0x44, 1);
        func_ov002_02207f04(obj, 2, 0, 0, 0x30);
        func_ov002_02207e80(obj, 4, 0, -8);
        func_ov002_02208090(obj, 0xb);
        obj->unk_A4 = func_ov002_02207f60(obj);
        obj->unk_A8 = obj->unk_A4;
    }
}

void func_ov112_022a14d8(struct UnkStruct_022a14d8 *self)
{
    if (func_ov002_02207f3c((void *) self, 0) != 0) {
        func_020027f0(4);
        func_ov002_022080a0((void *) self, 5);
    } else {
        func_ov002_02207e80((void *) self, 4, 0, -8);
    }
    self->unk_A4 = func_ov002_02207f60((void *) self);
    self->unk_A8 = self->unk_A4;
}

void func_ov112_022a145c(UnkStruct_022a145c *self)
{
    if (func_ov112_0229fb70(self)) {
        return;
    }
    func_ov112_0229fe50(self, 0x40);
    func_ov112_0229f058(self);
    func_ov092_02299324(func_020ee45c(self), 0x44, 1);
    func_ov002_02207f04(self, 0xa, 0, 0, 0x30);
    func_ov002_02207e80(self, 4, 0, -8);
    func_ov002_02207e80(self, 6, 0, -8);
    func_ov002_02208090(self, 0xd);
    self->unk_A4 = func_ov002_02207f60(self);
    self->unk_A8 = self->unk_A4;
}

void func_ov112_022a13f4(UnkStruct_022a13f4 *p)
{
    if (func_ov002_02207f3c((void *) p, 0)) {
        func_020027f0(4);
        func_020027f0(6);
        func_ov002_022080a0((void *) p, 5);
    } else {
        func_ov002_02207e80((void *) p, 4, 0, -8);
        func_ov002_02207e80((void *) p, 6, 0, -8);
    }
    p->unk_A4 = func_ov002_02207f60((void *) p);
    p->unk_A8 = p->unk_A4;
    p->unk_A0 = p->unk_A4;
}

void func_ov112_022a1310(char *self)
{
    struct {
        u8 a[0x20];
        u8 b[0x6c];
        u8 c[0x0c];
        u8 d[0x54];
    } s;
    int r4;

    *(u32 *) (self + 0xac) = 0;

    func_ov095_0229c084(self + 0x384, 2);
    func_02051bf8(self + 0xc4, 0x60);

    func_02070c08(s.b);
    r4 = func_020984e8();
    func_02094fd4(s.a);
    func_02095074(func_02099870(r4), s.a);
    func_020b496c(0, s.a);

    func_0207094c(s.b, 0x89);
    func_020707d0(s.c);
    func_020a87e0(s.c, s.b);

    r4 = func_02051c8c_unk(&s.d[2], 0x10);
    func_02051c08(&s.d[2], self + 0xc4, r4);

    for (; r4 < 0x10; r4++) {
        ((u16 *) (self + 0xc4))[r4] = 0x3000;
    }

    *(u8 *) (self + 0xc0) = 0x10;

    func_ov002_0220a580(self + 0x4234);
    MI_CpuFill8(self + 0x4e50, 0xdd, 0x1e00);

    *(u8 *) (self + 0xb6) = 0;
    *(u8 *) (self + 0xb7) = 0;
    *(u8 *) (self + 0xb8) = 0;

    func_020707b8(s.c);
    func_02094fbc(s.a);
    func_02070be8(s.b);
}

void func_ov112_022a12dc(void *self)
{
    func_ov112_0229fbf4((void *) self);
    func_ov095_0229c05c((char *) self + 0x384);
    func_020b9ccc((char *) self + 0x360);
    func_ov002_0220af74((char *) self + 0x427c);
}
