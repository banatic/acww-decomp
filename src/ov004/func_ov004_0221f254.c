/* func_ov004_0221f254 @ 0x0221f254, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221f254;
struct UnkStruct_0221f254_2 {
    void (*unk_00)(struct UnkStruct_0221f254 *);
    void (*unk_04)(struct UnkStruct_0221f254 *);
    void (*unk_08)(struct UnkStruct_0221f254 *);
};
struct UnkStruct_0221f254 {
    struct UnkStruct_0221f254_2 *vt;
};
extern int func_0201c2a4(void *s, int a);
extern void func_02016108(void *p, int a);
extern void func_ov004_0221fdf4(void *s, int a);

void func_ov004_0221f254(char *s, int sel)
{
    struct UnkStruct_0221f254 *o;
    u8 v;
    switch (sel) {
        case 1:
            o = (struct UnkStruct_0221f254 *) (s + 0x8a8);
            o->vt->unk_08(o);
            func_02016108(s + 0x8a8, func_0201c2a4(s, 4));
            v = *(u8 *) (s + 0xa54);
            if (v == 0) {
                func_ov004_0221fdf4(s, 1);
            } else if (v == 3) {
                func_ov004_0221fdf4(s, 3);
            } else {
                func_ov004_0221fdf4(s, 7);
            }
            break;
        case 0:
            o = (struct UnkStruct_0221f254 *) (s + 0x8a8);
            o->vt->unk_08(o);
            func_02016108(s + 0x8a8, func_0201c2a4(s, 4));
            func_ov004_0221fdf4(s, 1);
            break;
        case 8:
            func_ov004_0221fdf4(s, 4);
            break;
    }
}
