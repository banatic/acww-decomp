/* func_02078540 @ 0x02078540, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern int func_02073d90(void *g);
extern void func_020785dc(int *outBuf, void *p0, void *p1, void *p2, void *p3, u8 flag);
extern void func_02073820(void *g);
extern void func_020737f0(void *g, int *buf, int n);
extern void func_02073770(void *g, int a, int n);

void func_02078540(void *p0, void *p1, void *p2, void *p3, u8 flag)
{
    if (func_02073d90(data_020ccf94)) {
        int local;
        void *g;

        func_020785dc(&local, p0, p1, p2, p3, (u8) (flag != 0));
        g = data_020ccf94;
        func_02073820(g);
        func_020737f0(g, &local, 4);
        func_02073770(g, 0x3d, 4);
    }
}
