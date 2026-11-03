/* sound_object: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02003e10 @ 0x02003e10, 0x10 bytes, Thumb
 * func_02003e00 @ 0x02003e00, 0x10 bytes, Thumb
 */

typedef void (*Method)(void *self, void *param);

struct VTable {
    void *unk_00;
    void *unk_04;
    void *unk_08;
    Method method;
};

struct Object {
    struct VTable *vtable;
};

typedef struct UnkStruct_02003e00 UnkStruct_02003e00;

typedef int (*ObjFunc)(UnkStruct_02003e00 *);

typedef struct {
    ObjFunc funcs[5];
} VTable;

struct UnkStruct_02003e00 {
    VTable *vtable;
};

void func_02003e10(struct Object *obj, void *param)
{
    obj->vtable->method(obj, param);
}

int func_02003e00(UnkStruct_02003e00 *obj)
{
    return obj->vtable->funcs[4](obj);
}
