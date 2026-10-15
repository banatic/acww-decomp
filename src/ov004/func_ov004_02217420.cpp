/* func_ov004_02217420 @ 0x02217420, 0x114 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_0225211c.h"

typedef struct {
    int a, b;
} UnkStruct_02217420;
typedef struct {
    int n;
    UnkStruct_02217420 e[4];
} List;
typedef struct {
    int x, y, z;
} Vec3;

extern "C" {
extern void func_ov004_0220cfec(char *p, int n);
extern int func_ov004_0223cb10(void);
extern int func_ov004_0223ca9c(int a, char *self);
extern int func_ov004_0220d2a8(char *p);
extern int func_ov004_0223cb20(int e);
extern char *func_ov004_0220db94(List *l);
extern void func_ov004_0220db90(List *l);
extern unsigned int func_ov004_0220db68(List *l);
extern UnkStruct_02217420 *func_ov004_0220db5c(List *l, unsigned int i);
extern void func_ov004_0220f27c(char *self, List *l, int a, int b);
extern void func_020ea6e0(Vec3 *v, int ang);
extern int func_ov004_0223c5b8(int a, int b);
extern int func_020308a4(int a, int b);
extern void func_ov004_0220d280(char *p, int a, int b);
extern int func_0203e0a8(char *self, int n);
extern int func_02095ec4(void);
extern int func_ov004_0220e5c8(char *self);

void func_ov004_02217420(Obj_ov004_0225211c *obj)
{
    char *self = (char *) obj;
    // DECLS
    int t;
    volatile int dx, dz;
    List list;
    Vec3 v;
    unsigned int i;
    int a;
    int k;
    int e;
    // ENDDECLS

    func_ov004_0220cfec(self + 0x764, 0);
    e = func_ov004_0223ca9c(func_ov004_0223cb10(), self);
    if (func_ov004_0220d2a8(self + 0x740) != 0 && e != 0 && func_ov004_0223cb20(e) == 0) {
        if (*(int *) (self + 0x780) == 0xb) {
            func_ov004_0220db94(&list);
            func_ov004_0220f27c(self, &list, 0, 0);
            v.x = 0;
            v.y = 0;
            v.z = 0x2000;
            func_020ea6e0(&v, *(short *) (self + 0x8e));
            i = 0;
            dx = 0;
            dz = 0;
            dx = v.x >> 13;
            dz = v.z >> 13;
            k = 0;
            for (; i < func_ov004_0220db68(&list); i++) {
                a = dx + func_ov004_0220db5c(&list, i)->a;
                t = dz + func_ov004_0220db5c(&list, i)->b;
                if (func_ov004_0223c5b8(a, t) != 0 || func_020308a4(a, t) != ~k) {
                    func_ov004_0220d280(self + 0x740, 1, 0);
                    func_ov004_0220db90(&list);
                    return;
                }
            }
            func_ov004_0220db90(&list);
        }
        func_0203e0a8(self, 0);
        func_02095ec4();
    } else if (func_ov004_0220e5c8(self) != 0) {
        obj->vfunc_70(1, 0xff);
    }
}
}
