/* astro_talk_4: 10 functions, module ov046
 * mwccarm 1.2/base -O4,s
 * func_ov046_02261508 @ 0x02261508, 0x88 bytes, Thumb
 * func_ov046_022614e8 @ 0x022614e8, 0x20 bytes, Thumb
 * func_ov046_02261424 @ 0x02261424, 0xc4 bytes, Thumb
 * func_ov046_022613c8 @ 0x022613c8, 0x5c bytes, Thumb
 * func_ov046_02261378 @ 0x02261378, 0x50 bytes, Thumb
 * func_ov046_0226131c @ 0x0226131c, 0x5c bytes, Thumb
 * func_ov046_02261304 @ 0x02261304, 0x18 bytes, Thumb
 * func_ov046_022612ec @ 0x022612ec, 0x18 bytes, Thumb
 * func_ov046_022612cc @ 0x022612cc, 0x20 bytes, Thumb
 * func_ov046_022612a0 @ 0x022612a0, 0x2c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a, b;
} UnkStruct_02261508;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
} UnkStruct_022614e8;

typedef struct UnkStruct_02261424_2 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xc0 - 0x44];
    int unk_C0;
    u8 unk_C4;
    u8 unk_C5;
} UnkStruct_02261424_2;

typedef struct UnkStruct_02261424 {
    u8 b[16];
} UnkStruct_02261424;

typedef struct UnkStruct_022613c8 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xc0 - 0x44];
    void *unk_C0;
} UnkStruct_022613c8;

typedef struct UnkStruct_02261378 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xc4 - 0x44];
    char unk_C4;
    char unk_C5;
} UnkStruct_02261378;

typedef struct UnkStruct_0226131c {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xc0 - 0x44];
    void *unk_C0;
} UnkStruct_0226131c;

typedef struct UnkStruct_02261304 UnkStruct_02261304;

struct UnkStruct_02261304 {
    void *unk_00;
};

typedef struct {
    void *vtable;
} UnkStruct_022612cc;

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    char pad_00[0xb8];
    Pair pair;
    int c0;
} UnkStruct_022612a0;

extern int data_ov046_0226245c;
extern UnkStruct_02261508 data_ov046_02262464[];
extern UnkStruct_02261508 data_ov046_02261f98;
extern UnkStruct_02261508 data_ov046_02261f90;
extern UnkStruct_02261508 data_ov046_02261f28;
extern UnkStruct_02261508 data_ov046_02261f58;
extern UnkStruct_02261508 data_ov046_02261f68;
extern unsigned char data_ov046_02261fe8[];
extern int func_0206fc6c(void);
extern void func_020b12e0(int *out, int a);
extern void func_02015ed0(UnkStruct_02261424_2 *self, int a, int b);
extern void func_02015ea0(UnkStruct_02261424_2 *self, int a, int b);
extern void func_02015fb0(UnkStruct_02261424_2 *self, int a, int b, int c, int d, int e);
extern int func_020683e4(int h, int a, u8 *p, int k);
extern void func_020b14c0(int a);
extern int func_020b1558(void);
extern int data_ov046_02262420;
extern int func_0206fbc0(void);
extern void *func_020b1954(char *);
extern int func_020b1394(char *, void *);
extern void func_02068404(void *, int, char *);
extern void *func_020b193c(char *);
extern void func_0206844c(void *a, char *b, const void *c);
extern void *func_0202eb70(UnkStruct_02261304 *this);
extern void *func_0202eb20(void *arg0);
extern unsigned char data_ov046_0226204c[];
extern void func_020edb3c(UnkStruct_022612cc *);
extern void func_0201612c(UnkStruct_022612a0 *self);
extern int func_020b1580(void);
extern Pair __ptmf_null;

void func_ov046_02261508(u8 *self, int i)
{
    if ((data_ov046_0226245c & 1) == 0) {
        data_ov046_02262464[0] = data_ov046_02261f98;
        data_ov046_02262464[1] = data_ov046_02261f90;
        data_ov046_02262464[2] = data_ov046_02261f28;
        data_ov046_02262464[3] = data_ov046_02261f58;
        data_ov046_02262464[4] = data_ov046_02261f68;
        data_ov046_0226245c |= 1;
    }
    *(UnkStruct_02261508 *) (self + 0xb8) = data_ov046_02262464[i];
}

void func_ov046_022614e8(UnkStruct_022614e8 *this)
{
    void *p = this->unk_40;
    char local = 0x12;
    func_0206844c(p, (char *) (&local), (const void *) data_ov046_02261fe8);
}

void func_ov046_02261424(UnkStruct_02261424_2 *self)
{
    UnkStruct_02261424 m;
    int h;
    int code;
    int v;

    h = self->unk_40;
    m.b[0] = 0xc;
    if (func_0206fc6c() != 0) {
        *(int *) &m.b[4] = 0;
        *(int *) &m.b[8] = 0;
        func_020b12e0((int *) &m.b[4], self->unk_C0);
        func_02015ed0(self, m.b[8], 2);
        func_02015ea0(self, m.b[7], 3);
        func_02015fb0(self, m.b[5], 5, 2, 0, 0);
        code = 0x19;
        v = (int) m.b[6];
        if (v > 0xc) {
            code = 0x1a;
            v -= 0xc;
        }
        func_02015fb0(self, v, 4, 2, 0, 0);
        m.b[1] = (u8) code;
        func_020683e4(h, 8, &m.b[1], (int) &data_ov046_02262420);
        m.b[0] = 8;
    } else {
        self->unk_C5 = (u8) (0x10 - ((void) (func_020b14c0(self->unk_C0)), func_020b1558()));
        self->unk_C4 = 0;
    }
    func_0206844c((void *) h, (char *) (&m.b[0]), (const void *) ((int) ((int *) data_ov046_02261fe8)));
}

void func_ov046_022613c8(UnkStruct_022613c8 *this)
{
    void *o = this->unk_40;
    char code;
    int buf[8];

    code = 5;
    if (func_0206fbc0() == 0) {
        return;
    }
    if (func_0206fc6c() != 0) {
        func_020b1954((char *) buf);
        code = 0xb;
        func_020b1394((char *) buf, this->unk_C0);
        func_02068404(this->unk_40, 0, (char *) buf);
        func_020b193c((char *) buf);
    }
    func_0206844c(o, &code, (const void *) ((const int *) data_ov046_02261fe8));
}

void func_ov046_02261378(UnkStruct_02261378 *this)
{
    void *o = this->unk_40;
    char code;

    code = 0x1d;
    if (func_0206fc6c() != 0) {
        code = 0x38;
    } else {
        this->unk_C5 = (char) (0x10 - func_020b1558());
        this->unk_C4 = 0;
        code = 0x1d;
    }
    func_0206844c(o, &code, (const void *) ((const int *) data_ov046_02261fe8));
}

void func_ov046_0226131c(UnkStruct_0226131c *this)
{
    void *o = this->unk_40;
    char code;
    int buf[8];

    code = 5;
    if (func_0206fbc0() == 0) {
        return;
    }
    if (func_0206fc6c() != 0) {
        code = 0x3d;
        func_020b1954((char *) buf);
        func_020b1394((char *) buf, this->unk_C0);
        func_02068404(this->unk_40, 0, (char *) buf);
        func_020b193c((char *) buf);
    }
    func_0206844c(o, &code, (const void *) ((const int *) data_ov046_02261fe8));
}

UnkStruct_02261304 *func_ov046_02261304(UnkStruct_02261304 *this)
{
    func_0202eb70(this);
    this->unk_00 = ((char *) data_ov046_0226204c);
    return this;
}

void *func_ov046_022612ec(void *p)
{
    *(void **) p = (void *) data_ov046_0226204c;
    func_0202eb20(p);
    return p;
}

UnkStruct_022612cc *func_ov046_022612cc(UnkStruct_022612cc *self)
{
    self->vtable = (void *) ((int *) data_ov046_0226204c);
    func_0202eb20((void *) self);
    func_020edb3c(self);
    return self;
}

void func_ov046_022612a0(UnkStruct_022612a0 *self)
{
    func_0201612c(self);
    self->pair = __ptmf_null;
    self->c0 = func_020b1580();
}
