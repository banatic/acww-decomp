/* villager_house: 10 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221d594 @ 0x0221d594, 0x38 bytes, Thumb
 * func_ov003_0221d55c @ 0x0221d55c, 0x38 bytes, Thumb
 * func_ov003_0221d558 @ 0x0221d558, 0x4 bytes, Thumb
 * func_ov003_0221d544 @ 0x0221d544, 0x12 bytes, Thumb
 * func_ov003_0221d530 @ 0x0221d530, 0x12 bytes, Thumb
 * func_ov003_0221d43c @ 0x0221d43c, 0xf4 bytes, Thumb
 * func_ov003_0221d3a4 @ 0x0221d3a4, 0x98 bytes, Thumb
 * func_ov003_0221d2b0 @ 0x0221d2b0, 0xf4 bytes, Thumb
 * func_ov003_0221d2ac @ 0x0221d2ac, 0x4 bytes, Thumb
 * func_ov003_0221d2a8 @ 0x0221d2a8, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xec];
    char unk_EC;
    char pad_ED[0x10a - 0xed];
    u8 unk_10A;
    char pad_10B[0x12c - 0x10b];
    int unk_12C;
    char pad_130[0x136 - 0x130];
    u16 unk_136;
    char pad_138[0x236 - 0x138];
    unsigned char f236_a : 1;
    unsigned char f236_b : 1;
    unsigned char f236_c : 6;
    u8 unk_237;
} UnkStruct_0221d43c;

typedef struct {
    char b[0x20];
} Buf;

typedef struct {
    int pad_00;
    Buf b;
} BufW;

typedef struct {
    char pad_00[0x136];
    unsigned short unk_136;
} UnkStruct_0221d2b0;

extern int func_ov003_0221d64c(void *);
extern int func_ov003_0221d5cc(void *);
extern int func_ov003_022203dc(void);
extern int func_02064328(char *, char *, int, int, int);
extern char data_ov003_0223c948[];
extern char data_ov003_022390a0[];
extern int data_ov003_0223c970[];
extern int data_ov003_02239084[];
extern int func_ov003_022203c0(void);
extern void *func_ov003_0221ffb0(void *argument0);
extern int func_ov003_0221ffac(void *argument0);
extern void *func_0207cec0(void *p, int idx);
extern void func_020a8164(void *p, void *q);
extern int func_0207f1d4(void *h);
extern int func_0208150c(void *h);
extern int func_020036e8(int q);
extern void *func_02094fd4(Buf *b);
extern int func_02003618(int a, Buf *b);
extern void func_02068404(int a, int b, Buf *c);
extern void *func_02094fbc(Buf *b);
extern char data_021e5a2c[];
extern char data_ov003_02239064[];
extern char data_ov003_02239074[];
extern u8 data_ov003_0223664c[];
extern u8 data_ov003_02236644[];
extern int func_0207f1d8(void *);
extern int func_ov009_02264c40(void *self);
extern int func_02073dd4(void *g, unsigned int i);
extern void func_020a6e4c(unsigned int i, unsigned char *a, unsigned char *b, unsigned char *c);
extern int func_020b66c4(unsigned char v);
extern void *data_020ccf94;

char *func_ov003_0221d594(void *param)
{
    int a = func_ov003_0221d64c(param);
    int b = func_ov003_0221d5cc(param);
    int c = func_ov003_022203dc();
    func_02064328(data_ov003_0223c948, data_ov003_022390a0, a >> 2, b, c);
    return data_ov003_0223c948;
}

int *func_ov003_0221d55c(int arg)
{
    int ret1 = func_ov003_0221d64c((void *) arg);
    int ret2 = func_ov003_0221d5cc((void *) arg);
    int ret3 = func_ov003_022203dc();
    func_02064328((char *) data_ov003_0223c970, (char *) data_ov003_02239084, ret1 >> 2, ret2, ret3);
    return data_ov003_0223c970;
}

int func_ov003_0221d558(void)
{
    return 0;
}

void func_ov003_0221d544(void)
{

    func_ov003_0221ffb0((void *) func_ov003_022203c0());
}

void func_ov003_0221d530(void)
{

    func_ov003_0221ffac((void *) func_ov003_022203c0());
}

void func_ov003_0221d43c(UnkStruct_0221d43c *self)
{
    unsigned int ok = 0;
    u16 id;
    int idx;
    void *h;
    BufW w;

    id = self->unk_136;
    if (id >= 0x5001 && id <= 0x5008) {
        ok = 1;
    }
    if (ok != 0) {
        idx = id - 0x5001;
    } else {
        idx = -1;
    }

    h = func_0207cec0(data_021e5a2c, idx);
    func_020a8164(&self->unk_EC, data_ov003_02239064);
    if (func_0207f1d4(h) == 0) {
        self->unk_10A = 6;
    } else if (self->f236_b != 0) {
        func_020a8164(&self->unk_EC, data_ov003_02239074);
        self->unk_10A = 0;
    } else {
        int q = func_0208150c(h);
        if (q != 0) {
            if (self->unk_237 == 0) {
                self->unk_10A = data_ov003_0223664c[func_020036e8(q)];
            } else {
                self->unk_10A = data_ov003_02236644[func_020036e8(q)];
            }
        }
    }
    func_02094fd4(&w.b);
    func_02003618(func_0208150c(h), &w.b);
    func_02068404(self->unk_12C, 0, &w.b);
    func_02094fbc(&w.b);
}

int func_ov003_0221d3a4(void *p)
{
    unsigned int v;
    int idx;
    void *h;
    int ok = 0;
    v = *(unsigned short *) ((char *) p + 0x136);
    if (v >= 0x5001 && v <= 0x5008) {
        ok = 1;
    }
    if (ok) {
        idx = v - 0x5001;
    } else {
        idx = -1;
    }
    h = func_0207cec0((void *) ((unsigned char *) data_021e5a2c), idx);
    if (h != 0) {
        if (func_0207f1d4(h) == 0) {
            return 0;
        }
        if (func_0207f1d8(h) == 0 || func_0207f1d8(h) == 3 || func_0207f1d8(h) == 4 || func_0207f1d8(h) == 5 ||
            func_0207f1d8(h) == 6 || func_0207f1d8(h) == 7) {
            return 0;
        }
        return 1;
    }
    return 0;
}

int func_ov003_0221d2b0(UnkStruct_0221d2b0 *self)
{
    unsigned char b[3];
    unsigned int ok;
    unsigned short v;
    int id;
    void *p;
    void *g;
    unsigned int i;

    ok = 0;
    v = self->unk_136;
    if (v >= 0x5001 && v <= 0x5008) {
        ok = 1;
    }
    if (ok > 0) {
        id = v - 0x5001;
    } else {
        id = -1;
    }
    if (func_ov009_02264c40(self) != 0) {
        p = func_0207cec0(((int *) data_021e5a2c), id);
        if (p != 0) {
            if (func_0207f1d4(p) == 0) {
                return 0;
            }
            if (func_0207f1d8(p) == 0 || func_0207f1d8(p) == 3 || func_0207f1d8(p) == 4 || func_0207f1d8(p) == 5 ||
                func_0207f1d8(p) == 6 || func_0207f1d8(p) == 7) {
                return 0;
            }
            if (func_0207f1d8(p) == 2) {
                i = 0;
                g = data_020ccf94;
                for (; i < 4; i++) {
                    if (func_02073dd4(g, i) != 0) {
                        func_020a6e4c(i, &b[0], &b[1], &b[2]);
                        if (id == func_020b66c4(b[0])) {
                            return 1;
                        }
                    }
                }
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int func_ov003_0221d2ac(void)
{
    return 1;
}

int func_ov003_0221d2a8(void)
{
    return 1;
}
