/* atm_4: 14 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220c4b8 @ 0x0220c4b8, 0x1c bytes, Thumb
 * func_ov004_0220c4ac @ 0x0220c4ac, 0xc bytes, Thumb
 * func_ov004_0220c45c @ 0x0220c45c, 0x50 bytes, Thumb
 * func_ov004_0220c414 @ 0x0220c414, 0x48 bytes, Thumb
 * func_ov004_0220c3c8 @ 0x0220c3c8, 0x4c bytes, Thumb
 * func_ov004_0220c3a0 @ 0x0220c3a0, 0x28 bytes, Thumb
 * func_ov004_0220c380 @ 0x0220c380, 0x20 bytes, Thumb
 * func_ov004_0220c37c @ 0x0220c37c, 0x4 bytes, Thumb
 * func_ov004_0220c36c @ 0x0220c36c, 0x10 bytes, Thumb
 * func_ov004_0220c318 @ 0x0220c318, 0x54 bytes, Thumb
 * func_ov004_0220c308 @ 0x0220c308, 0x10 bytes, Thumb
 * func_ov004_0220c250 @ 0x0220c250, 0xb8 bytes, Thumb
 * func_ov004_0220c1f4 @ 0x0220c1f4, 0x5c bytes, Thumb
 * func_ov004_0220c1d0 @ 0x0220c1d0, 0x22 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0220c414 {
    void *unk_00;
    unsigned char pad_04[0xE8];
    void *unk_EC;
    unsigned char pad_F0[0x48];
    char sub_138;
    unsigned char pad_139[0x9B];
    char sub_1D4;
};

struct Work {
    u8 pad_00[0x12c];
    u32 unk_12C;
};

typedef struct {
    u32 data[16];
} BUFFER;

extern int func_020edf70(int);
extern void *func_0203f130(void *self);
extern void *func_02066a30(void *p);
extern void *func_020324fc(void *p);
extern void *func_020b82ec(void *p);
extern int data_ov004_02256c00;
extern unsigned char data_ov004_0224fc4c[];
extern unsigned char data_ov004_0224fcc0[];
extern void *func_020b82d0(void *addr);
extern void *func_020324c4(void *addr);
extern void *func_02066994(void *addr);
extern void *func_0203f080(void *addr);
extern void func_020edf54(void *);
extern void func_0203efb0(int p, int flag);
extern int func_ov004_0220c144(int p, int flag);
extern void func_ov004_0220c0c8(void *self);
extern int func_020b6590(void);
extern int func_020b7e04(int value, void *addr);
extern int func_020321bc(void *a, int b, int c, int d, void *e, int f, int g);
extern int func_020b7dc8(int a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern int func_02032180(int x);
extern u32 func_020984e8(void);
extern unsigned int func_020996a0(unsigned int);
extern u16 *func_020adf50(void *record);
extern void *func_020b5630(BUFFER *);
extern int func_020b45d0(BUFFER *, u16, int, int, int, int);
extern void func_02068404(u32, int, BUFFER *);
extern u16 func_020adda8(u16 *);
extern u8 func_020adde4(u16);
extern int func_020683e4(u32, int, void *, u32);
extern void *func_020b5618(BUFFER *);
extern u32 data_ov004_0224fbe4;
extern int func_020ea990(void *a, void *b);

void *func_ov004_0220c45c(void *self);
void func_ov004_0220c318(char *self);
int func_ov004_0220c308(int arg);

void func_ov004_0220c4b8(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_020edf70(0x47c)))) {
        func_ov004_0220c45c((void *) conditionInput0);
    }
}

unsigned int func_ov004_0220c4ac(void)
{
    return (*(unsigned int *) &data_ov004_02256c00);
}

void *func_ov004_0220c45c(void *self)
{
    func_0203f130(self);
    func_02066a30((char *) self + 0xec);
    *(int *) ((char *) self + 0) = (unsigned int) data_ov004_0224fc4c;
    *(int *) ((char *) self + 0xec) = (unsigned int) data_ov004_0224fcc0;
    func_020324fc((char *) self + 0x138);
    func_020b82ec((char *) self + 0x1d4);
    data_ov004_02256c00 = 0;
    return self;
}

struct UnkStruct_0220c414 *func_ov004_0220c414(struct UnkStruct_0220c414 *self)
{
    self->unk_00 = ((char *) data_ov004_0224fc4c);
    self->unk_EC = ((char *) data_ov004_0224fcc0);
    func_020b82d0(&self->sub_1D4);
    func_020324c4(&self->sub_138);
    func_02066994(&self->unk_EC);
    func_0203f080(self);
    return self;
}

char *func_ov004_0220c3c8(char *self)
{
    *(int *) self = (int) ((char *) data_ov004_0224fc4c);
    *(int *) (self + 0xec) = (int) ((char *) data_ov004_0224fcc0);
    func_020b82d0(self + 0x1d4);
    func_020324c4(self + 0x138);
    func_02066994(self + 0xec);
    func_0203f080(self);
    func_020edf54(self);
    return self;
}

int func_ov004_0220c3a0(int p)
{
    data_ov004_02256c00 = p;
    func_0203efb0(p, 0);
    func_ov004_0220c144(p, 0);
    func_ov004_0220c318((char *) p);
    return 1;
}

int func_ov004_0220c380(void *self)
{
    func_ov004_0220c0c8(self);
    func_020b7e04(func_020b6590(), (char *) self + 0x1d4);
    return 1;
}

int func_ov004_0220c37c(void)
{
    return 1;
}

int func_ov004_0220c36c(int arg0)
{
    func_ov004_0220c308(arg0);
    return 1;
}

void func_ov004_0220c318(char *self)
{
    func_020321bc(self + 0x138, 0x2000, 0x2000, 0x2000, self + 0x5c, 0, 0);
    func_020b7dc8(func_020b6590(), self + 0x1d4, self + 0x5c, 0x2000, 0x2000, 0x2000, 0, 0xb, 0xff);
}

int func_ov004_0220c308(int arg)
{
    return func_02032180(arg + 0x138);
}

void func_ov004_0220c250(struct Work *self)
{
    u8 bytes[2];
    BUFFER buf;
    u16 *p;

    if (self->unk_12C == 0) {
        return;
    }

    p = func_020adf50((void *) func_020996a0((unsigned int) func_020984e8()));

    func_020b5630(&buf);

    func_020b45d0(&buf, *(u16 *) p, 10, 0, 0, 0);
    func_02068404(self->unk_12C, 0, &buf);
    func_020b45d0(&buf, func_020adda8(p), 10, 0, 0, 0);
    func_02068404(self->unk_12C, 1, &buf);

    if (func_020adde4(*(u16 *) p) != 0) {
        bytes[0] = (u8) (func_020adde4(*(u16 *) p) - 1);
        func_020683e4(self->unk_12C, 2, &bytes[0], data_ov004_0224fbe4);
    }
    bytes[1] = func_020adde4(*(u16 *) p);
    func_020683e4(self->unk_12C, 3, &bytes[1], data_ov004_0224fbe4);

    func_020b5618(&buf);
}

int func_ov004_0220c1f4(void *a, void *b)
{
    unsigned short d;

    if (b != 0 && func_020ea990((char *) b + 0x5c, (char *) a + 0x5c) < 0x2333) {
        d = (unsigned short) (*(short *) ((char *) b + 0x8e) - (*(short *) ((char *) a + 0x8e) + 0x8000));
        if (d < 0x1000) {
            goto ret1;
        }
        if (d < 0xf000) {
            goto ret0;
        }
    ret1:
        return 1;
    ret0:
        return 0;
    }
    return 0;
}

void func_ov004_0220c1d0(int a, int b)
{
    switch (b) {
        case 0:
            func_ov004_0220c144(a, 1);
            break;
        case 8:
            func_ov004_0220c144(a, 0);
            break;
        default:
            break;
    }
}
