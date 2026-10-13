/* func_ov004_0222feac @ 0x0222feac, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0222feac UnkStruct_0222feac;
struct UnkStruct_0222feac {
    void (**vt)(UnkStruct_0222feac *, int);
};
void func_ov004_0222feac(UnkStruct_0222feac *self)
{
    *(int *) ((char *) self + 0x198) = 0x1000;
    *(int *) ((char *) self + 0x428) = 0x1000;
    self->vt[24](self, 2);
}
