/* func_ov003_02228150 @ 0x02228150, 0x168 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern int data_020c904c;
extern int func_0200322c(void *a, Vec3 *b);
extern int func_020912d4(int id, Vec3 *v, int a, int b);

int func_ov003_02228150(char *obj, void *pos)
{
    Vec3 v;
    Vec3 w;
    short *h;
    Vec3 *p;
    int *hh;
    int k;
    if (obj == 0) {
        return 0;
    }
    if (*(u8 *) (obj + 0x200) == 5 || *(u8 *) (obj + 0x224) == 6 || *(int *) (obj + 0x80) != 3) {
        return 0;
    }
    if (*(u8 *) (obj + 0x23c) == 0) {
        *(u8 *) (obj + 0x200) = 5;
    } else {
        *(u8 *) (obj + 0x224) = 6;
    }
    *(u8 *) (obj + 0x1fd) = 0x1e;
    *(int *) (obj + 0x13c) = 0;
    h = (short *) (obj + 0x138);
    p = (Vec3 *) (obj + 0x120);
    v.x = p->x;
    v.y = p->y;
    v.z = p->z;
    if (*(u8 *) (obj + 0x7f) != 0) {
        *h = 0;
    } else {
        *h = func_0200322c(pos, &v);
    }
    k = *(u8 *) (obj + 0x1ff);
    hh = (int *) (obj + 0x204);
    w.x = v.x;
    w.y = v.y;
    w.z = v.z;
    w.y = data_020c904c;
    switch (k) {
        case 0:
            *hh = func_020912d4(0x1a, &w, 0, 0);
            break;
        case 1:
            *hh = func_020912d4(0x1b, &w, 0, 0);
            break;
        case 2:
            *hh = func_020912d4(0x1c, &w, 0, 0);
            break;
        case 3:
            *hh = func_020912d4(0x1d, &w, 0, 0);
            break;
        case 4:
            *hh = func_020912d4(0x1e, &w, 0, 0);
            break;
        case 5:
            *hh = func_020912d4(0x1f, &w, 0, 0);
            break;
        case 6:
            *hh = func_020912d4(0x21, &w, 0, 0);
            break;
        case 7:
            *hh = func_020912d4(0x20, &w, 0, 0);
            break;
    }
    return 1;
}
