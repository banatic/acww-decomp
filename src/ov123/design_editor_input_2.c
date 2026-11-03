/* design_editor_input_2: 6 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_02299ce0 @ 0x02299ce0, 0x20 bytes, Thumb
 * func_ov123_02299cc0 @ 0x02299cc0, 0x20 bytes, Thumb
 * func_ov123_02299ca0 @ 0x02299ca0, 0x20 bytes, Thumb
 * func_ov123_02299c04 @ 0x02299c04, 0x9c bytes, Thumb
 * func_ov123_02299adc @ 0x02299adc, 0x128 bytes, Thumb
 * func_ov123_022999b0 @ 0x022999b0, 0x12c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02299c04 {
    u8 pad_00[0x8d];
    u8 unk_8D;
    u8 pad_8E[0x12];
    u8 unk_A0;
    u8 pad_A1[9];
    u8 unk_AA;
};

typedef struct {
    char pad_00[0xaa];
    unsigned char state;
    char pad_AB;
    unsigned char flag;
} UnkStruct_02299adc;

typedef struct {
    char pad_00[0xaf];
    unsigned char unk_AF;
    unsigned char unk_B0;
    char pad_B1[2];
    unsigned char unk_B3;
} UnkStruct_022999b0;

extern void func_ov002_0220a0ec(void *p);
extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_0220a164(void *ptr);
extern int func_ov123_02299650(void *self, int arg);
extern void func_ov123_02299630(void *self, int arg);
extern int func_ov123_02299d34(void *self);
extern int func_ov123_02299d24(void *self);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern void func_ov002_0220a314(void *p);
extern void func_ov002_0220a2b4(void *p);
extern unsigned char data_ov123_0229cb08[];
extern unsigned char data_ov123_0229cac0[];
extern unsigned char data_ov123_0229ca9c[];
extern unsigned char data_ov123_0229cae4[];
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088bc(void *);
extern void func_ov123_02299640(void *, int);
extern void func_0200467c(int);
extern unsigned short data_021fbe40[2];
extern void func_020041bc(unsigned char byte);
extern int func_ov123_0229ae7c(void *obj, unsigned char byte);

void func_ov123_02299ce0(void *self)
{
    void *p;
    void *q;
    void *(*fn)(void *);

    p = (char *) self + 0x1cc;
    func_ov002_0220a0ec(p);
    q = (char *) self + 0x1cc;
    fn = *(void *(**) (void *) )(*(char **) q + 0xc);
    fn(q);
}

void func_ov123_02299cc0(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x1cc);
    func_ov002_02208098(self, 10);
}

void func_ov123_02299ca0(void *self)
{
    func_ov002_0220a164((char *) self + 0x1cc);
    func_ov002_02208098(self, 0xb);
}

void func_ov123_02299c04(struct UnkStruct_02299c04 *self)
{
    if ((u8) (self->unk_AA + 0xe3) <= 1) {
        func_ov002_0220a314((u8 *) self + 0x1cc);
    } else {
        func_ov002_0220a2b4((u8 *) self + 0x1cc);
    }

    if (func_ov123_02299650(self, 0x200) != 0) {
        int a = func_ov123_02299d34(self);
        int b = func_ov123_02299d24(self);
        func_ov002_0220a0b4((u8 *) self + 0x1cc, a, b);
        func_ov123_02299630(self, 0x200);
    } else {
        int a = func_ov123_02299d34(self);
        int b = func_ov123_02299d24(self);
        func_ov002_0220a05c((u8 *) self + 0x1cc, a, b, 3, 1);
        self->unk_A0 = self->unk_8D;
        func_ov002_02208098(self, 9);
    }
}

int func_ov123_02299adc(UnkStruct_02299adc *p, void *a)
{
    unsigned char orig;
    unsigned char cur;

    if (a == 0) {
        return 0;
    }

    orig = p->state;

    if (func_ov002_022088cc(a)) {
        if (p->state == 0x1d) {
            goto handler_1d;
        }
        if (p->state != 0x1e) {
            goto after_first_if;
        }
        if (p->flag == 0) {
            p->state = 5;
        } else {
            p->state = 0x16;
        }
        return 1;

    handler_1d:
        if (p->flag == 0) {
            p->state = 5;
        } else {
            p->state = 0x1c;
        }
        return 1;
    }
after_first_if:

    if (func_ov002_022088ac(a)) {
        p->state = data_ov123_0229cb08[p->state];
    } else if (func_ov002_0220889c(a)) {
        p->state = data_ov123_0229cac0[p->state];
    }

    cur = p->state;
    if (orig == cur || cur <= 11) {
        if (func_ov002_022088cc(a)) {
            p->state = data_ov123_0229ca9c[p->state];
        } else if (func_ov002_022088bc(a)) {
            p->state = data_ov123_0229cae4[p->state];
        }
    }

    cur = p->state;
    if (orig == cur) {
        goto ret0;
    }
    if (cur < 14) {
        goto ret1;
    }
    if (cur > 28) {
        goto ret1;
    }
    if (orig < 14) {
        goto ret1;
    }
    if (orig > 28) {
        goto ret1;
    }

    func_ov123_02299640(p, 0x200);
    func_0200467c(0x869);
ret1:
    return 1;
ret0:
    return 0;
}

int func_ov123_022999b0(UnkStruct_022999b0 *obj, int param1, int param2)
{
    unsigned char new_af, new_b0;

    new_af = obj->unk_AF;
    new_b0 = obj->unk_B0;

    if (data_021fbe40[0] & 0x20) {
        if (data_021fbe40[1] & 0x20) {
            obj->unk_B3 = 4;
        }
        if (new_af != 0) {
            new_af--;
        }
    } else {
        if (data_021fbe40[0] & 0x10) {
            if (data_021fbe40[1] & 0x10) {
                obj->unk_B3 = 4;
            }
            if (new_af < 0x1F) {
                new_af++;
            }
        }
    }

    if (data_021fbe40[0] & 0x40) {
        if (data_021fbe40[1] & 0x40) {
            obj->unk_B3 = 4;
        }
        if (new_b0 != 0) {
            new_b0--;
        }
    } else {
        if (data_021fbe40[0] & 0x80) {
            if (data_021fbe40[1] & 0x80) {
                obj->unk_B3 = 4;
            }
            if (new_b0 < 0x1F) {
                new_b0++;
            }
        }
    }

    if (obj->unk_AF != new_af) {
        goto else_part;
    }
    if (obj->unk_B0 == new_b0) {
        goto return0;
    }

else_part:
    if (obj->unk_B3 == 0) {
        goto common;
    }
    if (obj->unk_B3 == 4) {
        obj->unk_B3--;
        goto common;
    }
    obj->unk_B3--;
    return 0;

common:
    obj->unk_AF = new_af;
    obj->unk_B0 = new_b0;
    if (param2 == 0) {
        func_0200467c(0x865);
    }
    func_020041bc((unsigned char) func_ov123_0229ae7c(obj, new_af));
    return 1;

return0:
    obj->unk_B3 = 0;
    return 0;
}
