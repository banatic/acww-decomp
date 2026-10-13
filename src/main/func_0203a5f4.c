/* func_0203a5f4 @ 0x0203a5f4, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a;
    int b;
} UnkStruct_0203a5f4;

extern int func_020644cc(int);
extern void func_02063ccc(UnkStruct_0203a5f4 *o, int a, int b);
extern void func_020638d4(u16 *out, UnkStruct_0203a5f4 *o, int a, int b, int c, int d, int e);
extern void func_02063cc8(UnkStruct_0203a5f4 *o);

void func_0203a5f4(u16 *dst)
{
    int i;
    for (i = 0; i < 3; i++) {
        int ids[3] = {1, 0, 2};
        u16 h[2];
        UnkStruct_0203a5f4 o;
        func_02063ccc(&o, ids[func_020644cc(3)], 0);
        func_020638d4(&h[0], &o, 0, 0, 1, 1, 0);
        func_02063cc8(&o);
        dst[i] = h[0];
    }
}
