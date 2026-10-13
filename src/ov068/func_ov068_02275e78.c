/* func_ov068_02275e78 @ 0x02275e78, 0x358 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    void *msg;
    u8 v;
} Buf;

typedef struct {
    u8 pad_00[0xc8];
    u8 bits : 3;
    u8 : 5;
} Ctl;

extern void *func_0208150c(void *);
extern void func_0200366c(void *, void *, int, void *);
extern int func_020644cc(int);
extern void *func_020036e8(void *);
extern int func_ov004_0223c144(void *);
extern void func_02062e18(void *, s16 *);
extern void func_02062e00(void *);
extern void func_020a8228(void *);
extern void func_020a8a70(void *, void *, int, int);
extern void func_02068404(int, int, void *);
extern void func_020a8210(void *);
extern void func_020984e8(void);
extern Ctl *func_02099640(void);
extern void func_0202da88(u8 *, void *);
extern void func_0202d994(u8 *, Buf *);
extern void func_ov068_02276278(u8 *);
extern int func_ov068_02276254(u8 *);
extern void func_ov068_02276230(u8 *);
extern int func_ov068_0227620c(u8 *);
extern void func_ov068_022761f0(u8 *);

extern u8 data_ov068_02278920[];
extern u8 data_ov068_02278208[];
extern u8 data_ov068_02278214[];
extern u8 data_ov068_02278220[];
extern u8 data_ov068_0227822c[];
extern u8 data_ov068_02278238[];
extern u8 data_ov068_02278244[];
extern u8 data_ov068_02278254[];
extern s16 data_ov068_0227807c[];
extern u8 data_021c1f04[];
extern u8 data_021c1f34[];

void func_ov068_02275e78(u8 *self, Buf *b)
{
    s16 tmp[10];
    u8 st1[0x24];
    u8 st2[0x60];
    int msgid;
    u32 t;
    u32 j;
    u32 lv;
    int i;
    int flg;
    u8 *obj;
    u16 *src;
    u16 *dst;
    int n;

    b->msg = data_ov068_02278920;
    obj = *(u8 **) (self + 0x1a4);
    if (*(int *) (obj + 0x898) == 1) {
        obj[0xa5a] = 1;
        func_0200366c(func_0208150c(*(void **) (*(u8 **) (self + 0x1a4) + 0x830)), data_ov068_02278920, 0x28,
                      data_ov068_02278208);
        b->v = (u8) func_020644cc(3);
        func_ov068_02276278(self);
        return;
    }
    if (obj[0xa58] != 0 && obj[0xa59] != 0) {
        obj[0xa58] = 0;
    }

    obj = *(u8 **) (self + 0x1a4);
    if (obj[0xa58] != 0) {
        obj[0xa5a] = 6;
        func_0200366c(func_0208150c(*(void **) (*(u8 **) (self + 0x1a4) + 0x830)), data_ov068_02278920, 0x28,
                      data_ov068_02278214);
        b->msg = data_ov068_02278920;
        b->v = (u8) func_020644cc(3);
        return;
    }
    if (obj[0xa59] != 0) {
        obj[0xa5a] = 8;
        func_0200366c(func_0208150c(*(void **) (*(u8 **) (self + 0x1a4) + 0x830)), data_ov068_02278920, 0x28,
                      data_ov068_02278220);
        b->msg = data_ov068_02278920;
        b->v = (u8) func_020644cc(2);
        return;
    }
    if (func_ov068_02276254(self) == 0) {
        (*(u8 **) (self + 0x1a4))[0xa5a] = 2;
        func_0200366c(func_0208150c(*(void **) (*(u8 **) (self + 0x1a4) + 0x830)), data_ov068_02278920, 0x28,
                      data_ov068_0227822c);
        b->v = (u8) func_020644cc(3);
        func_ov068_02276230(self);
        return;
    }
    if (func_ov068_0227620c(self) != 0) {
        (*(u8 **) (self + 0x1a4))[0xa5a] = 5;
        func_0200366c(func_0208150c(*(void **) (*(u8 **) (self + 0x1a4) + 0x830)), data_ov068_02278920, 0x28,
                      data_ov068_02278238);
        b->msg = data_ov068_02278920;
        b->v = (u8) func_020644cc(3);
        func_ov068_022761f0(self);
        return;
    }

    obj = *(u8 **) (self + 0x1a4);
    if (obj[0xa5c] != 0) {
        obj[0xa5c]--;
    }

    t = func_020644cc(0x64);
    msgid = func_ov004_0223c144(func_020036e8(func_0208150c(*(void **) (*(u8 **) (self + 0x1a4) + 0x830))));
    lv = *(u32 *) (*(u8 **) (self + 0x1a4) + 0xa4c);
    if (lv >= 5) {
        lv = 5;
    }
    src = (u16 *) data_ov068_0227807c;
    dst = (u16 *) tmp;
    n = 10;
    do {
        *dst++ = *src++;
    } while (--n != 0);
    for (j = lv; j < 10; j++) {
        tmp[j] = 0;
    }
    func_02062e18(st1, tmp);
    func_020a8228(st2);
    func_020a8a70(st2, st1, 0, 0);
    func_02068404(*(int *) (self + 0x40), 3, st2);

    if (t < 0x1e && msgid != -1) {
        (*(u8 **) (self + 0x1a4))[0xa5a] = 3;
        func_0200366c(func_0208150c(*(void **) (*(u8 **) (self + 0x1a4) + 0x830)), data_ov068_02278920, 0x28,
                      data_ov068_02278244);
        b->msg = data_ov068_02278920;
        b->v = (u8) msgid;
        func_020a8210(st2);
        func_02062e00(st1);
        return;
    }
    if (t < 0x32) {
        (*(u8 **) (self + 0x1a4))[0xa5a] = 4;
        func_0200366c(func_0208150c(*(void **) (*(u8 **) (self + 0x1a4) + 0x830)), data_ov068_02278920, 0x28,
                      data_ov068_02278254);
        b->msg = data_ov068_02278920;
        flg = *(int *) (*(u8 **) (self + 0x1a4) + 0xa54);
        if ((flg & 1) != 0) {
            b->v = (u8) func_020644cc(2);
        } else if ((flg & 2) != 0) {
            b->v = (u8) (func_020644cc(2) + 2);
        } else if ((flg & 4) == 0) {
            b->v = (u8) (func_020644cc(2) + 4);
        } else if ((flg & 0x10) != 0) {
            b->v = 0xa;
        } else if ((flg & 0x20) != 0) {
            b->v = (u8) (func_020644cc(2) + 8);
        } else {
            b->v = (u8) (func_020644cc(2) + 6);
        }
        func_020984e8();
        func_02099640()->bits = (u8) lv;
    } else if (t < 0x46) {
        (*(u8 **) (self + 0x1a4))[0xa5a] = 0;
        func_0202da88(self, data_021c1f04);
        func_0202d994(self, b);
    } else {
        (*(u8 **) (self + 0x1a4))[0xa5a] = 0;
        func_0202da88(self, data_021c1f34);
        func_0202d994(self, b);
    }
    func_020a8210(st2);
    func_02062e00(st1);
}
