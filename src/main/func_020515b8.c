/* func_020515b8 @ 0x020515b8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020515b8;
typedef unsigned int (*FuncPtr)(struct UnkStruct_020515b8 *);
struct VTable {
    unsigned int pad_00;
    unsigned int pad_04;
    unsigned int pad_08;
    FuncPtr func;
};
struct UnkStruct_020515b8 {
    struct VTable *vtable;
};

unsigned int func_020515b8(struct UnkStruct_020515b8 *obj)
{
    return (obj->vtable->func(obj) + 7) >> 3;
}
