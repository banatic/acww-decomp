/* player_pick: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022458dc @ 0x022458dc, 0x50 bytes, Thumb
 * func_ov004_022458b8 @ 0x022458b8, 0x24 bytes, Thumb
 * func_ov004_02245898 @ 0x02245898, 0x20 bytes, Thumb
 * func_ov004_02245874 @ 0x02245874, 0x24 bytes, Thumb
 * func_ov004_0224586c @ 0x0224586c, 0x8 bytes, Thumb
 * func_ov004_02245850 @ 0x02245850, 0x1a bytes, Thumb
 * func_ov004_0224581c @ 0x0224581c, 0x34 bytes, Thumb
 * func_ov004_02245818 @ 0x02245818, 0x2 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern int func_ov004_0222c110(int, int);
extern void func_0208e508(void *, int);
extern void *func_0208e260(void *);
extern int func_020e8840(unsigned short *argument0);
extern void func_ov004_02245cf4(void *self, int i);
extern int func_02095a8c(int, int);
extern int func_ov004_02246a74(void);
extern void func_020a1918(void);
extern int func_020a182c(void);
extern Vec3 *func_02095794(int);
extern int func_02095ab0(Vec3 *, int, int);

void func_ov004_022458dc(char *self)
{
    int a = 0;
    unsigned char v = *(unsigned char *) (self + 0x31c);
    unsigned char i;
    if (v == 0 || v == 2) {
        a = 1;
    }
    func_ov004_0222c110(a, 1);
    func_0208e508(self + 0x50, 0);
    for (i = 0; i < 5; i++) {
        func_0208e260(self + 0x9c + (i << 7));
    }
    *(short *) (self + 0x324) = 0x19;
}

void func_ov004_022458b8(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020e8840((unsigned short *) (self + 0x324));
    if (v1 == 0x0) {
        func_ov004_02245cf4(self, 0x4);
        return;
    }
    return;
}

int func_ov004_02245898(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02246a74();
    func_02095a8c(0x0, 0x4);
    *(u16 *) (self + 0x324) = 0x5;
    return 0x324;
}

void func_ov004_02245874(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020e8840((unsigned short *) (self + 0x324));
    if (v1 == 0x0) {
        func_ov004_02245cf4(self, 0x5);
        return;
    }
    return;
}

void func_ov004_0224586c(void)
{
    func_020a1918();
}

void func_ov004_02245850(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020a182c();
    if (v1 != 0x0) {
        func_ov004_02245cf4(self, 0x6);
        return;
    }
    return;
}

void func_ov004_0224581c(void)
{
    Vec3 *s = func_02095794(4);
    Vec3 v;
    v.x = s->x;
    v.y = s->y;
    v.z = s->z;
    v.z += 0x6000;
    func_02095ab0(&v, 0x2b8, 4);
}

void func_ov004_02245818(void) {}
