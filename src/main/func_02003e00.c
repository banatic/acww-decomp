/* func_02003e00 @ 0x02003e00, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02003e00 UnkStruct_02003e00;
typedef int (*ObjFunc)(UnkStruct_02003e00 *);

typedef struct {
    ObjFunc funcs[5];
} VTable;

struct UnkStruct_02003e00 {
    VTable *vtable;
};

int func_02003e00(UnkStruct_02003e00 *obj)
{
    return obj->vtable->funcs[4](obj);
}
