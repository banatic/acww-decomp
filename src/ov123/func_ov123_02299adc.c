/* func_ov123_02299adc @ 0x02299adc, 0x128 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov123_0229cb08[];
extern unsigned char data_ov123_0229cac0[];
extern unsigned char data_ov123_0229ca9c[];
extern unsigned char data_ov123_0229cae4[];

extern int func_ov002_022088cc(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088bc(void *);
extern void func_ov123_02299640(void *, int);
extern void RtcSendPxiCommand(int);

typedef struct {
    char pad_00[0xaa];
    unsigned char state;
    char pad_AB;
    unsigned char flag;
} UnkStruct_02299adc;

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
    RtcSendPxiCommand(0x869);
ret1:
    return 1;
ret0:
    return 0;
}
