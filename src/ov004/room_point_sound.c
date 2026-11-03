/* room_point_sound: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223a704 @ 0x0223a704, 0x2a bytes, Thumb
 * func_ov004_0223a6d8 @ 0x0223a6d8, 0x2a bytes, Thumb
 * func_ov004_0223a6ac @ 0x0223a6ac, 0x2a bytes, Thumb
 */

extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cbe8(void *x, void *self, int k);
extern int func_ov004_0220e5b0(void *arg0);
extern int func_ov004_0221078c(void *p);
extern int func_ov004_022107d4(void *p);
extern int func_ov004_02210744(void *p);

void func_ov004_0223a704(void *self)
{
    void *p = func_ov004_0223cbe8(func_ov004_0223cd50(), self, 0);
    if (p != 0 && func_ov004_0220e5b0((void *) p) != 0) {
        func_ov004_0221078c(p);
    }
}

void func_ov004_0223a6d8(void *self)
{
    void *p = func_ov004_0223cbe8(func_ov004_0223cd50(), self, 0);
    if (p != 0 && func_ov004_0220e5b0((void *) p) != 0) {
        func_ov004_022107d4(p);
    }
}

void func_ov004_0223a6ac(void *self)
{
    void *p = func_ov004_0223cbe8(func_ov004_0223cd50(), self, 0);
    if (p != 0 && func_ov004_0220e5b0((void *) p) != 0) {
        func_ov004_02210744(p);
    }
}
