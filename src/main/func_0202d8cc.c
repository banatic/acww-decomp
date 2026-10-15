/* func_0202d8cc @ 0x0202d8cc, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202d8cc;
typedef struct UnkStruct_0202d8cc UnkStruct_0202d8cc;

struct Vtbl {
    unsigned char pad_00[0xA4];
    void (*method)(UnkStruct_0202d8cc *, unsigned long long);
};

struct UnkStruct_0202d8cc {
    struct Vtbl *vtable;
};

extern UnkStruct_0202d8cc *func_02015d90(void *);

void func_0202d8cc(void *object)
{
    UnkStruct_0202d8cc *obj;

    obj = func_02015d90(object);
    if (obj != 0) {
        obj->vtable->method(obj, 0);
    }
}
