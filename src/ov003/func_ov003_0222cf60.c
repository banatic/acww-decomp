/* func_ov003_0222cf60 @ 0x0222cf60, 0x25c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off
typedef struct {
    int x, y, z;
} UnkStruct_0222cf60;

extern u8 data_ov003_02260538;
extern u8 data_ov003_02260544;
extern u8 data_ov003_02260548;
extern u8 data_ov003_0226054c;
extern volatile unsigned short data_ov003_02260550;

extern void *func_0204e414(void);
extern int func_020644cc(int n);
extern void *func_020961a8(int a);
extern int func_020ea990(UnkStruct_0222cf60 *a, UnkStruct_0222cf60 *b);
extern int func_ov003_0222c888(void *p1, int kind, int *ox, int *oz, void *w, int q);

int func_ov003_0222cf60(u8 *self, void *p1, int kind, int p3)
{
    unsigned m;
    UnkStruct_0222cf60 v;
    UnkStruct_0222cf60 *pos;
    // Aggregate storage keeps the snapshot distinct from the bit-test scratch.
    struct {
        int value;
    } snapshot;
    int ox;
    unsigned c;
    int cbase3;
    int found;
    int k;
    UnkStruct_0222cf60 v2;
    int r3;
    int r;
    int cbase2;
    void *w;
    void *o;
    int r2;
    int yy;
    int oz;

    m = 0;
    ox = 0;
    oz = 0;
    w = func_0204e414();
    if (w == 0) {
        return 0;
    }
    if (kind == 0x3b) {
        int i;
        r = func_020644cc(0x10 - data_ov003_02260548);
        c = 0;
        i = c;
        snapshot.value = data_ov003_02260550;
        for (; i < 0x10; i++) {
            if (((snapshot.value >> i) & 1) == 0) {
                if (r-- == 0) {
                    data_ov003_02260550 = (unsigned short) (data_ov003_02260550 | (1 << i));
                    break;
                }
            }
            c++;
        }
        ox = c >> 2;
        oz = c & 3;
        data_ov003_02260548 = (u8) (data_ov003_02260548 + 1);
        if (func_ov003_0222c888(p1, kind, &ox, &oz, w, (u8) p3) != 0) {
            o = func_020961a8(4);
            data_ov003_02260544 = 1;
            if (o != 0) {
                v.x = ox;
                v.y = 0;
                v.z = oz;
                if (func_020ea990((UnkStruct_0222cf60 *) ((char *) o + 0x5c), &v) > 0x10000) {
                    pos = (UnkStruct_0222cf60 *) (self + 0x204);
                    pos->x = ox;
                    pos->z = oz;
                    data_ov003_02260550 = 0;
                    data_ov003_02260548 = 0;
                    data_ov003_02260544 = 0;
                    return 1;
                }
            }
        }
        if (data_ov003_02260548 >= 0x10) {
            data_ov003_02260550 = 0;
            data_ov003_02260548 = 0;
            if (data_ov003_02260544 != 0) {
                data_ov003_02260544 = 0;
            } else {
                data_ov003_02260538 = 0;
            }
        }
    } else if (kind == 0x33) {
        int i;
        found = 0;
        k = found;
        cbase2 = k;
        yy = k;
        for (; k < 0x10; k++) {
            r2 = func_020644cc(0x10 - k);
            c = cbase2;
            i = c;
            for (; i < 0x10; i++) {
                if (((m >> i) & 1) == 0) {
                    if (r2-- == 0) {
                        m = m | (1 << i);
                        break;
                    }
                }
                c++;
            }
            ox = c >> 2;
            oz = c & 3;
            if (func_ov003_0222c888(p1, kind, &ox, &oz, w, (u8) p3) != 0) {
                o = func_020961a8(4);
                if (o != 0) {
                    v2.x = ox;
                    v2.y = yy;
                    v2.z = oz;
                    if (func_020ea990((UnkStruct_0222cf60 *) ((char *) o + 0x5c), &v2) > 0x10000) {
                        pos = (UnkStruct_0222cf60 *) (self + 0x204);
                        pos->x = ox;
                        pos->z = oz;
                        return 1;
                    }
                }
                found = 1;
            }
        }
        if (found == 0) {
            data_ov003_0226054c = 0;
        }
    } else {
        int i;
        k = 0;
        cbase3 = 0;
        for (; k < 0x10; k++) {
            r3 = func_020644cc(0x10 - k);
            c = cbase3;
            i = c;
            for (; i < 0x10; i++) {
                if (((m >> i) & 1) == 0) {
                    if (r3-- == 0) {
                        m = m | (1 << i);
                        break;
                    }
                }
                c++;
            }
            ox = c >> 2;
            oz = c & 3;
            if (func_ov003_0222c888(p1, kind, &ox, &oz, w, (u8) p3) != 0) {
                pos = (UnkStruct_0222cf60 *) (self + 0x204);
                pos->x = ox;
                pos->z = oz;
                return 1;
            }
        }
    }
    return 0;
}
