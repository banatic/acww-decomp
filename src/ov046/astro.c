/* astro: 4 functions, module ov046
 * mwccarm 1.2/base -O4,s
 * func_ov046_022604a8 @ 0x022604a8, 0x108 bytes, Thumb
 * func_ov046_02260474 @ 0x02260474, 0x34 bytes, Thumb
 * func_ov046_02260448 @ 0x02260448, 0x2c bytes, Thumb
 * func_ov046_02260420 @ 0x02260420, 0x28 bytes, Thumb
 */

#include "types.h"

struct Locals {
    int local2;
    int arr1[3];
    int arr2[3];
    int local1;
    int pad[2];
};

extern u8 data_021f6c38;
extern u8 data_021f6c34;
extern struct {
    u16 pad;
    u16 val;
} data_021fbe40;
void *func_020961a8(int);
int func_02014868(void *);
void func_ov046_02261268(void *, int);
int func_020ea990(int *, int *);
int func_020b6590(void);
int func_020b755c(int, int *, int *, int);
extern void func_0203ac04(void);
extern int func_0203e0a8(void *, int);
extern void *func_ov046_022612ec(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern unsigned char data_ov046_022620e0[];

int func_ov046_022604a8(void *self)
{
    struct Locals frame;
    void *obj;
    int r6;
    int ret;
    int s;

    obj = func_020961a8(4);
    if (data_021f6c38 != 0 && data_021f6c34 != 0) {
        r6 = 1;
    } else {
        r6 = 0;
    }
    if (r6 != 0) {
        r6 = 1;
    } else {
        r6 = 0;
    }

    if (obj == 0 || func_02014868((char *) self + 0x618) != 0) {
        func_ov046_02261268((char *) self + 0x658, 5);
        return 0;
    }

    {
        int *p = (int *) ((char *) obj + 0x5c);
        frame.arr1[0] = p[0];
        frame.arr1[1] = p[1];
        frame.arr1[2] = p[2];
        frame.arr2[0] = p[0];
        frame.arr2[1] = p[1];
        frame.arr2[2] = p[2];
        frame.arr2[0] = 0x10800;
        frame.arr2[2] = 0x17000;
    }

    ret = func_020ea990(frame.arr1, frame.arr2);
    s = *(short *) ((char *) obj + 0x8e);

    if (ret >= 0x1000) {
        goto exit_0;
    }

    s &= 0xffff;
    if (s < 0x6000 || s > 0xa000) {
        func_ov046_02261268((char *) self + 0x658, 5);
        return 0;
    }

    if (r6 == 0 && (data_021fbe40.val & 1)) {
        return 1;
    }

    if (r6 != 0) {
        if (func_020b755c(func_020b6590(), &frame.local1, &frame.local2, 0) != 0) {
            if (frame.local2 == 0x16) {
                return 1;
            }
        }
    }

exit_0:
    return 0;
}

int func_ov046_02260474(void *r0)
{
    void *r4 = r0;
    if (func_ov046_022604a8(r4) != 0) {
        func_ov046_02261268((char *) r4 + 0x658, 4);
        func_0203ac04();
        func_0203e0a8(r4, 0);
        return 1;
    }
    return 0;
}

void *func_ov046_02260448(void *obj)
{
    *(void **) obj = (void *) data_ov046_022620e0;
    func_ov046_022612ec((char *) obj + 0x658);
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}

int *func_ov046_02260420(int *obj)
{
    obj[0] = (int) ((int *) data_ov046_022620e0);
    func_ov046_022612ec((char *) obj + 0x658);
    func_0202ee5c(obj);
    return obj;
}
