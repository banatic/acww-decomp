/* catch_panel_5: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208d164 @ 0x0208d164, 0x10 bytes, Thumb
 * func_0208d15c @ 0x0208d15c, 0x8 bytes, Thumb
 * func_0208d14c @ 0x0208d14c, 0x10 bytes, Thumb
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

extern void func_0208d014(void *ptr);
extern void func_0208cc64(void *);

void func_0208d164(void *ptr)
{
    ((unsigned char *) ptr)[0xa8] = 0;
    func_0208d014(ptr);
}

void func_0208d15c(void *argument0)
{
    func_0208cc64((void *) argument0);
}

void func_0208d14c(struct Object *obj)
{
    obj->vtable->method3(obj);
}
