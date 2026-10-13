/* func_ov004_02220318 @ 0x02220318, 0xc8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
extern Vec3 *func_02095794(int a);
extern int func_02030818(Vec3 *v);
extern void func_0203e0a8(void *s, int a);
extern int func_0203ec98(void);
extern void func_0209e474(int *p);
extern int func_0209e350(void *p, int *q);

int func_ov004_02220318(char *s)
{
    int pair[2];
    Vec3 v;
    Vec3 *q;
    int r;
    q = func_02095794(4);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    if (func_02030818(&v) != 0) {
        *(u8 *) (s + 0xac8) = 5;
        func_0203e0a8(s, 0);
        return 1;
    }
    if (func_0203ec98() != 0) {
        return 0;
    }
    if (*(int *) (s + 0xacc) != 0) {
        *(int *) (s + 0xacc) = *(int *) (s + 0xacc) - 1;
        if (*(int *) (s + 0xacc) == 1) {
            *(u8 *) (s + 0xac8) = 3;
            func_0203e0a8(s, 0);
            return 1;
        }
    }
    pair[0] = 0;
    pair[1] = 0;
    func_0209e474(pair);
    r = func_0209e350(s + 0xad0, pair);
    if (*(int *) (s + 0xae8) != 0) {
        *(int *) (s + 0xae8) = *(int *) (s + 0xae8) + 1;
    }
    if (r >= 0x3c || *(int *) (s + 0xae8) > 0x258) {
        *(u8 *) (s + 0xac8) = 3;
        func_0203e0a8(s, 0);
        return 1;
    }
    return 0;
}
