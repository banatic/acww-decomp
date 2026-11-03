/* gatekeeper_talk_lines: 9 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_02261ee4 @ 0x02261ee4, 0x30 bytes, Thumb
 * func_ov048_02261ed0 @ 0x02261ed0, 0x12 bytes, Thumb
 * func_ov048_02261e78 @ 0x02261e78, 0x58 bytes, Thumb
 * func_ov048_02261e5c @ 0x02261e5c, 0x1c bytes, Thumb
 * func_ov048_02261e1c @ 0x02261e1c, 0x40 bytes, Thumb
 * func_ov048_02261ddc @ 0x02261ddc, 0x40 bytes, Thumb
 * func_ov048_02261d08 @ 0x02261d08, 0xd4 bytes, Thumb
 * func_ov048_02261ce4 @ 0x02261ce4, 0x24 bytes, Thumb
 * func_ov048_02261be8 @ 0x02261be8, 0xfc bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02261e78 {
    u8 pad_00[0x40];
    void *p;
    u8 pad_44[0xae - 0x44];
    char c;
    u8 pad_AF[0x813 - 0xaf];
    u8 state;
};

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x813 - 0x44];
    char unk_813;
} UnkStruct_02261e1c;

typedef struct UnkStruct_02261ddc UnkStruct_02261ddc;

struct UnkStruct_02261ddc {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x7CF];
    unsigned char unk_813;
};

struct UnkStruct_02261d08 {
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad_44[0x7cc];
    u8 unk_810;
    u8 pad_811[2];
    u8 unk_813;
};

typedef struct {
    char pad_00[0x40];
    void *unk_40;
} SelfType;

typedef struct UnkStruct_02261be8_2 {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02261be8_2;

typedef struct UnkStruct_02261be8 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02261be8;

extern void func_020a0194(void);
extern int func_020984e8(void);
extern int func_02099664(int);
extern void func_02077be8(unsigned char *);
extern int func_020a0174(void);
extern int func_ov048_02262658(void *receiver);
extern void *data_ov048_02263d20;
extern unsigned char func_ov048_022609fc(void *receiver);
extern void func_0206844c(void *a, char *b, void *d);
extern int func_ov048_0226254c(struct UnkStruct_02261d08 *self);
extern void *func_02077bcc(void *record);
extern int func_020eb6ac(u32 p);
extern int func_020eb064(u32 p);
extern const u8 data_ov048_02263964[];
extern UnkStruct_02261be8 *data_020ccf94;
extern int func_02099020(int t, int a);
extern int func_02073d90(UnkStruct_02261be8 *g);
extern int func_02073918(UnkStruct_02261be8 *g, int a);
extern int func_02073dd4(UnkStruct_02261be8 *g, int a);
extern int func_ov048_02260a24(void *receiver);
extern long long func_020eb694(int a);
extern void func_ov048_02262588(UnkStruct_02261be8_2 *self, long long v);

void func_ov048_02261e78(struct UnkStruct_02261e78 *self, int flag);
void func_ov048_02261d08(struct UnkStruct_02261d08 *self);

void func_ov048_02261ee4(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;

    if (r4 == 0) {
        func_020a0194();
        func_02077be8((unsigned char *) func_02099664((int) func_020984e8()));
        func_020a0174();
    }

    func_ov048_02261e78((struct UnkStruct_02261e78 *) r5, r4);
}

void func_ov048_02261ed0(int param1, int param2)
{
    if (param2 == 2) {
        func_ov048_02262658((void *) param1);
    }
}

void func_ov048_02261e78(struct UnkStruct_02261e78 *self, int flag)
{
    unsigned char ch;
    char c;

    if (flag != 0) {
        return;
    }
    ch = 0xff;

    switch (self->state) {
        case 2:
            self->c = '[';
            ch = 'j';
            break;
        case 1:
            self->c = '>';
            ch = 'j';
            break;
        case 0:
            ch = '%';
            // falls through
    }

    if (ch != 0xff) {
        c = (char) ch;
        func_0206844c(self->p, (char *) (&c), data_ov048_02263d20);
    }
}

void func_ov048_02261e5c(char *r0, int r1)
{
    if (r1 == 0) {
        r0[0x813] = 0;
        func_ov048_02261d08((struct UnkStruct_02261d08 *) ((void *) r0));
    }
}

void func_ov048_02261e1c(UnkStruct_02261e1c *p, int mode)
{
    if (mode == 1) {
        p->unk_813 = 2;
        func_ov048_02261d08((struct UnkStruct_02261d08 *) p);
    } else if (mode == 2) {
        char c = func_ov048_022609fc(p);
        func_0206844c((void *) p->unk_40, &c, (void *) ((*(int *) &data_ov048_02263d20)));
    }
}

void func_ov048_02261ddc(UnkStruct_02261ddc *self, int ev)
{
    if (ev == 1) {
        self->unk_813 = 1;
        func_ov048_02261d08((struct UnkStruct_02261d08 *) self);
    } else if (ev == 2) {
        char local;
        local = func_ov048_022609fc(self);
        func_0206844c(self->unk_40, &local, data_ov048_02263d20);
    }
}

void func_ov048_02261d08(struct UnkStruct_02261d08 *self)
{
    char buf[5];
    u32 p;

    if (self->unk_813 != 0 && func_ov048_0226254c(self) == 0) {
        if (self->unk_813 == 2) {
            buf[0] = 'o';
            func_0206844c(self->unk_40, buf, data_ov048_02263d20);
        } else {
            buf[1] = 'p';
            func_0206844c(self->unk_40, buf + 1, data_ov048_02263d20);
        }
        return;
    }

    p = (u32) func_02077bcc((void *) func_02099664((int) func_020984e8()));
    func_020a0194();
    if (func_020eb6ac(p) != 0) {
        if (func_020eb064(p) != 0) {
            buf[2] = data_ov048_02263964[self->unk_813];
            func_0206844c(self->unk_40, buf + 2, data_ov048_02263d20);
        } else {
            self->unk_810 = 1;
            buf[3] = 'r';
            func_0206844c(self->unk_40, buf + 3, data_ov048_02263d20);
        }
    } else {
        buf[4] = 'q';
        func_0206844c(self->unk_40, buf + 4, data_ov048_02263d20);
    }
    func_020a0174();
}

void func_ov048_02261ce4(SelfType *self, int flag)
{
    if (flag == 0) {
        char local = 25;
        func_0206844c(self->unk_40, (char *) (&local), data_ov048_02263d20);
    }
}

void func_ov048_02261be8(UnkStruct_02261be8_2 *self, int mode)
{
    u8 arg;
    int code;
    int t;
    UnkStruct_02261be8 *g;
    int q;
    int valid;

    t = func_020984e8();
    code = 0xff;
    switch (mode) {
        case 0:
            if (func_02099020(t, 1) != 0) {
                code = 8;
                break;
            }
            g = data_020ccf94;
            if (func_02073d90(g) != 0 && func_02073918(g, 0) != 0) {
                code = 0x50;
                break;
            }
            if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
                code = 0x51;
            } else {
                code = 0x52;
            }
            break;
        case 1:
            if (func_02099020(t, 1) != 0) {
                code = 0xe;
            } else {
                code = func_ov048_02260a24(self);
            }
            break;
        case 2:
            if (func_02073918(data_020ccf94, 0) != 0) {
                break;
            }
            if (func_02099020(t, 1) != 0) {
                code = 8;
                break;
            }
            func_020a0194();
            q = (int) func_02077bcc((void *) func_02099664(t));
            valid = func_020eb064((u32) ((void *) q));
            if (valid != 0) {
                if (func_020eb6ac(q) != 0) {
                    code = 0x29;
                    func_ov048_02262588(self, func_020eb694(q));
                } else {
                    code = 0x23;
                }
            } else {
                code = 0x2f;
            }
            func_020a0174();
            break;
    }
    if (code != 0xff) {
        arg = (u8) code;
        func_0206844c((void *) self->unk_40, (char *) (&arg), (void *) ((*(int *) &data_ov048_02263d20)));
    }
}
