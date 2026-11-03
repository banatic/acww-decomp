/* clock_panel: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208d560 @ 0x0208d560, 0x34 bytes, Thumb
 * func_0208d4a4 @ 0x0208d4a4, 0xba bytes, Thumb
 * func_0208d410 @ 0x0208d410, 0x94 bytes, Thumb
 * func_0208d400 @ 0x0208d400, 0xe bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    int unk_44;
} UnkStruct_0208d560;

typedef union {
    u16 w;
    u8 b[2];
} U16;

typedef struct {
    u8 pad_00[0x48];
    u8 flags[6];
    u8 pad_4E[0x12];
    U16 unk_60;
    U16 unk_62;
    u32 unk_64;
} UnkStruct_0208d4a4;

typedef struct {
    char pad_00[0x50];
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5C;
} UnkStruct_0208d410;

typedef struct {
    char pad_00[0x50];
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5C;
} UnkStruct_0208d400;

extern void func_02051694(void *arg);
extern void func_0205166c(void *arg, int flag);
extern void func_0209df94(void *);
extern void func_0209def4(void *);
extern u32 func_0209ded0(void);
extern int func_02039810(void);
extern int func_0208db3c(void *s);
extern int func_020e8bb0(void *a, int b, int c, int d, int e);

void func_0208d560(UnkStruct_0208d560 *obj)
{
    if (obj->unk_40 != 0) {
        obj->unk_44 = obj->unk_44 - 1;
        if (obj->unk_44 <= 0) {
            obj->unk_44 = 20;
            func_02051694(obj->unk_40);
        } else if (obj->unk_44 == 8) {
            func_0205166c(obj->unk_40, 0);
        }
    }
}

void func_0208d4a4(UnkStruct_0208d4a4 *self)
{
    U16 v[2];
    u32 s;

    func_0209df94(&v[0]);
    func_0209def4(&v[1]);
    s = func_0209ded0();

    if (v[0].w != self->unk_60.w) {
        if (v[0].b[1] != self->unk_60.b[1]) {
            self->flags[0] = 1;
        }
        if (v[0].b[0] != self->unk_60.b[0]) {
            self->flags[1] = 1;
        }
        self->unk_60.w = v[0].w;
    }

    if (v[1].w != self->unk_62.w) {
        if (v[1].b[1] != self->unk_62.b[1]) {
            self->flags[4] = 1;
            self->flags[3] = 1;
        }
        if (v[1].b[0] != self->unk_62.b[0]) {
            self->flags[5] = 1;
        }
        self->unk_62.w = v[1].w;
    }

    if (s != self->unk_64) {
        self->flags[2] = 1;
        self->unk_64 = s;
    }
}

void func_0208d410(UnkStruct_0208d410 *self)
{
    int v1;
    int v2;
    int val;

    v1 = func_02039810();
    v2 = func_0208db3c(self);
    val = (v1 != 0 && v2 != 0) ? 0xfffec000 : 0;
    self->unk_58 += 0xa00;
    self->unk_58 = (self->unk_58 < 0x2300) ? 0x2300 : (self->unk_58 > 0x5000) ? 0x5000 : self->unk_58;
    if (val != self->unk_54) {
        if (self->unk_5C >= 0) {
            if (v2 != 0) {
                self->unk_5C++;
                if (self->unk_5C <= 0xa) {
                    goto l_done;
                }
            }
        }
        self->unk_54 = val;
        self->unk_5C = 0;
    l_done:;
    } else {
        self->unk_5C = 0;
    }
    func_020e8bb0((char *) self + 0x50, self->unk_54, 0x600, self->unk_58, 0x2300);
}

void func_0208d400(UnkStruct_0208d400 *s)
{
    int zero = 0;
    s->unk_50 = zero;
    s->unk_54 = zero;
    s->unk_5C = ~zero;
    s->unk_58 = zero;
}
