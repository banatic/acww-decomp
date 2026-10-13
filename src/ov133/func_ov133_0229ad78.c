/* func_ov133_0229ad78 @ 0x0229ad78, 0xe bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

struct Overlay133_Struct {
    char pad_00[0x98];
    unsigned short flags;
};

void func_ov133_0229ad78(struct Overlay133_Struct *obj, unsigned short val)
{
    obj->flags |= val;
}
