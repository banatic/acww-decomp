/* owl: 4 functions, module ov047
 * mwccarm 1.2/base -O4,s
 * func_ov047_02260610 @ 0x02260610, 0x2c bytes, Thumb
 * func_ov047_02260474 @ 0x02260474, 0x19c bytes, Thumb
 * func_ov047_02260448 @ 0x02260448, 0x2c bytes, Thumb
 * func_ov047_02260420 @ 0x02260420, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02260474_2 UnkStruct_02260474_2;

typedef struct SubVT {
    void (*unk_00)(UnkStruct_02260474_2 *);
    void (*unk_04)(UnkStruct_02260474_2 *);
    void (*unk_08)(UnkStruct_02260474_2 *);
} SubVT;

struct UnkStruct_02260474_2 {
    const SubVT *vt;
};

typedef struct UnkStruct_02260474_3 UnkStruct_02260474_3;

struct UnkStruct_02260474_3 {
    u8 pad_00[0x560];
    u8 mode;
    u8 pad_561[0x658 - 0x561];
    UnkStruct_02260474_2 sub;
};

typedef struct UnkStruct_02260474 {
    u8 pad_00[0x64];
    int unk_64;
} UnkStruct_02260474;

struct UnkStruct_02260448 {
    void *unk_00;
    char pad_04[0x654];
};

struct UnkStruct_02260420 {
    void *vtable;
    char pad_04[0x654];
    char sub[1];
};

extern int func_02014868(void *p);
extern int func_0201c014(void *p);
extern UnkStruct_02260474 *data_020ccf94;
extern void func_0201c054(UnkStruct_02260474_3 *, int, int, int);
extern int func_0201c0e0(UnkStruct_02260474_3 *);
extern int func_0201c2a4(UnkStruct_02260474_3 *, int);
extern void func_02016108(UnkStruct_02260474_2 *, int);
extern void func_ov047_022624f4(UnkStruct_02260474_3 *, int);
extern int func_020a7278(void);
extern int func_02073d90(UnkStruct_02260474 *);
extern short *func_0209d358(int, int);
extern int func_0201c040(UnkStruct_02260474_3 *, int *, int *);
extern void *func_ov047_02261978(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern unsigned char data_ov047_02262ca4[];

int func_ov047_02260610(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0 || func_0201c014(p) != 0) {
        return 0;
    }
    return 1;
}

void func_ov047_02260474(UnkStruct_02260474_3 *self, int ev, int v)
{
    int a, b;
    int t;
    UnkStruct_02260474 *g;

    switch (ev) {
        case 3:
            self->mode = (u8) v;
            if (v != 4) {
                func_0201c054(self, 1, data_020ccf94->unk_64, v);
                func_ov047_022624f4(self, 8);
            } else if (func_0201c0e0(self)) {
                t = data_020ccf94->unk_64;
                func_0201c054(self, 1, t, t);
                func_ov047_022624f4(self, 8);
            }
            break;
        case 0:
            self->mode = (u8) v;
            if (v != 4 && v != data_020ccf94->unk_64) {
                func_0201c054(self, 1, v, v);
                func_ov047_022624f4(self, 7);
            } else if (func_0201c0e0(self)) {
                t = data_020ccf94->unk_64;
                func_0201c054(self, 1, t, t);
                self->sub.vt->unk_08(&self->sub);
                func_02016108(&self->sub, func_0201c2a4(self, 4));
                func_ov047_022624f4(self, 3);
            }
            break;
        case 8:
            if (v == 4) {
                if (func_020a7278()) {
                    g = data_020ccf94;
                    func_0201c054(self, 1, g->unk_64, 4);
                    if (func_02073d90(g) != 0 || *func_0209d358(0, 0x4a) != 0) {
                        func_ov047_022624f4(self, 0);
                    } else {
                        func_ov047_022624f4(self, 1);
                    }
                } else {
                    func_0201c054(self, 1, 4, data_020ccf94->unk_64);
                    func_ov047_022624f4(self, 6);
                }
            }
            break;
        case 4:
            if (func_0201c014((void *) self) && func_0201c0e0(self)) {
                a = 4;
                b = 4;
                if (func_0201c040(self, &a, &b)) {
                    if (v != 4) {
                        if (v == b) {
                            goto ok4;
                        }
                    }
                    if (v != 4) {
                        return;
                    }
                ok4:
                    func_0201c054(self, 1, data_020ccf94->unk_64, 4);
                    func_ov047_022624f4(self, 0);
                }
            }
            break;
    }
}

void *func_ov047_02260448(struct UnkStruct_02260448 *self)
{
    self->unk_00 = ((char *) data_ov047_02262ca4);
    func_ov047_02261978((char *) self + 0x658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}

struct UnkStruct_02260420 *func_ov047_02260420(struct UnkStruct_02260420 *self)
{
    self->vtable = (void *) data_ov047_02262ca4;
    func_ov047_02261978(&self->sub);
    func_0202ee5c(self);
    return self;
}
