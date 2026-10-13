/* func_0202d88c @ 0x0202d88c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct SomeObj SomeObj;
typedef struct SomeObjVtable SomeObjVtable;

struct SomeObj {
    SomeObjVtable *vtable;
};

struct SomeObjVtable {
    char pad_00[0xa4];
    void (*method)(SomeObj *obj, int a, int b);
};

extern SomeObj *func_02015d90(void *a, int b);

void func_0202d88c(void *a, int b)
{
    SomeObj *obj;
    obj = func_02015d90(a, b);
    if (obj) {
        obj->vtable->method(obj, 2, b);
    }
}
