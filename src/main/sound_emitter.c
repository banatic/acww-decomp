/* sound_emitter: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02004290 @ 0x02004290, 0x10 bytes, Thumb
 * func_02004280 @ 0x02004280, 0x10 bytes, Thumb
 */

typedef struct Vtbl {
    char pad_00[12];
    void (*fn)(void *self, void *arg);
} Vtbl;

typedef struct UnkStruct_02004290 {
    Vtbl *vtbl;
} UnkStruct_02004290;

typedef struct VTable VTable;

typedef struct Object Object;

struct VTable {
    int pad_00;
    void (*method)(Object *self);
};

struct Object {
    VTable *vtable;
};

void func_02004290(void *self, void *arg)
{
    UnkStruct_02004290 *obj = (UnkStruct_02004290 *) self;
    obj->vtbl->fn(self, arg);
}

void func_02004280(Object *self)
{
    self->vtable->method(self);
}
