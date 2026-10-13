/* func_0208786c @ 0x0208786c, 0xe2 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pt;
typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0208786c;
typedef struct {
    int a;
    int b;
} UnkStruct_0208786c_2;
typedef struct {
    int unk_00;
    UnkStruct_0208786c_2 s;
} UnkStruct_0208786c_3;

extern UnkStruct_0208786c_3 *func_0204e414(void);
extern void MI_CpuFill8(void *dst, int v, int n);
extern int func_02087a08(int p0, Pt *pos, UnkStruct_0208786c_3 *obj);
extern int func_02087950(int p0, UnkStruct_0208786c *r, Pt *pos, UnkStruct_0208786c_3 *obj);
extern void func_02087864(int p0, int a, int b);
extern int func_020644cc(int);

int func_0208786c(int p0)
{
    UnkStruct_0208786c_3 *obj;
    u8 mask[4];
    Pt pos;
    UnkStruct_0208786c r;
    int count;
    int w;
    int h;
    int k;
    u8 *m;
    UnkStruct_0208786c_2 *q;

    obj = func_0204e414();
    if (obj != 0) {
        count = 0;
        pos.x = 0;
        pos.y = 0;
        q = &obj->s;
        w = q->a;
        h = q->b;
        MI_CpuFill8(mask, 0, 4);
        for (pos.y = 1; pos.y < h - 1; pos.y++) {
            for (pos.x = 1; pos.x < w - 1; pos.x++) {
                if (func_02087a08(p0, &pos, obj) != 0) {
                    mask[pos.y - 1] = mask[pos.y - 1] | (1 << (pos.x - 1));
                    count++;
                }
            }
        }
        if (count > 0) {
            k = func_020644cc(count);
            pos.y = 1;
            m = mask;
            for (; pos.y < h - 1; pos.y++) {
                for (pos.x = 1; pos.x < w - 1; pos.x++) {
                    if (((m[pos.y - 1] >> (pos.x - 1)) & 1) != 0) {
                        if (k == 0) {
                            func_02087950(p0, &r, &pos, obj);
                            func_02087864(p0, r.a, r.c);
                            return 1;
                        }
                        k--;
                    }
                }
            }
        }
    }
    return 0;
}
