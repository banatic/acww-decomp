/* func_0208d13c @ 0x0208d13c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct VTable {
    int unk_00;
    int unk_04;
    int (*handler)(void *);
};
struct Object {
    struct VTable *vtable;
};
int func_0208d13c(struct Object *obj)
{
    return obj->vtable->handler(obj);
}
