/* func_02081418 @ 0x02081418, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int b[8];
} UnkStruct_02081418;

extern char data_021dc7aa;

extern void *func_02065f7c(void *p);
extern int func_0209527c(UnkStruct_02081418 *it, void *x);
extern int func_020951bc(UnkStruct_02081418 *it);
extern void *func_020807a8(void *self, UnkStruct_02081418 *it);
extern int func_0209526c(UnkStruct_02081418 *it);
extern void func_02081cc4(void *obj);
extern int func_02066830(void *a, void *p);
extern void func_020642d0(void *a, void *b);
extern int func_02065f18(void *p);
extern void func_02061b1c(u16 *dst, u16 *src, int one);
extern int func_0204bcdc(u16 *p);
extern void func_0207df18(void *self, u16 *p);

int func_02081418(void *self, void *p1)
{
    u16 w[2];
    UnkStruct_02081418 it;
    void *obj;
    int ret;
    void *x;
    int f;
    u16 a0, a1;

    obj = 0;
    x = func_02065f7c(p1);
    ret = 0;
    if (x != 0) {
        func_0209527c(&it, x);
        if (func_020951bc(&it) != 0) {
            obj = func_020807a8(self, &it);
        }
        func_0209526c(&it);
    }
    if (obj != 0) {
        func_02081cc4(obj);
        func_02066830((char *) self + 0x634, p1);
        func_020642d0((char *) self + 0x7dc, &data_021dc7aa);
        w[0] = (u16) func_02065f18(p1);
        if (w[0] != 0xfff1) {
            func_02061b1c(&w[1], &w[0], 1);
            if (func_0204bcdc(&w[1]) == 0) {
                f = 0;
                a0 = *(volatile u16 *) &w[1];
                a1 = *(volatile u16 *) &w[1];
                if (a1 >= 0x1100 && a0 <= 0x1143) {
                    f = 1;
                }
                if (f == 0 && !(a0 >= 0x1144 && a0 <= 0x1187)) {
                    goto done;
                }
            }
            func_0207df18(self, &w[0]);
        done:;
        }
        ret = 1;
    }
    return ret;
}
