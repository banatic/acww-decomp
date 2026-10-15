/* func_020b18e4 @ 0x020b18e4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a887c(void *obj);
extern unsigned char data_020e4278;

struct Object {
    void *vtable;
};

struct Object *func_020b18e4(struct Object *obj)
{
    obj->vtable = &data_020e4278;
    func_020a887c(obj);
    return obj;
}
