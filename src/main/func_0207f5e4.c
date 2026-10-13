/* func_0207f5e4 @ 0x0207f5e4, 0xf8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Triple {
    int unk_00[3];
} Triple;

extern Triple data_020e18c0;

extern int func_0208150c(void *self);
extern int func_02003704(int t);
extern int func_0207f6dc(void *self);
extern int func_020644cc(int n);
extern void func_0207f1c8(void *self);
extern int func_0209b5ec(void);
extern int func_0209c330(void);
extern int func_0209c2c0(int y);
extern int func_0207fe94(void *self, int *a, int *b, int i, int s1, int s2);
extern int func_0207fbb4(void *self, int s1, int a, int b);
extern int func_0207ffa0(void *self, int v);
extern void func_0207fb98(u16 *p);

void func_0207f5e4(char *self)
{
    int y;
    int s1;
    int s2;
    Triple arr;
    int count;
    int a;
    int b;
    int i;
    int sel;
    int t;
    u16 *p;
    u16 *base;

    if (func_02003704(func_0208150c(self)) == 0) {
        return;
    }
    if (func_0207f6dc(self) < 7) {
        return;
    }
    if (func_020644cc(2) != 0) {
        return;
    }

    func_0207f1c8(self);
    y = func_0209b5ec();
    s1 = func_0209c330();
    s2 = func_0209c2c0(y);

    arr = data_020e18c0;

    count = 0;
    a = 0;
    b = 0;
    for (i = 0; i < 3; i++) {
        if (func_0207fe94(self, &a, &b, i, s1, s2) != 0) {
            arr.unk_00[i] = func_0207fbb4(self, s1, a, b);
            if (func_0207ffa0(self, arr.unk_00[i]) != 0) {
                count++;
            }
        }
    }

    if (count <= 0) {
        return;
    }
    sel = func_020644cc(count);
    if (sel >= 3) {
        return;
    }

    for (i = 0; i < 3; i++) {
        t = arr.unk_00[i];
        if (func_0207ffa0(self, t) != 0) {
            if (sel == 0) {
                base = (u16 *) (self + 0x78c);
                p = &base[t];
                if (base[t] != 0xfff1) {
                    func_0207fb98(p);
                }
                *p = 0xfff1;
                return;
            }
            sel--;
        }
    }
}
