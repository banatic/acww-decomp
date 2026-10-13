/* func_02003e10 @ 0x02003e10, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

void func_02003e10(struct Object *obj, void *param)
{
    obj->vtable->method(obj, param);
}
