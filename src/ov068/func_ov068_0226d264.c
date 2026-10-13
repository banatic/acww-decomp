/* func_ov068_0226d264 @ 0x0226d264, 0x110 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
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

extern void func_0208150c(void);
extern int func_02003704(void);
extern int func_0207f270(int obj);
extern int func_020794cc(void);
extern int func_020ba4e4(void);
extern u16 *func_02079464(int a);
extern void func_0207945c(int a, u16 *p);
extern void func_0209bd98(u16 *p, int b);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern void func_02080c60(u16 *p, int obj);

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
        func_0208150c();
        if (func_02003704() != 0) {
            a = func_0207f270(obj);
            b = func_020794cc();
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
