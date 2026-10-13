/* func_ov068_0226c0f4 @ 0x0226c0f4, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    fx32 x, y;
} UnkStruct_0226c0f4;
typedef struct {
    fx32 x, y, z;
} Vec;

extern void func_0204f818(fx32 *, fx32 *, void *);
extern int func_ov068_0226c170(void *, UnkStruct_0226c0f4 *);
extern void func_0204f7e0(Vec *, void *);
extern int func_020ea990(Vec *, void *);
extern int func_0201c444(void *);
extern int func_02043830(int, UnkStruct_0226c0f4 *);
extern int func_020436a8(int);
extern void func_020431b8(int);

int func_ov068_0226c0f4(void *a1, void *a2)
{
    UnkStruct_0226c0f4 p;
    UnkStruct_0226c0f4 p2;
    Vec v;
    int r;
    int h;
    void *q = (char *) a2 + 0x5c;
    r = 0;
    p.x = 0;
    p.y = 0;
    func_0204f818(&p.x, &p.y, q);
    if (func_ov068_0226c170(a1, &p) != 0) {
        func_0204f7e0(&v, q);
        if (func_020ea990(&v, q) <= 0xb00) {
            p2.x = p.x;
            p2.y = p.y;
            h = func_02043830((signed char) func_0201c444(a2), &p2);
            if (h >= 0) {
                if (func_020436a8(h) == 1) {
                    r = 1;
                }
                func_020431b8(h);
            }
        }
    }
    return r;
}
