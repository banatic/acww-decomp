/* func_ov050_0226310c @ 0x0226310c, 0x14c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xb4];
    u8 *ptr;
} FieldHolder;
extern void *func_020984e8(void);
extern void *func_02099640(void);
extern void func_0209ad9c(void *a, int b);
extern void *func_0209b4d4(void);
extern void func_02099fe8(void);
extern int func_ov050_02263394(void *a, void *b);
extern int func_02099e9c(u16 *p);
extern int func_02099020(void *a, int b);
extern void *func_02099870(void *a);
extern int func_0207a5d0(void *a, void *b);
extern u16 *func_020992e4(void);
extern void func_0209bb90(void *a, int b);
extern unsigned char data_021e5a2c[];

void func_ov050_0226310c(void *p0, void *p1)
{
    void *h;
    void *x;
    volatile int v[5];
    u16 arr[5];
    u16 *ptr2;
    u16 *q;
    int i;
    h = func_020984e8();
    func_0209ad9c(func_02099640(), 0);
    ptr2 = &arr[0];
    x = func_0209b4d4();
    func_02099fe8();
    if (func_ov050_02263394(p0, p1) != 0) {
        return;
    }
    i = 0;
    q = (u16 *) ((unsigned int) arr);
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
    v[3] = 0;
    v[4] = 0;
    for (; i < 3; i++) {
        q[0] = 0x151d;
        if (((func_02099e9c(ptr2) >= 0) ? (1) : (v[0])) == 0) {
            q[1] = (u16) (0x14fe + i);
            if (((func_02099e9c(&arr[1]) >= 0) ? (1) : (v[1])) == 0) {
                q[2] = (u16) (0x1504 + i);
                if (((func_02099e9c(&arr[2]) >= 0) ? (1) : (v[2])) == 0) {
                    q[3] = (u16) (0x150a + i);
                    if (((func_02099e9c(&arr[3]) >= 0) ? (1) : (v[3])) == 0) {
                        q[4] = (u16) (0x1510 + i);
                        if (((func_02099e9c(&arr[4]) >= 0) ? (1) : (v[4])) == 0) {
                            continue;
                        }
                    }
                }
            }
        }
        ((u8 *) p1)[4] = (u8) (((FieldHolder *) p0)->ptr[0x73e] + 0xf);
        ((FieldHolder *) p0)->ptr[0x73e] = 1;
        return;
    }

    ((FieldHolder *) p0)->ptr[0x73e] = 1;
    if ((func_02099020(h, 0xa) != 0) && (func_0207a5d0((void *) data_021e5a2c, func_02099870(h)) != 0)) {
        func_020984e8();
        if ((*func_020992e4()) != 0) {
            func_0209bb90(x, 1);
            ((u8 *) p1)[4] = 0x1a;
            return;
        }
    }
    ((u8 *) p1)[4] = 0x11;
}
