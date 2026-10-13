/* func_ov004_02226f90 @ 0x02226f90, 0x12 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} UnkStruct_02226f90;

void func_ov004_02226f90(int *d, UnkStruct_02226f90 v)
{
    d[0] = v.a;
    d[1] = v.b;
    d[2] = v.c;
}
