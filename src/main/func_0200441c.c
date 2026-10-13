/* func_0200441c @ 0x0200441c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef int (*FuncPtr)(void *);
struct UnkStruct_0200441c {
    FuncPtr *vtable;
};
int func_0200441c(struct UnkStruct_0200441c *obj)
{
    return obj->vtable[4](obj);
}
