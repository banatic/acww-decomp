/* func_020a8194 @ 0x020a8194, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a8194 {
    void *vtable;
};

extern void func_020edb3c(struct UnkStruct_020a8194 *obj);

extern unsigned char data_020e3d4c[];

struct UnkStruct_020a8194 *func_020a8194(struct UnkStruct_020a8194 *obj)
{
    obj->vtable = (void *) data_020e3d4c;
    func_020edb3c(obj);
    return obj;
}
