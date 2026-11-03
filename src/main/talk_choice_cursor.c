/* talk_choice_cursor: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ab17c @ 0x020ab17c, 0x24 bytes, Thumb
 * func_020ab158 @ 0x020ab158, 0x24 bytes, Thumb
 * func_020ab130 @ 0x020ab130, 0x28 bytes, Thumb
 * func_020ab0f4 @ 0x020ab0f4, 0x3a bytes, Thumb
 * func_020ab0a4 @ 0x020ab0a4, 0x4e bytes, Thumb
 * func_020aaf20 @ 0x020aaf20, 0x184 bytes, Thumb
 * func_020aaee8 @ 0x020aaee8, 0x36 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[8];
    int arr[5];
} UnkStruct_020ab17c;

typedef struct {
    unsigned char pad_00[8];
    void *arr[5];
} UnkStruct_020ab158;

struct UnkStruct_020ab130 {
    int pad_00[2];
    void *data[5];
};

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[0x18];
    int unk_20;
} Param;

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

typedef struct {
    int uTrig;
    int dTrig;
    int ret;
    int old;
    int changed;
} Locals;

struct UnkStruct_020aaee8 {
    int unk_00;
    unsigned char pad_04[28];
    int unk_20;
};

extern void func_02051694(int arg);
extern void func_0205166c(void *ptr, unsigned int something);
extern void func_020a8fb8(void *ptr);
extern int func_020a7e50(void);
extern int func_020a7ffc(void);
extern void func_020a7e64(void);
extern int func_020a7e44(void);
extern int func_020a812c(void);
extern void func_020a7e70(void);
extern int func_020a806c(int *a, int *b);
extern int func_020ac148(int a, int b, int c);
extern int func_020ab510(int a);
extern void func_0200467c(int cmd);
extern Pad data_021fbe40;
extern int func_020ab51c(int);
extern void func_020a7e7c(void);
extern void func_020a7e88(void);
extern int func_020ab550(int a, int b);
extern int func_020ab780(int a);

void func_020aaee8(struct UnkStruct_020aaee8 *arg);

void func_020ab17c(UnkStruct_020ab17c *s)
{
    unsigned int i;
    for (i = 0; i < 5; i++) {
        if (s->arr[i] != 0) {
            func_02051694(s->arr[i]);
        }
    }
}

void func_020ab158(UnkStruct_020ab158 *obj)
{
    unsigned int i;
    unsigned int something;
    i = 0;
    something = i;
    do {
        if (obj->arr[i] != 0) {
            func_0205166c(obj->arr[i], something);
        }
        i++;
    } while (i < 5);
}

void func_020ab130(struct UnkStruct_020ab130 *s)
{
    unsigned int i;
    for (i = 0; i < 5; i++) {
        if (s->data[i] != 0) {
            func_020a8fb8(s->data[i]);
            s->data[i] = 0;
        }
    }
}

int func_020ab0f4(void *object)
{
    int result;

    result = 0;
    if (func_020a7e50() != 0) {
        if (func_020a7ffc() != 0) {
            func_020a7e64();
            result = 1;
        }
    } else {
        if (func_020a7e44() != 0) {
            if (func_020a812c() != 0) {
                func_020a7e70();
                result = 1;
            }
        }
    }
    return result;
}

int func_020ab0a4(Param *param)
{
    int r6 = 0;
    int localA, localB;
    if (func_020a806c(&localA, &localB)) {
        int r4;
        r4 = func_020ac148(param->unk_04, localA, localB);
        if (r4 >= 0) {
            int r0;
            param->unk_00 = r4;
            r6 = 1;
            r0 = func_020ab510(param->unk_20);
            if (r0 >= 0 && r0 == r4) {
                func_0200467c(0x2a);
            } else {
                func_020aaee8((struct UnkStruct_020aaee8 *) param);
            }
        }
    }
    return r6;
}

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
            func_020aaee8((struct UnkStruct_020aaee8 *) self);
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

void func_020aaee8(struct UnkStruct_020aaee8 *arg)
{
    int result;
    int cmd;

    result = func_020ab780(func_020ab550(arg->unk_20, arg->unk_00));
    cmd = 0x29;
    if (result == 1) {
        cmd = 0x3a;
    } else if (result == 2) {
        cmd = 0x6a;
    } else if (result == 3) {
        cmd = 0x6c;
    }
    func_0200467c(cmd);
}
