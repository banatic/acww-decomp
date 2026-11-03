/* outdoor_villager_records_2: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226d264 @ 0x0226d264, 0x110 bytes, Thumb
 * func_ov068_0226d20c @ 0x0226d20c, 0x58 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0226d264;

typedef struct Vt {
    char pad_00[0x64];
    int (*unk_64)(struct UnkStruct_0226d264 *self);
} Vt;

typedef struct UnkStruct_0226d264 {
    Vt *vt;
} UnkStruct_0226d264;

typedef struct {
    int x, y, z;
} UnkStruct_0226d20c;

typedef struct {
    char pad_00[0x5c];
    UnkStruct_0226d20c pos;
} UnkStruct_0226d20c_2;

extern unsigned int func_0208150c(unsigned int argument0);
extern int func_02003704(void *argument0);
extern int func_0207f270(int obj);
extern int func_020794cc(void *argument0);
extern int func_020ba4e4(void);
extern u16 *func_02079464(int a);
extern void func_0207945c(int a, u16 *p);
extern void func_0209bd98(u16 *p, int b);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern void func_02080c60(u16 *p, int obj);
extern int func_0201cddc(void *argument0);
extern UnkStruct_0226d20c_2 *func_02096190(int);
extern void *data_021c80bc;
extern int func_0204f61c(void *, int, int, int);

void func_ov068_0226d264(UnkStruct_0226d264 *self)
{
    u16 x;
    u16 y;
    u16 z;
    int obj;
    int a;
    int b;
    int mode;
    int r;
    u16 v;
    u16 *p;
    unsigned int ok;
    unsigned int in;

    obj = self->vt->unk_64(self);
    if (obj != 0) {

        if (func_02003704((void *) func_0208150c(obj)) != 0) {
            a = func_0207f270(obj);
            b = func_020794cc((void *) a);
            mode = func_020ba4e4();
            if (mode != 1) {
                p = func_02079464(a);
                in = 0;
                if (*p >= 0x1380 && *p <= 0x139f) {
                    in = 1;
                }
                if (in != 0) {
                    y = 0xfff1;
                    func_0207945c(a, &y);
                }
            }
            p = func_02079464(a);
            in = 0;
            if (*p >= 0x1380 && *p <= 0x139f) {
                in = 1;
            }
            if (in == 0) {
                func_0209bd98(&x, b);
                p = func_02079464(a);
                if (func_0204bcdc(p) != 0) {
                    r = func_0204bc64(p);
                    ok = (r == func_0204bc64(&x)) ? 1 : 0;
                } else {
                    ok = (*p == x) ? 1 : 0;
                }
                if (ok == 0) {
                    func_0207945c(a, &x);
                }
            }
            p = func_02079464(a);
            in = 0;
            if (*p >= 0x1378 && *p <= 0x1378) {
                in = 1;
            }
            if (in != 0 && mode == 1) {
                func_02080c60(&z, obj);
                func_0207945c(a, &z);
            }
        }
    }
}

int func_ov068_0226d20c(void *argument0)
{
    volatile UnkStruct_0226d20c t;
    UnkStruct_0226d20c_2 *o;
    void *g;
    UnkStruct_0226d20c *v;
    unsigned char k;

    k = (unsigned char) (func_0201cddc(argument0) + 0xfd);
    if (k <= 1) {
        o = func_02096190(4);
        g = data_021c80bc;
        if (o != 0 && g != 0) {
            v = &o->pos;
            t.x = v->x;
            t.y = v->y;
            t.z = v->z;
            if (func_0204f61c(g, v->x >> 17, v->z >> 17, 0x200) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
