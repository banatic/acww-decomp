/* func_02081144 @ 0x02081144, 0x254 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// msg is eight bytes {b0, pad, h2, h4, h6}; ext[2] follows it at msg + 8.

typedef struct {
    u8 unk_00;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} Msg;

extern int func_0208150c(int);
extern int func_02099020(int, int);
extern int func_02003704(int);
extern int func_02099870(int);
extern int func_020951bc(int);
extern int func_020807a8(int, int);
extern int func_0206d7ac(int);
extern int func_0206d7a0(int);
extern void *func_02094fd4(void *);
extern void *func_02094fbc(void *);
extern int func_020644cc(int);
extern int func_0207d33c(int, int, int, int, void *);
extern signed char func_02081cec(int, int);
extern void *func_020a8228(void *);
extern void *func_020a8210(void *);
extern int func_0209c54c(void *, int);
extern void func_020a8c1c(void *);
extern void *func_020b49d4(void *, void *, int);
extern int func_0203d7c4(int, void *);
extern void *func_02095074(int, void *);
extern int func_02065f18(int);
extern void func_02063ccc(void *, int, int);
extern void func_02063cc8(void *);
extern void func_020638d4(void *, void *, int, int, int, int, int);
extern void func_02063414(void *, int, int, int, int, int, int, int, int, int);
extern int func_0207d3dc(void *, int, void *, void *, void *, u16 *);

extern int data_020cd43c[];

extern unsigned char data_020e199c[];

extern unsigned char data_020e1994[];

void func_02081144(int p0, int p1, int p2)
{
    int ctx;          // sp+18
    int state;        // sp+1c
    int selres;       // sp+20
    Msg msg;          // sp+24
    u16 ext[2];       // sp+2c
    int cnt;          // sp+30
    int t34[2];       // sp+34
    int t3c[2];       // sp+3c
    int t44[2];       // sp+44
    int t4c[2];       // sp+4c
    int t54[2];       // sp+54
    int t5c[2];       // sp+5c
    int buf64[8];     // sp+64
    char obj84[0x5c]; // sp+84
    int r4;
    int type;
    int r7;
    int i;
    int t;
    int rnd;

    ctx = func_0208150c(p0);
    if (p1 == 0) {
        return;
    }
    if (func_02099020(p1, 1) != 0) {
        return;
    }
    if (func_02003704(ctx) == 0) {
        return;
    }
    r7 = func_02099870(p1);
    if (func_020951bc(r7) == 0) {
        return;
    }
    r4 = func_020807a8(p0, r7);
    type = func_0206d7ac(p2);
    func_02094fd4(buf64);

    switch (type) {
        case 1: {
            rnd = func_020644cc(3);
            func_0207d33c((unsigned int) data_020e1994, rnd, r7, ctx, 0);
            if (r4 == 0) {
                goto tail;
            }
            func_02081cec(r4, ~2);
            goto tail;
        }
        case 2: {
            msg.unk_02 = 0xfff1;
            func_020a8228(obj84);
            state = 0;
            cnt = 0;
            func_02095074(r7, buf64);
            func_0203d7c4(0, buf64);
            for (i = 0; i < 6; i++) {
                selres = func_0209c54c(&cnt, i);
                func_020a8c1c(obj84);
                msg.unk_00 = (u8) cnt;
                func_020b49d4(obj84, &msg, selres);
                func_0203d7c4(i + 2, obj84);
            }
            if (func_02065f18(p2) != 0xfff1) {
                t = func_0206d7a0(p2);
                if (t <= 0x20) {
                    if (func_020644cc(2) == 0) {
                        func_02063ccc(t34, 2, 0);
                        t4c[0] = t34[0];
                        t4c[1] = t34[1];
                        func_020638d4(&msg.unk_04, t4c, 0, 0, 1, 1, 0);
                        msg.unk_02 = msg.unk_04;
                        func_02063cc8(t4c);
                        func_02063cc8(t34);
                    } else {
                        func_02063414(&msg.unk_06, 0x1518, 5, 0, 0, 0, 1, 0xa, 0, 1);
                        msg.unk_02 = msg.unk_06;
                    }
                } else if (t <= 0x2f) {
                    func_02063ccc(t3c, 0, 0);
                    t54[0] = t3c[0];
                    t54[1] = t3c[1];
                    func_020638d4(&ext[0], t54, 0, 0, 1, 1, 0);
                    msg.unk_02 = ext[0];
                    func_02063cc8(t54);
                    func_02063cc8(t3c);
                } else {
                    rnd = func_020644cc(3);
                    func_02063ccc(t44, data_020cd43c[rnd], 0);
                    t5c[0] = t44[0];
                    t5c[1] = t44[1];
                    func_020638d4(&ext[1], t5c, 0, 0, 1, 1, 0);
                    msg.unk_02 = ext[1];
                    func_02063cc8(t5c);
                    func_02063cc8(t44);
                }
                if (msg.unk_02 != 0xfff1) {
                    state = 0xa;
                }
            }
            func_0207d3dc((void *) data_020e199c, state, (void *) 0xa, (void *) r7, (void *) ctx, &msg.unk_02);
            if (r4 != 0) {
                if (func_02065f18(p2) != 0xfff1) {
                    func_02081cec(r4, 5);
                } else {
                    func_02081cec(r4, 3);
                }
            }
            func_020a8210(obj84);
            goto tail;
        }
    }
tail:
    func_02094fbc(buf64);
}
