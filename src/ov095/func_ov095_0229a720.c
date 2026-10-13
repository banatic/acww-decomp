/* func_ov095_0229a720 @ 0x0229a720, 0x2b4 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x28];
    int unk_28;
    char pad_2C[0x17];
    u8 unk_43;
} UnkStruct_0229a720;

extern int data_ov095_0229e410[];
extern int data_ov095_0229e3e8[];

extern int func_ov095_02299bb4(UnkStruct_0229a720 *self);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_022088bc(void *p);
extern int func_ov002_0220889c(void *p);
extern void func_ov095_0229a9d4(UnkStruct_0229a720 *self);
extern void func_ov095_0229aa3c(UnkStruct_0229a720 *self);
extern void func_ov095_0229a1d4(UnkStruct_0229a720 *self);

void func_ov095_0229a720(UnkStruct_0229a720 *self, void *pad)
{
    int mode;
    int lo;
    int hi;
    int lo2;
    int hi2;
    int *p;
    int *p2;

    if (func_ov095_02299bb4(self) != 0) {
        return;
    }
    if (self->unk_28 >= 0x3b) {
        if (self->unk_28 <= 0x46) {
            mode = 0;
        } else if (self->unk_28 <= 0x51) {
            mode = 1;
            if (self->unk_28 == 0x51) {
                if (func_ov002_022088cc(pad)) {
                    if (func_ov002_022088ac(pad)) {
                        self->unk_28 = 0x45;
                    } else {
                        self->unk_28 = 0x46;
                    }
                    return;
                }
                if (func_ov002_022088bc(pad)) {
                    self->unk_28 = 0x5c;
                    return;
                }
            }
        } else if (self->unk_28 <= 0x5c) {
            mode = 2;
            if (self->unk_28 == 0x5c) {
                if (func_ov002_022088cc(pad)) {
                    if (func_ov002_022088ac(pad)) {
                        self->unk_28 = 0x50;
                    } else {
                        self->unk_28 = 0x51;
                    }
                    return;
                }
            }
        } else if (self->unk_28 <= 0x67) {
            mode = 3;
            if (func_ov002_022088bc(pad)) {
                if (func_ov002_022088ac(pad)) {
                    self->unk_28 = self->unk_28 - 1;
                }
                if (self->unk_28 < 0x5d) {
                    self->unk_28 = 0x5d;
                }
                if (self->unk_28 <= 0x5e) {
                    self->unk_28 = self->unk_28 + 0xb;
                } else if (self->unk_28 <= 0x65) {
                    self->unk_28 = 0x6b;
                } else {
                    self->unk_28 = self->unk_28 + 8;
                }
                return;
            }
        } else if (self->unk_28 <= 0x6f) {
            mode = 4;
            if (func_ov002_022088cc(pad)) {
                if (self->unk_28 == 0x6b) {
                    self->unk_28 = 0x63;
                    if (func_ov002_022088ac(pad)) {
                        self->unk_28 = self->unk_28 - 1;
                        return;
                    }
                    if (func_ov002_0220889c(pad) == 0) {
                        return;
                    }
                    self->unk_28 = self->unk_28 + 1;
                    return;
                } else if (self->unk_28 > 0x6b) {
                    self->unk_28 = self->unk_28 - 8;
                    if (func_ov002_0220889c(pad) == 0) {
                        return;
                    }
                    if (self->unk_28 < 0x67) {
                        self->unk_28 = self->unk_28 + 1;
                    }
                    return;
                }
            } else {
                if (func_ov002_022088bc(pad)) {
                    if (self->unk_28 < 0x6c) {
                        func_ov095_0229a9d4(self);
                    } else {
                        func_ov095_0229aa3c(self);
                    }
                    return;
                }
            }
        } else {
            return;
        }
    }
    if (func_ov002_022088cc(pad)) {
        if (mode == 0) {
            func_ov095_0229a1d4(self);
            return;
        }
        lo = data_ov095_0229e410[mode - 1];
        hi = data_ov095_0229e3e8[mode - 1];
        p = &self->unk_28;
        self->unk_28 = self->unk_28 - (hi - lo + 1);
        if (mode == 2) {
            *p = *p - 1;
        }
        if (func_ov002_0220889c(pad)) {
            self->unk_28 = self->unk_28 + 1;
        }
        if (self->unk_28 < lo) {
            self->unk_28 = lo;
        } else if (self->unk_28 > hi) {
            self->unk_28 = hi;
        }
    } else if (func_ov002_022088bc(pad) && mode < 3) {
        lo2 = data_ov095_0229e410[mode + 1];
        hi2 = data_ov095_0229e3e8[mode + 1];
        self->unk_28 = self->unk_28 + (data_ov095_0229e3e8[mode] - data_ov095_0229e410[mode] + 1);
        p2 = &self->unk_28;
        if (mode == 1) {
            *p2 = *p2 + 1;
        }
        if (func_ov002_022088ac(pad)) {
            self->unk_28 = self->unk_28 - 1;
        }
        if (self->unk_28 > hi2) {
            self->unk_28 = hi2;
        } else if (self->unk_28 < lo2) {
            self->unk_28 = lo2;
        }
    } else {
        if (self->unk_28 == 0x6b) {
            if (func_ov002_022088ac(pad)) {
                self->unk_28 = 0x69;
                return;
            }
            if (func_ov002_0220889c(pad)) {
                self->unk_28 = 0x6e;
            }
            return;
        }
        if (func_ov002_022088ac(pad)) {
            if (self->unk_28 > data_ov095_0229e410[mode]) {
                self->unk_28 = self->unk_28 - 1;
            } else {
                self->unk_43 = 1;
                self->unk_28 = data_ov095_0229e3e8[mode];
            }
        } else if (func_ov002_0220889c(pad)) {
            if (self->unk_28 < data_ov095_0229e3e8[mode]) {
                self->unk_28 = self->unk_28 + 1;
            } else {
                self->unk_43 = 2;
                self->unk_28 = data_ov095_0229e410[mode];
            }
        }
        if (self->unk_28 == 0x6a || self->unk_28 == 0x6c || self->unk_28 == 0x6d) {
            self->unk_28 = 0x6b;
        }
    }
}
