/* func_02004280 @ 0x02004280, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct VTable VTable;
typedef struct Object Object;

struct VTable {
    int pad_00;
    void (*method)(Object *self);
};

struct Object {
    VTable *vtable;
};

void func_02004280(Object *self)
{
    self->vtable->method(self);
}
