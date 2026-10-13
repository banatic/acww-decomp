/* func_ov004_0220d45c @ 0x0220d45c, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0220d45c {
    int x;
    int y;
    int u1;
    int u2;
};
extern int func_ov004_0220d3c8(int *x, int *y, short *z, int a, int b, int c);
extern int func_ov004_0220d494(void *self, int x, int *y, short z);
int func_ov004_0220d45c(void *self, int a, int b, int c)
{
    short z;
    struct UnkStruct_0220d45c o;
    if (func_ov004_0220d3c8(&o.x, &o.y, &z, a, b, c) != 0) {
        return func_ov004_0220d494(self, o.x, &o.y, z);
    }
    return 0;
}
