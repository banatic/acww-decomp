/* func_ov004_02215360 @ 0x02215360, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02215360 UnkStruct_02215360;
struct UnkStruct_02215360 {
    void (**vt)(UnkStruct_02215360 *);
};
int func_ov004_02215360(UnkStruct_02215360 *self)
{
    self->vt[32](self);
    return 1;
}
