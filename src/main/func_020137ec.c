/* func_020137ec @ 0x020137ec, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 x, y;
} Pt;
typedef struct {
    char pad_00[0x30];
    int unk_30;
    char pad_34[0x10];
} UnkStruct_020137ec;

extern int func_02034240(UnkStruct_020137ec *o, u32 x, u32 y, int a, int b);
extern void func_0203423c(UnkStruct_020137ec *o);
extern int func_0204ed58(void *ctx, u32 x, u32 y);
extern void func_0204f794(void *p, u32 x, u32 y);

int func_020137ec(int p1, void *p2, Pt *p3, Pt *step, int n, Pt *lim, int flagA, void *ctx)
{
    UnkStruct_020137ec obj;
    int cnt;
    int i;
    u32 x, y;

    x = p3->x;
    y = p3->y;
    cnt = 0;
    i = 0;
    while (i < n) {
        x += step->x;
        y += step->y;
        if (x < lim->x && y < lim->y) {
            if (flagA != 0) {
                func_02034240(&obj, x, y, 0, 0);
                if (obj.unk_30 != 0) {
                    cnt = cnt + 1;
                } else {
                    cnt = 0;
                }
                if (cnt >= 4) {
                    func_0203423c(&obj);
                    goto fail;
                }
                func_0203423c(&obj);
            }
            if (func_0204ed58(ctx, x, y) != 0) {
                func_0204f794(p2, x, y);
                return 1;
            }
        }
        i++;
    }
fail:
    return 0;
}
