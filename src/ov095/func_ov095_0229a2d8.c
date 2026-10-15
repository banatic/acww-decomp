/* func_ov095_0229a2d8 @ 0x0229a2d8, 0x1fc bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229a2d8 {
    u8 pad_00[0x28];
    int st;
    u8 pad_2C[0x43 - 0x2c];
    u8 flag;
} UnkStruct_0229a2d8;

extern int data_ov095_0229cfa0[6];
extern int data_ov095_0229cfb4[6];

extern int func_ov095_02299bb4(void *unused0, void *unused1);
extern int func_ov002_022088cc(void *evt);
extern void func_ov095_0229a1d4(UnkStruct_0229a2d8 *self);
extern int func_ov002_0220889c(void *evt);
extern int func_ov002_022088ac(void *evt);
extern int func_ov002_022088bc(void *evt);
extern void func_ov095_0229a9d4(UnkStruct_0229a2d8 *self);
extern void func_ov095_0229aa3c(UnkStruct_0229a2d8 *self);

void func_ov095_0229a2d8(UnkStruct_0229a2d8 *self, void *evt)
{
    int phase;
    int state;
    int kind;
    int diff;

    if (func_ov095_02299bb4(self, evt)) {
        return;
    }

    state = self->st;
    if (state < 0xc9) {
        return;
    }
    if (state > 0xf6) {
        return;
    }

    for (phase = 0; phase < 5; phase++) {
        if (state <= data_ov095_0229cfb4[phase]) {
            kind = phase;
            diff = state - data_ov095_0229cfa0[phase];
            break;
        }
    }

    if (func_ov002_022088cc(evt)) {
        if (kind == 0) {
            func_ov095_0229a1d4(self);
            return;
        }
        if (kind == 4) {
            int s2 = self->st;
            if (s2 <= 0xf3) {
                if (func_ov002_0220889c(evt)) {
                    diff++;
                }
                self->st = diff + 0xe8;
                return;
            }
            if (s2 == 0xf4) {
                self->st = 0xec;
                if (func_ov002_0220889c(evt)) {
                    self->st = self->st + 1;
                    return;
                }
                if (!func_ov002_022088ac(evt)) {
                    return;
                }
                self->st = self->st - 1;
                return;
            }
            self->st = s2 - 6;
            if (!func_ov002_022088ac(evt)) {
                return;
            }
            self->st = self->st - 1;
            return;
        }
        if (self->st == 0xe7) {
            if (func_ov002_022088ac(evt)) {
                self->st = 0xe6;
                return;
            }
            self->st = 0xdd;
            return;
        }
        if (func_ov002_0220889c(evt)) {
            diff++;
        }
        self->st = diff + data_ov095_0229cfa0[kind - 1];
        if (self->st > data_ov095_0229cfb4[kind - 1]) {
            self->st = data_ov095_0229cfb4[kind - 1];
        }
        return;
    }

    if (func_ov002_022088bc(evt)) {
        if (kind == 4) {
            int s2 = self->st;
            if (s2 <= 0xf4) {
                func_ov095_0229a9d4(self);
                return;
            }
            func_ov095_0229aa3c(self);
            return;
        }
        if (kind == 3) {
            int s2 = self->st;
            if (s2 <= 0xea) {
                if (func_ov002_022088ac(evt)) {
                    if (diff > 0) {
                        diff--;
                    }
                }
                self->st = diff + data_ov095_0229cfa0[kind + 1];
                return;
            }
            if (func_ov002_0220889c(evt)) {
                self->st = self->st + 1;
            }
            if (self->st <= 0xee) {
                self->st = 0xf4;
                return;
            }
            if (self->st == 0xef) {
                self->st = 0xf5;
                return;
            }
            self->st = 0xf6;
            return;
        }
        if (func_ov002_022088ac(evt)) {
            if (diff > 0) {
                diff--;
            }
        }
        self->st = diff + data_ov095_0229cfa0[kind + 1];
        if (self->st > data_ov095_0229cfb4[kind + 1]) {
            self->st = data_ov095_0229cfb4[kind + 1];
        }
        return;
    }

    if (func_ov002_022088ac(evt)) {
        self->st = self->st - 1;
        if (self->st < data_ov095_0229cfa0[kind]) {
            self->st = data_ov095_0229cfb4[kind];
            self->flag = 1;
        }
        return;
    }
    if (func_ov002_0220889c(evt)) {
        self->st = self->st + 1;
        if (self->st > data_ov095_0229cfb4[kind]) {
            self->st = data_ov095_0229cfa0[kind];
            self->flag = 2;
        }
    }
}
