/* func_0200430c @ 0x0200430c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef int (*func_t)(void *);

struct Vtable {
    func_t func;
};

struct UnkStruct_0200430c {
    struct Vtable *vtable;
};

int func_0200430c(struct UnkStruct_0200430c *obj)
{
    return obj->vtable->func(obj);
}
