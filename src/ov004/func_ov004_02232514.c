/* func_ov004_02232514 @ 0x02232514, 0x194 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02057a50(int, int);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern int func_0203cb3c(void *, u16 *);
extern int func_020b6730(void);
extern void func_020573f0(void *, int, void *, void *);
extern int func_0203cb34(void *);
extern int func_020b9d3c(void *, int, int, int, int, int);
extern void func_ov004_022326a8(void *, u16 *, int);
extern int func_020b65c4(void);
extern void func_020349d0(int, u16 *);
extern int func_0204c100(u16 *);
extern int func_0204c090(u16 *);
extern int func_02072614(void);
extern int func_02072630(int, u8, u8);
extern void func_020573b8(void *, int, int, int);
extern int data_ov004_02255a80;
extern char data_ov004_02255b18;
extern char data_ov004_02255b24;

int func_ov004_02232514(char *self, u16 *item, int a2, int a3)
{
    int same;
    int ok;
    u16 v;
    if (func_02057a50(a2, data_ov004_02255a80) == -1) {
        return 0;
    }
    if (func_0204bcdc(self + 2) != 0) {
        int mine = func_0204bc64(self + 2);
        same = (mine == func_0204bc64(item));
    } else {
        same = (*(u16 *) (self + 2) == *item);
    }
    if (same == 0 || *(int *) (self + 0x20f0) != a3) {
        ok = 0;
        v = *item;
        if (v >= 0x1144 && v <= 0x1187) {
            ok = 1;
        }
        if (ok != 0) {
            if (func_0203cb3c(self + 0x2c, item) != 0) {
                if (func_020b6730() == 0) {
                    func_020573f0(self + 0x20f4, *(int *) (self + 0x20fc), &data_ov004_02255b18, &data_ov004_02255b24);
                }
                if (func_020b9d3c(self + 4, a2, data_ov004_02255a80, func_0203cb34(self + 0x2c), 0, 0) != 0) {
                    *(u16 *) self = *(u16 *) (self + 2);
                    *(u16 *) (self + 2) = *item;
                    func_ov004_022326a8(self, (u16 *) (self + 2), a3);
                    func_020349d0(func_020b65c4(), (u16 *) (self + 2));
                    return 1;
                }
            }
        } else if (v >= 0x1188 && v <= 0x11a7) {
            int c, d, x;
            c = func_0204c100(item);
            d = func_0204c090(item);
            x = func_02072630(func_02072614(), c, d);
            func_020573b8(self + 0x20f4, x, 0, 0);
            *(u16 *) self = *(u16 *) (self + 2);
            *(u16 *) (self + 2) = *item;
            *(int *) (self + 0x20f0) = a3;
            func_ov004_022326a8(self, (u16 *) (self + 2), a3);
            func_020349d0(func_020b65c4(), (u16 *) (self + 2));
            return 1;
        }
        return 0;
    }
    *(u16 *) self = *(u16 *) (self + 2);
    *(u16 *) (self + 2) = *item;
    *(int *) (self + 0x20f0) = a3;
    func_ov004_022326a8(self, (u16 *) (self + 2), a3);
    func_020349d0(func_020b65c4(), (u16 *) (self + 2));
    return 1;
}
