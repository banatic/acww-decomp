/* func_ov004_02221138 @ 0x02221138, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
extern int func_020ea990(void *a, void *b);
extern void func_0201b458(Vec3 *out, void *s, void *b);
extern int func_0200322c(void *a, void *b);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern u16 data_020c80f8;

int func_ov004_02221138(char *s)
{
    Vec3 out;
    func_020ea990(s + 0x5c, s + 0x89c);
    func_0201b458(&out, s, s + 0x89c);
    func_02019d0c(s + 0x564, 3, 1, 0, 0, 0, func_0200322c(s + 0x5c, s + 0x89c), 0, 0, data_020c80f8, 0);
    return 1;
}
