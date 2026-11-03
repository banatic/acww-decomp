/* room_object_02253058_6: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02217eb8 @ 0x02217eb8, 0x74 bytes, Thumb
 * func_ov004_02217e0c @ 0x02217e0c, 0xac bytes, Thumb
 * func_ov004_02217e08 @ 0x02217e08, 0x4 bytes, Thumb
 */

#include "types.h"

extern int data_020ca0ec;
extern int func_ov004_0223cb10(void);
extern void *func_ov004_0223ca9c(int a, void *s);
extern u8 func_020984d4(void);
extern int func_ov004_0223cb20(void *o);
extern int func_ov004_0223cb30(void *o);
extern int func_02073d90(int a);
extern int func_0203e0a8(void *s, int a);
extern unsigned int func_020b2300(void);
extern int data_020ccf94;

int func_ov004_02217eb8(char *self)
{
    unsigned int t;
    t = (*(int *) (self + 0x5c) < (data_020ca0ec >> 1)) ? 1 : 0;
    *(u8 *) (self + 0x846) = (u8) t;
    t = (*(int *) (self + 0x64) < 0x16000) ? 1 : 0;
    *(u8 *) (self + 0x847) = (u8) t;
    if (*(u8 *) (self + 0x846) != 0) {
        if (*(u8 *) (self + 0x847) != 0) {
            *(u8 *) (self + 0x848) = 0;
        } else {
            *(u8 *) (self + 0x848) = 2;
        }
    } else {
        if (*(u8 *) (self + 0x847) != 0) {
            *(u8 *) (self + 0x848) = 1;
        } else {
            *(u8 *) (self + 0x848) = 3;
        }
    }
    return 1;
}

void func_ov004_02217e0c(char *s)
{
    int flag = 0;
    void *o;
    *(int *) (s + 0x858) = 0;
    o = func_ov004_0223ca9c(func_ov004_0223cb10(), s);
    if (o != 0) {
        if (*(u8 *) (s + 0x848) == func_020984d4()) {
            if (func_ov004_0223cb20(o) == 2 || func_ov004_0223cb20(o) == 0) {
                *(int *) (s + 0x858) = 1;
                if (*(u16 *) (s + 0x844) < 7) {
                    flag = 1;
                    *(u16 *) (s + 0x844) = (u16) (*(u16 *) (s + 0x844) + 1);
                }
                if (func_ov004_0223cb30(o) > 0x200) {
                    if (*(u16 *) (s + 0x844) >= 7) {
                        if (func_02073d90(data_020ccf94) == 0) {
                            func_0203e0a8(s, 0);
                        }
                    }
                }
            } else {
                if (func_020b2300() <= 1) {
                    *(int *) (s + 0x858) = 2;
                }
            }
        }
    }
    if (flag == 0) {
        *(u16 *) (s + 0x844) = 0;
    }
}

int func_ov004_02217e08(void *callbackObject)
{
    return 1;
}
