/* catch_panel_6: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208d338 @ 0x0208d338, 0xc8 bytes, Thumb
 * func_0208d2e8 @ 0x0208d2e8, 0x50 bytes, Thumb
 * func_0208d290 @ 0x0208d290, 0x58 bytes, Thumb
 * func_0208d20c @ 0x0208d20c, 0x84 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0208d338 {
    void *unk_00;
    u8 pad_04[0x20 - 4];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    u8 unk_34[0x50 - 0x34];
    u8 unk_50[0x6c - 0x50];
    u8 unk_6C[0x88 - 0x6c];
    u8 unk_88[0xa4 - 0x88];
    u8 unk_A4;
    u8 unk_A5;
    u8 unk_A6;
    u8 unk_A7;
    u8 unk_A8;
    u8 unk_A9;
    u8 pad_AA[0xac - 0xaa];
    int unk_AC;
    int unk_B0;
    int unk_B4;
    int unk_B8;
    int unk_BC;
    int unk_C0;
    int unk_C4;
    int unk_C8;
    int unk_CC;
    int unk_D0;
    int unk_D4;
    int unk_D8;
    int unk_DC;
    int unk_E0;
};

struct Sub1 {
    char pad_00[0x28];
};

struct Arr {
    char pad_00[0x1c];
};

struct UnkStruct_0208d290 {
    void *unk_00;
    char pad_04[8];
    struct Sub1 sub;
    struct Arr arr[4];
};

typedef struct {
    char pad_00[0xc];
    char sub[0x14];
    int unk_20;
    char pad_24[0xa8];
    int unk_CC;
} UnkStruct_0208d20c;

extern u8 data_020e2218[];
extern void func_0208af30(void *p);
extern void func_0208a1f8(void *p);
extern void *func_0208e024(void *p);
extern void *func_0208a144(void *);
extern void func_0208d15c(void *);
extern void *func_0208e00c(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);
extern void *func_0208a1d0(void *);
extern int func_0208a1b0(void *, int);
extern int func_0208a198(void *, int);
extern int func_0208aef0(void *);
extern int func_0208aeec(void *);
extern void func_02088df8(int, void *, int, int, int, int, int, int, int, int, int, int);

void *func_0208d338(void *thisArg)
{
    struct UnkStruct_0208d338 *self = (struct UnkStruct_0208d338 *) thisArg;

    func_0208af30(self);
    self->unk_00 = data_020e2218;
    func_0208a1f8((u8 *) self + 0xc);

    self->unk_20 = 0;
    self->unk_24 = 0;
    self->unk_28 = 0;
    self->unk_2C = 0;
    self->unk_30 = 0;

    func_0208e024((u8 *) self + 0x34);
    func_0208e024((u8 *) self + 0x50);
    func_0208e024((u8 *) self + 0x6c);
    func_0208e024((u8 *) self + 0x88);

    self->unk_A4 = 0;
    self->unk_A5 = 0;
    self->unk_A6 = 0;
    self->unk_A7 = 0;
    self->unk_A8 = 0;
    self->unk_A9 = 0;

    self->unk_AC = 0;
    self->unk_B0 = 0;
    self->unk_B4 = 0;
    self->unk_B8 = 0;
    self->unk_BC = 0;
    self->unk_C0 = 0;
    self->unk_C4 = 0;
    self->unk_C8 = 0;
    self->unk_CC = 0;
    self->unk_D0 = 0;
    self->unk_D4 = 0;
    self->unk_D8 = ~0;
    self->unk_DC = 0;
    self->unk_E0 = 0;

    return self;
}

void *func_0208d2e8(void *self)
{
    *(unsigned int *) self = (unsigned int) ((char *) data_020e2218);
    func_0208a144((char *) self + 0xc);
    func_0208d15c(self);
    func_0208e00c((char *) self + 0x88);
    func_0208e00c((char *) self + 0x6c);
    func_0208e00c((char *) self + 0x50);
    func_0208e00c((char *) self + 0x34);
    func_0208a1f4((char *) self + 0xc);
    func_0208af00(self);
    return self;
}

void *func_0208d290(struct UnkStruct_0208d290 *p)
{
    p->unk_00 = (void *) ((unsigned char *) data_020e2218);
    func_0208a144(&p->sub);
    func_0208d15c(p);
    func_0208e00c(&p->arr[3]);
    func_0208e00c(&p->arr[2]);
    func_0208e00c(&p->arr[1]);
    func_0208e00c(&p->arr[0]);
    func_0208a1f4(&p->sub);
    func_0208af00(p);
    func_020edb3c(p);
    return p;
}

// Rounds a 20.12 fixed-point value to an integer.
static inline int fx_round(int v)
{
    return (v + 0x800) >> 12;
}

void func_0208d20c(UnkStruct_0208d20c *obj)
{
    if (obj->unk_20 != 0) {
        void *p = func_0208a1d0(obj->sub);
        if (p != 0) {
            int v1 = func_0208a1b0(obj->sub, -1);
            int v2 = func_0208a198(obj->sub, -1);
            int v3 = func_0208aef0(obj);
            int v4 = func_0208aeec(obj) + fx_round(obj->unk_CC);
            func_02088df8(0, p, v3 + v1, v4 + v2, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
    }
}
