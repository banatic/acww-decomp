/* func_02088470 @ 0x02088470, 0x168 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 a : 2;
    u8 b : 3;
    u8 c : 3;
} Flags;
extern int func_02073d90(void *);
extern void *func_020984e8(void);
extern int func_02099020(void *, int);
extern int func_020885d8(int, int, int, Flags *);
extern void *func_02099694(void *);
extern void func_02088748(void *, Flags *);
extern u8 *func_02088724(void *);
extern void *func_02099670(void *);
extern int func_02088bdc(void *);
extern int func_020af028(void *);
extern int func_02070fa0(void *);
extern void *data_020ccf94;
extern u8 data_021dc7a8[];
extern u8 data_021f38f8[];
int func_02088470(int a, int b, int c, Flags *d)
{
    u8 *ptr;
    void *h;
    Flags loc;
    u8 *p;
    if (func_02073d90(data_020ccf94) != 0) {
        return 0;
    }
    h = func_020984e8();
    if (func_02099020(h, 1) != 0) {
        return 0;
    }
    if (func_020885d8(a, b, c, d) == 0) {
        return 0;
    }
    func_02088748(func_02099694(h), &loc);
    p = func_02088724(func_02099694(h));
    ptr = data_021dc7a8;
    if (((d->a == loc.a) && (d->b == loc.b)) && (d->c == loc.c)) {
        if ((((p[2] == a) && (p[1] == b)) && (p[0] == c)) || (((p[2] == 0) && (p[1] == 0)) && (p[0] == 0))) {
            return 1;
        }
        return 0;
    }
    if (d->c == 0) {
        switch (d->a) {
            case 0:
                if (func_02099020(h, 6) != 0) {
                    return 1;
                }
                break;

            case 2:
                if (func_02088bdc(func_02099670(h)) == 0xf) {
                    return 1;
                }
                break;

            case 3:
                if (func_020af028((void *) (0x171b4 + ((int) ptr))) == 3) {
                    return 1;
                }
                break;

            case 1:
                if ((func_02099020(h, 8) != 0) || (func_02070fa0(data_021f38f8) != 0)) {
                    return 1;
                }
                break;
        }

    } else {
        u8 t = (u8) (d->c - 1);
        if (((d->a == loc.a) && (d->b == loc.b)) && (t == loc.c)) {
            return 1;
        }
    }
    return 0;
}
