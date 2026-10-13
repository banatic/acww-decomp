/* func_ov004_022131c8 @ 0x022131c8, 0x16 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022131c8 UnkStruct_022131c8;
struct UnkStruct_022131c8 {
    void (**vt)(UnkStruct_022131c8 *, int, int);
};
int func_ov004_022131c8(UnkStruct_022131c8 *self)
{
    self->vt[28](self, 0, 0xff);
    return 1;
}
