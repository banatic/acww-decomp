/* func_020045ac @ 0x020045ac, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// actually pointer to object, but we need proper type
typedef struct VTable VTable;
struct VTable {
    char pad_00[0x24];
    void (*method)(void *self, int arg);
};
typedef struct Object {
    VTable *vtable;
} Object;
extern Object *data_0213fff0;

void func_020045ac(int arg)
{
    data_0213fff0->vtable->method(data_0213fff0, arg);
}
