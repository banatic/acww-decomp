/* func_0207f76c @ 0x0207f76c, 0x134 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0207f76c_2 {
    u8 pad_00[0x78c];
    u16 arr[1];
};

struct UnkStruct_0207f76c {
    int a, b;
};

extern void func_02061b1c(struct UnkStruct_0207f76c *, u16 *, int);
extern void func_0207f1c8(struct UnkStruct_0207f76c_2 *);
extern int func_0209b5ec(void);
extern int func_0209c330(void);
extern int func_0209c2c0(int);
extern int func_0204bcdc(struct UnkStruct_0207f76c *);
extern int func_0207fc34(struct UnkStruct_0207f76c_2 *, u16 *, int);
extern int func_02053bc0(struct UnkStruct_0207f76c *);
extern int func_0207f8a0(struct UnkStruct_0207f76c_2 *, u16 *, int, int, int, int);
extern int func_0207fad0(struct UnkStruct_0207f76c_2 *, int, int, int, int);
extern int func_0207ffa0(struct UnkStruct_0207f76c_2 *, int);
extern void func_0207fb70(u16 *);
extern void func_0207f2f4(struct UnkStruct_0207f76c_2 *, u8);
extern void func_0207f2e8(struct UnkStruct_0207f76c_2 *, u8);

int func_0207f76c(struct UnkStruct_0207f76c_2 *o, u16 *p)
{
    struct UnkStruct_0207f76c loc;
    int a, b, c, r, kind, t2, t3;
    u16 w;

    if (*p != 0xfff1) {
        func_02061b1c(&loc, p, 1);
        func_0207f1c8(o);
        a = func_0209b5ec();
        b = func_0209c330();
        c = func_0209c2c0(a);
        if (func_0204bcdc(&loc)) {
            r = func_0207fc34(o, p, b);
            kind = func_02053bc0(&loc);
            t2 = (*p >= 0x450c && *p <= 0x45db);
            if (t2 && kind == 2) {
                return func_0207f8a0(o, p, kind, b, c, r);
            }
            r = func_0207fad0(o, kind, b, c, r);
            if (func_0207ffa0(o, r)) {
                o->arr[r] = *p;
                return 1;
            }
            func_0207fb70(p);
        } else {
            t3 = 0;
            w = *p;
            if (w >= 0x1100 && w <= 0x1143) {
                t3 = 1;
            }
            if (t3) {
                func_0207f2f4(o, (u8) ((w >= 0x1100 && w <= 0x1143) ? w - 0x1100 : -1));
            } else if (w >= 0x1144 && w <= 0x1187) {
                func_0207f2e8(o, (u8) ((w >= 0x1144 && w <= 0x1187) ? w - 0x1144 : -1));
            }
        }
    }
    return 0;
}
