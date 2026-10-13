/* func_ov004_02217e0c @ 0x02217e0c, 0xac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0223cb10(void);
extern void *func_ov004_0223ca9c(int a, void *s);
extern u8 func_020984d4(void);
extern int func_ov004_0223cb20(void *o);
extern int func_ov004_0223cb30(void *o);
extern int func_02073d90(int a);
extern void func_0203e0a8(void *s, int a);
extern unsigned int func_020b2300(void);
extern int data_020ccf94;

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
