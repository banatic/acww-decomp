/* func_ov004_0220ff74 @ 0x0220ff74, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int m[12];
} Mtx43;
extern Mtx43 data_021fbe48;
extern void MTX_MultVec43(void *a, Mtx43 *b, void *c);

void func_ov004_0220ff74(char *self, void *x, void *y)
{
    data_021fbe48 = *(Mtx43 *) (self + 0x254);
    MTX_MultVec43(y, &data_021fbe48, x);
}
