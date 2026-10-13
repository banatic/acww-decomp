/* func_02076638 @ 0x02076638, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern int data_021e5a2c;
extern void func_020736bc(void *h, u8 *p, int n);
extern void func_02078448(int *out, volatile u16 *v, u8 *p);
extern int func_0207cec0(int *tbl, int k);
extern void func_0207f1c8(void);
extern void *func_0209b5e8(void);
extern void *func_0209b91c(void);
extern int func_0209bd44(void);
extern int func_0209bc40(void *o);
extern u16 *func_0209b8c4(void *o);

void func_02076638(void)
{
    struct {
        volatile u16 v;
        u8 b[4];
        u8 pad[2];
        int r;
    } q;
    void *o5;
    void *o4;
    unsigned int ok;
    unsigned int a, b;
    u16 *p;

    q.v = 0xfff1;
    func_020736bc(data_020ccf94, q.b, 4);
    func_02078448(&q.r, &q.v, q.b);
    if (func_0207cec0(&data_021e5a2c, q.r) == 0) {
        return;
    }
    func_0207f1c8();
    o5 = func_0209b5e8();
    o4 = func_0209b91c();
    if (func_0209bd44() == 0) {
        return;
    }
    if (func_0209bc40(o4) == 0) {
        ok = 0;
        a = q.v;
        b = q.v;
        if (b >= 0x12b0 && a <= 0x12e7) {
            ok = 1;
        }
        if (ok != 0) {
            goto act;
        }
    }
    if (func_0209bc40(o4) != 1) {
        return;
    }
    ok = 0;
    a = q.v;
    b = q.v;
    if (b >= 0x12e8 && a <= 0x131f) {
        ok = 1;
    }
    if (ok == 0) {
        return;
    }
act:
    p = func_0209b8c4(o5);
    *p = q.v;
}
