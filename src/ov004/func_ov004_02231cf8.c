/* func_ov004_02231cf8 @ 0x02231cf8, 0x2d4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define PTR(p, o) (*(char **) ((p) + (o)))
#define HALF(p, o) (*(u16 *) ((p) + (o)))
#define WORD(p, o) (*(u32 *) ((p) + (o)))
#define SBYTE(p, o) (*(signed char *) ((p) + (o)))
extern signed char func_02057124(char *);
extern u16 *func_ov004_022329c4(char *), *func_ov004_02232738(char *);
extern int func_ov004_022329b4(char *), func_ov004_02232728(char *);
extern int FX_Div(int, int);
static inline unsigned is_animated(const u16 *p)
{
    unsigned yes = 0;
    u16 item = *p;
    if (item >= 0x1188 && item <= 0x11a7) {
        yes = 1;
    }
    return yes;
}
void func_ov004_02231cf8(char *self, u32 id, char *rs)
{
    char *resource = PTR(rs, 0xd8);
    char *dict = resource + 4;
    u16 offset = HALF(resource, 0xa);
    char *entry = dict + offset;
    u16 stride = HALF(dict, offset);
    char *record = entry + stride * id;
    char *material = resource + WORD(record, 4);
    unsigned first = (id == func_02057124(self + 0x121c)) ? 1 : 0;
    unsigned second = (id == func_02057124(self + 0x331c)) ? 1 : 0;
    int mode;
    int scaleS, scaleT, scale;
    if (!((first && is_animated(func_ov004_022329c4(self + 0x128))) ||
          (second && is_animated(func_ov004_02232738(self + 0x1228))))) {
        return;
    }
    WORD(PTR(rs, 0xb0), 0x10) &= 0x3fffffff;
    WORD(PTR(rs, 0xb0), 0x10) &= 0xfffbffff;
    WORD(PTR(rs, 0xb0), 0x10) &= 0xfff7ffff;
    WORD(PTR(rs, 0xb0), 0x10) &= 0xfffeffff;
    WORD(PTR(rs, 0xb0), 0x10) &= 0xfffdffff;
    WORD(PTR(rs, 0xb0), 0x10) |= 0x40000000;
    if (first) {
        mode = func_ov004_022329b4(self + 0x128);
    } else {
        mode = func_ov004_02232728(self + 0x1228);
    }
    WORD(PTR(rs, 0xb0), 0x10) |= 0x10000;
    WORD(PTR(rs, 0xb0), 0x10) |= 0x20000;
    if (mode == 1) {
        WORD(PTR(rs, 0xb0), 0x10) |= 0x40000;
        WORD(PTR(rs, 0xb0), 0x10) |= 0x80000;
    }
    WORD(PTR(rs, 0xb0), 0) |= 8;
    HALF(PTR(rs, 0xb0), 0x2c) = HALF(material, 0x20);
    HALF(PTR(rs, 0xb0), 0x2e) = HALF(material, 0x22);
    WORD(PTR(rs, 0xb0), 0x30) = WORD(material, 0x24);
    WORD(PTR(rs, 0xb0), 0x34) = WORD(material, 0x28);
    WORD(PTR(rs, 0xb0), 0) &= ~1u;
    WORD(PTR(rs, 0xb0), 0) |= 6;
    if (first) {
        switch (SBYTE(self, 0x3522)) {
            case 4:
                scaleS = FX_Div(0, 0x64000) + 0x2000;
                scaleT = FX_Div(0, 0x64000) + 0x4000;
                break;
            case 6:
                scaleS = FX_Div(0, 0x64000) + 0x2000;
                scaleT = FX_Div(0, 0x64000) + 0x4000;
                break;
            case 8:
                scaleS = FX_Div(0, 0x64000) + 0x2000;
                scaleT = FX_Div(0, 0x64000) + 0x4000;
                break;
        }
        WORD(PTR(rs, 0xb0), 0x18) = scaleS;
        WORD(PTR(rs, 0xb0), 0x1c) = scaleT;
    } else {
        switch (SBYTE(self, 0x3522)) {
            case 4:
                scale = FX_Div(0, 0x64000) + 0x2000;
                break;
            case 6:
                scale = FX_Div(0, 0x64000) + 0x3000;
                break;
            case 8:
                scale = FX_Div(0, 0x64000) + 0x4000;
                break;
        }
        WORD(PTR(rs, 0xb0), 0x18) = scale;
        WORD(PTR(rs, 0xb0), 0x1c) = scale;
    }
    WORD(rs, 8) &= 0xfffffeff;
}
