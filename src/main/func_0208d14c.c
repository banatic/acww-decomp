/* func_0208d14c @ 0x0208d14c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct VTable;
struct Object;

struct VTable {
    void (*method0)(struct Object *);
    void (*method1)(struct Object *);
    void (*method2)(struct Object *);
    void (*method3)(struct Object *);
};

struct Object {
    struct VTable *vtable;
};

void func_0208d14c(struct Object *obj)
{
    obj->vtable->method3(obj);
}
