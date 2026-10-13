/* func_ov004_022335b8 @ 0x022335b8, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_022335b8;
extern void func_0204f794(int *, int, int);
extern int func_ov004_0223c5b8(int, int);
extern void func_ov004_0223362c(void *, void *, int *, UnkStruct_022335b8 *, UnkStruct_022335b8 *, int, int, int, int);
extern int data_ov004_02258af4;

void func_ov004_022335b8(void *p0, int p1, int *p2, int *p3, u8 p5)
{
    int d[2];
    int a[3];
    UnkStruct_022335b8 b, c;
    func_0204f794(a, p2[0], p2[1]);
    if (p5 != 0) {
        a[1] = func_ov004_0223c5b8(p2[0], p2[1]);
    }
    b.x = p3[0];
    b.y = p3[1];
    b.z = p3[2];
    c.x = a[0];
    c.y = a[1];
    c.z = a[2];
    d[0] = p2[0];
    d[1] = p2[1];
    func_ov004_0223362c(&data_ov004_02258af4, p0, d, &b, &c, 0, p1, 0, p5);
}
