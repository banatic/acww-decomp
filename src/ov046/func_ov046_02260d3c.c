/* func_ov046_02260d3c @ 0x02260d3c, 0x12 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02260d3c UnkStruct_02260d3c;
typedef void (*Func)(UnkStruct_02260d3c *);
struct UnkStruct_02260d3c {
    Func *vtable;
};

void func_ov046_02260d3c(UnkStruct_02260d3c *o)
{
    o->vtable[0x88 / 4](o);
}
