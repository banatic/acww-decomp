/* func_ov046_022604a8 @ 0x022604a8, 0x108 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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

struct Locals {
    int local2;
    int arr1[3];
    int arr2[3];
    int local1;
    int pad[2];
};

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
