/* func_020aaf20 @ 0x020aaf20, 0x184 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Menu {
    int sel;
    int pad_04[7];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
} Menu;

typedef struct Pad {
    u16 held;
    u16 trig;
} Pad;

extern Pad data_021fbe40;

extern int func_020ab510(int);
extern int func_020ab51c(int);
extern void func_020a7e7c(void);
extern void func_020a7e88(void);
extern void func_0200467c(int);
extern void func_020aaee8(Menu *);

typedef struct {
    int uTrig;
    int dTrig;
    int ret;
    int old;
    int changed;
} Locals;

int func_020aaf20(Menu *self)
{
    Locals locals;
    int v;
    int dHeld;
    int uHeld;
    int last;
    int dir;
    u16 held;
    u16 trig;

    locals.ret = 0;
    v = func_020ab510(self->unk_20);

    if (self->unk_24 > 0) {
        self->unk_24 = self->unk_24 - 1;
        if (self->unk_24 <= 0) {
            locals.ret = 1;
            func_020a7e7c();
            goto done;
        }
    }

    trig = data_021fbe40.trig;
    if ((trig & 1) != 0) {
        if (v >= 0 && v == self->sel) {
            func_0200467c(0x2a);
        } else {
            func_020aaee8(self);
        }
        locals.ret = 1;
        func_020a7e7c();
        goto done;
    }

    if (v >= 0 && (trig & 2) != 0) {
        func_0200467c(0x2a);
        self->sel = func_020ab510(self->unk_20);
        self->unk_24 = 1;
        func_020a7e88();
        goto done;
    }

    held = data_021fbe40.held;
    if ((held & 0x40) != 0) {
        dHeld = 1;
    } else {
        dHeld = 0;
    }

    if ((held & 0x80) != 0) {
        uHeld = 1;
    } else {
        uHeld = 0;
    }

    if ((trig & 0x40) != 0) {
        locals.dTrig = 1;
    } else {
        locals.dTrig = 0;
    }

    if ((trig & 0x80) != 0) {
        locals.uTrig = 1;
    } else {
        locals.uTrig = 0;
    }

    last = func_020ab51c(self->unk_20) - 1;
    locals.old = self->sel;
    locals.changed = 0;
    dir = self->unk_2C;

    if (dir == 0 && (dHeld != 0 || uHeld != 0) && (locals.dTrig != 0 || locals.uTrig != 0)) {
        locals.changed = 1;
        func_020a7e88();
        self->unk_28 = 9;
        self->unk_2C = (dHeld != 0) ? -1 : 1;
    } else if ((dir > 0 && uHeld != 0) || (dir < 0 && dHeld != 0)) {
        if (self->unk_28 > 0) {
            self->unk_28 = self->unk_28 - 1;
            if (self->unk_28 <= 0) {
                locals.changed = 1;
                self->unk_28 = 3;
            }
        }
    } else {
        if (dir != 0) {
            func_020a7e7c();
        }
        self->unk_2C = 0;
        self->unk_28 = 0;
    }

    if (locals.changed != 0) {
        self->sel = self->sel + self->unk_2C;
    }

    if (self->sel < 0) {
        self->sel = last;
    } else if (self->sel > last) {
        self->sel = 0;
    }

    if (locals.old != self->sel) {
        func_0200467c(0xb);
    }

done:
    return locals.ret;
}
