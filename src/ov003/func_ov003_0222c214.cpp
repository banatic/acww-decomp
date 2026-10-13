/* func_ov003_0222c214 @ 0x0222c214, 0x150 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

struct UnkStruct_0222c214 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual int get(Vec3 *out);
};

inline int has(int f, int m)
{
    if (f & m) {
        return 1;
    }
    return 0;
}

extern "C" {
extern char data_ov003_0225f35c[];
extern int data_020ccf94;
extern UnkStruct_0222c214 *func_02096190(int i);
extern int func_02073d90(int g);
extern int func_02073918(int g, int i);

int func_ov003_0222c214(int i)
{
    Vec3 v;
    char *s;
    UnkStruct_0222c214 *o;
    int g;
    int f;
    if (i < 0 || i >= 4) {
        return 0;
    }
    s = &data_ov003_0225f35c[i * 0x60];
    if (*(u8 *) (s + 0x30) != 0) {
        return 1;
    }
    o = func_02096190(i);
    if (o == 0) {
        return 0;
    }
    g = data_020ccf94;
    if (func_02073d90(g)) {
        if (func_02073918(g, i)) {
            *(u8 *) (s + 0x5c) = 1;
        } else {
            *(u8 *) (s + 0x5c) = 0;
        }
        f = *(int *) ((char *) o + 0xb0);
        if (has(f, 4) && has(f, 2)) {
            Vec3 *p = (Vec3 *) ((char *) o + 0x5c);
            Vec3 *q = (Vec3 *) (s + 0x40);
            q->x = p->x;
            q->y = p->y;
            q->z = p->z;
        } else if (o->get(&v)) {
            Vec3 *q = (Vec3 *) (s + 0x40);
            q->x = v.x;
            q->y = v.y;
            q->z = v.z;
        } else {
            Vec3 *p = (Vec3 *) ((char *) o + 0x5c);
            Vec3 *q = (Vec3 *) (s + 0x40);
            q->x = p->x;
            q->y = p->y;
            q->z = p->z;
        }
    } else {
        *(u8 *) (s + 0x5c) = 1;
        if (o->get(&v)) {
            Vec3 *q = (Vec3 *) (s + 0x40);
            q->x = v.x;
            q->y = v.y;
            q->z = v.z;
        } else {
            Vec3 *p = (Vec3 *) ((char *) o + 0x5c);
            Vec3 *q = (Vec3 *) (s + 0x40);
            q->x = p->x;
            q->y = p->y;
            q->z = p->z;
        }
    }
    *(u8 *) (s + 0x30) = 1;
    {
        Vec3 *q = (Vec3 *) (s + 0x34);
        q->x = v.x;
        q->y = v.y;
        q->z = v.z;
    }
    *(int *) (s + 0x58) = 0;
    *(int *) (s + 0x50) = 0xffffc800;
    return 2;
}
}
