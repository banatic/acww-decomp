/* func_0209583c @ 0x0209583c, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Each field is read into a local before it is stored.

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

extern void *func_02096718(int);
extern int func_02008258(void *, int);
extern int func_020b5e10(void);
extern void func_020b6044(int, int, int *, s16 *);
extern int func_02064558(s16);
extern int func_ov004_022265dc(void *, Vec *, int, int);

int func_0209583c(void)
{
    s16 h;
    int q;
    Vec pos;
    char *p;
    int a;
    int dir;
    Vec *src;
    int x;
    int y;
    int z;

    p = (char *) func_02096718(4);
    if (p != 0) {
        *(int *) (p + 0x7fc) = func_02008258(p, *(int *) (p + 0x7f0));
        if (*(int *) (p + 0x808) == 3) {
            a = *(int *) (p + 0x804);
            h = *(s16 *) (p + 0x8e);
            if (a != -1) {
                func_020b6044(func_020b5e10(), a, &q, &h);
            }
            dir = func_02064558(h);
            src = (Vec *) (p + 0x5c);
            x = src->x;
            pos.x = x;
            y = src->y;
            pos.y = y;
            z = src->z;
            pos.z = z;
            switch (dir) {
                case 2:
                    pos.z = z - 0x6000;
                    break;
                case 0:
                    pos.z = z + 0x6000;
                    break;
                case 3:
                    pos.x = x - 0x6000;
                    break;
                case 1:
                    pos.x = x + 0x6000;
                    break;
            }
            return func_ov004_022265dc(p, &pos, 6, -1);
        }
    }
    return 0;
}
