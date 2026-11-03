/* scene_sound: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020045c8 @ 0x020045c8, 0x2 bytes, Thumb
 * func_020045ac @ 0x020045ac, 0x1c bytes, Thumb
 */

typedef struct VTable VTable;

struct VTable {
    char pad_00[0x24];
    void (*method)(void *self, int arg);
};

typedef struct Object {
    VTable *vtable;
} Object;

extern Object *data_0213fff0;

void func_020045c8(void) {}

// actually pointer to object, but we need proper type
void func_020045ac(int arg)
{
    data_0213fff0->vtable->method(data_0213fff0, arg);
}
