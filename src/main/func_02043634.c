/* func_02043634 @ 0x02043634, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Vec2;
typedef struct {
    u8 flag;
    u16 a;
    u16 b;
} UnkStruct_02043634;

extern int func_02043368(void *, Vec2 *, u8 *);
extern void func_020445c0(u16 *, u16 *, u16);
extern int func_02042f20(void *g, int a0, int a1, Vec2 *w, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9, int p10);
extern int data_021c7c48;

int func_02043634(int a0, int a1, u16 a2)
{
    UnkStruct_02043634 info;
    Vec2 vec;
    Vec2 vec2;
    int ret;

    vec.x = 0;
    vec.y = 0;
    ret = -1;

    if (func_02043368((void *) a1, &vec, &info.flag) != 0) {
        if (a1 == 0x18) {
            func_020445c0(&info.a, &info.b, a2);
        } else {
            info.a = a2;
            info.b = a2;
        }
        vec2.x = vec.x;
        vec2.y = vec.y;
        ret = func_02042f20(&data_021c7c48, a0, a1, &vec2, info.a, info.b, 0, info.flag, 0, -1);
    }
    return ret;
}
